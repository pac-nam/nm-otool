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

# include "ft_nm.h"

int					ft_nm_parse(t_context *ctx)
{
	uint32_t		magic_number;

	magic_number = *(uint32_t*)ctx->master_start;
	// ft_printf("debug 14\n");
	if (magic_number == MH_MAGIC_64)
		return (ft_nm_64(ctx));
	else if (magic_number == MH_MAGIC)
		return (ft_nm_32(ctx));
	else if (magic_number == FAT_MAGIC)
		return (ft_nm_fat(ctx));
	ft_printf("magic_number %x does not match\n", magic_number);
	return (FAIL);
}