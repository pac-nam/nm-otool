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

void							ft_debug_segment(t_context *ctx)
{
	t_section_symbol		*tmp;

	tmp = ctx->sec_symbols;
	while (tmp)
	{
		ft_printf("section %c-%d\n", tmp->symbol, tmp->index);
		tmp = tmp->next;
	}
}

int								ft_new_function(t_context *ctx)
{
	t_function					*new;

	if (!(new = (t_function*)malloc(sizeof(t_function))))
		return (610);
	ft_memset(&(new->before[0]), ' ', 16);
	new->before[16] = 0;
	new->symbol = 'U';
	new->name = NULL;
	new->next = ctx->functions;
	ctx->functions = new;
	return (0);
}

int							ft_new_sec_symbol(t_context *ctx, char symbol, uint32_t index)
{
	t_section_symbol		*new;

	if (!(new = (t_section_symbol*)malloc(sizeof(t_section_symbol))))
		return (-1);
	new->symbol = symbol;
	new->index = index;
	new->next = ctx->sec_symbols;
	ctx->sec_symbols = new;
	return (0);
}

int							ft_important_section(t_context *ctx, char *segment, char *section, int section_index)
{
	if (ft_strequ(segment, "__TEXT") && ft_strequ(section, "__text"))
	{
		if (ft_new_sec_symbol(ctx, 't', section_index))
			return (510);
	}
	else if (ft_strequ(segment, "__DATA") && ft_strequ(section, "__data"))
	{
		if (ft_new_sec_symbol(ctx, 'd', section_index))
			return (511);
	}
	else if (ft_strequ(segment, "__DATA") && ft_strequ(section, "__bss"))
	{
		if (ft_new_sec_symbol(ctx, 'b', section_index))
			return (512);
	}
	return (0);
}
