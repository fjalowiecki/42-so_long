/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:50:07 by fjalowie          #+#    #+#             */
/*   Updated: 2024/06/20 17:47:04 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
 
#define BUFFER_SIZE 4096
#define TILE_SIZE   32
#define GAME_TITLE  "crystal chaser"

typedef struct t_map
{
    char    *map;
    int     width;
    int     height;
} t_map;

typedef struct t_data
{
	void    *mlx_ptr;
	void    *win_ptr;
	char    *textures[5];
	t_map   *map;
} t_data;


#endif