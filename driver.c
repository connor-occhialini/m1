#include<stdio.h>
#include "pi_funs.h" 	/* Function declarations for series computations and M_PI */
#include<math.h>	
#include "timer.c"	/* Function declarations for timer_start() and timer_stop() */
#include "adjust.c"	/* Function declaration for adjust_rep_count() */

int main(void)
{
	/*Declare tolerance level (accuracy to which we want PI approximation)*/
	double tol = 0.000001;
	double abserr;
	double pi;
	
	/*Compute Leibniz Series until pi approximation has coverged to within tol of M_PI
	 *prints number of series terms, the approximation and the relative error at each stage
	 *returns number of iterations necessary at the end*/
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

	/*Compute BBP Series until pi approximation has coverged to within tol of M_PI
	 *prints number of series terms, the approximation and the relative error at each stage
	 *returns number of iterations necessary at the end*/	
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

	/* Define the intial number of counts, tmin, tmax*/
	double time, tleib, tbbp;
	int tmin = 1;
	int tmax = 2;
	int count = 1000;
	
	/*Runs the leibniz series function at number of iterations for our requested
	 *accuracy with respect to M_PI as many times as "count".  The time is recorded,
	 *and the time for each function call is saved as tleib. The number of counts
	 *is adjusted until the total time for count calls of pi_leibniz is between 1
	 *1 and 2 seconds.*/
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

	/*Runs the BBP series function at number of iterations for our requested
	 *accuracy with respect to M_PI as many times as "count".  The time is recorded,
	 *and the time for each function call is saved as tbbp. The number of counts
	 *is adjusted until the total time for count calls of pi_bbp is between 1
	 *1 and 2 seconds.*/
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

	/*Prints time per function call for leibniz and bbp series, and then takes
	 *the ratio between the times to compare the relative speed*/
	printf("\nTime per function call for Leibniz:    %10.6f usec", tleib*1.e6);
	printf("\nTime per function call for BBP:        %10.6f usec", tbbp*1.e6);
	int ratio = tleib/tbbp;
	printf("\nRatio of function times tleib/tbbp:        %d\n",ratio);
}

