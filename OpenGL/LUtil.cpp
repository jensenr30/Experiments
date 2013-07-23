/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 001

#include "LUtil.h"

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
	static float a = -0.5, r = 0, g = 0.33, b = 0.67;
	a += 0.01;
	r += 0.01;
	g= 0.01;
	b += 0.01;
	if(r >= 1.0) r = 0.0;
	if(g >= 1.0) g = 0.0;
	if(b >= 1.0) b = 0.0;
	if(a >= 0.5) a = -0.5;
	
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Render quad
    glBegin( GL_QUADS );
        glVertex2f( -a, -a );
        glVertex2f(  a, -a );
        glVertex2f(  a,  a );
        glVertex2f( -a,  a );
        glColor3f(r,g,b);
    glEnd();

    //Update screen
    glutSwapBuffers();
}
