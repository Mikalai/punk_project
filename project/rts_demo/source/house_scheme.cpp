#include "../../../source/punk_engine.h"
#include "house.h"
#include "house_scheme.h"

static const System::string MODEL_NAME(L"cube.static");
static const System::string MODEL_MATERIAL("diffuse.material");

HouseScheme::HouseScheme()
{
	Virtual::Geometry* geometry = Cast<Virtual::Geometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + MODEL_NAME));
	Virtual::Material* material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + MODEL_MATERIAL));

	m_final_geometry.push_back(geometry);
	m_material = material;
	m_max_capacity = 4;
}

Structure* HouseScheme::CreateNewStruture()
{
	House* house = new House(this);
	Add(house);
	return house;
}