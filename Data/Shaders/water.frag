
uniform sampler2D u_Texture;

uniform float u_Time;

varying vec2 v_UV;
varying vec4 v_Color;

void main()
{
	gl_FragColor = texture2D( u_Texture, v_UV ) + vec4(0, 0, 139, 0) + v_Color;
	//gl_FragColor = v_Color;
}
