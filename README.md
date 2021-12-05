# FFTW Tutorials
<img src="https://img.shields.io/badge/FFTW-3.3.5-76B900?style=for-the-badge" alt="GPU" style="vertical-align:top margin:6px 4px">

This repo contains the fftw library examples for 1D/2D fourier transforms and an easy to use interface (**ffwf_.h**).

In the **tutorials** directory,
- [Complex_1D_FFT](https://github.com/fbasatemur/fftw_tutorials/blob/main/tutorials/COMPLEX_1D_FFT.cpp) : 1-dimensional fft calculation with complex input and complex output
- [Complex_2D_FFT](https://github.com/fbasatemur/fftw_tutorials/blob/main/tutorials/COMPLEX_2D_FFT.cpp) : 2-dimensional fft calculation with complex input and complex output
- [Real_2D_FFT](https://github.com/fbasatemur/fftw_tutorials/blob/main/tutorials/REAL_2D_FFT.cpp) : 2-dimensional fft calculation with real input and complex output
- [Complex_2D_Each_Row_FFT](https://github.com/fbasatemur/fftw_tutorials/blob/main/tutorials/COMPLEX_2D_EACH_ROW_FFT.cpp) : 1-dimensional fft calculation for each row of 2D matrix
- [Complex_3D_Each_Channel_FFT](https://github.com/fbasatemur/fftw_tutorials/blob/main/tutorials/COMPLEX_3D_EACH_CHANNEL_FFT.cpp) : 2-dimensional fft calculation for each channel of 3D tensor

## fftwf_.h
If the tutorials seem complicated to you, you can use **fftwf_.h** (Float values are preferred instead of double for operations).
You can get help from [**fftwf_tutorial**](https://github.com/fbasatemur/fftw_tutorials/blob/main/fftwf_tutorial.cpp) to use the fftwf interface. 

Below is the uml diagram for you to understand the FFTWF interface

![fftwf_uml](https://github.com/fbasatemur/fftw_tutorials/blob/main/doc/fftwf_uml.png)

