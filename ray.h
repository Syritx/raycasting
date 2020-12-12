//
//  ray.h
//  raycaster
//
//  Created by Syritx on 2020-12-11.
//

#ifndef ray_h
#define ray_h

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DEG2RAD 0.0174533
#define FOV 90

float angle;
int resolution = 8;
int mapScale = resolution*resolution;


int map[] {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

float pythagorean(float ax, float ay, float bx, float by) {
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void renderRays(float xPlayer, float yPlayer) {
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, dist;
    
    ra = angle-DEG2RAD*(FOV/2);
    if (ra < 0) ra += 2*PI;
    if (ra > 2*PI) ra -= 2*PI;
    
    
    for (r = 0; r < FOV; r++) {
        dof = 0;
        float hDist = 1000,
              hxRay = xPlayer,
              hyRay = yPlayer;
        float atan = -1/tan(ra);
        
        if (ra>PI) {
            ry = (((int)yPlayer>>6)<<6)-0.0001;
            rx = (yPlayer-ry)*atan+xPlayer;
            
            yo = -mapScale;
            xo = -yo*atan;
        }
        
        if (ra<PI) {
            ry = (((int)yPlayer>>6)<<6)+mapScale;
            rx = (yPlayer-ry)*atan+xPlayer;
            
            yo = mapScale;
            xo = -yo*atan;
        }
        
        if (ra == 0 || ra == PI) {
            rx = xPlayer;
            ry = yPlayer;
            dof = 8;
        }
        
        while (dof < resolution) {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my*resolution+mx;
            
            if (mp > 0 && mp < resolution*resolution && map[mp] == 1) {
                hxRay = rx;
                hyRay = ry;
                hDist = pythagorean(xPlayer, yPlayer, hxRay, hyRay);
                dof = resolution;
            }
            
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        
        dof = 0;
        float vDist = 1000000,
              vxRay = xPlayer,
              vyRay = yPlayer;
        
        float ntan = -tan(ra);
        
        if (ra > P2 && ra < P3) {
            rx = (((int)xPlayer>>6)<<6)-0.0001;
            ry = (xPlayer-rx)*ntan+yPlayer;
            
            xo = -mapScale;
            yo = -xo*ntan;
        }
        
        if (ra < P2 || ra > P3) {
            rx = (((int)xPlayer>>6)<<6)+mapScale;
            ry = (xPlayer-rx)*ntan+yPlayer;
            
            xo = mapScale;
            yo = -xo*ntan;
        }
        
        if (ra == 0 || ra == PI) {
            rx = xPlayer;
            ry = yPlayer;
            dof = resolution;
        }
        
        while (dof < resolution) {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my*resolution+mx;
            
            if (mp > 0 && mp < resolution*resolution && map[mp] == 1) {
                
                vxRay = rx;
                vyRay = ry;
                
                vDist = pythagorean(xPlayer, yPlayer, vxRay, vyRay);
                dof = resolution;
            }
            
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        
        if (vDist < hDist) {
            rx = vxRay;
            ry = vyRay;
            dist = vDist;
            glColor3f(0.9, 0.0, 0.0);
        }
        
        if (vDist > hDist) {
            rx = hxRay;
            ry = hyRay;
            dist = hDist;
            glColor3f(0.7, 0.0, 0.0);
        }
        
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2i(xPlayer, yPlayer);
        glVertex2i(rx, ry);
        glEnd();
        
        float ca = angle - ra;
        if (ca < 0) ca += 2*PI;
        if (ca > 2*PI) ca -= 2*PI;
        
        dist = dist * cos(ca);
        
        float lineH = (mapScale*320)/dist, lineO = 160-lineH/2;
        if (lineH > 320) lineH = 320;
        
        glLineWidth(12);
        glBegin(GL_LINES);
        
        glVertex2i(r*8+530, lineO);
        glVertex2i(r*8+530, lineH+lineO);
        glEnd();
        
        ra += DEG2RAD;
        if (ra < 0) ra += 2*PI;
        if (ra > 2*PI) ra -= 2*PI;
    }
}


#endif /* ray_h */
