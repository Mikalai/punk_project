#ifndef _H_PUNK_MATH_OCT_TREE
#define _H_PUNK_MATH_OCT_TREE

#include <vector>
#include <memory>
#include <iosfwd>

#include "../config.h"
#include "aabb.h"

namespace Math
{
	class Line3D;

	class PUNK_ENGINE_PUBLIC OctTree
	{
	public:
		typedef std::vector<ivec3> FaceList;
		typedef std::vector<vec3> VertexList;
	private:
		static const int MaxFaceCount = 8;
		static const int MaxDepth = 20;
        OctTree* m_parent;
        AxisAlignedBox m_bbox;
        int m_face_count;
        bool m_is_finale;
		int m_cur_depth;
		std::unique_ptr<OctTree> m_right_front_up;
		std::unique_ptr<OctTree> m_right_front_down;
		std::unique_ptr<OctTree> m_right_back_up;
		std::unique_ptr<OctTree> m_right_back_down;
		std::unique_ptr<OctTree> m_left_front_up;
		std::unique_ptr<OctTree> m_left_front_down;
		std::unique_ptr<OctTree> m_left_back_up;
		std::unique_ptr<OctTree> m_left_back_down;						
		FaceList m_face_list;
		//VertexList vertexList;		

	public:
		OctTree(OctTree* parent = 0);
		OctTree(const OctTree& tree);
		void SetData(const FaceList& fl, const VertexList& vl);
		OctTree* Build(const FaceList& fl, const VertexList& vertexList);
		FaceList Cross(const Line3D& line);
		FaceList CrossAll(const Line3D& line) const;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
	};
}

#endif
