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

	if (ac < 2)
	{
		av[1] = "a.out";
		ac++;
	}
	i = 0;
	while (++i < ac)
	{
		if (ac > 3)
			ft_printf("\n%s:\n", av[i]);
		if (av[i] && ft_nm_this_file(av[i]) != SUCCESS)
		{
			ft_putstr_fd("ERROR\n", 2);
		}
	}
	return (0);
}
