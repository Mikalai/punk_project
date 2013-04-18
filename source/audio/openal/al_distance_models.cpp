#ifdef USE_OPENAL

#include "al_distance_models.h"

namespace Audio
{
	ALint DistanceModelToOpenALDistanceModel(DistanceModel value)
	{
		switch (value)
		{
		case Audio::DistanceModel::NONE:
			return AL_NONE;
		case Audio::DistanceModel::INVERSE_DISTANCE:
			return AL_INVERSE_DISTANCE;
		case Audio::DistanceModel::INVERSE_DISTANCE_CLAMPED:
			return AL_INVERSE_DISTANCE_CLAMPED;
		case Audio::DistanceModel::LINEAR_DISTANCE:
			return AL_LINEAR_DISTANCE;
		case Audio::DistanceModel::LINEAR_DISTANCE_CLAMPED:
			return AL_LINEAR_DISTANCE_CLAMPED;
		case Audio::DistanceModel::EXPONENT_DISTANCE:
			return AL_EXPONENT_DISTANCE;
		case Audio::DistanceModel::EXPONENT_DISTANCE_CLAMPED:
			return AL_EXPONENT_DISTANCE_CLAMPED;
		default:
			throw System::PunkException(L"Bad distance model requested");
		}
	}

	DistanceModel OpenALDistanceModelToDistanceModel(ALenum value)
	{
		switch (value)
		{
		case AL_NONE:
			return Audio::DistanceModel::NONE;
		case AL_INVERSE_DISTANCE:
			return Audio::DistanceModel::INVERSE_DISTANCE;
		case AL_INVERSE_DISTANCE_CLAMPED:
			return Audio::DistanceModel::INVERSE_DISTANCE_CLAMPED;
		case AL_LINEAR_DISTANCE:
			return Audio::DistanceModel::LINEAR_DISTANCE;
		case AL_LINEAR_DISTANCE_CLAMPED:
			return Audio::DistanceModel::LINEAR_DISTANCE_CLAMPED;
		case AL_EXPONENT_DISTANCE:
			return Audio::DistanceModel::EXPONENT_DISTANCE;
		case AL_EXPONENT_DISTANCE_CLAMPED:
			return Audio::DistanceModel::EXPONENT_DISTANCE_CLAMPED;
		default:
			throw System::PunkException(L"Bad distance model requested");
		}
	}
}

#endif // USE_OPENAL
