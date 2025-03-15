
#
# COLORS
#

# Reset
Color_Off='\033[0m'       # Text Reset

BILGreen='\033[1;38;2;147;196;125m'  # Bold Custom Color (#93c47d)
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

MSG1 = @echo ${BILGreen}"✔︎ Compiled successfully"${Color_Off}
MSG2 = @echo ${BILGreen}"✔︎ Cleaned successfully"${Color_Off}
MSG3 = @echo ${BILGreen}"✔︎ Cleaned ${NAME} executable successfully"${Color_Off}
HOWTO = @echo ${BIGreen}"To run the program write:"${BIWhite}"./${NAME}"${Color_Off}

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
					$(MS_SRCS)set_redirections/set_commands.c \
					$(MS_SRCS)set_redirections/set_redirections.c \
					$(MS_SRCS)set_redirections/heredoc.c \
					\
					$(MS_SRCS)executor/bin_cmds.c \
					$(MS_SRCS)executor/bin_utils.c \
					$(MS_SRCS)executor/builtin_cmds.c \
					$(MS_SRCS)executor/pipeline.c \
					$(MS_SRCS)executor/start.c \
					$(MS_SRCS)executor/utils.c \
					\
					$(MS_SRCS)builtins/builtin_exit.c \
					$(MS_SRCS)builtins/cd.c \
					$(MS_SRCS)builtins/echo.c \
					$(MS_SRCS)builtins/env.c \
					$(MS_SRCS)builtins/export.c \
					$(MS_SRCS)builtins/pwd.c \
					$(MS_SRCS)builtins/unset.c \
					$(MS_SRCS)builtins/utils_cd.c \
					\
					$(MS_SRCS)miscellaneous/data.c \
					$(MS_SRCS)miscellaneous/ft_functions.c \
					$(MS_SRCS)miscellaneous/lst_functions.c \
					$(MS_SRCS)miscellaneous/exit_functions.c \
					$(MS_SRCS)miscellaneous/free_functions.c \
					$(MS_SRCS)miscellaneous/get_env.c \
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
				$(MSG1)
				$(HOWTO)


clean:			
				@$(RM) -r $(OBJ_DIR)
				@make clean -s -C ./libft
				$(MSG2)
				
fclean:			
				@$(RM) -r $(OBJ_DIR)
				@make fclean -s -C ./libft
				@$(RM) $(NAME)
				$(MSG3)

re:				fclean all

# Phony (It helps avoid conflicts between files named the same)
.PHONY: 		all clean fclean re
