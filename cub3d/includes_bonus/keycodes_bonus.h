/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:12:05 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 21:06:07 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_BONUS_H
# define KEYCODES_BONUS_H

/* Event Definitions (same for both) */
# define X_EVENT_KEY_PRESS     2
# define X_EVENT_KEY_RELEASE   3
# define X_EVENT_MOUSE_PRESS   4
# define X_EVENT_MOUSE_MOVE    6
# define X_EVENT_EXIT          17

/* Mouse Buttons */
# define LEFT_CLICK    1

/* Linux (X11) Keysyms */
# include <X11/keysym.h>
# define KEY_Q       	XK_q
# define KEY_W       	XK_w
# define KEY_E       	XK_e
# define KEY_R       	XK_r
# define KEY_A       	XK_a
# define KEY_S       	XK_s
# define KEY_D       	XK_d
# define KEY_LEFT    	XK_Left
# define KEY_RIGHT   	XK_Right
# define KEY_FORWARD 	XK_Up
# define KEY_BACKWARD	XK_Down
# define KEY_ESC     	XK_Escape
# define KEY_F			XK_f
# define KEY_C			XK_c

#endif /* KEYCODES_H */
