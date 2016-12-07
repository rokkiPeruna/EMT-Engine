#version 110

precision mediump float;

varying vec2 v_texCoordinate;

uniform sampler2D sampler_texture;

void main()
{
	gl_FragColor = texture2d(sampler_texture, v_texCoordinate);
}