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
	if (magic_number == MH_MAGIC_64)
		return (ft_nm_64(ctx));
	if (magic_number == 0xfeedface)
		return (ft_nm_32(ctx));  //must be changed
	ft_printf("magic_number %x does not match\n", magic_number);
	return (310);
}