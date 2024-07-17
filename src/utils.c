/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:13:31 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/17 12:06:21 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief Utility functions for 'so_long' game.
 */
#include "so_long.h"

/**
 * @brief Exits the game and frees resources on error.
 * @param data Game data structure.
 * @param err Error message.
 */
void	msg_err_and_exit(t_data *data, char *err)
{
	if (data->map->map_grid != NULL)
		free_map_grid(data);
	if (data->mlx_ptr != NULL && data->win_ptr != NULL)
	{
		free_textures(data);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

/**
 * @brief Frees the memory allocated for the map grid.
 * @param data Game data structure.
 */
void	free_map_grid(t_data *data)
{
	char	**map_grid_ptr;

	map_grid_ptr = data->map->map_grid;
	while (*map_grid_ptr)
	{
		free(*map_grid_ptr);
		map_grid_ptr++;
	}
	free(data->map->map_grid);
	data->map->map_grid = NULL;
}

/**
 * @brief Frees loaded textures.
 * @param data Game data structure.
 */
void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->textures[i] != NULL)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
}

/**
 * @brief Converts an integer to a string.
 * @param n Integer to convert.
 * @return String representation of n.
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		num_digits;
	int		n_cp;
	int		i;

	n_cp = n;
	num_digits = 0;
	while (n_cp != 0)
	{
		num_digits++;
		n_cp /= 10;
	}
	str = (char *)malloc((num_digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = num_digits - 1;
	while (i >= 0)
	{
		str[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	str[num_digits] = '\0';
	return (str);
}

/**
 * @brief Calculates the length of a string.
 * @param s String to measure.
 * @return Length of s.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
