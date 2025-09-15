#include "cub3D.h"

int	check_line(char *line)
{
	int			i;
	static int	player_count;

	i = 0;
	while (line[i])
	{
		if (!detect_content(line, NULL))
			return (printf("Error: empty line found in map\n"), 1);
		if (!ft_strchr("01NSEW \n\t", line[i]))
		{
			ft_printf_fd(STDERR_FILENO,
				"Error: Invalid character <%c> inserted\n", line[i]);
			return (1);
		}
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