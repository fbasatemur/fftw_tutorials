#include <iostream>
#include "fftwf_.h"

#define COMPLEX_1D 1
#define COMPLEX_2D 0
#define COMPLEX_2D_EACH_ROW 0
#define COMPLEX_2D_EACH_COL 0
#define COMPLEX_3D_EACH_CHANNEL 0

int main() {

	UINT i;
	FFTWF* complexFFT;

#if COMPLEX_1D
	UINT size = 10;
	complexFFT = FFTWF_Factory::Complex::_1D::Create(size);
#endif
#if COMPLEX_2D
	UINT rows = 5, cols = 10, size = rows * cols;
	complexFFT = FFTWF_Factory::Complex::_2D::Create(rows, cols);
#endif
#if COMPLEX_2D_EACH_ROW
	UINT rows = 5, cols = 10, size = rows * cols;
	complexFFT = FFTWF_Factory::Complex::_2D_Each_Row::Create(rows, cols);
#endif
#if COMPLEX_2D_EACH_COL
	UINT rows = 5, cols = 10, size = rows * cols;
	complexFFT = FFTWF_Factory::Complex::_2D_Each_Col::Create(rows, cols);
#endif
#if COMPLEX_3D_EACH_CHANNEL
	UINT rows = 4, cols = 5, depth = 2, size = rows * cols * depth;
	complexFFT = FFTWF_Factory::Complex::_3D_Each_Channel::Create(rows, cols, depth);
#endif

	float* inputReal = new float[size], *inputImag = new float[size];

	for (i = 0; i < size; i++) {
		inputReal[i] = i;
		inputImag[i] = 0.0F;
	}

	printf("\n fft inputs - real, imag \n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", inputReal[i]);
	printf("\n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", inputImag[i]);
	printf("\n");

	// input values set for fft calculate
	complexFFT->Forward()->SetIn(inputReal, inputImag);

	// calculate fft
	complexFFT->Forward()->Execute();

	// get fft results
	float* outReal = new float[size], * outImag = new float[size];
	complexFFT->Forward()->GetOut(outReal, outImag);

	printf("\n fft outputs - real, imag \n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", outReal[i]);
	printf("\n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", outImag[i]);
	printf("\n");

	// fft results set for ifft calculate
	complexFFT->Backward()->SetIn(outReal, outImag);

	// calculate ifft
	complexFFT->Backward()->Execute();

	// get ifft results
	float* invReal = new float[size], * invImag = new float[size];
	complexFFT->Backward()->GetOut(invReal, invImag);

	printf("\n ifft outputs - real, imag \n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", invReal[i]);
	printf("\n");
	for (i = 0; i < size; i++)
		printf(" %10.4f ", invImag[i]);
	printf("\n");

	return 0;
}