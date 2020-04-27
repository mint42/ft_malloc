# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 09:39:36 by rreedy            #+#    #+#              #
#    Updated: 2020/04/27 07:26:49 by mint             ###   ########.fr        #
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

LIBS := ft_malloc
LIBS += ft
LIB_DIRS := ./
LIB_DIRS += $(LIBFT_DIR)
LIB_INCLUDE_DIR := $(LIBFT_DIR)/includes

SRC_DIR := ./srcs
INCLUDE_DIR := ./includes

CC := gcc
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)
LDFLAGS := $(foreach lib_dirs,$(LIB_DIRS),-L$(lib_dirs))
LDFLAGS += $(foreach lib,$(LIBS),-l$(lib))

MK_OBJ_FLAGS := -fPIC
LNK_OBJ_FLAGS := -shared

# testing
TEST := test
