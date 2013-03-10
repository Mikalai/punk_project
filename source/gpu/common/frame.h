#ifndef _H_PUNK_COMMON_RENDER_FRAME
#define _H_PUNK_COMMON_RENDER_FRAME

#include "../../config.h"
#include "gpu_state.h"

namespace Math
{
	class mat4;
	class vec4;
}

namespace GPU
{
	class Texture2D;
	class Renderable;

	class PUNK_ENGINE Frame : public System::Poolable<Frame>
	{
	public:
		
		~Frame();

		void BeginRendering();
		void Render(Renderable* value);
		void PushState();
		void PopState();
		void MultWorldMatrix(const Math::mat4& value);		
		void SetWorldMatrix(const Math::mat4& value);		
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseMap0(const Texture2D* value);
		void SetDiffuseMap1(const Texture2D* value);
		void SetBoneMatrix(int bone_index, const Math::mat4& value);
		void SetSpecularColor(const Math::vec4& value);
		void SetSpecularFactor(float value);
		void SetAmbientColor(float value);
		void SetClipSpace(const Math::ClipSpace& value);
		void SetHeightMap(const Texture2D* value);
		void SetLineWidth(float value);
		void SetPointSize(float value);
		void SetTextureMatrix(const Math::mat4& value);
		void SetLocalMatrix(const Math::mat4& value);

		void SetSpecularMap(const Texture2D* value);		
		void SetBumpMap(const Texture2D* value);		
		void CastShadows(bool value);		

		const Math::mat4& GetWorldMatrix() const;		
		const Math::mat4& GetLocalMatrix() const;
		const Math::mat4& GetViewMatrix() const;
		const Math::mat4& GetProjectionMatrix() const;
		const Math::vec4& GetDiffuseColor() const;
		const Texture2D* GetDiffuseMap0() const;
		const Texture2D* GetDiffuseMap1() const;
		const Math::mat4& GetBoneMatrix(int bone_index) const;
		const Math::vec4& GetSpecularColor() const;
		const Texture2D* GetSpecularMap() const;		
		const Texture2D* GetBumpMap() const;		
		const Math::ClipSpace& GetClipSpace() const;
		
		void ReceiveShadow(bool value);
		void EndRendering();

		void EnableBlending(bool value);
		void EnableDepthTest(bool value);
		void EnableSpecularShading(bool value);
		void EnableBumpMapping(bool value);
		void EnableDiffuseShading(bool value);
		void EnableSkinning(bool value);
		void EnableWireframe(bool value);
		void EnableTerrainRendering(bool value);
		void EnableLighting(bool value);
		void EnableTexturing(bool value);
		struct FrameImpl;
		FrameImpl* impl;

	private:
		friend struct VideoDriverImpl;
		//	driver can create frames
		Frame();

		Frame(const Frame&);
		Frame& operator = (const Frame&);
	};
}

#endif	//	_H_PUNK_COMMON_RENDER_FRAME