#version 150

// OF default uniforms and attributes
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

// App uniforms and attributes
out vec4 vColor;
out vec2 vTexCoord;

void main(void)
{
	gl_Position = modelViewProjectionMatrix * position;
	vTexCoord = texcoord;
}
