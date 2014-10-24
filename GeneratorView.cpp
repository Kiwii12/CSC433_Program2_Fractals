#include "GeneratorView.h"

GeneratorView::GeneratorView(double x, double y, double w, double h)
	: View(x, y, w, h)
{
	endx = 0;
	endy = 0;
	leftButton = false;
}

void GeneratorView::mouseclick(int button, int state, double x, double y)
{
	Fractal::point p;
	
	// Cancel if point is outside view
	if (state == 0
		&& (x < this->x || y < this->y ||
			x > this->x + this->width || y > this->y + this->height))
	{
		return;
	}
	
	switch ( button )
    {
        case 0:				// left button: create objects
            if ( state == 0 )		// press - new start point
            {
				leftButton = true;

				if (generator.size() == 0)
				{
					p.x = x;
					p.y = y;
					p.angle = 0;
					p.distance = 0;
					generator.push_back(p);
				}
                // store end coordinates
                endx = x;
                endy = y;

				glLogicOp(GL_XOR);

				// Create new rubber banded line
				glColor3d( 1.0, 1.0, 1.0 );
				glBegin( GL_LINES );
					glVertex2d( generator.back().x, generator.back().y );
					glVertex2d( x, y );
				glEnd();
				
				glFlush();
				glLogicOp(GL_COPY);
            }

            else if ( state == 1 && leftButton)	// release - new endpoint
            {
				leftButton = false;

				if (x < this->x) x = this->x;
				if (y < this->y) y = this->y;
				if (x > this->x + this->width) x = this->x + this->width;
				if (y > this->y + this->height) y = this->y + this->height;

                p.x = x;
				p.y = y;
				p.angle = 0;
				p.distance = 0;
				generator.push_back(p);

                // force redraw
                glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
			if (state == 0) // pressed
			{
				// Delete last point
				if (generator.size() == 2)
				{
					generator.clear();
				}
				else if (generator.size() > 0)
				{
					generator.pop_back();
				}
			}
			break;

		default:
			break;
    }
}

void GeneratorView::mousemove(double x, double y)
{
	// TODO
}

void GeneratorView::mousedrag(double x, double y)
{
	if (generator.size() > 0 && leftButton) //left Mouse Button
    {
		glColor3d( 1.0, 1.0, 1.0 ); //makes sure color is white before draw
		glLogicOp(GL_XOR);

        // erase previous line
        glBegin( GL_LINES );
			glVertex2d( generator.back().x, generator
				.back().y );
			glVertex2d( endx, endy );
		glEnd();

		// If mouse is out of bounds, make it in bounds
		if (x < this->x) x = this->x;
		if (y < this->y) y = this->y;
		if (x > this->x + this->width) x = this->x + this->width;
		if (y > this->y + this->height) y = this->y + this->height;

        // draw new (rubberbanded) line
        glBegin( GL_LINES );
			glVertex2d( generator.back().x, generator.back().y );
			glVertex2d( x, y );
		glEnd();
		
		glFlush();
		glLogicOp(GL_COPY);
		
        endx = x;
        endy = y;
    }
}

void GeneratorView::draw()
{
	// Display every line in initiator
	if (generator.size() > 1)
	{
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		auto it1 = generator.begin();
		auto it2 = generator.begin();
		for (it2++; it2 != generator.end(); it1++, it2++)
		{
			glVertex2d(it1->x, it1->y);
			glVertex2d(it2->x, it2->y);
		}
		glEnd();
	}
	
	if (generator.size() > 2)
	{
		glLogicOp(GL_XOR);
		
		glColor3d(1.0, 1.0, 1.0);
		glLineStipple(3, 0xAAAA);

		glLogicOp(GL_COPY);
	}

	View::draw();
}
