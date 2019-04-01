/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_verticalwall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 11:45:06 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/31 11:45:08 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_floatpoint		vertical_first_delta_calcu(t_context *ct, float angle)
{
	t_floatpoint	d;

	angle = set_neg_posi(ct, angle);
	if (angle > 90 && angle < 270)
	{
		d.x = ct->cam.posi.x - (float)(int)(ct->cam.posi.x);
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(angle)));
	}
	else
	{
		d.x = ((float)(int)(ct->cam.posi.x + 1)) - ct->cam.posi.x;
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(angle)));
	}
	return (d);
}

t_floatpoint		first_vertical_step(t_context *ct, float angle, t_floatpoint detect)
{
	t_floatpoint	delta;

	delta = vertical_first_delta_calcu(ct, angle);
	detect.x += delta.x * ct->cam.neg_posi.x;
	detect.y += delta.y * ct->cam.neg_posi.y;
	return (detect);
}

t_floatpoint		continue_vertical_step(t_context *ct, float angle, t_floatpoint detect)
{
	detect.x += ct->cam.neg_posi.x * CUBESIZE;
	detect.y += ct->cam.neg_posi.y * CUBESIZE
	* ft_float_abs(tan(convert_degree_to_radian(angle)));
	return (detect);
}

t_floatpoint		sub_vertial(t_context *ct, float angle, t_floatpoint detect, SDL_Point to_int)
{
	int				count;

	count = 0;
	while (ct->mpp.map[to_int.y][to_int.x] != WALL_CUBE)
	{
		if (count == 0)
		{
			detect = first_vertical_step(ct, angle, detect);
			count++;
		}
		else
			detect = continue_vertical_step(ct, angle, detect);
		to_int.x = (int)detect.x;
		to_int.y = (int)detect.y;

		if (angle > 90 && angle < 270)
			to_int.x--;
		if (detect.x > ct->mpp.x - 1 || detect.x < 1 || detect.y <= 0 || detect.y >= ct->mpp.y)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
			return (detect);
		}
		if (ct->mpp.map[to_int.y][to_int.x] == SPRITE_CUBE)
			sprite_visible(ct, detect, to_int, angle);
	}
	return (detect);
}

t_floatpoint			vertical_wall_position_calcu(t_context *ct, float angle)
{
	t_floatpoint	detect;
	SDL_Point		to_int;

	detect.x = ct->cam.posi.x;
	detect.y = ct->cam.posi.y;
	to_int.x = (int)detect.x;
	to_int.y = (int)detect.y;
	angle = set_neg_posi(ct, angle);
	if ((angle == 90) || (angle == 270))
	{
		detect.x = NO_WALL;
		detect.y = NO_WALL;
		return(detect);
	}
	detect = sub_vertial(ct, angle, detect, to_int);
	return(detect);
}
