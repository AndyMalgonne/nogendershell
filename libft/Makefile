### PROGRAM_NAME ###
NAME = libft.a

### UTILS ###
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SILENT_FLAG 	:= --no-print-directory --silent

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
UGREEN    	:= \033[4;32m
YELLOW    	:= \033[;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m
NEW			:= \r\033[K

### DIR ###
GNL_SRC	= $(addprefix ft_gnl/, get_next_line.c get_next_line_utils.c)
PRT_SRC	= $(addprefix ft_printf/, conversion.c conversion2.c ft_printf.c)
OBJS	= ${SRCS:.c=.o} ${PRT_SRC:.c=.o} ${GNL_SRC:.c=.o}
INCLD_DIR	= include/

SRCS = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcat.c ft_strlcpy.c \
		ft_toupper.c ft_tolower.c ft_strncmp.c ft_strcmp.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_memcmp.c ft_memchr.c  ft_strnstr.c \
		ft_strdup.c ft_strndup.c ft_calloc.c \
		ft_split.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_striteri.c ft_strmapi.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_fsplit.c ft_ftab.c ft_strcut.c




all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(NEW)$(PURPLE)[$@] $(UGREEN)Building:$(DEFAULT)$(BWHITE) $@$(DEFAULT)"
	@ar rcs $@ $(OBJS)
	@printf "\n"

%.o: %.c
	@printf "$(NEW)$(PURPLE)[$(NAME)] $(UGREEN)Building:$(DEFAULT) $<"
	@${CC} ${CFLAGS} -I${INCLD_DIR} -c $< -o $@

clean:
	@$(RM) $(OBJS) $(BOBJS)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
	norminette ${SRCS} ${INCLD_DIR}

.PHONY : all clean fclean re norm
