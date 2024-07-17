/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:50:30 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/17 10:35:00 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file so_long.c
 * @brief Main game logic for 'so_long'.
 */
#include "so_long.h"

static void	load_map(t_data *data, char *file_path);

/**
 * @brief Entry point for the 'so_long' game.
 * 
 * Initializes game data, loads the map, sets up the game window,
 * and enters the main event loop.
 * Exits with an error message if any step fails.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments, including the path to
 * the map file.
 * @return Execution status.
 */
int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	map;

	data.mlx_ptr = NULL;
	data.win_ptr = NULL;
	map.map_grid = NULL;
	data.map = &map;
	if (argc != 2)
		msg_err_and_exit(&data, ERR_NO_FILE_PATH);
	load_map(&data, argv[1]);
	process_and_validate_map(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		msg_err_and_exit(&data, ERR_MLX);
	data.win_ptr = mlx_new_window(data.mlx_ptr, map.width * TILE_SIZE,
			map.height * TILE_SIZE, GAME_TITLE);
	if (!data.win_ptr)
		msg_err_and_exit(&data, ERR_MLX_WIN);
	load_textures(&data);
	draw_static_elements(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &data);
	mlx_loop(data.mlx_ptr);
}

/**
 * @brief Loads a map from a file into the game data structure.
 * 
 * This function opens a file specified by `file_path`
 * and reads its content into a buffer.
 * The content is then split into a grid based on newline
 * characters, which represents the game map.
 * 
 * @param data Pointer to the game data structure where
 * the loaded map will be stored.
 * @param file_path Path to the file containing the map to be loaded.
 */
static void	load_map(t_data *data, char *file_path)
{
	int		fd;
	char	*loaded_map_ptr;
	ssize_t	bytes_read;

	fd = open(file_path, O_RDWR);
	if (fd == -1)
		msg_err_and_exit(data, ERR_FILE);
	loaded_map_ptr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!loaded_map_ptr)
		msg_err_and_exit(data, ERR_MALLOC);
	bytes_read = read(fd, loaded_map_ptr, BUFFER_SIZE);
	if (bytes_read == -1)
		msg_err_and_exit(data, ERR_FILE);
	loaded_map_ptr[bytes_read] = '\0';
	data->map->map_grid = ft_split(loaded_map_ptr, '\n');
	if (!data->map->map_grid)
	{
		free(loaded_map_ptr);
		msg_err_and_exit(data, ERR_MALLOC);
	}
	close(fd);
	free(loaded_map_ptr);
}

/**
 * @brief Frees resources and exits the game.
 *
 * @param data Pointer to the game's data structure.
 * @return Always returns SUCCESS.
 */
int	on_destroy(t_data *data)
{
	free_textures(data);
	free_map_grid(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(SUCCESS);
	return (SUCCESS);
}
