/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_sort_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 13:30:36 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/30 13:30:37 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int			ft_is_before(t_function *f1, t_function *f2)
{
	int				score;

	if (f1->size < f2->size)
		score = ft_strncmp(f1->name, f2->name, f1->size);
	else
		score = ft_strncmp(f1->name, f2->name, f2->size);
	if (score > 0)
		return (1);
	else if (score < 0)
		return (0);
	else if (f1->size < f2->size)
		return (0);
	else if (f1->size > f2->size)
		return (1);
	score = ft_strcmp(f1->before, f2->before);
	if (score > 0)
		return (1);
	else if (score < 0)
		return (0);
	else if (f1->symbol == 'U' && f2->symbol == 'I')
		return (0);
	return (1);
}

static t_function	*ft_mini_sort(t_context *ctx)
{
	t_function		*new_start;
	t_function		*tmp;

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
	return (new_start);
}

void				ft_insert_sort_functions(t_context *ctx)
{
	t_function		*new_start;
	t_function		*tmp;
	t_function		*insert;

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
