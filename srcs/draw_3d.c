/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:41:03 by llejeune          #+#    #+#             */
/*   Updated: 2019/04/01 12:41:16 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_wall(t_context *ct)
{
	float	angle;
	int		x_pixel;

	SDL_QueryTexture(ct->wall.motif_red, NULL, NULL,
		&ct->wall.width, &ct->wall.height);
	angle = ct->cam.angle + 30;
	x_pixel = 0;
	while (x_pixel < ct->xwin)
	{
		angle -= (float)ANGLE / ((float)ct->xwin);
		draw_line_wall(ct, angle, x_pixel);
		x_pixel++;
	}
}

SDL_Rect	define_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

void		copy_texture_wall(float wall_point,
	t_context *ct, SDL_Texture *wall_texture)
{
	SDL_Rect	src;
	float		pos_text;

	pos_text = (((int)(wall_point * 1000) % 1000) * ct->wall.width) / 1000;
	src = define_rect((int)pos_text, 0, 1, ct->wall.height);
	if (SDL_RenderCopy(ct->rend, wall_texture, &src, &ct->wall.dst) < 0)
		quit("SDL_SetRenderCopy failed\n", ct);
}

void		draw_line_wall(t_context *ct, float angle, int x_pixel)
{
	float				distance;
	int					wall_height;
	t_floatpoint		wall;

	wall = dda_return_posi(ct, angle);
	if ((distance = dda_return_distance(ct, angle)) < 0)
		return ;
	wall_height = convert_mapdis_to_screendis(distance, ct);
	ct->wall.dst = define_rect(x_pixel,
		(ct->ywin - wall_height) / 2, 1, wall_height);
	angle = angle_limit(angle);
	if (((int)(wall.x * 10000.0) % 10000) == 0 && (angle >= 90 && angle <= 270))
		copy_texture_wall(wall.y, ct, ct->wall.motif_red);
	else if (((int)(wall.y * 10000.0) % 10000) == 0
		&& (angle >= 0 && angle <= 180))
		copy_texture_wall(wall.x, ct, ct->wall.motif_yellow);
	else if (((int)(wall.y * 10000.0) % 10000) == 0
		&& (angle >= 180 && angle < 360))
		copy_texture_wall(wall.x, ct, ct->wall.motif_green);
	else if (((int)(wall.x * 10000.0) % 10000) == 0
		&& ((angle >= 270 && angle < 360)
		|| (angle >= 0 && angle <= 90)))
		copy_texture_wall(wall.y, ct, ct->wall.motif_blue);
}

int			convert_mapdis_to_screendis(float distance, t_context *ct)
{
	float	dis_max;
	int		wall_height;

	dis_max = sqrt(pow(ct->mpp.x, 2) + pow(ct->mpp.y, 2));
	wall_height = (int)((dis_max - distance) * 50.0 / distance) + 5;
	return (wall_height);
}
