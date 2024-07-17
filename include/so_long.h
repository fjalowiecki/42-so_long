/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:50:07 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/17 10:45:52 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file so_long.h
 * @brief Header file for the game.
 * 
 */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "mlx.h"

# define SUCCESS 0
# define FAIL -1

# define BUFFER_SIZE 4096
# define TILE_SIZE   64
# define GAME_TITLE  "chest chaser"

# define ERR_MALLOC "Error\nMemory allocation failed"
# define ERR_FILE "Error\nCannot open/read map file"
# define ERR_NO_FILE_PATH "Error\nPath to map file is incorrect"
# define ERR_NO_RECT "Error\nMap is not a rectangle"
# define ERR_NO_ITEMS "Error\nCollectibles, player position or exit are missing"
# define ERR_UNDEF_ITEM "Error\nMap contains undefined item"
# define ERR_NOT_CLOSED "Error\nMap does not have properly defined borders"
# define ERR_NO_PATH "Error\nProper path between obj and exit does not exist"
# define ERR_MLX "Error\nMlx initialization fail"
# define ERR_MLX_WIN "Error\nMlx window creation fail"

typedef struct t_point
{
	int	x;
	int	y;
}	t_point;

typedef struct t_map
{
	char	**map_grid;
	int		width;
	int		height;
	int		collectables_cnt;
	int		player_moves_cnt;
	t_point	player_pos;
	t_point	exit_pos;
}	t_map;

typedef struct t_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*textures[8];
	t_map	*map;
}	t_data;

typedef struct t_pnt_data
{
	t_point	new_pnt_dir[4];
	t_point	*visited_pnts;
	size_t	v_pnt_size;
	int		path_exists_flag;
}	t_pnt_data;

/* so_long.c */
int		on_destroy(t_data *data);

/* map_validation.c */
void	process_and_validate_map(t_data *data);

/* path_validation.c */
int		check_if_all_obj_are_reachable(t_data *data);

/* elements.drawing.c */
void	load_textures(t_data *data);
void	draw_static_elements(t_data *data);

/* movement_handling.c */
int		on_keypress(int keysym, t_data *data);

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* utils.c */
void	msg_err_and_exit(t_data *data, char *err);
void	free_map_grid(t_data *data);
void	free_textures(t_data *data);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

#endif