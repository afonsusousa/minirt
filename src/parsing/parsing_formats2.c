/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_formats2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:28:41 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:28:42 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj.h"
#include "parsing.h"
#include <stddef.h>

const t_format	*get_light_fmt(void)
{
	static const t_format	fmt[] = {
	{F_VEC3, offsetof(t_light, pos), "pos"},
	{F_DOUBLE, offsetof(t_light, ratio), "ratio"},
	{F_COLOR, offsetof(t_light, color), "color"},
	{F_END, 0, NULL}
	};
	return (fmt);
}
