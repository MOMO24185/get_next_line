/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:07 by melshafi          #+#    #+#             */
/*   Updated: 2023/12/15 10:21:15 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_strs(char *str, char *buff)
{
	char	*temp;

	temp = str;
	str = ft_strjoin(temp, buff);
	return (free(temp), str);
}

char	*last_iter(char *str, char *buff, int size)
{
	char	temp;

	temp = buff[size + 1];
	buff[size + 1] = 0;
	str = join_strs(str, buff);
	buff[size + 1] = temp;
	ft_strcpy(buff, &buff[size + 1]);
	return (str);
}

char	*end_of_file(char *str, char *buff, int size)
{
	buff[size] = 0;
	str = join_strs(str, buff);
	buff[0] = 0;
	return (str);
}

char	*check_last_read(ssize_t read_bytes, char *str, char *buff)
{
	if (read_bytes != -1 && buff[0])
		return (end_of_file(str, buff, read_bytes));
	ft_strcpy(buff, NULL);
	return (free(str), NULL);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1U];
	char		*str;
	int			size;
	ssize_t		read_bytes;

	size = -1;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str = ft_strjoin(NULL, buff);
	while (size == -1 && ft_strchr(str, '\n') < 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes > 0)
			buff[read_bytes] = 0;
		if (read_bytes < BUFFER_SIZE && ft_strchr(buff, '\n') < 0)
			return (check_last_read(read_bytes, str, buff));
		size = ft_strchr(buff, '\n');
		if (size >= 0)
			return (last_iter(str, buff, size));
		str = join_strs(str, buff);
	}
	return (free(str), last_iter(NULL, buff, ft_strchr(buff, '\n')));
}
