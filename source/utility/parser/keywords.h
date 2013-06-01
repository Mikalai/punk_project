#ifndef _H_PUNK_VIRTUAL_KEY_WORDS
#define _H_PUNK_VIRTUAL_KEY_WORDS

namespace Utility
{	
	enum KeywordCode
	{
		WORD_BAD_KEYWORD,					// 0
		WORD_OPEN_BRACKET,					// 1
		WORD_CLOSE_BRACKET,					// 2
		WORD_OBJECT,						// 3
		WORD_BOUNDING_BOX,					// 4
		WORD_LOCATION,						// 5
		WORD_WORLD_MATRIX,					// 7
		WORD_LOCAL_MATRIX,					// 8
		WORD_STATIC_MESH,					// 9
		WORD_STATIC_MESHES,					// 9
		WORD_STATIC_MESH_NODE,
		WORD_BONE_MATRIX,
		WORD_SKIN_MESH,
		WORD_SKIN_MESHES,
		WORD_SKIN_MESH_NODE,
		WORD_VERTEX_POSITION,				// 10
		WORD_NORMALS,						// 11
		WORD_FACES,							// 12
		WORD_VERTEX_POSITIONS_ID,			// 13
		WORD_BONES_WEIGHT,					// 14
		WORD_ARMATURE,						// 15
		WORD_ARMATURE_NODE,
		WORD_BONE,							// 16
		WORD_NAME,							// 17
		WORD_ACTIONS,						// 18
		WORD_POS_X,							// 19
		WORD_POS_Y,					// 6
		WORD_POS_Z,					// 6
		WORD_ROT_W,					// 6
		WORD_ROT_X,					// 6
		WORD_ROT_Y,					// 6
		WORD_ROT_Z,					// 6
		WORD_PARENT,					// 6
		WORD_TEXTURE_COORD,					// 6
		WORD_MATERIAL,					// 6
		WORD_NORMAL_MAP,					// 6
		WORD_DIFFUSE_MAP,					// 6
		WORD_MATERIALS,					// 6
		WORD_GIMBAL_TRANSFORM,					// 6
		WORD_ACTION,					// 6
		WORD_ARMATURES,					// 6
		WORD_FRAMES,					// 6
		WORD_TEXTURE,					// 6
		WORD_TIMING,					// 6
		WORD_PARENT_INVERSED_MATRIX,					// 6
		WORD_LENGTH,					// 6
		WORD_ALPHA,									//{ , L"*alpha" }, 
		WORD_AMBIENT,								//{ , L"*ambient" },
		WORD_DARKNESS,								//{ , L"*darkness" },
		WORD_DIFFUSE_COLOR,							//{ , L"*diffuse_color" }, 
		WORD_DIFFUSE_FRESNEL,						//{ , L"*diffuse_fresnel" }, 
		WORD_DIFFUSE_FRESNEL_FACTOR,				//{ , L"*diffuse_fresnel_factor" },
		WORD_DIFFUSE_INTENSITY,						//{ , L"*diffuse_intensity" },
		WORD_EMIT,									//{ , L"*emit" },
		WORD_MIRROR_COLOR,							//{ , L"*mirror_color" },
		WORD_ROUGHNESS,								//{ , L"*roughness" },
		WORD_SPECULAR_ALPHA,						//{ , L"*specular_alpha" },
		WORD_SPECULAR_COLOR,						//{ , L"*specular_color" },
		WORD_SPECULAR_HARDNESS,						//{ , L"*specular_hardness" },
		WORD_SPECULAR_INTENSITY,					//{ , L"*specular_intensity" },
		WORD_SPECULAR_IOR,							//{ , L"*specular_ior" },
		WORD_SPECULAR_SLOPE,						//{ , L"*specular_slope" },
		WORD_TRANSLUCENCY,							//{ , L"*translucency" },
		WORD_SOUND,					// 6
		WORD_FILENAME,					// 6
		WORD_VOLUME,					// 6
		WORD_PITCH,					// 6
		WORD_MAX_DISTANCE,					// 6
		WORD_REFERENCE_DISTANCE,					// 6
		WORD_CONE_ANGLE_INNER,					// 6
		WORD_CONE_ANGLE_OUTER,					// 6
		WORD_CONE_VOLUME_OUTER,					// 6
		WORD_ATTENUATION,					// 6
		WORD_TYPE,					// 6
		WORD_POINT_LIGHT,					// 6
		WORD_LIGHT_TYPE,					// 6
		WORD_COLOR,					// 6
		WORD_DISTANCE,					// 6
		WORD_ENERGY,					// 6
		WORD_FALLOFF_TYPE,					// 6
		WORD_LINEAR_ATTENUATION,					// 6
		WORD_QUADRATIC_ATTENUATION,					// 6
		WORD_REFERENCE, 					// 6
		WORD_BONE_ANIMATION,					// 6
		WORD_OBJECT_ANIMATION,					// 6
		WORD_POSITION_TRACK,					// 6
		WORD_ROTATION_TRACK,					// 6
		WORD_MATERIAL_REF,					// 6
		WORD_ACTIONS_REF,					// 6
		WORD_ACTION_REF,					// 6
		WORD_CAMERA,					// 6
		WORD_FOV,					// 6
		WORD_NEAR_PLANE,					// 6
		WORD_FAR_PLANE,					// 6
		WORD_FOCUS,					// 6
		WORD_ORTHO_SCALE,					// 6
		WORD_COLLISION_MESH,					// 6
		WORD_LOCATION_INDOOR,					// 6
		WORD_CONVEX_MESH,					// 6
		WORD_MATERIAL_NODE,					// 6
		WORD_BONE_NODE,
		WORD_TRANSFORM_NODE,					// 6
		WORD_PORTAL,					// 6
		WORD_PORTAL_NODE,					// 6
		WORD_FACE_NORMALS,
		WORD_MAPDESCTEXT,
		WORD_REF,
		WORD_RAW_DATA_SOURCE,
		WORD_NUM_BLOCKS,
		WORD_BLOCK_SCALE,
		WORD_BLOCK_SIZE,
		WORD_HEIGHT_SCALE,
		WORD_WORLD_ORIGIN,
		WORD_CELL,		
		WORD_ARMATURETEXT,
		WORD_ACTIONTEXT,
		WORD_STATICMESHTEXT,
		WORD_MATERIALTEXT
	};

