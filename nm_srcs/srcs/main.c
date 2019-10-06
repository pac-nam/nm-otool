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

#include "ft_nm.h"

int				main(int ac, char **av)
{
	int			i;
	int			error;

	if (ac < 2)
	{
		av[1] = "a.out";
		ac++;
	}
	i = 0;
	while (++i < ac)
	{
		// ft_putendl(av[i]);
		if (av[i] && (error = ft_nm_this_file(av[i])))
		{
			ft_putstr_fd("ERROR CODE: ", 2);
			ft_putnbr_fd(error, 2);
			ft_putchar_fd('\n', 2);
		}
	}
	return (0);
}
