/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:09:32 by jpinyot           #+#    #+#             */
/*   Updated: 2018/10/02 18:55:01 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static char		*ft_strtabspace(char *s, int j)
{
	int i;

	i = j;
	while (s[i] && (s[i] == '\t' || s[i] == ' '))
		i++;
	if (s[i] != '"')
		return (NULL);
	return (&s[i + 1]);
}

static int		ft_check_for_comm(char *s, int n_l)
{
	int i;
	int	ret;

	i = 0;
	while (s[i] && s[i] != '\"')
		i++;
	if (s[i] == 0)
		return (i);
	i++;
	ret = i;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == 0 || s[i] == COMMENT_CHAR || s[i] == END_LINE_CHAR)
		return (ret);
	ft_error_getname(n_l, 0);
	return (-1);
}

static t_header	ft_header_name(char *l, int n_l, int i, t_header h)
{
	char	*tmp;
	char	*d;
	int		j;
	int		end;

	tmp = l;
	if (h.flag_n == 0)
		if (!(tmp = ft_strtabspace(l, i)))
			ft_error_getname(n_l, 1);
	j = ft_check_for_comm(tmp, n_l);
	h.flag_n = 1;
	if (tmp[j - 1] == '\"')
		h.flag_n = 2;
	if (h.prog_name)
	{
		d = h.prog_name;
		h.prog_name = ft_strjoin(h.prog_name, tmp);
		/* free(l); */
		/* free(d); */
		h.name_size += j;
	}
	else
	{
		h.prog_name = tmp;
		h.name_line = l;
		h.name_size += j - 1;
	}
	return (h);
}

static t_header	ft_header_comment(char *l, int n_l, int i, t_header h)
{
	char	*tmp;
	char	*d;
	int		j;
	int		end;

	tmp = l;
	if (h.flag_c == 0)
		if (!(tmp = ft_strtabspace(l, i)))
			ft_error_getname(n_l, -1);
	j = ft_check_for_comm(tmp, n_l);
	h.flag_c = 1;
	if (tmp[j - 1] == '\"')
		h.flag_c = 2;
	if (h.comment)
	{
		d = h.comment;
		h.comment = ft_strjoin(h.comment, tmp);
		/* free(l); */
		/* free(d); */
		h.comment_size += j;
	}
	else
	{
		h.comment = tmp;
		h.comment_line = l;
		h.comment_size += j - 1;
	}
	return (h);
}
/*
static t_header	ft_header_comment(char *l, int n_l, int i, t_header h)
{
	char	*tmp;
	int		j;

	if (!(tmp = ft_strtabspace(l, i)))
		ft_error_getname(n_l, -1);
	if ((j = ft_check_for_comm(tmp, n_l)) > (COMMENT_LENGTH + 1) || j < 0)
		ft_error_getname(n_l, -2);
	h.comment = tmp;
	h.comment_size = j - 1;
	h.comment_line = l;
	return (h);
}
*/
t_header		ft_getname(char *line, int n_line, t_header h)
{
	int		i;
	int		j;

	j = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if ((i = ft_strcmp_index(&line[j], NAME_CMD_STRING)) != -1 || h.flag_n == 1)
		h = ft_header_name(line, n_line, i + j, h);
	else if ((i = ft_strcmp_index(&line[j], COMMENT_CMD_STRING)) != -1 || h.flag_c == 1)
		h = ft_header_comment(line, n_line, i + j, h);
	else if (line[j] != COMMENT_CHAR && line[j] != END_LINE_CHAR)
		ft_error_getname(n_line, 0);
	else
		ft_strdel(&line);
	return (h);
}
