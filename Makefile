
#
# VARIABLES
#

# Name of the executable(s)

NAME			= minishell

# Directories

LIBFT			= ./libft/libft.a
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compiler and Flags

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
RM				= rm -f

# Source Files

MS_SRCS			=	$(SRC_DIR)

# Conversion of files (Linking and applying pattern substituition to all source files)

SRC				=	\
					$(MS_SRCS)main.c \
					\
					$(MS_SRCS)parsing/parser.c \
					$(MS_SRCS)parsing/lexer.c \
					$(MS_SRCS)parsing/expander.c \
					$(MS_SRCS)parsing/post_expansion.c \
					$(MS_SRCS)parsing/parse_list.c \
					$(MS_SRCS)parsing/handle_cmd_args.c \
					$(MS_SRCS)parsing/handle_list_nodes.c \
					$(MS_SRCS)parsing/search_expan.c \
					$(MS_SRCS)parsing/handle_wspaces.c \
					\
					$(MS_SRCS)builtins/builtin_exit.c \
					\
					$(MS_SRCS)miscellaneous/data.c \
					$(MS_SRCS)miscellaneous/ft_functions.c \
					$(MS_SRCS)miscellaneous/lst_functions.c \
					$(MS_SRCS)miscellaneous/exit_functions.c \
					$(MS_SRCS)miscellaneous/free_functions.c \
					\
					$(MS_SRCS)signals/child_signals.c \
					$(MS_SRCS)signals/disable_signals.c \
					$(MS_SRCS)signals/environment_signals.c \
					$(MS_SRCS)signals/heredoc_signals.c \
					$(MS_SRCS)signals/eof_signals.c \
					$(MS_SRCS)ft_debug.c
				
OBJ				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRC))
DEPS			= ./libft/libft.a -lreadline

#
# RULES
#


all:			$(NAME)

$(LIBFT):	
				make -C ./libft
				make bonus -C ./libft
				
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ) $(LIBFT) $(PRINTF)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(DEPS) -o $(NAME)


clean:			
				$(RM) -r $(OBJ_DIR)
				make clean -C ./libft
				
fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re:				fclean all

# Phony (It helps avoid conflicts between files named the same)
.PHONY: 		all clean fclean re

