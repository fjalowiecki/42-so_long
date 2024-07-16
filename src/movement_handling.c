/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:19 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/16 14:51:17 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int		check_next_move(t_data *data, t_point next_pos);
static void		update_and_draw_new_player_position(t_data *data, int keysym);
static t_point	calc_next_player_position(t_point current_pos, int keysym);
static void		display_player_moves_count(t_data *data);

int	on_keypress(int keysym, t_data *data)
{
	t_point	next_pos;
	t_point	current_pos;

	if (keysym == 65307)
		on_destroy(data);
	current_pos = data->map->player_pos;
	next_pos = calc_next_player_position(current_pos, keysym);
	if (check_next_move(data, next_pos) == SUCCESS)
	{
		update_and_draw_new_player_position(data, keysym);
		data->map->player_moves_cnt++;
		display_player_moves_count(data);
	}
	return (SUCCESS);
}

static t_point	calc_next_player_position(t_point current_pos, int keysym)
{
	if (keysym == 65363)
		current_pos.x++;
	else if (keysym == 65361)
		current_pos.x--;
	else if (keysym == 65362)
		current_pos.y--;
	else if (keysym == 65364)
		current_pos.y++;
	return (current_pos);
}

static int	check_next_move(t_data *data, t_point next_pos)
{
	t_map	*map;

	map = data->map;
	if (map->map_grid[next_pos.y][next_pos.x] == '1')
		return (FAIL);
	else if (map->map_grid[next_pos.y][next_pos.x] == 'C')
	{
		map->collectables_cnt--;
		map->map_grid[next_pos.y][next_pos.x] = '0';
		if (map->collectables_cnt == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->textures[5], data->map->exit_pos.x * TILE_SIZE,
				data->map->exit_pos.y * TILE_SIZE);
	}
	else if (map->map_grid[next_pos.y][next_pos.x] == 'E' &&
		map->collectables_cnt != 0)
		return (FAIL);
	else if (map->map_grid[next_pos.y][next_pos.x] == 'E' &&
		map->collectables_cnt == 0)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[6], 0, 0);
		return (FAIL);
	}
	return (SUCCESS);
}

static void	update_and_draw_new_player_position(t_data *data, int keysym)
{
	t_map	*map;

	map = data->map;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->textures[0], map->player_pos.x * TILE_SIZE,
		map->player_pos.y * TILE_SIZE);
	map->player_pos = calc_next_player_position(map->player_pos, keysym);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->textures[3], map->player_pos.x * TILE_SIZE,
		map->player_pos.y * TILE_SIZE);
}

static void	display_player_moves_count(t_data *data)
{
	char	*message;
	char	*nmb;

	message = "moves cnt: ";
	nmb = ft_itoa(data->map->player_moves_cnt);
	if (!nmb)
		msg_err_and_exit(data, ERR_MALLOC);
	write(1, message, ft_strlen(message));
	write(1, nmb, ft_strlen(nmb));
	write(1, "\n", 1);
	free(nmb);
}
