/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 08:18:23 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/30 08:18:25 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_STRUCT_H
# define FT_NM_STRUCT_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

typedef struct				s_section_symbol
{
	uint8_t					index;
	char					symbol;
	struct s_section_symbol	*next;
}							t_section_symbol;

typedef struct				s_function
{
	char					before[17];
	char					symbol;
	char					*name;
	int						size;
	struct s_function		*next;
}							t_function;

typedef struct				s_context
{
	void					*master_start;
	void					*master_end;
	__int32_t				file_size;
	int						fd;
	char					to_print[4096];
	size_t					print_size;
	const char				*file_name;
	t_section_symbol		*sec_symbols;
	void					*header;
	t_function				*functions;
	unsigned int			options;
}							t_context;

typedef struct				s_before_info
{
	uint64_t				value;
	uint32_t				filetype;
	uint32_t				type;
	uint32_t				section;
}							t_before_info;

#endif
