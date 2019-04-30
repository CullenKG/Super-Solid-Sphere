#ifndef __VertexFormat_H__
#define __VertexFormat_H__

struct VertexFormat
{
    vec3 pos;
    MyColor color;
    vec2 uv;
    vec3 normal;
    vec3 tangent;

    VertexFormat() {}
    VertexFormat(float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float u, float v, float nX, float nY, float nZ)
    {
        pos.Set( x, y, z);
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
        uv.Set( u, v );
        normal.Set(nX, nY, nZ);
        tangent = vec3(0);
    }    
    VertexFormat(vec3 aPos, MyColor aColor, vec2 aUV, vec3 aNormal, vec3 aTangent)
    {
        pos = aPos;
        color = aColor;
        uv = aUV;
        normal = aNormal;
        tangent = aTangent;
    }

};

#endif //__VertexFormat_H__
