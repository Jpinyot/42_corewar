/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_to_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:38:10 by jpinyot           #+#    #+#             */
/*   Updated: 2018/10/04 20:12:36 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	label_to_line(t_line *line, int fd)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (line->arg_size[i])
		{
			ft_invert_bytes(&line->arg[i], line->arg_size[i]);
			write(fd, &line->arg[i], line->arg_size[i]);
		}
	}
}

void		ft_line_to_file(t_line *bgn, t_label **label, int fd)
{
	t_line *line;

	line = bgn->next;
	while (line)
	{
		if (line->order_n)
		{
			write(fd, &(line->order_n), 1);
			if (line->ocp != 1)
				write(fd, &(line->ocp), 1);
			label_to_line(line, fd);
		}
		line = line->next;
	}
	ft_delstruct(label, bgn);
}
