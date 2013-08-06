#ifndef _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
#define _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT

#include "../../config.h"
#include "gpu_state.h"
#include "vertex_component.h"
#include "../../system/aop/aop.h"

namespace Gpu
{
	enum class RenderPolicySet {
		Solid3D,
		SolidTextured3D,
		GUI,
		Terrain,
		Skinning,
		BumpMapping,
        BumpMappingSkinning,
        BumpMappingShadowing,
        BumpMappingSkinningShadowing,
		Painter,
		SolidVertexColor,
		LightPerFragmentDiffuse,
		LightPerFragmentTextureDiffuse,
        LightPerFragmentTextureDiffuseSkinning,
		LightPerVertexDiffuse,
		LightPerVertexTextureDiffuse,
        LightPerVertexTextureDiffuseSkinning,
		LightPerFragmentDiffuseSpecular,
        LightPerVertexDiffuseSpecular,
        LightPerFragmentDiffuseShadowing,
        LightPerFragmentTextureDiffuseShadowing,
        LightPerVertexDiffuseShadowing,
        LightPerVertexTextureDiffuseShadowing,
        LightPerFragmentDiffuseSpecularShadowing,
		LightPerVertexDiffuseSpecularShadowing,
        TextSolidColor,
        DepthRender,
        DepthRenderSkinning
	};

	class PUNK_ENGINE_API AbstractRenderPolicy : public System::Aspect<AbstractRenderPolicy*, RenderPolicySet>
	{
	public:
		AbstractRenderPolicy();
        virtual void InitUniforms() = 0;
        virtual void BindParameters(const CoreState& params) = 0;
        virtual int64_t GetRequiredAttributesSet() const = 0;
        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void Init() = 0;
		virtual ~AbstractRenderPolicy();
	protected:
		bool m_was_modified;
		int64_t  m_vertex_attributes;
	};
}

#endif	//	_H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
