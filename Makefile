NAME  = minishell

CC    = cc
CFLAGS= -I/usr/local/opt/readline/include -g
LDFLAGS= -L/usr/local/opt/readline/lib -lreadline 
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
			${CMDS_DIR}/cmd_fields.c \
			${CMDS_DIR}/redirect.c \
			${EXEC_DIR}/exec_prepare.c \
			${EXEC_DIR}/exec.c \
			${UTILS_DIR}/free_errors.c \
			${BUILTINS_DIR}/builtins.c \
			${BUILTINS_DIR}/export.c \
			${UTILS_DIR}/str.c \
			${UTILS_DIR}/test.c \

OBJSDIR     = ${SRCSDIR}/objs
OBJS        = $(SRCS:${SRCSDIR}/%.c=${OBJSDIR}/%.o)


all   : $(NAME)

$(NAME)     : $(OBJS)
		make --no-print-directory -C ${LIBDIR} all
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
