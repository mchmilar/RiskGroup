#include "Continent.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//Default constructor
Continent::Continent(){

}
//Constructor taking the continent's name as a string and an integer value to be associated with that continent
Continent::Continent(std::string name2, int intValue){
	name = name2;
	integerValue = intValue;
}
/*Continent::Continent(const Continent &p){
	name = p.name;
	integerValue = p.integerValue;
}*/
//Accesor function for the Continent name
std::string Continent::getName(){
	return name;
}
int Continent::getIntegerValue(){
	return integerValue;
}
//Mutator function to set the continent's name and associated integer value
void Continent::setContinent(std::string newName, int val){
	name = newName;
	integerValue = val;
}
//Mutator function to set the number of territories within the continent
void Continent::setNumberOfTerritories(int n){
	numberOfTerritories = n;
}
//Accessor function to return the total territories found inside the continent
int Continent::getNumberOfTerritories(){
	return numberOfTerritories;
}
int Continent::getContinentIntId(){
	return continentIntId;
}
void Continent::setContinentIntId(int i){
	continentIntId = i;
}
//Destructor
Continent::~Continent()
{
}

