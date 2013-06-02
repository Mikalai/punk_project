#ifndef _H_PUNK_AUDIO_SOURCE
#define _H_PUNK_AUDIO_SOURCE

#include "../config.h"
#include "resource.h"

namespace Math { class vec3; }

namespace Audio
{
	class Buffer;
	
	struct SourceImpl;

	class PUNK_ENGINE_API Source
	{
	public:
		Source();
		virtual ~Source();

		SourceImpl* impl;

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
		void SetPosition(float x, float y, float z);
		void SetPosition(const Math::vec3& value);
		const Math::vec3 GetPosition() const;
		void SetVelocity(float x, float y, float z);
		void SetVelocity(const Math::vec3& value);
		const Math::vec3 GetVelocity() const;
		void SetDirection(float x, float y, float z);
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

		/**
		*	Source should not be playing or paused
		*/
		void SetBuffer(Buffer* value);
		void EnqueBuffer(Buffer* value);

	private:
		Source(const Source&);
		Source(const Source&&);
		Source& operator = (const Source&);
		Source& operator = (const Source&&);
	};
}

#endif