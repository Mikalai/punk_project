#ifndef RENDER_RENDER_V2_H
#define RENDER_RENDER_V2_H

#include <stack>
#include "../../config.h"
#include "../../scene/interface.h"
#include "../../virtual/interface.h"
#include "../../math/mat4.h"
#include "../../gpu/common/lighting/module.h"

namespace Scene { class SceneGraph; }
namespace Gpu { class Frame; }
namespace Utility { class AsyncParser; }
namespace System { class Object; }

namespace Render
{
    class PUNK_ENGINE_API Render2
    {
    public:
        Render2();
        virtual ~Render2();
        void RenderScene(Scene::SceneGraph* value, const Math::mat4& view, const Math::mat4& projection, Gpu::Frame* frame);
        void Process(Scene::Node* node);
        void ProcessChildren(Scene::Node* node);
        Gpu::Frame* GetCurrentFrame();
        Virtual::ArmatureAnimationMixer* GetCurrentArmatureAnimationMixer();
        void SetCurrentArmatureAnimationMixer(Virtual::ArmatureAnimationMixer* value);
        void PushLocalMatrix(const Math::mat4 value);
        void PopLocalMatrix();
        const Math::mat4 GetLocalMatrix();

        void RegisterRenderProcessor(unsigned type, void (*F)(Render2*, Scene::Node*, System::Object*));

        void AddLight(const Gpu::LightParameters& light);
        size_t GetLightsCount();
        const Gpu::LightParameters& GetLight(int index);

    private:
        std::stack<Math::mat4> m_local_matrix;
        Gpu::Frame* m_frame;
        Virtual::ArmatureAnimationMixer* m_armature_mixer;
        std::vector<Gpu::LightParameters> m_all_lights;

        std::vector<void (*)(Render2*, Scene::Node*, System::Object*)> m_render_processor;
    };
}

#endif // RENDER_H
