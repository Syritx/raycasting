//
//  player.h
//  raycaster
//
//  Created by Syritx on 2020-12-11.
//

#ifndef player_h
#define player_h

float xPlayer, yPlayer, xDelta, yDelta;
void renderPlayer() {
    glColor3f(1,1,0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(xPlayer, yPlayer);
    glEnd();
    glFlush();
    
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i(xPlayer, yPlayer);
    glVertex2i(xPlayer+xDelta*5, yPlayer+yDelta*5);
    glEnd();
}

#endif /* player_h */
