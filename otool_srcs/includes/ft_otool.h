/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 08:18:23 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/30 08:18:25 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

# include "../../libft/includes/libft.h"

# define FAIL -1
# define SUCCESS 0

# define OTOOL_HEXA "0123456789abcdef"

typedef struct		s_context
{
	void			*master_start;
	void			*master_end;
	__int32_t		file_size;
	int				fd;
	char			to_print[4096];
	size_t			print_size;
	const char		*file_name;
	void			*header;
}					t_context;

int					ft_otool_this_file(const char *file);
int					ft_otool_parse(t_context *ctx);
int					ft_otool_64(t_context *ctx);
int					ft_otool_32(t_context *ctx);
int					ft_otool_fat_reverse(t_context *ctx);
int					ft_check(t_context *ctx, void *ptr);
char				*ft_hexdump(char *dst, uint32_t src);
char				*ft_hexdump64(char *dst, uint64_t src);
char				*ft_hexdump_space(char *dst, int c);
void				ft_otool_buff_end(t_context *ctx);
uint64_t			ft_rev64(uint64_t nb);
uint32_t			ft_rev32(uint32_t nb);
void				ft_otool_buff(t_context *ctx, const char *str);
void				ft_otool_buffn(t_context *ctx, const char *str);

#endif
