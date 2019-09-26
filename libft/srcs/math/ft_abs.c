/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 13:46:17 by tbleuse           #+#    #+#             */
/*   Updated: 2018/03/30 18:07:16 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_abs return absolute value of the integer passed in parameter.
*/

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
