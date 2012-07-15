#include <memory>
#include "utility_tree.h"

namespace Utility
{
	void Tree::MakeFromScene(Scene& scene)
	{
		int level = 0;
		while (1)
		{
			if (level == 10)
				level = level;
			try
			{			
				System::string name = System::string::Format(L"trunk_%d", level);
				std::auto_ptr<StaticMesh> mesh1(scene.CookStaticMesh(name));
				if (mesh1.get())
				{				
					name = System::string::Format(L"top_leaves_%d", level);
					std::auto_ptr<StaticMesh> mesh2(scene.CookStaticMesh(name));
					if (mesh2.get())
					{
						name = System::string::Format(L"bottom_leaves_%d", level);
						std::auto_ptr<StaticMesh> mesh3(scene.CookStaticMesh(name));
						if (mesh3.get())
						{
							m_trunks.PushLod(mesh1.release());
							m_top_leaves.PushLod(mesh2.release());
							m_bottom_leaves.PushLod(mesh3.release());
						}
					}
				}
			}
			catch(...)
			{
				throw;
			}		
			level++;
			if (level > 10)
				return;
		}
	}

	void Tree::Save(std::ostream& stream)
	{
		m_trunks.Save(stream);
		m_top_leaves.Save(stream);
		m_bottom_leaves.Save(stream);
	}

	void Tree::Load(std::istream& stream)
	{
		m_trunks.Load(stream);
		m_top_leaves.Load(stream);
		m_bottom_leaves.Load(stream);
	}
}