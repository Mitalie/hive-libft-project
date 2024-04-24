/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mock_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:56:33 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 17:02:44 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "testfw_mock_write.h"
#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ssize_t				(*g_real_write)(int fildes,
		const void *buf, size_t nbyte) = 0;

static struct s_mock_data	*g_mocks = 0;
static int					g_max_mock_fd = -1;

// Stored buffer is appended with a null byte to make it usable with
// printf %s in check_unmock_write
static ssize_t	mocked_write(int fildes, const void *buf, size_t nbyte)
{
	struct s_mock_data	*mock;

	assert(nbyte);
	mock = &g_mocks[fildes];
	mock->buf = realloc(mock->buf, mock->buf_len + nbyte + 1);
	assert(mock->buf);
	memcpy(mock->buf + mock->buf_len, buf, nbyte);
	mock->buf_len += nbyte;
	((char *)mock->buf)[mock->buf_len] = 0;
	return (nbyte);
}

ssize_t	write(int fildes, const void *buf, size_t nbyte)
{
	if (!g_real_write)
		g_real_write = dlsym(RTLD_NEXT, "write");
	if (fildes >= 0 && fildes <= g_max_mock_fd && g_mocks[fildes].buf)
		return (mocked_write(fildes, buf, nbyte));
	return (g_real_write(fildes, buf, nbyte));
}

void	mock_write(int fildes)
{
	if (fildes > g_max_mock_fd)
	{
		g_mocks = realloc(g_mocks, sizeof (*g_mocks) * (fildes + 1));
		assert(g_mocks);
		while (g_max_mock_fd < fildes)
			g_mocks[++g_max_mock_fd].buf = 0;
	}
	assert(g_mocks[fildes].buf == 0);
	g_mocks[fildes].buf = malloc(0);
	g_mocks[fildes].buf_len = 0;
}

size_t	unmock_write(int fildes, void **buf)
{
	assert(fildes <= g_max_mock_fd && g_mocks[fildes].buf);
	*buf = g_mocks[fildes].buf;
	g_mocks[fildes].buf = 0;
	return (g_mocks[fildes].buf_len);
}

void	check_unmock_write(char *fn, int fildes,
	const void *exp_data, size_t exp_len)
{
	void	*buf;
	size_t	len;

	len = unmock_write(fildes, &buf);
	if (len != exp_len)
		TEST_FAIL("%s: captured write length %zu doesn't match expected %zu\n",
			fn, len, exp_len);
	else if (memcmp(buf, exp_data, exp_len))
		TEST_FAIL("%s: captured data \"%s\" doesn't match expected \"%s\"\n",
			fn, (char *)buf, (char *)exp_data);
	free(buf);
}
