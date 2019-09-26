/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:10:18 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 12:19:11 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_isdigit return 1 if the integer passed is a digit, 0 elseway.
*/

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}