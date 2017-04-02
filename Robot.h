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

#include <stdbool.h>

static GLfloat robot_body_material[] = {0.25,0.25,0.25,1.0};
static GLfloat robot_panel_material[] = {0.0,0.30,0.35,0.5};
static GLfloat robot_eyes_material[] = {0.75,0.0,0.0,1.0};
static GLfloat robot_antenna_material[] = {255.0/255.0, 86.0/255.0, 240.0/255.0};


typedef struct point{
	float x;
	float y;
	float z;
} point;

//make a vector struct to easily stor vectors.
typedef struct{
	point p1;
	point p2;
} vector;

class Robot{
public:

	Robot(float x, float y, int z){
		robot_center.x = x;
		robot_center.y = y;
		robot_center.z = z;
	}
	void robot_body(){
   //draw the main rectangle
   
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_body_material);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_body_material);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
   glutSolidCube(1.0);//bottom part of body.
   glTranslatef(0.0,1.0,0.0);
   glutSolidCube(1.0);//top part of body
   glPopMatrix();
   //Draw front panel
   glBegin(GL_QUADS);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
      glVertex3f(-0.25,1.25,0.55);
      glVertex3f(-0.25,-0.25,0.55);
      glVertex3f(0.25,-0.25,0.55);
      glVertex3f(0.25,1.25,0.55);
   glEnd();

   //Drawing the two triangles on the back.
   glBegin(GL_TRIANGLES);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,15.0);
      glVertex3f(-0.25,-0.25,-0.65);
      glVertex3f(0.0,0.5,-0.65);
      glVertex3f(0.25,-0.25,-0.65); //First Triangle
      //Second Triangle
      glVertex3f(-0.25,0.55,-0.65);
      glVertex3f(0.0,1.25,-0.65);
      glVertex3f(0.25,0.55,-0.65);
   glEnd();

   //Draw the neck joint.
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,15.0);
   glTranslatef(0.0,1.65,0.0);
   glutSolidSphere(0.25,180,5);
   //glRotatef(90.0,0.0,0.0,0.0)
   }

   //Head should be translated to be at robot center up 2.0 on the y axis.
	void robot_head(){
	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_body_material);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_body_material);
	   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
	   glutSolidCube(0.75);//bottom part of body.

	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_eyes_material);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_eyes_material);
	   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10.0);
	   glPushMatrix();
	   glTranslatef(-0.1875,0.1875,0.375);
	   glutSolidSphere(0.125,10.0,10.0);
	   glPopMatrix();
	   glPushMatrix();
	   glTranslatef(0.1875,0.1875,0.375);
	   glutSolidSphere(0.125,10.0,10.0);
	   glPopMatrix();
	   //draw and rotate antenna
	   
	   glPushMatrix();
	   glRotatef(270.0,1.0,0.0,0.0);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_antenna_material);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_antenna_material);
	   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5.0);
	   glutSolidCone(0.2875,1.0,360,10);
	   glPopMatrix();

	   //Mouth
	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, robot_panel_material);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, robot_panel_material);
	   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5.0);
	   glBegin(GL_QUADS);
	      glVertex3f(-0.1,-0.09375,0.38);
	      glVertex3f(-0.1,-0.1875,0.38);
	      glVertex3f(0.1,-0.1875,0.38);
	      glVertex3f(0.1,-0.09375,0.38);
	   glEnd();
	}

	//The points for the robot should go here.
	point robot_center;
	//Materials for the robot.
	
		
};
#endif