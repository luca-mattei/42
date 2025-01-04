/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:46:30 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/16 12:14:39 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_char(int c);
int ft_str(char *str);
int	ft_pointer(void *ptr);
int	ft_decimal(int c);
int	ft_unsigned_decimal(unsigned int c);
int	ft_hexa(unsigned int nbr, char *base);
int	ft_printf(const char *s, ...);

#endif
