/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_this_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:14 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:16 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		ft_init_var(t_context *ctx, struct stat	*buf)
{
	ctx->file_size = buf->st_size;
	ctx->master_end = ctx->master_start + ctx->file_size;
	ctx->print_size = 0;
	ctx->sec_symbols = NULL;
	ctx->functions = NULL;
	//ft_putnbr(ctx->file_size);
	//ft_putaddr(ctx->master_start);
	//ft_putchar('\n');
	return (0);
}

static int		ft_init(t_context *ctx)
{
	struct stat	buf;

	if ((ctx->fd = open(ctx->file_name, O_RDONLY)) < 0)
	{
		ft_putendl_fd("open error", 2);
		return (110);
	}
	if (fstat(ctx->fd, &buf) < 0)
	{
		ft_putendl_fd("fstat error", 2);
		return (120);
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_putendl_fd("cannot open directory", 2);
		return (130);
	}
	if ((ctx->master_start = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, ctx->fd, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("mmap error", 2);
		return (140);
	}
	return (ft_init_var(ctx, &buf));
}

// void				ft_print_function(t_function func)
// {
// 	ft_nm_buff(ctx, tmp->before);
// 	ft_nm_buff(ctx, " ");
// 	ft_nm_buff(ctx, tmp->symbol);
// 	ft_nm_buff(ctx, " ");
// 	ft_nm_buff(ctx, tmp->name);
// }

void				ft_print_all_functions(t_context *ctx)
{
	t_function		*tmp;
	char			symbol[4];

	tmp = ctx->functions;
	while (tmp)
	{
		if (tmp->symbol != '-')
		{
			ft_nm_buff(ctx, tmp->before);
			symbol[0] = ' ';
			symbol[1] = tmp->symbol;
			symbol[2] = ' ';
			symbol[3] = '\0';
			ft_nm_buff(ctx, &(symbol[0]));
			ft_nm_buffn(ctx, tmp->name);
		}
		tmp = tmp->next;
	}
}

static int		ft_finish_nm(t_context *ctx)
{
	void		*tmp;

	ft_print_all_functions(ctx);
	ft_nm_buff_end(ctx);
	//ft_putnbr(ctx->file_size);
	//ft_putaddr(ctx->master_start);
	//ft_putchar('\n');
	munmap(ctx->master_start, ctx->file_size);
	//ft_putendl("REMEMBER SEGFAULT MUNMAP");
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
	close(ctx->fd);
	return (0);
}

int				ft_nm_this_file(const char *file)
{
	int			error;
	t_context	ctx;

	ctx.file_name = file;
	if ((error = ft_init(&ctx))
	|| (error = ft_nm_parse(&ctx))
	|| (error = ft_finish_nm(&ctx)))
		return (error);
	return (0);
}
