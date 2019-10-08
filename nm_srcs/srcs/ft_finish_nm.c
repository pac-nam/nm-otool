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
	if (ft_strcmp(tmp->name, new_start->name) > 0)
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

int				ft_insert_sort_functions(t_context *ctx)
{
	t_function			*new_start;
	t_function			*tmp;
	t_function			*insert;

	new_start = ft_mini_sort(ctx);
	while ((insert = ctx->functions))
	{
		ctx->functions = insert->next;
		if (ft_strcmp(new_start->name, insert->name) >= 0)
		{
			insert->next = new_start;
			new_start = insert;
		}
		else
		{
			tmp = new_start;
			while (tmp->next && ft_strcmp(insert->name, tmp->next->name) > 0)
				tmp = tmp->next;
			insert->next = tmp->next;
			tmp->next = insert;
		}
	}
	ctx->functions = new_start;
	return (SUCCESS);
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

int		ft_finish_nm(t_context *ctx)
{
	void		*tmp;

	// ft_putendl("g");
	// if (!option_P)
		ft_insert_sort_functions(ctx);
	// ft_putendl("h");
	// if (option_P || option_R)
		// ft_revert_functions(ctx);
	ft_print_all_functions(ctx);
	ft_nm_buff_end(ctx);
	// ft_putnbr(ctx->file_size);
	// ft_putaddr(ctx->master_start);
	// ft_putendl("i");
	// ft_putchar('\n');
	munmap(ctx->master_start, ctx->file_size);
	// ft_putendl("REMEMBER SEGFAULT MUNMAP");
	while ((tmp = ctx->sec_symbols))
	{
		ctx->sec_symbols = ((t_section_symbol*)tmp)->next;
		free(tmp);
	}
	while ((tmp = ctx->functions))
	{
		ctx->functions = ((t_function*)tmp)->next;
		free(tmp);
	}
	// ft_putendl("h");
	close(ctx->fd);
	return (SUCCESS);
}
