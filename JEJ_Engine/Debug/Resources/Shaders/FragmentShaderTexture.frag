#version 110

precision mediump float;

varying vec2 texCoord;

uniform sampler2D u_Texture;

void main()
{
	gl_FragColor = texture2d(u_Texture, texCoord);
}