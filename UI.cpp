#include "UI.h"
#include "Driver.h"
#include "Continent.h"
#include <msclr\marshal_cppstd.h>
#include <string>
#include <sstream>
#include <time.h>
using namespace Risk;
using namespace System;
using std::ostringstream;
bool loadTrigger = false;
int phase = 0;//different phases for map creation input

string filename;
string author;
string image;
bool wrap;
bool scroll;//true = horizontal, false = vertical
bool warn;
bool inGame = false;//if currently playing game


string newContinentName;
int newContinentValue;

string newTerritoryName;
int xLoc;
int yLoc;

bool continentAddEdit;//True = add phase; False = edit phase
bool territoryAddEdit;//True = add phase; False = edit phase
Driver *driver = new Driver();

bool alreadyWonOneBattleThisTurn = false;//tracks multiple ilegal attributions of cards per turn
vector<Territory*> temporalPlayerTerritory;//used to not allow played to attack with a territory he just won

UI::UI(void){
	InitializeComponent();
	this->ClientSize = System::Drawing::Size(345, 140);
	this->loadButton->Visible = true;
	this->createButton->Visible = true;
	this->enterMapNameLabel->Visible = true;
	this->numberOfPlayerComboBox->SelectedIndex = 0;
	this->numberOfAIComboBox->SelectedIndex = 0;
}
//converts strings between namespace System and namespace std
string convertSystemStringToString(String^ a){
	msclr::interop::marshal_context context;
	return context.marshal_as<string>(a);
}
//converts strings between namespace System and namespace std
String ^ convertStringToSystemString(string a){
	String^ str2 = gcnew String(a.c_str());
	return str2;
}
//converts int to system string
String^ convertIntToSystemString(int num){
	ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convertStringToSystemString(convert.str());
}
//event when OK button is clicked, used for both creating and loading map. If map is loading it checks map for issues like duplicate names and one way borders
System::Void UI::okButton_Click(System::Object^  sender, System::EventArgs^  e) {

	mapNameTextBox->Focus();
	if (loadTrigger){//if loading
		if (driver->loadMap(convertSystemStringToString(mapNameTextBox->Text))){//if map loaded
			string errors = driver->loadMapCheck();
			if (errors.compare("")!=0){
				this->enterMapNameLabel->Text = L"Map errors: " + convertStringToSystemString(errors);
				errors = "";
			}
			else{
				this->ClientSize = System::Drawing::Size(1350, 796);
				this->mapPictureBox->Visible = true;
				this->mapPictureBox->Refresh();
				this->loadButton->Visible = false;
				this->createButton->Visible = false;
				this->okButton->Visible = false;
				this->cancelButton->Visible = false;
				this->enterMapNameLabel->Visible = false;
				this->mapNameTextBox->Visible = false;
				this->yesButton->Visible = false;
				this->saveMapAndPlayButton->Visible = true;
				this->continentsLabel->Visible = true;
				this->continentsComboBox->Visible = true;
				this->addContinentButton->Visible = true;
				this->numberOfPlayersLabel->Visible = true;
				this->numberOfAIPlayersLabel->Visible = true;
				this->numberOfPlayerComboBox->Visible = true;
				this->numberOfAIComboBox->Visible = true;
				vector<Continent> continents = driver->getAllContinents();
				this->continentsComboBox->Items->Add("None");
				for (int i = 0; i < continents.size(); i++){//Populate continents comboBox
					this->continentsComboBox->Items->Add(convertStringToSystemString(continents[i].getName()));
				}
				this->continentsComboBox->SelectedIndex = 0;//Sets "None" as selected
				this->saveMapAndPlayButton->Focus();
				if (driver->getPlayerSet()){
					this->continentsLabel->Visible = false;//set previous map editing buttons to invisible
					this->territoriesLabel->Visible = false;
					this->bordersLabel->Visible = false;
					this->continentsComboBox->Visible = false;
					this->addContinentButton->Visible = false;
					this->deleteContinentButton->Visible = false;
					this->continentEditButton->Visible = false;
					this->continentNameLabel->Visible = false;
					this->continentEditTextBox->Visible = false;
					this->territoriesComboBox->Visible = false;
					this->territoryAddButton->Visible = false;
					this->territoryDeleteButton->Visible = false;
					this->territoryEditButton->Visible = false;
					this->territoryEditNameLabel->Visible = false;
					this->territoryEditTextBox->Visible = false;
					this->continentOkEditButton->Visible = false;
					this->territoryOkEditButton->Visible = false;
					this->bordersCheckList->Visible = false;
					this->borderApplyChangesButton->Visible = false;
					this->numberOfPlayerComboBox->Visible = false;
					this->numberOfAIComboBox->Visible = false;
					this->numberOfPlayersLabel->Visible = false;
					this->numberOfAIPlayersLabel->Visible = false;
					this->saveMapAndPlayButton->Visible = false;
					this->saveErrorMessage->Visible = false;
					this->saveErrorMessage->Text = L"";
					this->logTextBox->Visible = true;
					inGame = true;
					this->gamePanel->Visible = true;
					this->continentValuesListBox->Visible = true;

					this->showStatsButton->Visible = true;
					this->saveExitButton->Visible = true;


					this->continentValuesListBox->Items->Add("Continent Control Extra Armies:");
					vector < Continent> continents = driver->getAllContinents();
					for (int i = 0; i < continents.size(); i++){
						this->continentValuesListBox->Items->Add(convertStringToSystemString(continents[i].getName()) + ": " + convertIntToSystemString(continents[i].getIntegerValue()));
					}

					this->infantryCardLabel->Visible = true;
					this->cavalryCardLabel->Visible = true;
					this->artilleryCardLabel->Visible = true;
					this->artilleryCardTextBox->Visible = true;
					this->cavalryCardTextBox->Visible = true;
					this->infantryCardTextBox->Visible = true;
					this->useCardsButton->Visible = true;
					this->cardsValueTextBox->Visible = true;
					this->cardsValueLabel->Visible = true;

					driver->mapStartGameSetup(this->numberOfPlayerComboBox->SelectedIndex + 2);
					driver->setTurn(driver->getLoadingTurn());
					driver->nextTurn();

					newTurn(driver->getTurn());



				}


			}
		}
		else{//error loading map
			this->enterMapNameLabel->Text = L"Error loading map. Enter map name:";
		}
		
	}
	else{//if creating
		switch (phase)
		{
		case 0://When entering map name
			if (!convertSystemStringToString(mapNameTextBox->Text).compare("") == 0){
				filename = convertSystemStringToString(mapNameTextBox->Text);
				this->enterMapNameLabel->Text = L"Enter map author name:";
				this->mapNameTextBox->Text = L"";
				phase += 1;
			}
			break;
		case 1://Author name
			if (!convertSystemStringToString(mapNameTextBox->Text).compare("") == 0){
				author = convertSystemStringToString(mapNameTextBox->Text);
				this->enterMapNameLabel->Text = L"Enter map image name with the extension:";
				this->mapNameTextBox->Text = L"";
				phase += 1;
			}
			break;
		case 2://Image name
			if (!convertSystemStringToString(mapNameTextBox->Text).compare("") == 0){
				image = convertSystemStringToString(mapNameTextBox->Text);
				this->enterMapNameLabel->Text = L"Do you want map warp?";
				this->yesButton->Visible = true;
				this->okButton->Text = L"No";
				this->mapNameTextBox->Visible = false;
				this->mapNameTextBox->Text = L"";
				enterMapNameLabel->Focus();
				phase += 1;
			}
			break;
		case 3://Wrap
			wrap = false;
			this->yesButton->Text = L"Horizontal";
			this->okButton->Text = L"Vertical";
			this->enterMapNameLabel->Text = L"What kind of scroll do you want?";
			enterMapNameLabel->Focus();
			phase += 1;
			break;
		case 4://Scroll
			scroll = false;
			this->yesButton->Text = L"Yes";
			this->okButton->Text = L"No";
			this->enterMapNameLabel->Text = L"Do you want warnings?";
			enterMapNameLabel->Focus();
			phase += 1;
			break;
		case 5://Warn
			warn = false;
			driver->createMap(filename, author, image, wrap, scroll, warn);
			this->ClientSize = System::Drawing::Size(1350, 796);
			this->mapPictureBox->Visible = true;
			this->mapPictureBox->Refresh();
			enterMapNameLabel->Focus();
			this->loadButton->Visible = false;
			this->createButton->Visible = false;
			this->okButton->Visible = false;
			this->cancelButton->Visible = false;
			this->enterMapNameLabel->Visible = false;
			this->mapNameTextBox->Visible = false;
			this->yesButton->Visible = false;
			this->saveMapAndPlayButton->Visible = true;
			this->continentsLabel->Visible = true;
			this->continentsComboBox->Visible = true;
			this->addContinentButton->Visible = true;
			this->numberOfPlayersLabel->Visible = true;
			this->numberOfAIPlayersLabel->Visible = true;
			this->numberOfPlayerComboBox->Visible = true;
			this->numberOfAIComboBox->Visible = true;
			this->continentsComboBox->Items->Add("None");
			vector<Continent> continents = driver->getAllContinents();
			for (int i = 0; i < continents.size(); i++){//Populate continents comboBox
				this->continentsComboBox->Items->Add(convertStringToSystemString(continents[i].getName()));
			}
			this->continentsComboBox->SelectedIndex = 0;//Sets "None" as selected
			phase = 0;//resets phase
			break;
		}
	}
}
//event for cancel button during map loading/creating phase
System::Void UI::cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->mapNameTextBox->Visible = false;
	this->okButton->Visible = false;
	this->cancelButton->Visible = false;
	this->loadButton->Visible = true;
	this->createButton->Visible = true;
	this->mapNameTextBox->Text = L"";
	this->yesButton->Visible = false;
	this->enterMapNameLabel->Location = System::Drawing::Point(112, 19);
	this->enterMapNameLabel->Text = L"Welcome to Risk";
	this->okButton->Text = L"Ok";
	this->yesButton->Text = L"Yes";
	mapNameTextBox->Focus();
	phase = 0;
}
//selecting loading map
System::Void UI::loadButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->enterMapNameLabel->Visible = true;
	this->mapNameTextBox->Visible = true;
	this->okButton->Visible = true;
	this->cancelButton->Visible = true;
	this->loadButton->Visible = false;
	this->createButton->Visible = false;
	loadTrigger = true;
	this->enterMapNameLabel->Location = System::Drawing::Point(12, 9);
	this->enterMapNameLabel->Text = L"Enter Map Name";
	mapNameTextBox->Focus();
}
//selecting creating map
System::Void UI::createButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->enterMapNameLabel->Visible = true;
	this->mapNameTextBox->Visible = true;
	this->okButton->Visible = true;
	this->cancelButton->Visible = true;
	this->loadButton->Visible = false;
	this->createButton->Visible = false;
	loadTrigger = false;
	this->enterMapNameLabel->Location = System::Drawing::Point(12, 9);
	this->enterMapNameLabel->Text = L"Enter Map Name";
	mapNameTextBox->Focus();
}
//yes button used for yes/no question during map creation
System::Void UI::yesButton_Click(System::Object^  sender, System::EventArgs^  e){
	switch (phase)
	{
	case 3://Wrap
		wrap = true;
		this->yesButton->Text = L"Horizontal";
		this->okButton->Text = L"Vertical";
		this->enterMapNameLabel->Text = L"What kind of scroll do you want?";
		phase += 1;
		break;
	case 4://Scroll
		scroll = true;
		this->yesButton->Text = L"Yes";
		this->okButton->Text = L"No";
		this->enterMapNameLabel->Text = L"Do you want warnings?";
		phase += 1;
		break;
	case 5://Warn
		warn = true;
		driver->createMap(filename, author, image, wrap, scroll, warn);
		this->loadButton->Visible = false;
		this->createButton->Visible = false;
		this->okButton->Visible = false;
		this->cancelButton->Visible = false;
		this->enterMapNameLabel->Visible = false;
		this->mapNameTextBox->Visible = false;
		this->yesButton->Visible = false;
		this->saveMapAndPlayButton->Visible = true;
		this->continentsLabel->Visible = true;
		this->continentsComboBox->Visible = true;
		this->addContinentButton->Visible = true;
		this->numberOfPlayersLabel->Visible = true;
		this->numberOfAIPlayersLabel->Visible = true;
		this->numberOfPlayerComboBox->Visible = true;
		this->numberOfAIComboBox->Visible = true;
		this->continentsComboBox->Items->Add("None");
		vector<Continent> continents = driver->getAllContinents();
		for (int i = 0; i < continents.size(); i++){//Populate continents comboBox
			this->continentsComboBox->Items->Add(convertStringToSystemString(continents[i].getName()));
		}
		this->continentsComboBox->SelectedIndex = 0;//Sets "None" as selected
		this->ClientSize = System::Drawing::Size(1350, 796);
		this->mapPictureBox->Visible = true;
		this->mapPictureBox->Refresh();
		phase = 0;//resets phase
		break;
	}
	mapNameTextBox->Focus();
}
//Selected continent changed
System::Void UI ::continentsComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->territoriesComboBox->Items->Clear();
	this->bordersCheckList->Items->Clear();
	this->borderApplyChangesButton->Visible = false;
	this->bordersLabel->Visible = false;
	this->bordersCheckList->Visible = false;
	this->territoryDeleteButton->Visible = false;
	this->territoryEditButton->Visible = false;
	this->continentEditButton->Visible = false;
	this->continentNameLabel->Visible = false;
	this->continentEditTextBox->Visible = false;
	this->continentOkEditButton->Visible = false;
	this->territoryEditNameLabel->Visible = false;
	this->territoryEditTextBox->Visible = false;
	this->territoryOkEditButton->Visible = false;
	this->territoriesLabel->Visible = false;
	this->territoriesComboBox->Visible = false;
	this->territoryAddButton->Visible = false;
	this->saveErrorMessage->Visible = false;
	if (this->continentsComboBox->SelectedIndex != 0){//if none is not selected
		this->continentEditButton->Visible = true;
		this->deleteContinentButton->Visible = true;
		this->territoriesLabel->Visible = true;
		this->territoriesComboBox->Visible = true;
		this->territoryAddButton->Visible = true;
		this->territoriesComboBox->Items->Add("None");
		vector<Territory> territoriesOfContinent = driver->getTerritoriesOfContinent(convertSystemStringToString((String^)this->continentsComboBox->SelectedItem));
		for (int i = 0; i < territoriesOfContinent.size(); i++){//Populate territories comboBox of specific continent
			this->territoriesComboBox->Items->Add(convertStringToSystemString(territoriesOfContinent[i].getName()));
		}
		this->territoriesComboBox->SelectedIndex = 0;//Sets "None" as selected

	}
}
//Selected territory changed
System::Void UI::territoriesComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->bordersCheckList->Items->Clear();
	this->borderApplyChangesButton->Visible = false;
	this->territoryEditNameLabel->Visible = false;
	this->territoryEditTextBox->Visible = false;
	this->territoryOkEditButton->Visible = false;
	this->bordersLabel->Visible = false;
	this->bordersCheckList->Visible = false;
	this->saveErrorMessage->Visible = false;
	if (this->territoriesComboBox->SelectedIndex != 0){//if none is not selected
		this->bordersLabel->Visible = true;
		this->bordersCheckList->Visible = true;
		this->territoryDeleteButton->Visible = true;
		this->territoryEditButton->Visible = true;
		vector<Territory> territories = driver->getAllTerritories();
		vector<std::string> borders = driver->getBordersOfTerritory(convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));
		for (int i = 0; i < territories.size(); i++){//Populate territories in CheckList
			this->bordersCheckList->Items->Add(convertStringToSystemString(territories[i].getName()));
			for (int j = 0; j < borders.size(); j++){//sets the checkbox of correct borders
				if (borders[j].compare(territories[i].getName()) == 0){
					this->bordersCheckList->SetItemChecked(i, true);
				}
			}
		}
	}
}

