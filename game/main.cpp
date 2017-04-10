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

#include "Building.cc"
#include "Robot.cc"
#include <bits/stdc++.h>


static GLuint ground;
static GLuint sky;
static GLuint horizon;

vector<Building*> buildings;

float cameraHeight = -2;
float cameraLookX = 0;
float cameraLookZ = 0;

float cameraPositionX = 0;
float cameraPositionY = -2;
float cameraPositionZ = 0;

float originalCamPosZ = 0;
float originalCamPosX = 0;

float cameraAngle = 0;
float cameraDistance = 1;

GLfloat windowWidth = 0;
GLfloat windowHeight = 0;

int Building::gen_id = 0;

int SIZE = 1024;

int camera_state = 0;
int startingBody = 0;

bool firstRun = true;
bool moving = false;

//VARIABLES TO HELP TRACK ROBOT
Robot Philip(0,-4.5,0);

bool paused;

void cameraAnimLeft(int value) {
	switch(value){
		case 0:
			//cameraPositionX = Philip.robot_center.x;
			if (cameraPositionZ >= originalCamPosZ - 5) {

				cameraPositionZ -= 0.1;
				cameraPositionX -= 0.1;
				glutTimerFunc(20, cameraAnimLeft, value);

			} else {
				cameraPositionZ = originalCamPosZ - 5;
				cameraPositionX = Philip.robot_center.x;
				moving = false;

			}

			break;
		case 2:
			//cameraPositionX = Philip.robot_center.x;
			if (cameraPositionZ <= originalCamPosZ + 5) {
				cameraPositionZ += 0.1;
				cameraPositionX += 0.1;

				glutTimerFunc(20, cameraAnimLeft, value);
			} else {
				cameraPositionZ = originalCamPosZ + 5;
				cameraPositionX = Philip.robot_center.x;
				moving = false;


			}
			break;
		case 1:
			if (cameraPositionX >= originalCamPosX - 5) {
				cameraPositionX -= 0.1;
				cameraPositionZ += 0.1;

				glutTimerFunc(20, cameraAnimLeft, value);
			} else {
				cameraPositionX = originalCamPosX - 5;
				cameraPositionZ = Philip.robot_center.z;
				moving = false;


			}

			break;
		case 3:
			if (cameraPositionX <= originalCamPosX + 5) {
				cameraPositionX += 0.1;
				cameraPositionZ -= 0.1;

				glutTimerFunc(20, cameraAnimLeft, value);
			} else {
				cameraPositionX = originalCamPosX + 5;
				cameraPositionZ = Philip.robot_center.z;
				moving = false;

			}
			break;
	}
}

void cameraAnimRight(int value) {
	switch(value){
		case 0:
			//cameraPositionX = Philip.robot_center.x;
			if (cameraPositionX <= originalCamPosX + 5) {

				cameraPositionZ += 0.1;
				cameraPositionX += 0.1;
				glutTimerFunc(20, cameraAnimRight, value);

			} else {
				cameraPositionX = originalCamPosX + 5;
				cameraPositionZ = Philip.robot_center.z;
				moving = false;


			}

			break;
		case 2:
			if (cameraPositionX >= originalCamPosX - 5) {
				cameraPositionZ -= 0.1;
				cameraPositionX -= 0.1;

				glutTimerFunc(20, cameraAnimRight, value);
			} else {
				cameraPositionX = originalCamPosX - 5;
				cameraPositionZ = Philip.robot_center.z;
				moving = false;

			}
			break;
		case 1:
			//cameraPositionX = Philip.robot_center.x;
			if (cameraPositionZ >= originalCamPosZ - 5) {
				cameraPositionZ -= 0.1;
				cameraPositionX += 0.1;

				glutTimerFunc(20, cameraAnimRight, value);
			} else {
				cameraPositionZ = originalCamPosZ - 5;
				cameraPositionX = Philip.robot_center.x;
				moving = false;


			}

			break;
		case 3:
			if (cameraPositionZ <= originalCamPosZ + 5) {
				cameraPositionZ += 0.1;
				cameraPositionX -= 0.1;

				glutTimerFunc(20, cameraAnimRight, value);
			} else {
				cameraPositionZ = originalCamPosZ + 5;
				cameraPositionX = Philip.robot_center.x;
				moving = false;


			}
			break;
	}
}

