
#
# VARIABLES
#

# Name of the executable(s)

NAME			= minishell

# Directories

LIBFT			= ./libft/libft.a
SRC_DIR			= src/
OBJ_DIR			= obj/
INC_DIR			= inc/

# Compiler and Flags

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
IFLAGS			= -I $(INC_DIR)
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
					$(MS_SRCS)miscellaneous/get_env.c \
					\
					$(MS_SRCS)set_redirections/set_commands.c \
					$(MS_SRCS)set_redirections/set_redirections.c \
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
				@echo "Compiling libft..."
				@make -s -C ./libft
				@make -s bonus -C ./libft
				@echo "	libft compiled succefully"
				
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):		$(OBJ) $(LIBFT)
				@echo "Compiling $(NAME)..."
				@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LIBFT) $(DEPS) -o $(NAME)
				@echo "	$(NAME) compiled succefully"


clean:			
				@$(RM) -r $(OBJ_DIR)
				@make clean -s -C ./libft
				@echo "	$(NAME)'s objects deleted succefully"
				
fclean:			
				@$(RM) -r $(OBJ_DIR)
				@make fclean -s -C ./libft
				@$(RM) $(NAME)
				@echo "	$(NAME)'s objects and $(NAME)'s executable deleted succefully"

re:				fclean all

# Phony (It helps avoid conflicts between files named the same)
.PHONY: 		all clean fclean re

