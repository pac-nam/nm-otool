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

int								ft_symtab_64(t_context *ctx, struct symtab_command *command)
{
	struct nlist_64				*array;
	int							error;
	char						*stringtable;
	size_t						i;

	array = ctx->header + command->symoff;
	stringtable = ctx->header + command->stroff;
	i = 0;
	while (i < command->nsyms) 
	{
		// ft_printf("%s ", stringtable + array[i].n_un.n_strx);
		if ((error = ft_new_function(ctx))
		|| (error = ft_get_sign(ctx, (&array[i])->n_type, (&array[i])->n_sect,
		(&array[i])->n_value)))
			return (error);
		ctx->functions->name = stringtable + array[i].n_un.n_strx;
		i++;
		// ft_putchar('\n');
	}
	return (0);
}

int							ft_segment_64(t_context *ctx, struct segment_command_64 *segment, int *section_index)
{
	uint64_t					i;
	struct section_64			*section;
	int							error;

	i = 0;
	section = (struct section_64*)(segment + 1);
	while (i < segment->nsects)
	{
		if (ft_check(ctx, (void*)(section + 1)))
			return (810);
		// ft_printf("section %d %s | section %s\n", section_index, section->segname, section->sectname);
		if ((error = ft_important_section(ctx, section->segname, section->sectname, *section_index)))
			return (error);
		*section_index += 1;
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
	int							section_index;

	section_index = 1;
	ctx->header = ctx->master_start;
	lc = ctx->header + sizeof(struct  mach_header_64);
	command_index = 0;
	while (command_index < ((struct  mach_header_64*)ctx->header)->ncmds && (void*)lc < ctx->master_end)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if ((error = ft_segment_64(ctx, (void*)lc, &section_index)))
				return (error);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			// ft_debug_segment(ctx);
			if ((error = ft_symtab_64(ctx, (void*)lc)))
				return (error);
		}
		lc = (void*)lc + lc->cmdsize;
		command_index++;
	}
	return (0);
}