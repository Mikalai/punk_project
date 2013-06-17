#include "../../system/module.h"
#include "../../virtual/module.h"
#include "../../ai/module.h"

#include "parse_functions.h"

namespace Utility
{
    System::Object* ParseAnything(System::Buffer& buffer)
    {
        while (!buffer.IsEnd())
        {
            System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
            {
            case WORD_MAPDESCTEXT:
            {
                std::unique_ptr<Virtual::Terrain> terrain(new Virtual::Terrain);
                ParseMapDescription(buffer, terrain.get());
                return terrain.release();
            }
            case WORD_ARMATURETEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<Virtual::Armature> armature;
                if (word == L"male_armature")
                {
                    armature.reset(new Virtual::HumanMaleArmature);
                }
                else
                {
                    armature.reset(new Virtual::Armature);
                }

                ParseArmature(buffer, armature.get());
                Virtual::Armature::add(word, armature.get());
                return armature.release();
            }
            case WORD_ACTIONTEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<Virtual::Action> action;
                if (word == L"male_walk")
                    action.reset(new Virtual::ActionMaleWalk);
                else
                    throw System::PunkInvalidArgumentException(L"Punk engine doesn't support " + word + L" action");
                ParseAction(buffer, action.get());
                Virtual::Action::add(word, action.get());
                return action.release();
            }
            case WORD_STATICMESHTEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
                ParseStaticMesh(buffer, mesh.get());
                Virtual::StaticGeometry::add(word, mesh.get());
                mesh->SetName(word);
                mesh->SetStorageName(word);
                return mesh.release();
            }
                break;
            case WORD_MATERIALTEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<Virtual::Material> material(new Virtual::Material);
                ParseMaterial(buffer, material.get());
                Virtual::Material::add(word, material.get());
                return material.release();
            }
            case WORD_NAVIMESHTEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<AI::NaviMesh> navi_mesh(new AI::NaviMesh);
                ParseNaviMesh(buffer, navi_mesh.get());
                AI::NaviMesh::add(word, navi_mesh.get());
                return navi_mesh.release();
            }
            case WORD_PATHTEXT:
            {
                System::string word = buffer.ReadWord();
                std::unique_ptr<AI::CurvePath> path(new AI::CurvePath);
                ParseCurvePath(buffer, path.get());
                AI::CurvePath::add(word, path.get());
                return path.release();
            }
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        throw System::PunkInvalidArgumentException(L"Can't parse something");
    }
}
