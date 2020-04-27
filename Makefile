# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:54:37 by rreedy            #+#    #+#              #
#    Updated: 2020/04/27 08:55:02 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

LIBFT := $(LIBFT_DIR)/$(LIBFT_NAME)
MAKE_LIBFT := $(MAKE) -C $(LIBFT_DIR) -f $(LIBFT_MAKEFILE) --no-print-directory

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) Makefile config.mk
	$(CC) $(CFLAGS) $(LNK_OBJ_FLAGS) $(OBJS) -o $(NAME) $(LIBFT_LDFLAGS)
	ln -sf $(NAME) $(NAMELINK)

$(LIBFT):
	@- $(MAKE_LIBFT) all

$(TEST): $(NAME) test_main.c
	$(CC) $(CFLAGS) test_main.c -o $(TEST) $(LIBFT_LDFLAGS) $(MALLOC_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(MK_OBJ_FLAGS) -MMD -MT $@ -c $< -o $@

-include $(DEPS)

clean:
	@- $(RM) $(OBJS) $(DEPS)
	@- $(MAKE_LIBFT) clean

fclean: clean
	@- $(RM) $(NAME)
	@- $(RM) $(NAMELINK)
	@- $(RM) -r test_main.o test_main.d $(TEST) $(TEST).dSYM
	@- $(MAKE_LIBFT) fclean

re: fclean all
