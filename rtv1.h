/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:11:00 by cel-oiri          #+#    #+#             */
/*   Updated: 2020/02/20 00:03:11 by cel-oiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MPI 3.141592653589793
# define SPHERE 2
# define PLANE 3
# define CONE 5
# define CYLINDER 4
# define MIN_DIS 1E-6

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_intersect_var
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		sqrdelta;
	double		t0;
	double		t1;
	double		k;
	int			min;
	t_vector	dist;
}				t_intersect_var;

typedef struct	s_list_pars
{
	char				*str;
	struct s_list_pars	*next;
}				t_list_pars;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_light
{
	t_vector		pos;
	t_vector		intensity;
	t_vector		color;
	struct s_light	*next;
}				t_light;

typedef struct	s_camera
{
	t_vector	w;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	origin;
	t_vector	lookfrom;
	t_vector	lookat;
	t_vector	lookup;
	double		vfov;
	double		aspect;
	double		theta;
	double		half_height;
	double		half_width;
	t_vector	i;
	t_vector	j;
	t_vector	k;
}				t_camera;

typedef struct	s_material
{
	t_vector	diffuse;
}				t_material;

typedef struct	s_obj
{
	int				type;
	double			radius;
	double			angle;
	double			vertex;
	t_vector		normal;
	t_vector		pos;
	t_vector		rot;
	t_vector		trans;
	t_vector		color;
	t_material		material;
	t_vector		axis;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_hit
{
	int			hit;
	double		t;
	t_vector	n;
	t_vector	p;
	t_material	m;
	t_vector	cam_point;
}				t_hit;

typedef struct	s_all
{
	t_obj		*obj;
	t_light		*lights;
	t_camera	cam;
}				t_all;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	int		end;
	int		s_l;
	int		b;
}				t_data;

typedef struct	s_shade_var
{
	t_light		*light;
	t_ray		r;
	t_vector	color;
	double		t;
}				t_shade_var;

t_all			*ft_all(char *namefile);
t_light			*ft_light_new(t_vector pos, t_vector color, t_vector intensity);
t_obj			*ft_obj_new(t_obj o);
t_list_pars		*verif_cone_cyl(t_list_pars *l2, int *v);
t_list_pars		*verif_plane(t_list_pars *l2, int *v);
t_list_pars		*verif_sphere(t_list_pars *l2, int *v);
int				deal_key(int key, t_data *w);
void			free_list(t_list_pars *lt);
void			free_all(t_all *all);
void			ft_add_light_back(t_light **lst, t_light *nw);
void			ft_add_obj_back(t_obj **lst, t_obj *ne);
int				ft_close(void *data);
t_obj			ft_cone_new(t_vector pos, double angle, t_vector color,
t_vector axis);
t_obj			ft_cylinder_new(t_vector pos, double radius, t_vector color,
t_vector axis);
int				ft_min_ray(double t1, double t2, double *t);
t_obj			ft_plane_new(t_vector pos, t_vector normal, t_vector color);
t_obj			ft_sphere_new(t_vector pos, double radius, t_vector color,
t_vector trans, t_vector rot);
t_ray			get_ray(double u, double v, t_camera *c);
void			graph(t_data *s, t_all *all);
void			hit_cone(t_hit *hit, t_obj *new, t_ray r);
void			hit_cylinder(t_hit *hit, t_obj *new, t_ray r);
void			hit_plan(t_hit *hit, t_obj *new, t_ray r);
void			hit_sphere(t_hit *hit, t_obj *new, t_ray r);
void			init_camera(t_camera *cam, t_vector lookfrom, t_vector lookat);
void			insert_cam(t_list_pars **lt, t_all *all);
void			insert_color(t_vector *vector, char *str);
void			insert_cone(t_list_pars **lt, t_all *all);
void			insert_cylinder(t_list_pars **lt, t_all *all);
void			insert_light(t_list_pars **lt, t_all *all);
void			insert_plane(t_list_pars **lt, t_all *all);
void			insert_sph(t_list_pars **lt, t_all *all);
int				intersect_ray_cone(t_ray *r, t_obj *cyl, double *t);
int				intersect_ray_cylinder(t_ray *r, t_obj *cyl, double *t);
int				intersect_ray_plan(t_ray *r, t_obj *p, double *t);
int				intersect_ray_sphere(t_ray *r, t_obj *s, double *t);
int				length_line_nbr(char *str);
t_hit			ray_primary_intersection(t_all *all, t_ray *r);
int				ray_secondary_intersection(t_all *all, t_ray *ray, t_hit *hit);
int				rgb_color(t_vector color);
void			rotation(t_vector *axis, t_vector rot);
unsigned int	shade(t_all *all, t_hit *hit);
void			translation(t_vector *pos, t_vector trans);
t_vector		vector_rot_x(t_vector v, double rad);
t_vector		vector_rot_y(t_vector v, double rad);
t_vector		vector_rot_z(t_vector v, double rad);
t_vector		vector_add(t_vector v1, t_vector v2);
t_vector		vector_sub(t_vector v1, t_vector v2);
t_vector		vector_normalize(t_vector v);
t_vector		vector_cross(t_vector v0, t_vector v1);
t_vector		vector_scale(t_vector v, double s);
t_vector		vector_mult(t_vector v1, t_vector v2);
double			vector_dot(t_vector v1, t_vector v2);
int				verif_camera(t_list_pars **l);
int				verif_format_file(t_list_pars *lt);
int				verif_name_obj(char *str);
int				wrong_format(int v);

#endif
