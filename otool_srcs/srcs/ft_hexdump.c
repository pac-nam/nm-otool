/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 13:30:36 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/30 13:30:37 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
**		return char[4] (with '\0')
*/

char				*ft_hexdump_space(char *dst, int c)
{
	dst[0] = OTOOL_HEXA[c >> 4 & 0xf];
	dst[1] = OTOOL_HEXA[(c % 16) & 0xf];
	dst[2] = ' ';
	dst[3] = '\0';
	return (dst);
}

/*
**		return char[9] (with '\0')
*/

char				*ft_hexdump(char *dst, uint32_t src)
{
	int				i;
	uint32_t		tmp;

	dst[8] = '\0';
	i = 8;
	tmp = (uint32_t)src;
	while (--i >= 0)
	{
		dst[i] = OTOOL_HEXA[tmp % 16];
		tmp = tmp / 16;
	}
	return (dst);
}

/*
**		return char[17] (with '\0')
*/

char				*ft_hexdump_64(char *dst, uint64_t src)
{
	int				i;
	uint64_t		tmp;

	dst[16] = '\0';
	i = 16;
	tmp = (uint32_t)src;
	while (--i >= 0)
	{
		dst[i] = OTOOL_HEXA[tmp % 16];
		tmp = tmp / 16;
	}
	return (dst);
}
