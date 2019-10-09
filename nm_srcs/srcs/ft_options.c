/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				ft_invalid_option(char c)
{
	if (ft_strchr("pruUjg", c))
		return (SUCCESS);
	ft_putstr_fd("invalid flag: '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (FAIL);
}

int				ft_new_option(char c1, char c2, int decal, unsigned int *opt)
{
	if (c1 != c2)
		return (SUCCESS);
	if ((*opt >> decal) & 1)
	{
		ft_putstr_fd("invalid double flag", 2);
		ft_putchar_fd(c1, 2);
		ft_putstr_fd("'\n", 2);
		return (FAIL);
	}
	*opt += 1 << decal;
	return (SUCCESS);
}

int				ft_get_options(char **str, unsigned int *opt)
{
	int		i;

	i = 0;
	if (!(*str)[1])
	{
		ft_putstr_fd("missing option after -\n", 2);
		return (FAIL);
	}
	while ((*str)[++i])
	{
		if (ft_new_option((*str)[i], 'p', OPT_P, opt)
		|| ft_new_option((*str)[i], 'r', OPT_R, opt)
		|| ft_new_option((*str)[i], 'u', OPT_U, opt)
		|| ft_new_option((*str)[i], 'U', OPT_MU, opt)
		|| ft_new_option((*str)[i], 'j', OPT_J, opt)
		|| ft_new_option((*str)[i], 'g', OPT_G, opt)
		|| ft_invalid_option((*str)[i]))
			return (FAIL);
	}
	*str = NULL;
	return (SUCCESS);
}

int				ft_nb_files(unsigned int opt, int nb, int *ac, char **av)
{
	if (!opt)
		return (0);
	if (nb > 1)
		return (opt + (1 << OPT_MULTIPLES));
	if (nb == 0)
	{
		av[*ac] = "a.out";
		*ac += 1;
	}
	return (opt);
}

unsigned int	ft_set_options(int *ac, char **av)
{
	unsigned int	options;
	int				i;
	int				nb_files;

	options = 1 << OPT_SUCCESS;
	i = 0;
	nb_files = 0;
	while (++i < *ac)
	{
		if (ft_strequ(av[i], "--"))
		{
			av[i++] = NULL;
			break ;
		}
		else if (av[i][0] != '-')
		{
			// ft_printf("file: %s\n", av[i]);
			++nb_files;
		}
		else if (ft_get_options(&(av[i]), &options))
			return (0);
	}
	// ft_printf("nb_files %d, i %d, ac %d\n", nb_files, i, *ac);
	return (ft_nb_files(options, nb_files + (*ac - i), ac, av));
}
