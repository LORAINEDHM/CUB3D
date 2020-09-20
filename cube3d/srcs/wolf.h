/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 10:37:34 by lduhamel          #+#    #+#             */
/*   Updated: 2020/09/20 23:09:41 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

/*
** -------------------------- External Headers ---------------------------------
*/

# include "../libs/minilibx/mlx.h"
# include "../libs/GNL/get_next_line.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*
** --------------------------------- Define ------------------------------------
*/

# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define KEY_LEFT 0
# define ESC 53
# define ROTATE_RIGHT 124
# define ROTATE_LEFT 123
# define PI 3.14159265358979323846264338327950288419716939937510
# define SPEED 5
# define SENSITIVITY 4
# define FORWARD 1
# define BACKWARD -1
# define RIGHT 1
# define LEFT 1
# define BLOCKSIZE 64
# define POV 66
# define TRANSLATE_RIGHT -90
# define TRANSLATE_LEFT 90
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1L
# define KEYRELEASEMASK 2L
# define STRUCTURENOTIFYMASK 10001
# define DESTROYNOTIFY 17
# define F_F 1
# define F_C 2
# define F_R 4
# define F_SP 8
# define F_NO 16
# define F_SO 32
# define F_WE 64
# define F_EA 128

/*
** ------------------------- Enum Definitions ----------------------------------
*/

typedef	enum	e_error2
{
	ERROR,
	NB_ARG_ERROR_TOO_MANY,
	NB_ARG_ERROR_TOO_FEW,
	FILE_EXT_ERROR,
	SAVE_FLAG_ERROR,
	ERROR_MALLOC,
	ERROR_OPEN_FILE,
	WRITE_ERROR,
	ERROR_NEW_IMAGE,
	ERROR_NEW_WINDOW,
	SUCCESS
}				t_error2;

typedef	enum	e_error
{
	MISSING_SPACE = -15,
	INVALID_CHAR_IN_RESOLUTION,
	WRONG_NB_OF_RESOLUTION_NB,
	NEGATIVE_NB,
	COMMA_ISSUE,
	NONEXISTENT_COLOR,
	WRONG_NB_OF_COLOR_NB,
	INVALID_CHAR_IN_COLOR,
	INVALID_TEXTURE_DESCRIPTION,
	TOO_MANY_DESCRIPTIONS,
	MISSING_ELEMENT,
	MALLOC_FAILED,
}				t_elem_error;

typedef	enum	e_map_error
{
	MAP_NOT_CLOSED = -30,
	WRONG_NB_OF_LETTER,
	FORBIDDEN_CHARACTER,
	EMPTY_LINE,
	DIAGONAL_WALL,
	MALLOC_FAIL,
}				t_map_error;

/*
** ------------------------- Structure Definitions -----------------------------
*/

typedef struct	s_move
{
	bool		up;
	bool		down;
	bool		right;
	bool		left;
	bool		camr;
	bool		caml;
}				t_move;

typedef struct	s_p
{
	double		x;
	double		y;
	double		z;
}				t_p;

typedef struct	s_map
{
	int			x;
	int			y;
	int			z;
}				t_map;

typedef struct	s_ray
{
	double		m;
	double		n;
}				t_ray;

