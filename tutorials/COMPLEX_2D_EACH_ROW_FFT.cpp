#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fftw3.h"

/*
  Purpose:

	COMPLEX_2D_EACH_ROW_FFT: 1D FFT calculation for each row of 2D data and get complex outputs

  Discussion:

	in: Input data, we generate h = 6, w = 10 random complex values stored as a matrix of type fftwf_complex array named "in"
	out: 1D FFT calculation for each row of 2D data
	in2 : 1D Inverse FFT calculation for each row of out

*/

int main() {

	int i, j, h = 6, w = 10;
	fftwf_complex* in, * out, * in2;
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


	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h);

	/*
		in[] -> *(in + col_index * istride + height * idist)

		if data is column-major (1d fft calculate for each col), set istride=howmany, idist=1
		if data is row-major	(1d fft calculate for each row), set istride=1, idist=N

		FFT calculation will be made for each row on below
	*/
	int rank = 1;			/* rank is equal 1 because we computing 1d fft transform for each row*/
	int n[] = { w };		/* w is length of 1d transform (that is length of a row) */
	int howmany = h;		/* how many 1d fft transforms ? Answer, as much as number of rows */
	int idist, odist, istride, ostride;
	idist = odist = w;
	istride = ostride = 1;  /* distance between two elements in the same column */
	int* inembed = n, * onembed = n;

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

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", out[i * w + j][1]);
		printf("\n");
	}
	printf("\n");


	in2 = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * w * h);
	plan_backward = fftwf_plan_many_dft(rank, n, howmany, out, inembed, istride, idist, in2, onembed, ostride, odist, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftwf_execute(plan_backward);

	printf("\n Recovered input data divided by width:");
	printf("\n REAL ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][0] / float(w));
		printf("\n");
	}
	printf("\n");

	printf("\n IMAG ---\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
			printf(" %10.4f ", in2[i * w + j][1] / float(w));
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