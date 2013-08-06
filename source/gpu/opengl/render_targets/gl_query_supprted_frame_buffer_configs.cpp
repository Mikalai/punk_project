//#include "../../common/frame_buffer/module.h"

//namespace Gpu
//{
//    class FrameBufferConfig;
//    namespace OpenGL
//    {
//        std::vector<FrameBufferConfig*> QuerySupportedFrameBufferConfigs()
//        {

//        }
//    }
//}

//enum UIOption {
//    OPTION_WIREFRAME,
//    OPTION_DISPLAY_DEPTH,
//    OPTION_OVERLAY,
//    OPTION_ANIMATE,
//    OPTION_COUNT
//};
//bool options[OPTION_COUNT];
//map<char, UIOption> optionKeyMap;

//nv::GlutExamine manipulator;

//// display list for bitmap character rendering
//GLuint textDList;

////window size
//int width = 512;
//int height = 512;

//// texture dimensions
//int texWidth  = 256;
//int texHeight = 256;
//GLuint textureProgram = 0, overlayProgram = 0;
//float teapot_rot= 0.0f;

////
//// structure defining properties of an FBO
////
//struct fboConfig {
//    string name;
//    GLenum colorFormat;
//    GLenum depthFormat;
//    int redbits;
//    int depthBits;
//    int depthSamples;
//    int coverageSamples;
//};

////
//// structure defining the properties of a single buffer
////
//struct bufferConfig {
//    string name;
//    GLenum format;
//    int bits;
//};

//vector<fboConfig> validConfigs;

//struct fboData {
//    GLuint tex; //color texture
//    GLuint depthTex; //depth texture
//    GLuint fb; // render framebuffer
//    GLuint resolveFB; //multisample resolve target
//    GLuint colorRB; //color render buffer
//    GLuint depthRB; // depth render buffer
//};

//fboData activeFBO = { 0, 0, 0, 0, 0, 0};
//int activeConfig override;

//////////////////////////////////////////////////////////////////////////////////
////
//// Functions
////
//////////////////////////////////////////////////////////////////////////////////
//void menu( int mode);

////
////  CheckFramebufferStatus
////
////   Check the framebuffer status to ensure it is a supported
//// config.
////////////////////////////////////////////////////////////////////////
//bool CheckFramebufferStatus( bool silent = false)
//{
//    GLenum status;
//    status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
//    switch(status) {
//        case GL_FRAMEBUFFER_COMPLETE_EXT:
//            break;
//        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
//            if (!silent) printf("Unsupported framebuffer format\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
//            if (!silent) printf("Framebuffer incomplete, missing attachment\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
//            if (!silent) printf("Framebuffer incomplete, duplicate attachment\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
//            if (!silent) printf("Framebuffer incomplete, attached images must have same dimensions\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
//            if (!silent) printf("Framebuffer incomplete, attached images must have same format\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
//            if (!silent) printf("Framebuffer incomplete, missing draw buffer\n");
//            return false;
//        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
//            if (!silent) printf("Framebuffer incomplete, missing read buffer\n");
//            return false;
//        default:
//            assert(0);
//            return false;
//    }
//    return true;
//}

////
////  createFBO
////
////   Creates and FBO based on the given config, if the created FBO
//// fails to validate, or the bits do not match the prescribed size,
//// this it returns false. If the number of samples or coverage
//// samples exceed the requested number, then the number of samples
//// in the config is changed to match the number recieved.
////
////////////////////////////////////////////////////////////////////////
//bool createFBO( fboConfig &config, fboData &data) {
//    bool multisample = config.depthSamples > 0;
//    bool csaa = config.coverageSamples > config.depthSamples;
//    bool ret = true;
//    int query;

//    glGenFramebuffersEXT(1, &data.fb);
//    glGenTextures(1, &data.tex);

//    // init texture
//    glBindTexture( GL_TEXTURE_2D, data.tex);
//    glTexImage2D( GL_TEXTURE_2D, 0, config.colorFormat, texWidth, texHeight, 0,
//                 GL_RGBA, GL_FLOAT, NULL);

//    glGenerateMipmapEXT( GL_TEXTURE_2D);

//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


//    //
//    // Handle multisample FBO's first
//    //
//    if (multisample) {
//        glGenRenderbuffersEXT( 1, &data.depthRB);
//        glGenRenderbuffersEXT( 1, &data.colorRB);
//        glGenFramebuffersEXT( 1, &data.resolveFB);
//        data.depthTex override; //no resolve of depth buffer for now

