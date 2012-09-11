#include <iostream>
#include <fstream>
#include <algorithm>
#include "../string/string.h"
#include "../system/environment.h"
#include "../system/binary_file.h"
#include "../system/logger.h"
#include "../system/error.h"

#include "sound.h"
#include "static_mesh.h"
#include "skinned_mesh.h"
#include "skin_animation.h"
#include "punk_scene_loader.h"
#include "bone.h"
#include "bone_frame.h"
#include "material.h"
#include "armature.h"
#include "../config.h"
#include <map>
#include <vector>
#include "../math/math.h"
#include "bone_frame.h"
#include "material.h"
#include "bone.h"
#include "armature.h"
#include "mesh.h"
#include "../utility/model/vertex_bone_weight.h"
#include "action.h"
#include "texture_faces.h"
#include "object.h"
#include "skeleton_animation.h"
#include "intersection.h"
#include "light.h"

#define CHECK_START(buffer)\
	if (!CheckIntegrity(buffer))\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		}

#define CHECK_END(buffer)\
	if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		}

namespace Utility
{
	enum KeywordCode
	{
		WORD_BAD_KEYWORD,
		WORD_OPEN_BRACKET,
		WORD_CLOSE_BRACKET,
		WORD_OBJECT,
		WORD_BOUNDING_BOX,
		WORD_LOCATION,
		WORD_WORLD_MATRIX,
		WORD_LOCAL_MATRIX,
		WORD_MESH,
		WORD_VERTEX_POSITION,
		WORD_NORMALS,
		WORD_FACES,
		WORD_VERTEX_POSITIONS_ID,
		WORD_BONES_WEIGHT,
		WORD_ARMATURE,
		WORD_BONE,
		WORD_NAME,
		WORD_ACTIONS,
		WORD_POS_X,
		WORD_POS_Y,
		WORD_POS_Z,
		WORD_ROT_W,
		WORD_ROT_X,
		WORD_ROT_Y,
		WORD_ROT_Z,
		WORD_PARENT,
		WORD_TEXTURE_COORD,
		WORD_MATERIAL,
		WORD_NORMAL_MAP,
		WORD_DIFFUSE_MAP,
		WORD_MATERIALS,
		WORD_GIMBAL_TRANSFORM,
		WORD_BONE_MATRIX,
		WORD_ACTION,
		WORD_ARMATURES,
		WORD_FRAMES, 
		WORD_TEXTURE,
		WORD_TIMING,
		WORD_PARENT_INVERSED_MATRIX,
		WORD_LENGTH,																								
		WORD_ALPHA,									//	L"*alpha", 
		WORD_AMBIENT,								//	L"*ambient",
		WORD_DARKNESS,								//	L"*darkness",
		WORD_DIFFUSE_COLOR,							//	L"*diffuse_color", 
		WORD_DIFFUSE_FRESNEL,						//	L"*diffuse_fresnel", 
		WORD_DIFFUSE_FRESNEL_FACTOR,				//	L"*diffuse_fresnel_factor",
		WORD_DIFFUSE_INTENSITY,						//	L"*diffuse_intensity",
		WORD_EMIT,									//	L"*emit",
		WORD_MIRROR_COLOR,							//	L"*mirror_color",
		WORD_ROUGHNESS,								//	L"*roughness",
		WORD_SPECULAR_ALPHA,						//	L"*specular_alpha",
		WORD_SPECULAR_COLOR,						//	L"*specular_color",
		WORD_SPECULAR_HARDNESS,						//	L"*specular_hardness",
		WORD_SPECULAR_INTENSITY,					//	L"*specular_intensity",
		WORD_SPECULAR_IOR,							//	L"*specular_ior",
		WORD_SPECULAR_SLOPE,						//	L"*specular_slope",
		WORD_TRANSLUCENCY,							//	L"*translucency",
		WORD_SOUND,
		WORD_FILENAME,
		WORD_VOLUME,
		WORD_PITCH,
		WORD_MAX_DISTANCE,
		WORD_REFERENCE_DISTANCE,
		WORD_CONE_ANGLE_INNER,
		WORD_CONE_ANGLE_OUTER,
		WORD_CONE_VOLUME_OUTER,
		WORD_ATTENUATION,
		WORD_TYPE, 
		WORD_POINT_LIGHT,
		WORD_LIGHT_TYPE,
		WORD_COLOR,
		WORD_DISTANCE,
		WORD_ENERGY,
		WORD_FALLOFF_TYPE,
		WORD_LINEAR_ATTENUATION,
		WORD_QUADRATIC_ATTENUATION,
		WORD_REFERENCE
	};

	static const wchar_t* Keyword[] = {
		L"",
		L"{",
		L"}",
		L"*object",
		L"*bounding_box",
		L"*location",
		L"*world_matrix",
		L"*local_matrix",
		L"*mesh",
		L"*vertex_position",
		L"*normals",
		L"*faces",
		L"*vertex_positions_id",
		L"*bones_weight",
		L"*armature",
		L"*bone",
		L"*name",
		L"*actions",
		L"*pos_x",
		L"*pos_y",
		L"*pos_z",
		L"*rot_w",
		L"*rot_x",
		L"*rot_y",
		L"*rot_z",
		L"*parent",
		L"*tex_coord",
		L"*material",
		L"*normal_map",
		L"*diffuse_map",
		L"*materials",
		L"*gimbal_transform",
		L"*bone_matrix",
		L"*action",
		L"*armatures",
		L"*frames", 
		L"*texture",
		L"*timing",
		L"*parent_inverse_matrix",
		L"*length",
		L"*alpha", 
		L"*ambient",
		L"*darkness",
		L"*diffuse_color", 
		L"*diffuse_fresnel", 
		L"*diffuse_fresnel_factor",
		L"*diffuse_intensity",
		L"*emit",
		L"*mirror_color",
		L"*roughness",
		L"*specular_alpha",
		L"*specular_color",
		L"*specular_hardness",
		L"*specular_intensity",
		L"*specular_ior",
		L"*specular_slope",
		L"*translucency",
		L"*sound",
		L"*filename",
		L"*volume",
		L"*pitch",
		L"*max_distance",
		L"*reference_distance",
		L"*cone_angle_inner",
		L"*cone_angle_outer",
		L"*cone_volume_outer",
		L"*attenuation",
		L"*type",
		L"*point_light",
		L"*light_type",
		L"*color",
		L"*distance",
		L"*energy",
		L"*fallof_type",
		L"*linear_attenuation",
		L"*quadratic_attenuation",
		L"*reference"
	};

	struct Scene::SceneImpl
	{					
		typedef std::map<System::string, Math::Matrix<BoneFrame> > CookedAnimation;
		typedef std::vector<std::shared_ptr<CookedAnimation>> CookedAnimationCollection;
		//	struct 		
		typedef std::map<System::string, std::shared_ptr<Object>> Objects;
		System::string m_material;
		Objects m_objects;
		Math::BoundingBox m_bbox;
	//	SkeletonID m_skeleton_id;
		//ActionCollection m_skeleton_animation;
		Materials m_materials;
		//CookedAnimationCollection m_cooked_animation;
		std::map<System::string, Math::Matrix<float> > m_frame_value;
		std::map<BoneName, std::map<FrameID, BoneFrame> >::iterator m_maximum_frames;
		std::map<BoneName, int> m_bone_index;
		
		typedef std::map<System::string, std::shared_ptr<Animation>> AnimationCollection;
		typedef std::map<System::string, AnimationCollection> ActionCollection;
		ActionCollection m_actions;

		ArmatureCollection m_armature_collection;

		SceneImpl::SceneImpl()
		{}


