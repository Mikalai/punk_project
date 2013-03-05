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

	class PUNK_ENGINE Frame 
	{
	public:
		
		Frame();
		~Frame();

		void BeginRendering();
		void Render(Renderable* value);
		void PushState();
		void PopState();
		void SetWorldMatrix(const Math::mat4& value);
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseMap(const Texture2D* value);
		void SetBoneMatrix(int bone_index, const Math::mat4& value);
		void SetSpecularColor(const Math::vec4& value);
		void SetSpecularMap(const Texture2D* value);		
		void SetBumpMap(const Texture2D* value);		
		void CastShadows(bool value);
		void ReceiveShadow(bool value);
		void EndRendering();

		void EnableBlending(bool value);
		void EnableDepthTest(bool value);
		void EnableSpecularShading(bool value);
		void EnableBumpMapping(bool value);
		void EnableDiffuseShading(bool value);
		void EnableSkinning(bool value);

		struct FrameImpl;
		FrameImpl* impl;

	private:
		Frame(const Frame&);
		Frame& operator = (const Frame&);
	};
}

#endif	//	_H_PUNK_COMMON_RENDER_FRAME