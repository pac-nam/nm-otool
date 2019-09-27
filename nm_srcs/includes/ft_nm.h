#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

# include "../../libft/includes/libft.h"


typedef struct		s_context
{
	void			*master_start;
	void			*master_end;
	size_t			file_size;
	int				fd;
	char			to_print[4096];
	int				print_size;
	char			*file_name;
	struct stat		buf;
}					t_context;

int					ft_nm_this_file(const char *file);

#endif