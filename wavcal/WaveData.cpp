#include "StdAfx.h"
#include "WaveData.h"

WaveData::WaveData(void)
{
	data = 0;
	size = 0;
}

WaveData::~WaveData(void)
{
	if ( data ) delete [] data;
}
