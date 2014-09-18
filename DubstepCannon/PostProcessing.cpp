#include "stdafx.h"
#include "PostProcessing.h"

//==================

FrequencyMaximum* AnalyzeBand(double* data, int windowWidth, double* frequencyBand, int numMaxima)
{
	FrequencyMaximum* maxima = (FrequencyMaximum *)malloc(sizeof(FrequencyMaximum) * numMaxima);

	// Convert the frequencyBand parameter into integer boundaries
	int lowerBound = convertFrequencyToInt(frequencyBand[0]);
	int upperBound = convertFrequencyToInt(frequencyBand[1]);
	if(upperBound <= lowerBound || upperBound <= 0)
	{
		cout << "ERROR: Cannot interpret non-real frequency bounds." << endl;
		free(maxima);
		return NULL;
	}
	
	// Ascertain the value of the noise floor
	int dynamicNoiseFloor = calculateDynamicNoiseFloor(data,lowerBound,upperBound);

	// Determine the X number of maxima
	int numberOfMaxima = 3, 
		maximumCount = 0;
	std::vector<int> bufferedFrequencies(numberOfMaxima);
	for(int i=(lowerBound<0 ? 0 : lowerBound); i < upperBound; i++)
	{
		// Flatten Noise Floor if applicable
		bufferedFrequencies.at(numberOfMaxima-1) = (data[i] > dynamicNoiseFloor) ? data[i] : 0;

		if(bufferedFrequencies.at(1) > dynamicNoiseFloor && bufferedFrequencies.at(1) > bufferedFrequencies.at(0) && bufferedFrequencies.at(1) > bufferedFrequencies.at(numberOfMaxima))
		{
			maxima[maximumCount].setAmplitude(data[i-1]);		// Take the middle datapoint
			maxima[maximumCount].setMaximum(convertIntToFrequency(i-1)); // Convert from (unitless freq) to Hz 
			
			// Figure out if we've reached the maximum number of maxima
			if(++maximumCount == numMaxima) break;
		}

		// Rotate the vector to the left so we can reinsert at the end
		rotate(bufferedFrequencies.begin(), bufferedFrequencies.begin() + 1, bufferedFrequencies.end());
	}

	return maxima;
}

double calculateIntensity(double* data, double* frequencyBand)
{
	double intensity = 0;
	int dynamicNoiseFloor = calculateDynamicNoiseFloor(data, 0, convertFrequencyToInt(MAXIMUM_FREQUENCY_ACCOUNTED));

	for(int i=frequencyBand[0]; i<frequencyBand[1]; i++)
	{
		intensity += (data[i] > dynamicNoiseFloor) ? log10((7.33+10.9*i)*data[i]) : 0;
	}

	return intensity;
}

char* MaximumtoString(double maximum)
{
	return "Oops";
}

// I don't think this function does what I think it does...
double* ToByte(double* data, double* frequencyBand, int numBytes)
{
	// Allocate memory for our array of doubles
	double* bin = (double*)malloc(sizeof(double)*8*numBytes);
	
	// Convert the frequencyBand parameter into integer boundaries
	int lowerIndex = convertFrequencyToInt(frequencyBand[0]);
	int upperIndex = convertFrequencyToInt(frequencyBand[1]);
	if(upperIndex <= lowerIndex || upperIndex <= 0)
	{
		cout << "ERROR: Cannot interpret non-real frequency bounds." << endl;
		free(bin);
		return NULL;
	}

	// Ascertain the value of the noise floor
	int dynamicNoiseFloor = calculateDynamicNoiseFloor(data,lowerIndex,upperIndex);
	int count = 0;
	int binSize = (upperIndex - lowerIndex) / (8*numBytes);

	// What does this do?
	for(int i=lowerIndex; i<upperIndex; i += binSize)
	{
		double localizedAmplitude = 0;
		for(int j=i; j<(i+binSize); j++)
		{
			localizedAmplitude += double( data[j] > dynamicNoiseFloor ? data[j] : 0 );
		}
		bin[count++] = double(localizedAmplitude / binSize);
	}

	double maximum = -1;
	for(int i=0;i<8*numBytes;i++)
	{
		maximum = (bin[i] > maximum ? bin[i] : maximum);
	}

	for(int i=0;i<8*numBytes;i++)
	{
		bin[i] = (bin[i] / maximum > 0.5); // Why 0.5?
	}

	// Why am I returning an array of doubles? Would it not be better to return ints as either 0 or 1?
	return bin;
}