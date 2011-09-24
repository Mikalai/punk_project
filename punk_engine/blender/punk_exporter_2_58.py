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
    start_block(f, "*vertex_positions_id")
    for face in mesh.faces:
        make_offset(f)
        f.write("%d\t%d\t%d\t%d\n" % (face.index, face.vertices[0], face.vertices[1], face.vertices[2]))
        
    end_block(f)   
    return
#
#   export vertex id for faces. it is practicaly enough. but
#   it is needed more info later. 
#
def export_faces(f, mesh):
    start_block(f, "*faces")

    make_offset(f)
    f.write("%d\n" % len(mesh.faces))
    
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
#
#   exports vertex position for current mesh with no tranformation
#   applied in the scene
#
def export_vertex_position(f, mesh):        
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
    if (len(mesh.uv_textures) == 0):
        return
    
    start_block(f, "*tex_coord")
        
    #
    #   uv1 uv2 uv3 uv4
    #
    for data in mesh.uv_textures[0].data:
        make_offset(f)   
        f.write("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" % (data.uv1[0], data.uv1[1], data.uv2[0], data.uv2[1], data.uv3[0], data.uv3[1], data.uv4[0], data.uv4[1]))
        
        
    end_block(f)
    return

#
#   export mesh material
#
def export_mesh_material(f, mesh):
    start_block(f, "*material")
    make_offset(f)
    f.write("%s\n" % mesh.materials[0].name)
    end_block(f)
    return
  
#
#   export only mesh
#
def export_mesh(f, mesh):
    start_block(f, "*mesh")
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    export_tex_coords(f, mesh)
    export_mesh_material(f, mesh)
    end_block(f)
    return

#
#   export bones
#
def export_bones(f, object):
    armature = object.find_armature()
    if armature == None:
        return
    start_block(f, "*bones")    
    make_offset(f)
    f.write("%d\n" % len(armature.data.bones))
    for bone in armature.data.bones:
        #
        #   export bone
        #
        start_block(f, "*bone")
        
        #
        #   write bone name
        #
        
        start_block(f, "*name")
        make_offset(f);
        f.write("%s\n" % bone.name);
        end_block(f);
        
        #
        #   write bone parent
        #
        
        if bone.parent != None:
            start_block(f, "*parent")
            make_offset(f);
            f.write("%s\n" % bone.parent.name);
            end_block(f);
        
        #
        #   write local matrix
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
        end_block(f)
        
        #
        #   write bone matrix
        #
        
        start_block(f, "*bone_matrix")
        m = bone.matrix
        make_offset(f)
        f.write("%f %f %f %f\n" % (m[0][0], m[0][1], m[0][2], 0))
        make_offset(f)
        f.write("%f %f %f %f\n" % (m[1][0], m[1][1], m[1][2], 0))
        make_offset(f)
        f.write("%f %f %f %f\n" % (m[2][0], m[2][1], m[2][2], 0))
        make_offset(f)
        f.write("%f %f %f %f\n\n" % (0, 0, 0, 1))        
        end_block(f)
        
        #
        #   to global transform
        #
        start_block(f, "*gimbal_transform")
        m = m.to_3x3()
        m[0] = bone.x_axis;
        m[1] = bone.y_axis;
        m[2] = bone.z_axis;
        m.invert()
        m.transpose()
        quat = m.to_quaternion().normalized()
        make_offset(f)
        f.write("%f %f %f %f\n" % (quat.w, quat.x, quat.y, quat.z))
        end_block(f)
        
        end_block(f)
    end_block(f)
    #
    #   export all animation
    #
    for action in bpy.data.actions:
        start_block(f, "*skeleton_animation")
        make_offset(f)
        f.write("%s\n" % action.name)
        start = int(action.frame_range[0])
        end = int(action.frame_range[1])
        make_offset(f)
        f.write("%d %d\n" % (start, end))
        pos_x = []
        pos_y = []
        pos_z = []
        rot_w = []
        rot_x = []
        rot_y = []
        rot_z = []
        was_pos = 0
        was_rot = 0
        for curve in action.fcurves:
            #
            #   write bone name that is affected by this curve
            #
            if curve.data_path.rfind("bones") == -1:
                continue
            s = curve.data_path.split('"')
            start_block(f, "*bone")
            start_block(f, "*name")
            make_offset(f)
            f.write("%s\n" % s[1])
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
            
         #
         #   end animation block
         #
        end_block(f);
            
    return
#
#   export bones weights
#
def export_bones_weight(f, object):    
    start_block(f, "*bones_weight")    
    mesh = object.data
    for vert in object.data.vertices:
        for group in object.vertex_groups:
            print(vert.index)
            print(group.index)
            try:
                w = group.weight(vert.index)
                make_offset(f);
                f.write("%d %s %f\n" % (vert.index, group.name, w))
            except:
                pass
    end_block(f)
    return

#
#   export all materials
#
def export_materials(f, materials):
    start_block(f, "*materials")
    for m in materials:
        diffuse = []
        normal = []
        
        try:
            diffuse = m.texture_slots['diffuse']
            normal = m.texture_slots['normal']
        except:
            continue
        
        start_block(f, "*name")
        make_offset(f)
        f.write("%s\n" % m.name)
        end_block(f)
        
        start_block(f, "*diffuse_map")
        make_offset(f)
        f.write("%s\n" % diffuse.texture.image.name)
        end_block(f)
        
        start_block(f, "*normal_map")
        make_offset(f)
        f.write("%s\n" % normal.texture.image.name)
        end_block(f)
    end_block(f)
    return


#
#   export the whole object with all data i can imaginge
#
def export_object(f, object): 
    start_block(f, "*object")   
    
    export_name(f, object)
    export_bounding_box(f, object)
    export_location(f, object)
    export_world_matrix(f, object)
    export_local_matrix(f, object)
    export_mesh(f, object.data)
    export_bones_weight(f, object)
    export_bones(f, object)
    
    for child in object.children:
        export_object(f, child)
        
    export_materials(f, bpy.data.materials)
    end_block(f)
    return     


def export_model(context, filepath, anim_in_separate_file):
    f = open(filepath, 'w')
    for obj in bpy.context.selected_objects:
        export_object(f, obj)
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