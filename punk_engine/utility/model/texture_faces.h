#ifndef _H_PUNK_UTILITY
#define _H_PUNK_UTILITY

#include <map>
#include "../../system/string.h"

namespace Utility
{
	class TextureFace
	{
		Math::vec2 v[4];
	public:
		const Math::vec2& operator[] (int index) const
		{
			return v[index];
		}
		Math::vec2& operator[] (int index)
		{
			return v[index];
		}
	};

	class TextureMesh
	{
		System::string m_name;
		std::vector<TextureFace> m_coords;
	public:
		void SetName(const System::string& name)
		{
			m_name = name;
		}

		const System::string& GetName() const
		{
			return m_name;
		}
		TextureFace& operator [] (int index)
		{
			return m_coords[index];
		}
		const TextureFace& operator [] (int index) const
		{
			return m_coords[index];
		}
		unsigned size() const
		{
			return m_coords.size();
		}
		void push_back(const TextureFace& coord)
		{
			m_coords.push_back(coord);
		}
	};

	class TextureMeshes
	{
		static const int MAX_TEXTURE_MESHES = 8;
		std::auto_ptr<TextureMesh> m_mesh[MAX_TEXTURE_MESHES];
	public:
		TextureMeshes()
		{
			for (int i = 0; i < MAX_TEXTURE_MESHES; ++i)
				m_mesh[i].reset(new TextureMesh());
		}
		TextureMeshes(const TextureMeshes& meshes)
		{
			for (int i = 0; i < MAX_TEXTURE_MESHES; ++i)
				m_mesh[i].reset(new TextureMesh(*meshes.m_mesh[i]));
		}

		TextureMesh& operator [] (unsigned index)
		{
			return *m_mesh[index];
		}
		const TextureMesh& operator [] (unsigned index) const
		{
			return *m_mesh[index];
		}
		unsigned size()
		{
			return MAX_TEXTURE_MESHES;
		}
		TextureMesh* FindEmpty()
		{
			for (int i = 0; i < MAX_TEXTURE_MESHES; ++i)
				if (m_mesh[i]->size() == 0)
					return m_mesh[i].get();
		}
	};

	/*
	class TextureFaces
	{
		typedef std::map<System::string, TextureFace> type;
		typedef type::iterator iterator;
		typedef type::const_iterator const_iterator;
		type m_faces;
	public:

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		unsigned size() const;
		bool empty();
		iterator find(const System::string& texture_name);
		const_iterator find(const System::string& texture_name) const;
	};*/
}

#endif