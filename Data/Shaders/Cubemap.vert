attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

varying vec3 v_Position;

void main()
{
	vec4 viewPos = u_ViewMatrix * vec4(a_Position, 0);
	vec4 clipPos = u_ProjMatrix * vec4(viewPos.xyz, 1);

    gl_Position = clipPos.xyww;

    v_Position = a_Position;
}