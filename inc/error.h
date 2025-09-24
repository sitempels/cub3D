/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:24:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/24 17:32:20 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define USAGE "Wrong number of arguments\nUsage : ./cub3d <filename.cub>\n"
# define ERR_MALLOC "Memory allocation failed\n"
# define ERR_FILE "Incorrect or missing file extension. Expected: %s\n"
# define ERR_OPEN "Open failed\n"
//# define ERR_INIT_CONFIG "Init configuration failed\n"
# define EMPTY_FILE "Empty file\n"
# define RD_FILE "Reading file"
# define MISSING_CONFIG "Incomplete configuration\n"
# define ERR_CONFIG "Incorrect configuration value\n"
# define DOUBLE_TYPE "Texture type has already been parsed\n"
# define EXTRA_CONTENT "Extra content after texture path\n"
# define ERR_MAP "Empty line in map or content after map\n"
# define NO_PLAYER "The map must contain a player represented by N, S, W or E\n"
# define MULT_PLAYERS "Multiple players found\n"
# define ERR_RGB "Invalid RGB format, must be a digit\n"
# define RANGE_RGB "RGB value out of range (0-255)\n"
# define FRMT_RGB "RGB values must be separated by a comma\n"
# define RGB_COUNT "RGB must have exactly 3 values\n"
# define RGB_EXTRA "Extra content before or after RGB values\n"
# define UNCLOSED_MAP "Map is not closed\n"
# define ERR_TEXT "Texture with path %s is not valid\n"

#endif