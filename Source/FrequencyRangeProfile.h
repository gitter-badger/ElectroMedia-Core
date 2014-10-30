#include "stdafx.h"
#include "SignalProcessingAlgorithms.h"

class FrequencyRangeProfile
{
public:
    // Constructors and Destructors
    FrequencyRangeProfile();
    FrequencyRangeProfile(SignalProcessingAlgorithm processor);
    ~FrequencyRangeProfile();

    // Setters
    void setProcessor(SignalProcessingAlgorithm& processor);
    void setIndexBounds(int lower, int upper, int adjustmentType);
    void setFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType);
    void initializeFrequencyBounds(double lowerFrequency, double upperFrequency, int adjustmentType);

    // Convert To Bits function; returns the output of whichever processor is tied to this FRP
    std::string convertToBits(double* dataToConvert, int noiseFloor);

protected:
    // Variables for derived classes
    int lowerBound_, upperBound_, bits_;

private:
    // Format (bounds). Adjusts the frequency boundaries according to byte/frequency rules
    void format(double* lowerFrequency, double* upperFrequency, int adjustmentType);
	double formatChangeLower(double upperFrequency, double resolution);
	double formatChangeUpper(double lowerFrequency, double resolution);
	double* formatCenter(double lowerFrequency, double upperFrequency, double resolution);

    // Private Variables
    SignalProcessingAlgorithm* processor_;
    std::string name_;
};