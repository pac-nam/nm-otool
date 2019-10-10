/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 09:20:04 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/27 09:20:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_nm.h"

int					ft_nm_parse(t_context *ctx)
{
	uint32_t		magic_number;

	magic_number = *(uint32_t*)ctx->header;
	// ft_printf("debug 14\n");
	// ft_printf("%s %x\n", ctx->file_name, magic_number);
	// return (SUCCESS);
	if (magic_number == MH_MAGIC_64)
		return (ft_nm_64(ctx));
	// else if (magic_number == MH_CIGAM_64)
	// 	return (ft_nm_64_reverse(ctx));
	else if (magic_number == MH_MAGIC)
		return (ft_nm_32(ctx));
	else if (magic_number == FAT_CIGAM)
		return (ft_nm_fat_reverse(ctx));
	// else if (magic_number == FAT_MAGIC_64)
	// 	return (ft_nm_fat_64(ctx));
	// else if (magic_number == FAT_CIGAM_64)
	// 	return (ft_nm_fat_64_reverse(ctx));
	return (FAIL);
}