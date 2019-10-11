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
	ctx->header = ctx->master_start;
	ctx->print_size = 0;
	return (SUCCESS);
}

static int		ft_init(t_context *ctx)
{
	struct stat	buf;

	ctx->sec_symbols = NULL;
	ctx->functions = NULL;
	if ((ctx->fd = open(ctx->file_name, O_RDONLY)) < 0)
		return (FAIL);
	if (fstat(ctx->fd, &buf) < 0)
		return (FAIL);
	if (S_ISDIR(buf.st_mode))
		return (FAIL);
	if ((ctx->master_start = mmap(0, buf.st_size,
	PROT_READ, MAP_PRIVATE, ctx->fd, 0)) == MAP_FAILED)
		return (FAIL);
	return (ft_init_var(ctx, &buf));
}

static int		ft_finish_nm(t_context *ctx)
{
	void		*tmp;

	if (ctx->master_start)
		munmap(ctx->master_start, ctx->file_size);
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
	if (ctx->fd >= 0)
		close(ctx->fd);
	return (SUCCESS);
}

int				ft_nm_this_file(const char *file,
unsigned int options)
{
	t_context	ctx;

	ctx.file_name = file;
	ctx.options = options;
	if ((ft_init(&ctx) != SUCCESS)
	|| (ft_nm_parse(&ctx) != SUCCESS))
	{
		ft_finish_nm(&ctx);
		return (FAIL);
	}
	ft_print_result(&ctx);
	ft_finish_nm(&ctx);
	return (SUCCESS);
}
