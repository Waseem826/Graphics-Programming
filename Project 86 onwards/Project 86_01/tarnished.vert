#version 330

uniform mat4 model;
uniform mat4 modelViewProjection;
uniform mat4 modelInverseTranspose;
uniform vec3 eyePos;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoordIn;

out vec2 texCoordOut;
smooth out vec3 mapCoordOut;

void main()
{
	vec3 transformedPosition = (model * vec4(position, 1.0)).xyz;
	vec3 transformedNormal = (modelInverseTranspose * vec4(normal, 1.0)).xyz;
	gl_Position = modelViewProjection * vec4(position, 1.0);
	texCoordOut = texCoordIn;
	mapCoordOut = normalize(reflect(transformedPosition - eyePos, transformedNormal));
}