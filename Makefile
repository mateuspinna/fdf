
all:
	make -C libft
	cc -g fdf.c libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o fdf
