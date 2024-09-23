# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 13:45:58 by resilva           #+#    #+#              #
#    Updated: 2024/09/10 13:57:52 by resilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGETS = process threads

SRC_PROCESS = process.c
SRC_THREADS = threads.c

CFLAGS = -pthread -g

CC = gcc

all:$(TARGETS)

process: $(SRC_PROCESS)
	$(CC) $(CFLAGS) $^ -o $@

threads: $(SRC_THREADS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)

.PHONY: clean all
	