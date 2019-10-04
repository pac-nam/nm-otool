/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbol_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:39:21 by tbleuse           #+#    #+#             */
/*   Updated: 2019/10/04 13:39:23 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int								ft_secsymbol(t_context *ctx, uint8_t section_number)
{
	int							i;
	t_section_symbol		*tmp;

	i = 0;
	tmp = ctx->sec_symbols;
	while (tmp)
	{
		if (tmp->index == section_number)
		{
			ctx->functions->symbol = tmp->symbol;
			return (0);
		}
		tmp = tmp->next;
	}
	ctx->functions->symbol = 's';
	return (0);
}

void							ft_before(t_context *ctx, struct nlist_64 *list)
{
	if (ctx->header->filetype == MH_DYLIB || ctx->header->filetype == MH_OBJECT)
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000000", 8);
	}
	else
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000001", 8);
	}
	ft_hexdump(&(ctx->functions->before[8]), list->n_value);
}

int								ft_get_sign(t_context *ctx, struct	nlist_64 *list)
{
	char	sym;

	// ft_printf("desc %d ", list->n_desc);

	if ((list->n_type & N_TYPE) == N_SECT)
		ft_secsymbol(ctx, list->n_sect);
	else if (list->n_type & N_STAB)
		ctx->functions->symbol = '-';
	else if(list->n_sect == N_UNDF && list->n_type & N_EXT && list->n_value != 0)
		ctx->functions->symbol = 'c';
	else if (list->n_sect == N_UNDF)
		ctx->functions->symbol = 'U';
	sym = ctx->functions->symbol;
	if (sym == 't' || sym == 'b' || sym == 'd' || sym == 'c' || sym == 's')
		ft_before(ctx, list);
	if (list->n_type & N_EXT)
		ctx->functions->symbol = ft_toupper(ctx->functions->symbol);
	return (0);
}