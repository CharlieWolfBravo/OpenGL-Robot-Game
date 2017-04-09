//Lance C
//An openGL robot.
//Call robot_body() to draw the robots body.
//Call robot_head() to draw the robots head.
#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.

#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
//#include "Building.cc"


typedef struct point{
	float x;
	float y;
	float z;
} point;

//make a vector struct to easily stor vectors.
// typedef struct{
// 	point p1;
// 	point p2;
// } vector;

class Robot{
public:

	Robot(float x, float y, int z){
		robot_center.x = x;
		robot_center.y = y;
		robot_center.z = z;
		//std::cout << "here it is...\n";
		robot_body_material[0] = 0.25;
		robot_body_material[1] = 0.25;
		robot_body_material[2] = 0.25;
		robot_body_material[3] = 1.0;
		robot_panel_material[0] = 0.0;
		robot_panel_material[1] = 0.30;
		robot_panel_material[2] = 0.35;
		robot_panel_material[3] = 0.5;
		robot_eyes_material[0] = 0.75;
		robot_eyes_material[1] = 0.0;
		robot_eyes_material[2] = 0.0;
		robot_eyes_material[3] = 1.0;
		robot_antenna_material[0] = 255.0/255.0;
		robot_antenna_material[1] =  86.0/255.0;
		robot_antenna_material[2] = 240.0/255.0;
		robot_antenna_material[3] = 0;
	}
	void robot_body(){
		glRotatef(body_ROT,0.0,1.0,0.0);
	   //draw the main rectangle
	   glPushMatrix();
	   glColor4f(0.6,0.6,0.6,1.0);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_body_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_body_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
	   glutSolidCube(1.0);//bottom part of body.
	   glColor4f(0,0,0,1);
	   glutWireCube(1.0);
	   glTranslatef(0.0,1.0,0.0);
	   glColor4f(0.6,0.6,0.6,1.0);
	   glutSolidCube(1.0);//top part of body
	   glColor4f(0,0,0,1);
	   glutWireCube(1.0);
	   glPopMatrix();
	   //Draw front panel
	   glBegin(GL_QUADS);
	   glColor4f(124.0/255.0,123.0/255.0,29.0/255.0,1.0);
	      // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
	      // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
	      // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
	      glVertex3f(-0.25,1.25,0.55);
	      glVertex3f(-0.25,-0.25,0.55);
	      glVertex3f(0.25,-0.25,0.55);
	      glVertex3f(0.25,1.25,0.55);
	   glEnd();

	   //Drawing the two triangles on the back.
	   glBegin(GL_TRIANGLES);
	   glColor4f(124.0/255.0,123.0/255.0,29.0/255.0,1.0);
	      // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
	      // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
	      // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,15.0);
	      glVertex3f(-0.25,-0.25,-0.65);
	      glVertex3f(0.0,0.5,-0.65);
	      glVertex3f(0.25,-0.25,-0.65); //First Triangle
	      //Second Triangle
	      glVertex3f(-0.25,0.55,-0.65);
	      glVertex3f(0.0,1.25,-0.65);
	      glVertex3f(0.25,0.55,-0.65);
	   glEnd();

	   //Draw the neck joint.
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,15.0);
	   glColor4f(0.0,0.0,0.0,1.0);
	   glTranslatef(0.0,1.65,0.0);
	   glutSolidSphere(0.25,180,5);
	   //glRotatef(90.0,0.0,0.0,0.0)
   }

   //Head should be translated to be at robot center up 2.0 on the y axis.
	void robot_head(){
		//glRotatef(body_ROT,0.0,1.0,0.0);
		glRotatef(head_ROT,0.0,1.0,0.0);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_body_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_body_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
		glColor4f(0.7,0.7,0.7,1.0);
	   glutSolidCube(0.75);//bottom part of body.
	   glColor4f(0.0,0.0,0.0,1.0);
	   glutWireCube(0.75);//bottom part of body.

	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_eyes_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_eyes_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
	   glPushMatrix();
	   glColor4f(1.0,0.0,0.0,1.0);
	   glTranslatef(-0.1875,0.1875,0.375);
	   glutSolidSphere(0.125,10.0,10.0);
	   glPopMatrix();
	   glPushMatrix();
	   glTranslatef(0.1875,0.1875,0.375);
	   glutSolidSphere(0.125,10.0,10.0);
	   glPopMatrix();
	   //draw and rotate antenna
	   
	   glPushMatrix();
	   glColor4f(250.0/255.0,104.0/255.0,237.0/255.0,1.0);
	   glRotatef(270.0,1.0,0.0,0.0);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_antenna_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_antenna_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5.0);
	   glutSolidCone(0.2875,1.0,360,10);
	   glPopMatrix();

	   //Mouth
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
	   // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5.0);
	   glColor4f(0.0,0.0,1.0,1.0);
	   glBegin(GL_QUADS);
	      glVertex3f(-0.1,-0.09375,0.38);
	      glVertex3f(-0.1,-0.1875,0.38);
	      glVertex3f(0.1,-0.1875,0.38);
	      glVertex3f(0.1,-0.09375,0.38);
	   glEnd();
	}

	//The points for the robot should go here.
	point robot_center;

	int direction;

	
	//Body and head rotations.
	GLfloat head_ROT;
	GLfloat body_ROT;

	//Robot materials
	GLfloat robot_body_material[4];
	GLfloat robot_panel_material[4];
	GLfloat robot_eyes_material[4];
	GLfloat robot_antenna_material[4];
	
		
};
#endif