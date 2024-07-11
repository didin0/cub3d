#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

// Assurez-vous que vous avez bien déclaré la fonction get_next_line
char *get_next_line(int fd);

int main(int argc, char **argv)
{
    int fd;
    char *line;

    // Ouvrir le fichier en lecture seule
    fd = open("map.cub", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Lire le contenu du fichier ligne par ligne en utilisant get_next_line
    while ((line = get_next_line(fd)) != NULL)
    {
        // Afficher la ligne lue
        printf("Read from file:\033[34;01m \n%s \033[00m\n", line);
        // Libérer la mémoire allouée pour la ligne
        free(line);
    }

    // Fermer le descripteur de fichier
    close(fd);

    return 0;
}
