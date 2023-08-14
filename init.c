#include "philosopher.h"

int atoi(char *s)
{
	int num;
	int i;

	i = 0;
	num = 0;
	while (s[i] != 0)
		i++;
	while (i--)
	{
		num += s[i] - 48;
		num *= 10;
	}
	return (num);
}

int check_argv(int argc, char **argv, t_data *data)
{
	int	y;
	int	i;

	y = argc;
	if (argc < 4 || argc > 5)
		return (0);
	while (y)
	{
		i = 0;
		while (argv[y][i] != 0)
		{
			if (!(argv[argc][i] >= '0' && argv[argc][i] <= '9'))
				return (0);
			i++;
		}
		y--;
	}

}

int main(int argc, char **argv)
{
	t_data	data;

	if (!check_argv(argc, argv, &data))
		return(write (1,"Error\n", 6), 0);
	// pthread_create();
	return (0);
}

// number_of_philosopher - time_to_die - time_to_eat

// time_to_sleep number_of_times_each_philosopher_must_eat

// philosopher num 1 > philosopher num 2 > philosopher num 3 