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

int Building::gen_id = 0;

int SIZE = 1024;


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

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX + (i*2.5), startY, color, Building::gen_id));
			Building::gen_id++;

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

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX + (i*2.5), startY, Building::gen_id));
			Building::gen_id++;

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

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX - (i*2.5), startY, Building::gen_id));
			Building::gen_id++;

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

			buildings.push_back(new Building(buildingWidth, buildingHeight, startX - (i*2.5), startY, Building::gen_id));
			Building::gen_id++;

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
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);


//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glBindTexture(GL_TEXTURE_2D, ground);

//	ground=LoadTexture("./ground.bmp");
//	sky=LoadTexture("./sky.bmp");
//	horizon=LoadTexture("./horizon.bmp");

	// create some building
	buildingInit();
}

void destroy(int value) {
	cout << "destroying " << value << " height " << buildings[value]->height << endl;

	if (buildings[value]->height >= 0) {
		buildings[value]->height -= 0.1;
	}
}

void drawBuildings(GLenum mode) {

	if (mode == GL_SELECT) {
		glInitNames();
		glPushName(-1);

		// Buildings
		// create some buildings
		for (int i = 0; i < buildings.size(); i++) {
			if (i == 0)
				glColor3f(1.0, 0.0, 0.0);
			else
				glColor3f(0.0, 0.0, 1.0);
			//cout << "building id " << buildings[i]->id << endl;
			glLoadName(buildings[i]->id);
			buildings[i]->draw();
		}
	} else {
		// Buildings
		// create some buildings
		for (int i = 0; i < buildings.size(); i++) {
			if (i == 0)
				glColor3f(1.0, 0.0, 0.0);
			else
				glColor3f(0.0, 0.0, 1.0);

			if (buildings[i]->height > 0)
				buildings[i]->draw();

			if (buildings[i]->display == false)
				glutTimerFunc(100, destroy, i);
		}
	}
}


