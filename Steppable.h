/***************************************************************************//**
 * @file File containing the declaration for the Steppable class.
 *
 * @brief Contains the declaration for the Steppable class.
*******************************************************************************/
#ifndef _STEPPABLE_H_
#define _STEPPABLE_H_

/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for the Steppable class. Declares single virtual function
 *		step().
 *
 * @details Declares a single virtual function step() that will execute every
 *		game step. (Typically between 30 and 60 times per second.)
 */
class Steppable
{
	public:
		/*!
		 * @brief Function to take action per game step.
		 */
		virtual void step() = 0;
};

#endif