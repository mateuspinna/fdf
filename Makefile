LFTPATH     = ./libft
LIBFT       = $(LFTPATH)/libft.a
MLX			= ./mlx/libmlx.a
MLX_FLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -L $(LFTPATH) -lft $(MLX_FLAGS)
NAME = fdf
SRCS =	fdf.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) *.c $(LIBFT) $(LIBS)-Lmlx $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	@$(CC) -c $(FLAGS) -o $@ $<

$(LIBFT):
	@$(MAKE) -C $(LFTPATH)

clean:
	@$(MAKE) -C $(LFTPATH) clean
	@$(RM) -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LFTPATH) fclean
	@$(RM) -rf $(NAME)

cleanlib:
	$(MAKE) clean -C $(LFTPATH)

re: fclean all

lldb: re $(OBJS)
	$(CC) $(FLAGS) -g $(SRCS) $(LIBFT) $(LIBS) -o $(NAME) $(MLX_FLAGS)

.PHONY = re all clean fclean lldb