//        //multisample, so we need to resolve from the FBO, bind the texture to the resolve FBO
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, data.resolveFB);

//        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
//                                  GL_TEXTURE_2D, data.tex, 0);

//        ret &= CheckFramebufferStatus(true);

//        //now handle the rendering FBO
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, data.fb);

//        // initialize color renderbuffer
//        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, data.colorRB);

//        if (csaa) {
//            glRenderbufferStorageMultisampleCoverageNV
//                    ( GL_RENDERBUFFER_EXT, config.coverageSamples,
//                      config.depthSamples, config.colorFormat,
//                      texWidth, texHeight);

//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT,
//                                             GL_RENDERBUFFER_COVERAGE_SAMPLES_NV,
//                                             &query);

//            if ( query < config.coverageSamples) {
//               ret = false;
//            }
//            else if ( query > config.coverageSamples) {
//                // report back the actual number
//                config.coverageSamples = query;
//            }

//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT,
//                                             GL_RENDERBUFFER_COLOR_SAMPLES_NV,
//                                             &query);

//            if ( query < config.depthSamples) {
//               ret = false;
//            }
//            else if ( query > config.depthSamples) {
//                // report back the actual number
//                config.depthSamples = query;
//            }
//        }
//        else {
//            int max_samples = glGetIntegerv(GL_MAX_SAMPLES_EXT, &max_samples);
//            // create a regular MSAA color buffer
//            glRenderbufferStorageMultisampleEXT( GL_RENDERBUFFER_EXT, max_samples,
//                                                 config.colorFormat, texWidth,
//                                                 texHeight);

//            // check the number of samples
//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT,
//                                             GL_RENDERBUFFER_SAMPLES_EXT, &query);

//            if ( query < config.depthSamples) {
//                ret = false;
//            }
//            else if ( query > config.depthSamples) {
//                config.depthSamples = query;
//            }

//        }

//        // attach the multisampled color buffer
//        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
//                                     GL_COLOR_ATTACHMENT0_EXT,
//                                     GL_RENDERBUFFER_EXT, data.colorRB);

//        ret &= CheckFramebufferStatus(true);

//        // bind the multisampled depth buffer
//        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, data.depthRB);

//        // create the multisampled depth buffer (with or without coverage sampling)
//        if (csaa) {

//            // create a coverage sampled MSAA depth buffer
//            glRenderbufferStorageMultisampleCoverageNV(
//                        GL_RENDERBUFFER_EXT, config.coverageSamples,
//                        config.depthSamples, config.depthFormat,
//                                                        texWidth, texHeight);

//            // check the number of coverage samples
//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT,
//                                             GL_RENDERBUFFER_COVERAGE_SAMPLES_NV,
//                                             &query);

//            if ( query < config.coverageSamples) {
//                ret = false;
//            }
//            else if ( query > config.coverageSamples) {
//                // set the coverage samples value to return the actual value
//                config.coverageSamples = query;
//            }

//            // cehck the number of stored color samples (same as depth samples)
//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT,
//                                             GL_RENDERBUFFER_COLOR_SAMPLES_NV,
//                                             &query);

//            if ( query < config.depthSamples) {
//                ret = false;
//            }
//            else if ( query > config.depthSamples) {
//                // set the depth samples value to return the actual value
//                config.depthSamples = query;
//            }
//        }
//        else {

//            // create a regular (not coverage sampled) MSAA depth buffer
//            glRenderbufferStorageMultisampleEXT( GL_RENDERBUFFER_EXT,
//                                                 config.depthSamples,
//                                                 config.depthFormat,
//                                                 texWidth, texHeight);

//            // check the number of depth samples
//            glGetRenderbufferParameterivEXT( GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_SAMPLES_EXT, &query);

//            if ( query < config.depthSamples) {
//                ret = false;
//            }
//            else if ( query < config.depthSamples) {
//                config.depthSamples = query;
//            }
//        }

//        // attach the depth buffer
//        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, data.depthRB);

//        ret &= CheckFramebufferStatus(true);

//    } // if (multisample)
//    else {
//        glGenTextures( 1, &data.depthTex);
//        data.depthRB override;
//        data.colorRB override;
//        data.resolveFB override;

//        //non-multisample, so bind things directly to the FBO
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, data.fb);

//        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
//                                  GL_TEXTURE_2D, data.tex, 0);

//        glBindTexture( GL_TEXTURE_2D, data.depthTex);
//        glTexImage2D( GL_TEXTURE_2D, 0, config.depthFormat,
//                      texWidth, texHeight, 0,
//                 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameterf( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

