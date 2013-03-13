#include "house_scheme.h"

static const System::string MODEL_NAME(L"zombie_house.static");
static const System::string MODEL_MATERIAL("zombie_house.material");

HouseScheme::HouseScheme()
{
	Virtual::Geometry* geometry = Cast<Virtual::Geometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + MODEL_NAME));
	Virtual::Material* material = Cast<Virtual::Material*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + MODEL_MATERIAL));

	m_final_geometry.push_back(geometry);
	m_material = material;
	m_max_capacity = 4;
}