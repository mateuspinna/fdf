/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:45:10 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:42 by mateusteste      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined_str;
	int		s1s2_len;
	int		flag;

	flag = 0;
	if (!s2)
		return (0);
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
		flag++;
	}
	s1s2_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc((s1s2_len + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	while (*s1)
		*joined_str++ = *s1++;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	if (flag == 1)
		free(s1);
	return (joined_str - s1s2_len);
}