void draw_environment(GLenum mode){

	// CLEAR THE BUFFER, all drawing code should be after this point
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat) windowWidth/(GLfloat) windowHeight, 1.0, 300.0);

	cout << "Cam height: " << cameraHeight << " CamX: " << cameraLookX <<  " CamY: " << cameraLookY << endl;
	cout << "Cam angle: " << cameraAngle << endl;

    cout << "Cam posX: " << cameraPositionX << " Cam posY: " << cameraPositionY <<  " CamY: " << endl;

	calcCameraLook();
	gluLookAt(cameraPositionX, cameraHeight, cameraPositionY, cameraLookX, 0,cameraLookY, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

		drawBuildings(mode);

//		glEnable(GL_TEXTURE_2D);
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//		glBindTexture(GL_TEXTURE_2D, ground);
    glColor4f(0.1, 0.9, 0.1, 1.0);

    glBegin(GL_QUADS);
		for (int i=0; i<10; i++) {
			for (int j=0; j<10; j++) {
                glTexCoord2f(1.0, 1.0); glVertex3f(-50.0+i*10, -5.0, -40.0+j*10);
				glTexCoord2f(0.0, 1.0); glVertex3f(-40.0+i*10, -5.0, -40.0+j*10);
                glTexCoord2f(0.0, 0.0); glVertex3f(-40.0+i*10, -5.0, -50.0+j*10);
                glTexCoord2f(1.0, 0.0); glVertex3f(-50.0+i*10, -5.0, -50.0+j*10);
			}
		}
		glEnd();
    // streets

    glColor4f(0.5, 0.5, 0.5, 1.0);

    glBegin(GL_QUADS);

    for (int i=0; i<10; i++) {
            glTexCoord2f(1.0, 1.0); glVertex3f(-51+i*10, -4.95, 50.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-49+i*10, -4.95, 50.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-49+i*10, -4.95, -50.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(-51+i*10, -4.95, -50.0);
    }

    for (int i=0; i<10; i++) {
        glTexCoord2f(1.0, 0.0); glVertex3f(-50, -4.95, -51+i*10);

        glTexCoord2f(0.0, 0.0); glVertex3f(-50, -4.95, -49+i*10);
        glTexCoord2f(0.0, 1.0); glVertex3f(50, -4.95, -49+i*10);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, -4.95, -51+i*10);


    }
    glEnd();

    glColor4f(0.1, 0.1, 1.0, 1.0);

//		glBindTexture(GL_TEXTURE_2D, sky);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0, -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f( 50.0, 5.0,  50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 5.0,  50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 5.0, -50.0);
		glEnd();
		glEnd();
//		glBindTexture(GL_TEXTURE_2D, horizon);
		glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  -5.0,  -50.0);
        glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, 5.0,  -50.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, 5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  -5.0,  -50.0);



		glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, -5.0,   50.0);

		glTexCoord2f(0.0, 0.0); glVertex3f( 50.0, 5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f( 50.0,  -5.0,  -50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f( 50.0,  -5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f( 50.0, 5.0,   50.0);

		glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -5.0,  -50.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-50.0,  5.0,  -50.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(-50.0,  5.0,   50.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, -5.0,   50.0);
		glEnd();


		glFlush();
		//glDisable(GL_TEXTURE_2D);

}

void display(void)
{
	draw_environment(GL_RENDER);


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

void processHits(GLint hits, GLuint buffer[])
/* this is the same "boiler plate" as before */
{
	unsigned int i, j;
	GLint ii, jj, names, *ptr;

	printf ("hits = %d\n", hits);
	ptr = (GLint *) buffer;

	for (i = 0; i < 1; i++) { // For each hit record,
		names = *ptr;             // How many names are in this hit record?
		ptr += 3;                   // Skip the depth min and max information.

		for (j = 0; j < names; j++) { //  Look for each name in this record

			if (j == 0)
				buildings[*ptr]->display = false;

			cout << *ptr << endl;

			ptr++;                          // Go to the next name
		}
		// When this loop is done, ptr points to the start of the next hit record.
		printf("\n");
	}
	cout << "End of Processing hits" << endl;
}

void mouseFunc(int button, int state, int x, int y) {

	GLuint selectBuf[SIZE]; // Selection buffer, which is an array of size 512
	GLint hits;
	GLint viewport[4]; // Current viewport size. See below.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)  // When the left mouse button is pressed, we start picking.
	{

		glGetIntegerv(GL_VIEWPORT, viewport);  // Get the viewport size and put them into the array viewport.

		glSelectBuffer(SIZE, selectBuf); // Create the selection buffer for preparing picking.
		glRenderMode(GL_SELECT);          // Enter into the selection mode.

		glMatrixMode(GL_PROJECTION);   // Need to create a new projection matrix. We select projection stack first.
		glPushMatrix();                // Need to save the old one, which is our projection for rendering on the screen.
		glLoadIdentity();              // Start a new projection matrix calculation.

		// Create 5x5 pixel picking region near the current mouse pointer location
		// This is where we need to pay attention to.
		//
		// Note the second parameter of gluPickMatrix. OpenGL has a different origin
		// for its window coordinates than the operation system. The second parameter
		// provides for the conversion between the two systems, i.e. it transforms the
		// origin from the upper left corner, as provided by GLUT (related to the hardware,
		// for this case, the mouse pointer's location), into the bottom left corner,
		// which is the one OpenGL uses.
		//
		// The picking region in this case is a 5x5 window. You may find that it is not
		// appropriate for your application. Do some tests to find an appropriate value
		// if you're finding it hard to pick the right objects.
		//
		gluPickMatrix((GLdouble) x, (GLdouble)(viewport[3] - y),
					  1.0, 1.0, viewport);

		gluPerspective(90, (GLfloat) windowWidth/(GLfloat) windowHeight, 1.0, 300.0);

	cout << "Cam height: " << cameraHeight << " CamX: " << cameraLookX <<  " CamY: " << cameraLookY << endl;
	cout << "Cam angle: " << cameraAngle << endl;

		calcCameraLook();
		gluLookAt(cameraPositionX, cameraHeight, cameraPositionY, cameraLookX, 0,cameraLookY, 0, 1, 0);

		//gluOrtho2D(-5, 5, -5, 5);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// This also related how sensitive we want our picking to be.
		drawBuildings(GL_SELECT);             // See below for the tricks we play here.

		glMatrixMode(GL_PROJECTION);       // Now that the projection is done,
		glPopMatrix();                     // we don't need it any more. We have to
		glFlush();                         // retrieve the project matrix for displaying on the screen.

		hits = glRenderMode(GL_RENDER);    // Leave the selection mode.
		processHits(hits, selectBuf);      // To see which objects are hit. See below

		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	glutMouseFunc(mouseFunc);

	glutMainLoop();
	return 0;
}
