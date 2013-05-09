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
	class VideoDriver;
	class Texture2D;
	class Renderable;
	class Batch;
    enum class RenderTarget;

	class PUNK_ENGINE Frame : public System::Poolable<Frame>
	{
	public:
		
		~Frame();

		void BeginRendering();
		void Render(Renderable* value, bool destroy = false);
		void PushState();
		void PopState();
		void MultWorldMatrix(const Math::mat4& value);		
		void SetWorldMatrix(const Math::mat4& value);		
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseMap0(const Texture2D* value);
		void SetDiffuseMap1(const Texture2D* value);
		void SetTextColor(const Math::vec4& value);
		void SetFontMap(const Texture2D* value);
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
		void EnableDiffuseShading(bool value);
		void EnableSkinning(bool value);
		void EnableWireframe(bool value);
		void EnableTerrainRendering(bool value);
		void EnableLighting(bool value);
		void EnableTexturing(bool value);
		void EnableFontRendering(bool value);

        //  added on 01.05.2013
		void SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer);
        void SetClearColor(const Math::vec4& value);
		void SetClearDepth(float value);

        const Math::vec4 GetClearColor() const;

		void Clear(bool color, bool depth, bool stencil);

        //  added on 02.05.2013
		void EnablePerVertexColor(bool value);

		void SetLightModel(LightModel value);
		LightParameters& Light(int slot);

		void DrawLine(const Math::vec3& start, const Math::vec3& end);

	private:

		CoreState* Top();
		const CoreState* Top() const;

		//  true if rendering is active. Some operations
		//  are not supported while rendering is active
		bool m_rendering;

		//	next should be delete in destructor
		std::stack<CoreState*> m_state;

		//	next should not be deleted in destructor
		VideoDriver* m_driver;
		std::vector<Batch*> m_batches;

	private:
		//	driver can create frames
		Frame(VideoDriver* driver);

		Frame(const Frame&) = delete;
		Frame& operator = (const Frame&) = delete;

		friend class VideoDriver;
	};
}

#endif	//	_H_PUNK_COMMON_RENDER_FRAME