	struct Record
	{
		KeywordCode code;
		const wchar_t* word;
	};

	static const Record Keyword[] = {
		{ WORD_BAD_KEYWORD,				L"" },
		{ WORD_OPEN_BRACKET,			L"{" },
		{ WORD_CLOSE_BRACKET,			L"}" },
		{ WORD_OBJECT,					L"*object" },
		{ WORD_BOUNDING_BOX,			L"*bounding_box" },
		{ WORD_LOCATION,				L"*location" },
		{ WORD_WORLD_MATRIX,			L"*world_matrix" },
		{ WORD_LOCAL_MATRIX,			L"*local_matrix" },
		{ WORD_BONE_MATRIX,				L"*bone_matrix" },
		{ WORD_STATIC_MESH,				L"*static_mesh" },
		{ WORD_STATIC_MESHES,			L"*static_meshes" },
		{ WORD_STATIC_MESH_NODE,		L"*static_mesh_node" },
		{ WORD_SKIN_MESH,				L"*skin_mesh" },
		{ WORD_SKIN_MESHES,				L"*skin_meshes" },
		{ WORD_SKIN_MESH_NODE,			L"*skin_mesh_node" },
		{ WORD_VERTEX_POSITION,			L"*vertex_position" },
		{ WORD_NORMALS,					L"*normals" },
		{ WORD_FACES,					L"*faces" },
		{ WORD_VERTEX_POSITIONS_ID,		L"*vertex_positions_id" },
		{ WORD_BONES_WEIGHT,			L"*bones_weight" },
		{ WORD_ARMATURE_NODE,			L"*armature_node" },
		{ WORD_ARMATURE,				L"*armature" },
		{ WORD_BONE,					L"*bone" },
		{ WORD_NAME,					L"*name" },
		{ WORD_ACTIONS,					L"*actions" },
		{ WORD_POS_X,					L"*pos_x" },
		{ WORD_POS_Y,					L"*pos_y" },
		{ WORD_POS_Z,					L"*pos_z" },
		{ WORD_ROT_W,					L"*rot_w" },
		{ WORD_ROT_X,					L"*rot_x" },
		{ WORD_ROT_Y,					L"*rot_y" },
		{ WORD_ROT_Z,					L"*rot_z" },
		{ WORD_PARENT,					L"*parent" },
		{ WORD_TEXTURE_COORD,			L"*tex_coord" },
		{ WORD_MATERIAL,				L"*material" },
		{ WORD_NORMAL_MAP,				L"*normal_map" },
		{ WORD_DIFFUSE_MAP,				L"*diffuse_map" },
		{ WORD_MATERIALS,				L"*materials" },
		{ WORD_GIMBAL_TRANSFORM,		L"*gimbal_transform" },
		{ WORD_ACTION,					L"*action" },
		{ WORD_ARMATURES,				L"*armatures" },
		{ WORD_FRAMES,					L"*frames" }, 
		{ WORD_TEXTURE,					L"*texture" },
		{ WORD_TIMING,					L"*timing" },
		{ WORD_PARENT_INVERSED_MATRIX,	L"*parent_inverse_matrix" },
		{ WORD_LENGTH,					L"*length" },
		{ WORD_ALPHA,					L"*alpha" }, 
		{ WORD_AMBIENT,					L"*ambient" },
		{ WORD_DARKNESS,				L"*darkness" },
		{ WORD_DIFFUSE_COLOR,			L"*diffuse_color" }, 
		{ WORD_DIFFUSE_FRESNEL,			L"*diffuse_fresnel" }, 
		{ WORD_DIFFUSE_FRESNEL_FACTOR,	L"*diffuse_fresnel_factor" },
		{ WORD_DIFFUSE_INTENSITY,		L"*diffuse_intensity" },
		{ WORD_EMIT,					L"*emit" },
		{ WORD_MIRROR_COLOR,			L"*mirror_color" },
		{ WORD_ROUGHNESS,				L"*roughness" },
		{ WORD_SPECULAR_ALPHA,			L"*specular_alpha" },
		{ WORD_SPECULAR_COLOR,			L"*specular_color" },
		{ WORD_SPECULAR_HARDNESS,		L"*specular_hardness" },
		{ WORD_SPECULAR_INTENSITY,		L"*specular_intensity" },
		{ WORD_SPECULAR_IOR,			L"*specular_ior" },
		{ WORD_SPECULAR_SLOPE,			L"*specular_slope" },
		{ WORD_TRANSLUCENCY,			L"*translucency" },
		{ WORD_SOUND,					L"*sound" },
		{ WORD_FILENAME,				L"*filename" },
		{ WORD_VOLUME,					L"*volume" },
		{ WORD_PITCH,					L"*pitch" },
		{ WORD_MAX_DISTANCE,			L"*max_distance" },
		{ WORD_REFERENCE_DISTANCE,		L"*reference_distance" },
		{ WORD_CONE_ANGLE_INNER,		L"*cone_angle_inner" },
		{ WORD_CONE_ANGLE_OUTER,		L"*cone_angle_outer" },
		{ WORD_CONE_VOLUME_OUTER,		L"*cone_volume_outer" },
		{ WORD_ATTENUATION,				L"*attenuation" },
		{ WORD_TYPE,					L"*type" },
		{ WORD_POINT_LIGHT,				L"*point_light" },
		{ WORD_LIGHT_TYPE,				L"*light_type" },
		{ WORD_COLOR,					L"*color" },
		{ WORD_DISTANCE,				L"*distance" },
		{ WORD_ENERGY,					L"*energy" },
		{ WORD_FALLOFF_TYPE,			L"*fallof_type" },
		{ WORD_LINEAR_ATTENUATION,		L"*linear_attenuation" },
		{ WORD_QUADRATIC_ATTENUATION,	L"*quadratic_attenuation" },		
		{ WORD_BONE_ANIMATION,			L"*bone_animation" },
		{ WORD_OBJECT_ANIMATION,		L"*object_animation" },
		{ WORD_POSITION_TRACK,			L"*position_track" },
		{ WORD_ROTATION_TRACK,			L"*rotation_track" },
		{ WORD_MATERIAL_REF,			L"*material_ref" },
		{ WORD_ACTIONS_REF,				L"*actions_ref" },
		{ WORD_ACTION_REF,				L"*action_ref" },
		{ WORD_CAMERA,					L"*camera" },
		{ WORD_FOV,						L"*fov" },
		{ WORD_NEAR_PLANE,				L"*near" },
		{ WORD_FAR_PLANE,				L"*far" },
		{ WORD_FOCUS,					L"*focus" },
		{ WORD_ORTHO_SCALE,				L"*ortho_scale" },
		{ WORD_COLLISION_MESH,			L"*collision_mesh" },
		{ WORD_LOCATION_INDOOR,			L"*location_indoor" },
		{ WORD_CONVEX_MESH,				L"*convex_mesh" },
		{ WORD_MATERIAL_NODE,			L"*material_node" },
		{ WORD_TRANSFORM_NODE,			L"*transform_node"},
		{ WORD_PORTAL,					L"*portal" },
		{ WORD_PORTAL_NODE,				L"*portal_node" },
		{ WORD_STATIC_MESH,				L"*static_mesh" },		
		{ WORD_FACE_NORMALS,			L"*face_normals" },
		{ WORD_BONE_NODE,			    L"*bone_node" },
		{ WORD_MAPDESCTEXT,				L"MAPDESCTEXT" },
		{ WORD_REF,						L"*ref" },
		{ WORD_RAW_DATA_SOURCE,			L"*raw_data_source" },
		{ WORD_NUM_BLOCKS,				L"*num_blocks" },
		{ WORD_BLOCK_SCALE,				L"*block_scale" },
		{ WORD_BLOCK_SIZE,				L"*block_size" },
		{ WORD_HEIGHT_SCALE,			L"*height_scale" },
		{ WORD_WORLD_ORIGIN,			L"*world_origin" },
		{ WORD_CELL,					L"*cell" },
		{ WORD_ARMATURETEXT,			L"ARMATURETEXT" },
		{ WORD_ACTIONTEXT,				L"ACTIONTEXT" },
		{ WORD_STATICMESHTEXT,			L"STATICMESHTEXT" },
		{ WORD_MATERIALTEXT,			L"MATERIALTEXT" }
	};
}

#endif	//	_H_PUNK_VIRTUAL_KEY_WORDS