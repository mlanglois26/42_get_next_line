/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:44:39 by malanglo          #+#    #+#             */
/*   Updated: 2023/12/15 10:21:26 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[5256];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_from_fd_and_concatenate_to_stash(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_get_content(stash[fd]);
	stash[fd] = ft_update_stash_after_line_exctraction(stash[fd]);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		i;

// 	fd1 = open("tests/test1.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line fd1 %d :%s\n", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line fd2 %d :%s\n", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line fd3 %d :%s\n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
//  }