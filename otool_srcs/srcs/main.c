/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				main(int ac, char **av)
{
	int				i;

	i = 0;
	while (++i < ac)
	{
		if (av[i] && ft_otool_this_file(av[i]) != SUCCESS)
		{
			ft_putstr_fd(av[0], 2);
			ft_putstr_fd(": '", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd("': truncated or malformed object\n\n", 2);
			return (-1);
		}
	}
	return (0);
}
