/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lang.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 07:27:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/12 14:55:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_LANG_H
# define PHILO_LANG_H

//Set color strings
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define RES	"\x1B[0m\n"

//Set error messages
# define LANG_E			"\x1b[48;2;100;0;0;1m[Error]\x1b[0m "
# define LANG_E_MALLOC	"\x1b[31mMalloc Error 🤡\n\x1b[0m"
# define LANG_E_IPA		"\x1b[31mInvalid Philo Arg (1) 🧠\n\x1b[0m"
# define LANG_E_TTD		"\x1b[31mInvalid Time to die Arg (2) 💀\n\x1b[0m"
# define LANG_E_TTE		"\x1b[31mInvalid Time to eat Arg (3) 🍗\n\x1b[0m"
# define LANG_E_TTS		"\x1b[31mInvalid Time to sleep Arg (4) 💤\n\x1b[0m"
# define LANG_E_ARG		"\x1b[31mInvalid Args count 🧐\n\x1b[0m"

//Set warn messages
# define LANG_W		"\x1b[48;2;140;140;0;1m[Warning]\x1b[0m "
# define LANG_W_TMP	"\x1b[33mToo much philo (over 200) ⚠️ \n\x1b[0m"
# define LANG_W_CP	"Philo created %ld/%ld \n\x1b[0m"

//Philo messages
# if PHILO_BETTER
#  define L_TIME	"⌚ \x1b[2;29m[ %10ldMS ]\x1b[0m "
#  define L_P_TH	"\x1b[48;2;100;0;150;1m Philo %d \x1b[0m is thinking 🧠"
#  define L_P_TF	"\x1b[48;2;120;120;20;1m Philo %d \x1b[0m has taken a fork🍴"
#  define L_P_SL	"\x1b[48;2;0;0;160;1m Philo %d \x1b[0m is sleeping 💤"
#  define L_P_EA	"\x1b[48;2;120;50;10;1m Philo %d \x1b[0m is eating 🍗"
#  define L_P_DI	"\x1b[48;2;160;0;0;1m Philo %d \x1b[0m died 💀"
# else
#  define L_TIME	"%ld "
#  define L_P_TH	"%d is thinking"
#  define L_P_TF	"%d has taken a fork"
#  define L_P_SL	"%d is sleeping"
#  define L_P_EA	"%d is eating"
#  define L_P_DI	"%d died"
# endif

#endif