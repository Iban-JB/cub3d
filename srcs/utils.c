/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibjean-b <ibjean-b@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:40:04 by ibjean-b          #+#    #+#             */
/*   Updated: 2024/10/24 13:50:32 by ibjean-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strdup_until_char(const char *s, char c)
{
	char	*dup;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (len == SIZE_MAX)
		return (0);
	dup = ft_calloc(1, len + 1);
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*dup;

	dup = malloc(len + 1);
	if (!dup)
		return (0);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

void	ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	if (arr)
		free(arr);
}

char	**tab_dup(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i++])
		;
	new_tab = ft_calloc(i + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			ft_free_tab(new_tab);
			return (NULL);
		}
	}
	return (new_tab);
}

char	**tab_join(char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (NULL);
		i++;
	}
	if (ft_strchr(str, '\n'))
		new_tab[i] = ft_strndup(str, ft_strlen(str) - 1);
	else
		new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (NULL);
	new_tab[i + 1] = NULL;
	return (new_tab);
}
