//#ifndef _H_CODE
//#define _H_CODE
//
//#include <ostream>
//
//namespace Logic
//{
//	struct ID
//	{
//		union
//		{
//			char m_name[8];
//			__int64 m_code;
//		};
//
//		ID()
//			: m_code(0)
//		{}
//
//		ID(const char* m)
//		{
//			memset(m_name, 0, 8);
//			const char* src = m;
//			char* dst = m_name;
//			int count = 8;
//			while (*src && --count)
//			{
//				*dst = *src;
//				dst++;
//				src++;
//			}
//		}
//
//		operator __int64 () const
//		{
//			return m_code;
//		}
//
//		bool operator == (const ID& id) const
//		{
//			return m_code == id.m_code;
//		}
//
//		bool operator < (const ID& id) const
//		{
//			return m_code < id.m_code;
//		}
//
//		bool operator > (const ID& id) const
//		{
//			return m_code > id.m_code;
//		}
//
//		bool operator <= (const ID& id) const
//		{
//			return m_code <= id.m_code;
//		}
//
//		bool operator >= (const ID& id) const
//		{
//			return m_code >= id.m_code;
//		}
//	};
//
//	inline std::ostream& operator << (std::ostream& stream, const ID& id)
//	{
//		for (int i = 0; i < 8; ++i)
//		{
//			stream << id.m_name[i];
//		}
//		return stream;
//	}
//}
//
//#endif
