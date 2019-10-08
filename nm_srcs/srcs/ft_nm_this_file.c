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
	// ft_printf("debug 13\n");
	//ft_putnbr(ctx->file_size);
	//ft_putaddr(ctx->master_start);
	//ft_putchar('\n');
	return (SUCCESS);

}

static int		ft_init(t_context *ctx)
{
	struct stat	buf;

	if ((ctx->fd = open(ctx->file_name, O_RDONLY)) < 0)
	{
		ft_putendl_fd("open error", 2);
		return (FAIL);
	}
	// ft_putendl("debug here 1");
	if (fstat(ctx->fd, &buf) < 0)
	{
		ft_putendl_fd("fstat error", 2);
		return (FAIL);
	}
	// ft_putendl("debug here 2");
	if (S_ISDIR(buf.st_mode))
	{
		ft_putendl_fd("cannot open directory", 2);
		return (FAIL);
	}
	// ft_putendl("debug here 3");
	// ft_printf("st_size %lld\n", buf.st_size);
	if ((ctx->master_start = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, ctx->fd, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("mmap error", 2);
		return (FAIL);
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

int				ft_nm_this_file(const char *file)
{
	t_context	ctx;

	ctx.file_name = file;
	if ((ft_init(&ctx) != SUCCESS)
	|| (ft_nm_parse(&ctx) != SUCCESS)
	|| (ft_finish_nm(&ctx) != SUCCESS))
		return (FAIL);
	return (SUCCESS);
}
