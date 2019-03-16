/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:06:38 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/14 09:08:52 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"
# include <stdio.h>

# define XWIN 900
# define YWIN 600
# define CUBESIZE 1.0
# define NO_WALL -1

typedef enum 		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef enum 		e_neg_or_posi
{
	NEGATIVE = -1,
	POSITIVE = 1,
	ZERO = 0,
}					t_neg_or_posi;

typedef struct		s_map_params
{
	int				x;  // x and y are the number of points  for map 42, x = 10 y = 11
	int				y;
	int				ret;
	float			d;
	int				**map;
//	int				z_max;
//	int				z_min;
}					t_map_params;

typedef struct 		s_floatpoint
{
	float			x;
	float			y;
}					t_floatpoint;

typedef struct  	s_camera
{
	t_floatpoint	cam_position;
	float			angle; // angle is between 0 and 360


}					t_camera;

typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Event		*ev;
	t_camera		cam;
}					t_context;

int					load_map(t_context *ct, const char *argv);
int					init(t_context *ct, const char *argv);
void				quit(char *msg, t_context *ct);
void				loop(t_context *ct);
void				draw_background(t_context *ct);
SDL_Point			convert_plan_to_pixel(t_floatpoint n, t_context *ct);
void				dda(t_context *ct);
double				convert_degree_to_radian(double angle);
float				tan_angle_abs(float angle);
t_floatpoint		horizontal_first_delta_calcu(t_context *ct);
t_floatpoint		vertical_first_delta_calcu(t_context *ct);
void				horizontal_wall_position_calcu(t_context *ct);
t_floatpoint			vertial_wall_position_calcu(t_context *ct);




#endif
