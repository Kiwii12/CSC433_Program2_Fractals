/***************************************************************************//**
 * @file File containing the implementation for the Board class.
 *
 * @brief Contains the implementation for the Boad class.
*******************************************************************************/
#include "Board.h"

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Constuctor, creates the board parts and makes the scoring
 *			strings
 *
 * @param[in]	int x - the center width of the board
 * @param[in]	int y - the height of the center of the board
 * @param[in]	int width - the total width of the board
 * @param[in]	int height - the total height of the board
 * @param[in]	int border - the thickness of the border

*******************************************************************************/
Board::Board(int x, int y, int width, int height, int border) :
		x(x), y(y), width(width), height(height), border(border),
		left_text(NULL), right_text(NULL)
{
	//creates unsigned charactor arraws for scoring later
	left_text = new (nothrow) unsigned char[1];
	right_text = new (nothrow) unsigned char[1];
	center_text = new (nothrow) unsigned char[1];
	left_text[0] = '\0';
	right_text[0] = '\0';
	center_text[0] = '\0';
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Destructor, deletes allocated arrays
*******************************************************************************/
Board::~Board()
{
	delete[] left_text;
	delete[] right_text;
	delete[] center_text;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Fills the left text array with a string
 *
 * @param[in]	string text - the left score
*******************************************************************************/
void Board::setLeftText(string text)
{
	delete[] left_text;//clears current score
	left_text = new (nothrow) unsigned char[text.size() + 1]; //creates 
											//unsigned array
	for (unsigned int i = 0; i < text.size(); i++)
	{
		left_text[i] = (unsigned char) text[i]; //fills array from string
	};
	left_text[text.size()] = '\0';
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Fills the right text array with a string
 *
 * @param[in]	string text - the right score
*******************************************************************************/
void Board::setRightText(string text)
{
	delete[] right_text; //clears current score
	right_text = new (nothrow) unsigned char[text.size() + 1];
	for (unsigned int i = 0; i < text.size(); i++)
	{     //converts string to unsigned char
		right_text[i] = (unsigned char) text[i]; 
	};
	right_text[text.size()] = '\0';
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Fills the end game text with the wining side
 *
 * @param[in]	string text - text to be converted to unsigned char
*******************************************************************************/
void Board::setCenterText(string text)
{
	delete[] center_text; //deletes current string
	center_text = new (nothrow) unsigned char[text.size() + 1];
	for (unsigned int i = 0; i < text.size(); i++)
	{  //converts string to unsigned char array
		center_text[i] = (unsigned char) text[i];
	};
	center_text[text.size()] = '\0';
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns the x coordinate for other functions
 *
 * @returns x - x coordinant for the center of the board
*******************************************************************************/
int Board::getX()
{
	return x;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns the y coordinate of the board for other functions
 *
 * @returns y - y coordinant for the center of the board
*******************************************************************************/
int Board::getY()
{
	return y;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns the width of the board for other functions
 *
 * @returns width - the width of the board
*******************************************************************************/
int Board::getWidth()
{
	return width;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns the height of the board for other functions
 *
 * @returns height - the height of the board
*******************************************************************************/
int Board::getHeight()
{
	return height;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Draws the net, the border, and the scores for the bored
 *		as well as the end game text for the winner
*******************************************************************************/
void Board::draw()
{
	glColor3d( 1.0, 0.8, 0.8 );
	//creates a border that is visable if any part of it is on screen
    glRecti( x - border, y - border, x + border + width, y );
    glRecti( x - border, y - border, x, y + height + border );
	glRecti( x + width + border, y + height + border, x + width, y-border);
	glRecti( x + width + border, y + height + border, x -border, y+height);

	//creates the net
	glLineStipple(3, 0xAAAA );
	glEnable( GL_LINE_STIPPLE );
	glColor3d( 0.8, 1.0, 0.8 );
	glBegin( GL_LINES );
		glVertex2i( width/2, 0 );
		glVertex2i( width/2, height );
	glEnd();
	glDisable( GL_LINE_STIPPLE );

	glColor3d( 0.8, 0.8, 1.0 );
	glLineWidth( 2.5 );

	//creates left score
	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 - 64) * 4.0, (height - 32) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, left_text);
    glPopMatrix();

	//creates right score
	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 + 64) * 4.0, (height - 32) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, right_text);
    glPopMatrix();

	//creates end game text
	glColor3d( 1.0, 5.0, 0.0 );
	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated( (width / 2 - 120) * 4.0, (height / 2 - 16) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, center_text);
    glPopMatrix();

}
