/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		ft_otool_buff(t_context *ctx, const char *str)
{
	ctx->print_size = ft_add_buff(&(ctx->to_print[0]), str,
	4096, ctx->print_size);
}

void		ft_otool_buffn(t_context *ctx, const char *str)
{
	ctx->print_size = ft_add_buff(&(ctx->to_print[0]), str,
	4096, ctx->print_size);
	ctx->print_size = ft_add_buff(&(ctx->to_print[0]), "\n",
	4096, ctx->print_size);
}

void		ft_otool_buff_end(t_context *ctx)
{
	ctx->print_size = ft_end_buff(&(ctx->to_print[0]), ctx->print_size);
}
