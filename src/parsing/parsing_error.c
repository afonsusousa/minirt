#include "../../includes/obj.h"
#include "parsing.h"
#include <stdio.h>
#include <stdbool.h>

size_t  ft_strlen(const char *s);
bool    skip(char **s, bool (*predicate)(char));
bool    match_id(char **line, char *id);
bool    ft_isspace(char c);

static void     print_flags(const t_format *fmt)
{
        printf("expected format: ");
        for (int i = 0; fmt[i].type != F_END; i++)
        {
                if (fmt[i].type == F_VEC3)
                        printf("[%s: 0.0,0.0,0.0] ", fmt[i].name);
                else if (fmt[i].type == F_DOUBLE)
                        printf("[%s: 0.0] ", fmt[i].name);
                else if (fmt[i].type == F_COLOR)
                        printf("[%s: 0,0,0] ", fmt[i].name);
        }
        printf("\n");
}

static void     print_expected_format(const char *start)
{
        char    *tmp;
        const t_format *fmt;

        tmp = (char *)start;
        fmt = NULL;
        skip(&tmp, ft_isspace);
        if (match_id(&tmp, "sp"))
                fmt = get_sphere_fmt();
        else if (match_id(&tmp, "pl"))
                fmt = get_plane_fmt();
        else if (match_id(&tmp, "cy"))
                fmt = get_cylinder_fmt();
        else if (match_id(&tmp, "A"))
                fmt = get_ambient_fmt();
        else if (match_id(&tmp, "C"))
                fmt = get_camera_fmt();
        else if (match_id(&tmp, "L"))
                fmt = get_light_fmt();
                
        if (fmt)
                print_flags(fmt);
        else
                printf("invalid object\n");
}

void    syntax_error(const char *file, int line, const char *start, const char *c)
{
        int     offset;
        int     i;
        int     len;

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
