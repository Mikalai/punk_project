#ifndef H_PUNK_HANDLER
#define H_PUNK_HANDLER

namespace System
{
	class Handler
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
		explicit Handler(unsigned __int64 code) throw();
		Handler() : m_id(0) {}
		Handler(unsigned type, unsigned number) throw();
		Handler(const Handler& handler) throw();
		Handler& operator = (const Handler& handler) throw();
		operator unsigned __int64 () const;
		unsigned Type() const;
		unsigned Number() const;
		unsigned __int64 Id() const;

		void SetType(unsigned type);
		void SetNumber(unsigned number);
		void SetID(unsigned __int64 id);

		bool operator == (const Handler& handler) const;

		static const Handler Null()
		{
			return Handler(0,0);
		}
	};

	template<class T, unsigned U>
	class HandlerSetter
	{
		static unsigned g_next_instance_number;
		Handler m_handler;

	protected:

		HandlerSetter() : m_handler(U, g_next_instance_number++) {}
		HandlerSetter(const HandlerSetter& h) : m_handler(h.m_handler) {}
		HandlerSetter(const T& h) : m_handler(h.GetHandler()) {}

		HandlerSetter& operator = (const HandlerSetter& h)
		{
			if (this != &h)
			{
				m_handler = h.m_handler;
			}
			return *this;
		}

	public:

		Handler GetHandler() const
		{
			return m_handler;
		}

	};

	template<class T, unsigned U> unsigned HandlerSetter<T, U>::g_next_instance_number = 1;
}

#endif // HANDLER_H
