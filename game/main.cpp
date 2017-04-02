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
#include "Building.cc"
#include <vector>

static GLuint ground;
static GLuint sky;
static GLuint horizon;

vector<Building*> buildings;

float cameraHeight = 0;
float cameraLookX = 0;
float cameraLookY = 0;

float cameraPositionX = 0;
float cameraPositionY = 0;
float cameraPositionZ = -5;

float cameraAngle = 0;
float cameraDistance = 1;

GLfloat windowWidth = 0;
GLfloat windowHeight = 0;


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

void calcCameraLook(){
	cameraLookY = cos(cameraAngle) * cameraDistance;
	cameraLookX = sin(cameraAngle) * cameraDistance;
}

Building::Color randomColor() {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	return Building::Color(r, g, b, a);
}

void buildingInit() {
	int xPos = ((rand() % 20) + 5) /10;
	int yPos = ((rand() % 20) + 5) /10;

	float startY = 2.5;

	for (int j = 1; j < 16; j++) {
		float startX = 0;

		for (int i = 1; i < 16; i++) {

			cout << "X: " << startX << " Y: "<< startY<< endl;


			int buildingHeight = (rand() % 4 +1);
			int buildingWidth = (rand() % 2 + 1);

			Building::Color color = randomColor();

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX + (i*2.5), startY, color));

			if (i % 3 == 0)
				startX += 2.5;
		}
		startY += 2.5;
		if (j % 3 == 0)
			startY += 2.5;
	}

	startY = -2.5;

	for (int j = 1; j < 16; j++) {
		float startX = 0;

		for (int i = 1; i < 16; i++) {

			cout << "X: " << startX << " Y: "<< startY<< endl;

			int buildingHeight = (rand() % 4 +1);
			int buildingWidth = (rand() % 2 + 1);

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX + (i*2.5), startY));

			if (i % 3 == 0)
				startX += 2.5;
		}
		startY -= 2.5;
		if (j % 3 == 0)
			startY -= 2.5;
	}

	startY = 2.5;

	for (int j = 1; j < 16; j++) {
		float startX = 0;

		for (int i = 1; i < 16; i++) {

			cout << "X: " << startX << " Y: "<< startY<< endl;


			int buildingHeight = (rand() % 4 +1);
			int buildingWidth = (rand() % 2 + 1);

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX - (i*2.5), startY));

			if (i % 3 == 0)
				startX -= 2.5;
		}
		startY += 2.5;
		if (j % 3 == 0)
			startY += 2.5;
	}

	startY = -2.5;

	for (int j = 1; j < 16; j++) {
		float startX = 0;

		for (int i = 1; i < 16; i++) {

			cout << "X: " << startX << " Y: "<< startY<< endl;

			int buildingHeight = (rand() % 4 +1);
			int buildingWidth = (rand() % 2 + 1);

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX - (i*2.5), startY));

			if (i % 3 == 0)
				startX -= 2.5;
		}
		startY -= 2.5;
		if (j % 3 == 0)
			startY -= 2.5;
	}
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

	// create some building
	buildingInit();
}


void draw_environment(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat) windowWidth/(GLfloat) windowHeight, 1.0, 300.0);

	cout << "Cam height: " << cameraHeight << " CamX: " << cameraLookX <<  " CamY: " << cameraLookY << endl;
	cout << "Cam angle: " << cameraAngle << endl;

	calcCameraLook();
	gluLookAt(cameraPositionX, cameraHeight, cameraPositionY, cameraLookX, 0,cameraLookY, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// CLEAR THE BUFFER, all drawing code should be after this point
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Buildings
	// create some buildings

	for (int i = 0; i < buildings.size(); i++) {
		if (i == 0)
			glColor3f(1.0, 0.0, 0.0);
		else
			glColor3f(0.0, 0.0, 1.0);

		buildings[i]->draw();
	}

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
	windowHeight = h;
	windowWidth = w;


	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat) w/(GLfloat) h, 1.0, 300.0);

	calcCameraLook();
	gluLookAt(cameraPositionX, cameraHeight, cameraPositionY, cameraLookX, 0,cameraLookY, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 's':
			cameraDistance -=1;
			if (cameraDistance < 1)
				cameraDistance = 1;
			break;
		case 'w':
			cameraDistance +=1;
			break;
		case 'a':
			cameraAngle +=0.1;
			break;
		case 'd':
			cameraAngle -=0.1;
			break;

		default:
			cout << "key: " << key << endl;
			break;
	}
}

void SpecialInput(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
//do something here
			cameraPositionX += 0.1;
			break;
		case GLUT_KEY_DOWN:
			cameraPositionX -= 0.1;
//do something here
			break;
		case GLUT_KEY_LEFT:
			cameraPositionY += 0.1;
//do something here
			break;
		case GLUT_KEY_RIGHT:
			cameraPositionY -= 0.1;
//do something here
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);

	windowHeight = 750;
	windowWidth = 750;

	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);

	glutMainLoop();
	return 0;
}
