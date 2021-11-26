#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fftw3.h"

/*
  Purpose:

	COMPLEX_3D_EACH_CHANNEL_FFT: 2D FFT calculation for each channel of 3D data and get complex outputs

  Discussion:

	in: Input data, we generate h = 5, w = 10, d = 2 random complex values stored as a tensor of type fftwf_complex array named "in"
	out: 2D FFT calculation for each channel of 3D data
	in2 : 2D Inverse FFT calculation for each channel of out

*/

int main() {

	int i, j, h = 5, w = 10, d = 2;
	fftwf_complex* in, * out, * in2;
	fftwf_plan plan_backward;
	fftwf_plan plan_forward;

	// Create the input array.
	printf("\n Create the real and imaginary input values.");

	in = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h * d);

	srand(time(NULL));
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
		{
			// channel 1
			in[i * w + j][0] = rand() % 100;
			in[i * w + j][1] = 0;

			// channel 2
			in[i * w + j + h * w][0] = rand() % 100;
			in[i * w + j + h * w][1] = 0;
		}

	printf("\n");
	printf("  Input Data:\n");
	printf("REAL ----\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf("%10.4f ", in[i * w + j][0]);
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf("%10.4f ", in[i * w + j + h * w][0]);
		printf("\n");
	}
	printf("\nIMAG ----\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf("%10.4f ", in[i * w + j][1]);
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf("%10.4f ", in[i * w + j + h * w][1]);
		printf("\n");
	}


	/*
		Create the output array.
	*/
	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h * d);

	int rank = 2;					// we are computing 2d transforms 
	int n[] = { h, w };				// 2d transforms of size
	int howmany = d, * inembed = n, * onembed = n, idist, odist, istride, ostride;
	idist = odist = h * w;
	istride = ostride = 1;
	plan_forward = fftwf_plan_many_dft(rank, n, howmany, in, inembed, istride, idist, out, onembed, ostride, odist, FFTW_FORWARD, FFTW_ESTIMATE);

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
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", out[i * w + j + h * w][0]);
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
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", out[i * w + j + h * w][1]);
		printf("\n");
	}
	printf("\n");


	/*
		Recreate the input array.
	*/
	in2 = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h * d);

	plan_backward = fftwf_plan_many_dft(rank, n, howmany, out, inembed, istride, idist, in2, onembed, ostride, odist, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_backward);

	printf("\n Recovered input data divided by w * h:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][0] / float(w * h));
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j + h * w][0] / float(w * h));
		printf("\n");
	}
	printf("\n");
	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][1] / float(w * h));
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j + h * w][1] / float(w * h));
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