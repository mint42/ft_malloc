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

SRCS := $(foreach src_dir, $(SRC_DIRS), $(wildcard $(src_dir)/*.c))
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

LIBFT := $(LIBFT_DIR)/$(LIBFT_NAME)
MAKE_LIBFT := make -C $(LIBFT_DIR) -f $(LIBFT_MAKEFILE) --no-print-directory

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) Makefile config.mk
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MT $@ -c $< -o $@

-include $(DEPS)

$(LIBFT):
	@- $(MAKE_LIBFT) all

clean:
	@- $(RM) $(OBJS) $(DEPS)
	@- $(MAKE_LIBFT) clean

fclean: clean
	@- $(RM) $(NAME)
	@- $(MAKE_LIBFT) fclean

re: fclean all
