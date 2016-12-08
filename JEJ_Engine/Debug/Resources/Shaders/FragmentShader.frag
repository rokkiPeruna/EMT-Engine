#version 130
//The fragment shader operates on each pixel on given polygon

varying in vec4 v_color;

varying vec2 v_texCoordinate;
uniform sampler2D sampler_texture;


void main()
{
		//For solid color given on vertexShader
		//gl_FragColor = v_color;
		
		//For texture color
		gl_FragColor = texture2D(sampler_texture, v_texCoordinate);
}