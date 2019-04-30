
uniform sampler2D u_Texture;
varying vec2 v_WindowSpacePos;

varying vec2 v_UV;

void main()
{
	if (gl_FragCoord.x > v_WindowSpacePos.x)
	{
		gl_FragColor = vec4(0, 0, 0, 0);
	}
	else
	{
		gl_FragColor = texture2D(u_Texture, v_UV);
	}
}
