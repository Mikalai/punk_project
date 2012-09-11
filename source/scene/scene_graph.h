#ifndef _H_PUNK_SCENE_GRAPH
#define _H_PUNK_SCENE_GRAPH

#include "config.h"
#include <memory>

namespace System
{
	class string;
	class Buffer;
	class Descriptor;
}

namespace Scene
{
	class Visitor;

	/*! This class is supposed to contain the whole whole world. But instead of holding 
		object instances themselves it contains only their handlers. While in game process
		supposed to be happaned different events. To keep this graph up-to-date objects
		must inform it by sending events of special type. Through the build in mechanism of sending
		and subscribing events this event will be delivered to scene graph if it was subscribed.
		Than for response it will change himself.
		This structure can be used for searching of objects in the world. Requesting list of all objects
		in some region. To render scene. And some other staff maybe.
	*/
	class  LIB_SCENE SceneGraph
	{
		static std::auto_ptr<SceneGraph> m_instance;
		struct SceneGraphImpl;
		std::auto_ptr<SceneGraphImpl> impl_sg;

		SceneGraph();
		SceneGraph(const SceneGraph& graph);
		SceneGraph& operator = (const SceneGraph& graph);		
	public:

		void Visit(Visitor* visitor);

		void Add(const System::Descriptor& parent, const System::Descriptor& child);		
		bool Is_a_Parent_of_b(const System::Descriptor& a, const System::Descriptor& b);
		bool Is_a_Child_of_b(const System::Descriptor& a, const System::Descriptor& b);
		void RemoveChunk(const System::Descriptor& a);

		void Save(System::Buffer& buffer) const;
		void Load(System::Buffer& buffer);

		static SceneGraph* Instance();
		static void Destroy();
		
		~SceneGraph();
	};
}

#endif