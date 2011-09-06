#ifndef _LIGHT
#define _LIGHT

#include "../PunkEngine/PunkEngine.h"

class TLight : public ILight
{
public:
	TLight();
	TLight(const TLight& light);
	TLight& operator = (const TLight& light);
	virtual ~TLight();

	virtual void TurnOn();
	virtual void TurnOff();

	virtual const float* GetAmbient() const;
	virtual const float* GetDiffuse() const;
	virtual const float* GetSpecular() const;
	virtual const float* GetPosition() const;
	virtual const float* GetSpotDirection() const;
	virtual float GetSpotExponent() const;
	virtual float GetSpotCutoff() const;
	virtual float GetConstantAttenuation() const;
	virtual float GetLinearAttenuation() const;
	virtual float GetQuadraticAttenuation() const;

	virtual void SetAmbient(float r, float g, float b, float a);
	virtual void SetDiffuse(float r, float g, float b, float a);
	virtual void SetSpecular(float r, float g, float b, float a);
	virtual void SetPosition(float x, float y, float z, float w = 0.0f);
	virtual void SetSpotDirection(float x, float y, float z);
	virtual void SetSpotExponent(float e);
	virtual void SetSpotCutoff(float c);
	virtual void SetConstantAttenuation(float c);
	virtual void SetLinearAttenuation(float c);
	virtual void SetQuadraticAttenuation(float c);

	virtual void Apply();
private:
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_position[4];
	float m_spotDirection[4];
	float m_spotExponent;
	float m_spotCutoff;
	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;

	int m_id;

	friend class TLightManager;
};

#endif