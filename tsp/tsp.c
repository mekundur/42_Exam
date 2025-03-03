#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


float	dist(float x0, float y0, float x1, float y1)
{
	float	diff[2];
	diff[0] = x1 - x0;	
	diff[1] = y1 - y0;	

}

void	tsp(float x[11], float y[11], int num, int i, int path, int *min)
{
	



}	

int	main(int argc, char **argv)
{
	float	x[11];
	float	y[11];
	int	num;
	int	i;
	int	min;

	i = 0;
	while(fscanf(stdin, "%f, %f", &x[i], &y[i]) == 2)
		i++;	
	
	num = i;
	fprintf(stdout, "num: %d\n", num);
	while (i-- > 0)
		fprintf(stdout, "%.2f, %.2f\n", x[i], y[i]);
	min =

}
