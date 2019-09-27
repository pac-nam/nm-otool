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

static int		ft_initvar(t_context *ctx)
{
	ctx->file_size = ctx->buf.st_size;
	ctx->master_end = ctx->master_start + ctx->file_size;
	ctx->print_size = 0;
	return (0);
}

static int		ft_init(t_context *ctx)
{
	int			fd;
	char		*result;

	if ((ctx->fd = open(ctx->file_name, O_RDONLY)) < 0)
	{
		ft_putendl_fd("open error", 2);
		return (0110);
	}
	if (fstat(ctx->fd, &ctx->buf) < 0)
	{
		ft_putendl_fd("fstat error", 2);
		return (0120);
	}
	if (S_ISDIR(ctx->buf.st_mode))
	{
		ft_putendl_fd("cannot open directory", 2);
		return (0130);
	}
	if ((ctx->master_start = mmap(0, ctx->buf.st_size, PROT_READ, MAP_PRIVATE, ctx->fd, 0)) == MAP_FAILED)
	{
		ft_putendl_fd("mmap error", 2);
		return (0140);
	}
	return (ft_init_var(ctx));
}

static int		ft_finish_nm(t_context *ctx)
{
	ft_end_buff(ctx->to_print, ctx->print_size);
	free(ctx);
	return (0);
}

int				ft_nm_this_file(const char *file)
{
	int			error;
	t_context	*ctx;

	if (!(ctx = (t_context*)malloc(sizeof(t_context))))
	{
		ft_putendl_fd("malloc t_context error", 2);
		return (0210);
	}
	ctx->file_name = file;
	if ((error = ft_init(ctx))
	|| (error = ft_nm_compute(ctx))
	|| (error = ft_finish_nm(ctx)))
		return (error);
	return (0);
}