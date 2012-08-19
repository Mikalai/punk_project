#ifndef _H_PUNK_UTILITY_TRACK
#define _H_PUNK_UTILITY_TRACK

#include <ostream>
#include <istream>
#include <vector>
#include <algorithm>
#include "../../math/interpolation.h"
#include "../../math/quat.h"

namespace Utility
{
	template<class T>
	class AnimationTrack
	{
		typedef int Frame;
		typedef std::vector<std::pair<Frame, T>> Type;
		Type m_keys;
		bool m_is_looping;
	public:
		void AddKey(int frame, const T& pos);
		const T GetKey(float frame);
		bool HasKeyAt(int frame);
		T& GetOriginalKey(int frame, bool& flag);
		const T& GetOriginalKey(int frame, bool& flag) const;
		void SetLooping(bool flag) { m_is_looping = flag; }
		bool IsLooping() const { return m_is_looping; }
		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};

	template<class T>
	inline T& AnimationTrack<T>::GetOriginalKey(int frame, bool& value)
	{
		return const_cast<T&>(static_cast<const AnimationTrack<T>&>(*this).GetOriginalKey(frame, value));
	}

	template<class T>
	inline const T& AnimationTrack<T>::GetOriginalKey(int frame, bool& flag) const
	{
		for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
		{
			if (frame == it->first)
			{				
				flag = true;
				return it->second;
			}
		}
		flag = false;
		return m_keys.begin()->second;
	}

	template<class T>
	inline bool AnimationTrack<T>::HasKeyAt(int frame)
	{
		for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
		{
			if (it->first == frame)
				return true;
		}
		return false;
	}

	template<class T>
	inline void AnimationTrack<T>::AddKey(int frame, const T& v)
	{
		std::pair<Frame, T> p(frame, v);
		m_keys.push_back(p);
		/*auto it = m_keys.begin();
		for (; it != m_keys.end(); ++it)
		{
			if (p.first  it->first)
				break;
		}
		m_keys.insert(it, p);*/
	}

	template<class T>
	inline const T AnimationTrack<T>::GetKey(float frame)
	{
		// parameter check
		if (frame < (float)(*m_keys.begin()).first)
		{			
			frame = (float)(*m_keys.begin()).first;
		}

		if (m_keys.empty())
			return T();

		if (m_keys.size() == 1)
			return (*m_keys.begin()).second;

		while (frame > m_keys.back().first)
			frame -= m_keys.back().first;

		auto it1 = m_keys.begin();
		auto it2 = m_keys.begin();
		for (; it1 != m_keys.end() && frame >= (float)it1->first; ++it1);
		it2 = it1;
		--it1;
		if (it2 == m_keys.end())
			it2 = m_keys.begin();

		const T& p1 = it1->second;
		const T& p2 = it2->second;

		const T res = Math::linear_interpolation(p1, p2, (frame - it1->first) / (float)(it2->first - it1->first));
		return res;
	}

	template<>
	inline const Math::Quaternion<float> AnimationTrack<Math::Quaternion<float>>::GetKey(float frame)
	{
				// parameter check
		if (frame < (*m_keys.begin()).first)
		{			
			frame = (*m_keys.begin()).first;
		}
		if (m_keys.empty())
			return Math::Quaternion<float>();

		if (m_keys.size() == 1)
			return (*m_keys.begin()).second;

		while (frame > m_keys.back().first)
			frame -= m_keys.back().first;

		auto it1 = m_keys.begin();
		auto it2 = m_keys.begin();
		for (; it1 != m_keys.end() && frame >= (float)it1->first; ++it1);
		it2 = it1;
		--it1;
		
		if (it2 == m_keys.end())
			if (m_is_looping)
				it2 = m_keys.begin();
			else
				it2 = it1;

		const Math::Quaternion<float>& p1 = it1->second;
		const Math::Quaternion<float>& p2 = it2->second;

		const Math::Quaternion<float> res = Math::spherical_linear_interpolation(p1, p2, (frame - it1->first) / (float)(it2->first - it1->first));
		return res;
	}	

	template<class T>
	inline void AnimationTrack<T>::Save(std::ostream& stream)
	{
		int frame_count = m_keys.size();
		stream.write(reinterpret_cast<const char*>(&frame_count), sizeof(frame_count));
		if (frame_count)
		{
			stream.write(reinterpret_cast<const char*>(&m_keys[0]), m_keys.size()*sizeof(std::pair<Frame, T>));
			stream.write(reinterpret_cast<const char*>(&m_is_looping), sizeof(m_is_looping));
		}
	}

	template<class T>
	inline void AnimationTrack<T>::Load(std::istream& stream)
	{
		int frame_count = 0;
		stream.read(reinterpret_cast<char*>(&frame_count), sizeof(frame_count));
		if (frame_count)
		{
			m_keys.resize(frame_count);
			stream.read(reinterpret_cast<char*>(&m_keys[0]), m_keys.size()*sizeof(std::pair<Frame, T>));
			stream.read(reinterpret_cast<char*>(&m_is_looping), sizeof(m_is_looping));
		}
	}
}

#endif