typedef	struct	s_img
{
	void		*img_ptr;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_droite
{
	double		a;
	double		b;
	double		c;
}				t_droite;

typedef struct	s_sprites
{
	double		*dist;
	double		*x;
	double		*y;
	t_p			plandir;
	double		startdrawx;
	double		startdrawy;
	int			startray;
	double		height;
	t_ray		firstray;
	t_ray		lastray;
	t_ray		spriteray;
	t_ray		xaxis;
	t_droite	droite;
	t_droite	droite2;
	t_p			point;
	t_p			temp2;
	double		*walldist;
	double		*a;
	double		*c;
	double		spriteangle;
	int			endray;
	int			middleray;
	double		color;
	int			ystart;
}				t_sprites;

typedef struct	s_info
{
	void		*win_ptr;
	void		*mlx_ptr;
	int			**worldmap;
	int			mapwidth;
	int			mapheight;
	int			screenheight;
	int			screenwidth;
	double		angle;
	double		ad;
	double		bd;
	double		bad;
	t_p			dir;
	t_p			plan;
	t_p			p_of_plan;
	int			next_axis_x;
	int			next_axis_y;
	t_p			test_axis[2];
	int			redflag[2];
	bool		save_flag;
	char		*name_bmp_file;
	int			trgb_ceiling;
	int			trgb_floor;
	char		*we_texture;
	char		*sp_texture;
	char		*no_texture;
	char		*ea_texture;
	char		*so_texture;
	double		tex_y;
	double		tex_x;
	int			side;
	int			nesw;
	t_p			a;
	t_p			b;
	t_p			c;
	t_p			d;
	t_ray		ray;
	t_map		map[2];
	t_img		*img;
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_img		sp;
	int			wall[2];
	int			nbsprite;
	t_sprites	barrel;
	t_move		move;
	int			error;
	int			y;
	double		ratio;
}				t_info;

typedef struct	s_error
{
	int			ret;
	char		*msg;
}				t_error;

typedef struct	s_maptab
{
	int			fd;
	char		*line;
	int			counter;
	int			len_max;
	int			letter;
	char		*map_str1;
	char		*map_str2;
	int			lines_nb;
	int			**tab;
	int			i;
	int			j;
	int			ret;
	int			x;
	int			y;
	int			**sol;
	t_error		error;
}				t_maptab;

typedef struct	s_element
{
	char		*line;
	int			bitflag;
	int			counter;
	int			fd;
	int			ret;
	int			i;
	char		*msg;
	int			flag;
	int			t;
	int			r;
	int			g;
	int			b;
	char		*t_hex;
	char		*r_hex;
	char		*g_hex;
	char		*b_hex;
	char		*trgb;
	int			trgb_floor;
	int			trgb_ceiling;
	int			comma;
	int			texture_flag;
	int			nb_flag;
}				t_element;

int				ft_key_hit(int keycode, t_info *info, t_maptab *tab);
int				ft_key_release(int keycode, t_info *info);
int				events(t_info *info);
int				ft_handle_events(t_info *info, t_maptab *tab);
void			ft_move(t_info *info);
void			ft_render_display(t_info *info);
void			ft_free_img(t_info *info, t_img *img);
t_img			*ft_new_image(t_info *info, int screenwidth, int screenheight);
void			ft_exit(t_info *info, t_maptab *tab);
int				cub_check_ac_argv(t_info *info, int ac, char **argv);
void			cub_ac_argv_error(int error);
void			cub_avoid_wall_edge(t_info *info);
static int		cub_set_filename(char **pathname);
static int		cub_write_header(int fd, t_info *info);
static int		cub_write_dib(int fd, t_info *info);
static int		cub_write_data(int fd, t_info *info);
int				cub_save(t_info *info);
void			cub_error_save(int error);
void			cub_error_events(int error);
int				cub_check_nb_of_arg(int ac);
double			cub_redflag(t_info *info);
void			cub_main(t_info *info, t_maptab *tab);
void			display_1(t_info *info, int whichray,
					double wall_height, double color);
int				*display_2(t_info *info);

/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

int				hit_map(t_info *info, int n);
double			distance_to_wall(t_info *info);
void			test_x_axis(t_info *info);
void			test_y_axis(t_info *info);
void			p_on_plan(t_info *info, double whichray);
void			sprite(t_info *info, int n);

/*
** --------------------------- Parsing Functions -------------------------------
*/

int				parsing(t_element *elem, t_maptab *tab,
					t_info *info, char **argv);
void			init_parsing(t_element *elem, t_maptab *tab, t_info *info);
int				ft_strlen1(char *s);
char			*ft_strdup1(char *s1);
void			ft_putstr1(char *s);

/*
**   MAP ---------------------
*/

int				map_to_str(t_element *elem, t_maptab *tab, t_info *info);
int				ft_init(t_info *info, t_maptab *tab);
int				ft_init2(t_info *info, t_maptab *tab);
void			player_angle(t_maptab *tab, t_info *info, int i, int j);
int				check_diagonals(t_maptab *tab, int height, int x, int y);
int				str_to_tab(t_maptab *tab);
int				malloc_tab(t_maptab *tab);
char			*ft_join_lines(char *temp, char *line, int counter);
int				ft_check_line(t_maptab *tab, t_info *info, char **line, int i);
int				cleanline(t_maptab *tab, t_info *info,
					char **line, char **newline);
int				len_row(t_maptab *tab);
int				fill_shorter_lines(t_maptab *tab);
int				fill_shorter_lines2(t_maptab *tab, int i, int j, int limit);
int				mallocandinit_tab_sol(t_maptab *tab);
int				init_tab_sol(t_maptab *tab, int i, int j);
int				player_position(t_maptab *tab, t_info *info,
					int width, int height);
int				check_closing(t_maptab *tab, int height, int x, int y);
void			error_msg(t_info *info, t_maptab *tab, t_error *error, int n);
int				checking_map(t_maptab *tab, t_info *info);

/*
**  ELEMENTS ----------------
*/

int				read_elem(t_element *elem, t_maptab *tab, t_info *info);
int				nb_elements(t_element *elem, t_maptab *tab, t_info *info);
int				if_digit(t_element *elem);
int				is_digit(char c);
int				atoi_v1(t_element *elem);
int				color(t_element *elem);
int				which_color(t_element *elem, t_info *info);
int				create_trgb(t_element *elem, t_info *info, long int trgb);
void			init_rgb(t_element *elem);
int				resolution(t_element *elem, t_info *info);
int				checking_resolution_line(t_element *elem, t_info *info);
void			init_resolution(t_info *info);
char			*texture(t_element *elem, t_info *info);
int				which_texture(t_element *elem, t_info *info);
char			*creating_path(t_element *elem, t_info *info, int n);
int				texture_copy(t_element *elem, t_info *info, char *path, int n);
int				bit_texture(t_element *elem);
void			error_msg_elem(t_info *info, t_maptab *tab,
					t_element *elem, int n);
void			error_msg_elem2(t_info *info,
					t_maptab *tab, t_element *elem, int n);

/*
** ----------------------------- Error Handling- -------------------------------
*/

int				map_bounderies(t_info *info, int n);

/*
** ------------------------------ conversions ----------------------------------
*/

int				bloc_to_map(double position, double blocksize);

/*
** ----------------------------- Maths Functions -------------------------------
*/

double			distance_2_points(t_p a, t_p b);
void			ray(t_ray *ray, t_p a, t_p b);
double			ft_deg2rad(double degree);
double			ft_rad2deg(double rad);
void			find_y(t_p *a, double m, double n);
void			find_x(t_p *a, double m, double n);
double			toa(double angle, double o);
double			ft_distpointdroite(t_p p, t_droite e);

/*
** ------------------------------- Walls ---------------------------------------
*/

double			walls(t_info *info, double distance, int whichray);
double			fishbowl(t_info *info, double distorted_distance, int whichray);
double			projected_slice_height(t_info *info, double distance);
void			ft_display(t_info *info, int whichray, double distance);
void			put_texture(t_info *info);
void			nesw(t_info *info);

/*
** ------------------------------- Sprites -------------------------------------
*/

void			handlesprites(t_info *info);
int				barrel_xytab(t_info *info, t_maptab *tab);
void			coordinatesofbarrel(t_info *info);
void			distance_2_sprite(t_info *info);
void			ft_sort_sprites(t_info *info);
void			initialise(t_info *info, int i);
void			seekdrawstart(t_info *info, int i);
int				findray(t_info *info, int i, double x, double y);
double			spriteheight(t_info *info, double distance);
double			fishbowlsprite(t_info *info, double distorted_distance);
void			print_sprite(t_info *info, int i);
void			print_sprite_middle(t_info *info, int i);
void			print_sprite_left(t_info *info, int i,
					int whichray, double tex_x);
void			print_sprite_left2(t_info *info, int i,
					int whichray, double tex_x);
void			print_sprite_right(t_info *info, int i,
					int whichray, double tex_x);
void			print_sprite_right2(t_info *info,
					int i, int whichray, double tex_x);

/*
** --------------------------- Key Events --------------------------------------
*/

void			ft_angle(t_info *info);
int				ft_moove(int keycode, t_info *info);

/*
** ------------------------------ Motion --------------------------------------
*/

void			motion(t_info *info, int motion, int translation);
int				allowed_motion(t_info *info, double *displacement);
int				avoid_wall(t_map coordinates, t_info *info);
int				inside_map(t_info *info, t_map coordinates);
int				ft_key_press(int keycode, t_info *info, t_sprites *barrel);

/*
** --------------------------- Rendering --------------------------------------
*/

void			ft_put_in_img(t_info *info, int x, int y, int color);
int				saveintabs(t_info *info, t_maptab *tab);
void			update_info(t_info *info);

/*
** --------------------------- Free --------------------------------------
*/

void			free_and_init(char **variable);
void			free_tabs(t_info *info);
void			error_parsing_free(t_maptab *tab);
void			free_doubletab(int **tab, int i);
void			elem_free(t_info *info, t_maptab *tab);
void			texture_free(t_info *info);
void			free_and_init_tab(double *tab);
void			free_all(t_info *info, t_maptab *tab, int n);

#endif
