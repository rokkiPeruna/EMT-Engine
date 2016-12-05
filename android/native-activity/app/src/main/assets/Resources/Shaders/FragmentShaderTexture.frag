#version 110

precision mediump float;
varying vec2 texCoord;
void main()
{
	gl_FragColor = vec4(texCoord.x, texCoord.y, 0.f, 1.0f);
}