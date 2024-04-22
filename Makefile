# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/04/22 14:25:26 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBDIR = libft/
include libft/Makefile
SUBDIR =

.PHONY: all clean tclean fclean tfclean tre test

TESTFW_BIN = bin/testfw

TEST_SRCS = $(wildcard test/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_DEPS = $(TEST_OBJS:.o=.d)
TESTFW_OBJS = $(filter test/testfw%,$(TEST_OBJS))
TESTS = $(TESTFW_BIN) $(patsubst test/%.c,bin/%,$(wildcard test/test_*.c))

all: $(TESTS)

clean: tclean
tclean:
	rm -f $(TEST_OBJS) $(TEST_DEPS)

fclean: tfclean
tfclean: tclean
	rm -f $(TESTS)

tre: tfclean all

testbin:
	@mkdir -p bin

test: $(TESTFW_BIN)
	@./$(TESTFW_BIN)

$(TESTFW_BIN): $(TESTFW_OBJS) libft/libft.a | testbin
	$(CC) $(CFLAGS) $^ -o $@

bin/%: test/%.o libft/libft.a | testbin
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -MMD -Ilibft -c $< -o $@

-include $(TEST_DEPS)
