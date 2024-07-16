/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:01:05 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/16 15:19:49 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_this_obj_being_reachable(char **map_grid_ptr,
				t_pnt_data *pnt_data, int x, int y);
static void	populate_pnt_data(t_data *data, t_pnt_data *pnt_data);
static void	check_path_to_exit(char **map_grid_ptr, t_pnt_data *pnt_data,
				t_point now_pnt);
static int	pnt_already_visited(t_pnt_data *pnt_data, t_point now_pnt);

int	check_if_all_obj_are_reachable(t_data *data)
{
	char		**map_grid_ptr;
	t_pnt_data	pnt_data;
	int			i;
	int			j;

	populate_pnt_data(data, &pnt_data);
	map_grid_ptr = data->map->map_grid;
	i = 0;
	while (map_grid_ptr[i] != NULL)
	{
		j = 0;
		while (map_grid_ptr[i][j] != '\0')
		{
			if (map_grid_ptr[i][j] == 'P' || map_grid_ptr[i][j] == 'C')
			{
				if (check_this_obj_being_reachable(map_grid_ptr,
						&pnt_data, j, i) == FAIL)
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	free(pnt_data.visited_pnts);
	return (SUCCESS);
}

static void	populate_pnt_data(t_data *data, t_pnt_data *pnt_data)
{
	pnt_data->visited_pnts = (t_point *)malloc(sizeof(t_point)
			* data->map->height * data->map->width);
	if (!pnt_data->visited_pnts)
		msg_err_and_exit(data, ERR_MALLOC);

	pnt_data->new_pnt_dir[0].x = -1;
	pnt_data->new_pnt_dir[0].y = 0;
	pnt_data->new_pnt_dir[1].x = 0;
	pnt_data->new_pnt_dir[1].y = -1;
	pnt_data->new_pnt_dir[2].x = 1;
	pnt_data->new_pnt_dir[2].y = 0;
	pnt_data->new_pnt_dir[3].x = 0;
	pnt_data->new_pnt_dir[3].y = 1;
}

static int	check_this_obj_being_reachable(char **map_grid_ptr,
				t_pnt_data *pnt_data, int x, int y)
{
	t_point	start_pnt;

	pnt_data->v_pnt_size = 0;
	start_pnt.x = x;
	start_pnt.y = y;
	pnt_data->path_exists_flag = FAIL;
	check_path_to_exit(map_grid_ptr, pnt_data, start_pnt);
	if (pnt_data->path_exists_flag == FAIL)
	{
		free(pnt_data->visited_pnts);
		return (FAIL);
	}
	return (SUCCESS);
}

static void	check_path_to_exit(char **map_grid_ptr,
					t_pnt_data *pnt_data, t_point now_pnt)
{
	t_point	temp_pnt;
	int		i;

	i = 0;
	while (i < 4)
	{
		temp_pnt.x = now_pnt.x + pnt_data->new_pnt_dir[i].x;
		temp_pnt.y = now_pnt.y + pnt_data->new_pnt_dir[i].y;
		if (map_grid_ptr[temp_pnt.y][temp_pnt.x] != '1'
				&& !pnt_already_visited(pnt_data, temp_pnt)
				&& !pnt_data->path_exists_flag == SUCCESS)
		{
			if (map_grid_ptr[temp_pnt.y][temp_pnt.x] == 'E')
				pnt_data->path_exists_flag = SUCCESS;
			else
			{
				pnt_data->v_pnt_size++;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].x = temp_pnt.x;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].y = temp_pnt.y;
				check_path_to_exit(map_grid_ptr, pnt_data, temp_pnt);
			}
		}
		i++;
	}
}

static int	pnt_already_visited(t_pnt_data *pnt_data, t_point now_pnt)
{
	size_t	i;

	i = 0;
	while (i < pnt_data->v_pnt_size)
	{
		if (now_pnt.x == pnt_data->visited_pnts[i].x
			&& now_pnt.y == pnt_data->visited_pnts[i].y)
			return (1);
		i++;
	}
	return (0);
}
