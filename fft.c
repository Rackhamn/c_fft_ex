#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // -lm
#include <complex.h>

#define PI	3.1415926535897932384626434
#define TAU	6.2831853071795864769252868

void _fft(complex * buf, complex * out, int n, int step) {
	if(step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);

		for(int i = 0; i < n; i += 2 * step) {
			complex t = cexp(-I * PI * ((double)i / (double)n)) * out[i + step];
			buf[i / 2] = out[i] + t;
			buf[(i + n) / 2] = out[i] - t;
		}
	}
}

void fft(complex * buf, int n) {
	complex * out = malloc(sizeof(complex) * n);

	for(int i = 0; i < n; i++) {
		out[i] = buf[i];
	}

	_fft(buf, out, n, 1);

	free(out);
}

// * https://github.com/neeraj1397/Fast-Fourier-Transform-in-C/blob/main/Methodology%20and%20Theoretical%20verification.pdf
// FFT = x[k] = (N-1)Sigma(n=0){ (x[n]e)^((-j*2 * pi * kn) / N) }
// F(x) = Integral(+inf, -inf) == f(x) * e^(-x) * dt

// X_k = 1/N * (N-1)Sigma(n=0){ x_(n^e^(i * 2 * pi * k (n / N))) }

/*

Y = fft/X)
X = ifft(Y)

Y(k) = (n)Sigma(j=1){X(j) * (W_n)^((j-1) * (k - 1))}
X(j) = (1/n)(n)Sigma(k=1){Y(k) * (W_n)^((-(j-1) * (k -1)))}

*/

/*

exp(-t^2-u^2) := fourier(x):
pi^(1/2)*exp(- t^2 - w^2/4)

a*abs(t) := fourier(x):
-(2*a)/w^2


exp(-t^2-u^2) := fourier(x, y):
pi^(1/2)*exp(- t^2 - y^2/4)

a*abs(t) := fourier(x, y):
-(2*a)/y^2


exp(-t^2-u^2) := fourier(x, t, y):
pi^(1/2)*exp(- u^2 - y^2/4)

a*abs(t) := fourier(x, t, y):
-(2*a)/y^2
*/

/*
output:
	* an array of complex numbers -- one freq per index / bin
	* magnitude of each complex / bin says how strong that freq is
	* each index corresponds to a frequency
	> nyquist

	FFT converts time samples into frequency bins
	(samples/time)[] -> (freq+magnitude)[]
	
	so using FFT one can figure out which specific frequencies are over/under
	powered and one can then apply EQ correctly or other effects to get the
	desired effects from the program.


	IFFT == X(n) = (1/N) * (N-1)Sigma(k=0){ X(k) * e^(i * 2 * pi * n * (/n)) }

	X(k) == freq. domain samples
	X(n) == time  domain samples

	N == FFT Size
	k == 0..N-1
*/

/*
for 4096 samples
* dft: 4096^2 ~= 1.7 * 10^7 complex multiplications
* fft: 2 * 4096 * log_2(4096) = 8192 * 12 ~= 9.8 * 10^4 multiplications
*/

// * https://www.mathworks.com/help/matlab/ref/fft.html
#define SAMPLE_FREQ	1000
#define SIZE		2048
int main(void) {
	complex input[SIZE] = { 0 };
	complex output[SIZE] = { 0 };

	for(int i = 0; i < SIZE; i++) {
		double t = i * (1.0 / (double)SAMPLE_FREQ);
		double s = 0.8 + 0.7 * sin(2*PI*50*t) + sin(2*PI*120*t);
		// s += sin(2*PI*TAU*t);

		// corrupt signal
		s *= (rand() % sizeof(s));

		input[i] = s;
        }

#if 0
	printf("Signal Corrupted with Zero-Mean Random Noise\n");
	printf("%i\n", SAMPLE_FREQ);
	printf("%i\n", SIZE);

	for(int i = 0; i < SIZE; i++) {
		printf("%f\n", creal(input[i]));
	}
#else
	memcpy(output, input, sizeof(complex) * SIZE);
	fft(output, SIZE);

	printf("Single-Sided Amplitude Spectrum of X(t)\n");
	printf("%i\n", SAMPLE_FREQ);
	printf("%i\n", SIZE);

	double magnitude;
	for(int i = 1; i < SIZE / 2; i++) {
		magnitude = csqrt(output[i]);
		printf("%f\n", magnitude);
	}
#endif

	return 0;
}
