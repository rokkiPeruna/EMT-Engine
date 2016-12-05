#version 110

precision mediump float;
uniform sampler2D texture;
varying vec2 texCoord;
void main()
{
	gl_FragColor = texture2D(texture, texCoord);
}