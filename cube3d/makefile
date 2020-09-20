# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/19 13:34:56 by lduhamel          #+#    #+#              #
#    Updated: 2020/09/20 23:08:31 by lduhamel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

#	Sources

SRCS = $(SRCSDIR)/save.c $(SRCSDIR)/utils_parsing.c $(SRCSDIR)/acargv.c \
$(SRCSDIR)/init.c $(SRCSDIR)/sprites.c $(SRCSDIR)/color.c \
$(SRCSDIR)/elem_parsing.c $(SRCSDIR)/error_parsing.c $(SRCSDIR)/map.c \
$(SRCSDIR)/resolution.c $(SRCSDIR)/texture.c $(SRCSDIR)/utils_free.c \
$(SRCSDIR)/exit.c $(SRCSDIR)/main.c $(SRCSDIR)/utils.c $(SRCSDIR)/render.c \
$(SRCSDIR)/free.c $(SRCSDIR)/events.c $(SRCSDIR)/math.c $(SRCSDIR)/math2.c \
$(SRCSDIR)/motion.c $(SRCSDIR)/motion2.c $(SRCSDIR)/wall.c $(SRCSDIR)/wall2.c \
$(SRCSDIR)/map_parsing.c $(SRCSDIR)/map_parsing1.c $(SRCSDIR)/map_parsing2.c \
$(SRCSDIR)/print_sprites.c $(SRCSDIR)/sprites2.c
SRCSDIR = ./srcs
#	Objects

OBJS = $(SRCS:.c=.o)

#	Headers

HEADER = wolf.h
HEADERDIR = ./srcs

#	Libraries

LIBFTDIR = ./libs/libft
LIBFT = libft.a
# MINILIBDIR = ./libs/minilibx_linux
MINILIBDIR = ./libs/minilibx
MINILIB = libmlx.a
GNLDIR = ./libs/GNL
GNL = gnl.a

#	Name

NAME = cub3D

#	Compiler

CC = gcc

#	Flags

# CFLAGS = -lXext -lX11 -lm
CFLAGS = -Llibs/minilibx/ -lmlx -framework OpenGL -framework Appkit -Llibs/libft -lft -g
# CFLAGS = -fsanitize=address -Llibs/minilibx/ -lmlx -framework OpenGL -framework Appkit -Llibs/libft -lft


###############
##  TARGETS  ##
###############

all: $(NAME) Art

$(NAME): $(OBJS) $(LIBFT) $(MINILIB) $(GNL)
	@$(CC) -I$(HEADERDIR)/ $(OBJS) $(LIBFTDIR)/$(LIBFT) $(MINILIBDIR)/$(MINILIB) $(GNLDIR)/$(GNL) $(CFLAGS) -o $(NAME)
	@echo "cub3D compiled succesfully"

$(SRCSDIR)/%.o: %.c $(SRCSDIR)/$(HEADER)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(OBJS) $(LIBFTDIR)/*.o $(MINILIBDIR)/*.o $(GNLDIR)/*.o

fclean: clean
	/bin/rm -f $(NAME) $(LIBFTDIR)/$(LIBFT) $(MINILIBDIR)/$(MINILIB) $(GNLDIR)/$(GNL)

re: fclean all

$(LIBFT):
			@cd ${LIBFTDIR} && make
			@echo "libft compiled succesfully"

$(MINILIB):
			@cd ${MINILIBDIR} && make
			@echo "minilibx compiled succesfully"

$(GNL):
			@cd ${GNLDIR} && make
			@echo "get_next_line compiled succesfully"

.PHONY: all clean fclean re

Art:
	@echo ""
	@echo "     ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "    ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "    ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "    ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "    ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔"
	@echo ""
	@echo "cub3D ready to play"
	@echo "launch by following command: ./cub3D maps/<file.cub> --save(optional) followed by enter"