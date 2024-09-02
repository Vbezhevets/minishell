NAME  = minishell

CC    = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-gdwarf-4 -O0 -fno-omit-frame-pointer -fsanitize=address,leak,undefined
LDFLAGS = -lreadline
RM    = rm -rf

LIBDIR= ./libft
LIBFT = ${LIBDIR}/libft.a

SRCSDIR     = srcs

BUILTINS_DIR = ${SRCSDIR}/builtins
CMDS_DIR    = ${SRCSDIR}/cmds
EXEC_DIR    = ${SRCSDIR}/exec
PARSER_DIR  = ${SRCSDIR}/parser
UTILS_DIR   = ${SRCSDIR}/utils

SRCS  = \
			${SRCSDIR}/main.c \
			${PARSER_DIR}/tokenizer.c \
			${PARSER_DIR}/parser.c \
			${PARSER_DIR}/expand.c \
			${PARSER_DIR}/quotes.c \
			${CMDS_DIR}/built_cmds.c \
			${CMDS_DIR}/heredoc.c \
			${CMDS_DIR}/redirect.c \
			${EXEC_DIR}/exec_prepare.c \
			${EXEC_DIR}/exec.c \
			${UTILS_DIR}/free_errors.c \
			${BUILTINS_DIR}/builtins.c \
			${BUILTINS_DIR}/export.c \
			${BUILTINS_DIR}/env.c \
			${UTILS_DIR}/str.c \
			${UTILS_DIR}/test.c \
			${UTILS_DIR}/extra.c \
			${CMDS_DIR}/build_cmd.c \


OBJSDIR     = ${SRCSDIR}/objs
OBJS        = $(SRCS:${SRCSDIR}/%.c=${OBJSDIR}/%.o)

all   : $(NAME)

$(NAME)     : $(OBJS)
		$(MAKE) --no-print-directory -C ${LIBDIR} all
		$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LDFLAGS)

${OBJSDIR}/%.o : ${SRCSDIR}/%.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ -I ./includes

clean :
		make --no-print-directory -C ${LIBDIR} clean
		$(RM) $(OBJSDIR)

fclean:
		make --no-print-directory -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME) 

re    : fclean all

.PHONY: all clean fclean bonus re
