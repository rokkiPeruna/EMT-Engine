#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats

attribute vec4 a_position; 		// input position value
attribute vec2 a_texCoordinate;	// input texture coordinates
attribute vec4 a_color; 		// input vertex color


// varying variables – input to the fragment shader
varying vec2 v_texCoordinate;	// output vertex coordinates
varying vec4 v_color; 		// output vertex color


void
main()
{
	gl_Position = a_position;
	v_color = a_color;
	v_texCoordinate = a_texCoordinate;
	
}