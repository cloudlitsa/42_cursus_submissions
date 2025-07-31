/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:12:05 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/21 16:50:21 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# include <X11/keysym.h>
/* Event Definitions (same for both) */
# define X_EVENT_KEY_PRESS     2
# define X_EVENT_KEY_RELEASE   3
# define X_EVENT_MOUSE_PRESS   4
# define X_EVENT_MOUSE_MOVE    6
# define X_EVENT_EXIT          17

/* Mouse Buttons */
# define LEFT_CLICK    1

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

#endif
