NAME  = minishell

CC    = cc
CFLAGS= -I/usr/local/opt/readline/include -g # Add any other flags you need here
LDFLAGS= -L/usr/local/opt/readline/lib -lreadline 
RM    = rm -rf

LIBDIR= ./libft
LIBFT = ${LIBDIR}/libft.a

SRCSDIR     = srcs
SRCS  = \
			${SRCSDIR}/main.c \
			${SRCSDIR}/tokenizer.c \
			${SRCSDIR}/parser.c \
			${SRCSDIR}/cmds.c \
			${SRCSDIR}/cmd_utils.c \
			${SRCSDIR}/exec_prepare.c \
			${SRCSDIR}/exec.c \
			${SRCSDIR}/free_errors.c \
			${SRCSDIR}/builtins.c \
			${SRCSDIR}/test.c \



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
