/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int								ft_symtab_fat(t_context *ctx, struct symtab_command *command)
{
	struct nlist_64				*array;
	char						*stringtable;
	size_t						i;
	t_before_info				tmp;

	// ft_printf("debug 16\n");
	array = ctx->header + command->symoff;
	stringtable = ctx->header + command->stroff;
	i = 0;
	tmp.filetype = ((struct mach_header_64*)ctx->header)->filetype;
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
		|| ft_get_name(ctx, stringtable + array[i].n_un.n_strx, command->stroff))
			return (FAIL);
		i++;
		// ft_putchar('\n');
		// ft_putendl("b");
	}
	return (SUCCESS);
}

int							ft_segment_fat(t_context *ctx, struct segment_command_64 *segment, int *section_index)
{
	uint64_t					i;
	struct section_64			*section;

	i = 0;
	section = (struct section_64*)(segment + 1);
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

int								ft_init_tmp_context(t_context *ctx, struct fat_arch *arch, t_context *new)
{
	new->master_start = ctx->master_start + arch->offset;
	new->master_end = new->master_start + arch->size;
	new->
	return (SUCCESS);
}

int								ft_nm_fat(t_context *ctx)
{
	uint32_t					command_index;
	uint32_t        			nfat_arch;
	struct fat_arch				*arch;
	void						*tmp;
	t_context					tmp_ctx;
	int							best;

	ctx->header = ctx->master_start;
	nfat_arch = ((struct fat_header*)ctx->master_start)->nfat_arch;
	arch = ctx->header + sizeof(struct fat_header);
	command_index = 0;
	best = 0
	// ft_printf("debug 15\n");
	while (command_index < nfat_arch)
	{
		if (ft_check(ctx, arch + 1))
			return (FAIL);
		if (arch->cputype == CPU_TYPE_X86_64)
			best = 100;
		if ((arch->cputype == CPU_TYPE_POWERPC || arch->cputype == CPU_TYPE_I386) && ft_nm_32(ctx))
				return (FAIL);
		else if ( && ft_nm_64(ctx))
				return (FAIL);
		// ft_putendl("c");
		while ((tmp = ctx->sec_symbols))
		{
			ctx->sec_symbols = ((t_section_symbol*)tmp)->next;
			free(tmp);
		}
		arch++;
		command_index++;
		// ft_putendl("d");
	}
	// ft_putendl("e");
	return (SUCCESS);
}