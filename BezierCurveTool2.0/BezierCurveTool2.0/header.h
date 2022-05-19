#pragma once

int SCREEN_HEIGHT = 500;

//Point class for taking the points
class Point {
public:
    float x, y;

    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }

    //operator overloading for '=' sign
    const Point& operator=(const Point& rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

};

void drawDot(Point p1)
{
    glBegin(GL_POINTS);
    glVertex2i(p1.x, p1.y);
    glEnd();
}

void drawLine(Point p1, Point p2)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

float interpolate(float n1, float n2, float perc)
{
    float diff = n2 - n1;

    return n1 + (diff * perc);
}