//Changes in the borders CheckListBox
System::Void UI::bordersCheckList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->borderApplyChangesButton->Visible = true;
}
//adding a continent button event
System::Void UI::addContinentButton_Click(System::Object^  sender, System::EventArgs^  e){
	newContinentName = "";
	newContinentValue = NULL;
	continentAddEdit = true;
	this->continentNameLabel->Text = L"Name:";
	this->continentNameLabel->Visible = true;
	this->continentEditTextBox->Visible = true;
	this->continentOkEditButton->Visible = true;
}
//adding a territory button event
System::Void UI::territoryAddButton_Click(System::Object^  sender, System::EventArgs^  e){
	newTerritoryName = "";
	xLoc = NULL;
	yLoc = NULL;
	territoryAddEdit = true;
	this->territoryEditNameLabel->Text = L"Name:";
	this->territoryEditNameLabel->Visible = true;
	this->territoryEditTextBox->Visible = true;
	this->territoryOkEditButton->Visible = true;
}
//editing a continent button event
System::Void UI::continentEditButton_Click(System::Object^  sender, System::EventArgs^  e){
	newContinentName = "";
	newContinentValue = NULL;
	continentAddEdit = false;
	this->continentNameLabel->Text = L"Name:";
	this->continentNameLabel->Visible = true;
	this->continentEditTextBox->Visible = true;
	this->continentOkEditButton->Visible = true;
}
//editing a territory button event
System::Void UI::territoryEditButton_Click(System::Object^  sender, System::EventArgs^  e){
	newTerritoryName = "";
	xLoc = NULL;
	yLoc = NULL;
	territoryAddEdit = false;
	this->territoryEditNameLabel->Text = L"Name:";
	this->territoryEditNameLabel->Visible = true;
	this->territoryEditTextBox->Visible = true;
	this->territoryOkEditButton->Visible = true;
}
//checks if string gives a integer and returns it, else returns negative integer
int checkPositiveStringToInt(string a){
	int value;
	try
	{
		std::stringstream ss(a);
		if ((ss >> value).fail())
		{
			throw std::bad_cast();
		}
	}
	catch (...)
	{
		value = -1;
	}

	return value;
}
//confirming to add or editing continent button
System::Void UI::continentOkEditButton_Click(System::Object^  sender, System::EventArgs^  e){
	string text = convertSystemStringToString(this->continentEditTextBox->Text);
	if (text.compare("") != 0){//If textbox not empty
		if (newContinentName.compare("") == 0){
			newContinentName = text;
			this->continentEditTextBox->Text = L"";
			this->continentNameLabel->Text = L"Value";
		}
		else if (newContinentValue == NULL){
			if (checkPositiveStringToInt(text) > -1){
				newContinentValue = checkPositiveStringToInt(text);
				this->continentNameLabel->Visible = false;
				this->continentEditTextBox->Visible = false;
				this->continentOkEditButton->Visible = false;
				vector<Continent> continents = driver->getAllContinents();
				for (int i = 0; i < continents.size(); i++){//checks if continent name exists already
					if (continents[i].getName().compare(newContinentName) == 0){
						this->continentNameLabel->Visible = true;
						this->continentNameLabel->Text = L"A continent with that name exists already";
					}
				}
				if (this->continentNameLabel->Visible == false){//if continent name doesn't exist already
					if (continentAddEdit){//adding
						driver->addContinent(newContinentName, newContinentValue);
					}
					if (!continentAddEdit){//editing
						string oldContinentName = convertSystemStringToString((String^)this->continentsComboBox->SelectedItem);
						driver->editContinent(oldContinentName, newContinentName, newContinentValue);
					}
					this->continentsComboBox->Items->Clear();
					this->continentsComboBox->Items->Add("None");
					vector<Continent> newContinents = driver->getAllContinents();
					for (int i = 0; i < newContinents.size(); i++){//Populate continents comboBox
						this->continentsComboBox->Items->Add(convertStringToSystemString(newContinents[i].getName()));
					}
					this->continentsComboBox->SelectedIndex = 0;//Sets "None" as selected
				}
				
			}
			this->continentEditTextBox->Text = L"";
		}
	}
}
//confirming to add or editing territory button
System::Void UI::territoryOkEditButton_Click(System::Object^  sender, System::EventArgs^  e){
	string text = convertSystemStringToString(this->territoryEditTextBox->Text);
	if (text.compare("") != 0){//If textbox not empty
		if (newTerritoryName.compare("") == 0){
			newTerritoryName = text;
			this->territoryEditTextBox->Text = L"";
			this->territoryEditNameLabel->Text = L"X Coordinate";
		}
		else if (xLoc == NULL){
			if (checkPositiveStringToInt(text) > -1){
				xLoc = checkPositiveStringToInt(text);
				if (xLoc > 1000){
					xLoc = NULL;
					this->territoryEditTextBox->Text = L"";
					this->territoryEditNameLabel->Text = L"X must be under 1000:";
				}
				else{
					this->territoryEditTextBox->Text = L"";
					this->territoryEditNameLabel->Text = L"Y Coordinate";
				}
				
			}
		}
		else if (yLoc == NULL){
			if (checkPositiveStringToInt(text) > -1){
				yLoc = checkPositiveStringToInt(text);
				if (yLoc > 1000){
					yLoc = NULL;
					this->territoryEditTextBox->Text = L"";
					this->territoryEditNameLabel->Text = L"Y must be under 1000:";
				}
				else{
					this->territoryEditNameLabel->Visible = false;
					this->territoryEditTextBox->Visible = false;
					this->territoryOkEditButton->Visible = false;
					vector<Territory> territory = driver->getAllTerritories();
					for (int i = 0; i < territory.size(); i++){//checks if continent name exists already
						if (territory[i].getName().compare(newTerritoryName) == 0){
							this->territoryEditNameLabel->Visible = true;
							this->territoryEditNameLabel->Text = L"A territory with that name exists already";
						}
					}
					if (this->territoryEditNameLabel->Visible == false){//if continent name doesn't exist already
						if (territoryAddEdit){//adding
							driver->addTerritory(newTerritoryName, xLoc, yLoc, convertSystemStringToString((String^)this->continentsComboBox->SelectedItem));
						}
						if (!territoryAddEdit){//editing
							string oldTerritoryName = convertSystemStringToString((String^)this->continentsComboBox->SelectedItem);
							driver->editTerritory(oldTerritoryName, newTerritoryName, xLoc, yLoc);
						}
						this->territoriesComboBox->Items->Clear();
						this->territoriesComboBox->Items->Add("None");

						vector<Territory> newTerritories = driver->getTerritoriesOfContinent(convertSystemStringToString((String^)this->continentsComboBox->SelectedItem));
						for (int i = 0; i < newTerritories.size(); i++){//Populate territories comboBox of specific continent
							this->territoriesComboBox->Items->Add(convertStringToSystemString(newTerritories[i].getName()));
						}
						this->territoriesComboBox->SelectedIndex = 0;//Sets "None" as selected
						this->mapPictureBox->Refresh();
					}
				}
			}
			this->territoryEditTextBox->Text = L"";
		}
	}
}
//delete continent button click
System::Void UI::deleteContinentButton_Click(System::Object^  sender, System::EventArgs^  e){
	newContinentName = "";
	newContinentValue = NULL;
	this->continentNameLabel->Visible = false;
	this->continentEditTextBox->Visible = false;
	this->continentOkEditButton->Visible = false;
	if (driver->getTerritoriesOfContinent(convertSystemStringToString((String^)this->continentsComboBox->SelectedItem)).size() > 0){//if continent has territories
		this->continentNameLabel->Visible = true;
		this->continentNameLabel->Text = L"Must delete all the territories of this continent first.";
	}
	else{
		driver->deleteContinent(convertSystemStringToString((String^)this->continentsComboBox->SelectedItem));
		this->continentsComboBox->Items->Clear();
		this->continentsComboBox->Items->Add("None");
		vector<Continent> newContinents = driver->getAllContinents();
		for (int i = 0; i < newContinents.size(); i++){//Populate continents comboBox
			this->continentsComboBox->Items->Add(convertStringToSystemString(newContinents[i].getName()));
		}
		this->continentsComboBox->SelectedIndex = 0;//Sets "None" as selected

	}
}
//delete territory button click
System::Void UI::territoryDeleteButton_Click(System::Object^  sender, System::EventArgs^  e){
	string newTerritoryName = "";
	int xLoc = NULL;
	int yLoc = NULL;
	this->territoryEditNameLabel->Visible = false;
	this->territoryEditTextBox->Visible = false;
	this->territoryOkEditButton->Visible = false;
	if (driver->getBordersOfTerritory(convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem)).size() > 0){//if continent has territories
		this->territoryEditNameLabel->Visible = true;
		this->territoryEditNameLabel->Text = L"Must delete all the borders of this territory first.";
	}
	else{
		driver->deleteTerritory(convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));
		this->territoriesComboBox->Items->Clear();
		this->territoriesComboBox->Items->Add("None");
		vector<Territory> newTerritories = driver->getTerritoriesOfContinent(convertSystemStringToString((String^)this->continentsComboBox->SelectedItem));
		for (int i = 0; i < newTerritories.size(); i++){//Populate territories comboBox of specific continent
			this->territoriesComboBox->Items->Add(convertStringToSystemString(newTerritories[i].getName()));
		}
		this->territoriesComboBox->SelectedIndex = 0;//Sets "None" as selected
		this->mapPictureBox->Refresh();
	}
}



