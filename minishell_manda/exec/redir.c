/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:30:05 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/25 13:57:11 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_redir *redirections, int flag);
void	ft_rout(t_redir *red, int flag);
void	ft_append(t_redir *red, int flag);
void	ft_rin(t_redir *red, int flag);
void	ft_h_doc(t_redir *red);

void	handle_redirections(t_redir *redirections, int flag)
{
	t_redir	*redir;

	redir = redirections;
	while (redir)
	{
		if ((redir->tp == 1 || redir->tp == 2 || redir->tp == 3)
			&& (ft_strcmp(redir->file_name, "Œ") == 0))
		{
			ft_spcl_red(flag);
			return ;
		}
		if (redir->tp == 1)
			ft_rout(redir, flag);
		else if (redir->tp == 2)
			ft_append(redir, flag);
		else if (redir->tp == 3)
			ft_rin(redir, flag);
		else if (redir->tp == 4)
			ft_h_doc(redir);
		redir = redir->next;
	}
	fd_collector(36, 0);
}

void	ft_rout(t_redir *red, int flag)
{
	int	fd;

	fd = 0;
	if (red->file_name == NULL)
		return ;
	if (access(red->file_name, F_OK) == 0
		&& (access(red->file_name, W_OK) == -1))
	{
		show_prblm(red->file_name, 2, flag);
	}
	fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		if (errno == ENOENT)
			show_prblm(red->file_name, 1, flag);
		else if (errno == EISDIR)
			show_prblm(red->file_name, 3, flag);
		else
			show_prblm(red->file_name, 4, flag);
	}
	dup2(fd, 1);
	close(fd);
}

void	ft_append(t_redir *red, int flag)
{
	int	fd;

	fd = 0;
	if (red->file_name == NULL)
		return ;
	if (access(red->file_name, F_OK) == 0
		&& (access(red->file_name, W_OK) == -1))
	{
		show_prblm(red->file_name, 2, flag);
	}
	fd = open(red->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		if (errno == ENOENT)
			show_prblm(red->file_name, 1, flag);
		else if (errno == EISDIR)
			show_prblm(red->file_name, 3, flag);
		else
			show_prblm(red->file_name, 4, flag);
	}
	dup2(fd, 1);
	close(fd);
}

void	ft_rin(t_redir *red, int flag)
{
	int	fd;

	fd = 0;
	if (red->file_name == NULL)
		return ;
	if (access(red->file_name, F_OK) == -1)
	{
		show_prblm(red->file_name, 1, flag);
	}
	else if (access(red->file_name, F_OK) == 0
		&& (access(red->file_name, R_OK) == -1))
	{
		if (errno == EACCES)
			show_prblm(red->file_name, 2, flag);
		else if (errno == EISDIR)
			show_prblm(red->file_name, 3, flag);
		else
			show_prblm(red->file_name, 4, flag);
	}
	fd = open(red->file_name, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	ft_h_doc(t_redir *red)
{
	dup2(red->fd_her, 0);
	close(red->fd_her);
}
