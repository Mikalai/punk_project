#ifndef ENGINE_OBJECTS_H
#define ENGINE_OBJECTS_H

enum EngineObject
{
    PUNK_NOT_OBJECt= 0,
    PUNK_OBJECT = 1,
    PUNK_COMPOUND_OBJECT,
    PUNK_NODE,
    PUNK_SCENE_GRAPH,
    PUNK_GEOMETRY,
    PUNK_STATIC_GEOMETRY,
    PUNK_SKIN_GEOMETRY,
    PUNK_ARMATURE,
    PUNK_HUMAN_ARMATURE,
    PUNK_HUMAN_MALE_ARMATURE,
    PUNK_HUMAN_FEMALE_ARMATURE,
    PUNK_MATERIAL,
    PUNK_NAVI_MESH,
    PUNK_ARMATURE_ANIMATION_MIXER,
    PUNK_ANIMATION_MIXER,
    PUNK_LIGHT,
    PUNK_POINT_LIGHT,
    PUNK_SPOT_LIGHT,
    PUNK_DIR_LIGHT,
    PUNK_TRANSFORM,
    PUNK_CURVE_PATH,
    PUNK_TERRAIN_MESH,
    PUNK_SUN,
    PUNK_RIVER,
    PUNK_LAST_ENGINE_OBJECT
};

#endif // ENGINE_OBJECTS_H