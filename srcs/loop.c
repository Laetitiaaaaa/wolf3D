/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/22 10:43:03 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_text(t_context *ct)
{
	TTF_Font		*font;
	SDL_Color		color = {255, 255, 255,  SDL_ALPHA_OPAQUE};
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25);
	if (font == NULL)
		quit("TTF_OpenFont()failed", ct);
	surface = TTF_RenderText_Solid(font, ft_itoa(ct->sp.mushroom_nb), color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	int	texw = 0;
	int texh = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texw, &texh);
	SDL_Rect dst= {80, 20, texw, texh };
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
	TTF_CloseFont(font);
}

void	draw_icon(t_context *ct)
{
	SDL_Rect dst;

	dst = define_rect(10, 10, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.mushroom, NULL, &dst);
	draw_text(ct);
}

static void	choose_interface(t_context *ct)
{
	if (ct->choose_inter == MAP)
	{
		draw_2d(ct);
		if (ct->at_least_one_sprite == TRUE)
			draw_sprite_in_2d(ct);
	}
	if (ct->choose_inter == GAME)
	{

		draw_background(ct);
		draw_wall(ct);
		if (ct->at_least_one_sprite == TRUE)
			draw_sprite_in_3d(ct);
		draw_icon(ct);
	}
}

static void	action_loop_game(t_context *ct)
{
	ct->cam.angle = angle_limit(ct->cam.angle);
	SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ct->rend);
	choose_interface(ct);
	SDL_RenderPresent(ct->rend);
}


void	loop(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	delta_time;
	unsigned int	frame_time;

	int		fps;
	unsigned int i = 0;
	fps = 0;
	frame_time = 1000 / 60;
	last_time = 0;
	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (ct->menu.in != OUT)
	{
		delta_time = SDL_GetTicks() - last_time;
		last_time += delta_time;
		delta_time < frame_time ? SDL_Delay(frame_time - delta_time) : 0;
		while (SDL_PollEvent(&event))
		{
			((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN)) ? ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		key_events(ct, state, delta_time);
		action_loop_game(ct);
		fps++;
		i += delta_time;

		if (i >1000)
		{
			// printf("fps%d\n", fps ); //fps
			fps = 0;
			i =0;
		}
	}
}

