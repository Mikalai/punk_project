
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

struct AttenuationResult
{
    vec3 l; //  point to light
    vec3 d; //  light direction
    float c;    //  attenuation factor
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

AttenuationResult LightAttenuation(Light light, vec3 vertex_position)
{
    AttenuationResult res;
    float k0 = light.attenuation_constant;
    float k1 = light.attenuation_linear;
    float k2 = light.attenuation_quadric;
    int mode = light.attenuation_model;
    if (light.type == POINT_LIGHT)
    {
        res.l = light.position.xyz - vertex_position;
        float dst = length(res.l);
        res.l = normalize(res.l);
        if (mode == ATTENUATION_CONSTANT)
            res.c = AttenuationConstant(k0);
        else if (mode == ATTENUATION_LINEAR)
            res.c = AttenuationLinear(k0, k1, dst);
        else if (mode == ATTENUATION_QUADRIC)
            res.c = AttenuationQuadric(k0, k1, k2, dst);
    }
    else if (light.type == DIRECTION_LIGHT)
    {
        res.l = normalize(-light.direction.xyz);
        res.d = light.direction.xyz;
        res.c = 1;
    }
    else if (light.type == SPOT_LIGHT)
    {
        float p  = light.spot;
        res.l = light.position.xyz - vertex_position;
        float dst = length(res.l);
        res.l = normalize(res.l);
        float sc = SpotAttenuation(normalize(light.direction.xyz), res.l, p);
        if (mode == ATTENUATION_CONSTANT)
            res.c = sc*AttenuationConstant(k0);
        else if (mode == ATTENUATION_LINEAR)
            res.c = sc*AttenuationLinear(k0, k1, dst);
        else if (mode == ATTENUATION_QUADRIC)
            res.c = sc*AttenuationQuadric(k0, k1, k2, dst);
    }
    return res;
}
