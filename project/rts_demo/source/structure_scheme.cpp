#include "structure_scheme.h"

void StructureScheme::Add(Structure* instance)
{
	m_instances.push_back(instance);
}

void StructureScheme::Clear()
{
	for (auto o : m_instances)
	{
		delete o;
	}
	m_instances.clear();
}
