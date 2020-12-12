//
//  main.cpp
//  raycaster
//
//  Created by Syritx on 2020-12-09.
//

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <ctype.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DEG2RAD 0.0174533

#include "ray.h"
#include "player.h"
void renderMap();

void renderMap() {
    int x, y, xOff, yOff;
    
    for (y = 0; y < resolution; y++) {
        for (x = 0; x < resolution; x++) {
            if (map[y*resolution+x]==1) {
                glColor3f(1, 1, 1);
            }
            else {
                glColor3f(0, 0, 0);
            }
            
            xOff = x*mapScale;
            yOff = y*mapScale;
            glBegin(GL_QUADS);
            glVertex2i(xOff,          yOff);
            glVertex2i(xOff,          yOff+mapScale);
            glVertex2i(xOff+mapScale, yOff+mapScale);
            glVertex2i(xOff+mapScale, yOff);
            glEnd();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (tolower(key) == 'w') {
        xPlayer += xDelta*2;
        yPlayer += yDelta*2;
    }
    if (tolower(key) == 's') {
        xPlayer -= xDelta*2;
        yPlayer -= yDelta*2;
    }
    
    if (tolower(key) == 'a') {
        angle -= 0.1;
        
        if (angle < 0) angle += 2*PI;
        xDelta = cos(angle)*5;
        yDelta = sin(angle)*5;
    }
    if (tolower(key) == 'd') {
        angle += 0.1;
        
        if (angle > 2*PI) angle -= 2*PI;
        xDelta = cos(angle)*5;
        yDelta = sin(angle)*5;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 1024, 512, 0);
    xPlayer = 300;
    yPlayer = 300;
    
    xDelta = cos(angle)*5;
    yDelta = sin(angle)*5;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderMap();
    renderRays(xPlayer, yPlayer);
    renderPlayer();
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 512);
    glutCreateWindow("hello");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
