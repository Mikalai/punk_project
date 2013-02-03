bl_info = {
    "name":         "PunkEngine Middle Format",
    "author":       "Mikalaj Abramau",
    "blender":      (2,6,2),
    "version":      (0,0,1),
    "location":     "File > Import-Export",
    "description":  "Export PunkEngine (.pmd)",
    "category":     "Import-Export"
}

#mesh.materials['Material'].texture_slots['bump].texture.image.name
import bpy
import copy

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from copy import deepcopy

text_offset = 0 #used to print data nice
used_materials = set()
used_actions = set()
used_armatures = set()
used_skin_meshes = set()
used_static_meshes = set()
vertex_groups = {}

#   export single float
def export_float(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%f\n" % value)
    end_block(f)
    return

#   export single vec4
def export_vec4(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%f   %f   %f   %f\n" % (value[0], value[1], value[2], value[3]))
    end_block(f)
    return

#   export single vec4
def export_vec3(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%f   %f   %f\n" % (value[0], value[1], value[2]))
    end_block(f)
    return

#   export single string
def export_string(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%s\n" % value)
    end_block(f)
    return

def export_mat4(f, name, matrix):
    start_block(f, name)
    for v in matrix:  
        make_offset(f)      
        f.write("%16f%16f%16f%16f\n" % (v[0], v[1], v[2], v[3]))
    end_block(f)
    return

def inc_offset():
    global text_offset
    text_offset = text_offset + 1
    return

def dec_offset():
    global text_offset
    text_offset = text_offset - 1
    return

def make_offset(f):
    for i in range(text_offset):
        f.write("  ")
    return

def start_block(f, title):
    make_offset(f)
    f.write("%s\n" % title)
    make_offset(f)
    f.write("{\n")
    inc_offset()
    return

def end_block(f):
    dec_offset()
    make_offset(f)
    f.write("}\n\n")
    return

def export_name(f, object):
    start_block(f, "*name")
    
    make_offset(f)
    f.write("%s\n" % object.name)
    
    end_block(f)
    return

def export_bounding_box(f, object):
    start_block(f, "*bounding_box")
        
    for vertex in object.bound_box:
        make_offset(f)
        f.write("%16f%16f%16f\n" % (vertex[0], vertex[1], vertex[2]))
    
    end_block(f)
    return

#
#   export world matrix, if a child it will differ from local
#
def export_world_matrix(f, object):
    start_block(f, "*world_matrix")
    for v in object.matrix_world:  
        make_offset(f)      
        f.write("%16f%16f%16f%16f\n" % (v[0], v[1], v[2], v[3]))
    end_block(f)
    return

#
#   export normalse. one normal for one vertex. i still don't know
#   how to realize when one vertex can have some normals depending
#   on the current face
#   
def export_normals(f, mesh):
    if len(mesh.vertices) == 0:
        return;
    
    start_block(f, "*normals")
    #make_offset(f)
    #   f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("%5d%16f%16f%16f\n" % (vertex.index, vertex.normal.x, vertex.normal.y, vertex.normal.z))
    end_block(f)
    return
    
#
#   exports vertex position for current mesh with no tranformation
#   applied in the scene
#
def export_vertex_position(f, mesh):   
    if (mesh == None) or (len(mesh.vertices) == 0):
        return
    start_block(f, "*vertex_position")    
    #f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("%5d%16f%16f%16f\n" % (vertex.index, vertex.co.x, vertex.co.y, vertex.co.z)) 

    end_block(f)
    return

#
#   export vertex id for faces. it is practicaly enough. but
#   it is needed more info later. 
#
def export_faces(f, mesh):
    
    if (mesh == None) or len(mesh.polygons) == 0:
        return
    
    start_block(f, "*faces")
    for face in mesh.polygons:
        make_offset(f)
        f.write("%10d%10d%10d%10d\n" % (face.index, face.vertices[0], face.vertices[1], face.vertices[2]))       
    end_block(f)
    
    return

#
#   eports face normals
#
def export_face_normals(f, mesh):
    if (mesh == None) or len(mesh.polygons) == 0:
        return
    start_block(f, "*face_normals")
    for face in mesh.polygons:
        make_offset(f)
        f.write("%16d%16f%16f%16f\n" % (face.index, face.normal[0], face.normal[1], face.normal[2]))
    end_block(f)
    return

#
#   export bones weights
#
def export_bones_weight(f, data):    
    if len(vertex_groups) == 0:
        return
    
    start_block(f, "*bones_weight")    
    for vert in data.vertices:
        for group in vertex_groups[data.name]:
            try:
                ind = vert.index
                #print(ind)
                gr_name = group.name
                #print(gr_name)
                weight = group.weight(ind)
                #print(weight)
                make_offset(f)
                f.write("%5d %s %f\n" % (ind, gr_name, weight))
            except:
                pass
                #print("found a vertex that is not in a group")
    end_block(f)
    return


#   export local matrix
#
def export_local_matrix(f, object):
    start_block(f, "*local_matrix")
    for v in object.matrix_local:  
        make_offset(f)      
        f.write("%16f%16f%16f%16f\n" % (v[0], v[1], v[2], v[3]))
    end_block(f)
    return    

#   export parent inverse matrix
#
def export_parent_inverse_matrix(f, object):
    start_block(f, "*parent_inverse_matrix")
    for v in object.matrix_parent_inverse:  
        make_offset(f)      
        f.write("%16f%16f%16f%16f\n" % (v[0], v[1], v[2], v[3]))
    end_block(f)
    return    

#
#   export tex coords. i can't understand what is uv1 uv2 uv3 uv4
#   but i export all this staff. later should clear situation
#
def export_tex_coords(f, mesh):
    
    if (mesh == None) or (len(mesh.uv_textures) == 0):
        return

    index = 0;
    for texture in mesh.uv_layers:
        start_block(f, "*texture")    
        start_block(f, "*name")
        make_offset(f)
        f.write("texture_%d\n" % index)
        index = index + 1
        end_block(f)
        
        start_block(f, "*tex_coord")        
        #
        #   uv1 uv2 uv3 uv4
        #

        data = texture.data
    
        for face in range(0, len(mesh.polygons)):
            make_offset(f)
            f.write("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t\n" % (data[3*face].uv[0], data[3*face].uv[1], data[3*face+1].uv[0], data[3*face+1].uv[1], data[3*face+2].uv[0], data[3*face+2].uv[1], 0, 0))
            
        end_block(f)   
        end_block(f)
    return

#
#   export mesh material
#
def export_mesh_material(f, mesh):
    if (mesh == None) or (len(mesh.materials) == 0):
        return
    start_block(f, "*material_ref")
    make_offset(f)
    f.write("%s\n" % mesh.materials[0].name)
    used_materials.add(mesh.materials[0].name)
    end_block(f)
    return
  
#
#   export only mesh
#
#def export_mesh(f, object):
#    if object.data == None:
#        return
#    if type(object.data) == bpy.types.Mesh:
#        start_block(f, "*mesh")
#        export_vertex_position(f, object.data)
#        export_normals(f, object.data)
#        export_faces(f, object.data)
#        export_tex_coords(f, object.data)
#        export_mesh_material(f, object.data)
#        export_bones_weight(f, object) 
#        end_block(f)
#    return

#
#   exort collision mesh
#
def export_collision_mesh(f, object):
    if object.data == None:
        return
    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*collision_mesh")
        export_vertex_position(f, object.data)
        end_block(f)
    return
#
#   export bones
#
def export_bones(f):
    armatures = bpy.data.armatures
    if len(armatures) == 0:
        return
    start_block(f, "*armatures")
    for armature in armatures:
        export_armature(f, armature)
    end_block(f)    #*armatures

#
#   export armature skeleton
#
def export_armatures(f, armatures):    
    start_block(f, "*armatures")
    for armature_name in used_armatures:        
        armature = armatures[armature_name]
        start_block(f, "*armature")
        export_string(f, "*name", armature.name)    
        for bone in armature.bones:
            #   export bone
            start_block(f, "*bone")
            #   write bone name
            export_string(f, "*name", bone.name)
            #   write bone length
            export_float(f, "*length", bone.length)
            #   write bone parent
            if bone.parent != None:
                export_string(f, "*parent", bone.parent.name)
            #   write bone matrix
            export_mat4(f, "*local_matrix", bone.matrix_local)
            end_block(f)    #*bone
        end_block(f)    #*armature        
    end_block(f)    #*armatures
    return
    
#
#   used to export animation data
#
def export_action_ref(f, object):
    if object.animation_data == None:
        return
    animation = object.animation_data
    for track in animation.nla_tracks:        
        for strip in track.strips:
            used_actions.add(strip.name)
    return

#
#   export all animation
#    
def export_actions(f):    
    if len(used_actions) == 0:
        return
    if len(bpy.data.actions) == 0:
        return    
    
    start_block(f, "*actions")
    for action_name in used_actions:
        action = bpy.data.actions[action_name]
        export_action(f, action)
    end_block(f) #*actions
                
    return

#
#   export one action
#
def export_action(f, action):
    start_block(f, "*action")
    start_block(f, "*name")
    make_offset(f)
    f.write("%s\n" % action.name)
    end_block(f)
    try:
        start = int(action.frame_range[0])
        end = int(action.frame_range[1])
        start_block(f, "*timing")
        make_offset(f)
        f.write("%d %d\n" % (start, end))
        end_block(f)    #*timing
    except:
        print("erorr in timings")            
    
    tracks = dict()        
    
    #   cook tracks from curves
    #   keyframe points in each channel should be equal
    for curve in action.fcurves:         
        index = curve.array_index
        track_name = curve.group.name                    
        #   get all location tracks collection
        object_tracks = tracks.get(track_name)
        if object_tracks == None:
            object_tracks = dict()
            tracks[track_name] = object_tracks
        
        #   determine whether it is location or rotation.
        #   rotation should be represented only as quaternion
        if curve.data_path.rfind("location") != -1:
            track = object_tracks.get(curve.data_path)
            #   if no, than create new location tracks collection
            if track == None:
                track = list()
                object_tracks[curve.data_path] = track 
            #   [time, [x, y, z]]
            etalon = [0, [0.0, 0.0, 0.0]]
        if curve.data_path.rfind("rotation_quaternion") != -1:
            track = object_tracks.get(curve.data_path)
            if track == None:
                track = list()
                object_tracks[curve.data_path] = track
            #   [time, [w, x, y, z]]
            etalon = [0, [0.0, 0.0, 0.0, 0.0]]
        #   extract points from curve
        for key_index in range(0, len(curve.keyframe_points)):
            #   define location to write data
            #   if point already in track we use it
            #   otherwise create new point and add it
            #   to the track
            if len(track) > key_index:
                point = track[key_index]
            else:
                point = deepcopy(etalon)
                track.append(point)     
            #   retrieve cure           
            key = curve.keyframe_points[key_index]
            point[0] = int(key.co[0])
            point[1][index] = key.co[1]
      
    #   export all tracks 
    for object_name in tracks:
        object_tracks = tracks[object_name]
        #   write bone name that is affected by this curve
        if list(object_tracks.keys())[0].rfind("bones") != -1:
            start_block(f, "*bone_animation")
            start_block(f, "*name")
            make_offset(f)
            f.write("%s\n" % object_name)
            end_block(f)
        #   otherwise just mark this track as suitable for any object
        else:
            start_block(f, "*object_animation")
            
        #   export all tracks for current object    
        for track_name in object_tracks:
            track = object_tracks[track_name]            
            #   export position
            if track_name.rfind("location") != -1:
                start_block(f, "*position_track")
                for point in track:
                    make_offset(f)
                    f.write("%5d %16f %16f %16f\n" % (point[0], point[1][0], point[1][1], point[1][2]))
                end_block(f) #  *position_track
            #   epxort rotation
            if track_name.find("rotation_quaternion") != -1:
                start_block(f, "*rotation_track")
                for point in track:
                    make_offset(f)
                    f.write("%5d %16f %16f %16f %16f\n" % (point[0], point[1][0], point[1][1], point[1][2], point[1][3]))
                end_block(f) #  *rotation_track
        
        end_block(f)    # *bone_animation or *object_animation
    end_block(f)    # *action    

#   export all materials
def export_materials(f, materials):
    if len(used_materials) == 0:
        return
        
    if (len(materials) == 0):
        return
    
    start_block(f, "*materials")
    for material in used_materials:
        m = materials[material]
        start_block(f, "*material")        
        export_string(f, "*name", m.name)
        export_float(f, "*alpha", m.alpha)
        export_float(f, "*ambient", m.ambient)
        export_float(f, "*darkness", m.darkness)
        export_vec3(f, "*diffuse_color", m.diffuse_color)
        export_float(f, "*diffuse_fresnel", m.diffuse_fresnel)
        export_float(f, "*diffuse_fresnel_factor", m.diffuse_fresnel_factor)
        export_float(f, "*diffuse_intensity", m.diffuse_intensity)
        export_float(f, "*emit", m.emit)
        export_vec3(f, "*mirror_color", m.mirror_color)
        export_float(f, "*roughness", m.roughness)
        export_float(f, "*specular_alpha", m.specular_alpha)
        export_vec3(f, "*specular_color", m.specular_color)
        export_float(f, "*specular_hardness", m.specular_hardness)
        export_float(f, "*specular_intensity", m.specular_intensity)
        export_float(f, "*specular_ior", m.specular_ior)
        export_float(f, "*specular_slope", m.specular_slope)
        export_float(f, "*translucency", m.translucency)

        try:            
            export_string(f, "*diffuse_map", m.texture_slots[0].texture.image.name)   
        except:
            print("No texture found")
        
        try:
            export_string(f, "*normal_map", m.texture_slots[1].texture.image.name)
        except:
            print("No texture found")
                        
        end_block(f)  # *material
    end_block(f)    #   *materials
    return

def export_static_meshes(f, meshes): 
    start_block(f, "*static_meshes")
    for name in used_static_meshes:
        data = meshes[name]
        start_block(f, "*static_mesh")
        export_string(f, "*name", data.name)
        export_vertex_position(f, data)
        export_normals(f, data)
        export_faces(f, data)
        export_tex_coords(f, data)
        end_block(f)    #   static_mesh        
    end_block(f)    #   *static_meshes
    return

def export_skin_meshes(f, skins):     
    start_block(f, "*skin_meshes")
    for name in used_skin_meshes:
        data = skins[name]
        start_block(f, "*skin_mesh")
        export_string(f, "*name", data.name)
        export_vertex_position(f, data)
        export_normals(f, data)
        export_faces(f, data)
        export_tex_coords(f, data)
        export_bones_weight(f, data)
        end_block(f)    #   skin_mesh        
    end_block(f)    #   skin_meshes
    return

#
#   export sound
#
def export_sound(f, object):
    start_block(f, "*sound")
    export_string(f, "*name", object.data.name)    
    export_string(f, "*filename", object.data.sound.name)
    export_float(f, "*volume", object.data.volume)
    export_float(f, "*pitch", object.data.pitch)
    export_float(f, "*max_distance", object.data.distance_max)
    export_float(f, "*reference_distance", object.data.distance_reference)
    export_float(f, "*cone_angle_inner", object.data.cone_angle_inner)
    export_float(f, "*cone_angle_outer", object.data.cone_angle_outer)
    export_float(f, "*cone_volume_outer", object.data.cone_volume_outer)
    export_float(f, "*attenuation", object.data.attenuation)
    end_block(f)    #   *sound
    return

#
#   export properties
#
def export_properties(f, object):
    print(object.name)
    try:
        for p in object.items():
            try:
                print(p)
                if p[0] == 'type':           
                    start_block(f, "*type")
                    make_offset(f)
                    f.write("%s\n" % p[1])
                    end_block(f)
                if p[0] == 'reference':
                    export_string(f, "*reference", p[1])
                if p[0] == 'subtype':
                    export_string(f, "*subtype", p[1])
                if p[0] == 'options':
                    export_string(f, "*options", p[1])
            except:
                print("Bad property")
    except:
        print("No properties")
    return
       
#
#   export animation tracks for the object
#
#def export_animation_tracks(f, object):
#    if object.animation_data == None:
#        return
#    
#    if len(object.animation_data.nla_tracks) == 0:
#        return
#    
#    start_block(f, "*actions_ref")
#    for track in object.animation_data.nla_tracks:        
#        if len(track.strips) == 0:
#            print("No strips in track %s", track.name)
#            return        
#        if len(track.strips) != 1:
#            print("Wanring: only first strip will be exported")
#       export_string(f, "*action_ref", track.strips[0].action.name)
#        
#        used_actions.add(track.strips[0].action.name)
#        
#    end_block(f)

#
#   export lamps from the scene
#
def export_point_lamp(f, lamp):
    start_block(f, "*point_light")
    export_string(f, "*name", lamp.name)
    export_vec3(f, "*color", lamp.color)
    export_float(f, "*distance", lamp.distance)
    export_float(f, "*energy", lamp.energy)
#    export_string(f, "*fallof_type", lamp.falloff_type)
    export_float(f, "*linear_attenuation", lamp.linear_attenuation)
    export_float(f, "*quadratic_attenuation", lamp.quadratic_attenuation)
    end_block(f);
        
#
#   export camera
#
def export_camera(f, camera):
    start_block(f, "*camera")
    export_string(f, "*name", camera.name)
    export_string(f, "*type", camera.type)
    export_float(f, "*fov", camera.angle)
    export_float(f, "*near", camera.clip_start)
    export_float(f, "*far", camera.clip_end)
    export_float(f, "*focus", camera.dof_distance)
    export_float(f, "*ortho_scale", camera.ortho_scale)   
    end_block(f)
 
def export_light(f, object):
    start_block(f, "*transform_node")
    export_string(f, "*name", object.name + "_transform")
    export_local_matrix(f, object)
    export_bounding_box(f, object)
    if type(object.data) == bpy.types.PointLamp:
        export_point_lamp(f, object.data)
    end_block(f)
    return
 
def export_transform(f, object):
    #   transform node can be bound to the bone, thus check this fact
    if object.parent_bone != '':
        start_block(f, "*bone_node")
        export_string(f, "*name", object.parent_bone)
    start_block(f, "*transform_node")
    export_string(f, "*name", object.name + "_transform")
    export_local_matrix(f, object)
    export_children(f, object)        
    end_block(f)
    if object.parent_bone != '':
        end_block(f)    #*bone_node
    return

def export_portal(f, object):
    if type(object.data) == bpy.types.Mesh:        
        start_block(f, "*portal_node")
        export_string(f, "*name", object.name)
        export_local_matrix(f, object)
        export_vertex_position(f, object.data)
        end_block(f)
    return

def export_static_mesh_node(f, object): 
    if object.data == None:
        return
    mesh = object.data
    if not((mesh == None) or (len(mesh.materials) == 0)):
        start_block(f, "*material_node")
        used_materials.add(mesh.materials[0].name)
        export_string(f, "*name", mesh.materials[0].name)
     
    start_block(f, "*transform_node")
    export_string(f, "*name", object.name)
    export_local_matrix(f, object)
    export_bounding_box(f, object)

    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*static_mesh_node")
        export_string(f, "*name", object.data.name)
        used_static_meshes.add(object.data.name)
        end_block(f)    #   static_mesh_node        
    end_block(f) #  transform
    if not((mesh == None) or (len(mesh.materials) == 0)):
        end_block(f)    #   material
    return

def export_skin_mesh_node(f, object): 
    if object.data == None:
        return
    mesh = object.data
    if not((mesh == None) or (len(mesh.materials) == 0)):
        start_block(f, "*material_node")
        used_materials.add(mesh.materials[0].name)
        export_string(f, "*name", mesh.materials[0].name)
     
    start_block(f, "*transform_node")
    export_string(f, "*name", object.name)
    export_bounding_box(f, object)    
    export_local_matrix(f, object)

    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*skin_mesh_node")
        export_string(f, "*name", object.data.name)
        vertex_groups[object.data.name] = object.vertex_groups
        used_skin_meshes.add(object.data.name)
        end_block(f)    #   *skin_mesh_node
    end_block(f) #  transform
    if not((mesh == None) or (len(mesh.materials) == 0)):
        end_block(f)    #   material
    return

def export_armature_node(f, object):
    if object.data == None:
        return
     
    start_block(f, "*transform_node")
    export_string(f, "*name", object.name)
    export_local_matrix(f, object)
    export_bounding_box(f, object)
    
    armature = object.data
    start_block(f, "*armature_node")    
    export_string(f, "*name", armature.name)  
    used_armatures.add(armature.name)  
    #   export animation
    export_action_ref(f, object)
    #   export all children
    export_children(f, object)        
    end_block(f)    #*armature_node
    end_block(f)    #*transform
    return

def export_convex_mesh(f, object): 
    if object.data == None:
        return       
    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*convex_mesh")      
        export_vertex_position(f, object.data)
        export_face_normals(f, object.data)
        export_faces(f, object.data)
        end_block(f)
    return

def export_sound_2d(f, object):
    start_block(f, "*sound_2d")
    export_common(f, object)
    if type(object.data) == bpy.types.Speaker:
        export_sound(f, object)
    end_block(f)
    return

def export_sound_3d(f, object):
    start_block(f, "*sound_3d")
    export_common(f, object)
    if type(object.data) == bpy.types.Speaker:
        export_sound(f, object)
    end_block(f)
    return

def export_character(f, object):
    start_block(f, "*character")
    export_common(f, object)
    if type(object.data) == bpy.types.Armature:
        export_armature(f, object.data)
    export_children(f, object)       
    end_block(f)
    return

def export_location_indoor(f, object):
    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*location_indoor")
        export_local_matrix(f, object)
        export_convex_mesh(f, object)
        export_children(f, object)        
        end_block(f)
    return

def export_common(f, object):
    export_properties(f, object)
    export_name(f, object)
    
    if object.parent != None:
        export_string(f, "*parent", object.parent.name)
        
    export_bounding_box(f, object)
    export_world_matrix(f, object)
    export_local_matrix(f, object)
    export_parent_inverse_matrix(f, object)
    return

def export_children(f, object):
    for child in object.children:
        export_object(f, child)    
    return
   
def export_collision_mesh(f, object):
    return

#
#   export the whole object with all data i can imaginge
#
def export_object(f, object):        
    if object.punk_entity_type == "LOCATION_INDOOR":
        export_location_indoor(f, object)
    elif object.punk_entity_type == "TRANSFORM":
        export_transform(f, object)
    elif object.punk_entity_type == "ARMATURE":
        export_armature_node(f, object)
    elif object.punk_entity_type == "LIGHT":
        export_light(f, object)
    elif object.punk_entity_type == "PORTAL":
        export_portal(f, object)
    elif object.punk_entity_type == "STATIC":
        export_static_mesh_node(f, object)        
    elif object.punk_entity_type == "SKIN":
        export_skin_mesh_node(f, object)
    elif object.punk_entity_type == "NAVI":
        export_navi_mesh(f, object)
    elif object.punk_entity_type == "SOUND_2D":
        export_sound_2d(f, object)
    elif object.punk_entity_type == "SOUND_3D":
        export_sound_3d(f, object)
    elif object.punk_entity_type == "RIGID":
        export_rigid_body(f, object)
    elif object.punk_entity_type == "CHARACTER":
        export_character(f, object)
    elif object.punk_entity_type == "CAMERA":   
        if type(object.data) == bpy.types.Camera:
            export_camera(f, object.data)   
    elif object.punk_entity_type == "COLLISION_MESH":
        export_collision_mesh(f, object)                 
    return     


def export_model(context, filepath, anim_in_separate_file):
    f = open(filepath, 'w')
    for obj in bpy.context.selected_objects:
        export_object(f, obj)
    export_static_meshes(f, bpy.data.meshes)
    export_skin_meshes(f, bpy.data.meshes)
    export_armatures(f, bpy.data.armatures)
    export_materials(f, bpy.data.materials)
    export_actions(f)
    f.close()
    return {'FINISHED'}
    
class ExportPunkModel(bpy.types.Operator, ExportHelper):
    'Exports mesh for Punk Engine'
    bl_idname = "export.punk_model"  
    bl_label = "Export PunkEngine Scene"

    # ExportHelper Mixin classed uses this
    filename_ext = ".pmd"

    filter_glob = StringProperty(default="*.pmd", options = {'HIDDEN'})

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    export_animation = BoolProperty(name="Export animation", description="Export animation in separate .pan animation file", default=True)
    export_type = EnumProperty \
        (name = "Export type", description = "Define what output format is prefered", \
        items = [ ("INDOOR_LOCATION", "Indoor location", "Indoor location", 1), \
                  ("ARMATURE", "Armature", "Armature", 2)])

    @classmethod
    def poll(cls, context):
        return context.active_object != None

    def execute(self, context):
        return export_model(context, self.filepath, self.export_animation)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportPunkModel.bl_idname, text="Export Punk Model")


def register():
    bpy.utils.register_class(ExportPunkModel)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportPunkModel)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
bpy.ops.export.punk_model('INVOKE_DEFAULT')