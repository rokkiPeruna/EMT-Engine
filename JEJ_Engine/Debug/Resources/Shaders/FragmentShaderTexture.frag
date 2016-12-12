precision mediump float;
varying vec2 v_texCoordinate;
varying vec4 v_color; // output vertex color
uniform sampler2D sampler_texture;
void main()
{
gl_FragColor = texture2D(sampler_texture, v_texCoordinate);
gl_FragColor.rgb *= v_color.a;
}
