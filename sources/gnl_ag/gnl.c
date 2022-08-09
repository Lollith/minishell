#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_mstrchr(const char *s, char c)
{
	char	*s_end;
	int		i;

	s_end = NULL;
	i = 0;
	if (BUFFER_SIZE == 1)
		return (NULL);
	while (s[i])
	{
		if (((char)s[i]) == c)
		{
			if (s[i + 1] == '\0')
				return (NULL);
			s_end = (ft_substr(s, i + 1, ft_strlen(s) - i));
			return (s_end);
		}
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*piece_s;

	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
		len = 0;
	piece_s = (char *) malloc (sizeof (char) * (len + 1));
	if (!piece_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		piece_s[i] = s[start + i];
		i++;
	}
	piece_s[i] = '\0';
	return (piece_s);
}

char	*ft_p_strcpy(char *dest, char const *src, int *pt_i, int *pt_j)
{
	int	i;
	int	j;

	i = *pt_i;
	j = *pt_j;
	while (src[j])
	{
		dest[i] = src [j];
		i++;
		j++;
	}
	dest [i] = '\0';
	*pt_i = i;
	return (dest);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		ft_p_strcpy(s, s1, &i, &j);
		free((void *)s1);
	}
	j = 0;
	if (s2)
		ft_p_strcpy(s, s2, &i, &j);
	return (s);
}
int	ft_chr(const char *s, int c)
{
	if (!s)
		return (1);
	while (*s)
	{
		if ((char) *s == (char) c)
			return (0);
		s++;
	}
	return (1);
}

void	ft_freee( char *line, char *save_buf)
{
	free(save_buf);
	free(line);
}

char	*get_next_line2(int fd)
{
	char		*save_buf;
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	static char	*next;
	char		*save_line;

	save_line = NULL;
	if (fd < 0 || (read (fd, buf, 0) < 0) || BUFFER_SIZE < 0)
	{
		free(next);
		return (NULL);
	}
	while (ft_chr(save_line, '\n'))
	{
		buf[read (fd, buf, BUFFER_SIZE)] = '\0';
		if (!buf[0] && !next)
			return (save_line);
		save_buf = ft_strjoin(next, buf);
		next = ft_mstrchr(save_buf, '\n');
		line = ft_substr(save_buf, 0, (ft_strlen(save_buf) - ft_strlen(next)));
		save_line = ft_strjoin2(save_line, line);
		ft_freee(line, save_buf);
	}
	return (save_line);
}