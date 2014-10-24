#include "FractalView.h"

FractalView::FractalView(double x, double y, double w, double h)
: View(x, y, w, h), build_button("Build Fractal", Fractals::button_x,
Fractals::button_y, Fractals::button_w * 2, Fractals::button_h)
{
	build_button.setAction([](){
		Fractals::getInstance()->fractalView->calculate();
		Fractals::getInstance()->fractalView->draw();
		glFlush();
	});
	drawObject(&build_button);
	
	generated = false;
	generating = false;
	generror = 0;
}

void FractalView::calculate()
{
	// Reset variables
	generated = false;
	generating = true;
	generror = 0;

	// Get shortcut pointers to initiator and generator
	list<Fractal::point>* initiator = &(Fractals::getInstance() -> initiatorView -> initiator);
	list<Fractal::point>* generator = &(Fractals::getInstance() -> generatorView -> generator);

	// Make sure both have minimum number of points
	if( initiator->size() < 3 || generator->size() < 2 )
	{
		generror = 1;
		generating = false;
		return;
	}
}

void FractalView::mouseclick(int button, int state, double x, double y)
{
	build_button.mouseclick(button, state, x, y);
}

void FractalView::mousemove(double x, double y)
{
	build_button.mousemove(x, y);
}

void FractalView::mousedrag(double x, double y)
{
	build_button.mousedrag(x, y);
}

void FractalView::draw()
{
	const static double grid_spacing = 32.0;

	// Draw background
	glColor3ub(255, 255, 255);
	glRectd(x, y, x+width, y+height);

	// Draw grid
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_LINES);
	for (double i = grid_spacing; i < width; i += grid_spacing)
	{
		glVertex2d(x + i - 0.5, y);
		glVertex2d(x + i - 0.5, y + height);
	}
	for (double i = grid_spacing; i < height; i += grid_spacing)
	{
		glVertex2d(x, y + i - 0.5);
		glVertex2d(x + width, y + i - 0.5);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2d(x + 0.5, y + 0.5);
		glVertex2d(x + 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + 0.5);
	}
	glEnd();

	// Draw the fractal
	if (generated && !generating)
	{
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		for (auto p : fractal)
		{
			glVertex2d(p.x, p.y);
		}
		glEnd();
	}

	View::draw();
}
