#define M_PI 3.14159265358979323846	/* pi */

double pi_leibniz (int n);
double pi_bbp (int n);

/* 
    Begins by defining the first term in the sequence (sum = 1), then adding terms by
    adding 2 to the denominator of each term and alternating the sign of each term by
    multiplying it by -1 at each iteration.  Then, this next term is incorporated into
    the sum by (sum += (num/denom)). The return of this function is 4 times the result
    of the iteration.
	*/

double pi_leibniz (int n)
{
	double sum = 1, num = 1, denom = 1;
	int i;
	for(i = 0; i < (n-1); i++)
	{
		denom += 2;
		num *= -1;
		sum += (num/denom);
	}
	return (sum *= 4);
}
	

/*
	Begins by defining the denominator of each term in the sum for k=0.  Then the sum
	of these terms corresponding to k=0 is computed a stored.  For each iteration, each
	denominator in the sum has 8*k added to it and the coefficient denominator is multiplied
	by 16.  Then this term is added onto "sum".
	*/

double pi_bbp (int n)
{
	double coden = 1, t1den = 1, t2den = 4, t3den = 5, t4den = 6; 
	double sum = 1/coden*(4/t1den - 2/t2den - 1/t3den - 1/t4den);
	int i;
	for(i = 0; i < (n-1); i++)
	{
		t1den += 8;
		t2den += 8;
		t3den += 8;
		t4den += 8;
		coden *= 16;
		sum += 1/coden*(4/t1den - 2/t2den - 1/t3den - 1/t4den);
	}
	return (sum);
}

