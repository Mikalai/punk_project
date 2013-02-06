import bpy
from bpy.types import Panel
from rna_prop_ui import PropertyPanel
   
class OBJECT_PT_punk_engine_tools(Panel):
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "object"
    bl_label = "Punk Engine Tools"

    def draw(self, context):
        layout = self.layout

        ob = context.object
            
        layout.prop(ob, "punk_entity_type")
                
        if (ob.punk_entity_type == 'STATIC'):
            layout.prop(text = "Triangles count", data = ob.data, property = "polygons")
            layout.prop(ob, "name", expand = True)
            layout.prop(ob.data.materials[0], "diffuse_color", expand = True)
        elif ob.punk_entity_type == 'SKIN':
            layout.prop(text = "Triangles count", data = ob.data, property = "polygons")
            layout.prop(ob, "name", expand = True)
            layout.prop(ob.data.materials[0], "diffuse_color", expand = True)
        elif ob.punk_entity_type == 'NAVI':
            layout.prop(text = "Triangles count", data = ob.data, property = "polygons")
        elif ob.punk_entity_type == 'SOUND_3D':
            layout.prop(ob, "name", expand = True)
            speaker = ob.data
    
            split = layout.split(percentage=0.75)
    
            split.template_ID(speaker, "sound", open="sound.open_mono")
            split.prop(speaker, "muted")
    
            row = layout.row()
            row.prop(speaker, "volume")
            row.prop(speaker, "pitch")
            
            split = layout.split()

            col = split.column()
            col.label("Volume:")
            col.prop(speaker, "volume_min", text="Minimum")
            col.prop(speaker, "volume_max", text="Maximum")
            col.prop(speaker, "attenuation")
    
            col = split.column()
            col.label("Distance:")
            col.prop(speaker, "distance_max", text="Maximum")
            col.prop(speaker, "distance_reference", text="Reference")
    
            split = layout.split()

            col = split.column()
            col.label("Angle:")
            col.prop(speaker, "cone_angle_outer", text="Outer")
            col.prop(speaker, "cone_angle_inner", text="Inner")
    
            col = split.column()
            col.label("Volume:")
            col.prop(speaker, "cone_volume_outer", text="Outer")
            
        elif ob.punk_entity_type == 'SOUND_2D':
            layout.prop(ob, "name", expand = True)
            speaker = ob.data
    
            split = layout.split(percentage=0.75)
    
            split.template_ID(speaker, "sound", open="sound.open_mono")
            split.prop(speaker, "muted")
    
            row = layout.row()
            row.prop(speaker, "volume")
            row.prop(speaker, "pitch")
        elif ob.punk_entity_type == 'RIGID':
            layout.prop(ob, "name")
            layout.prop(ob, "punk_mass")
        elif ob.punk_entity_type == 'PORTAL':
            layout.prop(ob, "name")     
        elif ob.punk_entity_type == 'LOCATION_INDOOR':
            layout.prop(ob, "name")               
        elif ob.punk_entity_type == 'ARMATURE':
            layout.prop(ob, "name")
            layout.prop(ob, "armature_type")
        elif ob.punk_entity_type == 'LIGHT':
            light = ob.data
            layout.prop(ob, "name")
            layout.prop(light, "type")
            layout.prop(light, "color")
            layout.prop(light, "distance")
            layout.prop(light, "energy")
            layout.prop(light, "fallof_type")
            layout.prop(light, "linear_attenuation")
            layout.prop(light, "quadratic_attenuation")     
        elif ob.punk_entity_type == 'CHARACTER':
            empty = ob.data
            layout.prop(ob, "name")
        elif ob.punk_entity_type == 'COLLISION_MESH':
            empty = ob.data
            layout.prop(ob, "name")
                 

def register():  
    bpy.types.Object.punk_mass = bpy.props.FloatProperty \
        (name = "Mass", description = "Mass of the rigid body")

    bpy.types.Object.armature_type = bpy.props.EnumProperty \
        (name = "Armature type", description = "Armature type", \
        items = [ ("HUMAN_MALE", "Human Male", "Human male", 1), \
                  ("HUMAN_FEMALE", "Human Female", "Humane female", 2)])
            
    bpy.types.Object.punk_entity_type = bpy.props.EnumProperty \
        (name = "Property", description = "Engine entity type", \
        items = [("STATIC", "Static",   "Static object. Has geometry", 1), \
                 ("NAVI",   "Navigation Mesh", "Navigation mesh",      2), \
                 ("SOUND_2D",  "2D Sound", "Sound",                    3), \
                 ("SOUND_3D",  "3D Sound", "Sound",                    4), \
                 ("RIGID",  "Rigid Body", "Sound",                     5), \
                 ("PORTAL", "Portal", "Scene portal",                  6), \
                 ("LIGHT", "Light", "Scene light",                     7), \
                 ("LOCATION_INDOOR", "Indoor location", "Interior location", 8), \
                 ("CHARACTER", "Character", "Character armature and skin", 9), \
                 ("CAMERA", "Camera", "A camera that can be used in game", 10),\
                 ("TRANSFORM", "Transform", "A simple transorm",           11),\
                 ("ARMATURE", "Armature", "Animated armature",             12),\
                 ("SKIN", "Skin",   "Skin object. Has geometry",           13),\
                 ("COLLISION_MESH", "Collision mesh", "Collision mesh",    14),\
                 ("SMALL_SLOT", "Small slot", "Small slot",                15),\
                 ("MIDDLE_SLOT", "Middle slot", "Middles slot",            16),\
                 ("LARGE_SLOT", "Large slot", "Large slot",                17),\
                 ("COLD_WEAPON", "Cold weapon", "Cold weapon",             18)])
                         
def unregister():
    del bpy.types.Object.punk_entity_type
    del bpy.types.Object.armature_type
    del bpy.types.Object.punk_mass
    
if __name__ == "__main__":  # only for live edit.
    register()
    bpy.utils.register_module(__name__)