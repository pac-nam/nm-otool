/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int					ft_otool_info_32(t_context *ctx, char *ptr,
uint32_t size, uint32_t addr)
{
	uint32_t				i;
	char					before[9];
	char					value[4];

	if (ft_check(ctx, ptr + size))
		return (FAIL);
	ft_otool_buff(ctx, ctx->file_name);
	ft_otool_buffn(ctx, ":\nContents of (__TEXT,__text) section");
	i = 0;
	while (i < size)
	{
		ft_hexdump(&(before[0]), addr);
		ft_otool_buff(ctx, &(before[0]));
		addr += 16;
		ft_otool_buff(ctx, "\t");
		while (i < size && (i + 1) % 16 != 0)
			ft_otool_buff(ctx, ft_hexdump_space(&(value[0]), ptr[i++]));
		if (i == size - 1)
			ft_otool_buff(ctx, ft_hexdump_space(&(value[0]), ptr[i++]));
		else if (i < size)
			ft_otool_buffn(ctx, ft_hexdump_space(&(value[0]), ptr[i++]));
	}
	return (SUCCESS);
}

static int					ft_segment_32(t_context *ctx,
struct segment_command *segment, int *section_index)
{
	uint64_t				i;
	struct section			*section;

	i = 0;
	section = (struct section*)(segment + 1);
	if (ft_check(ctx, section))
		return (FAIL);
	while (i < segment->nsects)
	{
		if (ft_check(ctx, (void*)(section + 1)))
			return (FAIL);
		if (ft_strequ(section->segname, "__TEXT")
		&& ft_strequ(section->sectname, "__text"))
			if (ft_otool_info_32(ctx, ctx->header + section->offset,
			section->size, section->addr))
				return (FAIL);
		*section_index += 1;
		section += 1;
		++i;
	}
	return (SUCCESS);
}

int							ft_otool_32(t_context *ctx)
{
	uint32_t				command_index;
	struct load_command		*lc;
	int						section_index;

	section_index = 1;
	lc = ctx->header + sizeof(struct  mach_header);
	command_index = ((struct mach_header*)ctx->header)->ncmds;
	while (command_index--)
	{
		if (ft_check(ctx, lc + 1))
			return (FAIL);
		if (lc->cmd == LC_SEGMENT)
			if (ft_segment_32(ctx, (void*)lc, &section_index))
				return (FAIL);
		lc = (void*)lc + lc->cmdsize;
	}
	return (SUCCESS);
}
