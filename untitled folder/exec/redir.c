#include "minishell.h"

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
		ft_putstr_x(red->file_name, ": permission denied:\n", NULL, 2);
		if (flag == 0)
			exit(ft_hrb(1, 1));
		ft_hrb(1, 1);
	}
	fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_putstr_x("open\n", NULL, NULL, 2);
		exit(ft_hrb(1, 1));
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
		ft_putstr_x(red->file_name, ": permission denied:\n", NULL, 2);
		if (flag == 0)
			exit(ft_hrb(1, 1));
		ft_hrb(1, 1);
	}
	fd = open(red->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		ft_putstr_x("open\n", NULL, NULL, 2);
		exit(ft_hrb(1, 1));
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
		ft_putstr_x(red->file_name, ": No such file or directory\n", NULL, 2);
		if (flag == 0)
			exit(ft_hrb(1, 1));
		exit(ft_hrb(1, 1));
	}
	else if (access(red->file_name, F_OK) == 0
		&& (access(red->file_name, R_OK) == -1))
	{
		ft_putstr_x(red->file_name, ": permission denied:\n", NULL, 2);
		if (flag == 0)
			exit(ft_hrb(1, 1));
		exit(ft_hrb(1, 1));
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
