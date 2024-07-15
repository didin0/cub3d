/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:58:16 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/15 15:24:13 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
        ft_colors(config, line, 'F');
    if (line[i] == 'C' && line[i + 1] == ' ')
        ft_colors(config, line, 'C');
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