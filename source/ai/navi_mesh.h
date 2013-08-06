#ifndef _H_PUNK_AI_NAVI_MESH
#define _H_PUNK_AI_NAVI_MESH

#include "../config.h"
#include "../system/aop/aop.h"
#include "../system/object.h"
#include "../math/mat4.h"
#include "../math/vec3.h"

namespace System { class string; }

namespace AI
{
    class PUNK_ENGINE_API NaviMesh : public System::Object
	{
	public:
        typedef std::vector<Math::vec3> Points;
        typedef std::vector<Math::vec3> Normals;
        typedef std::vector<Math::ivec3> Faces;
    public:
        NaviMesh();
        NaviMesh(const NaviMesh&) = delete;
        NaviMesh& operator = (const NaviMesh&) = delete;
        virtual ~NaviMesh();

        void SetTransform(const Math::mat4& value);
        const Math::mat4& GetTranform() const;

		static NaviMesh* CreateFromFile(const System::string& path);

        const Math::vec3& GetPoint(int index) const;

        void SetPoints(const Points& value);
        void SetNormals(const Normals& value);
        void SetFaces(const Faces& value);

        const Points& GetPoints() const;
        const Faces& GetFaces() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

	private:
        System::string m_name;
		Math::mat4 m_transfrom;
        Points m_points;
        Normals m_normals;
        Faces m_faces;

        PUNK_OBJECT(NaviMesh)
	};


}

#endif	//	_H_PUNK_AI_NAVI_MESH
