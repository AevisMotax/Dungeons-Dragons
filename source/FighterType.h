#ifndef FIGHTERTYPE_H
#define FIGHTERTYPE_H
#include "player/CharacterBuilder.h"
#include "player/characterStat.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>

/** 
* @brief
*/
class Bully : public CharacterBuilder {
	
public:
	/**
	* @brief constructors and destructors
	*/
	Bully();
	~Bully();

	Character* getCharacter() override;

	void createCharacter();
	/** @brief Inherited from Builder*/
	void assignAbilityOrder();

};


/**
* @brief
*/
class Nimble : public CharacterBuilder {

public:
	/**
	* @brief constructors and destructors
	*/
	Nimble();
	~Nimble();

	Character* getCharacter() override;


	void createCharacter();
	/** @brief  Inherited from Builder*/
	void assignAbilityOrder();

};


/**
* @brief
*/
class Tank : public CharacterBuilder {

public:
	/**
	* @brief constructors and destructors
	*/
	Tank();
	~Tank();

	Character* getCharacter() override;

	void createCharacter();

	/** @brief  Inherited from Builder*/
	void assignAbilityOrder();
		
};


//class FighterType
//{
//
//
//
//};

#endif