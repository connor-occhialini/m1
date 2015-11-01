#include<stdio.h>
#include "pi_funs.h"
#include<math.h>
#include "timer.c"
#include "adjust.c"

int main(void)
{
	double tol = 0.000001;
	double abserr;
	double pi;

	int i = 1;
	printf("Leibniz Series\n");
	do
	{
		pi = pi_leibniz(i);
		abserr = fabs(pi - M_PI);
		printf ("%8d    %20.15f    %20.15f \n", i, pi, abserr);
		i *= 2;
	}
	while (abserr > tol);
	int nleib = i/2;	
	printf("Total iterations for Leibniz: %d\n", nleib);

	i = 1;
	printf("\n Bailey-Borwein-Plouffe Series \n");
	do
	{
		pi = pi_bbp(i);
		abserr = fabs(pi - M_PI);
		printf ("%8d    %20.15f    %20.15f \n", i, pi, abserr);
		i *= 2;
	}
	while (abserr > tol);
	int nbbp = i/2;
	printf("Total iterations for BBP: %d\n", nbbp);

	double time, tleib, tbbp;
	int tmin = 1;
	int tmax = 2;
	int count = 1000;

	printf("\n Timing for Leibniz Series:\n");
	do
	{
		timer_start ();
		for(i = 0; i < count; i++)
		{
			pi_leibniz(nleib);
		}
		time = timer_stop ();
		tleib = time /count;
		printf (" %10.2f usec     %10.6f sec    %10d\n",tleib * 1.e6, time, count);
		count = adjust_rep_count (count, time, tmin, tmax);
	}
	while ((time >tmax) || (time <tmin));

	printf("\n Timing for BBP Series:\n");
	do
	{
		timer_start ();
		for(i = 0; i < count; i++)
		{
			pi_bbp(nbbp);
		}
		time = timer_stop ();
		tbbp = time /count;
		printf (" %10.2f usec     %10.6f sec    %10d\n",tbbp * 1.e6, time, count);
		count = adjust_rep_count (count, time, tmin, tmax);
	}
	while ((time >tmax) || (time <tmin));

	printf("\nTime per function call for Leibniz:    %10.6f usec", tleib*1.e6);
	printf("\nTime per function call for BBP:        %10.6f usec", tbbp*1.e6);
	int ratio = tleib/tbbp;
	printf("\nRatio of function times tleib/tbbp:        %d\n",ratio);
}

