#ifndef _H_PUNK_AUDIO_OPENAL_SOURCE
#define _H_PUNK_AUDIO_OPENAL_SOURCE

#include "../../math/vec3.h"
#include "openal.h"
#include "al_buffer_impl.h"
#include "../audio_source.h"

namespace Audio
{
	struct SourceImpl
	{
		ALuint m_source;
		std::vector<Buffer*> m_buffers;

		SourceImpl();
		~SourceImpl();
		void SetPitch(float value);
		float GetPitch() const;
		void SetGain(float value);
		float GetGain() const;
		void SetMinGain(float value);
		float GetMinGain() const;
		void SetMaxGain(float value);
		float GetMaxGain() const;
		void SetRolloffFactor(float value);
		float GetRolloffFactor() const;
		void SetMaxDistance(float value);
		float GetMaxDistance() const;
		void SetConeOuterGain(float value);
		float GetConeOuterGain() const;
		void SetConeInnerAngle(float value);
		float GetConeInnerAngle() const;
		void SetConeOuterAngle(float value);
		float GetConeOuterAngle() const;
		void SetReferenceDistance(float value);
		float GetReferenceDistance() const;
		void SetPosition(const Math::vec3& value);
		const Math::vec3 GetPosition() const;
		void SetVelocity(const Math::vec3& value);
		const Math::vec3 GetVelocity() const;
		void SetDirection(const Math::vec3& value);
		const Math::vec3 GetDirection() const;
		void SetRelative(bool value);
		bool IsRelative() const;
		void SetLooping(bool value);
		bool IsLooping() const;
		void Play();
		bool IsPlaying() const;
		void Pause();
		bool IsPaused() const;
		void Stop();
		bool IsStopped() const;
		bool IsActive() const;
		void Reset();
		void SetBuffer(Buffer* value);
		void EnqueBuffer(Buffer* value);
	};
}

#endif	//	_H_PUNK_AUDIO_OPENAL_SOURCE