
attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

uniform float u_LoadingBarProgress;

uniform vec2 u_ViewportSize;
uniform vec2 u_ViewportPosition;

varying vec2 v_UV;
varying vec2 v_WindowSpacePos;

void main()
{
    vec4 objectpos = vec4(a_Position, 1);
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

	vec4 loadingBarView = u_ViewMatrix * vec4(u_LoadingBarProgress, 0, 0, 1);
	vec4 loadingBarClip = u_ProjMatrix * loadingBarView;

	vec3 ndcPos = loadingBarClip.xyz / loadingBarClip.w;
	vec2 windowSpacePos = ((ndcPos.xy + 1.0) / 2.0) * u_ViewportSize + u_ViewportPosition;

	v_WindowSpacePos = windowSpacePos;

    gl_Position = clippos;

    v_UV = a_UV;
}
