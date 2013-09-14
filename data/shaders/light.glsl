
const int MAX_LIGHTS = 8;

struct Light
{
    int   enabled;
    vec4  direction;
    vec4  position;
    vec4  diffuse_color;
    vec4  ambient_color;
    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadric;
    float spot;
    int   type;                 //	0 - point, 1 - direction
    int   attenuation_model;    //	0 - Constant, 1 - Linear, 2 - Quadric
};
