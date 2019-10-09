// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_nm_64_reverse.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
// /*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ft_nm.h"

// int								ft_rev_symtab_64(t_context *ctx, struct symtab_command *command)
// {
// 	struct nlist_64				*array;
// 	char						*stringtable;
// 	size_t						i;
// 	t_before_info				tmp;

// 	// ft_printf("debug 16\n");
// 	array = ctx->header + ft_rev32(command->symoff);
// 	stringtable = ctx->header + ft_rev32(command->stroff);
// 	i = 0;
// 	tmp.filetype = ((struct mach_header_64*)ctx->header)->filetype;
// 	while (i < command->nsyms) 
// 	{
// 		// ft_putendl("a");
// 		// ft_printf("verif 17: %d\n", array[i].n_sect);
// 		tmp.value = array[i].n_value;
// 		// ft_printf("nb 35: %lld\n", (int)array[i].n_value);
// 		tmp.section = array[i].n_sect;
// 		tmp.type = array[i].n_type;
// 		// ft_printf("debug 17\n");
// 		if (ft_new_function(ctx) || ft_get_before_and_symbol(ctx, &tmp)
// 		|| ft_get_name(ctx, stringtable + array[i].n_un.n_strx, command->stroff))
// 			return (FAIL);
// 		i++;
// 		// ft_putchar('\n');
// 		// ft_putendl("b");
// 	}
// 	return (SUCCESS);
// }

// int							ft_rev_segment_64(t_context *ctx, struct segment_command_64 *segment, int *section_index)
// {
// 	uint64_t					i;
// 	struct section_64			*section;

// 	i = 0;
// 	section = (struct section_64*)(segment + 1);
// 	if (ft_check(ctx, section))
// 		return (FAIL);
// 	while (i < segment->nsects)
// 	{
// 		if (ft_check(ctx, (void*)(section + 1)))
// 			return (FAIL);
// 		// ft_printf("section %d %s | section %s\n", section_index, section->segname, section->sectname);
// 		if (ft_important_section(ctx, section->segname, section->sectname, *section_index))
// 			return (FAIL);
// 		*section_index += 1;
// 		section += 1;
// 		++i;
// 	}
// 	return (SUCCESS);
// }

// int								ft_nm_64_reverse(t_context *ctx)
// {
// 	uint32_t					command_index;
// 	struct load_command			*lc;
// 	int							section_index;

// 	section_index = 1;
// 	lc = ctx->header + sizeof(struct  mach_header_64);
// 	command_index = ((struct  mach_header_64*)ctx->header)->ncmds;
// 	ft_printf("debug command_index: %d\n", command_index);
// 	while (command_index--)
// 	{
// 		if (ft_check(ctx, lc + 1))
// 			return (FAIL);
// 		if (lc->cmd == LC_SEGMENT_64)
// 		{
// 			ft_printf("segment 64\n");
// 			if (ft_rev_segment_64(ctx, (void*)lc, &section_index))
// 				return (FAIL);
// 		}
// 		if (lc->cmd == LC_SYMTAB)
// 		{
// 			ft_debug_segment(ctx);
// 			if (ft_rev_symtab_64(ctx, (void*)lc))
// 				return (FAIL);
// 		}
// 		ft_putendl("c");
// 		// ft_printf("cmdsize: %d revcmdsize: %d\n", lc->cmdsize, ft_rev32(lc->cmdsize));
// 		lc = (void*)lc + lc->cmdsize;
// 		ft_putendl("d");
// 	}
// 	ft_putendl("e");
// 	return (SUCCESS);
// }