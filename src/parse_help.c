#include "ft_sh.h"

int		is_shovel(char *format, int i)
{
	if (format[i] && format[i + 1] &&
		ft_isdigit(format[i]) && _redir(format[i + 1]))
		return (1);
	else if (_redir(format[i]))
		return (1);
	return (0);
}

int		is_all_space(char *format, int i)
{
	while (format[i])
	{
		if (!ft_isspace(format[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**st_strptrnew(size_t size)
{
	char			**tmp;
	unsigned int	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (0);
	while (i < size + 1)
	{
		*(tmp + i) = 0;
		i++;
	}
	return (tmp);
}

void	st_init(int *i, int *k, int *hold)
{
	*i = 0;
	*k = 0;
	*hold = 0;
}

int		op_len(char *c)
{
	int	i;

	i = 0;
	while (c[i] && _op(c[i]))
		i++;
	return (i);
}
