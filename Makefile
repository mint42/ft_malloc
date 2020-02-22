# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:54:37 by rreedy            #+#    #+#              #
#    Updated: 2020/02/22 01:04:16 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(OBJS) Makefile config.mk
	$(CC) $(CFLAGS) $(LNK_OBJ_FLAGS) $(OBJS) -o $(NAME)
	ln -sf $(NAME) $(NAMELINK)

$(TEST): $(NAME) test_main.o
	$(CC) $(CFLAGS) test_main.o -o $(TEST) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(MK_OBJ_FLAGS) -MMD -MT $@ -c $< -o $@

-include $(DEPS)

clean:
	@- $(RM) $(OBJS) $(DEPS)

fclean: clean
	@- $(RM) $(NAME)
	@- $(RM) $(NAMELINK)
	@- $(RM) -r test_main.o test_main.d $(TEST) $(TEST).dSYM

re: fclean all