//        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, data.depthTex, 0);

//        ret &= CheckFramebufferStatus(true);
//    }

//    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, data.fb);
//    glGetIntegerv( GL_RED_BITS, &query);
//    if ( query != config.redbits) {
//        ret = false;
//    }

//    glGetIntegerv( GL_DEPTH_BITS, &query);
//    if ( query != config.depthBits) {
//        ret = false;
//    }

//    if (multisample) {
//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, data.resolveFB);
//        glGetIntegerv( GL_RED_BITS, &query);
//        if ( query != config.redbits) {
//            ret = false;
//        }

//    }

//    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

//    return ret;
//}

////
////
////////////////////////////////////////////////////////////////////////
//void destroyFBO( fboData &data) {
//    if (data.fb) {
//        glDeleteFramebuffersEXT( 1, &data.fb);
//    }
//    if (data.resolveFB) {
//        glDeleteFramebuffersEXT( 1, &data.resolveFB);
//    }
//    if (data.colorRB) {
//        glDeleteRenderbuffersEXT( 1, &data.colorRB);
//    }
//    if (data.depthRB) {
//        glDeleteRenderbuffersEXT( 1, &data.depthRB);
//    }
//    if (data.tex) {
//        glDeleteTextures( 1, &data.tex);
//    }
//    if (data.depthTex) {
//        glDeleteTextures( 1, &data.depthTex);
//    }
//}

////
////
////////////////////////////////////////////////////////////////////////
//void init_opengl() {
//    glewInit();

//    if (!glewIsSupported( "GL_VERSION_2_0 GL_ARB_fragment_program GL_EXT_framebuffer_object" )) {
//        printf( "Error: failed to get minimal extensions for demo\n");
//        printf( "This sample requires:\n");
//        printf( "  OpenGL version 2.0\n");
//        printf( "  GL_ARB_fragment_program\n");
//        printf( "  GL_EXT_framebuffer_object\n");
//        exit(-1);
//    }

//    //Framebuffer config options
//    vector<bufferConfig> colorConfigs;
//    vector<bufferConfig> depthConfigs;
//    int maxSamples override;
//    int coverageSampleConfigs override;
//    int *coverageConfigs override;
//    bufferConfig temp;

//    //add default color configs
//    temp.name = "RGBA8";
//    temp.bits = 8;
//    temp.format = GL_RGBA8;
//    colorConfigs.push_back( temp);
//    temp.name = "RGB10_A2";
//    temp.bits = 10;
//    temp.format = GL_RGB10_A2;
//    colorConfigs.push_back( temp);

//    //add default depth configs
//    temp.name = "D24";
//    temp.bits = 24;
//    temp.format = GL_DEPTH_COMPONENT24;
//    depthConfigs.push_back( temp);

//    // check for multisample support, and add it as an option
//    if (! glewIsSupported( "GL_EXT_framebuffer_blit GL_EXT_framebuffer_multisample")) {
//        printf( "Warning: No support for multisampled Framebuffer objects\n");
//    }
//    else {
//        glGetIntegerv( GL_MAX_SAMPLES_EXT, &maxSamples);


//        //check for CSAA support
//        if (! glewIsSupported( "GL_NV_framebuffer_multisample_coverage")) {
//            printf( "Warning: No support for coverage multisampling\n");
//        }
//        else {
//            // get the valid configs for Coverage multisampling
//            glGetIntegerv( GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV, &coverageSampleConfigs);

//            coverageConfigs = new int[coverageSampleConfigs * 2 + 4];
//            glGetIntegerv( GL_MULTISAMPLE_COVERAGE_MODES_NV, coverageConfigs);
//        }
//    }

//    // Check for sRGB support, and add it as an option
//    if (! glewIsSupported( "GL_EXT_texture_sRGB GL_EXT_framebuffer_sRGB")) {
//        printf( "Warning: No support for sRGB framebuffer objects\n");
//    }
//    else {
//        //add sRGB textures
//        temp.name = "sRGB8_A8";
//        temp.format = GL_SRGB8_ALPHA8_EXT;
//        temp.bits = 8;
//        colorConfigs.push_back( temp);
//    }

//    // check for float support, and add it as an option
//    if (! glewIsSupported( "GL_ARB_texture_float")) {
//        printf( "Warning: No support for floating point framebuffer objects\n");
//    }
//    else {
//        //add float16 RGBA textures
//        temp.name = "RGBA16F";
//        temp.format = GL_RGBA16F_ARB;
//        temp.bits = 16;
//        colorConfigs.push_back( temp);

