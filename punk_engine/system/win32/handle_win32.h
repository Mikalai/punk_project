#ifndef H_PUNK_HANDLER
#define H_PUNK_HANDLER

#include "../config.h"

namespace System
{
	class LIB_SYSTEM Handle
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
		explicit Handle(unsigned __int64 code) throw();
		Handle() : m_id(0) {}
		Handle(unsigned type, unsigned number) throw();
		Handle(const Handle& handler) throw();
		Handle& operator = (const Handle& handler) throw();
		operator unsigned __int64 () const;
		unsigned Type() const;
		unsigned Number() const;
		unsigned __int64 Id() const;

		void SetType(unsigned type);
		void SetNumber(unsigned number);
		void SetID(unsigned __int64 id);

		bool operator == (const Handle& handler) const;

		static const Handle Null()
		{
			return Handle(0,0);
		}
	};
}

#endif // HANDLER_H
