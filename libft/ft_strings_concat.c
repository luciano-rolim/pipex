/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_concat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:01:41 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/06/24 17:04:45 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strings_concat(char const *prefix, char *str1, char *str2)
{
	char	*intermediate_string;
	char	*final_string;

	if (!prefix || !str1 || !str2)
		return (NULL);
	intermediate_string = ft_strjoin(prefix, str1);
	if (!intermediate_string)
		return (NULL);
	final_string = ft_strjoin(intermediate_string, str2);
	free(intermediate_string);
	if (!final_string)
		return (NULL);
	return (final_string);
}
