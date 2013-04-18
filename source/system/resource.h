//#ifndef _H_RESOURCE
//#define _H_RESOURCE
//
//#include <sstream>
//#include <fstream>
//#include "timer.h"
//
//namespace System
//{
//
//	template<class T>
//	class Resource
//	{
//		__int64 m_code;
//		__int64 m_last_access;
//		bool m_unloaded;
//		T* m_resource;
//	public:
//		Resource(T* resoruce) : m_resource(resoruce), m_unloaded(false), m_code(0), m_last_access(0) {}
//		virtual void Unload()
//		{
//			std::stringstream s;
//			std::string type = typeid(T).name();
//			for (std::string::iterator it = type.begin(); it != type.end(); ++it)
//			{
//				if ((*it) != ' ' && (*it) != ':')
//					s << *it;
//			}
//			s << '_';
//			s << m_code;
//			std::string filename = s.str();
//			std::ofstream stream(filename, std::ios_base::binary);
//			m_resource->Save(stream);
//			m_unloaded = true;
//		}
//
//		virtual void Reload()
//		{
//			std::stringstream s;
//			std::string type = typeid(T).name();
//			for (std::string::iterator it = type.begin(); it != type.end(); ++it)
//			{
//				if ((*it) != ' ' && (*it) != ':')
//					s << *it;
//			}
//			s << "_" << m_code;
//			std::ifstream stream(s.str(), std::ios_base::binary);
//			m_resource->Load(stream);
//			m_unloaded = false;
//		}
//
//		virtual bool WasAccessedLately() { return Timer::GetGlobalTimer()->GetCurrentSystemTimeUS() - m_last_access < 60000; }
//		virtual void SetCode(__int64 code) { m_code = code; }
//		virtual __int64 GetCode() { return m_code; }
//
//		operator T* ()
//		{
//			//std::cout << __FUNCSIG__ << std::endl;
//			return m_resource;
//		}
//
//		virtual T* operator -> ()
//		{
//			//std::cout << __FUNCSIG__ << std::endl;
//			m_last_access = Timer::GetGlobalTimer()->GetCurrentSystemTimeUS();
//			if (m_unloaded)
//				Reload();
//			return m_resource;
//		}
//
//		virtual void Clean()
//		{
//			delete m_resource;
//		}
//
//		virtual ~Resource() {};
//	};
//
//}
//#endif
