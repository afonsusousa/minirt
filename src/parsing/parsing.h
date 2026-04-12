#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdbool.h>
# include "../includes/obj.h"

// parsing_utils.c
size_t	magnitude(int n);
bool	ft_isspace(char c);
bool	skip(char **s, bool (*predicate)(char));
bool	match_id(char **line, char *id);
char	*get_next_line(int fd);

// parsing_error.c
void	syntax_error(const char *file, int line, const char *start, const char *c);

#endif