/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					ft_nm_parse(t_context *ctx)
{
	uint32_t		magic_number;

	magic_number = *(uint32_t*)ctx->header;
	if (magic_number == MH_MAGIC_64)
		return (ft_nm_64(ctx));
	else if (magic_number == MH_MAGIC)
		return (ft_nm_32(ctx));
	else if (magic_number == FAT_CIGAM)
		return (ft_nm_fat_reverse(ctx));
	return (FAIL);
}
