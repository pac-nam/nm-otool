/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_nm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:29:19 by tbleuse           #+#    #+#             */
/*   Updated: 2019/10/04 13:29:23 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					ft_is_before(t_function *f1, t_function *f2)
{
	int				score;

	score = ft_strcmp(f1->name, f2->name);
	if (score > 0)
		return (1);
	else if (score < 0)
		return (0);
	return (ft_strcmp(f1->before, f2->before) > 0);
}

void				ft_print_all_functions(t_context *ctx)
{
	t_function		*tmp;
	char			symbol[4];

	tmp = ctx->functions;
	while (tmp)
	{
		if (tmp->symbol != '-' && tmp-> size > 0)
		{
			ft_nm_buff(ctx, tmp->before);
			symbol[0] = ' ';
			symbol[1] = tmp->symbol;
			symbol[2] = ' ';
			symbol[3] = '\0';
			ft_nm_buff(ctx, &(symbol[0]));
			// ft_printf("size: %d\n", tmp->size);
			ft_nm_nbuffn(ctx, tmp->name, tmp->size);
		}
		tmp = tmp->next;
	}
}

t_function			*ft_mini_sort(t_context *ctx)
{
	t_function			*new_start;
	t_function			*tmp;

	if (!ctx->functions)
		return (NULL);
	tmp = ctx->functions;
	ctx->functions = tmp->next;
	new_start = tmp;
	tmp->next = NULL;
	if (!ctx->functions)
		return (new_start);
	tmp = ctx->functions;
	ctx->functions = tmp->next;
	// ft_putendl("k");
	// ft_printf("1: %s | 2: %s\n", tmp->name, new_start->name);
	if (ft_is_before(tmp, new_start))
	{
		new_start->next = tmp;
		tmp->next = NULL;
	}
	else
	{
		tmp->next = new_start;
		new_start = tmp;
	}
	// ft_putendl("l");
	return (new_start);
}

void				ft_insert_sort_functions(t_context *ctx)
{
	t_function			*new_start;
	t_function			*tmp;
	t_function			*insert;

	new_start = ft_mini_sort(ctx);
	while ((insert = ctx->functions))
	{
		ctx->functions = insert->next;
		if (ft_is_before(new_start, insert))
		{
			insert->next = new_start;
			new_start = insert;
		}
		else
		{
			tmp = new_start;
			while (tmp->next && ft_is_before(insert, tmp->next))
				tmp = tmp->next;
			insert->next = tmp->next;
			tmp->next = insert;
		}
	}
	ctx->functions = new_start;
}

void	ft_revert_functions(t_context *ctx)
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

void	ft_print_result(t_context *ctx)
{
	// ft_putendl("g");
	// ft_printf("options: %d\n", ctx->options);
	if ((ctx->options >> OPT_MULTIPLES) & 1)
		ft_printf("\n%s:\n", ctx->file_name);
	if (!((ctx->options >> OPT_P) & 1))
		ft_insert_sort_functions(ctx);
	// ft_putendl("h");
	if (((ctx->options >> OPT_P) & 1)
	|| ((ctx->options >> OPT_R) & 1))
		ft_revert_functions(ctx);
	ft_print_all_functions(ctx);
	ft_nm_buff_end(ctx);
	// ft_putnbr(ctx->file_size);
	// ft_putaddr(ctx->master_start);
	// ft_putendl("i");
	// ft_putchar('\n');
}
