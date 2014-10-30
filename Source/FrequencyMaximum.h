#include "stdafx.h"

// FrequencyMaximum
// ---
// Data object which is used to store information about spectrally significant
// points of data. This object keeps track of continuous segments of frequency
// that are significantly above the noise floor, dynamic or otherwise.

class FrequencyMaximum
{
public:
    // Constructors / Destructors
    FrequencyMaximum();

    // Private Member Getters
    double getMaximum();
    double getAmplitude();

    // Private Member Setters
    void setMaximum(double newMaximum_);
    void setAmplitude(double newAmplitude_);

private:
    double maximum_, amplitude_;
    double* bounds_;
};