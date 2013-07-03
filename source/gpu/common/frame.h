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

	class PUNK_ENGINE_API Frame : public System::Poolable<Frame>
	{
	public:
		
		~Frame();

		void BeginRendering();
		void Render(Renderable* value, bool destroy = false);
		void MultWorldMatrix(const Math::mat4& value);		
		void SetWorldMatrix(const Math::mat4& value);		
		void SetViewMatrix(const Math::mat4& value);
		void SetProjectionMatrix(const Math::mat4& value);
		void SetDiffuseColor(const Math::vec4& value);
		void SetDiffuseColor(float r, float g, float b, float a);
		void SetDiffuseMap0(const Texture2D* value);
		void SetDiffuseMap1(const Texture2D* value);
        void SetHeightMap(const Texture2D* value);
        void SetNormalMap(const Texture2D* value);
		void SetTextColor(const Math::vec4& value);
		void SetFontMap(const Texture2D* value);
		void SetBoneMatrix(int bone_index, const Math::mat4& value);
		void SetSpecularColor(const Math::vec4& value);
		void SetSpecularFactor(float value);
		void SetAmbientColor(float value);
		void SetClipSpace(const Math::ClipSpace& value);		
		void SetLineWidth(float value);
		void SetPointSize(float value);
		void SetTextureMatrix(const Math::mat4& value);
		void SetLocalMatrix(const Math::mat4& value);

		void SetSpecularMap(const Texture2D* value);		
		void SetBumpMap(const Texture2D* value);				

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
		
        void CastShadows(bool value);
		void ReceiveShadow(bool value);
		void EndRendering();

		void EnableBlending(bool value);
		void EnableDepthTest(bool value);		
        void EnableDiffuseShading(bool value);
        //void EnableBumpMapping(bool value);
		void EnableSkinning(bool value);
		void EnableWireframe(bool value);
		void EnableTerrainRendering(bool value);
		void EnableLighting(bool value);
		void EnableTexturing(bool value);
		void EnableFontRendering(bool value);        
        void EnableBoundBoxRendering(bool value);
        bool IsEnabledBoundingBoxRendering() const;
        void EnableBoundingSphereRendering(bool value);
        bool IsEnabledBoundingSphereRendering() const;
        void EnableNaviMeshRendering(bool value);
        bool IsEnabledNaviMeshRendering();

        //  added on 01.05.2013
		void SetRenderTarget(Texture2D* color_buffer, Texture2D* depth_buffer);
		void SetClearColor(const Math::vec4& value);
		void SetClearColor(float r, float g, float b, float a);
		void SetClearDepth(float value);

        const Math::vec4 GetClearColor() const;

		void Clear(bool color, bool depth, bool stencil);

        //  added on 02.05.2013
		void EnablePerVertexColor(bool value);

		void SetLightModel(LightModel value);
		LightParameters& Light(int slot);

		void DrawLine(const Math::vec3& start, const Math::vec3& end);
        void DrawLine(float x1, float y1, float x2, float y2);
        void DrawPoint(float x, float y);
        void DrawPoint(const Math::vec3& v);
        void DrawPoint(float x, float y, float z);
        void DrawCircleXY(float x, float y, float z, float r);
        void DrawCircleXY(const Math::vec3& c, float r);


		void SetBlendColor(const Math::vec4& value);
		void SetBlendColor(float r, float g, float b, float a);
		void SetBlendFunc(BlendFunction src, BlendFunction dst);

		FogDescription& Fog();
		const FogDescription& Fog() const;

		void PushAllState();
		void PopAllState();

		void PushViewState();
		void PopViewState();

		void PushLightState();
		void PopLightState();

		void PushRenderState();
		void PopRenderState();

		void PushBatchState();
		void PopBatchState();

		void PushTextureState();
		void PopTextureState();

        VideoDriver* GetVideoDriver() const;
	private:

		CoreState* Top();
		const CoreState* Top() const;

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
