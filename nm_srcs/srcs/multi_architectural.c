/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_architectural.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int						ft_new_function(t_context *ctx)
{
	t_function			*new;
	int					length;

	length = 0;
	if (!(new = (t_function*)malloc(sizeof(t_function))))
	{
		return (FAIL);
	}
	if (*(uint32_t*)ctx->header == MH_MAGIC_64)
		length = 16;
	else if (*(uint32_t*)ctx->header == MH_MAGIC)
		length = 8;
	ft_memset(&(new->before[0]), ' ', length);
	new->before[length] = 0;
	new->symbol = 'U';
	new->name = NULL;
	new->size = 0;
	new->next = ctx->functions;
	ctx->functions = new;
	return (SUCCESS);
}

int						ft_new_sec_symbol(t_context *ctx, char symbol,
uint32_t index)
{
	t_section_symbol	*new;

	if (!(new = (t_section_symbol*)malloc(sizeof(t_section_symbol))))
		return (FAIL);
	new->symbol = symbol;
	new->index = index;
	new->next = ctx->sec_symbols;
	ctx->sec_symbols = new;
	return (SUCCESS);
}

int						ft_important_section(t_context *ctx, char *segment,
char *section, int section_index)
{
	if (ft_strequ(segment, "__TEXT") && ft_strequ(section, "__text"))
	{
		if (ft_new_sec_symbol(ctx, 't', section_index))
			return (FAIL);
	}
	else if (ft_strequ(segment, "__DATA") && ft_strequ(section, "__data"))
	{
		if (ft_new_sec_symbol(ctx, 'd', section_index))
			return (FAIL);
	}
	else if (ft_strequ(segment, "__DATA") && ft_strequ(section, "__bss"))
	{
		if (ft_new_sec_symbol(ctx, 'b', section_index))
			return (FAIL);
	}
	return (SUCCESS);
}
