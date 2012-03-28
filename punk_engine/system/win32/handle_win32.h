#ifndef H_PUNK_HANDLER
#define H_PUNK_HANDLER

#include "../config.h"

namespace System
{
	class Buffer;

	class MODULE_SYSTEM Descriptor
	{
	public:
		typedef unsigned short int TypeCode;
		typedef unsigned short int RESERVED;
		typedef unsigned int InstanceNumberType;
	private:
		union
		{
			struct
			{
				TypeCode m_object_instance_number;
				RESERVED res;
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

		static const Descriptor Root()
		{
			return Descriptor(0,0);
		}

		void Save(Buffer& buffer) const;
		void Load(Buffer& buffer);
	};
}

#endif // HANDLER_H
