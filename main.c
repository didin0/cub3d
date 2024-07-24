/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:58:16 by mabbadi           #+#    #+#             */
/*   Updated: 2024/07/24 19:15:01 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*ft_lstnewmap(void *content)
{
    printf("content : %s", (char *)content);
	t_map	*result;

	result = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!result)
		return (NULL);
	result->grid = content;
	result->next = NULL;
	return (result);
}

void	ft_lstadd_backmap(t_map **lst, t_map *new)
{
	t_map	*tmp;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int ft_is_map_char(char s)
{
    if (s == '0' || s == '1' || s == '\n' || s == ' ')
        return 1;
    if (s == 'N' || s == 'S' || s == 'E' || s == 'W')
        return 1;
    return 0;
}

void ft_map(t_config *config, char *line)
{
    int i = 0;
    while (*line == ' ' || *line == '\t')
        line++;
    while (line[i] && line[i] != '\n')
    {
        printf("%i : %c\n",i, line[i]);
        if (!ft_is_map_char(line[i]))
        {
            printf("\033[31;01m MAP WRONG CHARACTER \033[00m\n");
            break;
        }
        i++;
    }
    config->map->height = i;
    if (line[i - 1] != '1')
        printf("\033[31;01mMAP WRONG DONT CLOSE WITH 1 i : %i\033[00m\n", i);
    ft_lstadd_backmap(&config->map, ft_lstnewmap((char *)line));
    printf("%s\n", config->map->grid);
}

int ft_check_line(char *line, t_config *config)
{
    (void)config;
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
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
    if (line[i] == '1')
        ft_map(config, line);
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

void print_map(t_map *map) {
    printf("MAP :");
    while (map) {
        printf("\n%s\n", map->grid);  // Printing each line of the map
        map = map->next;
    }
}

int main(int argc, char **argv)
{
    t_config *config;
    config = malloc(sizeof(t_config));
    t_map *map;
    map = malloc(sizeof(t_map));
    config->map = map;

    if (argc != 2)
        return (write(2, "Error: argument\n", 16));
    if (ft_parsing(config, argv[1]))
        return (1);
    print_map(config->map);
    return 0;
}