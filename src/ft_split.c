/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:35:42 by fjalowie          #+#    #+#             */
/*   Updated: 2024/07/17 10:39:57 by fjalowie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_split.c
 * @brief Splits a string into words by a delimiter.
 */
#include "so_long.h"

static int	num_words_count(char const *s, char c);
static void	split_words(char **result, char const *s, char c, int i);

/**
 * @brief Splits a string by a delimiter into an array of words.
 * 
 * Allocates an array of strings where each element is a word from the input
 * string 's', split by the delimiter 'c'. The array is null-terminated.
 * 
 * @param s The input string to split.
 * @param c The delimiter character.
 * @return A null-terminated array of words, or NULL on failure.
 */
char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**result;
	int		i;

	i = 0;
	num_words = num_words_count(s, c);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_words(result, s, c, i);
	result[num_words] = NULL;
	return (result);
}

/**
 * @brief Counts the number of words separated by a delimiter.
 * 
 * @param s The input string.
 * @param c The delimiter character.
 * @return The number of words.
 */
static int	num_words_count(char const *s, char c)
{
	int	num_words;
	int	i;

	num_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num_words++;
		i++;
	}
	return (num_words);
}

/**
 * @brief Splits the string into words and stores them in an array.
 * 
 * Allocates memory for each word and copies the word from the input string
 * to the newly allocated memory. Each word is then stored in the result array.
 * 
 * @param result The array to store the words.
 * @param s The input string.
 * @param c The delimiter character.
 * @param i The starting index for splitting.
 */
static void	split_words(char **result, char const *s, char c, int i)
{
	int	start;
	int	j;
	int	k;

	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = malloc((i - start + 1) * sizeof(char));
			if (!result[j])
				return ;
			k = 0;
			while (start < i)
				result[j][k++] = s[start++];
			result[j++][k] = '\0';
		}
		else
			i++;
	}
}
