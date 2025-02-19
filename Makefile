<<<<<<< HEAD

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
=======
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 11:14:44 by mde-maga          #+#    #+#              #
#    Updated: 2025/02/10 19:22:31 by mde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = execute/builtins/cd.c \
		execute/builtins/echo.c \
		execute/builtins/exit.c \
		execute/builtins/env.c \
		execute/builtins/export.c \
		execute/builtins/pwd.c \
		execute/builtins/unset.c \
		execute/builtins/utils_cd.c \
		execute/executor/bin.c \
		execute/executor/cmd.c \
		execute/executor/start.c \
		execute/executor/utils.c \
		execute/executor/more_utils.c \
		execute/executor/main.c \

OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -Iheaders

LIBFT_DIR = utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Libraries
LIBS = -lreadline -lhistory

# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# High Intensity
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White
BILGreen='\033[1;38;2;147;196;125m'  # Bold Custom Color (#93c47d)

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White

MSG1 = @echo ${BILGreen}"✔︎ Compiled successfully"${Color_Off}
MSG2 = @echo ${BILGreen}"✔︎ Cleaned successfully"${Color_Off}
MSG3 = @echo ${BILGreen}"✔︎ Cleaned ${NAME} executable successfully"${Color_Off}
HOWTO = @echo ${BIGreen}"To run the program write:"${BIWhite}"./${NAME}"${Color_Off}

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	$(MSG1)
	$(HOWTO)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	$(MSG2)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	$(MSG3)

re: fclean all
>>>>>>> origin/executor

