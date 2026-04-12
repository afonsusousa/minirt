#include "obj.h"
#include <stdio.h>
#include <stdbool.h>

size_t	ft_strlen(const char *s);
bool	skip(char **s, bool (*predicate)(char));
bool	match_id(char **line, char *id);
bool	ft_isspace(char c);

static void	print_flags(int flags)
{
	int	mask;

	mask = F_POS | F_DIR | F_RATIO | F_FOV | F_SIZE | F_HEIGHT | F_COLOR;
	if (flags & ~mask)
	{
		printf("internal error\n");
		return ;
	}
	printf("expected format: ");
	if (flags & F_POS)
		printf("[pos: 0.0,0.0,0.0] ");
	if (flags & F_DIR)
		printf("[dir (normalized): 0.0,0.0,1.0] ");
	if (flags & F_RATIO)
		printf("[ratio: 0.0] ");
	if (flags & F_FOV)
		printf("[fov: 0] ");
	if (flags & F_SIZE)
		printf("[size: 0.0] ");
	if (flags & F_HEIGHT)
		printf("[height: 0.0] ");
	if (flags & F_COLOR)
		printf("[color: 0,0,0] ");
	printf("\n");
}

static void	print_expected_format(const char *start)
{
	char	*tmp;
	int		flags;

	tmp = (char *)start;
	flags = 0;
	skip(&tmp, ft_isspace);
	if (match_id(&tmp, "sp"))
		flags = F_FMT_SPHERE;
	else if (match_id(&tmp, "pl"))
		flags = F_FMT_PLANE;
	else if (match_id(&tmp, "cy"))
		flags = F_FMT_CYLINDER;
	else if (match_id(&tmp, "A"))
		flags = F_FMT_AMBIENT;
	else if (match_id(&tmp, "C"))
		flags = F_FMT_CAMERA;
	else if (match_id(&tmp, "L"))
		flags = F_FMT_LIGHT;
	if (flags)
		print_flags(flags);
	else
		printf("invalid object\n");
}

void	syntax_error(const char *file, int line, const char *start, const char *c)
{
	int	offset;
	int	i;
	int	len;

	offset = c - start;
	printf("%s:%d:%d: error: syntax error\n", file, line, offset + 1);
	printf("%s", start);
	len = ft_strlen(start);
	if (len == 0 || start[len - 1] != '\n')
		printf("\n");
	i = 0;
	while (i < offset)
	{
		if (start[i] == '\t')
			printf("\t");
		else
			printf(" ");
		i++;
	}
	printf("\033[31m^\033[0m\n");
	print_expected_format(start);
}
