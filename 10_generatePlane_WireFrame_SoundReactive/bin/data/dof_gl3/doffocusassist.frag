#version 150

//Shader for visualizing a depth texture as a focal distance map
//paired with dofblur for debugging purposes

uniform sampler2DRect depthTex;
uniform float focalDistance;
uniform float focalRange;

in vec4 vColor;
in vec2 vTexCoord;

out vec4 vFragColor;

float LinearizeDepth(float zoverw){
    float n = 1.0; // camera z near
    float f = 20000.0; // camera z far
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

void main()
{
    float depth = LinearizeDepth( texture(depthTex, vTexCoord).r ) * 20000.;
    vFragColor.rgb = vec3(min( abs(depth  - focalDistance) / focalRange, 1.0) );
    vFragColor.a = 1.0;
}