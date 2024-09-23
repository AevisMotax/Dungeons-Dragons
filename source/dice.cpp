/**
 * @briefImplement a C++ class that provides support for rolling dice in the game. The dice are
 *of the following kinds (d4, d6, d8, d10, d12, d20, d100). The Dice class must allow to roll
 *any number of dice of one kind at once using the following regular expression: xdy[+z].
 *Where x is the number of dice of the dy kind, optionally added with z after all the dice
 *results have been added. The Dice class must parse a string of this form, roll the
 *individual dice, make the addition and return an integer value.
*/
#include "source/logger/logger.h"
#include "dice.h"
#include <iostream>
#include<string>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <random>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

//Constructor
dice::dice() {
	/* Nothing */
	srand(static_cast<unsigned>(time(nullptr)));
};

//roll a single dy kind
int dice::diceRandomizer(int type) {
	static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<> dist(1, type);
	return dist(rng);
};

bool dice::validateDyKind(const std::string& dy) 
{
	//get values and separate them into respective values
	if (regex_match(dy, match, regexDice)) {

		numberOfRolls = stoi(match[1]);
		dy_Kind = stoi(match[2]);
		z_Modifier = match[4].matched ? stoi(match[4]) : 0; //WIthin the regex expression, match[4] is the integer modifer within match[3]
	
		//Validate if dy kind is part of the available dices (d4, d6, d8, d10, d12, d20, d100)
		if ((dy_Kind != 4 && dy_Kind != 6 && dy_Kind != 8 && dy_Kind != 10 && dy_Kind != 12 && dy_Kind != 20 && dy_Kind != 100)) {
			cerr << "Invalid expression. Please retry again." << endl;
			_getch(); //Pause
			return false;
		}

		return true;
	}
	else {
		/* Error */
		cerr << "Invalid expression. Please retry again." << endl;
		_getch(); //Pause
		return false;
	}
}

std::vector<int> dice::obtainSingleDieValue() 
{
	std::vector<int> temp{};
	for (int i = 0; i < numberOfRolls; i++) {
		temp.push_back(diceRandomizer(dy_Kind));
	}
	return temp;
}

//Getting the Representation of die type and the number of times we wish to roll. 
void dice::rollDie(const std::string& dy) {

	bool isValid = validateDyKind(dy);

	if (isValid) {
		//roll the specified number of dice and return result
		total += z_Modifier;
		for (int i = 0; i < numberOfRolls; i++) {
			int result = diceRandomizer(dy_Kind);
			total += result;
		}

		//Jut put 1 if the total is in the negatives.
		if (total <= 0) {
			total = 1;
		}
	}
	else 
	{
		return;
	}
};


/* Getters and Setters*/
int dice::getTotal() {
	return total;
};

int* dice::getSingleRolls() 
{
	return rolls;
}


//User selects a dice kind.
void dice::selectDiceToUse() {
	while (true) {
		//Random string
		string expression;
		//User input
		expression = diceExpression();

		//Validate the expression
		rollDie(expression);

		if (total != 0) {
			break;
		}
	}

	//Final
	cout << "You rolled " << this->total << endl;
	Logger::getSingleton()->log("dice", "Rolled an " + std::to_string(this->total));

	//Pause to see
	std::cin.get();
};


//User selects a nonsense
string dice::diceExpression() 
{
	system("cls");
	cout << "\n\nPlease select a dy kind and the number of time you wish to roll it, along with a modifier if you want.\n"
		" The options are : (d4, d6, d8, d10, d12, d20, d100). \n"
		" Example: 3d6[+1]--> you would roll a d6 dice 3 times and add a +1 modifier" << endl;

	//Random string
	string expression;
	//User input
	cin >> expression;

	return expression;
}