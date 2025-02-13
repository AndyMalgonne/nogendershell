### PROGRAM NAME ###
NAME		:= minishell

### UTILS ###
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g3
LDFLAGS 	:= -lreadline
DEP_FLAGS	:= -MMD -MP
MAKE_FLAG 	:= --no-print-directory --silent
RM 			:= rm -rf
IGNORE_RDLN	:= ignore_readline.supp

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
DRED		:= \033[0;31;5m
GREEN    	:= \033[0;32m
UGREEN    	:= \033[4;32m
YELLOW    	:= \033[;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m
NEW			:= \r\033[K

### DIRECTORIES ###
LIBFT_DIR 	:= libft
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs
BUILTIN_DIR	:= builtin
PARSING_DIR	:= parsing
EXEC_DIR	:= exec


### FILES ###
define INCLUDES	:=
	$(INCLD_DIR)/
	$(LIBFT_DIR)/$(INCLD_DIR)/
endef
INCLD_FLAG 	:= ${addprefix -I , ${INCLUDES}}

define INCLD_FILES :=
	minishell.h
	parsing.h
endef

### LIB ###
LIBFT		:= ${LIBFT_DIR}/libft.a
LIB 		:= ${LIBFT}
LIB 		:= ${strip ${LIB}}

### SRCS ###
define SRC 	:=
	$(addprefix $(BUILTIN_DIR)/, \
		pwd.c \
		echo.c \
		env.c \
		unset.c
	)
	$(addprefix $(EXEC_DIR)/, \
		builtin.c \
		exec.c \
		here_doc.c \
		here_doc_utils.c \
		path.c
	)
	$(addprefix $(PARSING_DIR)/, \
		checks.c \
		expand.c \
		is_checks.c \
		parse_input.c \
		token_utils.c \
		token_utils2.c \
		tokenize.c
	)
	main.c
	t_env.c
	t_iofile.c
	t_tree_utils.c
	t_tree.c
	t_env2.c
	utils.c
	prompt.c
	var.c
endef


SRC 		:= ${strip ${SRC}}
OBJS 		:= ${patsubst %.c,${OBJS_DIR}/%.o,${SRC}}
DEPS		:= ${patsubst %.c,${OBJS_DIR}/%.d,${SRC}}

### PROJECT ###
all: ${NAME}

${NAME}: ${LIB} ${OBJS}
	@printf "${NEW}${PURPLE}[${NAME}] ${UGREEN}Compiling :${DEFAULT}${BWHITE} $@${DEFAULT}"
	@${CC} ${CFLAGS} ${OBJS} ${LIB} ${INCLD_FLAG} -o $@ ${LDFLAGS}
	@printf "\n"

-include ${DEPS}
${OBJS_DIR}/%.o: ${SRC_DIR}/%.c
	@printf "${NEW}${PURPLE}[${NAME}] ${UGREEN}Compiling :${DEFAULT} $<"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/$(BUILTIN_DIR)
	@mkdir -p ${OBJS_DIR}/$(PARSING_DIR)
	@mkdir -p ${OBJS_DIR}/$(EXEC_DIR)
	@${CC} ${DEP_FLAGS} ${CFLAGS} ${INCLD_FLAG} -c $< -o $@

clean:
	@printf "${PURPLE}[${NAME}] ${RED}Cleaning ${DEFAULT}${OBJS_DIR} files.\n"
	@${RM} ${OBJS_DIR} ${OBJS_BONUS_DIR}

fclean: clean
	@printf "${PURPLE}[${NAME}] ${RED}Cleaning ${DEFAULT}${NAME}.\n"
	@${RM} ${NAME}

re: fclean all

### LIBFT ###
${LIBFT}:
	@make -C ${LIBFT_DIR} ${MAKE_FLAG}

cleanlib:
	@make -C ${LIBFT_DIR} clean ${MAKE_FLAG}

fcleanlib:
	@make -C ${LIBFT_DIR} fclean ${MAKE_FLAG}
	@printf "${DRED}[${LIBFT_DIR}] Library cleaned.\n"

relib:
	@make -C ${LIBFT_DIR} re ${MAKE_FLAG}

### NORM ###
norm: ; @make -C ${LIBFT_DIR} norm ${MAKE_FLAG}
	@norminette ${SRC_DIR} ${INCLD_DIR}

watch:
	watch norminette ${SRC_DIR} ${INCLD_DIR}

format:
	@for file in $(SRC); do \
		c_formatter_42 $(SRC_DIR)/$$file; \
	done
	@for file in $(INCLD_FILES); do \
		c_formatter_42 $(INCLD_DIR)/$$file; \
	done

### RUN ###
run: $(NAME)
	./$(NAME)

test: $(NAME) $(IGNORE_RDLN)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=$(IGNORE_RDLN) ./$(NAME)

.PHONY: all clean fclean re cleanlib fcleanlib relib norm watch format run test
