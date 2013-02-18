#ifndef _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
#define _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT

#include "../../config.h"
#include "gpu_state.h"
#include "vertex_component.h"
#include "../../system/aop/aop.h"

namespace GPU
{
	enum RenderPolicySet { 
	RC_SOLD_3D,
	RC_TEXTURED_3D,
	RC_GUI,
	RC_TERRAIN,
	RC_SKINNING,
	RC_BUMP_MAPING,
	RC_PAINTER};

	class PUNK_ENGINE AbstractRenderPolicy : public System::Aspect<AbstractRenderPolicy*, RenderPolicySet>
	{
	public:
		AbstractRenderPolicy();
		virtual void InitUniforms() = 0;
		virtual void BindParameters(const CoreState& params) = 0;
		virtual VertexAttributes GetRequiredAttributesSet() const = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Init() = 0;		
		virtual ~AbstractRenderPolicy();
	protected:
		bool m_was_modified;
		VertexAttributes m_vertex_attributes;
	};
}

#endif	//	_H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT