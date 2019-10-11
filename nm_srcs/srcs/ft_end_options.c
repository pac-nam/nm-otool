/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			ft_only_name(t_function *f)
{
	if (f)
	{
		f->symbol = '\0';
		f->before[0] = '\0';
	}
}

static void			ft_opt_g(t_context *ctx)
{
	t_function		*tmp;
	t_function		*to_free;

	while ((tmp = ctx->functions) && (tmp->symbol < 'A' || 'Z' < tmp->symbol))
	{
		ctx->functions = ctx->functions->next;
		free(tmp);
	}
	tmp = ctx->functions;
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
}

static void			ft_opt_mu(t_context *ctx)
{
	t_function		*tmp;
	t_function		*to_free;

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

static void			ft_opt_u(t_context *ctx)
{
	t_function		*tmp;
	t_function		*to_free;

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

void				ft_options_end(t_context *ctx)
{
	t_function		*tmp;

	if ((ctx->options >> OPT_G) & 1)
		ft_opt_g(ctx);
	if ((ctx->options >> OPT_MU) & 1)
		ft_opt_mu(ctx);
	if ((ctx->options >> OPT_U) & 1)
		ft_opt_u(ctx);
	if (((ctx->options >> OPT_J) & 1) && (tmp = ctx->functions))
		while (tmp)
		{
			ft_only_name(tmp);
			tmp = tmp->next;
		}
}
