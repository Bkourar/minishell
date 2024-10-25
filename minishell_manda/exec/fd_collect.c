/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:42 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/14 14:18:08 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_collector(int flag, int fd);
t_fd	*fd_new_node(int fd);
void	fd_add_back(t_fd **head, t_fd *new_node);

t_fd	*fd_new_node(int fd)
{
	t_fd	*new_node;

	new_node = (t_fd *)malloc(sizeof(t_fd));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->next = NULL;
	return (new_node);
}

void	fd_add_back(t_fd **head, t_fd *new_node)
{
	t_fd	*tmp;

	if (!new_node)
		return ;
	if (!(*head))
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
}

void	fd_close_all(t_fd **head)
{
	t_fd	*current;
	t_fd	*tmp;

	current = *head;
	while (current)
	{
		close(current->fd);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

void	fd_collector(int flag, int fd)
{
	static t_fd	*head;

	if (flag == 36)
	{
		fd_close_all(&head);
	}
	else
	{
		fd_add_back(&head, fd_new_node(fd));
	}
}
