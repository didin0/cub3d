######################################
# COLOR
######################################

#----TEXT-----

RED = \033[031m
DEF = \033[0m
GREEN= \033[032m
YELLOW= \033[33m
BLUE= \033[034m
PURPLE= \033[035m

######################################
# VARIABLES
######################################

SRCS = *.c \
	libft/*.c \
	get_next_line/*.c \

HEADERS = libft/libft.h get_next_line/get_next_line.h

DATARACE = -fsanitize=thread
SILENT = --no-print-directory
MAKE_SILENT = @make ${SILENT} -C
COMPILE = cc ${SRCS} ${CFLAGS} ${DEBUG} -o
MAKE_MSG = @printf "\n${PURPLE}Makefile : ${RED}${NAME}${DEF}\n\n"

NAME = cub3d
DEBUG=  #-fsanitize=address
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
ifeq ($(shell uname), Darwin)
	CFLAGS = $(MLX_FLAGS) -g -Wall -Werror #-Wextra ${DEBUG}
else
	@printf "\n${PURPLE}coucou${RED}\n\n"
endif

${NAME}: ${SRCS} ${HEADERS}
	clear
	${COMPILE} ${NAME}
	${MAKE_MSG}
	@$(MAKE) cube

######################################
# RULES	
######################################

all: ${NAME}

clean:
	@rm -rf ${OBJ}

fclean: clean
	@rm -rf ${NAME}
	@printf "\t\t${YELLOW}CLEANED!\n"

re: fclean all

run: re
	@./${NAME}

cube:
	@printf "\n"
	@printf "${RED}       +-------+\n${DEF}"
	@printf "${YELLOW}      /       /|${DEF}\n"
	@printf "${GREEN}     /       / |${DEF}\n"
	@printf "${BLUE}    +------+   |${DEF}\n"
	@printf "${PURPLE}    |      |   +${DEF}\n"
	@printf "${RED}    |      |  /${DEF}\n"
	@printf "${YELLOW}    |      | /${DEF}\n"
	@printf "${GREEN}    +------+\n${DEF}"
	@printf "\n"


.PHONY: all re clean fclean ascii_cube
