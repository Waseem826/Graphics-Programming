#version 330

uniform sampler2D tex;

in vec2 texCoordOut;

out vec4 colour;

void main()
{
	vec4 col = texture2D(tex, texCoordOut);
	colour = col;
	colour.a = 1.0;
}