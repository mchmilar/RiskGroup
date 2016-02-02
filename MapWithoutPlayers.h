#ifndef MAPWITHOUTPLAYERS_H
#define MAPWITHOUTPLAYERS_H

#include <string>
#include <iostream>
#include "Map.h"
#include "MapBuilder.h"
#include <fstream>
#include <vector>
#include "Continent.h"
#include "Territory.h"
#include <sstream>

using std::string; 
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::istringstream;

class MapWithoutPlayers : public MapBuilder
{
public:
	string getAfterEqualSpacer(string line){//function to get text after the "=" in the text file
		bool notFinished = true;
		while (line != "" && notFinished){
			if (line[0] == '='){//found the equal spacer
				line = line.erase(0, 1);//delete the equal spacer
				notFinished = false;
			}
			else{
				line = line.erase(0, 1);//delete that first character of the text
			}
		}
		return line;
	}
	string getBeforeEqualSpacer(string line){//function to get text before the "=" in the text file
		bool notFinished = true;
		string buffer = "";
		while (line != "" && notFinished){
			if (line[0] == '='){//found the equal spacer
				notFinished = false;
			}
			else{
				buffer += line[0];
				line = line.erase(0, 1);//delete that first character of the text
			}
		}
		return buffer;
	}
	virtual bool setMapModel(string location)
	{


		string line;
		//Map map;
		string fileLocation = location;
		ifstream file(fileLocation);
		if (file.is_open())
		{
			int counter = 0;//line counter
			int phase = 1;//2 is for continents, 3 is for territories
			string author;
			string image;
			bool wrap;
			bool scroll;
			bool warn;
			int continentCounter = 0;
			while (getline(file, line))//first phase when creating map with info and populating continents and territories
			{
				counter += 1;
				if (phase == 1){//map settings
					switch (counter){
					case 1:{//[Map]
						if (line.compare("[Map]") != 0){
							return false;
						}
						break;
					}
					case 2:{//author
						author = getAfterEqualSpacer(line);
						break;
					}
					case 3:{//image
						image = getAfterEqualSpacer(line);
						break;
					}
					case 4:{//wrap
						string wrapString = getAfterEqualSpacer(line);
						if (wrapString.compare("yes") == 0){
							wrap = true;
						}
						else{
							wrap = false;
						}
						break;
					}
					case 5:{//scroll
						string scrollString = getAfterEqualSpacer(line);
						if (scrollString.compare("horizontal") == 0){
							scroll = true;
						}
						else{
							scroll = false;
						}
						break;
					}
					case 6:{//warn
						string warnString = getAfterEqualSpacer(line);
						if (warnString.compare("yes") == 0){
							warn = true;
						}
						else{
							warn = false;
						}
						if (fileLocation.compare("") == 0 || author.compare("") == 0 || image.compare("") == 0){
							return false;
						}
						mapModel->setMap(fileLocation, author, image, wrap, scroll, warn);//creates map
						break;
					}
					case 7:{//blank spacer
						break;
					}
					case 8:{//[continents] first line
						phase = 2;
						break;
					}
					}
				}
				else if (phase == 2){//continents
					if (line.compare("[Territories]") == 0){//begining of territories
						phase = 3;
					}
					else if (line.compare("") != 0){//if line not empty
						int intergerValue;
						string intValue = getAfterEqualSpacer(line);
						istringstream(intValue) >> intergerValue;
						mapModel->addContinent(getBeforeEqualSpacer(line), intergerValue);
					}
				}
				else{//teritories
					if (line.compare("") != 0){
						string teritoryname;
						int xLoc;
						int yLoc;
						string buffer = "";
						int counter = 0;
						while (line != ""){
							buffer += line[0];
							line = line.erase(0, 1);//delete that first character of the text
							if (line[0] == ',' || line == ""){//found the equal spacer
								counter += 1;
								line = line.erase(0, 1);
								if (counter == 1){//teritory name
									teritoryname = buffer;
								}
								else if (counter == 2){//x loc
									istringstream(buffer) >> xLoc;
								}
								else if (counter == 3){//y loc
									istringstream(buffer) >> yLoc;
								}
								else if (counter == 4){//continent
									mapModel->addTeritory(teritoryname, xLoc, yLoc, mapModel->getContinent(continentCounter)->getName());
								}
								buffer = "";
							}
						}
					}
					else{
						continentCounter += 1;
					}
				}
			}
			file.close();
			ifstream file2(fileLocation);
			bool territoryPhase = false;
			int territoryCounter = 0;
			while (getline(file2, line)){//Second phase, after map was created and territories/continents added, this re-reads the file to add the territory links
				if (territoryPhase){
					if (line.compare("") != 0){//if not a spacer between contients

						string teritorybuffer = "";

						int wordCounter = 0;//line counter
						while (line != ""){
							teritorybuffer += line[0];
							line = line.erase(0, 1);//delete that first character of the text
							if (line[0] == ',' || line == ""){//found the equal spacer
								wordCounter += 1;
								line = line.erase(0, 1);
								if (wordCounter >= 5){//territory links
									int correctIndex = 0;
									for (int i = 0; i < mapModel->getNumberOfTerritories(); i++){
										if (mapModel->getTerritoriesNames(i).compare(teritorybuffer) == 0){//finds the index of the correct territory link
											correctIndex = i;
										}
									}
									mapModel->putTerritoryLink(territoryCounter, mapModel->getTerritory(correctIndex)->getName());//adds the territory link to the territory
								}
								teritorybuffer = "";
							}
						}
						territoryCounter += 1;
					}
					else{
						//next continent
					}
				}
				else if (line.compare("[Territories]") == 0){
					territoryPhase = true;
				}
			}
		}
		else{
			return false;
		}

		return true;
	}

};

#endif