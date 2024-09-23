#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


/** 
* @file
* @brief 
*/
class Attribute 
{
public:
	/** 
	* @brief default constructor
	*/
	Attribute();
	/**
	* @brief constructor with parameters
	*/
	Attribute(int intelligence, int wisdom, int strength, int dexterity, int constitution, int charisma);
	/**
	* @brief default destructor
	*/
	~Attribute();


	bool validate();

	/** @brief setter and getter */
	int getIntelligence() const;
	void setIntelligence(int intelligence);
	int getWisdom() const;
	void setWisdom(int wisdom);
	int getStrength() const;
	void setStrength(int strength);
	int getDexterity() const;
	void setDexterity(int dexterity);
	int getConstitution() const;
	void setConstitution(int constitution);
	int getCharisma() const;
	void setCharisma(int charisma);

private:

};


#endif
