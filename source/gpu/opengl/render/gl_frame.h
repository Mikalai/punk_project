#ifndef _H_PUNK_OPENGL_FRAME
#define _H_PUNK_OPENGL_FRAME

#include "../../common/frame.h"
#include "../../common/gpu_state.h"
#include "../../../system/state_manager.h"
#include "gl_batch.h"

namespace GPU
{
	class VideoDriver;

	struct Frame::FrameImpl
	{
		FrameImpl();
		~FrameImpl();

		void BeginRendering();
		void Render(Renderable* value);
		void PushState();
		void PopState();
		CoreState* Top();
		void SetWorldMatrix(const Math::mat4& value);
		void MultWorldMatrix(const Math::mat4& value);
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseMap0(const Texture2D* value);
		void SetDiffuseMap1(const Texture2D* value);
		void EnableDiffuseShading(bool value);
		void EnableSkinning(bool value);
		void SetBoneMatrix(int bone_index, const Math::mat4& value);
		void SetSpecularColor(const Math::vec4& value);
		void SetSpecularMap(const Texture2D* value);
		void EnableSpecularShading(bool value);
		void SetBumpMap(const Texture2D* value);
		void EnableBumpMapping(bool value);
		void CastShadows(bool value);
		void ReceiveShadow(bool value);
		void EndRendering();

		const Math::mat4& GetWorldMatrix();		
		const Math::mat4& GetViewMatrix();
		const Math::mat4& GetProjectionMatrix();
		const Math::vec4& GetDiffuseColor();
		const Texture2D* GetDiffuseMap0();
		const Texture2D* GetDiffuseMap1();
		const Math::mat4& GetBoneMatrix(int bone_index);
		const Math::vec4& GetSpecularColor();
		const Texture2D* GetSpecularMap();		
		const Texture2D* GetBumpMap();		

		void SetVideoDriver(VideoDriver* driver);
	private:
		std::stack<CoreState*> m_state;
		std::vector<OpenGL::Batch*> m_batches;
		VideoDriver* m_driver;
	};
}

#endif	//	_H_PUNK_OPENGL_FRAME
