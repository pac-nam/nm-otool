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

void				ft_print_all_functions(t_context *ctx)
{
	t_function		*tmp;
	char			symbol[4];

	tmp = ctx->functions;
	while (tmp)
	{
		if (tmp->symbol != '-' && tmp->size > 0)
		{
			ft_nm_buff(ctx, tmp->before);
			symbol[0] = ' ';
			symbol[1] = tmp->symbol;
			symbol[2] = ' ';
			symbol[3] = '\0';
			if (tmp->symbol)
				ft_nm_buff(ctx, &(symbol[0]));
			// ft_printf("size: %d\n", tmp->size);
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

void	ft_opt_g(t_context *ctx)
{
	t_function			*tmp;
	t_function			*to_free;

	// ft_putendl("debug g start");
	while ((tmp = ctx->functions) && (tmp->symbol < 'A' || 'Z' < tmp->symbol))
	{
		ctx->functions = ctx->functions->next;
		free(tmp);
	}
	tmp = ctx->functions;
	// ft_putendl("debug g 1");
	while (tmp && tmp->next)
	{
		if ((tmp->next->symbol < 'A' || 'Z' < tmp->next->symbol))
		{
			to_free = tmp->next;
			tmp->next = to_free->next;
			free(to_free);
		}
		else
			tmp = tmp->next;
	}
	// ft_putendl("debug g end");
}


void	ft_only_name(t_function *f)
{
	if (f)
	{
		f->symbol = '\0';
		f->before[0] = '\0';
	}
}

void	ft_opt_mu(t_context *ctx)
{
	t_function			*tmp;
	t_function			*to_free;

	while ((tmp = ctx->functions) && tmp->symbol == 'U')
	{
		ctx->functions = ctx->functions->next;
		free(tmp);
	}
	tmp = ctx->functions;
	while (tmp && tmp->next)
	{
		if (tmp->next->symbol == 'U')
		{
			to_free = tmp->next;
			tmp->next = to_free->next;
			free(to_free);
		}
		else
			tmp = tmp->next;
	}
}

void	ft_opt_u(t_context *ctx)
{
	t_function			*tmp;
	t_function			*to_free;

	while ((tmp = ctx->functions) && tmp->symbol != 'U')
	{
		ctx->functions = ctx->functions->next;
		free(tmp);
	}
	if ((tmp = ctx->functions))
		ft_only_name(tmp);
	while (tmp && tmp->next)
	{
		if (tmp->next->symbol != 'U')
		{
			to_free = tmp->next;
			tmp->next = to_free->next;
			free(to_free);
		}
		else
		{
			ft_only_name(tmp->next);
			tmp = tmp->next;
		}
	}
}

void	ft_print_result(t_context *ctx)
{
	t_function			*tmp;
	// ft_putendl("g");
	// ft_printf("options: %d\n", ctx->options);

	if ((ctx->options >> OPT_G) & 1)
		ft_opt_g(ctx);
	// ft_putendl("a1");
	if ((ctx->options >> OPT_MU) & 1)
		ft_opt_mu(ctx);
	// ft_putendl("a2");
	if ((ctx->options >> OPT_U) & 1)
		ft_opt_u(ctx);
	// ft_putendl("a3");
	if (((ctx->options >> OPT_J) & 1) && (tmp = ctx->functions))
		while (tmp)
		{
			ft_only_name(tmp);
			tmp = tmp->next;
		}
	// ft_putendl("a4");
	if ((ctx->options >> OPT_MULTIPLES) & 1 && *(uint32_t*)ctx->master_start != FAT_CIGAM)
		ft_printf("\n%s:\n", ctx->file_name);
	// ft_putendl("a5");
	if (!((ctx->options >> OPT_P) & 1))
		ft_insert_sort_functions(ctx);
	// ft_putendl("a6");
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
