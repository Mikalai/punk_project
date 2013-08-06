require "qt-support"

_ACTION = _ACTION or "gmake"

-- A solution contains projects, and defines the available configurations
solution "punk_engine"
   configurations { "Debug", "Release" }

-- A project defines one build target
   project "punk_tests"
      kind "ConsoleApp"
      language "C++"
      files { "../../source/tests/**.h", "../../source/tests/**.cpp", "../../source/tests/**.c" }	  
	  
	  buildoptions { "-std=c++11", "-pipe" }
	  links { "punk_engine" }
	  
      configuration "Debug"
         defines { "_DEBUG" }
         flags { "Symbols" }
		 targetdir "../../bin/debug"
 
      configuration "Release"
         defines { "_NDEBUG" }
         flags { "Optimize" }   
		 targetdir "../../bin/release"
		   
   -- A project defines one build target
   project "punk_engine"
      kind "SharedLib"
      language "C++"
      files { "../../source/**.h", "../../source/**.cpp", "../../source/**.c" }	  
	  
	--	Bullet usage
	  newoption { 
		trigger = "physics-api", 
		value = "API",
		description = "Select physics API",
		allowed = {
		  { "no-physics", "Physics simulation disabled" },
		  { "bullet", "Bullet API is used" },
		  { "physix", "NVIDIA Physix API is used" }
		}
	  }
		
	--	Graphics API selection (Not used now)
	  newoption {
	    trigger = "gfxapi",
		value = "API",
		description = "Select 3D graphics API",
		allowed = {
		  { "opengl", "OpenGL" },
		  { "d3d10", "Direct3D 10" },
		  { "d3d11", "Direct3D 11" } 
		}
	  }
				
	-- OpenCL usage
	  newoption { 
	    trigger = "use-opencl",
		description = "Enable OpenCL API usage"
		}
	
	-- Freetype usage
	  newoption {
	    trigger = "use-freetype",
		description = "Enable Freetype 2 usage"
		}
		
	-- Jpeg usage
	  newoption {
	    trigger = "use-jpeg",
		description = "Enable JpegLib usage"
		}
		
	-- Vorbis usage (vorbis and libvorbis)
	  newoption {
	    trigger = "use-vorbis",
		description = "Enable Vorbis stuff usage"
		}
		
	-- Libnoise usage
	  newoption {
	    trigger = "use-noise",
		description = "Enable Libnoise usage"
		}
		
	-- ogg usage
	  newoption { 
	    trigger = "use-ogg",
		description = "Enable ogg lib usage"
		}
		
	--	audio api usage usage
	  newoption {
		trigger = "sndapi",
		value = "API",
		description = "Select audio API",
		allowed = {
		  { "no-sound", "No sound" },
		  { "openal", "OpenAL API" },
		  { "xaudio2", "DirectX XAudio 2 API" }		  
		}
	  }
		
	--	png lib usage
	  newoption {
	    trigger = "use-png",
		description = "SEnable png lib usage" 
		}
		
	  includedirs { "../../source/3rd/",	 
			"../../source/3rd/libvorbis/",
			"../../source/3rd/png/", 
			"../../source/3rd/freetype" }
					
	  excludes { "../../source/3rd/noise/win32/**"
	  , "../../source/3rd/png/example.c"
	  , "../../source/tests/**"
	  , "../../source/tools/**"
	  , "../../source/3rd/freetype/autofit/aflatin2.c"
	  , "../../source/3rd/freetype/base/ftmac.c"
	  , "../../source/3rd/freetype/gzip/infutil.c"
	  , "../../source/3rd/freetype/tools/ftrandom/ftrandom.c"
	  }
	  
	  

	  if not _OPTIONS["physics-api"] then
		_OPTIONS["physics-api"] = "no-physics"
	  end
	  
	  if not _OPTIONS["sndapi"] then
	    _OPTIONS["sndapi"] = "no-sound"
	  end
	  
	  if not _OPTIONS["gfxapi"] then
	    _OPTIONS["gfxapi"] = "opengl"
	  end
	  
	  buildoptions { "-std=c++11", "-pipe" }
	  
	  if os.get() == "windows" then
	      defines ( "_WIN32" )
		  links { "gdi32", "opengl32", "Ole32", "strmiids", "DbgHelp", "OleAut32" }
	  end
	  
	  defines { "PUNK_ENGINE_EXPORTS", "UNICODE", "FT2_BUILD_LIBRARY" }	  
	  
      configuration "Debug"
         defines { "_DEBUG" }
         flags { "Symbols" }
		 targetdir "../../bin/debug"
 
      configuration "Release"
         defines { "_NDEBUG" }
         flags { "Optimize" }   
		 targetdir "../../bin/release"
		 
	  configuration "bullet"
		 excludes { "../../source/3rd/bullet/MiniCL/**"
	  , "../../source/3rd/bullet/BulletSoftBody/**"
	  , "../../source/3rd/bullet/BulletMultiThreaded/**" }
		 includedirs { "../../source/3rd/bullet" }
	     defines { "USE_BULLET_PHYSICS" }
	  
	  configuration "no-physics"
	     excludes { "../../source/3rd/bullet/**" }
		 defines { "USE_SIMPLE_PHYSICS" }
		 
	  configuration "use-opencl"
	    defines { "USE_OPENCL" }
	  
	  configuration "not use-opencl"
	    excludes { "../../source/3rd/cl/**" }
	  
	  configuration "use-freetype"
	    defines { "USE_FREETYPE" }
		
	  configuration "not use-freetype"
	    excludes { "../../source/3rd/freetype/**" }
		
	  configuration "use-jpeg"
	    defines { "USE_JPEG" }
		
		if os.get() == "windows" then	      
		  excludes { "../../source/3rd/jpeg/jmemdos.c"
			, "../../source/3rd/jpeg/jmemmac.c" }
	    end
	  
	  configuration "not use-jpeg"
	    excludes { "../../source/3rd/jpeg/**" }
		
		
	  configuration "use-vorbis"
		defines { "USE_VORBIS" }
	    excludes { "../../source/3rd/libvorbis/psytune.c" }
		
      configuration "not use-vorbis"
		excludes { "../../source/3rd/vorbis/**" }
		excludes { "../../source/3rd/libvorbis/**" }
	  
	  configuration "use-noise"
	    defines { "USE_NOISE" }
		
	  configuration "not use-noise"
		excludes { "../../source/3rd/noise/**" }
		
	  configuration "use-ogg"
		defines { "USE_OGG" }
		
	  configuration "not use-ogg"
	    excludes { "../../source/3rd/ogg/**" }
		
	  configuration "openal"
	    defines { "USE_OPENAL" }
		
	  configuration "xaudio2"
	    excludes { "../../source/3rd/openal/**" }
		
	  configuration "no-sound"
	    excludes { "../../source/3rd/openal/**" }

	  configuration "use-png"
	    defines { "USE_PNG" }
		
	  configuration "not use-png"
	    excludes { "../../source/3rd/png/**" }
	