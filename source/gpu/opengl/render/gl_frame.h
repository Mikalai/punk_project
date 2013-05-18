#ifndef _H_PUNK_OPENGL_FRAME
#define _H_PUNK_OPENGL_FRAME

#include "../../common/frame.h"
#include "../../common/gpu_state.h"
#include "../../../system/state_manager.h"
#include "../../common/render_batch.h"
#include "../render_targets/module.h"

namespace GPU
{
	struct VideoDriverImpl;

	struct Frame::FrameImpl
	{
		FrameImpl();
		~FrameImpl();

		void BeginRendering();
		void Render(Renderable* value);        
		void PushState();
		void PopState();
		CoreState* Top();
		const CoreState* Top() const;
		void SetWorldMatrix(const Math::mat4& value);
		void MultWorldMatrix(const Math::mat4& value);
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseMap0(const Texture2D* value);
		void SetDiffuseMap1(const Texture2D* value);
		void SetFontMap(const Texture2D* value);
		void SetBoneMatrix(int bone_index, const Math::mat4& value);
		void SetSpecularColor(const Math::vec4& value);
		void SetSpecularMap(const Texture2D* value);
		void SetBumpMap(const Texture2D* value);
		void CastShadows(bool value);
		void ReceiveShadow(bool value);
		void EndRendering();
		void SetAmbientColor(float value);
		void SetClipSpace(const Math::ClipSpace& value);
		void SetHeightMap(const Texture2D* value);
		void SetLineWidth(float value);
		void SetPointSize(float value);
		void SetTextureMatrix(const Math::mat4& value);
		void SetLocalMatrix(const Math::mat4& value);
		void SetSpecularFactor(float value);
		void SetTextColor(const Math::vec4& value);

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
		void EnableFontRendering(bool value);

		void SetVideoDriver(VideoDriverImpl* driver);

        //  Added on 01.05.2013
        void SetRenderTarget(RenderTarget target, Texture2D* buffer = nullptr);
        RenderTarget GetRenderTarget();
        void SetClearColor(const Math::vec4& value);
        const Math::vec4 GetClearColor() const;

        //  Added on 02.05.2013
        void EnablePerVertexColor(bool value);

	private:

        //  true if rendering is active. Some operations
        //  are not supported while rendering is active
        bool m_rendering;

        std::unique_ptr<OpenGL::RenderTarget> m_render_target;

		//	next should be delete in destructor
		std::stack<CoreState*> m_state;
		
		//	next should not be deleted in destructor
		VideoDriverImpl* m_driver;
        std::vector<Batch*> m_batches;
	};
}

#endif	//	_H_PUNK_OPENGL_FRAME