//saving map and going to play phase. Also checks map for issues like unlinked territories and empty continents
System::Void UI::saveMapAndPlayButton_Click(System::Object^  sender, System::EventArgs^  e){
	if (this->numberOfAIComboBox->SelectedIndex>this->numberOfPlayerComboBox->SelectedIndex+2){
		this->saveErrorMessage->Visible = true;
		this->saveErrorMessage->Text = convertStringToSystemString("Error: Total number of player must be lower than AI");
	}
	else if (driver->getAllContinents().size() == 0){//Checks for atleast one continent
		this->saveErrorMessage->Visible = true;
		this->saveErrorMessage->Text = convertStringToSystemString("Error: There must be atleast one continent");
	}
	else if (driver->getAllTerritories().size() < this->numberOfPlayerComboBox->SelectedIndex+2){//Checks for Territories >= number of players
		this->saveErrorMessage->Visible = true;
		this->saveErrorMessage->Text = convertStringToSystemString("Error: There must be more territories than players");
	}
	else{
		this->saveErrorMessage->Visible = true;
		this->saveErrorMessage->Text = convertStringToSystemString("Checking for errors in progress...");
		string error = driver->saveMapcheck();
		if (error.compare("") == 0){
			
			driver->saveMap();

			this->continentsLabel->Visible = false;//set previous map editing buttons to invisible
			this->territoriesLabel->Visible = false;
			this->bordersLabel->Visible = false;
			this->continentsComboBox->Visible = false;
			this->addContinentButton->Visible = false;
			this->deleteContinentButton->Visible = false;
			this->continentEditButton->Visible = false;
			this->continentNameLabel->Visible = false;
			this->continentEditTextBox->Visible = false;
			this->territoriesComboBox->Visible = false;
			this->territoryAddButton->Visible = false;
			this->territoryDeleteButton->Visible = false;
			this->territoryEditButton->Visible = false;
			this->territoryEditNameLabel->Visible = false;
			this->territoryEditTextBox->Visible = false;
			this->continentOkEditButton->Visible = false;
			this->territoryOkEditButton->Visible = false;
			this->bordersCheckList->Visible = false;
			this->borderApplyChangesButton->Visible = false;
			this->numberOfPlayerComboBox->Visible = false;
			this->numberOfAIComboBox->Visible = false;
			this->numberOfPlayersLabel->Visible = false; 
			this->numberOfAIPlayersLabel->Visible = false;
			this->saveMapAndPlayButton->Visible = false;
			this->saveErrorMessage->Visible = false;
			this->saveErrorMessage->Text = L"";
			this->logTextBox->Visible = true;
			inGame = true;
			this->gamePanel->Visible = true;
			this->continentValuesListBox->Visible = true;

			this->showStatsButton->Visible = true;
			this->saveExitButton->Visible = true;


			this->continentValuesListBox->Items->Add("Continent Control Extra Armies:");
			vector < Continent> continents = driver->getAllContinents();
			for (int i = 0; i < continents.size(); i++){
				this->continentValuesListBox->Items->Add(convertStringToSystemString(continents[i].getName()) + ": " + convertIntToSystemString(continents[i].getIntegerValue()));
			}
			
			this->infantryCardLabel->Visible = true;
			this->cavalryCardLabel->Visible = true;
			this->artilleryCardLabel->Visible = true;
			this->artilleryCardTextBox->Visible = true;
			this->cavalryCardTextBox->Visible = true;
			this->infantryCardTextBox->Visible = true;
			this->useCardsButton->Visible = true;
			this->cardsValueTextBox->Visible = true;
			this->cardsValueLabel->Visible = true;

			driver->mapStartGameSetup(this->numberOfPlayerComboBox->SelectedIndex+2);
			driver->setTurn(rand() % (this->numberOfPlayerComboBox->SelectedIndex + 2));//sets turn between 0 and number of players-1
			driver->assignTerritoriesAtStart(this->numberOfPlayerComboBox->SelectedIndex + 2);
			driver->nextTurn();		
			
			newTurn(driver->getTurn());

		}
		else{
			this->saveErrorMessage->Visible = true;
			this->saveErrorMessage->Text = convertStringToSystemString(error);
		}
	}
}
//applying changes to border checkbox list
System::Void UI::borderApplyChangesButton_Click(System::Object^  sender, System::EventArgs^  e){
	vector<string> previousBorders = driver->getBordersOfTerritory(convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));
	bool borderExist = false;
	for (int i = 0; i < driver->getAllTerritories().size(); i++){//for all territories
		if (this->bordersCheckList->GetItemChecked(i)){//if territory is checked
			borderExist = false;
			for (int j = 0; j < previousBorders.size(); j++){//for all previous borders of that territory
				if (previousBorders[j].compare(driver->getTerritoryName(i)) == 0){//if border name matches checked territory name
					borderExist = true;
				}
			}
			if (!borderExist){//if border doesn't exist already
				if (convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem).compare(driver->getTerritoryName(i)) != 0){//if not adding border to own territory
					driver->addBorders(i, convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));//adds borders both sides
				}
			}
		}
		else{//if territory not checked
			borderExist = false;
			for (int j = 0; j < previousBorders.size(); j++){//for all previous borders of that territory
				if (previousBorders[j].compare(driver->getTerritoryName(i)) == 0){//if border name matches checked territory name
					borderExist = true;
				}
			}
			if (borderExist){//if territory was previously checked
				driver->deleteBorders(i, convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));//delete border both sides
			}
		}
	}

	//refreshes borders box
	this->bordersCheckList->Items->Clear();
	this->borderApplyChangesButton->Visible = false;
	this->saveErrorMessage->Visible = false;
	this->bordersLabel->Visible = true;
	this->bordersCheckList->Visible = true;
	this->territoryDeleteButton->Visible = true;
	this->mapPictureBox->Refresh();
	this->territoryEditButton->Visible = true;
	vector<Territory> territories = driver->getAllTerritories();
	vector<std::string> borders = driver->getBordersOfTerritory(convertSystemStringToString((String^)this->territoriesComboBox->SelectedItem));
	for (int i = 0; i < territories.size(); i++){//Populate territories in CheckList
		this->bordersCheckList->Items->Add(convertStringToSystemString(territories[i].getName()));
		for (int j = 0; j < borders.size(); j++){//sets the checkbox of correct borders
			if (borders[j].compare(territories[i].getName()) == 0){
				this->bordersCheckList->SetItemChecked(i, true);
			}
		}
	}
}



