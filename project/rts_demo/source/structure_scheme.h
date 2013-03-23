#ifndef _H_STRUCTURE_SCHEME
#define _H_STRUCTURE_SCHEME

#include <vector>
//#include "../../../source/punk_engine.h"

namespace Virtual 
{
	class Geometry; 
	class Material;
}

class ResourceRequirenments;
class Structure;

class StructureScheme
{
public:
	int GetTotalJobsElements() { return m_total_jobs; }
	ResourceRequirenments* GetResourceRequirenments() { return m_requirenments; }

	void Add(Structure* instance);
	void Clear();

	Virtual::Material* GetMaterial() { return m_material; }
	std::vector<Virtual::Geometry*>& GetFinalGeometry() { return m_final_geometry; }
	std::vector<Virtual::Geometry*>& GetConstructionGeometry() { return m_construction_elements; }

	virtual Structure* CreateNewStruture() = 0;

protected:
	std::vector<Virtual::Geometry*> m_construction_elements;
	std::vector<Virtual::Geometry*> m_final_geometry;
	Virtual::Material* m_material;
	int m_total_jobs;	//	amount of working units to complete
	ResourceRequirenments* m_requirenments;

	std::vector<Structure*> m_instances;
};

#endif	//	_H_STRUCTURE_SCHEME