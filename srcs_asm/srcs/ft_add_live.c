/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:50:14 by jpinyot           #+#    #+#             */
/*   Updated: 2018/10/06 15:34:32 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	intern_error(int l, int sel)
{
	ft_puterr("\x1B[91mInvalid live parameters at line ");
	ft_putnerr(l);
	if (sel == 0)
		ft_puterr(":\n\t\x1B[97m-At first parameter.");
	ft_puterr("\n\t\x1B[92mUsage:\x1B[97m");
	ft_puterr("\n\t-The first parameter must be direct.");
	ft_puterr("\n\t\x1B[92mExample:\x1B[97m\n\t");
	ft_puterr("live\t%12");
	ft_puterr("\n\e[0m");
	exit(-1);
}

t_line		*ft_add_live(char *l, int j, int n_line)
{
	t_line	*line;
	int		i;

	if ((i = ft_strcmp_index_jmp(&l[j], "live")) == -1 || l[i] == 0)
		ft_error_order(n_line, 0, "live", "live\t%432");
	i += j;
	line = ft_newline(NULL, 1, l, 1);
	if (l[i] == DIRECT_CHAR)
		i = ft_extract_dir(&line, i + 1, n_line, 0);
	else
		intern_error(n_line, 0);
	ft_check_for_coments(l, i, n_line);
	line->ocp = 1;
	return (line);
}