		SceneImpl::SceneImpl(const SceneImpl& impl)
			: m_material(impl.m_material)
			, m_bbox(impl.m_bbox)
			, m_objects(impl.m_objects)
//			, m_skeleton_id(impl.m_skeleton_id)
//			, m_skeleton_animation(impl.m_skeleton_animation)
			, m_materials(impl.m_materials)
			//, m_cooked_animation(impl.m_cooked_animation)
			, m_frame_value(impl.m_frame_value)
			, m_maximum_frames(impl.m_maximum_frames)
			, m_bone_index(impl.m_bone_index)
			, m_armature_collection(impl.m_armature_collection)
		{}

		void ObjectSimplifySave(const Object& object)
		{

		}

		void Save(std::ostream& stream)
		{
			int size = (int)m_objects.size();
			stream.write((char*)&size, sizeof(int));
			if (size)
			{
				for each (auto object in m_objects)
				{				
					object.second->Save(stream);
				}
			}

			m_bbox.Save(stream);
			size = (int)m_materials.size();
			stream.write((char*)&size, sizeof(int));
			for each (auto mat in m_materials)
			{
				mat.first.Save(stream);
				mat.second.Save(stream);
			}
			size = (int)m_actions.size();
			stream.write((char*)&size, sizeof(int));
			for each (auto anim_col in m_actions)
			{
				anim_col.first.Save(stream);
				size = (int)anim_col.second.size();
				stream.write((char*)&size, sizeof(int));
				for each (auto anim in anim_col.second)
				{
					anim.first.Save(stream);
					anim.second->Save(stream);
				}
			}
			size = (int)m_armature_collection.size();
			stream.write((char*)&size, sizeof(int));
			for each (auto armature in m_armature_collection)
			{
				armature.first.Save(stream);
				armature.second->Save(stream);
			}
		}

		void LoadFromBinaryFile(std::istream& stream)
		{
			int size = -1;
			stream.read((char*)&size, sizeof(int));
			for (int i = 0; i < size; ++i)
			{
				std::shared_ptr<Object> object(new Object);
				object->Load(stream);
				m_objects[object->GetName()] = object;
			}				

			m_bbox.Load(stream);
			size = 0;
			stream.read((char*)&size, sizeof(int));
			if (size)
			{
				for (int i = 0; i < size; ++i)
				{
					System::string name;
					name.Load(stream);
					m_materials[name].Load(stream);
				}
			}

			size = 0;
			stream.read((char*)&size, sizeof(int));
			if (size)
			{
				for (int i = 0; i < size; ++i)
				{
					System::string action_name;
					action_name.Load(stream);
					int count = 0;
					stream.read((char*)&count, sizeof(count));
					for (int j = 0; j < count; ++j)
					{
						System::string animation_name;
						animation_name.Load(stream);
						m_actions[action_name][animation_name].reset(new Animation);
						m_actions[action_name][animation_name]->Load(stream);
					}
				}
			}
			size = 0;
			stream.read((char*)&size, sizeof(int));
			for (int i = 0; i < size; ++i)
			{
				System::string name;
				name.Load(stream);
				m_armature_collection[name].reset(new Armature);
				m_armature_collection[name]->Load(stream);
			}
		}

		void Load(std::istream& ss)
		{
			bool use_text = false;
			try
			{
				std::ifstream& stream = dynamic_cast<std::ifstream&>(ss);
				std::ios_base::fmtflags f = stream.flags();	
				if (f & std::ios_base::binary)
					use_text = true;
				else
				{
					LoadFromBinaryFile(ss);
				}

			}
			catch(std::bad_cast&)
			{
				use_text = true;
			}

			if (use_text)
			{
				System::Buffer buffer;
				if (!System::BinaryFile::Load(ss, buffer))
				{
					out_error() << L"Unable to load binary file from stream" << std::endl;
					return;
				}

				LoadFromBuffer(buffer);
			}
			else
			{

			}
		}

		///	Loads entire scene
		void Load(const System::string& filename)
		{
			System::Buffer buffer;
			if (!System::BinaryFile::Load(filename, buffer))
			{
				out_error() << (L"Unable to load file " + filename).Data() << std::endl;
				return;
			}

			LoadFromBuffer(buffer);				
		}

		void LoadFromBuffer(System::Buffer& buffer)
		{
			while (!buffer.IsEnd())
			{
				System::string word = buffer.ReadWord();
				switch(Parse(word))
				{
				case WORD_OBJECT:
					{
						std::auto_ptr<Object> o(new Object);
						ParseObject(buffer, *o);
						Object* oo = o.release();
						m_objects[oo->GetName()].reset(oo);
					}
					break;
				case WORD_MATERIALS:
					ParseMaterials(buffer);
					break;
				case WORD_ARMATURES:
					ParseArmatures(buffer);
					break;
				case WORD_ACTIONS:
					ParseActions(buffer);
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword: %s",  word.Data()) << std::endl;
				}
			}

			for each (auto object in m_objects)
			{
				UpdateMaterials(*object.second.get());
				UpdateOctTree(*object.second.get());
			}
		}

