# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 09:39:36 by rreedy            #+#    #+#              #
#    Updated: 2020/04/27 08:57:05 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
NAMELINK := libft_malloc.so

LIBFT_NAME := libft.a
LIBFT_DIR := ./libft
LIBFT_MAKEFILE := Makefile
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/includes

SRC_DIR := ./srcs
INCLUDE_DIR := ./includes

CC := gcc
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR)
LIBFT_LDFLAGS := -L$(LIBFT_DIR) -lft
MALLOC_LDFLAGS := -L./ -lft_malloc

MK_OBJ_FLAGS := -fPIC
LNK_OBJ_FLAGS := -shared

# testing
TEST := test
