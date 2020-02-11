# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 09:39:36 by rreedy            #+#    #+#              #
#    Updated: 2020/02/10 16:36:05 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
NAMELINK := libft_malloc.so

SRC_DIR := ./srcs
INCLUDE_DIR := ./includes

CC := gcc
CFLAGS := -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -I$(INCLUDE_DIR)

MK_OBJ_FLAGS := -fPIC
LNK_OBJ_FLAGS := -shared

# testing

TEST := test

LIB := ft_malloc
LIB_DIR := ./

LDFLAGS := -l$(LIB) -L$(LIB_DIR)
