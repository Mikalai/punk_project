#
#add bounding sphere
#

import bpy

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
    f.write("%s\n" % title)
    make_offset(f)
    f.write("{\n")
    inc_offset()
    make_offset(f)
    return

def end_block(f):
    dec_offset()
    make_offset(f)
    f.write("}\n")
    return

def export_name(f, object):
    start_block(f, "*object_name")
    
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
        f.write("%f\t%f\t%f\n" % (v.x, v.y, v.z))
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
        f.write("%f\t%f\t%f\n" % (v.x, v.y, v.z))
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
#   export only mesh
#
def export_mesh(f, mesh):
    start_block(f, "*mesh")
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    export_tex_coords(f, mesh)
    
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
    for child in object.children:
        export_object(f, child)

    end_block(f)
    return                        
    
def export_punk_mesh(context, filepath, export_position):
    print("running write_some_data...")
    f = open(filepath, 'w')
    for obj in bpy.context.selected_objects:
        export_object(f, obj)
    f.close()
    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from io_utils import ExportHelper

from bpy.props import *


class ExportSomeData(bpy.types.Operator, ExportHelper):
    '''This appiers in the tooltip of the operator and in the generated docs.'''
    bl_idname = "export.punk_mesh_data" # this is important since its how bpy.ops.export.some_data is constructed
    bl_label = "Punk Mesh Export"
    
    # ExportHelper mixin class uses this
    filename_ext = ".pm"

    filter_glob = StringProperty(default="*.pm", options={'HIDDEN'})

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before cal
    
    export_texcoord = BoolProperty(name="Texture", description="Export texture coordinations (u, v)", default=True)
    
    export_tangent = BoolProperty(name="Tangents", description="Export vertex tangent (tx, ty, tz)", default=True)
    
    export_binormals = BoolProperty(name="Binormals", description="Export vertex binormal (bx, by, bz)", default=True)
    
    export_normals = BoolProperty(name="Normals", description="Export vertex normal (nx,ny,nz)", default=True)
    
    export_position = BoolProperty(name="Position", description="Export vertex position (x,y,z)", default= True)
    
#    collection = CollectionProperty(items=["qwer","2","3"]);
    
    export_hierarchy = BoolProperty(name=":Hierarchy", description="Export with children", default = True)
                
  #  use_setting = BoolProperty(name="Example Boolean", description="Example Tooltip", default= True)

    #type = bpy.props.EnumProperty(items=(('OPT_A', "First Option", "Description one"), ('OPT_B', "Second Option", "Description two.")),
     #                   name="Example Enum",
     #                   description="Choose between two items",
     #                   default='OPT_A')

    @classmethod
    def poll(cls, context):
        return context.active_object != None

    def execute(self, context):
        return export_punk_mesh(context, self.filepath, 0)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="Text Export Operator")


def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export.some_data('INVOKE_DEFAULT')