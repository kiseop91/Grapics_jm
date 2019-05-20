#version 330

uniform float Scale;

in vec4 v_color;
out vec4 frag_colour;

void main()
{
	frag_colour = v_color * Scale;
};