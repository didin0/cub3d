/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:13:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/04 18:23:33 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *backup)
{
	int		readed;
	char	*tmp;

	readed = 1;
	while (readed != '\0')
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (NULL);
		else if (readed == 0)
			break ;
		buf[readed] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = ft_read(fd, buf, backup[fd]);
	free(buf);
	if (!line)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = extract(line);
	return (line);
}

// int main()
// {
// 	int fd1 = open("read_error.txt", O_RDONLY);
// 	int fd2 = open("foo.txt", O_RDONLY);
// 	int fd;
// 	int i = 0;

// 	while (i++ < 6)
// 	{
// 		printf("fd1: %s", get_next_line(fd1));
// 		printf("fd2: %s", get_next_line(fd2));
// 	}
// 	return 0;
// }
