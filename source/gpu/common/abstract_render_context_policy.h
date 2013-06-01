#ifndef _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
#define _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT

#include "../../config.h"
#include "gpu_state.h"
#include "vertex_component.h"
#include "../../system/aop/aop.h"

namespace GPU
{
	enum class RenderPolicySet {
		Solid3D,
		SolidTextured3D,
		GUI,
		Terrain,
		Skinning,
		BumpMapping,
        BumpMappingShadowing,
		Painter,
		SolidVertexColor,
		LightPerFragmentDiffuse,
		LightPerFragmentTextureDiffuse,
		LightPerVertexDiffuse,
		LightPerVertexTextureDiffuse,
		LightPerFragmentDiffuseSpecular,
        LightPerVertexDiffuseSpecular,
        LightPerFragmentDiffuseShadowing,
        LightPerFragmentTextureDiffuseShadowing,
        LightPerVertexDiffuseShadowing,
        LightPerVertexTextureDiffuseShadowing,
        LightPerFragmentDiffuseSpecularShadowing,
		LightPerVertexDiffuseSpecularShadowing,
		DepthRender
	};

	class PUNK_ENGINE_PUBLIC AbstractRenderPolicy : public System::Aspect<AbstractRenderPolicy*, RenderPolicySet>
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
