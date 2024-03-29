#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include "header.h"

using namespace std;

vector<Point> Points;
Point Tangent;
Point inverseTangent;
Point cursorLocationLive;
Point p2;
int TangentsSize = 0;
vector<Point> Tangents(TangentsSize);
vector<Point> inverseTangents(TangentsSize);
vector<Point> BezierCurve;
bool MouseReleased = false;
bool PrevMouse = false;

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            MouseReleased = false;
            // Store points into Points vector on click
            Point point;
            point.setxy(x, SCREEN_HEIGHT - y);
            Points.push_back(point);

            // Tangents are set to the cursor position
            Tangent.setxy(x, SCREEN_HEIGHT - y);
            inverseTangent.x = (2 * Points[Points.size() - 1].x) - Tangent.x;
            inverseTangent.y = (2 * Points[Points.size() - 1].y) - Tangent.y;

            /*Add new element to Tangent & inverseTangent so when we draw the curve
            the tangents are accessed at the right index*/
            TangentsSize++;
        }
        else if (state == GLUT_UP)
        {
            MouseReleased = true;
            // Upon mouse release store tangent and inverse tangent into separate vectors
            Tangents.push_back(Tangent);
            inverseTangents.push_back(inverseTangent);
        }
    }
}

void passiveMotion(int x, int y)
{
    // Sets the location of cursor while moving with no buttons pressed
    cursorLocationLive.setxy(x, SCREEN_HEIGHT - y);
}

void motion(int x, int y)
{
    // Sets the coordinates of the tangents when mouse moves with a button held down
    Tangent.setxy(x, SCREEN_HEIGHT - y);
    inverseTangent.x = (2 * Points[Points.size() - 1].x) - Tangent.x;
    inverseTangent.y = (2 * Points[Points.size() - 1].y) - Tangent.y;
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw live tangent dots in green
    glColor3f(0, 255, 0);
    drawDot(Tangent);
    drawDot(inverseTangent);
    // Draw live tangent lines in blue
    glColor3f(0, 0, 255);
    drawLine(Tangent, inverseTangent);

    // Draw main points in red
    glColor3f(255, 0, 0);
    for (int i = 0; i < Points.size(); i++)
    {
        drawDot(Points[i]);
    }

    // If there is a starting point draw a line to cursor from last drawn point in passive motion
    if (Points.size() > 0)
    {
        glColor3f(0, 0, 0);
        drawLine(Points[Points.size() - 1], cursorLocationLive);
    }

    for (int i = 0; i < Tangents.size(); i++)
    {
        // Draw stored tangent dots in green
        glColor3f(0, 255, 0);
        drawDot(Tangents[i]);
        drawDot(inverseTangents[i]);
        // Draw stored tangent lines in blue
        glColor3f(0, 0, 255);
        drawLine(Tangents[i], inverseTangents[i]);
    }

    // Curve Generator (The most recent curve segment is drawn even if stored)
    if (Points.size() >= 2)
    {
        // p1 is the start of the curve set to second last point
        Point p1;
        p1 = Points[Points.size() - 2];

        float i;
        // Calculate curve coordinates
        for (float j = 0; j <= 100; j++)
        {
            i = j / 100;
            // The Green Lines
            float xa = interpolate(Points[Points.size() - 2].x, Tangents[TangentsSize - 2].x, i);
            float ya = interpolate(Points[Points.size() - 2].y, Tangents[TangentsSize - 2].y, i);
            float xb = interpolate(Tangents[TangentsSize - 2].x, inverseTangent.x, i);
            float yb = interpolate(Tangents[TangentsSize - 2].y, inverseTangent.y, i);
            float xc = interpolate(inverseTangent.x, Points[Points.size() - 1].x, i);
            float yc = interpolate(inverseTangent.y, Points[Points.size() - 1].y, i);

            // The Blue Line
            float xm = interpolate(xa, xb, i);
            float ym = interpolate(ya, yb, i);
            float xn = interpolate(xb, xc, i);
            float yn = interpolate(yb, yc, i);

            // The Black Dot
            float x2 = interpolate(xm, xn, i);
            float y2 = interpolate(ym, yn, i);

            p2.setxy(x2, y2);

            glColor3f(0, 0, 0);
            drawLine(p1, p2);

            p1 = p2;

            // If the mouse is released after an edit, save points.
            if (MouseReleased == true && PrevMouse == false)
            {
                BezierCurve.push_back(p2);
            }
        }
    }

    // Draw all bezier curvature
    for (int i = 1; i < BezierCurve.size(); i++)
    {
        drawLine(BezierCurve[i - 1], BezierCurve[i]);
    }

    // Save the mouse state for the next frame
    PrevMouse = MouseReleased;

    glutSwapBuffers();
}

void timer(int)
{
    glutTimerFunc(1000 / 60, timer, 0);
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(myMouse);
    glutPassiveMotionFunc(passiveMotion);
    glutMotionFunc(motion);
    glClearColor(255, 255, 255, 0.0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 500.0);
    glutMainLoop();

    return 0;
}