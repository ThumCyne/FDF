
NAME = fdf

MLX = minilibx_macos/libmlx.a 

SRC = *.c
CC = gcc -Wall -Wextra -Werror

all	:	$(NAME)

mlxlib :
	@make -C minilibx_macos/  

$(NAME) : $(SRC) mlxlib
	$(CC) -o $(NAME) $(SRC) $(MLX) -framework OpenGL -framework AppKit 

clean : 
	rm fdf
	@make clean -C minilibx_macos/
	
re : clean all
