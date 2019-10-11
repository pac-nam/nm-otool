/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:57:02 by tbleuse           #+#    #+#             */
/*   Updated: 2019/10/04 12:57:10 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int					ft_check(t_context *ctx, void *ptr)
{
	if (ptr < ctx->header || ctx->master_end < ptr)
		return (FAIL);
	return (SUCCESS);
}
