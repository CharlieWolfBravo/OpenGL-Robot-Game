#define PROGRAM_TITLE "Lance Chisholm - 001177098"
#define DISPLAY_INFO "Press the Z key to move the cube along the Z axis. Press the right mouse button to move the camera."

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.

#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

#include <stdbool.h>
#include <cstdlib>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include "bmpread.h"


static GLuint ground;
static GLuint sky;
static GLuint horizon;

GLuint LoadTexture(const char * bitmap_file)
{
	GLuint texture = 0;
	bmpread_t bitmap;
	
	if(!bmpread(bitmap_file, 0, &bitmap))
	{
		fprintf(stderr, "%s: error loading bitmap file\n", bitmap_file);
		exit(1);
	}
	
	/* At this point, bitmap.width and .height hold the pixel dimensions of the
	 * file, and bitmap.rgb_data holds the raw pixel data in RGB triplets.
	 */
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.width, bitmap.height, 0,
					 GL_RGB, GL_UNSIGNED_BYTE, bitmap.rgb_data);
	
	bmpread_free(&bitmap);
	
	return texture;
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glBindTexture(GL_TEXTURE_2D, ground);

	ground=LoadTexture("./ground.bmp");
	sky=LoadTexture("./sky.bmp");
	horizon=LoadTexture("./horizon.bmp");
	
}

void draw_environment(){
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, ground);
	glBegin(GL_QUADS);
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			glTexCoord2f(0.0, 0.0); glVertex3f(-40.0+i*10, -5.0, -50.0+j*10);
			glTexCoord2f(0.0, 1.0); glVertex3f(-40.0+i*10, -5.0, -40.0+j*10);
			glTexCoord2f(1.0, 1.0); glVertex3f(-50.0+i*10, -5.0, -40.0+j*10);
			glTexCoord2f(1.0, 0.0); glVertex3f(-50.0+i*10, -5.0, -50.0+j*10);
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, sky);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0, -50.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 50.0, 5.0,  50.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 5.0,  50.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 5.0, -50.0);
	glEnd();
	glEnd();
	glBindTexture(GL_TEXTURE_2D, horizon);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,  -50.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,  -50.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  5.0,  -50.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, -5.0,  -50.0);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  5.0,   50.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, -5.0,   50.0);
	
	glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, -5.0,  -50.0);
	glTexCoord2f(0.0, 1.0); glVertex3f( 50.0,  5.0,  -50.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  5.0,   50.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, -5.0,   50.0);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,  -50.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,  -50.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void display(void)
{
	draw_environment();
	

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat) w/(GLfloat) h, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			printf("key: %i\n",key);
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
