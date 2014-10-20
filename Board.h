/***************************************************************************//**
 * @file File containing the declaration for the Board class.
 *
 * @brief Contains the declaration for the Board class.
*******************************************************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Board;

#include <string>
#include "Drawable.h"

using namespace std;

/***************************************************************************//**
 * @brief The Board class takes care of all the parts of the board. It
 *		provides the backround for the pong game as well as the score.
 *		It also states the end text when a side has reached 10 points
*******************************************************************************/
class Board : public Drawable
{
private:
	int x;	/*!< Location of the center of the board on the x plane */
	int y;	/*!< Location of the center of the board on the y plane */
	int width;	/*!< Total width of the board */
	int height;	/*!< Total height of the board */
	int border;	/*!< The Thickness of the boarder */
	unsigned char* left_text;	/*!< The left score */
	unsigned char* right_text;	/*!< The right score */
	unsigned char* center_text;	/*!< The end game text after a game */

public:

	/*! 
	*  @brief Creates an instance of the board
	*/
	Board(int x, int y, int width, int height, int border);

	/*! 
	*  @brief deletes the allocated memory for the scores and end game
	*		text
	*/
	~Board();

	/*! 
	*  @brief Creates and sets an unsighned charactor array for the left
		score
	*/
	void setLeftText(string text);

	/*! 
	*  @brief Creates and sets an unsighned charactor array for the right
		score
	*/
	void setRightText(string text);

	/*! 
	*  @brief Creates and sets an unsighned charactor array for the end
		game winner's text
	*/
	void setCenterText( string text );



	/*! 
	*  @brief returns x demention of the center of the board
	*/
	int getX();

	/*! 
	*  @brief returns y demention of the center of the board
	*/
	int getY();

	/*! 
	*  @brief returns width of board
	*/
	int getWidth();

	/*! 
	*  @brief returns height of board
	*/
	int getHeight();



	/*! 
	*  @brief draws the board in conjunction with the drawable class
	*/
	void draw();


};

#endif