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
	// ft_printf("debug 13\n");
	//ft_putnbr(ctx->file_size);
	//ft_putaddr(ctx->header);
	//ft_putchar('\n');
	return (SUCCESS);

}

static int		ft_init(t_context *ctx)
{
	struct stat	buf;

	ctx->sec_symbols = NULL;
	ctx->functions = NULL;
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

int		ft_finish_nm(t_context *ctx)
{
	void		*tmp;

	if (ctx->master_start)
		munmap(ctx->master_start, ctx->file_size);
	// ft_putendl("REMEMBER SEGFAULT MUNMAP");
	while ((tmp = ctx->sec_symbols))
	{
		ctx->sec_symbols = ((t_section_symbol*)tmp)->next;
		free(tmp);
	}
	// ft_putendl("h");
	while ((tmp = ctx->functions))
	{
		ctx->functions = ((t_function*)tmp)->next;
		free(tmp);
	}
	// ft_putendl("h");
	if (ctx->fd >= 0)
		close(ctx->fd);
	return (SUCCESS);
}

int				ft_nm_this_file(const char *file, unsigned int options)
{
	t_context	ctx;

	ctx.file_name = file;
	ctx.options = options;
	// ft_printf("OPT_R 3: %d\n", (ctx.options >> OPT_R) & 0xf);
	// ft_printf("debug ft_nm_this_file\n");
	if ((ft_init(&ctx) != SUCCESS)
	|| (ft_nm_parse(&ctx) != SUCCESS))
	{
		ft_finish_nm(&ctx);
		return (FAIL);
	}
	// ft_printf("OPT_R 4: %d\n", (ctx.options >> OPT_R) & 0xf);
	ft_print_result(&ctx);
	ft_finish_nm(&ctx);
	return (SUCCESS);
}
