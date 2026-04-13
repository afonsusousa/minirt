#include "../../lib/libft/libft.h"
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos;
	static int	buffer_read;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(70000);
	if (!line)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
        {
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

size_t	magnitude(int n)
{
	size_t	mag;

	if (!n)
		return (1);
	mag = 0;
	while (n != 0)
	{
		mag++;
		n /= 10;
	}
	return (mag);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	skip(char **s, bool (*predicate)(char))
{
	bool	ret;

	ret = false;
	while (**s && predicate(**s))
	{
		(*s)++;
		ret = true;
	}
	return (ret);
}

bool	match_id(char **line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(*line, id, len) == 0)
	{
		*line += len;
		return (true);
	}
	return (false);
}