		/// Parse actions
		void ParseActions(System::Buffer& buffer)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				KeywordCode index;
				switch(index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_ACTION:
					{	
						ParseAction(buffer, m_actions);
					}
					break;
				}
			}
		}

		void ParseAction(System::Buffer& buffer, ActionCollection& actions)
		{
			CHECK_START(buffer);

			System::string name;

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				KeywordCode index;				
				switch(index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					{
						name = ParseName(buffer);
						actions[name] = AnimationCollection();
					}
					break;
				case WORD_TIMING:
					{
						CHECK_START(buffer);
						buffer.ReadWord().ToInt32();
						buffer.ReadWord().ToInt32();
						if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)
							out_error() << L"Can't parse object" << std::endl;		
					}
					break;
				case WORD_FRAMES:
					ParseAnimation(buffer, name, actions[name]);
					break;
				}
			}
		}

		/// Parse armatures
		void ParseArmatures(System::Buffer& buffer)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				KeywordCode index;
				switch(index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_ARMATURE:
					{
						std::auto_ptr<Armature> armature(new Armature);
						ParseArmature(buffer, *armature);
						Armature* t = armature.get();
						m_armature_collection[t->GetName()].reset(armature.release());
					}
					break;
				}
			}
		}

		/// Parse single armature
		void ParseArmature(System::Buffer& buffer, Armature& res)
		{
			CHECK_START(buffer);
			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				int index;
				System::string name;
				switch(index = Parse(name = buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					res.CacheBones();
					return;
				case WORD_NAME:
					res.SetName(ParseName(buffer));
					break;
				case WORD_BONE:
					{
						std::auto_ptr<Bone> bone(new Bone);
						ParseBone(buffer, res, *bone);
						res.AddBone(bone.release());
					}
					break;
				default:
					out_error() << L"Unknown keyword: " + name << std::endl;
				}
			}
		}

		/// Perform parsing object chunk
		void ParseObject(System::Buffer &buffer, Object& o)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				System::string word = buffer.ReadWord(); 
				if (word == L"*sound")
					word = word;
				KeywordCode index;
				switch(index = Parse(word))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_TYPE:
					o.SetType(ParseName(buffer));
					break;
				case WORD_NAME:
					o.SetName(ParseName(buffer));
					out_message() << L"Parsing " + o.GetName() << std::endl;
					break;
				case WORD_PARENT:
					o.SetParentName(ParseName(buffer));
					break;
				case WORD_BOUNDING_BOX:
					o.AsBoundingBox() = ParseBoundingBox(buffer);
					break;
				case WORD_LOCATION:
					o.SetLocation(ParseVector(buffer));
					break;
				case WORD_WORLD_MATRIX:
					o.SetWorldMatrix(ParseMatrix(buffer));
					break;
				case WORD_PARENT_INVERSED_MATRIX:
					ParseMatrix(buffer);
					break;
				case WORD_LOCAL_MATRIX:
					o.SetLocalMatrix(ParseMatrix(buffer));
					break;
				case WORD_MESH:
					{
						o.SetMesh(new Mesh());
						ParseObjectMesh(buffer, *o.GetMesh(), o);
					}
					break;
					//case WORD_ARMATURE:
					//	ParseBones(buffer);
					//	break;
					//case WORD_SKELETON_ANIMATION:
					//	ParseAnimation(buffer);
					//	break;
				case WORD_MATERIAL:
					o.SetMaterialName(buffer.ReadWord());
					break;
				case WORD_REFERENCE:
					o.SetReferenceObjectName(ParseName(buffer));
					break;
				case WORD_SOUND:
					{
						std::auto_ptr<Sound> sound(new Sound);
						ParseSound(buffer, *sound.get());
						o.SetSound(sound.release());
					}
					break;
				case WORD_POINT_LIGHT:
					{
						std::auto_ptr<PointLight> light(new PointLight);
						ParsePointLight(buffer, *light.get());
						o.SetLight(light.release());
					}
					break;
				case WORD_OBJECT:
					{
						std::auto_ptr<Object> child(new Object);
						ParseObject(buffer, *child);
						o.AddChild(child.release());
					}
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl;
				}
			}
		}

		void ParsePointLight(System::Buffer& buffer, PointLight& light)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse sound" << std::endl;
					return;
				}

				switch(int index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					light.SetName(ParseName(buffer));
					break;					
				case WORD_LIGHT_TYPE:
					light.SetType(ParseName(buffer));
					break;
				case WORD_COLOR:
					light.SetColor(ParseVector(buffer).ToHomogeneous());
					break;
				case WORD_DISTANCE:
					light.SetDistance(ParseFloat(buffer));
					break;
				case WORD_ENERGY:
					light.SetEnergy(ParseFloat(buffer));
					break;
				case WORD_FALLOFF_TYPE:
					light.SetFalloffType(ParseName(buffer));
					break;
				case WORD_LINEAR_ATTENUATION:
					light.SetLinearAttenuation(ParseFloat(buffer));
					break;
				case WORD_QUADRATIC_ATTENUATION:
					light.SetQuadraticAttenuation(ParseFloat(buffer));
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl;
				}
			}	
		}

		void ParseSound(System::Buffer& buffer, Sound& snd)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse sound" << std::endl;
					return;
				}

				switch(int index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					snd.SetName(ParseName(buffer));
					break;					
				case WORD_FILENAME:
					snd.SetFilename(ParseName(buffer));
					break;
				case WORD_VOLUME:
					snd.SetVolume(ParseFloat(buffer));
					break;
				case WORD_PITCH:
					snd.SetPitch(ParseFloat(buffer));
					break;
				case WORD_MAX_DISTANCE:
					snd.SetMaxDistance(ParseFloat(buffer));
					break;
				case WORD_REFERENCE_DISTANCE:
					snd.SetReferenceDistance(ParseFloat(buffer));
					break;
				case WORD_CONE_ANGLE_INNER:
					snd.SetConeAngleInner(ParseFloat(buffer));
					break;
				case WORD_CONE_ANGLE_OUTER:
					snd.SetConeAngleOuter(ParseFloat(buffer));
					break;
				case WORD_CONE_VOLUME_OUTER:
					snd.SetConeVolumeOuter(ParseFloat(buffer));
					break;
				case WORD_ATTENUATION:
					snd.SetAttenuation(ParseFloat(buffer));
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl;
				}
			}
		}

		void ParseObjectMesh(System::Buffer& buffer, Mesh& mesh, Object& o)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				switch(int index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_VERTEX_POSITION:
					std::cout << "Loading vertex position..." << std::endl;
					ParseVertexPosition(buffer, mesh.m_vertices);					
					break;					
				case WORD_NORMALS:
					std::cout << "Loading normals..." << std::endl;
					ParseNormals(buffer, mesh.m_normals);
					break;
				case WORD_FACES:
					std::cout << "Loading faces..." << std::endl;
					ParseFaces(buffer, mesh.m_faces);
					break;
				case WORD_BONES_WEIGHT:
					ParseBonesWeights(buffer, mesh.m_bone_weights);
					break;
				case WORD_TEXTURE:
					{
						std::cout << "Loading textures..." << std::endl;
						TextureMesh* tm = mesh.m_tex_coords.FindEmpty();
						if (tm)
							ParseTexture(buffer, *tm);
						else
							ParseTexture(buffer, TextureMesh());
					}
					break;
				case WORD_MATERIAL:
					o.SetMaterialName(ParseMeshMaterial(buffer));
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl;
				}
			}
		}

		void ParseTexture(System::Buffer& buffer, TextureMesh& face)
		{
			CHECK_START(buffer);

			while (1)
			{
				if (buffer.IsEnd())
				{
					out_error() << L"Can't parse object" << std::endl;
					return;
				}

				switch(KeywordCode index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					face.SetName(ParseName(buffer));
					break;
				case WORD_TEXTURE_COORD:
					ParseTextureCoords(buffer, face);
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl;
				}
			}
		}

		void ParseTextureCoords(System::Buffer& buffer, TextureMesh& mesh)
		{
			CHECK_START(buffer);
			while (1)
			{
				System::string word = buffer.ReadWord();

				if (word == Keyword[WORD_CLOSE_BRACKET])
					return;
				
				float u1 = word.ToFloat();
				float v1 = buffer.ReadWord().ToFloat();
				float u2 = buffer.ReadWord().ToFloat();
				float v2 = buffer.ReadWord().ToFloat();
				float u3 = buffer.ReadWord().ToFloat();
				float v3 = buffer.ReadWord().ToFloat();
				float u4 = buffer.ReadWord().ToFloat();
				float v4 = buffer.ReadWord().ToFloat();

				TextureFace face;
				face[0].Set(u1, v1);
				face[1].Set(u2, v2);
				face[2].Set(u3, v3);
				face[3].Set(u4, v4);

				mesh.push_back(face);		
			}
		}

		const System::string ParseName(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			System::string name = buffer.ReadWord();
			CHECK_END(buffer);
			return name;
		}

		float ParseFloat(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			float v = buffer.ReadWord().ToFloat();
			CHECK_END(buffer);
			return v;
		}

		const Math::BoundingBox ParseBoundingBox(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			Math::BoundingBox bbox;
			for (int i = 0; i < 8; i++)
			{
				bbox[i].X() = buffer.ReadWord().ToFloat();
				bbox[i].Y() = buffer.ReadWord().ToFloat();
				bbox[i].Z() = buffer.ReadWord().ToFloat();
			}
			CHECK_END(buffer);
			return bbox;
		}

		const Math::vec3 ParseVector(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			Math::vec3 v;
			for (int i = 0; i < 3; i++)
				v[i] = buffer.ReadWord().ToFloat();
			CHECK_END(buffer);
			return v;
		}

		const Math::mat4 ParseMatrix(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			Math::mat4 m;
			for (int i = 0; i < 16; i++)
				m[i] = buffer.ReadWord().ToFloat();
			CHECK_END(buffer);
			return m.Transposed();
		}

		void ParseVertexPosition(System::Buffer &buffer, Vertices& v)
		{
			CHECK_START(buffer);
			int count = buffer.ReadWord().ToInt32();
			for (int i = 0; i < count; i++)
			{
				buffer.ReadWord();
				float x = buffer.ReadWord().ToFloat();
				float y = buffer.ReadWord().ToFloat();
				float z = buffer.ReadWord().ToFloat();
				//m_bbox.Max().X() = max(x, m_bbox.Max().X());
				//m_bbox.Max().Y() = max(y, m_bbox.Max().Y());
				//m_bbox.Max().Z() = max(z, m_bbox.Max().Z());
				//m_bbox.Min().X() = min(x, m_bbox.Min().X());
				//m_bbox.Min().Y() = min(y, m_bbox.Min().Y());
				//m_bbox.Min().Z() = min(z, m_bbox.Min().Z());
				v.push_back(Math::vec3(x,y,z));
			}
			CHECK_END(buffer);
		}

		void ParseNormals(System::Buffer &buffer, Normals& n)
		{
			CHECK_START(buffer);
			int count = buffer.ReadWord().ToInt32();
			for (int i = 0; i < count; i++)
			{
				buffer.ReadWord();
				float x = buffer.ReadWord().ToFloat();
				float y = buffer.ReadWord().ToFloat();
				float z = buffer.ReadWord().ToFloat();
				n.push_back(Math::vec3(x,y,z));
			}
			CHECK_END(buffer);
		}

		void ParseFaces(System::Buffer& buffer, Faces& f)
		{
			CHECK_START(buffer);
			int count = buffer.ReadWord().ToInt32();
			f.resize(count);

			while(1)
			{
				int index;
				switch(index = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_VERTEX_POSITIONS_ID:
					ParseFaceVertexID(buffer, f);
					break;
				}
			}
		}

		void ParseFaceVertexID(System::Buffer &buffer, Faces& f)
		{
			CHECK_START(buffer);
			for (int i = 0; i < (int)f.size(); i++)
			{
				buffer.ReadWord();	//skip index
				f[i].X() = buffer.ReadWord().ToInt32();
				f[i].Y() = buffer.ReadWord().ToInt32();
				f[i].Z() = buffer.ReadWord().ToInt32();
			}
			CHECK_END(buffer);
		}

		void ParseBonesWeights(System::Buffer& buffer, VertexBoneWeights& w)
		{
			CHECK_START(buffer);

			while (1)
			{
				System::string word = buffer.ReadWord();
				if (word == Keyword[WORD_CLOSE_BRACKET])
					return;
				int vertex_id = word.ToInt32();
				System::string bone_name = buffer.ReadWord();
				float weight = buffer.ReadWord().ToFloat();
				w[vertex_id][bone_name] = weight;
			}
		}

		//void ParseBones(System::Buffer &buffer)
		//{
		//	/*CHECK_START(buffer);

		//	int count = buffer.ReadWord().ToInt32();
		//	for (int i = 0; i < count; i++)
		//	{
		//		if (Parse(buffer.ReadWord()) != WORD_BONE)
		//			return;
		//		ParseBone(buffer, );
		//	}
		//	CHECK_END(buffer);*/
		//}

		Math::quat ParseQuaternion(System::Buffer& buffer)
		{
			CHECK_START(buffer);
			Math::quat q;
			q.W() = buffer.ReadWord().ToFloat();
			q.X() = buffer.ReadWord().ToFloat();
			q.Y() = buffer.ReadWord().ToFloat();
			q.Z() = buffer.ReadWord().ToFloat();
			CHECK_END(buffer);
			return q;
		}

		void ParseBone(System::Buffer& buffer, Armature& armature, Bone& bone)
		{
			CHECK_START(buffer);
			System::string name, parent;
			while (1)
			{
				switch(int code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					bone.SetName(ParseName(buffer));
					bone.SetParent(0);
					break;
				case WORD_PARENT:
					bone.SetParent(armature.GetBoneByName(ParseName(buffer)));
					break;
				case WORD_LOCAL_MATRIX:
					bone.SetMatrix(ParseMatrix(buffer));
					break;
				case WORD_GIMBAL_TRANSFORM:
					ParseQuaternion(buffer);
					break;
				case WORD_BONE_MATRIX:
					bone.SetBoneMatrix(ParseMatrix(buffer));
					break;
				case WORD_LENGTH:
					bone.SetLength(ParseFloat(buffer));
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl;
				}
			}
		}

		void ParseAnimation(System::Buffer& buffer, const System::string& action_name, AnimationCollection& animations)
		{
			CHECK_START(buffer);

			while (1)
			{
				switch(int code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_BONE:
					{						
						ParseBoneAnimation(buffer, action_name, animations);
					}
					break;
				case WORD_OBJECT:
					{
						ParseObjectAnimation(buffer, action_name, animations);
					}
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl;
				}
			}
		}

		void ParseObjectAnimation(System::Buffer& buffer, const System::string& action_name, AnimationCollection& animation)
		{
			CHECK_START(buffer);

			Object dummy;
			Object* cur_object = 0;

			System::string bone_name;
			while (1)
			{
				switch(KeywordCode code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					cur_object = FindObjectByName(ParseName(buffer));
					if (cur_object == 0)
					{
						cur_object = &dummy;
					}
					break;
				case WORD_POS_X:
				case WORD_POS_Y:
				case WORD_POS_Z:
				case WORD_ROT_W:
				case WORD_ROT_X:
				case WORD_ROT_Y:
				case WORD_ROT_Z:
					ParseObjectAnimationValues(buffer, *cur_object->AsAnimationMixer().GetOrCreateTrack(action_name), code);
					break;
				}
			}
		}

		void ParseBoneAnimation(System::Buffer& buffer, const System::string& action_name, AnimationCollection& animation)
		{
			CHECK_START(buffer);

			Bone* cur_bone = 0;

			System::string bone_name;
			while (1)
			{
				switch(KeywordCode code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					cur_bone = FindBoneByName(ParseName(buffer));
					if (cur_bone == 0)
						throw "Can't parse bone animation";
					break;
				case WORD_POS_X:
				case WORD_POS_Y:
				case WORD_POS_Z:
				case WORD_ROT_W:
				case WORD_ROT_X:
				case WORD_ROT_Y:
				case WORD_ROT_Z:
					ParseObjectAnimationValues(buffer, *cur_bone->GetAnimationMixer().GetOrCreateTrack(action_name), code);
					break;
				}
			}
		}

		void ParseObjectAnimationValues(System::Buffer& buffer, Animation& action, KeywordCode code)
		{
			CHECK_START(buffer);

			while (1)
			{
				System::string s = buffer.ReadWord();
				if (s == L"}")
					return;

				switch(code)
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_POS_X:
					{
						int frame = s.ToInt32();
						float x = buffer.ReadWord().ToFloat();
						action.GetOrCreatePositionKey(frame).X() = x;
					}
					break;
				case WORD_POS_Y:
					{
						int frame = s.ToInt32();
						float y = buffer.ReadWord().ToFloat();
						action.GetOrCreatePositionKey(frame).Y() = y;
					}
					break;
				case WORD_POS_Z:
					{
						int frame = s.ToInt32();
						float z = buffer.ReadWord().ToFloat();
						action.GetOrCreatePositionKey(frame).Z() = z;
					}
					break;
				case WORD_ROT_W:
					{
						int frame = s.ToInt32();
						float w = buffer.ReadWord().ToFloat();
						action.GetOrCreateRotationKey(frame).W() = w;
					}
					break;
				case WORD_ROT_X:
					{
						int frame = s.ToInt32();
						float x = buffer.ReadWord().ToFloat();
						action.GetOrCreateRotationKey(frame).X() = x;
					}
					break;
				case WORD_ROT_Y:
					{
						int frame = s.ToInt32();
						float y = buffer.ReadWord().ToFloat();
						action.GetOrCreateRotationKey(frame).Y() = y;
					}
					break;
				case WORD_ROT_Z:
					{
						int frame = s.ToInt32();
						float z = buffer.ReadWord().ToFloat();
						action.GetOrCreateRotationKey(frame).Z() = z;
					}
					break;
				}
			}
		}

		const System::string ParseMeshMaterial(System::Buffer& buffer)
		{
			System::string result;
			CHECK_START(buffer);
			result = buffer.ReadWord();
			CHECK_END(buffer);
			return result;
		}

		const System::string ParseMaterialsDiffuseMap(System::Buffer& buffer, const System::string& name)
		{
			System::string result;
			CHECK_START(buffer);
			result = buffer.ReadWord();
			CHECK_END(buffer);
			return result;
		}

		const System::string ParseMaterialsNormalMap(System::Buffer& buffer, const System::string& name)
		{
			System::string result;
			CHECK_START(buffer);
			result = buffer.ReadWord();
			CHECK_END(buffer);
			return result;
		}

		void ParseMaterials(System::Buffer &buffer)
		{
			CHECK_START(buffer);
			System::string name;
			while (1)
			{
				switch(KeywordCode code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_MATERIAL:
					{
						Material m;
						ParseMaterial(buffer, m);
						m_materials[m.GetName()] = m;
					}
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl;
				}
			}
		}

		void ParseMaterial(System::Buffer& buffer, Material& material)
		{
			CHECK_START(buffer);
			System::string name;
			while (1)
			{
				switch(KeywordCode code = Parse(buffer.ReadWord()))
				{
				case WORD_CLOSE_BRACKET:
					return;
				case WORD_NAME:
					material.SetName(ParseName(buffer));
					break;
				case WORD_ALPHA:
					material.SetAlpha(ParseFloat(buffer));
					break;
				case WORD_AMBIENT:
					material.SetAmbient(ParseFloat(buffer));
					break;
				case WORD_DARKNESS:
					material.SetDarkness(ParseFloat(buffer));
					break;
				case WORD_DIFFUSE_COLOR:
					material.SetDiffuseColor(ParseVector(buffer).ToHomogeneous());
					break;
				case WORD_DIFFUSE_FRESNEL:
					material.SetDiffuseFresnel(ParseFloat(buffer));
					break;
				case WORD_DIFFUSE_FRESNEL_FACTOR:
					material.SetDiffuseFresnelFactor(ParseFloat(buffer));
					break;
				case WORD_DIFFUSE_INTENSITY:
					material.SetDiffuseIntensity(ParseFloat(buffer));
					break;
				case WORD_EMIT:
					material.SetEmit(ParseFloat(buffer));
					break;
				case WORD_MIRROR_COLOR:
					material.SetMirrorColor(ParseVector(buffer).ToHomogeneous());
					break;
				case WORD_ROUGHNESS:
					material.SetRoughness(ParseFloat(buffer));
					break;
				case WORD_SPECULAR_ALPHA:
					material.SetSpecularAlpha(ParseFloat(buffer));
					break;
				case WORD_SPECULAR_COLOR:
					material.SetSpecularColor(ParseVector(buffer).ToHomogeneous());
					break;
				case WORD_SPECULAR_HARDNESS:
					material.SetSpecularFactor(ParseFloat(buffer));
					break;
				case WORD_SPECULAR_INTENSITY:
					material.SetSpecularIntensity(ParseFloat(buffer));
					break;
				case WORD_SPECULAR_IOR:
					material.SetSpecularIndexOfRefraction(ParseFloat(buffer));
					break;
				case WORD_SPECULAR_SLOPE:
					material.SetSpecularSlope(ParseFloat(buffer));
					break;
				case WORD_TRANSLUCENCY:
					material.SetTranslucency(ParseFloat(buffer));
					break;
				case WORD_NORMAL_MAP:
					material.SetTexture1(ParseMaterialsNormalMap(buffer, name));
					break;
				case WORD_DIFFUSE_MAP:
					material.SetTexture0(ParseMaterialsDiffuseMap(buffer, name));
					break;
				default:
					out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl;
				}
			}
		}

		/// This function convert a string representation of the file into code
		KeywordCode Parse(System::string& word)
		{
			for (int i = 0; i < sizeof(Keyword)/sizeof(void*); i++)
			{
				if (word == Keyword[i])
					return static_cast<KeywordCode>(i);
			}	
			out_error() << System::string::Format(L"Unknown keyword %s", word.Data()) << std::endl;		
			return WORD_BAD_KEYWORD;
		}

		/// Simple check of file integrity. if brackets mismatch occured we stop parsing
		bool CheckIntegrity(System::Buffer& buffer)
		{
			if (Parse(buffer.ReadWord()) != WORD_OPEN_BRACKET)
				return false;
			return true;
		}

		const Object* FindObjectByName(const System::string& obj) const
		{
			for each (auto object in m_objects)
			{
				if (object.second->GetName() == obj)
					return object.second.get();
				else
				{
					const Object* res = object.second->GetChild(obj, true);
					if (res)
						return res;
				}
			}
			return 0;
		}

		Object* FindObjectByName(const System::string& obj)
		{
			return const_cast<Object*>(static_cast<const SceneImpl*>(this)->FindObjectByName(obj));
		}

		const Bone* FindBoneByName(const System::string& name) const
		{
			for each (auto armature in m_armature_collection)
			{
				auto bone = armature.second->GetBoneByName(name);
				if (bone)
					return bone;
			}
			return 0;
		}

		Bone* FindBoneByName(const System::string& name) 
		{
			return const_cast<Bone*>(static_cast<const SceneImpl*>(this)->FindBoneByName(name));
		}

		Animation* FindAnimationByName(const System::string& name)
		{
			return 0;
		}

		const Animation* FindAnimationByName(const System::string& name) const
		{
			return 0;
		}


		bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res)
		{
			for each (auto record in m_objects)
			{
				record.second->IntersectWithRay(start, end, res);
			}
			return !res.empty();
		}

		void UpdateOctTree(Object& object)
		{
			object.BuildOctTree();
			for each (auto child in object.GetChildren())
			{
				UpdateMaterials(*child.get());
			}
		}

		void UpdateMaterials(Object& object)
		{
			const System::string& name = object.GetMaterialName();
			if (name.Length())
				object.SetMaterial(m_materials.at(name));
			for each (auto child in object.GetChildren())
			{
				UpdateMaterials(*child.get());
			}
		}

		//void BuildOctTree()
		//{
		//	m_oct_tree.SetData(m_faces, m_vertices);
		//}

		//Math::OctTree& GetOctTree()
		//{
		//	return m_oct_tree;
		//}

		//void BuildBoneIndex()
		//{
		//	int i = 0;
		//	for (BonesCollection::iterator bone = m_skeleton.m_bones.begin(); bone != m_skeleton.m_bones.end(); ++bone)
		//	{
		//		m_bone_index[(*bone).first] = i;
		//		(*bone).second->SetName((*bone).first);
		//		m_skeleton_id[i] = *((*bone).second);
		//		++i;
		//	}

		//	//
		//	//	Check skeleton hierarchy
		//	//
		//	for (BonesCollection::iterator bone = m_skeleton.m_bones.begin(); bone != m_skeleton.m_bones.end(); ++bone)
		//	{
		//		const System::string pname = (*bone).second->GetParentName();
		//		if (pname.Length() != 0)
		//			(*bone).second->SetParent(GetBoneID(pname));
		//		m_skeleton_id[GetBoneID((*bone).first)] = *(*bone).second;
		//	}
		//}

		//int GetBoneID(const System::string& bone_name) const
		//{
		//	return m_bone_index.at(bone_name);
		//}

		/*void CookAnimationFrames(const System::string& action_name, CookedAnimation& cooked_animation) 
		{
			//
			//	cook anitmation
			//
			Action& action = *m_skeleton_animation.at(action_name);

			//CalculateMaximumFrameCount(action_name);

			for (auto animation = action.GetSkeletonAnimation().begin(); animation != action.GetSkeletonAnimation().end(); ++animation)
			{
				System::string bone_name = animation->first;						
				BoneAnimation& bone_animation = *animation->second;
				for (auto frame = bone_animation.GetFrames().begin(); frame != bone_animation.GetFrames().end(); ++frame)
				{
					int current_frame = frame->first;
					cooked_animation[action_name].At(current_frame, bone_id).m_position = (*frame).second.m_position;
					m_cooked_animation[action_name].At(current_frame, bone_id).m_rotation= (*frame).second.m_rotation;
				}
			}
		}

		/*void CalculateMaximumFrameCount(const System::string& action_name)
		{
		int max = 0;
		Action& action = m_skeleton_animation[action_name];
		SkeletonAnimation::iterator max_iter; 
		for (SkeletonAnimation::iterator bone_anim = action.m_pose.begin(); bone_anim != action.m_pose.end(); ++bone_anim)
		{
		if (max < (*bone_anim).second.m_frames.size())
		{
		max_iter = bone_anim;
		max = (*bone_anim).second.m_frames.size();
		}
		}
		action.m_key_count = max;
		m_frame_value[action_name].SetSize(1, max);

		for (FramesCollection::iterator frame = (*max_iter).second.m_frames.begin(); frame != (*max_iter).second.m_frames.end(); ++frame)
		{
		int frame_index = GetFrameID(action_name, GetBoneID((*max_iter).first), (*frame).first);
		m_frame_value[action_name].At(0, frame_index) = (*frame).first;
		}
		}*/

	/*	int GetFrameID(const System::string& action_name, int bone_name, FrameID frame) const
		{
			int id = 0;
			const BoneAnimation& anim = m_skeleton_animation.at(action_name).m_pose.at(GetBoneName(bone_name));			
			for (auto pose = anim.m_frames.begin(); pose != anim.m_frames.end(); ++pose)
			{
				if ((*pose).first == frame)
					return id;
				id++;
			}
			return -1;
		}*/

		/*const System::string GetBoneName(int id) const
		{
			BonesCollection::const_iterator it = m_skeleton.m_bones.begin();
			for (int i = 0; i < id && it != m_skeleton.m_bones.end(); i++)
			{
				it++;
			}

			if (it == m_skeleton.m_bones.end())
				return L"NULL";
			return (*it).first;
		}
		*/
		int GetObjectsCount() const
		{
			return m_objects.size();
		}

		const System::string GetObjectName(int index) const
		{
			if (index >= (int)m_objects.size())
				throw System::SystemError(L"Index out of range");
			int i = 0;
			for (Objects::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
			{
				if (i == index)
					return it->first;
				i++;
			}
			return L"";
		}

		StaticMesh* CookStaticMesh(Object& o) const
		{
			struct Vertex
			{
				float x, y, z, w;
				float nx, ny, nz, nw;
				float tx, ty, tz, tw;
				float bx, by, bz, bw;				
				float u, v, s, q;
			};					
			std::auto_ptr<StaticMesh> mesh(new StaticMesh);
			mesh->SetIndexCount(o.GetMesh()->m_faces.size()*3);			
			mesh->SetIndexBuffer(0, mesh->GetIndexCount()*sizeof(unsigned));
			for (unsigned i = 0; i < o.GetMesh()->m_faces.size()*3; i++)
			{
				((unsigned*)mesh->GetIndexBuffer())[i] = i;
			}
			mesh->SetVertexCount(o.GetMesh()->m_faces.size()*3);			
			mesh->SetVertexBuffer(0, mesh->GetVertexCount()*sizeof(Vertex));
			Vertex* vb = (Vertex*)mesh->GetVertexBuffer();

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0; i < o.GetMesh()->m_tex_coords[0].size(); i++)
			{
				const Math::ivec3& f = o.GetMesh()->m_faces[i];
				const Math::vec3& v1 = o.GetMesh()->m_vertices[f[0]];
				const Math::vec3& v2 = o.GetMesh()->m_vertices[f[1]];
				const Math::vec3& v3 = o.GetMesh()->m_vertices[f[2]];
				const Math::vec2& t1 = o.GetMesh()->m_tex_coords[0][i][0];
				const Math::vec2& t2 = o.GetMesh()->m_tex_coords[0][i][1];
				const Math::vec2& t3 = o.GetMesh()->m_tex_coords[0][i][2];
				const Math::vec3& n1 = o.GetMesh()->m_normals[f[0]];
				const Math::vec3& n2 = o.GetMesh()->m_normals[f[1]];
				const Math::vec3& n3 = o.GetMesh()->m_normals[f[2]];

				Math::vec3 tgn;
				Math::vec3 nrm;
				Math::vec3 btn;
				float det;

				Math::CalculateTBN(v1, v2, v3, t1, t2, t3, tgn, btn, nrm, det);

				det = (det < 0) ? -1.0f : 1.0f;

				vb[index].x = v1[0];	vb[index].y = v1[1];	vb[index].z = v1[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n1[0];	vb[index].ny = n1[1];	vb[index].nz = n1[2];	vb[index].nw = 1.0f;
				vb[index].u = t1[0];	vb[index].v = t1[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
				base_index.push_back(f[0]);
				index++;

				Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
				vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
				vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
				base_index.push_back(f[1]);
				index++;

				Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
				vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
				vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
				base_index.push_back(f[2]);
				index++;
			}

			/// Smooth TBN
			std::vector<int> mask(mesh->GetVertexCount());
			for (int i = 0; i < (int)o.GetMesh()->m_vertices.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)mesh->GetVertexCount(); j++)
				{
					Vertex* v = static_cast<Vertex*>(mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						norm[0] += v->nx; norm[1] += v->ny; norm[2] += v->nz; 
						tang[0] += v->tx; tang[1] += v->ty; tang[2] += v->tz; 
						btan[0] += v->bx; btan[1] += v->by; btan[2] += v->bz; 
					}				
				}

				norm.Normalize();
				tang.Normalize();
				btan.Normalize();
				tang = (tang - norm.Dot(tang)*norm).Normalized();
				btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

				Math::Matrix<float> m(3,3);
				m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
				m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
				m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
				float w = m.Determinant();

				for (int j = 0; j < (int)mesh->GetVertexCount(); j++)
				{	
					Vertex* v = static_cast<Vertex*>(mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						v->nx = norm[0]; v->ny = norm[1]; v->nz = norm[2]; 
						v->tx = tang[0]; v->ty = tang[1]; v->tz = tang[2];  v->tw = w;
						v->bx = btan[0]; v->by = btan[1]; v->bz = btan[2]; 
					}				
				}
			}

			mesh->SetMeshOffset(o.GetLocalMatrix());
			mesh->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT);
			mesh->SetOneVertexSize(sizeof(Vertex));

			return mesh.release();
		}
			struct Vertex
			{
				float x, y, z, w;
				float nx, ny, nz, nw;				
				float bx, by, bz, bw;
				float tx, ty, tz, tw;
				float u, v, s, q;
				float b1, b2, b3, b4;
				float w1, w2, w3, w4;
			};

		StaticMesh* CookSkinnedMesh(Object& o, Armature armature) const
		{
			if (!o.GetMesh())
				return nullptr;

			if (o.GetMesh()->m_bone_weights.empty())
				return nullptr;

			std::auto_ptr<StaticMesh> mesh(new StaticMesh);
			mesh->SetIndexCount(o.GetMesh()->m_faces.size()*3);
			mesh->SetIndexBuffer(0, mesh->GetIndexCount()*sizeof(unsigned));

			for (unsigned i = 0; i < o.GetMesh()->m_faces.size()*3; i++)
			{
				((unsigned*)mesh->GetIndexBuffer())[i] = i;
			}

			mesh->SetVertexCount(o.GetMesh()->m_faces.size()*3);			
			mesh->SetVertexBuffer(0, sizeof(Vertex)*mesh->GetVertexCount());
			Vertex* vb = (Vertex*)mesh->GetVertexBuffer();

			std::vector<int> base_index;		/// contains vertex index in the source array

			int index = 0;
			for (unsigned i = 0, max_i = o.GetMesh()->m_tex_coords[0].size(); i < max_i; i++)
			{
				if (index == 18)
					i = i;
				const Math::ivec3& f = o.GetMesh()->m_faces[i];
				const Math::vec3& v1 = o.GetMesh()->m_vertices[f[0]];
				const Math::vec3& v2 = o.GetMesh()->m_vertices[f[1]];
				const Math::vec3& v3 = o.GetMesh()->m_vertices[f[2]];
				const Math::vec2& t1 = o.GetMesh()->m_tex_coords[0][i][0];
				const Math::vec2& t2 = o.GetMesh()->m_tex_coords[0][i][1];
				const Math::vec2& t3 = o.GetMesh()->m_tex_coords[0][i][2];
				const Math::vec3& n1 = o.GetMesh()->m_normals[f[0]];
				const Math::vec3& n2 = o.GetMesh()->m_normals[f[1]];
				const Math::vec3& n3 = o.GetMesh()->m_normals[f[2]];			

				Math::vec3 tgn;
				Math::vec3 nrm;
				Math::vec3 btn;
				float det;

				Math::CalculateTBN(v1, v2, v3, t1, t2, t3, tgn, btn, nrm, det);

				det = (det < 0) ? -1.0f : 1.0f;

				vb[index].x = v1[0];	vb[index].y = v1[1];	vb[index].z = v1[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n1[0];	vb[index].ny = n1[1];	vb[index].nz = n1[2];	vb[index].nw = 1.0f;
				vb[index].u = t1[0];	vb[index].v = t1[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

				CookOneVertexWithBone //{}\\==>
					(
					o, armature, f[0], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				float tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[0]);
				index++;
				if (index == 18)
					i = i;

				Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
				vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//	vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
				vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

				CookOneVertexWithBone //{}\\==>
					(
					o, armature, f[1], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[1]);
				index++;
				if (index == 18)
					i = i;

				Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
				vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//	vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
				vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

				CookOneVertexWithBone //{}\\==>
					(
					o, armature, f[2], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[2]);
				index++;
			}

			/// Smooth TBN
			std::vector<int> mask(mesh->GetVertexCount());
			for (int i = 0; i < (int)o.GetMesh()->m_vertices.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)mesh->GetVertexCount(); j++)
				{
					Vertex* v = static_cast<Vertex*>(mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						norm[0] += v->nx; norm[1] += v->ny; norm[2] += v->nz; 
						tang[0] += v->tx; tang[1] += v->ty; tang[2] += v->tz; 
						btan[0] += v->bx; btan[1] += v->by; btan[2] += v->bz; 
					}				
				}

				if (norm.Length() == 0)
					norm = norm;
				norm.Normalize();

				if (tang.Length() == 0)
					tang = tang;
				tang.Normalize();

				if (btan.Length() == 0)
					btan = btan;
				btan.Normalize();
				tang = (tang - norm.Dot(tang)*norm).Normalized();
				btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

				Math::Matrix<float> m(3,3);
				m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
				m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
				m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
				float w = m.Determinant();

				for (int j = 0; j < (int)mesh->GetVertexCount(); j++)
				{	
					Vertex* v = static_cast<Vertex*>(mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						v->nx = norm[0]; v->ny = norm[1]; v->nz = norm[2]; 
						v->tx = tang[0]; v->ty = tang[1]; v->tz = tang[2];  v->tw = w;
						v->bx = btan[0]; v->by = btan[1]; v->bz = btan[2]; 
					}				
				}
			}

			//CookBonesMatrix(bones, count);

			mesh->SetMeshOffset(o.GetLocalMatrix());
			mesh->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE_ID|COMPONENT_BONE_WEIGHT);
			mesh->SetOneVertexSize(sizeof(Vertex));
			return mesh.release();
		}

		void CookOneVertexWithBone(Object& o, Armature& armature, int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4) const
		{
			const BoneWeights& weights = o.GetMesh()->m_bone_weights.at(index);

			int b_id[4];
			memset(b_id, 0, sizeof(b_id));
			float w[4];
			memset(w, 0, sizeof(w));
			int used = 0;
			for (int i = 0; i < armature.GetBonesCount() /*&& used < 4*/; ++i)
			{
				const Bone* cur_bone = armature.GetBoneByIndex(i);
				if (weights.find(cur_bone->GetName()) != weights.end())
				{	
					//
					// �������� �������� ��������� �������
					//
					int min = 0;
					for (int j = 0; j < 4; j++)
					{
						if (w[j] < w[min])
							min = j;
					}
					b_id[min] = i;
					w[min] = weights.at(cur_bone->GetName());
					used++;
				}
			}

			//
			//	normalize
			//
			float l = w[0] + w[1] + w[2] + w[3];
			//		if (l == 0)
			//			throw System::SystemError(System::string::Format(L"Unable to calculate bone weight for %d vertex", index));

			if (w[0] < 0 || w[1] < 0 || w[2] < 0 || w[3] < 0)
				throw;

			w[0] /= l; w[1] /= l; w[2] /= l; w[3] /= l;
			w1 = w[0]; w2 = w[1]; w3 = w[2]; w4 = 1.0f - w1 - w2 - w3 ;
			b1 = (float)b_id[0]; b2 = (float)b_id[1]; b3 = (float)b_id[2]; b4 = (float)b_id[3];
		}

		Armature* GetArmature(const System::string& name)
		{
			auto it = m_armature_collection.find(name);
			if (it == m_armature_collection.end())
				return 0;
			return it->second.get();
		}

		const System::string GetArmatureName(int index) const
		{
			if (index >= (int)m_armature_collection.size())
				throw System::SystemError(L"Index out of range");
			
			int i = 0;
			for (auto it = m_armature_collection.begin(); it != m_armature_collection.end(); ++it)
			{
				if (i == index)
					return it->first;
				i++;
			}
			return L"";
		}

		int GetArmatureCount() const
		{
			return m_armature_collection.size();
		}

		void PrintObject(Object* object, int offset)
		{
			for (int i = 0; i != offset; ++i)
				std::wcout << L'\t';

			std::wcout << object->GetName().Data() << std::endl;
			
			for each (auto child in object->GetChildren())
				PrintObject(child.get(), offset + 1);
		}

		void PrintDebug()
		{
			for each (auto object in m_objects)
			{
				std::wcout << object.first.Data() << std::endl;
				for each (auto child in object.second->GetChildren())
				{
					PrintObject(child.get(), 1);
				}
			}
		}
	};


	/*! Side effect of this function is filling m_frame_value that holds correspondence between
	frames index and frame values
	*/

	/*int GetBoneID(const System::string& bone_name) const
	{
	return m_bone_index.at(bone_name);
	}*/

	/*const System::string GetBoneName(int id) const
	{	
		Armature::const_iterator it = m_skeleton.begin();
		for (int i = 0; i < id && it != m_skeleton.end(); i++)
		{
			it++;
		}

		if (it == m_skeleton.end())
			return L"NULL";
		return (*it).first;
	}

	/*BoneFrame GetGlobalFrame(int bone_name, System::string action_name, FrameID frame) const
	{
		BoneFrame res;
		if (bone_name == -1)
			return res;

		FramesCollection& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[GetBoneName(bone_name)];
		Armature& skelet = const_cast<Model*>(this)->m_skeleton;

		int frame_id = GetFrameID(action_name, bone_name, frame);
		int parent_id = skelet[GetBoneName(bone_name)].GetParent();


		Math::quat p(1, 0, 0, 0);
		if (parent_id != -1)
		{
			p = GetGlobalFrame(parent_id, action_name, frame).m_rotation;
		}


		Math::quat parent = GetBoneLocalOrientation(skelet[GetBoneName(bone_name)].GetParent(), action_name, frame);


		/*	res.m_rotation =
		(parent
		*skelet[GetBoneName(bone_name)].GetMatrix()
		*anim[frame].m_rotation
		*skelet[GetBoneName(bone_name)].GetMatrix().Inversed();
		*parent.Conjugated()).Normalized();
		/**/

		/*res.m_position = Math::vec3(0,0,0);
		return res;
	}

	/*const Math::quat GetBoneLocalOrientation(int bone_name, const System::string& action_name, FrameID frame) const
	{
		Math::quat res(1, 0, 0, 0);
		if (bone_name == -1)
			return res;
		FramesCollection& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[GetBoneName(bone_name)];
		Armature& skelet = const_cast<Model*>(this)->m_skeleton;

		//res = skelet[GetBoneName(bone_name)].m_gimbal_transform * anim[frame].m_rotation;;

		return (GetBoneLocalOrientation(skelet[GetBoneName(bone_name)].GetParent(), action_name, frame) * res).Normalized();	
	}

	const Math::quat GetBoneLocalPosition(int bone_name, const System::string& action_name, FrameID frame) const
	{
		Math::vec3 res(0, 0, 0);
		if (bone_name == -1)
			return res;
		FramesCollection& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name];
		Armature& skelet = const_cast<Model*>(this)->m_skeleton;

		res = anim[frame].m_rotation;;

		return (GetBoneLocalOrientation(skelet[bone_name].m_parent, action_name, frame) * res).Normalized();	
	}

	const Math::mat4 GetSourceGlobalMatrix(int bone_name) const
	{
		const Bone& bone = const_cast<Model*>(this)->m_skeleton[GetBoneName(bone_name)];
		if (bone.GetParent() == -1)
			return bone.GetMatrix();

		Math::mat4 res = GetSourceGlobalMatrix(bone.GetParent())*bone.GetMatrix();
		return res;
	}

	/*const Math::mat4 GetSourceGlobalMatrix(int bone_id) const
	{
		int id = 0;
		for (Armature::const_iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
		{
			if (id == bone_id)
				return (*bone).second.GetMatrix();
			id++;
		}
		return Math::mat4();
	}

	void CookBonesMatrix(Math::mat4*& bones, int& count) const
	{
		throw(System::SystemError(L"Not implemented"));
		count = m_skeleton.size();
		Math::mat4* cur_bone = bones = new Math::mat4[count];
		for (std::map<System::string, Bone>::const_iterator i = m_skeleton.begin(); i != m_skeleton.end(); ++i)
		{
			Math::mat4 m = CookGlobalMatrix((*i).first);
			m[12] = 0;
			m[13] = 0;
			m[14] = 0;
			cur_bone++ = m;
		}
	}*/


	/*bool CookSkinAnimation(const System::string& action_name, SkinAnimation*& anim)
	{
		anim = new SkinAnimation;
		anim->m_bones.resize(m_skeleton_animation.size());

		int index = 0;
		for (ActionCollection::iterator i = m_skeleton_animation.begin(); i != m_skeleton_animtion.end(); ++i)
		{
			(*i).second.
				anim->m_bones[
		}
	}


	bool CookAnimation(const System::string& action_name, SkinAnimation*& anim)
	{
		CookAnimationFrames(action_name);

		anim = new SkinAnimation;

		anim->SetAnimationSize(m_cooked_animation[action_name].RowCount(), m_cooked_animation[action_name].ColumnCount());
		anim->SetName(action_name);
		for (int bone_num = 0; bone_num < m_cooked_animation[action_name].RowCount(); bone_num++)
		{
			for (int frame_num = 0; frame_num < m_cooked_animation[action_name].ColumnCount(); frame_num++)
			{
				anim->SetPosition(m_cooked_animation[action_name].At(bone_num, frame_num).m_position, bone_num, frame_num);
				anim->SetRotation(m_cooked_animation[action_name].At(bone_num, frame_num).m_rotation, bone_num, frame_num);
			}			
		}

		for (int frame_num = 0; frame_num < m_cooked_animation[action_name].ColumnCount(); frame_num++)
		{
			anim->SetFrameTimeValue(frame_num, frame_num);
		}			

		anim->SetDuration(1);
		anim->SetTicksPerSecond(1);		
		anim->SetRestPosition(m_skeleton_id);
		anim->SetMeshOffset(m_local_matrix);

		return true;
	}*/

	

}

