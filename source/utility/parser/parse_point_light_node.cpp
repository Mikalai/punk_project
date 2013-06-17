#include "../../virtual/data/lights/point_light.h"
#include "../../scene/point_light_node.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParsePointLightNode(System::Buffer& buffer, Scene::PointLightNode* value)
    {
        CHECK_START(buffer);
        std::unique_ptr<Virtual::PointLight> light(new Virtual::PointLight);
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            switch(Parse(word))
            {
            case WORD_CLOSE_BRACKET:
                value->SetPointLight(light.release());
                return true;
            case WORD_NAME:
            {
                System::string name;
                ParseBlockedString(buffer, name);
                value->SetName(name);
                value->SetStorageName(name);
            }
                break;
            case WORD_COLOR:
            {
                Math::vec3 color;
                ParseBlockedVector3f(buffer, color);
                light->SetColor(color);
            }
                break;
            case WORD_DISTANCE:
            {
                float dst;
                ParseBlockedFloat(buffer, dst);
                light->SetDistance(dst);
            }
                break;
            case WORD_ENERGY:
            {
                float energy;
                ParseBlockedFloat(buffer, energy);
                light->SetEnergy(energy);
            }
                break;
            case WORD_LINEAR_ATTENUATION:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                light->SetLinearAttenuation(v);
            }
                break;
            case WORD_QUADRATIC_ATTENUATION:
            {
                float v;
                ParseBlockedFloat(buffer, v);
                light->SetQuadraticAttenuation(v);
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return true;
    }
}
