#include "FrameworkPCH.h"
#include "Helpers.h"

void OutputMessage(const char* message, ...)
{
#define MAX_MESSAGE 1024
    char szBuff[MAX_MESSAGE];
    va_list arg;
    va_start(arg, message);
    vsnprintf_s( szBuff, sizeof(szBuff), _TRUNCATE, message, arg );
    va_end(arg);

    szBuff[MAX_MESSAGE-1] = 0; // vsnprintf_s might do this, but docs are unclear
    OutputDebugString( szBuff );
}

double GetSystemTime()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
    QueryPerformanceCounter( (LARGE_INTEGER*)&time );

    double timeseconds = (double)time / freq;

    return timeseconds;
}

char* LoadCompleteFile(const char* filename, long* length)
{
    char* filecontents = 0;

    FILE* filehandle;
    errno_t error = fopen_s( &filehandle, filename, "rb" );

    if( filehandle )
    {
        fseek( filehandle, 0, SEEK_END );
        long size = ftell( filehandle );
        rewind( filehandle );

        filecontents = new char[size+1];
        fread( filecontents, size, 1, filehandle );
        filecontents[size] = 0;

        if( length )
            *length = size;

        fclose( filehandle );
    }

    return filecontents;
}

GLuint LoadTextureCubemap(const char** filenames)
{
    unsigned char* pngbuffer = 0;
    unsigned int width = 0, height = 0;

    GLuint texhandle;
	glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texhandle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texhandle);

    for (int i = 0; i<6; i++)
    {
        lodepng_decode32_file(&pngbuffer, &width, &height, filenames[i]);
        assert(pngbuffer != 0);
        if (pngbuffer == 0)
            return 0;

        //Flip32BitImageVertically( pngbuffer, width, height );

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer);

        free(pngbuffer);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return texhandle;
}

double GetSystemTimeSinceGameStart()
{
	static double starttime = -1;

	if (starttime == -1)
		starttime = GetSystemTime();

	return GetSystemTime() - starttime;
}