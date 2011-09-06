#ifndef _MATERIAL
#define _MATERIAL

#include "../PunkEngine/common/IMaterial.h"
#include "../Util/Util.h"

class TMaterial : public IMaterial
{
public:
	TMaterial();
	TMaterial(const TMaterial& material);
	TMaterial& operator = (const TMaterial& material);
	virtual ~TMaterial();

	virtual float* GetAmbient();
	virtual float* GetDiffuse();
	virtual float* GetSpecular();
	virtual float GetShine() const;
	virtual float GetShineStrength() const;
	virtual float GetTransparency() const;
	virtual void SetAmbient(float r, float g, float b, float a);
	virtual void SetDiffuse(float r, float g, float b, float a);
	virtual void SetSpecular(float r, float g, float b, float a);
	virtual void SetShine(float shine);
	virtual void SetShineStrength(float shineStrength);
	virtual void SetTransparency(float transparency);

	virtual int GetSubMaterialsCount() const;
	virtual TMaterial* GetSubMaterials();

	virtual void Apply();
private:
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_shine;
	float m_shineStrength;
	float m_transparency;

	int m_subMaterialCount;
	TMaterial* m_subMaterial;

	friend class TMesh;
};

#endif