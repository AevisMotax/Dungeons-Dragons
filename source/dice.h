#ifndef DICE_H
#define DICE_H

#include <stdio.h>
#include <iostream>
#include<string>
#include <regex>
#include <cstdlib>
#include <ctime>


/**
 * @brief Dice class for simulating dice rolls in d20 like games.
 *
 * This class supports rolling various types of dice (d4, d6, d8, d10, d12, d20, d100)
 * using a notation in the form of xdy[+z],
 * where:
 *  	x is the number of dice to roll,
 * 		y is the type of dice, and
 * 		z is an optional modifier.
 */
class dice
{

public:


	/**
	 * @brief Constructs a new dice object.
	 *
	 * Initializes the random number generator with the current time as the seed.
	 */
	dice();


	/**
	 * @brief Generates a random number representing a dice roll of a specific type.
	 *
	 * @param type The type of dice to roll (e.g., 6 for d6).
	 * @return int The result of the dice roll.
	 */
	int diceRandomizer(int type);

	/**
	* @brief validating if the dyKind is really good or not
	 * @param dy A string representing the dice roll notation (e.g., 2d6[+3]).
	*/
	bool validateDyKind(const std::string& dy);

	/**
	 * @brief Rolls dice and obtain each specific roll. Example: Roll 1 was 6, then ROll 2 was 2....
	 */
	std::vector<int> obtainSingleDieValue();

	/**
	 * @brief Rolls dice based on the specified notation. 
	 *
	 * @param dy A string representing the dice roll notation (e.g., 2d6[+3]).
	 */
	void rollDie(const std::string& dy);
	

	/**
	 * @brief Interacts with the user to select the type and number of dice to roll.
	 *
	 * Reads input from the user and performs the dice roll based on the input.
	 */
	void selectDiceToUse();

	
	/**
	 * @brief Getters to get the total value of the last dice roll.
	 *
	 * @return int The total value of the dice roll.
	 */
	int getTotal();

	/**
	 * @brief Getters to get the value of each roll dice.
	 *
	 * @return int* an array.
	 */
	int* getSingleRolls();

	/**
	* @brief return an expression that user wish to test out
	*
	* @return a dice expression
	*/
	string diceExpression();


private:
	int z_Modifier;
	int numberOfRolls;
	int dy_Kind;
	int total;
	int* rolls; ///< each specific value of dice we obtain

	/**
	 * @brief Regular expression for parsing dice roll notations.
	 *
	 * This regular expression is used to validate and parse strings representing dice rolls.
	 * It supports the format xdy[+z] or xdy[-z], 
	 * where:
	 *		- x is the number of dice to roll,
	 *		- y is the type of dice (e.g., 4, 6, 8, 10, 12, 20, 100),
	 *		- z is an optional modifier to add or subtract from the total roll.
	 */
	const std::regex regexDice = std::regex("^([0-9]+)d(\\d+)(\\[([+\\-][0-9]+)\\])?");


	/**
	* @brief Match results for the regular expression parsing.
	*
	* Used to store the results of applying the regexDice pattern to a dice roll notation string.
	*/
	std::smatch match;

};
	

#endif DICE_H

