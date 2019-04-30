attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;
attribute vec3 a_Tangent;

uniform vec3 u_CameraPosition;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

varying mat3 v_TBN;

varying vec3 v_Pos;

varying vec3 v_CameraPosition;
varying vec3 v_ObjectPosition;
varying vec2 v_UV;

void main()
{
    vec4 objectpos = vec4(a_Position, 1);
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

	gl_Position = clippos;

	mat3 normalMatrix = transpose(inverse(mat3(u_WorldMatrix)));

	vec3 T = normalize(normalMatrix * a_Tangent);
	vec3 N = normalize(normalMatrix * a_Normal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	v_TBN = mat3(T, B, N);	

	mat4 viewModel = inverse(u_ViewMatrix);
	v_CameraPosition = viewModel[3];
	v_ObjectPosition = vec3(worldpos);
	v_UV = a_UV;
}
