#ifndef _MATERIAL
#define _MATERIAL

namespace Driver
{
	class Material
	{
	public:
		Material();
		Material(const Material& material);
		Material& operator = (const Material& material);
		virtual ~Material();

		float* GetAmbient();
		float* GetDiffuse();
		float* GetSpecular();
		float GetShine() const;
		float GetShineStrength() const;
		float GetTransparency() const;
		void SetAmbient(float r, float g, float b, float a);
		void SetDiffuse(float r, float g, float b, float a);
		void SetSpecular(float r, float g, float b, float a);
		void SetShine(float shine);
		void SetShineStrength(float shineStrength);
		void SetTransparency(float transparency);

		int GetSubMaterialsCount() const;
		Material* GetSubMaterials();

		void Apply();
	private:
		float m_ambient[4];
		float m_diffuse[4];
		float m_specular[4];
		float m_shine;
		float m_shineStrength;
		float m_transparency;

		int m_subMaterialCount;
		Material* m_subMaterial;

		friend class TMesh;
	};
}

#endif
