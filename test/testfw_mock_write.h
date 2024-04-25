/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mock_write.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:07 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 10:37:27 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_MOCK_WRITE_H
# define TESTFW_MOCK_WRITE_H

# include <stddef.h>

void	mock_write(int fildes);
size_t	unmock_write(int fildes, void **buf);
void	check_unmock_write(char *fn, int fildes,
			const void *exp_data, size_t exp_len);

#endif
