
attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProjection;

uniform bool u_Ripple;
uniform vec2 u_RippleOrigin;
uniform float u_RippleFrequency;
uniform float u_RippleMagnitude;
uniform float u_RippleWaveLength;
uniform float u_RippleRange;


uniform float u_Time;

varying vec2 v_UV;
varying vec4 v_Color;

vec2 UV;

void main()
{
	UV = a_UV;

	// Store object space position.
	vec4 objectpos = vec4(a_Position, 1);

	vec2 origin = vec2(0, 0);

	float distance = sqrt((objectpos.x - u_RippleOrigin.x) * (objectpos.x - u_RippleOrigin.x) + (objectpos.z - u_RippleOrigin.y) * (objectpos.z - u_RippleOrigin.y));

	u_RippleMagnitude -= u_RippleMagnitude * (distance / u_RippleRange);

	if (distance > u_RippleRange)
	{
		u_RippleMagnitude = 0;
	}

	if (u_Ripple)
	{
		objectpos.y += u_RippleMagnitude * sin(sqrt(((objectpos.x - u_RippleOrigin.x) * (objectpos.x - u_RippleOrigin.x)) + ((objectpos.z - u_RippleOrigin.y) * (objectpos.z - u_RippleOrigin.y))) * u_RippleWaveLength - (u_Time * u_RippleFrequency));
	}

	if (objectpos.y > 0)
	{
		a_Color += vec4(objectpos.y, objectpos.y, objectpos.y, 0);
	}
	
	//objectpos.y += sin( a_Position.z + u_Time ) * 0.2;


	vec4 worldpos = u_MatWorld * objectpos;
	vec4 viewpos = u_MatView * worldpos;
	vec4 clippos = u_MatProjection * viewpos;

	// Store final position in gl_Position
    gl_Position = clippos;

	//UV.x += (sin((u_Time / 1000) + UV.y) * 0.2) + u_Time * 0.1; 
	//UV.y += (sin((u_Time / 1000) + UV.x) * 0.2) + u_Time * 0.1;

	v_UV = UV;
	v_Color = a_Color;
}
