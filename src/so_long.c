/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:50:30 by fjalowie          #+#    #+#             */
/*   Updated: 2024/06/20 18:06:46 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
 
int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	return (0);
}

char *open_map(char *argv)
{
	int	fd;
	char *map;
	
	map = (char *)malloc(sizeof(char)*BUFFER_SIZE);
	printf("argv: %s\n", argv);
	fd = open(argv, O_RDWR);
	if (fd == -1)
		perror("ERR");
	read(fd, map, BUFFER_SIZE);
	return (map);
}

void draw_static_elements(t_data *data)
{
	int i;
	int	j;
	void *bg;
	int bg_width;
	int	bg_height;
	t_map *map;
	
	map = data->map;
	bg = mlx_xpm_file_to_image(data->mlx_ptr, data->textures[0], &bg_width, &bg_height);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, bg, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void process_map(t_map *map, char *file_path)
{
	char *map_ptr;
	
	map->map = open_map(file_path);
	map_ptr = map->map;
	map->width = 0;
	map->height = 1;
	while(*map_ptr++ != '\n')
		map->width++;
	map_ptr = map->map;
	while(*map_ptr != '\0')
	{	
		if (*map_ptr == '\n')
			map->height++;
		map_ptr++;
	}
}

int main(int argc, char *argv[])
{
	t_map map;
	t_data data;
	int width;
	int height;
	void *img_ptr;

	process_map(&map, argv[1]);
	data.textures[0] = "assets/bg.xpm";
	data.textures[1] = "assets/plant.xpm";
	data.textures[2] = "assets/hero.xpm";
	data.map = &map;
	
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, map.width * TILE_SIZE, map.height * TILE_SIZE, GAME_TITLE);
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
 
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);

	draw_static_elements(&data);
 
	mlx_loop(data.mlx_ptr);
	return (0);
}