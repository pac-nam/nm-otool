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

// int								ft_init_tmp_context(t_context *ctx, struct fat_arch *arch, t_context *new)
// {
// 	new->header = ctx->header + arch->offset;
// 	new->master_end = new->header + arch->size;
// 	new->
// 	return (SUCCESS);
// }

int								ft_nm_arch_rev(t_context *ctx, struct fat_arch *arch)
{
	ctx->header = ctx->header + ft_rev32(arch->offset);
	// ft_printf("in nm_fat_arch_rev\n");
	// ft_printf("size %x rev size: %x\n", arch->size, ft_rev32(arch->size));
	if (ctx->header + ft_rev32(arch->size) > ctx->master_end)
		return (FAIL);
	return (ft_nm_parse(ctx));
}

int								ft_nm_fat_reverse(t_context *ctx)
{
	uint32_t					arch_index;
	struct fat_arch				*arch;
	struct fat_arch				*best_arch;
	int							best;

	arch = ctx->header + sizeof(struct fat_header);
	arch_index = ft_rev32(((struct fat_header*)ctx->header)->nfat_arch);
	// ft_printf("arch_index %d\n", arch_index);
	best = 0;
	// ft_printf("CPU_TYPE_X86_64 %x\n", CPU_TYPE_X86_64);
	// ft_printf("CPU_TYPE_I386 %x\n", CPU_TYPE_I386);
	// ft_printf("CPU_TYPE_X86 %x\n", CPU_TYPE_X86);
	// ft_printf("debug 15\n");
	while (arch_index--)
	{
		if (ft_check(ctx, arch + 1))
			return (FAIL);
		// ft_printf("cputype %x rev cputype: %x\n", arch->cputype, ft_rev32(arch->cputype));
		if (ft_rev32(arch->cputype) == CPU_TYPE_X86_64)
		{
			best = 100;
			best_arch = arch;
		}
		else if (best < 50 && ft_rev32(arch->cputype) == CPU_TYPE_I386)
		{
			best = 50;
			best_arch = arch;
		}
		else if (best < 10 && ft_rev32(arch->cputype) == CPU_TYPE_X86)
		{
			best = 10;
			best_arch = arch;
		}
		arch++;
	}
	if (best)
		return (ft_nm_arch_rev(ctx, best_arch));
	return (FAIL);
}