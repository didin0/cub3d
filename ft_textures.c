/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:33:45 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/24 15:18:14 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_textures(t_config *config, char *line)
{
    (void)config;
    char *trimed;
    trimed = ft_strtrim(line, " ");
    trimed = trimed + 2;
    while (*trimed == ' ')
        trimed = trimed + 1;
    printf("Saved in struct:\n\033[32;01m%s\033[00m\n", trimed);
    return trimed;
}