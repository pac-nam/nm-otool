/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_fat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int				ft_otool_arch_rev(t_context *ctx, struct fat_arch *arch)
{
	ctx->header = ctx->header + ft_rev32(arch->offset);
	if (ctx->header + ft_rev32(arch->size) > ctx->master_end)
		return (FAIL);
	return (ft_otool_parse(ctx));
}

static struct fat_arch	*ft_best_arch(int *to_set, int score,
struct fat_arch *to_return)
{
	*to_set = score;
	return (to_return);
}

int						ft_otool_fat_reverse(t_context *ctx)
{
	uint32_t			arch_index;
	struct fat_arch		*arch;
	struct fat_arch		*best_arch;
	int					best;

	arch = ctx->header + sizeof(struct fat_header);
	arch_index = ft_rev32(((struct fat_header*)ctx->header)->nfat_arch);
	best = 0;
	while (arch_index--)
	{
		if (ft_check(ctx, arch + 1))
			return (FAIL);
		if (ft_rev32(arch->cputype) == CPU_TYPE_X86_64)
			best_arch = ft_best_arch(&best, 100, arch);
		else if (best < 50 && ft_rev32(arch->cputype) == CPU_TYPE_I386)
			best_arch = ft_best_arch(&best, 50, arch);
		else if (best < 10 && ft_rev32(arch->cputype) == CPU_TYPE_X86)
			best_arch = ft_best_arch(&best, 10, arch);
		arch++;
	}
	if (best)
		return (ft_otool_arch_rev(ctx, best_arch));
	return (FAIL);
}