//Function that draws the graphical map, is called with this->mapPictureBox->Refresh();
System::Void UI:: pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){

	Graphics^ g = e->Graphics;

	g->Clear(Color::AntiqueWhite);



	Pen^ pen = gcnew Pen(Color::Black, 1);
	SolidBrush^ brush = gcnew SolidBrush(Color::Black);
	int fontsize = 13;
	System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", fontsize, FontStyle::Bold);
	
	vector<Territory> territories = driver->getAllTerritories();
	vector<Continent> continents = driver->getAllContinents();
	
	int circleSize = 30;
	float resize = 0.65;
	float resizedCircle = resize * circleSize;
	float x;
	float y;
	Color specificColor;
	for (int i = 0; i < territories.size(); i++){
		
		for (int j = 0; j < territories[i].getAllBorders().size(); j++){
			int index = driver->getTerritoryIndex(territories[i].getAllBorders()[j]);
			x = resize*territories[i].getX();
			y = resize*territories[i].getY();
			g->DrawLine(pen, circleSize + x, circleSize + y, circleSize + resize*driver->getTerritoryX(index), circleSize + resize*driver->getTerritoryY(index));//start point X, Start point Y, endpoint X, endpoint Y				
			
			

		}
	}
	
	
	for (int i = 0; i < territories.size(); i++){
		for (int k = 0; k < continents.size(); k++){//gets continent index
			if (continents[k].getName().compare(territories[i].getContinentName()) == 0){
				srand(k*3);//generates random from seed
				specificColor = Color::FromArgb(255, rand() % 135 + 120, rand() % 135 + 120, rand() % 135 + 120);
				k = continents.size();//exits loop
			}
		}
		brush->Color = specificColor;
		x = resize*territories[i].getX();
		y = resize*territories[i].getY();
		g->FillEllipse(brush, circleSize + x - resizedCircle / 2, circleSize + y - resizedCircle / 2, resizedCircle, resizedCircle);
	}
	srand(time(NULL));
	if (inGame){
		for (int i = 0; i < territories.size(); i++){
			x = resize*territories[i].getX();
			y = resize*territories[i].getY();
			int player = territories[i].getIndexOfControllingPlayer();
			switch (player)
			{
			case -1:
				specificColor = Color::White;
				break;
			case 0:
				specificColor = Color::Blue;
				break;
			case 1:
				specificColor = Color::Red;
				break;
			case 2:
				specificColor = Color::Black;
				break;
			case 3:
				specificColor = Color::DarkViolet;
				break;
			case 4:
				specificColor = Color::ForestGreen;
				break;
			case 5:
				specificColor = Color::DarkOrange;
				break;
			}
			
			brush->Color = specificColor;
			pen->Color = specificColor;
			g->DrawEllipse(pen, circleSize + x - resizedCircle / 2, circleSize + y - resizedCircle / 2, resizedCircle, resizedCircle);
			g->DrawString(convertIntToSystemString(territories[i].getArmiesInTerritory()), drawFont, brush, fontsize + circleSize + x - resizedCircle, circleSize + y - resizedCircle / 2);
		}
	}
	delete drawFont;
	delete brush;
	delete pen;
}


