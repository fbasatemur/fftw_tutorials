#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fftw3.h"

/*
  Purpose:

	COMPLEX_2D_FFT: apply FFT to complex 2D data.

  Discussion:

	in: Input data, we generate h = 5, w = 10 random complex values stored as a matrix of type fftwf_complex named "in"
	out: FFTW compute the 2D Fourier transform of input data
	in2 : 2D Inverse Fourier Transform results
*/

int main() {

	int i, j, h = 5, w = 10;
	fftwf_complex* in;
	fftwf_complex* out;
	fftwf_complex* in2;
	fftwf_plan plan_backward;
	fftwf_plan plan_forward;

	// Create the input array.

	printf("\n Create the real and imaginary input values.");
	in = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h);

	srand(time(NULL));
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
		{
			in[i * w + j][0] = rand() % 100;
			in[i * w + j][1] = 0;
		}

	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in[i * w + j][0]);
		printf("\n");
	}
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in[i * w + j][1]);
		printf("\n");
	}
	printf("\n");

	// Create the output array.

	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h);
	plan_forward = fftwf_plan_dft_2d(h, w, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_forward);

	printf("\n Output FFT Coefficients:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", out[i * w + j][0]);
		printf("\n");
	}
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", out[i * w + j][1]);
		printf("\n");
	}
	printf("\n");


	//  Recreate the input array.

	in2 = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h);
	plan_backward = fftwf_plan_dft_2d(h, w, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_backward);

	printf("\n Recovered input data divided by w * h:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][0] / (w * h));
		printf("\n");
	}
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][1] / (w * h));
		printf("\n");
	}
	printf("\n");


	//  Free up the allocated memory.

	fftwf_destroy_plan(plan_forward);
	fftwf_destroy_plan(plan_backward);

	fftwf_free(in);
	fftwf_free(in2);
	fftwf_free(out);

	return 0;
}