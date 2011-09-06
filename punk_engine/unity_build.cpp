//////////////////	COMMON	/////////////////////////////
#include "common\attachable_object.cpp"
#include "common\geometry.cpp"
#include "common\logger.cpp"
#include "common\simple_container.cpp"

////////////////////	DRIVER->VIDEO->OPENGL->LINUX
#include "driver\video\opengl\linux\video_driver_linux.cpp"
#include "driver\video\opengl\linux\driver_parameters_linux.cpp"

/////////////////////	win32
#include "driver\video\opengl\win32\driver_parameters_win32.cpp"
#include "driver\video\opengl\win32\video_driver_win32.cpp"

////////////////////	nvtristrip
#include "driver\video\opengl\nvtristrip\nv_tri_strip.cpp"
#include "driver\video\opengl\nvtristrip\nv_tri_strip_objects.cpp"
#include "driver\video\opengl\nvtristrip\vertex_cache.cpp"

///////////////////	driver
#include "driver\video\opengl\vbo.cpp"
#include "driver\video\opengl\texture2d_object.cpp"
#include "driver\video\opengl\material.cpp"
#include "driver\video\opengl\light_manager.cpp"
#include "driver\video\opengl\light.cpp"
#include "driver\video\opengl\glsl_program.cpp"
#include "driver\video\opengl\frame_buffer_with_depth.cpp"
#include "driver\video\opengl\frame_buffer.cpp"
#include "driver\video\opengl\extensions.cpp"
#include "driver\video\opengl\camera.cpp"

///////////	gui
#include "gui\button.cpp"
#include "gui\console.cpp"
#include "gui\edit_box.cpp"
#include "gui\horizontal_slider.cpp"
#include "gui\int_watcher.cpp"
#include "gui\list_box.cpp"
#include "gui\manager.cpp"
#include "gui\static_text_area.cpp"
#include "gui\vertical_scrollbar.cpp"
#include "gui\vertical_slider.cpp"
#include "gui\widget.cpp"

