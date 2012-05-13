#ifndef _H_PUNK_UTILITY_TRACK_POS
#define _H_PUNK_UTILITY_TRACK_POS

#include <vector>
#include <algorithm>

namespace Math { template<class T> class Vector3; }

namespace Utility
{
	class TrackPos
	{
		typedef float Time;
		bool m_is_looping;
		typedef std::vector<std::pair<Time, Math::Vector3<float>>> Type;
		Type m_keys;
	public:

		void AddKey(float time, const Math::Vector3<float>& pos);
		const Math::Vector3<float> GetKey(float time);
	};
}

#endif