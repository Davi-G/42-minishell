/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:47:25 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/28 19:47:31 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(char const *src, ...);
int		ft_putstr_pf(char *s);
void	print_pf(char c);
int		type_c(char c);
int		type_s(char *s);
int		type_p(unsigned long long num);
int		type_p_r(unsigned long long num, int i);
int		type_d(int num);
int		type_d_r(int num, int i);
int		type_u(int num);
int		type_u_r(int num, int i);
int		type_x(int num, const char type);
int		type_x_r(int num, const char type, int i);

#endif
