/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:39:21 by tbleuse           #+#    #+#             */
/*   Updated: 2019/10/04 13:39:23 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void				ft_secsymbol(t_context *ctx, uint8_t section_number)
{
	int					i;
	t_section_symbol	*tmp;

	i = 0;
	tmp = ctx->sec_symbols;
	while (tmp)
	{
		if (tmp->index == section_number)
		{
			ctx->functions->symbol = tmp->symbol;
			return ;
		}
		tmp = tmp->next;
	}
	ctx->functions->symbol = 's';
}

static void				ft_before(t_context *ctx, uint64_t value,
uint32_t filetype)
{
	char				sym;

	sym = ft_tolower(ctx->functions->symbol);
	if (sym == 'u' || sym == 'i')
		return ;
	if (filetype == MH_DYLIB || filetype == MH_OBJECT || !value)
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000000", 8);
	}
	else
	{
		ft_strncpy(&(ctx->functions->before[0]), "00000001", 8);
	}
	if (*(uint32_t*)ctx->header == MH_MAGIC)
	{
		ft_hexdump(&(ctx->functions->before[0]), value);
		ctx->functions->before[8] = '\0';
	}
	else if (*(uint32_t*)ctx->header == MH_MAGIC_64)
		ft_hexdump(&(ctx->functions->before[8]), value);
}

int						ft_get_name(t_context *ctx, char *name)
{
	int					i;

	i = 0;
	if (ft_check(ctx, name))
		return (FAIL);
	while ((void*)(name + i) < ctx->master_end && name[i])
	{
		++i;
	}
	ctx->functions->size = i;
	ctx->functions->name = name;
	return (SUCCESS);
}

int						ft_get_before_and_symbol(t_context *ctx,
t_before_info *info)
{
	if ((info->type & N_TYPE) == N_SECT)
		ft_secsymbol(ctx, info->section);
	else if (info->type & N_STAB)
		ctx->functions->symbol = '-';
	else if ((info->type & N_TYPE) == N_INDR)
		ctx->functions->symbol = 'i';
	else if ((info->type & N_TYPE) == N_ABS)
		ctx->functions->symbol = 'a';
	else if (info->section == N_UNDF && info->type & N_EXT
	&& info->value != 0)
		ctx->functions->symbol = 'c';
	else if (info->section == N_UNDF)
		ctx->functions->symbol = 'u';
	if (info->type & N_EXT)
		ctx->functions->symbol = ft_toupper(ctx->functions->symbol);
	ft_before(ctx, info->value, info->filetype);
	return (SUCCESS);
}
