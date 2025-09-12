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
			free(*stash);
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

int	read_file(int fd, char *buffer, char **stash)
{
	ssize_t	bytes_read;
	char	*temp;

	temp = NULL;
	if (*stash && gnl_strchr(*stash, '\n'))
		return (GNL_SUCCESS);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(*stash, buffer);
		if (*stash)
			free(*stash);
		if (!temp)
			return (GNL_ERROR);
		*stash = temp;
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (free(*stash), GNL_ERROR);
	return (GNL_SUCCESS);
}

int	check_result(int read_result, char *stash)
{
	if (read_result == GNL_ERROR)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}

void	cleanup_stash(char **stash)
{
	int	i;

	i = 0;
	while (i < MAX_FD)
	{
		if (stash[i])
		{
			free(stash[i]);
			stash[i] = NULL;
		}
		i++;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*stash[MAX_FD];
	char		buffer[BUFFER_SIZE + 1];
	int			read_result;

	if (!line || fd < 0)
		return (cleanup_stash(stash), GNL_ERROR);
	*line = NULL;
	if (BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (GNL_ERROR);
	read_result = read_file(fd, buffer, &stash[fd]);
	if (check_result(read_result, stash[fd]) < 0)
		return (GNL_ERROR);
	if (!stash[fd])
		return (GNL_EOF);
	*line = extract_line_from_stash(*line, &stash[fd]);
	if (!*line)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (GNL_ERROR);
	}
	return (GNL_SUCCESS);
}
