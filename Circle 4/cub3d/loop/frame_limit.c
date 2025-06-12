/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:25:12 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 17:25:12 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

#define FPS_LIMIT		60

void	limit_frame_sleep(struct timeval *current_time)
{
	struct timeval	end_time;
	long long		elapsed_us;
	const double	frame_time_us = 1000000.0 / FPS_LIMIT;

	gettimeofday(&end_time, NULL);
	elapsed_us = (end_time.tv_sec - current_time->tv_sec) * 1000000
		+ (end_time.tv_usec - current_time->tv_usec);
	if (elapsed_us < frame_time_us && elapsed_us > 0)
		usleep(frame_time_us - elapsed_us);
}
