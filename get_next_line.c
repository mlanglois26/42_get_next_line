/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:56:26 by malanglo          #+#    #+#             */
/*   Updated: 2023/12/15 10:31:35 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_from_fd_and_concatenate_to_stash(int fd, char *stash)
{
	char	*buff;
	char	*tmp;
	int		bytes_read;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(stash), NULL);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buff);
		free(stash);
		stash = tmp;
	}
	return (free(buff), stash);
}

char	*ft_get_content(char *stash)
{
	char	*content;
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (ft_strchr(stash, '\n'))
		content = ft_substr(stash, 0, i + 1);
	else
		content = ft_strdup(stash);
	return (content);
}

char	*ft_update_stash_after_line_exctraction(char *stash)
{
	char	*current_stash;
	char	*new_stash;

	if (!stash)
		return (NULL);
	current_stash = ft_strchr(stash, '\n');
	if (current_stash)
	{
		new_stash = ft_strdup(current_stash + 1);
		return (free(stash), new_stash);
	}
	else
		return (free(stash), NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_from_fd_and_concatenate_to_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_content(stash);
	stash = ft_update_stash_after_line_exctraction(stash);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("Erreur lors de l'ouverture du fichier");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Ligne lue : %s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
