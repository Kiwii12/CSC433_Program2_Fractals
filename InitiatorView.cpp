#include "InitiatorView.h"

InitiatorView::InitiatorView(double x, double y, double w, double h)
	: View(x, y, w, h)
{
	
}

void InitiatorView::mouseclick(int button, int state, double x, double y)
{
	int startx = 0;
	int starty = 0;
	int endx = 0;
	int endy = 0;
	switch ( button )
    {
        case 0:				// left button: create objects
            if ( state == 0 )		// press - new start point
            {
                // store start coordinates
                startx = endx = x;
                starty = endy = height - y;

                // start XORing (rubberbanding)
                glLogicOp( GL_XOR );

                // draw first Line (actually unnecessary)
               	glBegin( GL_LINES );
					glVertex2i( startx, starty );
					glVertex2i( endx, endy );
				glEnd();
            }

            else if ( state == 1 )	// release - new endpoint
            {
                // erase last rectangle (actually unnecessary)
                glBegin( GL_LINES );
					glVertex2i( startx, starty );
					glVertex2i( endx, endy );
				glEnd();

                // store end coordinates
                endx = x;
                endy = height - y;

                // restore copy mode
                glLogicOp( GL_COPY );

                // force redraw
                glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
            break;
    }

    lastbutton = button;
}

void InitiatorView::mousemove(double x, double y)
{
	// TODO
}

void InitiatorView::mousedrag(double x, double y)
{
	// TODO
}

void InitiatorView::draw()
{
	// TODO
}
