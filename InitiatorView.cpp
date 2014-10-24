#include "InitiatorView.h"

InitiatorView::InitiatorView(double x, double y, double w, double h)
	: View(x, y, w, h)
{
	endx = 0;
	endy = 0;
	leftButton = false;
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
				leftButton = true;

				if (initiator.size() == 0)
				{
					p.x = x;
					p.y = y;
					p.angle = 0;
					p.distance = 0;
					initiator.push_back(p);
				}
                // store end coordinates
                endx = x;
                endy = y;

				glBegin( GL_LINES );
					glVertex2d( initiator.back().x, initiator.back().y );
					glVertex2d( x, y );
				glEnd();
				glFlush();
            }

            else if ( state == 1 )	// release - new endpoint
            {
				leftButton = false;

                p.x = x;
				p.y = y;
				p.angle = 0;
				p.distance = 0;
				initiator.push_back(p);

                // force redraw
                glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
			if (state == 0) // pressed
			{
				// Delete last point
				if (initiator.size() == 2)
				{
					initiator.clear();
				}
				else if (initiator.size() > 0)
				{
					initiator.pop_back();
				}
			}
			break;

		default:
			break;
    }
}

void InitiatorView::mousemove(double x, double y)
{
	// TODO
}

void InitiatorView::mousedrag(double x, double y)
{
	if (initiator.size() > 0 && leftButton) //left Mouse Button
    {
		glColor3d( 1.0, 1.0, 1.0 ); //makes sure color is white before draw
		glLogicOp(GL_XOR);

        // erase previous line
        glBegin( GL_LINES );
			glVertex2d( initiator.back().x, initiator.back().y );
			glVertex2d( endx, endy );
		glEnd();

        // draw new (rubberbanded) line
        endx = x;
        endy = y;
        glBegin( GL_LINES );
			glVertex2d( initiator.back().x, initiator.back().y );
			glVertex2d( x, y );
		glEnd();
		glFlush();
		
		glLogicOp(GL_COPY);
    }
}

void InitiatorView::draw()
{
	// Display every line in initiator
	if (initiator.size() > 1)
	{
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		auto it1 = initiator.begin();
		auto it2 = initiator.begin();
		for (it2++; it2 != initiator.end(); it1++, it2++)
		{
			glVertex2d(it1->x, it1->y);
			glVertex2d(it2->x, it2->y);
		}
		glEnd();
	}
	
	if (initiator.size() > 2)
	{
		glColor3d(0.75, 0.75, 0.75);
		glLineStipple(3, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		glVertex2d(initiator.back().x, initiator.back().y);
		glVertex2d(initiator.front().x, initiator.front().y);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}

	View::draw();
}
