import bpy
import copy

text_offset = 0 #used to print data nice
path = ""
used_entities = {}

def push_entity(type, object):
    if not(type in used_entities.keys()):
        used_entities[type] = set()
    print("Add " + type + " " + object.name)
    used_entities[type].add(object)
    return


#   export single float
def export_float(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0}\n".format(value))
    end_block(f)
    return

#   export single vec4
def export_vec4(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0} {1} {2} {3}\n".format(value[0], value[1], value[2], value[3]))
    end_block(f)
    return

#   export single vec4
def export_vec3(f, name, value):
    start_block(f, name)
    make_offset(f)
    f.write("{0} {1} {2}\n".format(value[0], value[1], value[2]))
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
        f.write("{0} {1} {2} {3}\n".format(v[0], v[1], v[2], v[3]))
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
        f.write("{0} {1} {2}\n".format(vertex[0], vertex[1], vertex[2]))
    
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
        f.write("{0} {1} {2} {3}\n".format(vertex.index, vertex.normal.x, vertex.normal.y, vertex.normal.z))
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
        f.write("{0} {1} {2} {3}\n".format(vertex.index, vertex.co.x, vertex.co.y, vertex.co.z))

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
        f.write("{0} {1} {2} {3}\n".format(face.index, face.vertices[0], face.vertices[1], face.vertices[2]))
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
        f.write("{0} {1} {2} {3}\n".format(face.index, face.normal[0], face.normal[1], face.normal[2]))
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
                f.write("{0} {1} {2}\n",format(ind, gr_name, weight))
            except:
                pass
                #print("found a vertex that is not in a group")
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
            f.write("{0} {1} {2} {3} {4} {5} {6} {7}\n".format(data[3*face].uv[0], data[3*face].uv[1], data[3*face+1].uv[0], data[3*face+1].uv[1], data[3*face+2].uv[0], data[3*face+2].uv[1], 0, 0))
            
        end_block(f)   
        end_block(f)
    return

def export_texture_slot(f, slot):
    start_block(f, "*texture_slot")
    try:
        export_vec3(f, "*scale", slot.scale)
        s = slot.texture.image.filepath
        export_string(f, "*image", s[s.rfind('/')+1:])
        if slot.use_map_color_diffuse:
            export_float(f, "*diffuse_map", slot.diffuse_color_factor)   
        if slot.use_map_normal:
            export_float(f, "*normal_map", slot.normal_factor)
        if slot.use_map_specular:
            export_float(f, "*specular_intensity_map", slot.specular_factor)
        end_block(f)    #*texture
    except:
        print("Failed to export texture")
    return

def export_material(f, m):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = m.name + ".material"
    print(file)
    f = open(file, "w")
    f.write("MATERIALTEXT\n")
    start_block(f, m.name)
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

    for slot in m.texture_slots:
        try:            
            if slot.texture.image != None:
                export_texture_slot(f, slot)
        except:
            print("No texture found")
                        
    end_block(f)  # *material
    f.close()        
    
    text_offset = old  
    return 

#   export all materials
def export_materials(f):
    if not ("*material" in used_entities.keys()):
        return        
    for material in used_entities["*material"]:
        if material != None:
            export_material(f, material)
    return

