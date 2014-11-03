#include "stdafx.h"
#include "FrequencyMaximum.h"

FrequencyMaximum::FrequencyMaximum()
    : maximum_(0), amplitude_(0), bounds_()
{}

double FrequencyMaximum::getMaximum()
{
    return maximum_;
}

void FrequencyMaximum::setMaximum(double newMaximum_)
{
    maximum_ = newMaximum_;
}

double FrequencyMaximum::getAmplitude()
{
    return amplitude_;
}

void FrequencyMaximum::setAmplitude(double newAmplitude_)
{
    amplitude_ = newAmplitude_;
}