#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE > 8192 * 1024
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1048576 /* = 1 MB */
# endif 

# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

/* valeur defaut de la limite max de fichiers ouverts sur linux */
# define MAX_FD 1024

int		get_next_line(int fd, char **line);
int		read_file(int fd, char *buffer, char **stash);
char	*extract_line_from_stash(char *line, char **stash);

size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strchr(char *s, int c);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strdup(const char *s1);

#endif