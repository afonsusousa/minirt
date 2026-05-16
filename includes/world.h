/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 20:28:50 by amagno-r          #+#    #+#             */
/*   Updated: 2026/05/16 20:28:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_world	*parse_file(t_world *wrld, char *path);
void	assign_material_scatter_funcs(t_world *w);
