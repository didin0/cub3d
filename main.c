#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line/get_next_line.h"

typedef struct s_map {
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_config {
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color[3];
    int ceiling_color[3];
    t_map *map;
} t_config;

void free_map(t_map *map) {
    if (map && map->grid) {
        for (int i = 0; i < map->height; i++) {
            free(map->grid[i]);
        }
        free(map->grid);
    }
}

void free_config(t_config *config) {
    if (config) {
        if (config->no_texture) free(config->no_texture);
        if (config->so_texture) free(config->so_texture);
        if (config->we_texture) free(config->we_texture);
        if (config->ea_texture) free(config->ea_texture);
        free_map(config->map);
        free(config);
    }
}

int parse_color(char *str, int color[3]) {
    return sscanf(str, " %d,%d,%d ", &color[0], &color[1], &color[2]) == 3;
}

int get_map_height(int fd) {
    char *line;
    int height = 0;
    while ((line = get_next_line(fd)) != NULL) {
        height++;
        free(line);
    }
    lseek(fd, 0, SEEK_SET); // Reset the file descriptor to the beginning
    return height;
}

t_map *parse_map(int fd, int height) {
    t_map *map = malloc(sizeof(t_map));
    if (!map) return NULL;
    map->height = height;
    map->grid = malloc(sizeof(char *) * (height + 1));
    if (!map->grid) {
        free(map);
        return NULL;
    }

    char *line;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        map->grid[i++] = ft_strdup(line);
        free(line);
    }
    map->grid[i] = NULL;
    map->width = (i > 0) ? ft_strlen(map->grid[0]) : 0;
    return map;
}

int validate_map(t_map *map) {
    for (int i = 0; i < map->height; i++) {
        if (ft_strlen(map->grid[i]) != map->width) {
            return 0;
        }
    }
    for (int i = 0; i < map->width; i++) {
        if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1') {
            return 0;
        }
    }
    for (int i = 0; i < map->height; i++) {
        if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1') {
            return 0;
        }
    }
    return 1;
}

int parse_config(char *filename, t_config *config) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return 0;

    char *line;
    int map_started = 0;
    while ((line = get_next_line(fd)) != NULL) {
        if (ft_strncmp(line, "NO ", 3) == 0) {
            config->no_texture = strdup(line + 3);
        } else if (ft_strncmp(line, "SO ", 3) == 0) {
            config->so_texture = strdup(line + 3);
        } else if (ft_strncmp(line, "WE ", 3) == 0) {
            config->we_texture = strdup(line + 3);
        } else if (ft_strncmp(line, "EA ", 3) == 0) {
            config->ea_texture = strdup(line + 3);
        } else if (ft_strncmp(line, "F ", 2) == 0) {
            if (!parse_color(line + 2, config->floor_color)) {
                free(line);
                close(fd);
                return 0;
            }
        } else if (ft_strncmp(line, "C ", 2) == 0) {
            if (!parse_color(line + 2, config->ceiling_color)) {
                free(line);
                close(fd);
                return 0;
            }
        } else if (line[0] == '1' || line[0] == ' ') {
            if (!map_started) {
                map_started = 1;
                int height = get_map_height(fd);
                config->map = parse_map(fd, height);
                if (!config->map || !validate_map(config->map)) {
                    free(line);
                    close(fd);
                    return 0;
                }
            }
        }
        free(line);
    }
    close(fd);
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    t_config *config = malloc(sizeof(t_config));
    if (!config) return 1;
    ft_memset(config, 0, sizeof(t_config));

    if (!parse_config(argv[1], config)) {
        printf("Error: Could not parse config.\n");
        free_config(config);
        return 1;
    }

    // Print the parsed configuration
    printf("NO Texture: %s\n", config->no_texture);
    printf("SO Texture: %s\n", config->so_texture);
    printf("WE Texture: %s\n", config->we_texture);
    printf("EA Texture: %s\n", config->ea_texture);
    printf("Floor Color: %d,%d,%d\n", config->floor_color[0], config->floor_color[1], config->floor_color[2]);
    printf("Ceiling Color: %d,%d,%d\n", config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]);

    // Print the map for verification
    for (int i = 0; i < config->map->height; i++) {
        printf("%s\n", config->map->grid[i]);
    }

    free_config(config);
    return 0;
}
