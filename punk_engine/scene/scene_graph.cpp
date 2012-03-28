#include "scene_graph.h"
#include "scene_events.h"
#include "../system/buffer.h"
#include <vector>
#include <set>
#include <map>
#include <algorithm>

namespace Scene
{
	std::auto_ptr<SceneGraph> SceneGraph::m_instance;

	struct SceneGraph::SceneGraphImpl
	{
		typedef std::multimap<System::Descriptor, System::Descriptor> ParentToChild;		
		typedef std::map<System::Descriptor, System::Descriptor> ChildToParent;		
		ParentToChild m_parent_to_child;		// children. It can be another scene graph or a simple object
		ChildToParent m_child_to_parent;
	};

	typedef std::map<System::Descriptor, System::Descriptor> HashTable;
	HashTable g_hash_map;	// contains information about all parents connection


	SceneGraph::SceneGraph()
	{}

	SceneGraph::~SceneGraph()
	{}

	///
	///
	///
	void SceneGraph::Add(const System::Descriptor& parent, const System::Descriptor& child)
	{
		impl_sg->m_parent_to_child.insert(std::make_pair<System::Descriptor, System::Descriptor>(parent, child));
		impl_sg->m_child_to_parent[child] = parent;
	}

	///
	///
	///
	bool SceneGraph::Is_a_Child_of_b(const System::Descriptor& a, const System::Descriptor& b)
	{
		SceneGraphImpl::ChildToParent::const_iterator i = impl_sg->m_child_to_parent.find(a);
		if (i == impl_sg->m_child_to_parent.end())
			return false;
		return i->second == b;
	}

	///
	///
	///
	bool SceneGraph::Is_a_Parent_of_b(const System::Descriptor& a, const System::Descriptor& b)
	{
		struct Finder
		{
			const System::Descriptor& m_child;
			Finder(const System::Descriptor& desc) : m_child(desc) {}
			bool operator () (const std::pair<System::Descriptor, System::Descriptor>& b)
			{
				return m_child == b.second;
			}
		};

		SceneGraphImpl::ParentToChild::const_iterator lower = impl_sg->m_parent_to_child.lower_bound(a);
		SceneGraphImpl::ParentToChild::const_iterator upper = impl_sg->m_parent_to_child.upper_bound(a);
		if (lower == upper)
			return false;		
		auto res = std::find_if(lower, upper, Finder(b));
		return res != upper;
	}

	///
	///
	///
	SceneGraph* SceneGraph::Instance()
	{
		if (!m_instance.get())
			m_instance.reset(new SceneGraph());
		return m_instance.get();			
	}

	///
	///
	///
	void SceneGraph::Destroy()
	{
		m_instance.reset(nullptr);
	}

	///
	///
	///
	void SceneGraph::RemoveChunk(const System::Descriptor& a)
	{
		struct Cleaner
		{
			SceneGraphImpl::ChildToParent& impl;
			Cleaner(SceneGraphImpl::ChildToParent& imp) : impl(imp) {}

			void operator () (const std::pair<System::Descriptor, System::Descriptor>& p)
			{
				auto j = impl.find(p.second);			
				if (j != impl.end())
					impl.erase(j);
			}
		};

		//
		//	remove from parent to child tree
		//
		{
			SceneGraphImpl::ParentToChild::iterator start = impl_sg->m_parent_to_child.lower_bound(a);
			SceneGraphImpl::ParentToChild::iterator end = impl_sg->m_parent_to_child.lower_bound(a);
			if (start != end)
			{
				std::for_each(start, end, Cleaner(impl_sg->m_child_to_parent));
				impl_sg->m_parent_to_child.erase(start, end);
			}
		}
		//
		//	remove from child to parent tree
		//
	}

	void SceneGraph::Save(System::Buffer& buffer) const
	{		
		buffer.WriteUnsigned32(impl_sg->m_parent_to_child.size());
		for (auto p = impl_sg->m_parent_to_child.begin(); p != impl_sg->m_parent_to_child.end(); ++p)
		{
			p->first.Save(buffer);
			p->second.Save(buffer);
		}
	}

	void SceneGraph::Load(System::Buffer& buffer)
	{
		impl_sg.reset(new SceneGraphImpl());
		unsigned size = buffer.ReadUnsigned32();
		for (unsigned i = 0; i < size; ++i)
		{
			std::pair<System::Descriptor, System::Descriptor> p;
			p.first.Save(buffer);
			p.second.Save(buffer);			
			impl_sg->m_parent_to_child.insert(p);
			impl_sg->m_child_to_parent[p.second] = p.first;
		}
	}
}