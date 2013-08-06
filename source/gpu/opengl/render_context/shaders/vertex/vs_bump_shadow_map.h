#ifndef VS_BUMP_SHADOW_MAP_H
#define VS_BUMP_SHADOW_MAP_H

#include "../shader.h"

namespace Gpu
{
    namespace OpenGL
    {
        class VsBumpShadowMap : public Shader
        {
        public:
            VsBumpShadowMap();

            virtual void InitUniforms() override;
            virtual void BindParameters(const CoreState& params) override;
            virtual int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uWorld;
            unsigned uView;
            unsigned uProj;
            unsigned uNormalMatrix;
            unsigned uLightPosition;
            unsigned uTextureMatrix;
            unsigned uLightProjectionMatrix;
            unsigned uLightViewMatrix;

        };
    }
}

#endif // VS_BUMP_SHADOW_MAP_H
