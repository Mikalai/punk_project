#include <memory>
#include "light.h"
#include "light_set.h"

namespace Virtual
{
	const Light* LightSet::GetLight(int index) const
	{
		return As<const Light*>(Find(index));
	}

	Light* LightSet::GetLight(int index)
	{
		return As<Light*>(Find(index));
	}

	bool LightSet::Save(std::ostream& stream) const
	{
		Object::Save(stream);
		return true;
	}

	bool LightSet::Load(std::istream& stream)
	{
		Object::Load(stream);			
		return true;
	}

	LightSet* LightSet::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<LightSet> res(new LightSet);
		res->Load(stream);
		return res.release();
	}

}