//        //add float32 RGBA textures
//        temp.name = "RGBA32F";
//        temp.format = GL_RGBA32F_ARB;
//        temp.bits = 32;
//        colorConfigs.push_back( temp);
//    }

//    // check for packed float support, and add it as an option
//    if (! glewIsSupported( "GL_EXT_packed_float")) {
//        printf( "Warning: No support for packed floating point framebuffer objects\n");
//    }
//    else {
//        //add float RGBA textures
//        temp.name = "RG11F_B10F";
//        temp.format = GL_R11F_G11F_B10F_EXT;
//        temp.bits = 11;
//        colorConfigs.push_back( temp);
//    }

//    // check for depth float support, and add it as an option
//    if (! glewIsSupported( "GL_NV_depth_buffer_float")) {
//        printf( "Warning: No support for floating point depth buffers\n");
//    }
//    else {
//        //add float depth textures
//        temp.name = "D32F";
//        temp.format = GL_DEPTH_COMPONENT32F_NV;
//        temp.bits = 32;
//        depthConfigs.push_back( temp);
//    }

//    int menuId = glutCreateMenu( menu);
//    for (int ii=0; ii < (int)validConfigs.size(); ii++) {
//        glutAddMenuEntry( validConfigs[ii].name.c_str(), ii);
//    }
//    glutAttachMenu( GLUT_RIGHT_BUTTON);

//    // iterate over all the potential configs detected above, and try to create an FBO
//    // If the FBO can be created, add it to the list of available configs, and make a menu entry
//    for (int ii = 0; ii < (int)colorConfigs.size(); ii++) {
//        for (int jj = 0; jj < (int)depthConfigs.size(); jj++) {
//            fboConfig config;
//            fboData data;
//            string root = colorConfigs[ii].name + " " + depthConfigs[jj].name;
//            int subMenuId = glutCreateMenu( menu);

//            config.colorFormat = colorConfigs[ii].format;
//            config.depthFormat = depthConfigs[jj].format;
//            config.redbits = colorConfigs[ii].bits;
//            config.depthBits = depthConfigs[jj].bits;

//            //single sample
//            config.name = root;
//            config.coverageSamples override;
//            config.depthSamples override;

//            if (createFBO( config, data)) {
//                glutAddMenuEntry( config.name.c_str(), (int)validConfigs.size());
//                validConfigs.push_back( config);

//            }
//            destroyFBO( data);

//            //now get multisampled configs
//            if ( coverageSampleConfigs > 0) {
//                //CSAA provides a list of all supported AA modes for quick enumeration
//                for (int kk = 0; kk < coverageSampleConfigs; kk++) {
//                    char msText[256];
//                    config.depthSamples = coverageConfigs[kk*2+1];
//                    config.coverageSamples = coverageConfigs[kk*2];

//                    if ( config.coverageSamples == config.depthSamples ) {
//                        // when coverage and color/depth samples are the same, it is just normal MSAA
//                        sprintf( msText, " - %d MSAA", config.depthSamples);
//                    }
//                    else {
//                        // when coverage is sampled more finely, this is a CSAA mode
//                        sprintf( msText, " - %d/%d CSAA", config.coverageSamples, config.depthSamples);
//                    }
//                    config.name = root + msText;

//                    if (createFBO( config, data)) {
//                        glutAddMenuEntry( config.name.c_str(), (int)validConfigs.size());
//                        validConfigs.push_back( config);
//                    }
//                    destroyFBO( data);
//                }
//            }
//            else {
//                //CSAA is not supported, so use the enumeration method built into GL_EXT_framebuffer_multisample
//                for (int kk = 1; kk <= maxSamples; kk++) {
//                    char msText[256];
//                    config.depthSamples = kk;

//                    if (createFBO( config, data)) {

//                        sprintf( msText, " - %d MSAA", config.depthSamples);
//                        config.name = root + msText;

//                        glutAddMenuEntry( config.name.c_str(), (int)validConfigs.size());
//                        validConfigs.push_back( config);

//                        //GL_EXT_framebuffer_multisample guarantees that the returned size
//                        // is the requested size of higher, so this advances over other values
//                        // that would return the same number of samples
//                        if ( config.depthSamples > kk)
//                            kk = config.depthSamples;
//                    }
//                    destroyFBO( data);
//                }
//            }

//            //add the sub-manu
//            glutSetMenu( menuId);
//            glutAddSubMenu( root.c_str(), subMenuId);
//        }
//    }

