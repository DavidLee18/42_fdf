/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:29:49 by jaehylee          #+#    #+#             */
/*   Updated: 2025/04/02 02:04:59 by jaehylee         ###   ########.fr       */
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
# define SCALE 100
# define ESC 0xFF1B
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_matrix
{
	size_t	col;
	size_t	cap;
	t_vec	*ptr;
}	t_matrix;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point2
{
	int	x;
	int	y;
}	t_point2;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_matrix	*points;
	t_list		**dyn;
	t_point2	*dim;
}	t_fdf;

void		matalloc(t_list **dyn, t_matrix *mat);
_Bool		add_row(t_list **dyn, t_vec row, t_matrix *mat);
_Bool		add_col(t_list **dyn, t_vec col, t_matrix *mat);
t_matrix	*matmul(t_list **dyn, t_matrix *a, t_matrix *b);
t_matrix	*matmul2(t_matrix *c, t_matrix *a, t_matrix *b);
int			dot_prod(t_vec row, t_matrix *mat, size_t col);
t_matrix	*rotate(t_list **dyn, double angx, double angy, t_matrix *mat);
t_matrix	*get_vrot(t_list **dyn, double angle);
t_matrix	*get_hrot(t_list **dyn, double angle);
t_matrix	*ortho_proj(t_list **dyn, t_matrix *mat);
t_matrix	*_3d_point_col(t_list **dyn, int x, int y, int z);
t_vec		*mat2vec(t_list **dyn, t_matrix *mat);
t_matrix	*transpose(t_list **dyn, t_matrix *mat);
t_matrix	*append(t_list **dyn, t_matrix *a, t_matrix *b);
t_matrix	*matcpy(t_list **dyn, t_matrix *mat);

t_matrix	*atoi_split(t_list **dyn, int fd, t_point2 *dim);
t_matrix	*atoi_push(t_list **dyn, char **nums, size_t row, t_point2 *dim);
int			*atoi_(t_list **dyn, const char *str);
int			clamp(int val, int min, int max);

t_fdf		*parse_fdf(t_list **dyn, char *path);
_Bool		init_img(t_list **dyn, void *mlx, t_img **img);
_Bool		draw_fdf(t_fdf *f);
int			on_key(int keycode, t_fdf *f);
int			cleanup(t_fdf *f);
void		put_pixel(t_img *img, int x, int y, int color);
void		draw_line(t_img *img, t_point2 p1, t_point2 p2);
size_t		get_max_width(t_matrix *mat);
size_t		get_max_height(t_matrix *mat);
void		fit_scale(t_fdf *f);
void		fit_pos(t_fdf *f);
int			get_max_dx(t_matrix *mat);
int			get_max_dy(t_matrix *mat);
void		draw_lines(t_fdf *f);
t_point2	coord(t_matrix *points, int row, int col, t_point2 *dim);

#endif
