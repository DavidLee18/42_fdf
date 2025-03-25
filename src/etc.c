/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:56:03 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/25 23:14:47 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*atoi_split(t_list **dyn, int fd)
{
	char		*str;
	t_vec		*row;
	char		**tmp;
	t_matrix	*mat;

	mat = gc_calloc(dyn, 1, sizeof(t_matrix));
	if (mat == NULL)
		return (NULL);
	str = gc_getline(dyn, fd);
	if (str == NULL)
		return (NULL);
	while (str != NULL)
	{
		tmp = gc_split(dyn, str, ' ');
		if (tmp == NULL)
			return (NULL);
		row = atoi_push(dyn, tmp);
		if (!row)
			return (NULL);
		add_row(dyn, *row, mat);
		str = gc_getline(dyn, fd);
		if (str == NULL)
			return (NULL);
	}
	return (mat);
}

t_vec	*atoi_push(t_list **dyn, char **nums)
{
	t_vec	*v;
	size_t	i;
	int		*j;

	v = (t_vec *)gc_calloc(dyn, 1, sizeof(t_vec));
	if (v == NULL)
		return (NULL);
	i = 0;
	while (nums[i])
	{
		j = atoi_(dyn, nums[i]);
		if (j == NULL)
			return (NULL);
		push_front(dyn, v, *j);
		i++;
	}
	return (v);
}

int	*atoi_(t_list **dyn, const char *str)
{
	int		*res;
	long	temp;
	size_t	i;
	int		sign;

	res = (int *)gc_calloc(dyn, 1, sizeof(int));
	if (res == NULL)
		return (NULL);
	temp = 0;
	if (str[0] != '-' && str[0] != '+' && (str[0] < '0' || str[0] > '9'))
		return (NULL);
	sign = (str[0] != '-') * 2 - 1;
	i = (str[0] == '-' || str[0] == '+');
	while (i < ft_strlen(str))
	{
		if (str[i] < '0' || str[i] > '9')
			return (NULL);
		temp = 10 * temp + sign * (str[i] - '0');
		i++;
	}
	if (temp < INT_MIN_ || temp > INT_MAX_ || (ft_strlen(str) == 1 && sign
			&& !temp && ft_strncmp(str, "0", 1)))
		return (NULL);
	*res = (int)temp;
	return (res);
}
