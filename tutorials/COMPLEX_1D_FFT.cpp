#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fftw3.h"

/*
  Purpose:

	COMPLEX_1D_FFT: apply FFT to complex 1D data.

  Discussion:

	in: Input data, we generate n=50 random complex values stored as a vector of type fftwf_complex named "in"
	out: FFTW compute the Fourier transform of input data
	in2 : Inverse Fourier Transform results
*/

int main() {

	int i, n = 50;
	fftwf_complex* in;
	fftwf_complex* in2;
	fftwf_complex* out;
	fftwf_plan plan_backward;
	fftwf_plan plan_forward;

	// Create the input array.

	printf("\n Create the real and imaginary input values.");
	in = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * n);

	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		in[i][0] = rand() % 100;
		in[i][1] = 0;
	}

	printf("\n REAL ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", in[i][0]);
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", in[i][1]);
	printf("\n");

	// Create the output array.

	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * n);
	plan_forward = fftwf_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_forward);

	printf("\n Output FFT Coefficients:");
	printf("\n REAL ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", out[i][0]);
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", out[i][1]);
	printf("\n");


	//  Recreate the input array.

	in2 = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * n);
	plan_backward = fftwf_plan_dft_1d(n, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_backward);

	printf("\n Recovered input data divided by N:");
	printf("\n REAL ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", in2[i][0] / float(n));
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < n; i++)
		printf(" %10.4f ", in2[i][1] / float(n));
	printf("\n");


	//  Free up the allocated memory.

	fftwf_destroy_plan(plan_forward);
	fftwf_destroy_plan(plan_backward);

	fftwf_free(in);
	fftwf_free(in2);
	fftwf_free(out);

	return 0;
}