//    delete []coverageConfigs;

//    // setup default state
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.2, 0.2, 0.2, 1.0);

//    if ( validConfigs.size() == 0) {
//        printf( "Failed to find any appropriate FBO configs\n");
//        exit(-1);
//    }

//    //create the initial FBO
//    createFBO( validConfigs[0], activeFBO);

//    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

//    // load fragment programs
//    const char* strTextureProgram2D =
//        "!!ARBfp1.0\n"
//        "TEX result.color, fragment.texcoord[0], texture[0], 2D;\n"
//        "END\n";

//    textureProgram = nv::CompileASMShader( GL_FRAGMENT_PROGRAM_ARB, strTextureProgram2D);

//    const char* strOverlayProgram =
//        "!!ARBfp1.0\n"
//        "TEMP t;\n"
//        "TEX t, fragment.texcoord[0], texture[0], 2D;\n"
//        "MOV result.color, t;\n"
//        "END\n";

//    overlayProgram = nv::CompileASMShader( GL_FRAGMENT_PROGRAM_ARB, strOverlayProgram);

//    //make display lists for ASCII characters
//    textDList = glGenLists(128);

//    for ( int ii = 0; ii < 128; ii++) {
//        glNewList( ii + textDList, GL_COMPILE);
//        glutBitmapCharacter(  GLUT_BITMAP_HELVETICA_12, ii );
//        glEndList();
//    }
//    glListBase( textDList);

//    glDepthFunc( GL_LEQUAL);

//}

////
////
////////////////////////////////////////////////////////////////////////
//void cleanup() {
//    // destroy objects
//    destroyFBO( activeFBO);

//    glDeleteProgramsARB(1, &textureProgram);
//    glDeleteProgramsARB(1, &overlayProgram);
//}

////
////
////////////////////////////////////////////////////////////////////////
//void drawFBO() {
//    float lightDir[] = { 1.0f, 1.0f, 1.0f, 0.0f};
//    float material[] = { 0.5f, 1.0f, 0.0f, 1.0f};
//    float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
//    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, activeFBO.fb);

//    GLboolean sRGB = GL_FALSE;

//    glGetBooleanv( GL_FRAMEBUFFER_SRGB_CAPABLE_EXT, &sRGB);

//    if (sRGB)
//        glEnable( GL_FRAMEBUFFER_SRGB_EXT);

//    glPushAttrib(GL_VIEWPORT_BIT);
//    glViewport(0, 0, texWidth, texHeight);

//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();

//    glLightfv( GL_LIGHT0, GL_POSITION, lightDir);
//    glEnable( GL_LIGHT0);
//    glTranslatef(0.0, 0.0, -1.5);
//    glRotatef(teapot_rot, 0.0, 1.0, 0.0);

//    glClearColor(0, 0, 0, 0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//    glColor3f(0.5, 1.0, 0.0);
//    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
//    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);

//    if (options[OPTION_WIREFRAME]) {
//        glutWireTeapot(0.5f);
//    }
//    else {
//        glEnable( GL_LIGHTING);
//        glutSolidTeapot(0.5f);
//    }

//    glDisable( GL_FRAMEBUFFER_SRGB_EXT);

//    glPopMatrix();
//    glPopAttrib();

//    glDisable( GL_LIGHTING);

//    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0);

//    // if this FBO is multisampled, resolve it, so it can be displayed
//    if ( activeFBO.resolveFB) {
//        glBindFramebufferEXT( GL_READ_FRAMEBUFFER_EXT, activeFBO.fb);
//        glBindFramebufferEXT( GL_DRAW_FRAMEBUFFER_EXT, activeFBO.resolveFB);
//        glBlitFramebufferEXT( 0, 0, texWidth, texHeight, 0, 0, texWidth, texHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

//        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
//    }

//    glBindTexture( GL_TEXTURE_2D, activeFBO.tex);
//    glGenerateMipmapEXT( GL_TEXTURE_2D);

//    glBindTexture( GL_TEXTURE_2D, 0);
//}

////
////
////////////////////////////////////////////////////////////////////////
//void display() {
//    // render to the render target texture first
//    drawFBO();

//    // now render to the screen using the texture...
//    glClearColor(0.2, 0.2, 0.2, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();

//    manipulator.applyTransform();

//    // draw textured quad
//    glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, textureProgram);
//    glEnable(GL_FRAGMENT_PROGRAM_ARB);

