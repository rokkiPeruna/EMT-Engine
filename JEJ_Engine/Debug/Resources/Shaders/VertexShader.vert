#version 110

attribute vec4 a_position;
attribute vec2 a_texCoordinate;
attribute vec4 a_color;

varying vec2 v_texCoordinate;
varying vec4 v_color;

void main()
{
	gl_Position = a_position;
	v_color = a_color;
	v_texCoordinate = a_texCoordinate;
}