/** Interface implementaion goes here */
namespace Utility
{
	Scene::Scene()
		: impl_scene(new SceneImpl())
	{}

	Scene::Scene(const Scene& scene)
		: impl_scene(new SceneImpl(*scene.impl_scene))
	{}

	Scene& Scene::operator = (const Scene& scene)
	{
		Scene temp(scene);
		std::swap(impl_scene, temp.impl_scene);
		return *this;
	}

	Scene::~Scene()
	{
		impl_scene.reset(0);
	}

	void Scene::Load(const System::string& filename)
	{
		impl_scene.reset(new SceneImpl);
		impl_scene->Load(filename);
	}

	StaticMesh* Scene::CookStaticMesh(const System::string& name) const
	{
		Utility::Object* obj = impl_scene->FindObjectByName(name);
		if (!obj)
			return nullptr;
		return impl_scene->CookStaticMesh(*obj);
	}

	StaticMesh* Scene::CookSkinnedMesh(const System::string& name) const
	{
		Utility::Object* obj = impl_scene->FindObjectByName(name);
		if (!obj)
			return nullptr;
		return impl_scene->CookSkinnedMesh(*obj, *impl_scene->m_armature_collection.begin()->second.get());
	}

	int Scene::GetArmatureCount() const
	{
		return impl_scene->GetArmatureCount();
	}

