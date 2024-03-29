
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

varying mat4 v_WorldMat;
varying vec2 v_UV;
varying vec4 v_WorldPos;
varying vec3 v_Normal;


void main()
{
    vec4 objectpos = a_Position;
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

	v_WorldPos = worldpos;
	v_Normal = a_Normal;
	v_WorldMat = u_WorldMatrix;
	v_UV = a_UV;
}
