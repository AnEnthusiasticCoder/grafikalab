
#define STB_IMAGE_IMPLEMENTATION
#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include "stb_image.h"

#include <array>

std::array<double, 3> calculateNormal(double* p1, double* p2, double* p3) {
    double u[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    double v[3] = { p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };

    std::array<double, 3> normal = {
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };

    double length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    for (auto& n : normal) n /= length;

    return normal;
}


void drawNormals(const std::vector<std::vector<double*>>& Points) {
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    for (size_t i = 0; i < Points.size() - 1; i++) {
        auto normal = calculateNormal(Points[i + 1][1], Points[i][1], Points[i][0]);

        double center[3] = {
            (Points[i][0][0] + Points[i][1][0] + Points[i + 1][1][0] + Points[i + 1][0][0]) / 4.0,
            (Points[i][0][1] + Points[i][1][1] + Points[i + 1][1][1] + Points[i + 1][0][1]) / 4.0,
            (Points[i][0][2] + Points[i][1][2] + Points[i + 1][1][2] + Points[i + 1][0][2]) / 4.0
        };

        glVertex3dv(center);
        glVertex3d(center[0] + normal[0] * 0.2, center[1] + normal[1] * 0.2, center[2] + normal[2] * 0.2);
    }

    glVertex3d(0, 0, 0.5);
    glVertex3d(0, 0, 0.7);

    glVertex3d(0, 0, -0.5);
    glVertex3d(0, 0, -0.7);



    auto normal = calculateNormal(Points.back()[0], Points.back()[1], Points[0][1]);
    double center[] = {
    (Points.back()[0][0] + Points.back()[1][0]+Points[0][1][0]+Points[0][0][0]) / 4.0,
    (Points.back()[0][1] + Points.back()[1][1] + Points[0][1][1] + Points[0][0][1]) / 4.0,
    (Points.back()[0][2] + Points.back()[1][2] + Points[0][1][2] + Points[0][0][2]) / 4.0
    };

    glVertex3dv(center);
    glVertex3d(center[0] -normal[0] * 0.2, center[1] - normal[1] * 0.2, center[2] -normal[2] * 0.2);

    glEnd();
}


void drawFaces(std::vector<std::vector<double*>> Points) {
    glBegin(GL_QUADS);
    for (size_t i = 0; i < Points.size() - 1; i++) {
        glColor3d(0.5-i*0.08, 0.5+i*0.08, 0.5);

        glVertex3dv(Points[i][0]);
        glVertex3dv(Points[i][1]);
        glVertex3dv(Points[i + 1][1]);
        glVertex3dv(Points[i + 1][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
        glColor3d(0.8, 0.8, 0.8);
        glVertex3dv(Points.back()[0]);
        glVertex3dv(Points.back()[1]);
        glVertex3dv(Points[0][1]);
        glVertex3dv(Points[0][0]);
    glEnd();

	glBegin(GL_QUADS);

    for (int i = 0; i < 2; i++) {
        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[0][i]);
        glVertex3dv(Points[1][i]);
        glVertex3dv(Points[2][i]);
        glVertex3dv(Points[7][i]);

        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[2][i]);
        glVertex3dv(Points[3][i]);
        glVertex3dv(Points[6][i]);
        glVertex3dv(Points[7][i]);

        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[3][i]);
        glVertex3dv(Points[4][i]);
        glVertex3dv(Points[5][i]);
        glVertex3dv(Points[6][i]);
    }
	glEnd();

}


void Render(double delta_time) {

    double A[]{ 0.2, 0.8, -0.5 };
    double A2[]{ 0.2, 0.8, 0.5 };

    double B[]{ -0.4, 0.3, -0.5 };
    double B2[]{ -0.4, 0.3, 0.5 };

    double C[]{ -0.2, 0.0, -0.5 };
    double C2[]{ -0.2, 0.0, 0.5 };

    double D[]{ -0.5, -0.5, -0.5 };
    double D2[]{ -0.5, -0.5, 0.5 };

    double E[]{ 0.1, -0.8, -0.5 };
    double E2[]{ 0.1, -0.8, 0.5 };

    double F[]{ 0.6, -0.4, -0.5 };
    double F2[]{ 0.6, -0.4, 0.5 };

    double G[]{ 0.1, 0.0, -0.5 };
    double G2[]{ 0.1, 0.0, 0.5 };

    double H[]{ 0.5, 0.3, -0.5 };
    double H2[]{ 0.5, 0.3, 0.5 };

    std::vector<std::vector<double*>> Points = {
        {A, A2}, 
        {B, B2}, 
        {C, C2}, 
        {D, D2},
        {E, E2}, 
        {F, F2}, 
        {G, G2}, 
        {H, H2}
    };

    drawFaces(Points);

    drawNormals(Points);
}










/*
#define STB_IMAGE_IMPLEMENTATION
#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include "stb_image.h"

#include <array>

double camAngle = 0.0;
double camX = 1.0, camY = 1.0, camZ = 1.0;
double targetX = 0.0, targetY = 0.0, targetZ = 0.0;


std::array<double, 3> calculateNormal(double* p1, double* p2, double* p3) {
    double u[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    double v[3] = { p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };

    std::array<double, 3> normal = {
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };

    double length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    for (auto& n : normal) n /= length;

    return normal;
}


void drawNormals(const std::vector<std::vector<double*>>& Points) {
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    for (size_t i = 0; i < Points.size() - 1; i++) {
        auto normal = calculateNormal(Points[i + 1][1], Points[i][1], Points[i][0]);

        double center[3] = {
            (Points[i][0][0] + Points[i][1][0] + Points[i + 1][1][0] + Points[i + 1][0][0]) / 4.0,
            (Points[i][0][1] + Points[i][1][1] + Points[i + 1][1][1] + Points[i + 1][0][1]) / 4.0,
            (Points[i][0][2] + Points[i][1][2] + Points[i + 1][1][2] + Points[i + 1][0][2]) / 4.0
        };

        glVertex3dv(center);
        glVertex3d(center[0] + normal[0] * 0.2, center[1] + normal[1] * 0.2, center[2] + normal[2] * 0.2);
    }

    glVertex3d(0, 0, 0.5);
    glVertex3d(0, 0, 0.7);

    glVertex3d(0, 0, -0.5);
    glVertex3d(0, 0, -0.7);



    auto normal = calculateNormal(Points.back()[0], Points.back()[1], Points[0][1]);
    double center[] = {
    (Points.back()[0][0] + Points.back()[1][0]+Points[0][1][0]+Points[0][0][0]) / 4.0,
    (Points.back()[0][1] + Points.back()[1][1] + Points[0][1][1] + Points[0][0][1]) / 4.0,
    (Points.back()[0][2] + Points.back()[1][2] + Points[0][1][2] + Points[0][0][2]) / 4.0
    };

    glVertex3dv(center);
    glVertex3d(center[0] -normal[0] * 0.2, center[1] - normal[1] * 0.2, center[2] -normal[2] * 0.2);

    glEnd();
}


void drawFaces(std::vector<std::vector<double*>> Points) {
    glBegin(GL_QUADS);
    for (size_t i = 0; i < Points.size() - 1; i++) {
        glColor3d(0.5-i*0.08, 0.5+i*0.08, 0.5);

        glVertex3dv(Points[i][0]);
        glVertex3dv(Points[i][1]);
        glVertex3dv(Points[i + 1][1]);
        glVertex3dv(Points[i + 1][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
        glColor3d(0.8, 0.8, 0.8);
        glVertex3dv(Points.back()[0]);
        glVertex3dv(Points.back()[1]);
        glVertex3dv(Points[0][1]);
        glVertex3dv(Points[0][0]);
    glEnd();

    glBegin(GL_QUADS);

    for (int i = 0; i < 2; i++) {
        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[0][i]);
        glVertex3dv(Points[1][i]);
        glVertex3dv(Points[2][i]);
        glVertex3dv(Points[7][i]);

        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[2][i]);
        glVertex3dv(Points[3][i]);
        glVertex3dv(Points[6][i]);
        glVertex3dv(Points[7][i]);

        glColor3d(0.2, 0.6, 0.8);
        glVertex3dv(Points[3][i]);
        glVertex3dv(Points[4][i]);
        glVertex3dv(Points[5][i]);
        glVertex3dv(Points[6][i]);
    }
    glEnd();

}

void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // X
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // Y
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // Z
    glEnd();
}

void Render(double delta_time) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    float amb[] = { 0.2f, 0.2f, 0.1f, 1.0f };
    float dif[] = { 0.4f, 0.65f, 0.5f, 1.0f };
    float spec[] = { 0.9f, 0.8f, 0.3f, 1.0f };
    float sh = 0.2f * 128.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT, GL_SHININESS, sh);

    float lamb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float ldif[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float lspec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lposition[] = { 2.0f, 1.5f, 1.3f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lposition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lspec);

    glDisable(GL_LIGHTING);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.8f, 0.0f);
    glVertex3fv(lposition);
    glEnd();
    glEnable(GL_LIGHTING);

    drawAxes();

    double A[]{ 0.2, 0.8, -0.5 };
    double A2[]{ 0.2, 0.8, 0.5 };
    double B[]{ -0.4, 0.3, -0.5 };
    double B2[]{ -0.4, 0.3, 0.5 };
    double C[]{ -0.2, 0.0, -0.5 };
    double C2[]{ -0.2, 0.0, 0.5 };
    double D[]{ -0.5, -0.5, -0.5 };
    double D2[]{ -0.5, -0.5, 0.5 };
    double E[]{ 0.1, -0.8, -0.5 };
    double E2[]{ 0.1, -0.8, 0.5 };
    double F[]{ 0.6, -0.4, -0.5 };
    double F2[]{ 0.6, -0.4, 0.5 };
    double G[]{ 0.1, 0.0, -0.5 };
    double G2[]{ 0.1, 0.0, 0.5 };
    double H[]{ 0.5, 0.3, -0.5 };
    double H2[]{ 0.5, 0.3, 0.5 };

    std::vector<std::vector<double*>> Points = {
        {A, A2},
        {B, B2},
        {C, C2},
        {D, D2},
        {E, E2},
        {F, F2},
        {G, G2},
        {H, H2}
    };

    camAngle += delta_time * 0.5;
    camX = 2.0 * cos(camAngle);
    camZ = 2.0 * sin(camAngle);
    camY = 1.0;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, targetX, targetY, targetZ, 0.0, 1.0, 0.0);


    drawFaces(Points);
    glDisable(GL_LIGHTING);
    drawNormals(Points);
}








*/