//
// Created by shaun on 4/1/17.
//

#ifndef OPENGL_ROBOT_GAME_MASTER_BUILDING_H
#define OPENGL_ROBOT_GAME_MASTER_BUILDING_H

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class Building {


public:
    struct Color {
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;

        Color(GLfloat rI, GLfloat gI, GLfloat bI, GLfloat aI) {
            r = rI;
            g = gI;
            b = bI;
            a = aI;
        }

        Building::Color randomColor() {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            return Building::Color(r, g, b, a);
        }
    };

    Building(float w, float h, float xPos, float yPos, Color c, int i){
        width = w;
        height = h;
        x = xPos;
        y = yPos;
        display = true;

        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;

        id = i;

    }

    Building(float w, float h, float xPos, float yPos, int i){
        width = w;
        height = h;
        x = xPos;
        y = yPos;

        display = true;

        id = i;

        Color c = Color(1.0, 1.0, 1.0, 1.0);

        c = c.randomColor();

        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;

    }

    static int gen_id;

    int id;
    bool display;

    float width;
    float height;
    float x;
    float y;

    float r;
    float g;
    float b;
    float a;

    void draw() {

            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();

            glLoadIdentity();

            glLineWidth(1.0);

            glTranslatef(x, (height / 2) - 5, y);
            glColor4f(r, g, b, a);
            //cout << "Building drawing itself at " << x << " " << y << endl;
            glScalef(1, height, 1);

            glutSolidCube(width);
            glColor4f(0.0, 0.0, 0.0, 0.5);

            glutWireCube(width);

            glPopMatrix();

    }

};

#endif //OPENGL_ROBOT_GAME_MASTER_BUILDING_H
