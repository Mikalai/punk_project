#ifndef H_PUNK_HANDLER
#define H_PUNK_HANDLER

#include "../config.h"

namespace System
{
	class LIB_SYSTEM Descriptor
	{
		union
		{
			struct
			{
				unsigned int m_object_instance_number;
				unsigned int m_object_type_code;
			};
			unsigned __int64 m_id;
		};

	public:
		explicit Descriptor(unsigned __int64 code) throw();
		Descriptor() : m_id(0) {}
		Descriptor(unsigned type, unsigned number) throw();
		Descriptor(const Descriptor& handler) throw();
		Descriptor& operator = (const Descriptor& handler) throw();
		operator unsigned __int64 () const;
		unsigned Type() const;
		unsigned Number() const;
		unsigned __int64 Id() const;

		void SetType(unsigned type);
		void SetNumber(unsigned number);
		void SetID(unsigned __int64 id);

		bool operator == (const Descriptor& handler) const;

		static const Descriptor Null()
		{
			return Descriptor(0,0);
		}
	};
}

#endif // HANDLER_H
