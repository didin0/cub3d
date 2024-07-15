/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:57:59 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/13 16:35:10 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line/get_next_line.h"

typedef struct s_map
{
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_config
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color[3];
    int ceiling_color[3];
    t_map *map;
} t_config;

// PARSING
char *ft_textures(t_config *config, char *line);
