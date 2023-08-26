#include "philosopher.h"

int ft_atoi(char *s)
{
	int i;
	int num;

	i = -1;
	num = 0;
	while (s[++i])
		num = (num * 10) + (s[i] - 48);
	return (num);
}

//check that the arguments are the proper numbers and not too small
int	check_num(int argc, char **argv, t_data *data)
{
	data->numP = ft_atoi(argv[1]);
	data->timeTD = ft_atoi(argv[2]);
	data->timeTE = ft_atoi(argv[3]);
	data->timeTS = ft_atoi(argv[4]);
	data->numPME = 0;
	if (argc == 6)
		data->numPME = ft_atoi(argv[5]);
	else
		data->numPME = 0;
	if (data->numP < 1 || data->timeTD < 1 || data->timeTE < 1 ||\
	data->timeTS < 1)
		return (0);
	return (1);
}

//checks that the arguments are only numbers
int check_argv(int argc, char **argv, t_data *d)
{
	int	y;
	int	i;

	y = argc;
	if (argc < 5 || argc > 6)
		return (0);
	while (y--)
	{
		i = 0;
		while (argv[y][i] != 0 && y != 0)
		{
			if (!(argv[y][i] >= '0' && argv[y][i] <= '9'))
				return (0);
			i++;
		}
	}
	if (!check_num(argc, argv, d))
		return (0);
	return (1);
}
