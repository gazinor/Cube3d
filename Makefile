NAME     =	Cub3D

# 	Compiler  #
CC       =	gcc

#	Flags     #
CFLAGS   =	-Wall -Wextra -Werror -O3 -g3 -fsanitize=address
GFLAGS   =	-lm -L$(MLX_PATH) -lmlx -I$(MLX_PATH) -framework OpenGL -framework Appkit

# 	Headers   #
HEADER_P = 	./includes
HEADER_N =	cub3d.h
HEADER   =	$(addprefix $(HEADER_P)/,$(HEADER_N))

#	Sources   #
SRC_PATH =	./srcs
SRC_NAME =	main.c \
			threads.c \
			display.c \
			display2.c \
			init.c \
			init2.c \
			launch.c \
			do_in_order.c \
			map.c \
			moves1.c \
			moves2.c \
			raycasting.c \
			obj.c \
			obj2.c \
			portal.c \
			screenshot.c \
			menu.c \
			menu2.c \
			option.c \
			parse.c \
			parse2.c \
			parse3.c \
			parse4.c \
			ft_itoa.c \
			color_screen.c \
			get_next_line.c \
			get_next_line_utils.c \
			transparence.c \
			floorcasting.c \
			events.c \
			utils.c \
			player2.c \
			monsters.c \
			load_images.c \
			load_gifs.c \
			load_gifs2.c \
			exit.c

SRC      =	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

DEP  = $(OBJ:%.o=%.d)

#	Objects   #
OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#	MiniLibX  #
MLX_PATH =	./mlx
MLX_LIB  =	libCub3d.a
MLX      =	$(addprefix $(MLX_PATH)/,$(MLX_LIB))

# unecessary vars  #
SCRIPT_P =	./scripts

################################################################################

all : header1 $(NAME) #$(MLX_LIB)

f : header2 $(NAME) #$(MLX_LIB)

$(MLX_LIB) :
	@make -C $(MLX_PATH)

header1 :
	@sh $(SCRIPT_P)/print_header.sh

header2 :
	@sh $(SCRIPT_P)/print_header2.sh


$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(GFLAGS) 

-include $(DEP)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<
	@printf "\e[1;30m$(CC): \e[1;37m./%-51s\e[1;0m" "$<"
	@printf "\e[32mcheck\e[1;0m\n"

save : fclean
	git add .
	git commit -m "$m"
	git push

clean :
	@make -C $(MLX_PATH) clean
	@rm -rf $(OBJ_PATH) #$(MLX_LIB) 

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