	Armature* Scene::GetArmature(const System::string& name) 
	{
		return impl_scene->GetArmature(name);
	}

	const System::string Scene::GetArmatureName(int index) const
	{
		return impl_scene->GetArmatureName(index);
	}

	/*Math::OctTree& Scene::GetOctTree()
	{
	return impl_scene->GetOctTree();
	}*/

	bool Scene::IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res)
	{
		return impl_scene->IntersectWithRay(start, end, res);
	}

	Object* Scene::FindObjectByName(const System::string& name)
	{
		return impl_scene->FindObjectByName(name);
	}

	const Object* Scene::FindObjectByName(const System::string& name) const
	{
		return impl_scene->FindObjectByName(name);
	}

	Bone* Scene::FindBoneByName(const System::string& name)
	{
		return impl_scene->FindBoneByName(name);
	}

	const Bone* Scene::FindBoneByName(const System::string& name) const
	{
		return impl_scene->FindBoneByName(name);
	}

	Animation* Scene::FindAnimationByName(const System::string& name)
	{
		return impl_scene->FindAnimationByName(name);
	}

	const Animation* Scene::FindAnimationByName(const System::string& name) const
	{
		return impl_scene->FindAnimationByName(name);
	}

	unsigned Scene::GetObjectsCount() const
	{
		return impl_scene->GetObjectsCount();
	}

	const System::string Scene::GetObjectName(int index) const
	{
		return impl_scene->GetObjectName(index);
	}

	void Scene::PrintDebug()
	{
		impl_scene->PrintDebug();
	}

	void Scene::Save(std::ostream& stream)
	{
		impl_scene->Save(stream);
	}

	void Scene::Load(std::istream& stream)
	{
		impl_scene.reset(new SceneImpl);
		impl_scene->Load(stream);
	}

	struct SceneObjectIteratorImpl
	{
	};	
}