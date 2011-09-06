/*
File: DP5V.h
Author: Abramov Nickolai
Description: Contains a description of the DP-5V entity
*/

#include "DP5Geometry.h"

namespace Device
{
    namespace DP
    {
        DP5Geometry::DP5Geometry()
        {
            ImageLoader::ImageFile* image = ImageLoader::Load("data/dp/dp.dds");
            texture.Create(image->textures[0].width, image->textures[0].height, image->format, image->components, image->textures[0].surface.data);
            ImageLoader::Free(image);
            image = ImageLoader::Load("data/dp/dp_bump.dds");
            bump.Create(image->textures[0].width, image->textures[0].height, image->format, image->components, image->textures[0].surface.data);
            ImageLoader::Free(image);

            CaseGeometryMesh = Render::AdvancedStaticMesh::CreateFromFile("data/dp_case.punk");
            CaseGeometryMesh->SetProgram(&Shaders::GLSL::g_TextureBumpProgram);
            CaseGeometryMesh->BindShaderData();
            CaseGeometryMesh->SetDecalMap(texture);
            CaseGeometryMesh->SetBumpMap(bump);
            //CaseGeometryMesh->FlipNormals();
            CaseGeometryMesh->Init();

            PanelGeometryMesh = Render::AdvancedStaticMesh::CreateFromFile("data/dp_panel.punk");
            float* m = PanelGeometryMesh->m_matrix;
            Math::mat4 rot = Math::RotationMatrixFromQuaternion(quat(PI,vec3(1,0,0)));
            PanelGeometryMesh->m_matrix = PanelGeometryMesh->m_matrix * rot;
            m[14] = 0.76f;
            PanelGeometryMesh->SetProgram(&Shaders::GLSL::g_TextureBumpProgram);
            PanelGeometryMesh->BindShaderData();
            PanelGeometryMesh->SetDecalMap(texture);
            PanelGeometryMesh->SetBumpMap(bump);
            //PanelGeometryMesh->FlipNormals();
            PanelGeometryMesh->Init();/**/

        }

        DP5Geometry::~DP5Geometry()
        {
            delete CaseGeometryMesh;
            delete PanelGeometryMesh;
        }
        void DP5Geometry::Draw()
        {
            CaseGeometryMesh->Render();
           // PanelGeometryMesh->Render(0);
        }

    };
}
