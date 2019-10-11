/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int					ft_otool_parse(t_context *ctx)
{
	uint32_t		magic_number;

	magic_number = *(uint32_t*)ctx->header;
	if (magic_number == MH_MAGIC_64)
		return (ft_otool_64(ctx));
	else if (magic_number == MH_MAGIC)
		return (ft_otool_32(ctx));
	else if (magic_number == FAT_CIGAM)
		return (ft_otool_fat_reverse(ctx));
	return (FAIL);
}
