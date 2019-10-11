/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:29:19 by tbleuse           #+#    #+#             */
/*   Updated: 2019/10/04 13:29:23 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void				ft_buff_symbol(t_context *ctx, char symbol)
{
	char				tmp[4];

	if (symbol == '\0')
		return ;
	tmp[0] = ' ';
	tmp[1] = symbol;
	tmp[2] = ' ';
	tmp[3] = '\0';
	ft_nm_buff(ctx, &(tmp[0]));
}

static void				ft_print_all_functions(t_context *ctx)
{
	t_function			*tmp;

	tmp = ctx->functions;
	while (tmp)
	{
		if (tmp->symbol != '-' && tmp->size > 0)
		{
			ft_nm_buff(ctx, tmp->before);
			ft_buff_symbol(ctx, tmp->symbol);
			ft_nm_nbuff(ctx, tmp->name, tmp->size);
			if (tmp->symbol == 'I')
			{
				ft_nm_buff(ctx, " (indirect for ");
				ft_nm_nbuff(ctx, tmp->name, tmp->size);
				ft_nm_buff(ctx, ")");
			}
			ft_nm_buff(ctx, "\n");
		}
		tmp = tmp->next;
	}
}

static void				ft_revert_functions(t_context *ctx)
{
	t_function			*new_start;
	t_function			*tmp;

	new_start = NULL;
	while ((tmp = ctx->functions))
	{
		ctx->functions = tmp->next;
		tmp->next = new_start;
		new_start = tmp;
	}
	ctx->functions = new_start;
}

void					ft_print_result(t_context *ctx)
{
	ft_options_end(ctx);
	if ((ctx->options >> OPT_MULTIPLES) & 1
	&& *(uint32_t*)ctx->master_start != FAT_CIGAM)
	{
		ft_nm_buff(ctx, "\n");
		ft_nm_buff(ctx, ctx->file_name);
		ft_nm_buff(ctx, ":\n");
	}
	if (!((ctx->options >> OPT_P) & 1))
		ft_insert_sort_functions(ctx);
	if (((ctx->options >> OPT_P) & 1)
	|| ((ctx->options >> OPT_R) & 1))
		ft_revert_functions(ctx);
	ft_print_all_functions(ctx);
	ft_nm_buff_end(ctx);
}
