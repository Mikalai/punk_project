#include "../../virtual/data/material.h"
#include "parse_functions.h"

namespace Utility
{
    bool ParseMaterials(System::Buffer& buffer, Scene::SceneGraph*)
    {
        CHECK_START(buffer);
        System::string name;
        while (1)
        {
            System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_CLOSE_BRACKET:
                return true;
            case WORD_MATERIAL:
            {
                std::unique_ptr<Virtual::Material> m(new Virtual::Material);
                ParseMaterial(buffer, m.get());
                Virtual::Material::add(m->GetStorageName(), m.get());
                m.release();
            }
                break;
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        return false;
    }
}
