#ifndef _H_PUNK_SYSTEM_SIGNAL_SLOT
#define _H_PUNK_SYSTEM_SIGNAL_SLOT

#include <iostream>
#include <vector>

namespace System
{
	template<class Dummy = void> class Slot0;

	template<> 
	class Slot0<void>
	{
	public:
		void* object;
		void* method;

		void Call()
		{
			class C {};
			C* c = (C*)object;
			void (C::*Method)();
			void** a = (void**)&Method;
			*a = method;
			(c->*Method)();
		}
	};

	template<class Arg1>
	class Slot1
	{
	public:
		void* object;
		void* method;

		void Call(Arg1 value)
		{
			class C {};
			C* c = (C*)object;
			void (C::*Method)(Arg1);
			void** a = (void**)&Method;
			*a = method;
			(c->*Method)(value);
		}
	};

	template<class Arg1, class Arg2>
	class Slot2
	{
	public:
		void* object;
		void* method;

		void Call(Arg1 v1, Arg2 v2)
		{
			class C {};
			C* c = (C*)object;
			void (C::*Method)(Arg1, Arg2);
			void** a = (void**)&Method;
			*a = method;
			(c->*Method)(v1, v2);
		}
	};

	template<class Arg1, class Arg2, class Arg3>
	class Slot3
	{
	public:
		void* object;
		void* method;

		void Call(Arg1 v1, Arg2 v2, Arg3 v3)
		{
			class C {};
			C* c = (C*)object;
			void (C::*Method)(Arg1, Arg2, Arg3);
			void** a = (void**)&Method;
			*a = method;
			(c->*Method)(v1, v2, v3);
		}
	};

	template<class T> Slot0<> MakeSlot(T* object, void (T::*Method)())
	{
		Slot0<> res;
		void** ptr = (void**)&Method;
		res.object = (void*)object;
		res.method = *ptr;
		return res;
	}

	template<class T, class Arg1> Slot1<Arg1> MakeSlot(T* object, void (T::*Method)(Arg1))
	{
		Slot1<Arg1> res;
		void** ptr = (void**)&Method;
		res.object = (void*)object;
		res.method = *ptr;
		return res;
	}

	template<class T, class Arg1, class Arg2> Slot2<Arg1, Arg2> MakeSlot(T* object, void (T::*Method)(Arg1, Arg2))
	{
		Slot2<Arg1, Arg2> res;
		void** ptr = (void**)&Method;
		res.object = (void*)object;
		res.method = *ptr;
		return res;
	}

	template<class T, class Arg1, class Arg2, class Arg3> Slot3<Arg1, Arg2, Arg3> MakeSlot(T* object, void (T::*Method)(Arg1, Arg3, Arg3))
	{
		Slot3<Arg1, Arg2, Arg3> res;
		void** ptr = (void**)&Method;
		res.object = (void*)object;
		res.method = *ptr;
		return res;
	}

	template<class Dummy = void> class Signal0;

	template<>
	class Signal0<void>
	{	
		std::vector<Slot0<> > m_slots;
	public:

		void Connect(Slot0<> slot) { m_slots.push_back(slot); }

		void Emit()
		{
			for (std::vector<Slot0<> >::iterator it = m_slots.begin(); it != m_slots.end(); ++it)
			{
				(*it).Call();
			}
		}

		void operator () ()
		{
			Emit();
		}
	};

	template<class Arg1>
	class Signal1
	{
		std::vector<Slot1<Arg1> > m_slots;
	public:

		void Connect(Slot1<Arg1> slot) { m_slots.push_back(slot); }

		void Emit(Arg1 value)
		{
			for (std::vector<Slot1<Arg1> >::iterator it = m_slots.begin(); it != m_slots.end(); ++it)
			{
				(*it).Call(value);
			}
		}

		void operator () (Arg1 value)
		{
			Emit(value);
		}
	};

	template<class Arg1, class Arg2>
	class Signal2
	{
		std::vector<Slot2<Arg1, Arg2> > m_slots;
	public:

		void Connect(Slot2<Arg1, Arg2> slot) { m_slots.push_back(slot); }

		void Emit(Arg1 v1, Arg2 v2)
		{
			for (std::vector<Slot2<Arg1, Arg2> >::iterator it = m_slots.begin(); it != m_slots.end(); ++it)
			{
				(*it).Call(v1, v2);
			}
		}

		void operator () (Arg1 v1, Arg2 v2)
		{
			Emit(v1, v2);
		}
	};


	template<class Arg1, class Arg2, class Arg3>
	class Signal3
	{
		std::vector<Slot3<Arg1, Arg2, Arg3> > m_slots;
	public:

		void Connect(Slot3<Arg1, Arg2, Arg3> slot) { m_slots.push_back(slot); }

		void Emit(Arg1 v1, Arg2 v2, Arg3, v3)
		{
			for (std::vector<Slot3<Arg1, Arg2, Arg3> >::iterator it = m_slots.begin(); it != m_slots.end(); ++it)
			{
				(*it).Call(v1, v2, v3);
			}
		}

		void operator () (Arg1 v1, Arg2 v2, Arg3 v3)
		{
			Emit(v1, v2, v3);
		}
	};
}

#endif	//	_H_PUNK_SYSTEM_SIGNAL_SLOT