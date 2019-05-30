#include <math.h>

void wavgen( double *wav, double f, double theta, int samples )
{
	int i;
	double dt;
	double pi = 4.0f * atan( 1.0 );

	dt = 2.0f * pi * f / (double)samples;

	for ( i = 0; i < samples; i ++ ) {
		wav[i] = cos( i*dt + theta);
	}
}

 void fft(int n, double theta, double ar[], double ai[])
 {
     int m, mh, i, j, k;
     double wr, wi, xr, xi;

     for (m = n; (mh = m >> 1) >= 1; m = mh) {
         for (i = 0; i < mh; i++) {
             wr = cos(theta * i);
             wi = sin(theta * i);
             for (j = i; j < n; j += m) {
                 k = j + mh;
                 xr = ar[j] - ar[k];
                 xi = ai[j] - ai[k];
                 ar[j] += ar[k];
                 ai[j] += ai[k];
                 ar[k] = wr * xr - wi * xi;
                 ai[k] = wr * xi + wi * xr;
             }
         }
         theta *= 2;
     }
     /* ---- unscrambler ---- */
     i = 0;
     for (j = 1; j < n - 1; j++) {
         for (k = n >> 1; k > (i ^= k); k >>= 1);
         if (j < i) {
             xr = ar[j];
             xi = ai[j];
             ar[j] = ar[i];
             ai[j] = ai[i];
             ar[i] = xr;
             ai[i] = xi;
         }
     }
 }
 

void ctfft( double ar[], double ai[], int n )
{
	double pi = 4.0f * atan( 1.0 );
	double theta = 2 * pi / n * -1.0f;
	
	fft( n, theta, ar, ai );
}

void ictfft( double ar[], double ai[], int n )
{
	double pi = 4.0f * atan( 1.0 );
	double theta = 2 * pi / n;
	int i;
	
	fft( n, theta, ar, ai );
	
	for ( i = 0; i < n; i ++ ) {
		ar[i] /= n;
		ai[i] /= n;
	}
}
