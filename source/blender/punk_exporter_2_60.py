#mesh.materials['Material'].texture_slots['bump].texture.image.name
import bpy

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty


#
#   export normalse. one normal for one vertex. i still don't know
#   how to realize when one vertex can have some normals depending
#   on the current face
#   
def export_normals(f, mesh):
    start_block(f, "*normals")
    make_offset(f)
    f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("%d\t%f\t%f\t%f\n" % (vertex.index, vertex.normal.x, vertex.normal.y, vertex.normal.z))
    end_block(f)
    return

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
    f.write("%f %f %f %f\n" % (value[0], value[1], value[2], value[3]))
    end_block(f)
    return

#   export single vec4
def export_vec3(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%f %f %f\n" % (value[0], value[1], value[2]))
    end_block(f)
    return

#   export single string
def export_string(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("%s\n" % value)
    end_block(f)
    return

#
#   exports id of vertecies that face consist of
#   face MUST be TRIANGULATED
#
def export_face_vertex_position_id(f, mesh):
    start_block(f, "*vertex_positions_id")
    for face in mesh.faces:
        make_offset(f)
        f.write("%d\t%d\t%d\t%d\n" % (face.index, face.vertices[0], face.vertices[1], face.vertices[2]))
        
    end_block(f)   
    return

text_offset = 0 #used to print data nice

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
        f.write("%f\t%f\t%f\n" % (vertex[0], vertex[1], vertex[2]))
    
    end_block(f)
    return

#
#   export relative location to parent, if no parent consider it as world
#   position
#
def export_location(f, object):
    start_block(f, "*location")
    
    make_offset(f)
    f.write("%f\t%f\t%f\n" % (object.location.x, object.location.y, object.location.z))
    end_block(f)
    return

#
#   export world matrix, if a child it will differ from local
#
def export_world_matrix(f, object):
    start_block(f, "*world_matrix")
    for v in object.matrix_world:  
        make_offset(f)      
        f.write("%f\t%f\t%f\t%f\n" % (v[0], v[1], v[2], v[3]))
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
    make_offset(f)
    f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("%d\t%f\t%f\t%f\n" % (vertex.index, vertex.normal.x, vertex.normal.y, vertex.normal.z))
    end_block(f)
    return

#
#   exports id of vertecies that face consist of
#   face MUST be TRIANGULATED
#
def export_face_vertex_position_id(f, mesh):
    if (mesh == None) or len(mesh.polygons) == 0:
        return;
    
    start_block(f, "*vertex_positions_id")
    for face in mesh.polygons:
        make_offset(f)
        f.write("%d\t%d\t%d\t%d\n" % (face.index, face.vertices[0], face.vertices[1], face.vertices[2]))
        
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

    make_offset(f)
    f.write("%d\n" % len(mesh.polygons))
    
    export_face_vertex_position_id(f, mesh)
    
    end_block(f)
    return

#   export local matrix
#
def export_local_matrix(f, object):
    start_block(f, "*local_matrix")
    for v in object.matrix_local:  
        make_offset(f)      
        f.write("%f\t%f\t%f\t%f\n" % (v[0], v[1], v[2], v[3]))
    end_block(f)
    return    

#   export parent inverse matrix
#
def export_parent_inverse_matrix(f, object):
    start_block(f, "*parent_inverse_matrix")
    for v in object.matrix_parent_inverse:  
        make_offset(f)      
        f.write("%f\t%f\t%f\t%f\n" % (v[0], v[1], v[2], v[3]))
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
    make_offset(f)
    f.write("%d\n" % len(mesh.vertices))
    for vertex in mesh.vertices:
        make_offset(f)
        f.write("%d\t%f\t%f\t%f\n" % (vertex.index, vertex.co.x, vertex.co.y, vertex.co.z)) 

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
    start_block(f, "*material")
    make_offset(f)
    f.write("%s\n" % mesh.materials[0].name)
    end_block(f)
    return
  
#
#   export only mesh
#
def export_mesh(f, object):
    if object.data == None:
        return
    if type(object.data) == bpy.types.Mesh:
        start_block(f, "*mesh")
        export_vertex_position(f, object.data)
        export_normals(f, object.data)
        export_faces(f, object.data)
        export_tex_coords(f, object.data)
        export_mesh_material(f, object.data)
        export_bones_weight(f, object) 
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
        start_block(f, "*armature")    
        
        start_block(f, "*name")
        make_offset(f)
        f.write("%s\n" % armature.name)
        end_block(f)    #*name
        
        for bone in armature.bones:
            #
            #   export bone
            #
            start_block(f, "*bone")
            
            #
            #   write bone name
            #
            
            start_block(f, "*name")
            make_offset(f)
            f.write("%s\n" % bone.name)
            end_block(f)
            
            #
            #   write bone length
            #
            start_block(f, "*length")
            make_offset(f)
            f.write("%f\n" % bone.length)
            end_block(f)
            
            #
            #   write bone parent
            #
            
            if bone.parent != None:
                start_block(f, "*parent")
                make_offset(f);
                f.write("%s\n" % bone.parent.name);
                end_block(f);
            
            #
            #   write bone matrix
            #
            start_block(f, "*local_matrix")
            m = bone.matrix_local
            make_offset(f)
            f.write("%f %f %f %f\n" % (m[0][0], m[0][1], m[0][2], m[0][3]))
            make_offset(f)
            f.write("%f %f %f %f\n" % (m[1][0], m[1][1], m[1][2], m[1][3]))
            make_offset(f)
            f.write("%f %f %f %f\n" % (m[2][0], m[2][1], m[2][2], m[2][3]))
            make_offset(f)
            f.write("%f %f %f %f\n\n" % (m[3][0], m[3][1], m[3][2], m[3][3]))        
            end_block(f)    #*local_matrix
            end_block(f)    #*bone
        end_block(f)    #*armature
    end_block(f)    #*armatures

#
#   export all animation
#    
def export_actions(f):
    start_block(f, "*actions")
    for action in bpy.data.actions:
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
        pos_x = []
        pos_y = []
        pos_z = []
        rot_w = []
        rot_x = []
        rot_y = []
        rot_z = []
        was_pos = 0
        was_rot = 0
        start_block(f, "*frames")
        for curve in action.fcurves:
            #
            #   write bone name that is affected by this curve
            #
            if curve.data_path.rfind("bones") != -1:
                start_block(f, "*bone")
                start_block(f, "*name")
                s = curve.data_path.split('"')
                make_offset(f)
                f.write("%s\n" % s[1])
                end_block(f)
            else:
                start_block(f, "*object")
                start_block(f, "*name")
                make_offset(f)
                f.write("%s\n" % curve.group.name)
                end_block(f)                

            #
            #   write data block
            #
            if curve.data_path.rfind("location") != -1:
                if curve.array_index == 0:
                    start_block(f, "*pos_x")
                elif curve.array_index == 1:
                    start_block(f, "*pos_y")
                elif curve.array_index == 2:
                    start_block(f, "*pos_z")
            if curve.data_path.rfind("rotation_quaternion") != -1:
                if curve.array_index == 0:
                    start_block(f, "*rot_w")
                elif curve.array_index == 1:
                    start_block(f, "*rot_x")
                elif curve.array_index == 2:
                    start_block(f, "*rot_y")
                elif curve.array_index == 3:
                    start_block(f, "*rot_z")

            for key in curve.keyframe_points:
                make_offset(f) 
                f.write("%s %s\n" % (int(key.co[0]), key.co[1])) 
        
            #
            #   end curve block
            #
            end_block(f)
            #
            #   end bone block
            end_block(f)
        end_block(f)    #frames
        end_block(f)    #*action    
    #
    #   end animation block
    #
    end_block(f) #*actions
            
    return
#
#   export bones weights
#
def export_bones_weight(f, object):    
    start_block(f, "*bones_weight")    
    for vert in object.data.vertices:
        for group in object.vertex_groups:
            try:
                ind = vert.index
                #print(ind)
                gr_name = group.name
                #print(gr_name)
                weight = group.weight(ind)
                #print(weight)
                make_offset(f)
                f.write("%d %s %f\n" % (ind, gr_name, weight))
            except:
                pass
                #print("found a vertex that is not in a group")
    end_block(f)
    return

#
#   export all materials
#
def export_materials(f, materials):
    if (len(materials) == 0):
        return
    start_block(f, "*materials")
    for m in materials:
        start_block(f, "*material")        
        
        #   export name
        export_string(f, "*name", m.name)
        
        #   export alpha
        export_float(f, "*alpha", m.alpha)
        
        #   export ambient
        export_float(f, "*ambient", m.ambient)
        
        #   export darkness
        export_float(f, "*darkness", m.darkness)
 
        #   export diffuse color
        export_vec3(f, "*diffuse_color", m.diffuse_color)
        
        #   export diffuse fresnel
        export_float(f, "*diffuse_fresnel", m.diffuse_fresnel)
        
        #   export diffuse fresnel factor
        export_float(f, "*diffuse_fresnel_factor", m.diffuse_fresnel_factor)
        
        #   export diffuse intensity
        export_float(f, "*diffuse_intensity", m.diffuse_intensity)
        
        #   export emit 
        export_float(f, "*emit", m.emit)
        
        #   export mirrot color
        export_vec3(f, "*mirror_color", m.mirror_color)
        
        #   export roughness
        export_float(f, "*roughness", m.roughness)
        
        #   export specular alpha
        export_float(f, "*specular_alpha", m.specular_alpha)
        
        #   export specular color
        export_vec3(f, "*specular_color", m.specular_color)
        
        #   export specular hardness
        export_float(f, "*specular_hardness", m.specular_hardness)
        
        #   export specular intensity
        export_float(f, "*specular_intensity", m.specular_intensity)
        
        #   export specular index of refraction
        export_float(f, "*specular_ior", m.specular_ior)
        
        #   export specular slope
        export_float(f, "*specular_slope", m.specular_slope)
        
        #   export translucency
        export_float(f, "*translucency", m.translucency)
                
        
        try:
            file_name = m.texture_slots[0].texture.image.name
            start_block(f, "*diffuse_map")      
            make_offset(f)            
            f.write("%s\n" % file_name)
            end_block(f)                        
        except:
            print("No texture found")
        
        try:
            file_name = m.texture_slots[1].texture.image.name
            start_block(f, "*normal_map")
            make_offset(f)
            f.write("%s\n" % file_name)
            end_block(f)
        except:
            print("No texture found")
        end_block(f)    
    end_block(f)
    return

#
#   export sound
#
def export_sound(f, object):
    start_block(f, "*sound")

    #   export name
    start_block(f, "*name")    
    make_offset(f)
    f.write("%s\n" % object.data.name)
    end_block(f)
    
    #   export filename
    start_block(f, "*filename")
    make_offset(f)
    f.write("%s\n" % object.data.sound.name)
    end_block(f)
    
    #   export volume
    start_block(f, "*volume")
    make_offset(f)
    f.write("%f\n" % object.data.volume)
    end_block(f)
    
    #   export pitch
    start_block(f, "*pitch")
    make_offset(f)
    f.write("%f\n" % object.data.pitch)
    end_block(f)
    
    #   export max distance
    start_block(f, "*max_distance")
    make_offset(f)
    f.write("%f\n" % object.data.distance_max)
    end_block(f)
    
    #   exoirt ref distance
    start_block(f, "*reference_distance")
    make_offset(f)
    f.write("%f\n" % object.data.distance_reference)
    end_block(f)
    
    #   exoirt inner cone angle in degreese
    start_block(f, "*cone_angle_inner")
    make_offset(f)
    f.write("%f\n" % object.data.cone_angle_inner)
    end_block(f)
    
    #   export outer cone angle
    start_block(f, "*cone_angle_outer")
    make_offset(f)
    f.write("%f\n" % object.data.cone_angle_outer)
    end_block(f)
    
    #   export outer cone volumn
    start_block(f, "*cone_volume_outer")
    make_offset(f)
    f.write("%f\n" % object.data.cone_volume_outer)
    end_block(f)
    
    #   export attenuation
    start_block(f, "*attenuation")
    make_offset(f)
    f.write("%f\n" % object.data.attenuation)
    end_block(f)
    

    end_block(f)
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
#   export lamps from the scene
#
def export_point_lamp(f, lamp):
    start_block(f, "*point_light")
    export_string(f, "*light_type", lamp.type)
    export_string(f, "*name", lamp.name)
    export_vec3(f, "*color", lamp.color)
    export_float(f, "*distance", lamp.distance)
    export_float(f, "*energy", lamp.energy)
    export_string(f, "*fallof_type", lamp.falloff_type)
    export_float(f, "*linear_attenuation", lamp.linear_attenuation)
    export_float(f, "*quadratic_attenuation", lamp.quadratic_attenuation)
    end_block(f);
    
       
#
#   export the whole object with all data i can imaginge
#
def export_object(f, object): 
    start_block(f, "*object")   
    
    export_properties(f, object)
    export_name(f, object)
    
    if object.parent != None:
        export_string(f, "*parent", object.parent.name)
        
    export_bounding_box(f, object)
    export_location(f, object)
    export_world_matrix(f, object)
    export_local_matrix(f, object)
    export_parent_inverse_matrix(f, object)

    if type(object.data) == bpy.types.Mesh:
        export_mesh(f, object)  
        
    if type(object.data) == bpy.types.Speaker:
        export_sound(f, object)
        
    if type(object.data) == bpy.types.PointLamp:
        export_point_lamp(f, object.data)
             
    for child in object.children:
        export_object(f, child)    
           
    end_block(f)
    return     


def export_model(context, filepath, anim_in_separate_file):
    f = open(filepath, 'w')
    for obj in bpy.context.selected_objects:
        export_object(f, obj)
    export_materials(f, bpy.data.materials)
    export_bones(f)    
    export_actions(f)
    f.close()
    return {'FINISHED'}

class ExportPunkModel(bpy.types.Operator, ExportHelper):
    'Exports mesh for Punk Engine'
    bl_idname = "export.punk_model"  
    bl_label = "Export Punk Model"

    # ExportHelper mixin classed uses this
    filename_ext = ".pmd"

    filter_glob = StringProperty(default="*.pmd", options = {'HIDDEN'})

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    export_animation = BoolProperty(name="Export animation", description="Export animation in separate .pan animation file", default=True)


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