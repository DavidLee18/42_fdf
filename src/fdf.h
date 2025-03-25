/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:29:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/26 02:12:40 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../ft_printf/src/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# define FDF "fdf"
# define INT_MAX_ 2147483647
# define INT_MIN_ -2147483648

typedef struct s_matrix
{
	size_t	col;
	size_t	cap;
	t_vec	*ptr;
}	t_matrix;

void		matalloc(t_list **dyn, t_matrix *mat);
void		add_row(t_list **dyn, t_vec row, t_matrix *mat);
void		add_col(t_list **dyn, t_vec col, t_matrix *mat);
t_matrix	*matmul(t_list **dyn, t_matrix *a, t_matrix *b);
t_matrix	*matmul2(t_matrix *c, t_matrix *a, t_matrix *b);
int			dot_prod(t_vec row, t_matrix *mat, size_t col);
t_matrix	*rotate(t_list **dyn, double angx, double angy, t_matrix *mat);
t_matrix	*get_vrot(t_list **dyn, double angle);
t_matrix	*get_hrot(t_list **dyn, double angle);
t_matrix	*ortho_proj(t_list **dyn, t_matrix *mat);
t_matrix	*_3d_point_vec(t_list **dyn, int x, int y, int z);

t_matrix	*atoi_split(t_list **dyn, int fd);
t_vec		*atoi_push(t_list **dyn, char **nums);
int			*atoi_(t_list **dyn, const char *str);

#endif
