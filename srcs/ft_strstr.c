/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:45:50 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 12:08:09 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *str1)
{
	int	i;
	int	z;
	int	lenght;

	i = 0;
	z = 0;
	lenght = 0;
	while (str1[lenght])
		lenght++;
	if (lenght == 0)
		return (str);
	while (str[i])
	{
		while (str1[z] == str[i + z])
		{
			if (z == lenght - 1)
				return (str + i);
			z++;
		}
		z = 0;
		i++;
	}
	return (0);
}
