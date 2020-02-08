# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:54:37 by rreedy            #+#    #+#              #
#    Updated: 2019/11/20 05:26:37 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(OBJS) Makefile config.mk
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(TEST): $(NAME)
	$(CC) $(CFLAGS) $(NAME) -shared

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MT $@ -c $< -o $@

-include $(DEPS)

clean:
	@- $(RM) $(OBJS) $(DEPS)

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
