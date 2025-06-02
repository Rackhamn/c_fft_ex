# FFT - Fast Fourier Transform
The common formula for the FFT is as following:  
x[k] = (N-1)Sigma(n=0){(x[n]e)^((-j*2 * pi * kn) / N)  
  
`fft.c` implements a FFT algorithm on a dataset of size N and it outputs a dataset of size (N/2)-1 along with a title, sampling frequency and input dataset size (N)  
  
`plot.py` simply takes a this input from stdin and plots the `fft.c` output  
