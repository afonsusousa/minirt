/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:26:34 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/06 23:13:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_newlen(const char *str);

char	*ft_strjoin_gnl(char *stash, char *buffer)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = (char *)ft_calloc(ft_newlen(stash) + ft_newlen(buffer) + 1, 1);
	if (!ret)
		return (free(stash), NULL);
	while (stash && stash[i])
	{
		ret[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
	{
		ret[i++] = buffer[j];
		if (buffer[j] == '\n')
			break ;
		j++;
	}
	return (free(stash), ret);
}

void	ft_update_buffer(char *buffer, int *newline)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
		{
			*newline = 1;
			while (buffer[++i])
				buffer[j++] = buffer[i];
			break ;
		}
	}
	ft_bzero(&buffer[j], i - j);
}

char	*ft_get_line(int fd, char *buffer)
{
	int		newline;
	int		br;
	char	*ret;

	newline = 0;
	br = 0;
	ret = NULL;
	while (!newline)
	{
		if (!*buffer)
		{
			br = read(fd, buffer, BUFFER_SIZE);
			if (br == -1)
				return (free(ret), NULL);
			if (br == 0)
				break ;
			buffer[br] = 0;
		}
		ret = ft_strjoin_gnl(ret, buffer);
		if (!ret)
			return (NULL);
		ft_update_buffer(buffer, &newline);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = ft_get_line(fd, buffer);
	return (ret);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*print;
	int		fd;

	fd = open("multiple_line_with_nl", O_RDONLY);
	while ((print = get_next_line(fd)))
	{
		printf("%s", print);
		sleep(1);
	}
} */