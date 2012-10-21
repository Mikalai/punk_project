/*
File: StandardShaders.h
Author: Abramau Mikalaj
Description: A collection of predefined shaders
*/


#ifndef _H_STANDARD_SHADERS
#define _H_STANDARD_SHADERS
/*
namespace Driver
{
    namespace Video
    {
        namespace OpengGL
        {
            namespace Shaders
            {
                /*	namespace Cg
                    {
                            namespace Position
                            {
                                    const char vertex[] =
                                            "float4x4 uProjViewWorld;\
                                            struct VS_INPUT \
                                            {\
                                            float4 Position : POSITION0;\
                                            };\
                                            struct VS_OUTPUT \
                                            {\
                                            float4 Position : POSITION0;\
                                            };\
                                            VS_OUTPUT main( VS_INPUT Input )\
                                            {\
                                            VS_OUTPUT Output;\
                                            Output.Position = mul( Input.Position, uProjViewWorld);\
                                            return( Output );\
                                            }";
                                    const char fragment[] =
                                            "float4 main() : COLOR0\
                                            {   \
                                            return( float4( 1.0f, 0.0f, 0.0f, 1.0f ) );\
                                            }";
                            }
                    }
                namespace Position
                {
                    const char vertex[] = "#version 330\n\
                                          uniform mat4 WorldViewProj;\
                                          in vec3 Vertex;\
                                          \
                                          void main(void)\
                                          {\
                                           gl_Position = WorldViewProj * vec4(Vertex, 1.0);\
                                                     }";
                    const char fragment[] = "#version 330\n\
                                            \
                                            out vec4 FragColor;\
                                            \
                                            void main(void)\
                                            {\
                                             FragColor = vec4( 0.8, 0.0, 0.9, 1.0 );\
                                                     }";
                }
                namespace DirectionalLight
                {
                    const char vertex[] = "#version 330\n\
                                          uniform mat4 uWorldViewProjection;\
                                          uniform mat4 uWorldView;\
                                          uniform mat3 uNormal;\
                                          uniform vec3 uLightDir;\
                                          in vec3 rm_Vertex;\
                                          in vec3 rm_Normal;\
                                          out vec3 Normal;\
                                          out vec3 LightDir;\
                                          void main(void)\
                                          {\
                                           gl_Position = uWorldViewProjection * vec4(rm_Vertex, 1.0);\
                                                         LightDir = vec3(uWorldView * vec4(uLightDir, 1.0));\
                                                                    Normal = uNormal * rm_Normal;\
                                                                         }";
                    const char fragment[] = "#version 330\n\
                                            in vec3 Normal;\
                                            in vec3 LightDir;\
                                            out vec4 FragColor;\
                                            void main(void)\
                                            {\
                                             FragColor = vec4( 1, 1, 1, 1 ) * dot(normalize(Normal), normalize(LightDir));\
                                                     }";
                }

                namespace Texture
                {
                    const char vertex[] = "#version 330\n\
                                          uniform mat4 matWorldViewProjection;\
                                          in vec3 Vertex;\
                                          in vec2 rm_Texcoord;\
                                          out vec2 Texcoord;\
                                          void main( void )\
                                          {\
                                           gl_Position = matWorldViewProjection * vec4(Vertex, 1.0);\
                                                         Texcoord    = rm_Texcoord;\
                                                                   }";
                    const char fragment[] = "#version 330\n\
                                            uniform sampler2D baseMap;\
                                            in vec2 Texcoord;\
                                            out vec4 FragColor;\
                                            void main( void )\
                                            {\
                                             FragColor = texture( baseMap, Texcoord );\
                                                     }";
                }

                namespace TextureBlinn
                {
                    const char vertex[] = "#version 330\n\
                                          uniform mat4 uWorldViewProjection;\
                                          uniform mat4 uWorldView;\
                                          uniform mat3 uNormal;\
                                          uniform vec3 uLightDir;\
                                          in vec3 rm_Vertex;\
                                          in vec3 rm_Normal;\
                                          in vec2 rm_Texcoord;\
                                          out vec3 Normal;\
                                          out vec3 LightDir;\
                                          out vec2 Texcoord;\
                                          void main(void)\
                                          {\
                                           gl_Position = uWorldViewProjection * vec4(rm_Vertex, 1.0);\
                                                         LightDir = normalize(vec3(uWorldView * vec4(uLightDir, 1.0)));\
                                                                    Normal = normalize(uNormal * rm_Normal);\
                                                                             Texcoord = rm_Texcoord;\
                                                                                    }";
                    const char fragment[] = "#version 330\n\
                                            in vec3 Normal;\
                                            in vec3 LightDir;\
                                            in vec2 Texcoord;\
                                            uniform sampler2D uBaseMap;\
                                            out vec4 FragColor;\
                                            void main(void)\
                                            {\
                                             vec4 baseColor = texture(uBaseMap, Texcoord);\
                                                              FragColor = baseColor * dot(normalize(Normal), normalize(LightDir));\
                                                                      }";
                }
                namespace TextureBump
                {
                    const char vertex[] =
                            "#version 330\n\
                            uniform mat4 uProjViewWorld;\
                            uniform mat4 uWorldView;\
                            uniform vec3 uLightPosition;\
                            uniform vec3 uEyePosition;\
                            out vec2 Texcoord;\
                            out vec3 ViewDirection;\
                            out vec3 LightDirection;\
                            in vec3 rm_Vertex;\
                            in vec2 rm_Texcoord;\
                            in vec3 rm_Normal;\
                            in vec3 rm_Binormal;\
                            in vec3 rm_Tangent;\
                            float Determinant(in mat3 m)\
                    {\
                     return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
                     - m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) \
                     + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);\
                 }\
void Inverse(in mat3 m, out mat3 outMat)\
{\
 outMat[0][0] =   m[1][1] * m[2][2] - m[1][2] * m[2][1];\
                  outMat[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);\
                                 outMat[0][2] =   m[0][1] * m[1][2] - m[0][2] * m[1][1];\
                                                  outMat[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);\
                                                                 outMat[1][1] =   m[0][0] * m[2][2] - m[0][2] * m[2][0];\
                                                                                  outMat[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);\
                                                                                                 outMat[2][0] =   m[1][0] * m[2][1] - m[1][1] * m[2][0];\
                                                                                                                  outMat[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);\
                                                                                                                                 outMat[2][2] =   m[0][0] * m[1][1] - m[0][1] * m[1][0];\
                                                                                                                                                  outMat /= Determinant(outMat);\
                                                                                                                                                        }\
void main(void)\
{\
 gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);   \
               vec4 ObjectPosition = uWorldView * vec4(rm_Vertex, 1.0);\
                                     vec3 ViewDir  = uEyePosition - ObjectPosition.xyz;\
                                                     vec3 LightDir = uLightPosition - ObjectPosition.xyz;\
                                                                     mat3 NormalMatrix;\
                                                                     Inverse(mat3(uWorldView[0].xyz, uWorldView[1].xyz, uWorldView[2].xyz), NormalMatrix);    \
                                                                     NormalMatrix = transpose(NormalMatrix);\
                                                                                    vec3 Normal       = normalize(NormalMatrix * rm_Normal);\
                                                                                                        vec3 Binormal     = normalize(NormalMatrix * rm_Binormal);\
                                                                                                                            vec3 Tangent      = normalize(NormalMatrix * rm_Tangent);\
                                                                                                                                                ViewDirection.x  = dot(Tangent, ViewDir);\
                                                                                                                                                                   ViewDirection.y  = dot(Binormal, ViewDir);\
                                                                                                                                                                                      ViewDirection.z  = dot(Normal, ViewDir);\
                                                                                                                                                                                                         LightDirection.x  = dot(Tangent, LightDir);\
                                                                                                                                                                                                                             LightDirection.y  = dot(Binormal, LightDir);\
                                                                                                                                                                                                                                                 LightDirection.z  = dot(Normal, LightDir);\
                                                                                                                                                                                                                                                                     Texcoord = rm_Texcoord.xy;   \
                                                                                                                                                                                                                                                                            }";
                    const char fragment[] =
                            "#version 330\n\
                            uniform vec4 uAmbient;\
                            uniform vec4 uSpecular;\
                            uniform vec4 uDiffuse;\
                            uniform float uSpecularPower;\
                            uniform sampler2D uBaseMap;\
                            uniform sampler2D uBumpMap;\
                            in vec2 Texcoord;\
                            in vec3 ViewDirection;\
                            in vec3 LightDirection;\
                            out vec4 FragColor;\
                            void main( void )\
                    {\
                     vec3 LightDir = normalize(LightDirection);\
                                     vec3 Normal = normalize((texture(uBumpMap, Texcoord).xyz * 2.0) - 1.0);\
                                                   float NDotL = dot(Normal, LightDir);    \
                                                                 vec3 Reflection = normalize(((2.0 * Normal)*NDotL) - LightDir); \
                                                                                   vec3 ViewDir = normalize(ViewDirection );\
                                                                                                  float RDotV = max(0.0, dot(Reflection, ViewDir));\
                                                                                                                vec4 BaseColor = texture(uBaseMap, Texcoord);\
                                                                                                                                 vec4 TotalAmbient = uAmbient * BaseColor; \
                                                                                                                                                     vec4 TotalDiffuse = uDiffuse * NDotL * BaseColor; \
                                                                                                                                                                         vec4 TotalSpecular = uSpecular * (pow(RDotV, uSpecularPower));\
                                                                                                                                                                                              FragColor = (TotalAmbient + TotalDiffuse + TotalSpecular );       \
                                                                                                                                                                                                      }";
                }
                namespace TexturePhong
                {
                    const char vertex[] =
                            "uniform vec3 fvLightPosition;\
                            uniform vec3 fvEyePosition;\
                            \
                            varying vec2 Texcoord;\
                            varying vec3 ViewDirection;\
                            varying vec3 LightDirection;\
                            varying vec3 Normal;\
                            \
                            void main( void )\
                    {\
                     gl_Position = ftransform();\
                                   Texcoord    = gl_MultiTexCoord0.xy;\
                                                 \
                                                 vec4 fvObjectPosition = gl_ModelViewMatrix * gl_Vertex;\
                                                                         \
                                                                         ViewDirection  = fvEyePosition - fvObjectPosition.xyz;\
                                                                                          LightDirection = fvLightPosition - fvObjectPosition.xyz;\
                                                                                                           Normal         = gl_NormalMatrix * gl_Normal;\
                                                                                                                            \
                                                                                                                        }";
                    const char fragment[] =
                            "uniform vec4 fvAmbient;\
                            uniform vec4 fvSpecular;\
                            uniform vec4 fvDiffuse;\
                            uniform float fSpecularPower;\
                            \
                            uniform sampler2D baseMap;\
                            \
                            varying vec2 Texcoord;\
                            varying vec3 ViewDirection;\
                            varying vec3 LightDirection;\
                            varying vec3 Normal;\
                            \
                            void main( void )\
                    {\
                     vec3  fvLightDirection = normalize( LightDirection );\
                                              vec3  fvNormal         = normalize( Normal );\
                                                                       float fNDotL           = dot( fvNormal, fvLightDirection ); \
                                                                                                \
                                                                                                vec3  fvReflection     = normalize( ( ( 2.0 * fvNormal ) * fNDotL ) - fvLightDirection ); \
                                                                                                                         vec3  fvViewDirection  = normalize( ViewDirection );\
                                                                                                                                                  float fRDotV           = max( 0.0, dot( fvReflection, fvViewDirection ) );\
                                                                                                                                                                           \
                                                                                                                                                                           vec4  fvBaseColor      = texture2D( baseMap, Texcoord );\
                                                                                                                                                                                                    \
                                                                                                                                                                                                    vec4  fvTotalAmbient   = fvAmbient * fvBaseColor; \
                                                                                                                                                                                                                             vec4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; \
                                                                                                                                                                                                                                                      vec4  fvTotalSpecular  = fvSpecular * ( pow( fRDotV, fSpecularPower ) );\
                                                                                                                                                                                                                                                                               \
                                                                                                                                                                                                                                                                               gl_FragColor = ( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular );\
                                                                                                                                                                                                                                                                                              \
                                                                                                                                                                                                                                                                                          }";
                }
                namespace ShowNormal
                {
                    const char vertex[] =
                            "#version 330\n\
                            uniform mat4 uProjViewWorld;\
                            out vec2 TexCoord;\
                            out vec3 Normal;\
                            out vec3 Binormal;\
                            out vec3 Tangent;\
                            in vec3 rm_Vertex;\
                            in vec3 rm_Normal;\
                            in vec3 rm_Binormal;\
                            in vec3 rm_Tangent;\
                            in vec2 rm_Texcoord;\
                            void main( void )\
                    {\
                     mat4 matTransform = mat4( 1.0, 0.0, 0.0, 0.0,\
                                               0.0, 1.0, 0.0, 0.0,\
                                               0.0, 0.0, 1.0, 0.0,\
                                               0.0, 0.0, 0.0, 1.0 );\
                     gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);\
                                   TexCoord    = rm_Texcoord.xy;\
                                                 Normal      = ( ( matTransform * vec4( rm_Normal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                               Binormal    = ( ( matTransform * vec4( rm_Binormal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                             Tangent     = ( ( matTransform * vec4( rm_Tangent.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                                       }";

                    const char fragment[] =
                            "#version 330\n\
                            in vec2 TexCoord;\
                            in vec3 Normal;\
                            in vec3 Binormal;\
                            in vec3 Tangent;\
                            out vec4 FragColor;\
                            void main( void )\
                    {\
                     vec4 color = vec4( 0.0, 0.0, 0.0, 0.0);\
                                  color.xyz = Normal;\
                                              FragColor = color;\
                                                      }";
                }
                namespace ShowBinormal
                {
                    const char vertex[] =
                            "#version 330\n\
                            uniform mat4 uProjViewWorld;\
                            out vec2 TexCoord;\
                            out vec3 Normal;\
                            out vec3 Binormal;\
                            out vec3 Tangent;\
                            in vec3 rm_Vertex;\
                            in vec3 rm_Normal;\
                            in vec3 rm_Binormal;\
                            in vec3 rm_Tangent;\
                            in vec2 rm_Texcoord;\
                            void main( void )\
                    {\
                     mat4 matTransform = mat4( 1.0, 0.0, 0.0, 0.0,\
                                               0.0, 1.0, 0.0, 0.0,\
                                               0.0, 0.0, 1.0, 0.0,\
                                               0.0, 0.0, 0.0, 1.0 );\
                     gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);\
                                   TexCoord    = rm_Texcoord.xy;\
                                                 Normal      = ( ( matTransform * vec4( rm_Normal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                               Binormal    = ( ( matTransform * vec4( rm_Binormal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                             Tangent     = ( ( matTransform * vec4( rm_Tangent.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                                       }";

                    const char fragment[] =
                            "#version 330\n\
                            in vec2 TexCoord;\
                            in vec3 Normal;\
                            in vec3 Binormal;\
                            in vec3 Tangent;\
                            out vec4 FragColor;\
                            void main( void )\
                    {\
                     vec4 color = vec4( 0.0, 0.0, 0.0, 0.0);\
                                  color.xyz = Binormal;\
                                              FragColor = color;\
                                                      }";
                }
                namespace ShowTangent
                {
                    const char vertex[] =
                            "#version 330\n\
                            uniform mat4 uProjViewWorld;\
                            out vec2 TexCoord;\
                            out vec3 Normal;\
                            out vec3 Binormal;\
                            out vec3 Tangent;\
                            in vec3 rm_Vertex;\
                            in vec3 rm_Normal;\
                            in vec3 rm_Binormal;\
                            in vec3 rm_Tangent;\
                            in vec2 rm_Texcoord;\
                            void main( void )\
                    {\
                     mat4 matTransform = mat4( 1.0, 0.0, 0.0, 0.0,\
                                               0.0, 1.0, 0.0, 0.0,\
                                               0.0, 0.0, 1.0, 0.0,\
                                               0.0, 0.0, 0.0, 1.0 );\
                     gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);\
                                   TexCoord    = rm_Texcoord.xy;\
                                                 Normal      = ( ( matTransform * vec4( rm_Normal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                               Binormal    = ( ( matTransform * vec4( rm_Binormal.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                             Tangent     = ( ( matTransform * vec4( rm_Tangent.xyz, 0.0 ) ).xyz + 1.0 ) / 2.0;\
                                                                                       }";

                    const char fragment[] =
                            "#version 330\n\
                            in vec2 TexCoord;\
                            in vec3 Normal;\
                            in vec3 Binormal;\
                            in vec3 Tangent;\
                            out vec4 FragColor;\
                            void main( void )\
                    {\
                     vec4 color = vec4( 0.0, 0.0, 0.0, 0.0);\
                                  color.xyz = Tangent;\
                                              FragColor = color;\
                                                      }";
                }
            }


        }
    }
}*/
#endif
