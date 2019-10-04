/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int								ft_secsymbol(t_context *ctx, uint8_t section_number)
{
	int							i;
	t_section_symbol		*tmp;

	i = 0;
	tmp = ctx->sec_symbols;
	while (tmp)
	{
		if (tmp->index == section_number)
		{
			ctx->functions->symbol = tmp->symbol;
			return (0);
		}
		tmp = tmp->next;
	}
	ctx->functions->symbol = UMAJ;
	return (0);
}

int								ft_section(t_context *ctx, struct nlist_64 *list)
{
	if (ctx->header->filetype == MH_DYLIB || ctx->header->filetype == MH_OBJECT)
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000000", 8);
	}
	else
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000001", 8);
	}
	ft_hexdump(&(ctx->functions->before[8]), list->n_value);
	ft_secsymbol(ctx, list->n_sect);
	return (0);
}

int								ft_get_sign(t_context *ctx, struct	nlist_64 *list)
{
	int		error;

	if ((list->n_type & N_TYPE) == N_SECT)
	{
		if ((error = ft_section(ctx, list)))
			return (error);
		else if (list->n_type & N_EXT)
			ctx->functions->symbol -= 32;
	}
	else if (list->n_type & N_STAB)
		ctx->functions->symbol = '-';
	else if (list->n_sect == N_UNDF)
	{
		ctx->functions->symbol = UMAJ;
	}
	else
	{
		ft_strncpy("NO SECTION", &(ctx->functions->before[0]), 10);
	}
	return (0);
}

int								ft_new_function(t_context *ctx)
{
	t_function					*new;

	if (!(new = (t_function*)malloc(sizeof(t_function))))
		return (610);
	ft_memset(&(new->before[0]), ' ', 16);
	new->before[16] = 0;
	new->symbol = UMAJ;
	new->name = NULL;
	new->next = ctx->functions;
	ctx->functions = new;
	return (0);
}

int								ft_symtab(t_context *ctx, struct symtab_command *command)
{
	struct	nlist_64			*array;
	int							error;
	char						*stringtable;
	size_t						i;

	array = (void*)ctx->header + command->symoff;
	stringtable = (void*)ctx->header + command->stroff;
	i = 0;
	while (i < command->nsyms) 
	{
		if ((error = ft_new_function(ctx)) || (error = ft_get_sign(ctx, &array[i])))
			return (error);
		ctx->functions->name = stringtable + array[i].n_un.n_strx;
		i++;
	}
	return (0);
}

int							ft_new_sec_symbol(t_context *ctx, char symbol, uint32_t index)
{
	t_section_symbol		*new;

	if (!(new = (t_section_symbol*)malloc(sizeof(t_section_symbol))))
		return (-1);
	new->symbol = symbol;
	new->index = index;
	new->next = ctx->sec_symbols;
	ctx->sec_symbols = new;
	return (0);
}


int							ft_segment64(t_context *ctx, struct segment_command_64 *segment)
{
	uint64_t					i;
	struct section_64			*section;

	i = 0;
	section = (void*)(segment + 1);
	while (i < segment->nsects)
	{
		if (ft_strequ(section->segname, "__TEXT") && ft_strequ(section->sectname, "__text") && ft_new_sec_symbol(ctx, 't', i + 1))
				return (510);
		else if (ft_strequ(section->segname, "__DATA") && ft_strequ(section->sectname, "__data") && ft_new_sec_symbol(ctx, 'd', i + 1))
				return (511);
		else if (ft_strequ(section->segname, "__DATA") && ft_strequ(section->sectname, "__bss") && ft_new_sec_symbol(ctx, 'b', i + 1))
				return (512);
		section += 1;
		++i;
	}
	ctx->fd = ctx->fd;
	return (0);
}

int								ft_nm_64(t_context *ctx)
{
	uint32_t						command_index;
	struct load_command			*lc;
	int							error;

	ctx->header = (struct mach_header_64*)ctx->master_start;
	lc = (void*)ctx->header + sizeof(*ctx->header);
	command_index = 0;
	while (command_index < ctx->header->ncmds && (void*)lc < ctx->master_end)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			ft_putstr("LC_SEGMENT_64\n");
			if ((error = ft_segment64(ctx, (void*)lc)))
				return (error);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			ft_putstr("LC_SYMTAB\n");
			if ((error = ft_symtab(ctx, (void*)lc)))
				return (error);
			ft_nm_buff_end(ctx);
		}
		lc = (void*)lc + lc->cmdsize;
		command_index++;
	}
	return (0);
}