//    if ( options[OPTION_DISPLAY_DEPTH] && activeFBO.depthTex)
//        glBindTexture( GL_TEXTURE_2D, activeFBO.depthTex);
//    else
//        glBindTexture( GL_TEXTURE_2D, activeFBO.tex);


//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_QUADS);
//    {
//        glTexCoord2f( 0.0f, 0.0f);
//        glVertex2f(-1, -1);
//        glTexCoord2f( 1.0f, 0.0f);
//        glVertex2f( 1, -1);
//        glTexCoord2f( 1.0f, 1.0f);
//        glVertex2f( 1,  1);
//        glTexCoord2f( 0.0f, 1.0f);
//        glVertex2f(-1,  1);
//    }
//    glEnd();

//    glPopMatrix();
//    glDisable(GL_FRAGMENT_PROGRAM_ARB);

//    //
//    // Render the UI
//    //
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    glOrtho( 0.0, double(width), 0.0, double(height), 0.0, 1.0);

//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();

//    if ( options[OPTION_OVERLAY]) {

//        glEnable( GL_BLEND);
//        glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

//        glColor4f( 0.3f, 0.3f, 0.3f, 0.75f);
//        glBegin(GL_QUADS);
//        glVertex2f( 0.0f, 0.0f);
//        glVertex2f( width, 0.0f);
//        glVertex2f( width, height);
//        glVertex2f( 0.0f, height);
//        glEnd();

//        glDisable( GL_BLEND);

//        glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, overlayProgram);
//        glEnable(GL_FRAGMENT_PROGRAM_ARB);

//        float xOffset = (width - texWidth) * 0.5f;
//        float yOffset = (height - texHeight) * 0.5f;

//        glBegin(GL_QUADS);
//        glTexCoord2f( 0.0f, 0.0f);
//        glVertex2f( xOffset, yOffset);
//        glTexCoord2f( 1.0f, 0.0f);
//        glVertex2f( xOffset + texWidth, yOffset);
//        glTexCoord2f( 1.0f, 1.0f);
//        glVertex2f( xOffset + texWidth, yOffset + texHeight);
//        glTexCoord2f( 0.0f, 1.0f);
//        glVertex2f( xOffset, yOffset + texHeight);
//        glEnd();

//        glDisable(GL_FRAGMENT_PROGRAM_ARB);
//    }

//    //render a small text overlay to show the config and size of the texture
//    char size[256];

//    glColor3f( 1.0f, 1.0f, 1.0f);

//    sprintf( size, "( %d x %d )", texWidth, texHeight);

//    glRasterPos2f( 10.0f, height - 20.0f);
//    glCallLists( (GLsizei)validConfigs[activeConfig].name.size(), GL_UNSIGNED_BYTE, validConfigs[activeConfig].name.c_str());
//    glCallLists( (GLsizei)strlen(size), GL_UNSIGNED_BYTE, size);

//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    glPopMatrix();

//    glBindTexture( GL_TEXTURE_2D, 0);

//    glutSwapBuffers();
//}

////
////
////////////////////////////////////////////////////////////////////////
//void key(unsigned char k, int x, int y) {
//    k = tolower(k);

//    if (optionKeyMap.find(k) != optionKeyMap.end())
//        options[optionKeyMap[k]] = ! options[optionKeyMap[k]];

//    if (k == '+') {
//        //move to the next larger FB size
//        if ( texWidth < 1024 && texHeight < 1024) {
//            texWidth <<= 1;
//            texHeight <<= 1;

//            destroyFBO( activeFBO);
//            createFBO( validConfigs[activeConfig], activeFBO);
//        }
//    }

//    if (k == '-') {
//        //move to the next smaller FB size
//        if ( texWidth > 32 && texHeight > 32) {
//            texWidth >>= 1;
//            texHeight >>= 1;

//            destroyFBO( activeFBO);
//            createFBO( validConfigs[activeConfig], activeFBO);
//        }
//    }

//    if(k==27 || k=='q') {
//        cleanup();
//        exit(0);
//    }

//    glutPostRedisplay();
//}

////
////
////////////////////////////////////////////////////////////////////////
//void resize(int w, int h) {
//    if (h == 0) h = 1;

//    glViewport(0, 0, w, h);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();

//    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

//    manipulator.reshape(w, h);
//    width = w;
//    height = h;
//}

////
////
////////////////////////////////////////////////////////////////////////
//void menu( int mode) {
//    destroyFBO( activeFBO);
//    activeConfig = mode;
//    createFBO( validConfigs[activeConfig], activeFBO);
//}
