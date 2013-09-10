#ifndef FS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
#define FS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class FsPerVertexLightingDiffuseSimpleShadow : public Shader
        {
        public:
            FsPerVertexLightingDiffuseSimpleShadow();
            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseMap;
            unsigned uFarDistance;
            unsigned uShadowTextureArray;
            unsigned uShadowMatrix[4];
        };
    }
}

#endif // FS_PER_VERTEX_LIGHTING_DIFFUSE_SHADOW_SIMPLE