//--------------------------
//game event pannel methods
//--------------------------

//sets new turn for selected player, sets display for reinforcment
void UI::newTurn(int playerTurn){
	
	this->reinforceTerritoryComboBox->Items->Clear();
	this->reinforceArmyComboBox->Items->Clear();
	this->attackArmyCombobox->Items->Clear();
	this->attackEnemyTerritoryCombobox->Items->Clear();
	this->attackPlayerTerritoryCombobox->Items->Clear();
	this->fortifyArmyComboBox->Items->Clear();
	this->fortifyDestinationTerritoryComboBox->Items->Clear();
	this->fortifySourceTerritoryComboBox->Items->Clear();

	this->reinforceTerritoryComboBox->Enabled = true;
	this->reinforceArmyComboBox->Enabled = true;
	this->finishReinforceButton->Enabled = true;

	this->finishAttackingPhaseButton->Enabled = false;
	this->attackButton->Enabled = false;
	this->attackArmyCombobox->Enabled = false;
	this->attackEnemyTerritoryCombobox->Enabled = false;
	this->attackPlayerTerritoryCombobox->Enabled = false;

	this->finishFortificationPhaseButton->Enabled = false;
	this->fortifyArmyComboBox->Enabled = false;
	this->fortifyDestinationTerritoryComboBox->Enabled = false;
	this->fortifySourceTerritoryComboBox->Enabled = false;
	this->fortifyButton->Enabled = false;
	this->useCardsButton->Enabled = true;

	while (driver->getArtilleryCards() > 4 || driver->getCavalryCards() > 4 || driver->getInfantryCards() > 4){
		if (driver->getInfantryCards() > 4){
			driver->setInfantryCards(driver->getInfantryCards() - 3);
			driver->addReinforcements(driver->getCardsValue());
			driver->setCardsPlayed(driver->getCardsValue()/ 5 + 1);
		}
		else if (driver->getCavalryCards() > 4){
			driver->setCavalryCards(driver->getCavalryCards() - 3);
			driver->addReinforcements(driver->getCardsValue());
			driver->setCardsPlayed(driver->getCardsValue()/ 5 + 1);
		}
		else if (driver->getArtilleryCards() > 4){
			driver->setArtilleryCards(driver->getArtilleryCards() - 3);
			driver->addReinforcements(driver->getCardsValue());
			driver->setCardsPlayed(driver->getCardsValue()/ 5 + 1);
		}
	}
	
	this->artilleryCardTextBox->Text = convertIntToSystemString(driver->getArtilleryCards());
	this->cavalryCardTextBox->Text = convertIntToSystemString(driver->getCavalryCards());
	this->infantryCardTextBox->Text = convertIntToSystemString(driver->getInfantryCards());
	this->cardsValueTextBox->Text = convertIntToSystemString(driver->getCardsValue());
	alreadyWonOneBattleThisTurn = false;
	this->saveExitButton->Enabled = false;
	this->finishReinforceButton->Focus();
	this->playerNameTextBox->Text = convertStringToSystemString(driver->getPlayerByID(playerTurn)->getName());
	driver->setPhase(1);
	this->reinforceTerritoryComboBox->Items->Clear();
	this->reinforceTerritoryComboBox->Items->Add("Territory to reinforce");
	this->reinforceTerritoryComboBox->SelectedIndex = 0;
	this->reinforceArmyComboBox->Items->Clear();
	this->reinforceArmyComboBox->Items->Add("Armies");
	this->reinforceArmyComboBox->SelectedIndex = 0;
	vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
	for (int i = 0; i < t.size(); i++){//display player's territories into the reinforce combobox
		this->reinforceTerritoryComboBox->Items->Add(convertStringToSystemString(t[i]->getName()));
	}
	this->mapPictureBox->Refresh();
	driver->setPhase(1);
}
//checks changes in the playerTextBox name, if changed, updates player name
System::Void UI::playerNameTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e){
	driver->setCurrentPlayerName(convertSystemStringToString(this->playerNameTextBox->Text));
}
//checks changes in reinforce combobox, if changed: updates available armies in army comboBox
System::Void UI::reinforceTerritoryComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->reinforceArmyComboBox->Items->Clear();
	this->reinforceArmyComboBox->Items->Add("Armies");
	this->reinforceArmyComboBox->SelectedIndex = 0;
	if (this->reinforceTerritoryComboBox->SelectedIndex != 0){
		for (int i = 0; i < driver->getCurrentPlayerReinforcments(); i++){
			this->reinforceArmyComboBox->Items->Add(convertIntToSystemString(i+1));
		}
	}
}
//checks changes in reinforce army combobox, if changed updates available armies in army comboBox
System::Void UI::reinforceArmyComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	if (this->reinforceArmyComboBox->SelectedIndex != 0){
		vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
		driver->reinforce(this->reinforceArmyComboBox->SelectedIndex, t[this->reinforceTerritoryComboBox->SelectedIndex - 1]);
		this->reinforceArmyComboBox->Items->Clear();
		this->reinforceArmyComboBox->Items->Add("Armies");
		this->reinforceArmyComboBox->SelectedIndex = 0;
		this->reinforceTerritoryComboBox->SelectedIndex = 0;
		this->mapPictureBox->Refresh();

	}
}
//changes phase, disable reinforce GUI, enables attack
System::Void UI::finishReinforceButton_Click(System::Object^  sender, System::EventArgs^  e){
	
	this->reinforceTerritoryComboBox->Enabled = false;
	this->reinforceArmyComboBox->Enabled = false;
	this->finishReinforceButton->Enabled = false;

	this->finishAttackingPhaseButton->Enabled = true;
	this->attackButton->Enabled = true;
	this->attackArmyCombobox->Enabled = true;
	this->attackEnemyTerritoryCombobox->Enabled = true;
	this->attackPlayerTerritoryCombobox->Enabled = true;

	this->finishFortificationPhaseButton->Enabled = false;
	this->fortifyArmyComboBox->Enabled = false;
	this->fortifyDestinationTerritoryComboBox->Enabled = false;
	this->fortifySourceTerritoryComboBox->Enabled = false;
	this->fortifyButton->Enabled = false;
	this->useCardsButton->Enabled = false;

	this->attackPlayerTerritoryCombobox->Items->Clear();
	this->attackPlayerTerritoryCombobox->Items->Add("Attack from this Territory");
	this->attackPlayerTerritoryCombobox->SelectedIndex = 0;
	this->attackEnemyTerritoryCombobox->Items->Clear();
	this->attackEnemyTerritoryCombobox->Items->Add("Attack this Territory");
	this->attackEnemyTerritoryCombobox->SelectedIndex = 0;
	this->attackArmyCombobox->Items->Clear();
	this->attackArmyCombobox->Items->Add("Armies");
	this->attackArmyCombobox->SelectedIndex = 0;
	vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
	temporalPlayerTerritory.clear();//used to not allow played to attack with a territory he just won
	for (int i = 0; i < t.size(); i++){//display player's territories into the reinforce combobox
		if (t[i]->getArmiesInTerritory() > 1){
			temporalPlayerTerritory.push_back(t[i]);
			this->attackPlayerTerritoryCombobox->Items->Add(convertStringToSystemString(t[i]->getName()));
		}
	}
	


	this->finishAttackingPhaseButton->Focus();
	driver->setPhase(2);
}
//checks changes in source attack combobox, updates the available armies to attack with and linked territories of that one
System::Void UI::attackPlayerTerritoryCombobox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->attackArmyCombobox->Items->Clear();
	this->attackArmyCombobox->Items->Add("Armies");
	this->attackArmyCombobox->SelectedIndex = 0;
	this->attackEnemyTerritoryCombobox->Items->Clear();
	this->attackEnemyTerritoryCombobox->Items->Add("Attack this Territory");
	this->attackEnemyTerritoryCombobox->SelectedIndex = 0;
	if (this->attackPlayerTerritoryCombobox->SelectedIndex != 0){
		//vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
		int territoryIndex = this->attackPlayerTerritoryCombobox->SelectedIndex;
		int correctIndex = territoryIndex-1;
		
		/*for (int i = 0; i < temporalPlayerTerritory.size(); i++){
			if (temporalPlayerTerritory[i]->getArmiesInTerritory() > 1){
				territoryIndex = territoryIndex - 1;
				if (territoryIndex == 0){
					correctIndex = i;
				}
			}
		}*/


		vector<Territory> allTerritories = driver->getAllTerritories();
		vector<string> borders = temporalPlayerTerritory[correctIndex]->getAllBorders();
		for (int i = 0; i < borders.size(); i++){
			if (allTerritories[driver->getTerritoryIndex(borders[i])].getIndexOfControllingPlayer() != driver->getTurn()){
				this->attackEnemyTerritoryCombobox->Items->Add(convertStringToSystemString(borders[i]));
			}
		}
		
		for (int j = 0; j < temporalPlayerTerritory[correctIndex]->getArmiesInTerritory() - 1; j++){
			this->attackArmyCombobox->Items->Add(convertIntToSystemString(j + 1));
		}
		/*for (int i = 0; i < t[this->attackPlayerTerritoryCombobox->SelectedIndex - 1]->getArmiesInTerritory()-1; i++){
			this->attackArmyCombobox->Items->Add(convertIntToSystemString(i + 1));
		}*/
		
	}
	
}
//calls the rolling and updates map and attacking comboboxes set to nothing
System::Void UI::attackButton_Click(System::Object^  sender, System::EventArgs^  e){
	if (this->attackPlayerTerritoryCombobox->SelectedIndex != 0 && this->attackEnemyTerritoryCombobox->SelectedIndex != 0 && this->attackArmyCombobox->SelectedIndex != 0){
		//vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();

		int territoryIndex = this->attackPlayerTerritoryCombobox->SelectedIndex;
		int correctIndex = territoryIndex-1;
		
		/*for (int i = 0; i < temporalPlayerTerritory.size(); i++){
			if (temporalPlayerTerritory[i]->getArmiesInTerritory() > 1){
				territoryIndex = territoryIndex - 1;
				if (territoryIndex == 0){
					correctIndex = i;
				}
			}
		}*/

		int attackingTerritoryIndex = this->attackEnemyTerritoryCombobox->SelectedIndex;
		int correctAttackingIndex;
		vector<Territory> allTerritories = driver->getAllTerritories();
		vector<string> borders = temporalPlayerTerritory[correctIndex]->getAllBorders();
		for (int i = 0; i < borders.size(); i++){
			if (allTerritories[driver->getTerritoryIndex(borders[i])].getIndexOfControllingPlayer() != driver->getTurn()){
				attackingTerritoryIndex = attackingTerritoryIndex - 1;
				if (attackingTerritoryIndex == 0){
					correctAttackingIndex = i;
				}
			}
		}

		
		alreadyWonOneBattleThisTurn = driver->attackCalculations(temporalPlayerTerritory[correctIndex], this->attackArmyCombobox->SelectedIndex, driver->getTerritory(driver->getTerritoryIndex(borders[correctAttackingIndex])), alreadyWonOneBattleThisTurn);
		this->mapPictureBox->Refresh();
		this->attackPlayerTerritoryCombobox->SelectedIndex = 0;
		this->attackArmyCombobox->Items->Clear();
		this->attackArmyCombobox->Items->Add("Armies");
		this->attackArmyCombobox->SelectedIndex = 0;
		this->attackEnemyTerritoryCombobox->Items->Clear();
		this->attackEnemyTerritoryCombobox->Items->Add("Attack this Territory");
		this->attackEnemyTerritoryCombobox->SelectedIndex = 0;



	}
}
//finishing attack, sets next phase, disables attack gui, enables fortify gui
System::Void UI::finishAttackingPhaseButton_Click(System::Object^  sender, System::EventArgs^  e){
	
	this->reinforceTerritoryComboBox->Enabled = false;
	this->reinforceArmyComboBox->Enabled = false;
	this->finishReinforceButton->Enabled = false;

	this->finishAttackingPhaseButton->Enabled = false;
	this->attackButton->Enabled = false;
	this->attackArmyCombobox->Enabled = false;
	this->attackEnemyTerritoryCombobox->Enabled = false;
	this->attackPlayerTerritoryCombobox->Enabled = false;

	this->finishFortificationPhaseButton->Enabled = true;
	this->fortifyArmyComboBox->Enabled = true;
	this->fortifyDestinationTerritoryComboBox->Enabled = true;
	this->fortifySourceTerritoryComboBox->Enabled = true;
	this->fortifyButton->Enabled = true;

	this->fortifySourceTerritoryComboBox->Items->Clear();
	this->fortifySourceTerritoryComboBox->Items->Add("From this Territory");
	this->fortifySourceTerritoryComboBox->SelectedIndex = 0;
	this->fortifyDestinationTerritoryComboBox->Items->Clear();
	this->fortifyDestinationTerritoryComboBox->Items->Add("To this Territory");
	this->fortifyDestinationTerritoryComboBox->SelectedIndex = 0;
	vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
	for (int i = 0; i < t.size(); i++){//display player's territories into the reinforce combobox
		if (t[i]->getArmiesInTerritory() > 1){
			this->fortifySourceTerritoryComboBox->Items->Add(convertStringToSystemString(t[i]->getName()));
		}
		this->fortifyDestinationTerritoryComboBox->Items->Add(convertStringToSystemString(t[i]->getName()));
	}
	this->saveExitButton->Enabled = true;

	this->finishFortificationPhaseButton->Focus();
	driver->setPhase(3);
}
//checks changes in source fortify comboBox, updates armies available for transfer from source territory
System::Void UI::fortifySourceTerritoryComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	this->fortifyArmyComboBox->Items->Clear();
	this->fortifyArmyComboBox->Items->Add("Armies");
	this->fortifyArmyComboBox->SelectedIndex = 0;
	if (this->fortifySourceTerritoryComboBox->SelectedIndex != 0){

		vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
		int territoryIndex = this->fortifySourceTerritoryComboBox->SelectedIndex;
		int correctIndex;
		for (int i = 0; i < t.size(); i++){
			if (t[i]->getArmiesInTerritory() > 1){
				territoryIndex = territoryIndex - 1;
				if (territoryIndex == 0){
					correctIndex = i;
				}
			}
		}




		for (int i = 0; i < t[correctIndex]->getArmiesInTerritory() - 1; i++){
			this->fortifyArmyComboBox->Items->Add(convertIntToSystemString(i + 1));
		}
	}
}
//Transfers armies
System::Void  UI::fortifyButton_Click(System::Object^  sender, System::EventArgs^  e){
	if (this->fortifyArmyComboBox->SelectedIndex != 0 && this->fortifyDestinationTerritoryComboBox->SelectedIndex != 0 && this->fortifySourceTerritoryComboBox->SelectedIndex != 0){
		
		vector<Territory*> t = driver->getPlayerByID(driver->getTurn())->getTerritories();
		int territoryIndex = this->fortifySourceTerritoryComboBox->SelectedIndex;
		int correctIndex;
		for (int i = 0; i < t.size(); i++){
			if (t[i]->getArmiesInTerritory() > 1){
				territoryIndex = territoryIndex - 1;
				if (territoryIndex == 0){
					correctIndex = i;
				}
			}
		}

		if (t[correctIndex]->getName().compare(t[this->fortifyDestinationTerritoryComboBox->SelectedIndex - 1]->getName()) != 0){//not transfering from territory to same territory	
			if (driver->checkPathBetweenTerritoriesOfSamePlayer(t[correctIndex], t[this->fortifyDestinationTerritoryComboBox->SelectedIndex - 1])){
				this->fortifyArmyComboBox->Enabled = false;
				this->fortifyDestinationTerritoryComboBox->Enabled = false;
				this->fortifySourceTerritoryComboBox->Enabled = false;
				this->fortifyButton->Enabled = false;
				driver->fortify(t[correctIndex], this->fortifyArmyComboBox->SelectedIndex, t[this->fortifyDestinationTerritoryComboBox->SelectedIndex - 1]);
				this->mapPictureBox->Refresh();
			}
		}

	}
}
//disable fortification, next player turn
System::Void UI::finishFortificationPhase_Click(System::Object^  sender, System::EventArgs^  e){
	this->reinforceTerritoryComboBox->Enabled = false;
	this->reinforceArmyComboBox->Enabled = false;
	this->finishReinforceButton->Enabled = false;

	this->finishAttackingPhaseButton->Enabled = false;
	this->attackButton->Enabled = false;
	this->attackArmyCombobox->Enabled = false;
	this->attackEnemyTerritoryCombobox->Enabled = false;
	this->attackPlayerTerritoryCombobox->Enabled = false;

	this->finishFortificationPhaseButton->Enabled = false;
	this->fortifyArmyComboBox->Enabled = false;
	this->fortifyDestinationTerritoryComboBox->Enabled = false;
	this->fortifySourceTerritoryComboBox->Enabled = false;
	this->fortifyButton->Enabled = false;
	this->saveExitButton->Enabled = false;
	driver->nextTurn();
	newTurn(driver->getTurn());
	driver->setPhase(0);
}
void UI::notify(){
	this->mapPictureBox->Refresh();
}
void UI::updateLogInUI(string text){
	this->logTextBox->Text = convertStringToSystemString(text);
}
System::Void UI::useCardsButton_Click(System::Object^  sender, System::EventArgs^  e){
	int artCard = driver->getArtilleryCards();
	int cavCard = driver->getCavalryCards();
	int infCard = driver->getInfantryCards();
	int cardVal = driver->getCardsValue();
	if (artCard > 0 && cavCard > 0 && infCard > 0){
		driver->setArtilleryCards(artCard-1);
		driver->setCavalryCards(cavCard - 1);
		driver->setInfantryCards(infCard - 1);
		driver->addReinforcements(cardVal);
		driver->setCardsPlayed(cardVal/5 + 1);
	}
	else if (infCard > 2){
		driver->setInfantryCards(infCard - 3);
		driver->addReinforcements(cardVal);
		driver->setCardsPlayed(cardVal / 5 + 1);
	}
	else if (cavCard > 2){
		driver->setCavalryCards(cavCard - 3);
		driver->addReinforcements(cardVal);
		driver->setCardsPlayed(cardVal / 5 + 1);
	}
	else if (artCard > 2){
		driver->setArtilleryCards(artCard - 3);
		driver->addReinforcements(cardVal);
		driver->setCardsPlayed(cardVal / 5 + 1);
	}
	this->artilleryCardTextBox->Text = convertIntToSystemString(driver->getArtilleryCards());
	this->cavalryCardTextBox->Text = convertIntToSystemString(driver->getCavalryCards());
	this->infantryCardTextBox->Text = convertIntToSystemString(driver->getInfantryCards());
	this->cardsValueTextBox->Text = convertIntToSystemString(driver->getCardsValue());
	this->reinforceTerritoryComboBox->SelectedIndex = 0;
}
System::Void UI::showStatsButton_Click(System::Object^  sender, System::EventArgs^  e){
	MessageBox::Show(convertStringToSystemString(driver->getStats()));
}
System::Void saveExitButton_Click(System::Object^  sender, System::EventArgs^  e){
	exit(0);
}