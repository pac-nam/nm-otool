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

int								ft_symtab_32(t_context *ctx, struct symtab_command *command)
{
	struct nlist				*array;
	char						*stringtable;
	size_t						i;
	t_before_info				tmp;

	// ft_putendl("debug 3");
	array = ctx->header + command->symoff;
	stringtable = ctx->header + command->stroff;
	i = 0;
	tmp.filetype = ((struct mach_header*)ctx->header)->filetype;
	while (i < command->nsyms) 
	{
		// ft_putendl("a");
		// ft_printf("%s ", stringtable + array[i].n_un.n_strx);
		tmp.value = array[i].n_value;
		tmp.section = array[i].n_sect;
		tmp.type = array[i].n_type;
		if (ft_new_function(ctx) || ft_get_before_and_symbol(ctx, &tmp)
		|| ft_get_name(ctx, stringtable + array[i].n_un.n_strx))
			return (FAIL);
		i++;
		// ft_putchar('\n');
		// ft_putendl("b");
	}
	return (SUCCESS);
}

int							ft_segment_32(t_context *ctx, struct segment_command *segment, int *section_index)
{
	uint64_t					i;
	struct section				*section;

	i = 0;
	section = (struct section*)(segment + 1);
	if (ft_check(ctx, section))
		return (FAIL);
	while (i < segment->nsects)
	{
		if (ft_check(ctx, (void*)(section + 1)))
			return (FAIL);
		// ft_printf("section %d %s | section %s\n", section_index, section->segname, section->sectname);
		if (ft_important_section(ctx, section->segname, section->sectname, *section_index))
			return (FAIL);
		*section_index += 1;
		section += 1;
		++i;
	}
	return (SUCCESS);
}

int								ft_nm_32(t_context *ctx)
{
	uint32_t					command_index;
	struct load_command			*lc;
	int							section_index;

	section_index = 1;
	// ft_printf("debug 15\n");
	lc = ctx->header + sizeof(struct  mach_header);
	command_index = 0;
	while (command_index < ((struct  mach_header*)ctx->header)->ncmds)
	{
		if (ft_check(ctx, lc + 1))
			return (FAIL);
		if (lc->cmd == LC_SEGMENT)
		{
			if (ft_segment_32(ctx, (void*)lc, &section_index))
			{
				// ft_putendl("debug 1");
				return (FAIL);
			}
		}
		if (lc->cmd == LC_SYMTAB)
		{
			// ft_debug_segment(ctx);
			if (ft_symtab_32(ctx, (void*)lc))
			{
				// ft_putendl("debug 2");
				return (FAIL);
			}
		}
		// ft_putendl("c");
		lc = (void*)lc + lc->cmdsize;
		command_index++;
		// ft_putendl("d");
	}
	// ft_putendl("e");
	return (SUCCESS);
}

int								ft_rev_symtab_32(t_context *ctx, struct symtab_command *command)
{
	struct nlist				*array;
	char						*stringtable;
	size_t						i;
	t_before_info				tmp;

	// ft_printf("debug 16\n");
	array = ctx->header + ft_rev32(command->symoff);
	stringtable = ctx->header + ft_rev32(command->stroff);
	i = 0;
	tmp.filetype = ((struct mach_header*)ctx->header)->filetype;
	while (i < command->nsyms) 
	{
		// ft_putendl("a");
		// ft_printf("verif 17: %d\n", array[i].n_sect);
		tmp.value = array[i].n_value;
		// ft_printf("nb 35: %lld\n", (int)array[i].n_value);
		tmp.section = array[i].n_sect;
		tmp.type = array[i].n_type;
		// ft_printf("debug 17\n");
		if (ft_new_function(ctx) || ft_get_before_and_symbol(ctx, &tmp)
		|| ft_get_name(ctx, stringtable + array[i].n_un.n_strx))
			return (FAIL);
		i++;
		// ft_putchar('\n');
		// ft_putendl("b");
	}
	return (SUCCESS);
}

int								ft_nm_32_reverse(t_context *ctx)
{
	uint32_t					command_index;
	struct load_command			*lc;
	int							section_index;

	section_index = 1;
	lc = ctx->header + sizeof(struct  mach_header);
	command_index = ft_rev32(((struct  mach_header*)ctx->header)->ncmds);
	// ft_printf("debug 15\n");
	while (command_index--)
	{
		if (ft_check(ctx, lc + 1))
			return (FAIL);
		if (lc->cmd == LC_SEGMENT)
		{
			// ft_printf("segment 32\n");
			if (ft_segment_32(ctx, (void*)lc, &section_index))
				return (FAIL);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			ft_debug_segment(ctx);
			if (ft_rev_symtab_32(ctx, (void*)lc))
				return (FAIL);
		}
		// ft_putendl("c");
		lc = (void*)lc + lc->cmdsize;
		// ft_putendl("d");
	}
	if (ctx->functions == NULL)
		return (FAIL);
	// ft_putendl("e");
	return (SUCCESS);
}