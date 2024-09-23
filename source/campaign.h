#pragma once
#ifndef CAMPAIGN_H
#define CAMPAIGN
#include "map/grid.h"

/**
* 
* @brief A sequence of grids for the game to load
*/
class Campaign
{
public:
	/**
	* \brief Initiate the campaign to a random map
	*/
	Campaign();

	/**
	* \brief Initiate the campaign to a specific map or no map with "notSet".
	* @param The grid to be loaded, or 'notSet' for no map
	*/
	Campaign(string fileName);

	/**
	* brief Initiate and create a campaign
	*/
	void static create();

	/**
	* \brief Load a previously made campaign
	* @param The file name of the map to be loaded
	*/
	static Campaign load(string name);

	/**
	* \brief Set an active map out of the map in the campaign
	*/
	void setActiveMap(int ind);

	/**
	* \brief Add a map to the sequence of grids
	* */
	void addMap(string mapFile);

	/**
	* \brief Remove the last map
	* */
	void removeMap();

	/**
	* \brief Get the currently loaded map
	* */
	Grid getActiveMap();

	/**
	* \brief Get the name of the file associated with a map
	* */
	string getMapFile(int ind);

	/**
	* \brief Get the number of maps in the campaign
	* */
	int getLength();

	/**
	* \brief Save the current campaign
	* @param the name of the campaign file
	* */
	void save(string name);



	/** 
	* \brief edit campaign if possible:
	*/
	static void editCampaign();

	 /** 
	 * \brief showcase all map files within the system
	 */
	void showAllFiles();

private:
	string mapSaves[100];	////< The maps in the campaign
	Grid activeMap;			////< The currently loaded map
	int campaignLength;		////< The total number of maps
};	
#endif //CAMPAIGN_H

