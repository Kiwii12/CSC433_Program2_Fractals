#include "FractalView.h"

FractalView::FractalView(double x, double y, double w, double h)
	: View(x, y, w, h)
{
	
}

void FractalView::calculate()
{
	list<Fractal::point>* initiator = &(Fractals::getInstance() -> initiatorView -> initiator);
	list<Fractal::point>* generator = &(Fractals::getInstance() -> generatorView -> generator);

	if( initiator->size() == 0 || generator->size() == 0 )
	{
		notGenerated = true;
		return;
	}
}

void FractalView::mouseclick(int button, int state, double x, double y)
{}

void FractalView::mousemove(double x, double y)
{}

void FractalView::mousedrag(double x, double y) {}

void FractalView::draw()
{
	if( notGenerated )
	{
		return;
	}
	

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (auto it = fractal.begin(); it != fractal.end(); it++)
	{
		glVertex2d(it->x, it->y);
	}
	glEnd();
	glFlush();

	View::draw();
}
