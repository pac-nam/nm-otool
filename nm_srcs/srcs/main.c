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
	int				i;
	unsigned int	options;

	if (!(options = ft_set_options(&ac, av)))
		return (-1);
	i = 0;
	// ft_printf("OPT_R 1: %d\n", (options >> OPT_R) & 0xf);
	// ft_printf("debug main\n");
	while (++i < ac)
	{
		// ft_printf("\n%s: %d\n", av[i], ac);
		if (av[i] && ft_nm_this_file(av[i], options) != SUCCESS)
		{
			ft_putstr_fd("ERROR\n", 2);
		}
	}
	return (0);
}
