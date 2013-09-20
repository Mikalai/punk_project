#include "../../system/module.h"
#include "../../virtual/module.h"
#include "../../scene/module.h"
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
                {
                    auto value = System::HasInstance<Virtual::Armature>(word);
                    if (value)
                        return value;
                }
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
                return armature.release();
            }
            case WORD_ACTIONTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = Virtual::Action::find(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<Virtual::Action> action;
                if (word == L"male_walk")
                    action.reset(new Virtual::ActionMaleWalk);
                else
                    action.reset(new Virtual::Action);
                ParseAction(buffer, action.get());
                Virtual::Action::add(word, action.get());
                return action.release();
            }
            case WORD_STATICMESHTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<Virtual::StaticGeometry>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
                ParseStaticMesh(buffer, mesh.get());                
                mesh->SetName(word);
                return mesh.release();
            }
                break;
            case WORD_MATERIALTEXT:
            {                
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<Virtual::Material>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<Virtual::Material> material(new Virtual::Material);
                ParseMaterial(buffer, material.get());                
                return material.release();
            }
            case WORD_NAVIMESHTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<AI::NaviMesh>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<AI::NaviMesh> navi_mesh(new AI::NaviMesh);
                ParseNaviMesh(buffer, navi_mesh.get());
                return navi_mesh.release();
            }
            case WORD_PATHTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<AI::CurvePath>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<AI::CurvePath> path(new AI::CurvePath);
                ParseCurvePath(buffer, path.get());                
                return path.release();
            }
            case WORD_RIVERTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<Virtual::River>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<Virtual::River> river(new Virtual::River);
                ParseRiver(buffer, *river);                
                return river.release();
            }
            case WORD_SCENETEXT:
            {
                std::unique_ptr<Scene::SceneGraph> graph(new Scene::SceneGraph);
                ParseSceneGraph(buffer, *graph);
                return graph.release();
            }
            case WORD_SUNTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto value = System::HasInstance<Virtual::Sun>(word);
                    if (value)
                        return value;
                }
                std::unique_ptr<Virtual::Sun> sun(new Virtual::Sun);
                ParseSun(buffer, *sun);
                return sun.release();
            }
            case WORD_TERRAINTEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto mesh = System::HasInstance<Virtual::TerrainMesh>(word);
                    if (mesh)
                        return mesh;
                }
                std::unique_ptr<Virtual::TerrainMesh> mesh(new Virtual::TerrainMesh);
                ParseTerrainMesh(buffer, *mesh);
                return mesh.release();
            }
            case WORD_SKINMESH_TEXT:
            {
                System::string word = buffer.ReadWord();
                {
                    auto mesh = System::HasInstance<Virtual::SkinGeometry>(word);
                    if (mesh)
                        return mesh;
                }
                std::unique_ptr<Virtual::SkinGeometry> mesh(new Virtual::SkinGeometry);
                ParseSkinMesh(buffer, mesh.get());
                return mesh.release();
            }
            default:
                throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
            }
        }
        throw System::PunkInvalidArgumentException(L"Can't parse something");
    }
}
