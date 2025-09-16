#include "cub3D.h"

int	check_line(char *line, t_config *config)
{
	int			i;
	static int	player_count;

	if (detect_content(line, NULL))
	{
		if (config->map_end == true)
		{
			ft_printf_fd(STDERR_FILENO, "Error: Empty line in map or content after map\n");
			return (1);
		}
	}
	else
	{
		config->map_end = true;
		return (0);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n\t", line[i]))
		{
			ft_printf_fd(STDERR_FILENO,
				"Error: Invalid character <%c> inserted\n", line[i]);
			return (1);
		}
		if (line[i] == ' ' || line[i] == '\t')
			i++;
			
		if (ft_strchr("NSEW", line[i]))
		{
			player_count++;
			if (player_count > 1)
			{
				ft_printf_fd(STDERR_FILENO, "Error: Multiple players found\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