void calcCameraLook(){
	switch(camera_state){
		case 0:
			cameraPositionY = -2;

			if (firstRun || moving == false) {

				switch (Philip.direction) {
					case 0:
						cameraPositionX = Philip.robot_center.x;
						cameraPositionZ = Philip.robot_center.z - 5;
						break;
					case 2:
						cameraPositionX = Philip.robot_center.x;
						cameraPositionZ = Philip.robot_center.z + 5;
						break;
					case 1:
						cameraPositionX = Philip.robot_center.x - 5;
						cameraPositionZ = Philip.robot_center.z;
						break;
					case 3:
						cameraPositionX = Philip.robot_center.x + 5;
						cameraPositionZ = Philip.robot_center.z;
						break;


				}
				firstRun = false;
			}
		break;
		case 6:
			switch(Philip.direction){
				case 0://north
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 2://south
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 1://east
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 3://west
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
			}
		break;
		case 5:
			switch(Philip.direction){
				case 0://north
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 2://south
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 1://east
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 3://west
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
			}
		break;
		case 7:
			switch(Philip.direction){
				case 0://north
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 2://south
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 1://east
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 3://west
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
			}
		break;
		case 8:
			switch(Philip.direction){
				case 0://north
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
				case 2://south
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 1://east
					cameraPositionX = Philip.robot_center.x+5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z-5;
				break;
				case 3://west
					cameraPositionX = Philip.robot_center.x-5;
					cameraPositionY = -1;
					cameraPositionZ = Philip.robot_center.z+5;
				break;
			}
	}

	cameraLookZ = Philip.robot_center.z;
	cameraLookX = Philip.robot_center.x;
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

			//cout << "X: " << startX << " Y: "<< startY<< endl;


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

			//cout << "X: " << startX << " Y: "<< startY<< endl;

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

			//cout << "X: " << startX << " Y: "<< startY<< endl;


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

			//cout << "X: " << startX << " Y: "<< startY<< endl;

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
	//out << "wat...\n";
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);

	// create some building
	buildingInit();
	//cout << "Starting robot...\n";
	Philip.head_ROT = 0;
	Philip.body_ROT = 0;
	Philip.direction = 0;
}

void destroy(int value) {

	if (buildings[value]->height >= 0) {
		buildings[value]->height -= 0.1;
	}
}

