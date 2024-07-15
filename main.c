/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:58:16 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/13 18:06:28 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoii(const char *str)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if (!ft_isdigit(*str))
			return (-1);
		sum = sum * 10 + *str - '0';
		if (sum < 0 && sign == 1)
			return (-1);
		if (sum < 0 && sign == -1)
			return (0);
		str++;
	}
	return (sign * sum);
}

int is_valid_rgb(int color)
{
    return (color >= 0 && color <= 255);
}

void ft_colors(t_config *config, char *line)
{
    char **trimed = malloc(3 * sizeof(char *));
    char **splited;
    int i = 0;
    int rgb[3];

    splited = ft_split(line, ',');
    splited[0] = splited[0] + 1;
    while (splited[i])
    {
        trimed[i] = ft_strtrim(splited[i], " ");
        rgb[i] = ft_atoi(trimed[i]);
        if (!is_valid_rgb(rgb[i]))
            printf("\033[31;01mWRONG RGB: %i \033[00m\n", rgb[i]);
        else
            printf("RGB: \033[32;01m%i\033[00m\n", rgb[i]);
        i++;
    }
    // trimed = ft_strtrim(line, " ");
    // trimed = trimed + 1;

}

int ft_check_line(char *line, t_config *config)
{
    (void)config;
    int i = 0;

    while (line[i] == ' ')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
       config->no_texture = ft_textures(config, line);
    if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
       config->so_texture = ft_textures(config, line);
    if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
       config->we_texture = ft_textures(config, line);
    if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
       config->ea_texture = ft_textures(config, line);
    if (line[i] == 'F' && line[i + 1] == ' ')
        ft_colors(config, line);
    return 0;
}

int ft_parsing(t_config *config, char *filename)
{
    int fd;
    char *line;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read from file:\033[34;01m \n%s \033[00m\n", line);
        ft_check_line(line, config);
        free(line);
    }
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{

    t_config config;

    if (argc != 2)
        return (write(2, "Error: argument\n", 16));
    if (ft_parsing(&config, argv[1]))
        return (1);
    return 0;
}