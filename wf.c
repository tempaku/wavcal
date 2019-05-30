void Hamming( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
        data[i] = data[i]*(0.54 - 0.46 * cos(2*rate));	
	}
}
void Hanning( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
        data[i] = data[i]*(0.5 - 0.5 * cos(2*rate));	
	}
}

void BlackmanHarris( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
		data[i] = data[i]*(0.35875F - 0.48829F * cos(2.0F*rate) + 0.14128F * cos(4.0F*rate) - 0.01168F * cos(6.0F*rate));
	}
}

