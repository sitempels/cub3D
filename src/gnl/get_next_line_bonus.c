#include "get_next_line_bonus.h"

char	*extract_line_from_stash(char *line, char **stash)
{
	int		i;
	char	*old_stash;

	i = 0;
	old_stash = *stash;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i] == '\n')
	{
		line = gnl_substr(*stash, 0, i + 1);
		*stash = gnl_substr(old_stash, i + 1, gnl_strlen(old_stash) - (i + 1));
		if (*stash && **stash == '\0')
		{
			free(*stash); //eviter 1 byte leaks de dup("")
			*stash = NULL;
		}
	}
	else
	{
		line = gnl_substr(*stash, 0, i);
		*stash = NULL;
	}
	free(old_stash);
	return (line);
}

char	*read_file(int fd, char *buffer, char *stash)
{
	ssize_t	bytes_read;
	char	*temp;

	temp = NULL;
	if (stash && gnl_strchr(stash, '\n'))
		return (stash);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(stash, buffer);
		if (stash)
			free(stash);
		if (!temp)
			return (NULL);
		stash = temp;
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	stash[fd] = read_file(fd, buffer, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line_from_stash(line, &stash[fd]);
	if (!line)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	return (line);
}