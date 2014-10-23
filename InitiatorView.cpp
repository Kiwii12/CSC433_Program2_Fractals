#include "InitiatorView.h"
#include <iostream>
using namespace std;

InitiatorView::InitiatorView(double x, double y, double w, double h)
	: View(x, y, w, h)
{
	startx = 0;
	starty = 0;
	endx = 0;
	endy = 0;
}

void InitiatorView::mouseclick(int button, int state, double x, double y)
{
	Fractal::point p;
	glColor3d( 1.0, 1.0, 1.0 ); //makes sure color is white  before draw
	switch ( button )
    {
        case 0:				// left button: create objects
            if ( state == 0 )		// press - new start point
            {
				cout << "mouse click: left press at    (" << x << "," << y << ")\n";
                // store start coordinates
                startx = endx = x;
                starty = endy = height - y;

				p.x = startx;
				p.y = starty;
				p.angle = 0;
				p.distance = 0;
				initiator.push_back(p);

                // start XORing (rubberbanding)
                glLogicOp( GL_XOR );

                // draw first Line (actually unnecessary)
               	glBegin( GL_LINES );
					glVertex2d( startx, starty );
					glVertex2d( endx, endy );
				glEnd();
				glFlush();
            }

            else if ( state == 1 )	// release - new endpoint
            {
                // erase last rectangle (actually unnecessary)
                glBegin( GL_LINES );
					glVertex2d( startx, starty );
					glVertex2d( endx, endy );
				glEnd();
				glFlush();

                // store end coordinates
                endx = x;
                endy = y;

				p.x = endx;
				p.y = endy;
				p.angle = 0;
				p.distance = 0;
				initiator.push_back(p);

                // restore copy mode
                glLogicOp( GL_COPY );

                // force redraw
                glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
            break;
    }

    lastButton = button;
}

void InitiatorView::mousemove(double x, double y)
{
	// TODO
}

void InitiatorView::mousedrag(double x, double y)
{
	glColor3d( 1.0, 1.0, 1.0 ); //makes sure color is white before draw
	if ( lastButton == 0 ) //left Mouse Button
    {
        // erase previous rectangle
        glBegin( GL_LINES );
			glVertex2d( startx, starty );
			glVertex2d( endx, endy );
		glEnd();
		glFlush();

        // draw new (rubberbanded) rectangle
        endx = x;
        endy = y;
        glBegin( GL_LINES );
			glVertex2d( startx, starty );
			glVertex2d( endx, endy );
		glEnd();
		glFlush();
    }
}

void InitiatorView::draw()
{
	// TODO
}
