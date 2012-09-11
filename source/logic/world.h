#ifndef _H_PUNK_LOGIC_WORLD
#define _H_PUNK_LOGIC_WORLD

namespace System
{
	class string;
	class ID;
	class Buffer;
}

namespace Logic
{
	class FindItem;
	class FindRoute;	

	class World
	{
	public:

		template<class Functor>
		void Apply(Functor& f) { f(this); }

		const System::string ToString() const;
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);
	};
}

#endif