def export_static_mesh(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".static"    
    print("Export static mesh to " + file)
    f = open(file, "w")
    f.write("STATICMESHTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    export_mat4(f, "*world_matrix", object.matrix_world)
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    export_tex_coords(f, mesh)
    if len(mesh.materials) != 0:
        export_material(f, bpy.data.materials[mesh.materials[0].name])        
    end_block(f)    #   skin_mesh        
    f.close()        
    
    text_offset = old    
    return
    
def export_static_meshes(f): 
    if not ("*static_mesh" in used_entities.keys()):
        return    
    for object in used_entities["*static_mesh"]:
        data = object.data
        if data != None:
            export_static_mesh(f, object)
    return

def export_suns(f):
    if not ("*sun" in used_entities.keys()):
        return
    
    for object in used_entities["*sun"]:
        data = object.data
        if data != None:
            export_sun(f, object)
    return

def export_sun(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".sun"    
    f = open(file, "w")
    f.write("SUNTEXT\n")
    sun = object.data
    start_block(f, sun.name)
    export_float(f, "*energy", sun.energy)
    export_vec3(f, "*color", sun.color)
    end_block(f)    #   skin_mesh        
    f.close()
    
    text_offset = old    
    return

def export_navi_mesh(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".navi_mesh"    
    print("Export static mesh to " + file)
    f = open(file, "w")
    f.write("NAVIMESHTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    export_mat4(f, "*world_matrix", object.matrix_world)
    export_vertex_position(f, mesh)
    export_normals(f, mesh)
    export_faces(f, mesh)
    end_block(f)    #   skin_mesh        
    f.close()        
    
    text_offset = old    
    return
    
def export_navi_meshes(f): 
    if not ("*navi_mesh" in used_entities.keys()):
        return    
    for object in used_entities["*navi_mesh"]:
        data = object.data
        if data != None:
            export_navi_mesh(f, object)
    return

def export_terrain(f, object):
    export_static_mesh(f, object)
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".terrain"    
    f = open(file, "w")
    f.write("TERRAINTEXT\n")    
    mesh = object.data
    start_block(f, mesh.name)
    export_string(f, "*mesh", mesh.name + ".static")
    end_block(f)    #   terrain        
    f.close()        
    
    text_offset = old    
    return
    
def export_terrains(f): 
    if not ("*terrain" in used_entities.keys()):
        return    
    for object in used_entities["*terrain"]:
        data = object.data
        if data != None:
            export_terrain(f, object)
    return

def export_river(f, object):
    export_static_mesh(f, object)
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".river"    
    f = open(file, "w")
    f.write("RIVERTEXT\n")
    mesh = object.data
    start_block(f, mesh.name)
    export_string(f, "*mesh", mesh.name + ".static")    
    export_float(f, "*flow_speed", 1)
    export_vec3(f, "*flow_direction", [1, 0, 0])
    end_block(f)    #   river            
    f.close()        
    
    text_offset = old    
    return
    
def export_rivers(f): 
    if not ("*river" in used_entities.keys()):
        return    
    for object in used_entities["*river"]:
        data = object.data
        if data != None:
            export_river(f, object)
    return

def export_path(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".path"    
    f = open(file, "w")
    f.write("PATHTEXT\n")
    curve = object.data    
    start_block(f, curve.name)
    for spline in curve.splines:
        start_block(f, "*spline")
        for point in spline.points:
            start_block(f, "*point")
            export_float(f, "*weight", point.weight)
            export_vec4(f, "*position", point.co)
            end_block(f)
        end_block(f)
    end_block(f)    #   path
    f.close()        
    
    text_offset = old    
    return
    
def export_paths(f): 
    if not ("*path" in used_entities.keys()):
        return    
    for object in used_entities["*path"]:
        data = object.data
        if data != None:
            export_path(f, object)
    return

def export_camera(f, object):
    global text_offset
    old = text_offset 
    text_offset = 0
    
    file = object.data.name + ".camera"    
    f = open(file, "w")
    f.write("CAMERATEXT\n")
    
    camera = object.data
    start_block(f, "*camera")
    export_string(f, "*name", camera.name)
    export_string(f, "*type", camera.type)
    export_float(f, "*fov", camera.angle)
    export_float(f, "*near", camera.clip_start)
    export_float(f, "*far", camera.clip_end)
    export_float(f, "*focus", camera.dof_distance)
    export_float(f, "*ortho_scale", camera.ortho_scale)   
    end_block(f)
    
    f.close()        
    
    text_offset = old    
    return

def export_cameras(f):
    if not ("*camera" in used_entities.keys()):
        return
    for object in used_entities["*camera"]:
        data = object.data
        if data != None:
            export_camera(f, object)
    return