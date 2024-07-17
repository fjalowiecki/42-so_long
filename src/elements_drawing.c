/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:50:38 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/17 11:42:44 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file elements_drawing.c
 * @brief Functions for drawing game elements in 'so_long'.
 */
#include "so_long.h"

static void	draw_element(t_data *data, int y, int x);

/**
 * @brief Loads textures for game elements from files.
 * 
 * @param data Pointer to the game data structure.
 */
void	load_textures(t_data *data)
{
	int	width;
	int	height;

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/bg.xpm", &width, &height);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/wall.xpm", &width, &height);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/item.xpm", &width, &height);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/hero.xpm", &width, &height);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/exit.xpm", &width, &height);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/exit_open.xpm", &width, &height);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets-64/endofgame.xpm", &width, &height);
	data->textures[7] = NULL;
}

/**
 * @brief Draws static elements on the game map.
 * 
 * Iterates through the map grid and calls draw_element for each cell.
 * 
 * @param data Pointer to the game data structure.
 */
void	draw_static_elements(t_data *data)
{
	char	**map_grid_ptr;
	int		y;
	int		x;

	map_grid_ptr = data->map->map_grid;
	y = 0;
	while (map_grid_ptr[y])
	{
		x = 0;
		while (map_grid_ptr[y][x])
		{
			draw_element(data, y, x);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws an individual element on the game window.
 * 
 * Selects the appropriate texture based on the map element and draws it.
 * 
 * @param data Pointer to the game data structure.
 * @param y Y-coordinate of the element in the map grid.
 * @param x X-coordinate of the element in the map grid.
 */
static void	draw_element(t_data *data, int y, int x)
{
	char	**map_grid_ptr;

	map_grid_ptr = data->map->map_grid;
	if (map_grid_ptr[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[1], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[0], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[3], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[4], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[2], x * TILE_SIZE, y * TILE_SIZE);
}
