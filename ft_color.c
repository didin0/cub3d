/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:12:01 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/15 15:23:52 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_rgb(int color)
{
    return (color >= 0 && color <= 255);
}

void ft_colors(t_config *config, char *line, char type)
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
        {
            if (type == 'F')
                config->floor_color[i] = rgb[i];
            else if (type == 'C')
                config->ceiling_color[i] = rgb[i];
            printf("RGB: \033[32;01m%i\033[00m\n", config->floor_color[i]);
        }
        i++;
    }
    free(trimed);
    free(splited);
    // free_array(trimed);
    // free_array(splited);
}
