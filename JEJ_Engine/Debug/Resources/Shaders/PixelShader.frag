#version 110

precision mediump float;
uniform sampler2D sampler_texture;
varying vec2 v_texCoordinate;
void main()
{
	gl_FragColor = texture2D(sampler_texture, v_texCoordinate);
}