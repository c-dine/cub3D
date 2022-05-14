/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:03 by ntan              #+#    #+#             */
/*   Updated: 2022/05/14 17:22:33 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include "sys/uio.h"
#include "sys/types.h"
#include "fcntl.h"
#include "unistd.h"

// struct s_data {
	
// }		t_data;

/** GARBAGE COLLECTOR **/

# define ERROR 0
# define NOERR 1

typedef struct s_memlst		t_memlst;

struct	s_memlst
{
	void		*address;
	t_memlst	*nxt;
};

int			mempush(void *ptr, const size_t byte, const size_t size);
int			memfree(void *ptr);
int			memrelease(void);

#endif