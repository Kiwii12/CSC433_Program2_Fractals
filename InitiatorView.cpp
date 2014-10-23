#include "InitiatorView.h"

InitiatorView::InitiatorView(double x, double y, double w, double h)
	: x(x), y(y), width(w), height(h)
{
	
}

void InitiatorView::mouseclick(int button, int state, int x, int y)
{
	switch ( button )
    {
        case MouseLeftButton:				// left button: create objects
            if ( state == MouseButtonPress )		// press - new start point
            {
                // store start coordinates
                startx = endx = x;
                starty = endy = ScreenHeight - y;

                // start XORing (rubberbanding)
                glLogicOp( GL_XOR );

                // draw first rectangle (actually unnecessary)
                DrawRectangle( startx, starty, endx, endy, White );
            }

            else if ( state == MouseButtonRelease )	// release - new endpoint
            {
                // erase last rectangle (actually unnecessary)
                DrawRectangle( startx, starty, endx, endy, White );

                // store end coordinates
                endx = x;
                endy = ScreenHeight - y;

                // restore copy mode
                glLogicOp( GL_COPY );

                // force redraw
                glutPostRedisplay();
            }

            break;

        case MouseMiddleButton:				// middle button: not used
            break;

        case MouseRightButton:				// right button: not used
            break;
    }

    lastbutton = button;
}

void InitiatorView::mousemove(int x, int y)
{
	// TODO
}

void InitiatorView::mousedrag(int x, int y)
{
	// TODO
}

void InitiatorView::draw()
{
	// TODO
}
