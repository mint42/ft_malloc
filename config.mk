# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 09:39:36 by rreedy            #+#    #+#              #
#    Updated: 2020/01/09 05:42:25 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so

LIBFT_NAME := libft.a
LIBFT_DIR := ./libft
LIBFT_MAKEFILE := Makefile
LIBS := ft
LIB_DIRS := $(LIBFT_DIR)
LIB_INCLUDE_DIRS := $(LIBFT_DIR)/includes
LIB_INCLUDE_DIRS += $(LIBFT_DIR)/includes/ft_printf

SRC_DIRS := ./srcs
SRC_DIRS += ./srcs/actions
INCLUDE_DIRS := ./includes

CC := gcc
CFLAGS := -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += $(foreach include,$(INCLUDE_DIRS),-I$(include))
CFLAGS += $(foreach lib_include,$(LIB_INCLUDE_DIRS),-I$(lib_include))
LDFLAGS := $(foreach local_lib_dirs,$(LIB_DIRS),-L$(local_lib_dirs))
LDFLAGS += $(foreach lib,$(LIBS),-l$(lib))
