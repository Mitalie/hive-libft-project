/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:28:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 11:13:35 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_INTERNAL_H
# define TESTFW_INTERNAL_H

# include <stddef.h>

struct s_test_list_node
{
	void					(*test_func)(void);
	const char				*test_name;
	struct s_test_list_node	*next;
};

struct s_mock_data
{
	void	*buf;
	size_t	buf_len;
};

#endif
