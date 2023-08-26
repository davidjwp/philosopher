#include "philosopher.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*itoa(long long n)
{
	char	*str;
	int	number;
	int	i;

	i = 0;
	number = n;
	while (number /= 10)
		i++;
	str = malloc((i + 2) * sizeof(char));
	str[i+1] = 0;
	while (i)
	{
		str[i--] = "0123456789"[n % 10];
		n = n / 10;
	}
	str[i] = "0123456789"[n % 10];
	return(str);
}