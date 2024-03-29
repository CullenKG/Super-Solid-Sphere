#include "FrameworkPCH.h"
#include "GLHelpers.h"
#include "../../Libraries/lodepng/lodepng.h"

void CheckForGLErrors()
{
    GLenum error = glGetError();

    if( error != 0 )
    {
        OutputMessage( "glGetError\n" );
        assert( false );
    }
}

GLuint LoadTexture(const char* filename)
{
    unsigned char* pngbuffer;
    unsigned int width, height;
    long filesize;
    unsigned char* filebuffer = (unsigned char*)LoadCompleteFile( filename, &filesize );
    unsigned int result = lodepng_decode32( &pngbuffer, &width, &height, filebuffer, filesize );
	delete[] filebuffer;
    assert( result == 0 );

    Flip32BitImageVertically( pngbuffer, width, height );

    GLuint texhandle = 0;
    glGenTextures( 1, &texhandle );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texhandle );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    glBindTexture( GL_TEXTURE_2D, 0 );

    free( pngbuffer );

    return texhandle;
}

GLuint LoadTexture(const char* filename, unsigned int &outWidth, unsigned int &outHeight)
{
    unsigned char* pngbuffer;
    unsigned int width, height;
    long filesize;
    unsigned char* filebuffer = (unsigned char*)LoadCompleteFile(filename, &filesize);
    unsigned int result = lodepng_decode32(&pngbuffer, &width, &height, filebuffer, filesize);
    delete[] filebuffer;
    assert(result == 0);
    outWidth = width;
    outHeight = height;
    Flip32BitImageVertically(pngbuffer, width, height);

    GLuint texhandle = 0;
    glGenTextures(1, &texhandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texhandle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(pngbuffer);

    return texhandle;
}

void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height)
{
    // flip the image in buffer.  Assumes RGBA 32 bit.
    
    {
        // temp allocation big enough for one line
        unsigned int* temp;
        temp = new unsigned int[width];
        int linesize = width * sizeof(unsigned int);

        unsigned int* buffer32 = (unsigned int*)buffer;
        for( unsigned int y=0; y<height/2; y++ )
        {
            int LineOffsetY = y*width;
            int LineOffsetHminusY = (height-1-y)*width;

            memcpy( temp, &buffer32[LineOffsetY], linesize );
            memcpy( &buffer32[LineOffsetY], &buffer32[LineOffsetHminusY], linesize );
            memcpy( &buffer32[LineOffsetHminusY], temp, linesize );
        }

        delete[] temp;
    }

    // slower but one less memory allocation.
    //{
    //    unsigned int* pngbuffer32 = buffer;
    //    for( unsigned int y=0; y<height/2; y++ )
    //    {
    //        int LineOffsetY = y*width;
    //        int LineOffsetHminusY = (height-1-y)*width;

    //        for( unsigned int x=0; x<width; x++ )
    //        {
    //            int tempcolor = pngbuffer32[LineOffsetY + x];
    //            pngbuffer32[LineOffsetY + x] = pngbuffer32[LineOffsetHminusY + x];
    //            pngbuffer32[LineOffsetHminusY + x] = tempcolor;
    //        }
    //    }
    //}
}
