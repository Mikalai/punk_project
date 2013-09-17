
const int MAX_LIGHTS = 8;

const int POINT_LIGHT = 0;
const int DIRECTION_LIGHT = 1;
const int SPOT_LIGHT = 2;

const int ATTENUATION_CONSTANT = 0;
const int ATTENUATION_LINEAR = 1;
const int ATTENUATION_QUADRIC = 2;

struct Light
{
    int   enabled;
    vec4  direction;
    vec4  position;
    vec4  diffuse_color;
    vec4  ambient_color;
    vec4  specular_color;
    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadric;
    float spot;
    int   type;                 //	0 - point, 1 - direction, 2 - spot
    int   attenuation_model;    //	0 - Constant, 1 - Linear, 2 - Quadric
};

float AttenuationConstant(float k0)
{
    return 1.0 / k0;
}

float AttenuationLinear(float k0, float k1, float dst)
{
    return 1.0f / (k0 + k1 * dst);
}

float AttenuationQuadric(float k0, float k1, float k2, float dst)
{
    return 1.0f / (k0 + k1 * dst + k2 * dst * dst);
}

float SpotAttenuation(vec3 r, vec3 l, float p)
{
    return pow(max(dot(-r, l), 0), p);
}
