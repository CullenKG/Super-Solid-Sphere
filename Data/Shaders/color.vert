
attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform vec4 u_Color;

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProjection;

uniform vec2 u_ProjectionScale;

varying vec2 v_UV;
varying vec4 v_Color;

void main()
{
	// Store object space position.
	vec4 objectpos = vec4(a_Position, 1);
	vec4 worldpos = u_MatWorld * objectpos;
	vec4 viewpos = u_MatView * worldpos;
	vec4 clippos = u_MatProjection * viewpos;

	// Store final position in gl_Position
    gl_Position = clippos;

	v_Color = u_Color;
}
