#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats

attribute vec2 a_position; 		// input position value
attribute vec2 a_texCoordinate;	// input texture coordinates
attribute vec4 a_color; 		// input vertex color


// varying variables – input to the fragment shader
varying vec2 v_texCoordinate;	// output vertex coordinates
varying vec4 v_color; 		// output vertex color


void
main()
{
	gl_Position.xy = a_position.xy;
	gl_Position.z = 0;
	gl_Position.w = 1.0;
	v_color = a_color;
	v_texCoordinate = a_texCoordinate;
	
}