void rotateAnim(int value) {
	if (value == 1) {
		if (Philip.body_ROT <= startingBody + 90){
			Philip.body_ROT += 2.5;
			glutTimerFunc(20, rotateAnim, 1);
		} else {
			Philip.body_ROT = startingBody + 90;
		}
	} else {
		if (Philip.body_ROT >= startingBody - 90){
			Philip.body_ROT -= 2.5;
			glutTimerFunc(20, rotateAnim, -1);
		} else {
			Philip.body_ROT = startingBody - 90;

		}
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


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawBuildings(mode);

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

void cameraFunc(){
	
	gluPerspective(90, (GLfloat) windowWidth/(GLfloat) windowHeight, 1.0, 300.0);

	calcCameraLook();

	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ, cameraLookX, Philip.robot_center.y+2,cameraLookZ, 0, 1, 0);
}

void reshape(int w, int h)
{
	windowHeight = h;
	windowWidth = w;


	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLfloat) w/(GLfloat) h, 1.0, 300.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool valid_forward(){
	int x1 = Philip.robot_center.x, x2 = Philip.robot_center.z;
	if((x1%10) == 0 || (x2%10) == 0){
		//cout<< (x1%10)<<" "<<(x2%10)<<endl;
		return true;
	}
	//cout << "cant walk on grass...\n";
	return false;
}

void forwardMove(){
	if(valid_forward()){
		int x1 = Philip.robot_center.x, x2 = Philip.robot_center.z;
		switch (Philip.direction){
			case 0://n
				if(x1 % 10 == 0 && x2 < 40)
					Philip.robot_center.z +=1.0;
				break;
			case 1://e
				if(x2 % 10 == 0 && x1 < 40)
					Philip.robot_center.x +=1.0;
				break;
			case 2://s
				if(x1 % 10 == 0 && x2 > -40)
					Philip.robot_center.z -=1.0;
				break;
			case 3://w
				if(x2 % 10 == 0 && x1 > -40)
					Philip.robot_center.x -=1.0;
				break;
		}
		//cout << Philip.robot_center.x << " " << Philip.robot_center.z << "\n";
	}
}

void Turn(char t){
	int x1 = Philip.robot_center.x, x2 = Philip.robot_center.z;
	if(x1 % 10 == 0 && x2%10 == 0)
		if (moving == false) {
			switch (t) {
				case 'q':
					//check for intesection here.
					glutTimerFunc(20, rotateAnim, 1);
					startingBody = Philip.body_ROT;
					//Philip.body_ROT += 90;
					Philip.direction = (Philip.direction + 1) % 4;
					originalCamPosX = cameraPositionX;
					originalCamPosZ = cameraPositionZ;
					glutTimerFunc(20, cameraAnimLeft, Philip.direction);
					moving = true;

					break;
				case 'a':
					//check for intesection here.
					glutTimerFunc(20, rotateAnim, -1);
					originalCamPosX = cameraPositionX;
					originalCamPosZ = cameraPositionZ;
					glutTimerFunc(20, cameraAnimRight, Philip.direction);
					//Philip.body_ROT -= 90;
					startingBody = Philip.body_ROT;
					Philip.direction = (Philip.direction + 3) % 4;
					moving = true;
					break;
			}
		}
}

void keyboard (unsigned char key, int x, int y)
{
	if(key == 'p'){
		paused = !paused;
	}
	if(!paused){
		switch (key) {
			case 27:
				exit(0);
				break;
			case 'z':
				forwardMove();
				break;
			case 'q':
				Turn('q');
				break;
			case 'a':
				Turn('a');
				break;
			case 'r':
				Philip.robot_center.x = 0;
				Philip.robot_center.z = 0;

				break;
			default:
			//cout << "key: " << key << endl;
				break;
		}
	}

}

void SpecialInput(int key, int x, int y) {
	if(!paused){
		switch (key) {
			case GLUT_KEY_F1:
				Philip.head_ROT = 0;
				break;
			case GLUT_KEY_F5:
				camera_state = 5;
				break;
			case GLUT_KEY_F6:
				camera_state = 6;
				break;
			case GLUT_KEY_F8:
				camera_state = 8;
				break;
			case GLUT_KEY_F7:
				camera_state = 7;
				break;
			case GLUT_KEY_F4:
				camera_state = 0;
				break;
		}
		if(key == GLUT_KEY_F2){
			Philip.head_ROT = -90;
		}else if(key == GLUT_KEY_F3){
			Philip.head_ROT = 90;
		}
	}
}
void upFunc(int c, int x, int y){
	//cout << c << "!!!!!!!!!!\n";
	if(c == GLUT_KEY_F2 || c == GLUT_KEY_F3){
		Philip.head_ROT = 0;
		//cout << "realeased...\n";
	}

}

void processHits(GLint hits, GLuint buffer[])
/* this is the same "boiler plate" as before */
{
	unsigned int i, j;
	GLint ii, jj, names, *ptr;

	//printf ("hits = %d\n", hits);
	ptr = (GLint *) buffer;

	int maxDepth = 0;
	int minId = 0;
	//cout << "Help...\n";
	if(hits == 0) return;
	cout << "Mouse click" << endl;
	for (i = 0; i < hits; i++) { // For each hit record,
		names = *ptr;             // How many names are in this hit record?
		ptr++;
		int thing1 = *ptr;
		ptr++;
		int thing2 = *ptr;
		ptr++;
		int id = *ptr;

		if (maxDepth < thing1*-1) {
			maxDepth = thing1 * -1;
			cout << thing1 * -1 << endl;
			minId = id;
		}
		ptr++;
		// Skip the depth min and max information.
		cout << "hit record " << endl;
		cout << names << " " <<  thing1 << " " << thing2 << " " << id << endl;
	}

	buildings[minId]->display = false;
	//cout << "End of Processing hits" << endl;
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

		gluPickMatrix((GLdouble) x, (GLdouble)(viewport[3] - y),
					  5.0, 5.0, viewport);

		cameraFunc();

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

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	cameraFunc();
	//cout << "Drawing...\n";
	draw_environment(GL_RENDER);
	glTranslatef(Philip.robot_center.x,Philip.robot_center.y,Philip.robot_center.z);
	Philip.robot_body();
	glTranslatef(0,0.4,0);
	Philip.robot_head();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//cout << "Hello there!\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);

	windowHeight = 750;
	windowWidth = 750;
	//cout << "wat\n";
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialUpFunc(upFunc);
	glutSpecialFunc(SpecialInput);
	glutMouseFunc(mouseFunc);
	//cout << "ready...\n";
	glutMainLoop();
	return 0;
}
