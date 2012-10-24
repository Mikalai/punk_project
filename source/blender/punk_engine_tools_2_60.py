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
                 

def register():  
    bpy.types.Object.punk_mass = bpy.props.FloatProperty \
        (name = "Mass", description = "Mass of the rigid body")
        
    bpy.types.Object.punk_entity_type = bpy.props.EnumProperty \
        (name = "Property", description = "Engine entity type", \
        items = [("STATIC", "Static",   "Static object. Has geometry", 1), \
                 ("NAVI",   "Navigation Mesh", "Navigation mesh",      2), \
                 ("SOUND_2D",  "2D Sound", "Sound",                    3), \
                 ("SOUND_3D",  "3D Sound", "Sound",                    4), \
                 ("RIGID",  "Rigid Body", "Sound",                    5)])
                         
def unregister():
    del bpy.types.Object.punk_entity_type
    del bpy.types.Object.punk_mass
    
if __name__ == "__main__":  # only for live edit.
    register()
    bpy.utils.register_module(__name__)