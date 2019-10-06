/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 08:18:23 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/30 08:18:25 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

# include "../../libft/includes/libft.h"

typedef struct							s_section_symbol
{
	uint8_t								index;
	char								symbol;
	struct s_section_symbol				*next;
}										t_section_symbol;

typedef struct							s_function
{
	char								before[17];
	char								symbol;
	char								*name;
	struct s_function					*next;
}										t_function;

typedef struct							s_context
{
	void								*master_start;
	void								*master_end;
	__int32_t							file_size;
	int									fd;
	char								to_print[4096];
	size_t								print_size;
	const char							*file_name;
	t_section_symbol					*sec_symbols;
	void								*header;
	t_function							*functions;
}										t_context;

typedef struct							s_section64
{
	struct s_section64					*next;
	struct section_64					s;
}										t_section64;

typedef struct							s_before_info
{
	uint32_t							value;
	uint32_t							filetype;
	uint32_t							type;
	uint32_t							section;
}										t_before_info;

int					ft_nm_this_file(const char *file);
int					ft_nm_parse(t_context *ctx);
void				ft_nm_buff_end(t_context *ctx);
void				ft_nm_buff(t_context *ctx, const char *str);
void				ft_nm_buffn(t_context *ctx, const char *str);
int					ft_nm_64(t_context *ctx);
char				*ft_hexdump(char *dst, uint32_t src);
char				*ft_hexdump64(char *dst, uint64_t src);
int					ft_check(t_context *ctx, void *ptr);
int					ft_finish_nm(t_context *ctx);
int					ft_get_before_and_symbol(t_context *ctx, t_before_info *info);
int					ft_nm_32(t_context *ctx);
int					ft_new_function(t_context *ctx);
int					ft_new_sec_symbol(t_context *ctx, char symbol, uint32_t index);
int					ft_important_section(t_context *ctx, char *segment, char *section, int section_index);
void				ft_debug_segment(t_context *ctx);
// void				ft_before(t_context *ctx, uint32_t value, uint32_t filetype);

#endif
