#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fftw3.h"

/*
  Purpose:

	REAL_2D_FFT: apply FFT to real 2D data and get complex outputs

  Discussion:

	in: Input data, we generate h = 5, w = 10 random real values stored as a matrix of type float array named "in"
	out: FFTW compute the 2D Fourier transform of input data
	in2 : 2D Inverse Fourier Transform (only real values are obtained)

	The Fourier coefficients are stored in an h by nxW array where nxW = (w/2) + 1.
	We only compute about half the data because of real data implies symmetric FFT coefficients.
*/

int main() {

	int i, j, h = 5, w = 10;
	float* in = nullptr;
	fftwf_complex* out;
	float* in2 = nullptr;
	fftwf_plan plan_backward;
	fftwf_plan plan_forward;

	// Create the input array.

	printf("\n Create the real and imaginary input values.");
	in = (float*)malloc(sizeof(float) * w * h);

	srand(time(NULL));
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
			in[i * w + j] = rand() % 100;

	printf("\n Input real data ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in[i * w + j]);
		printf("\n");
	}
	printf("\n");


	/*
		Create the output array out, which is of type fftwf_complex,
		and of a size h * nxW that is roughly half the dimension of the input data
	*/
	int nxW = (w / 2) + 1;

	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * h * nxW);
	plan_forward = fftwf_plan_dft_r2c_2d(h, w, in, out, FFTW_ESTIMATE);

	fftwf_execute(plan_forward);

	printf("\n Output FFT Coefficients:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < nxW; j++)
			printf(" %10.4f ", out[i * nxW + j][0]);
		printf("\n");
	}
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < nxW; j++)
			printf(" %10.4f ", out[i * nxW + j][1]);
		printf("\n");
	}
	printf("\n");


	//  Recreate the input array.

	in2 = (float*)malloc(sizeof(float) * w * h);
	plan_backward = fftwf_plan_dft_c2r_2d(h, w, out, in2, FFTW_ESTIMATE);

	fftwf_execute(plan_backward);

	printf("\n Recovered input data divided by w * h:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j] / (w * h));
		printf("\n");
	}
	printf("\n");


	//  Free up the allocated memory.

	fftwf_destroy_plan(plan_forward);
	fftwf_destroy_plan(plan_backward);

	free(in);
	free(in2);
	fftwf_free(out);

	return 0;
}