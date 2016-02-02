#ifndef UI_H
#define UI_H
#pragma once
#include <msclr/marshal.h>
#include <string>
namespace Risk {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	public ref class UI : public System::Windows::Forms::Form
	{
	public:
		UI(void);
		void notify();
		void updateLogInUI(std::string);
	protected:
		~UI()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
	System::Windows::Forms::Button^  loadButton;
	System::Windows::Forms::Button^  createButton;
	System::Windows::Forms::Button^  okButton;
	System::Windows::Forms::Button^  cancelButton;
	System::Windows::Forms::Label^  enterMapNameLabel;
	System::Windows::Forms::TextBox^  mapNameTextBox;
	System::Windows::Forms::Button^  yesButton;
	System::Windows::Forms::Label^  continentsLabel;
	System::Windows::Forms::Label^  territoriesLabel;
	System::Windows::Forms::Label^  bordersLabel;
	System::Windows::Forms::ComboBox^  continentsComboBox;
	System::Windows::Forms::Button^  addContinentButton;
	System::Windows::Forms::Button^  deleteContinentButton;
	System::Windows::Forms::Button^  continentEditButton;
	System::Windows::Forms::Label^  continentNameLabel;
	System::Windows::Forms::TextBox^  continentEditTextBox;
	System::Windows::Forms::ComboBox^  territoriesComboBox;
	System::Windows::Forms::Button^  territoryAddButton;
	System::Windows::Forms::Button^  territoryDeleteButton;
	System::Windows::Forms::Button^  territoryEditButton;
	System::Windows::Forms::Label^  territoryEditNameLabel;
	System::Windows::Forms::TextBox^  territoryEditTextBox;
	System::Windows::Forms::Button^  continentOkEditButton;
	System::Windows::Forms::Button^  territoryOkEditButton;
	System::Windows::Forms::CheckedListBox^  bordersCheckList;
	System::Windows::Forms::Button^  borderApplyChangesButton;
	System::Windows::Forms::Button^  saveMapAndPlayButton;
	private: System::Windows::Forms::Label^  numberOfPlayersLabel;
	private: System::Windows::Forms::ComboBox^  numberOfPlayerComboBox;
	private: System::Windows::Forms::Label^  saveErrorMessage;
	private: System::Windows::Forms::PictureBox^  mapPictureBox;
	private: System::Windows::Forms::Label^  numberOfAIPlayersLabel;

	private: System::Windows::Forms::ComboBox^  numberOfAIComboBox;
	private: System::Windows::Forms::Panel^  gamePanel;
	private: System::Windows::Forms::Label^  fortifyLabel;
	private: System::Windows::Forms::Button^  finishAttackingPhaseButton;
	private: System::Windows::Forms::Button^  attackButton;
	private: System::Windows::Forms::ComboBox^  attackArmyCombobox;
	private: System::Windows::Forms::ComboBox^  attackEnemyTerritoryCombobox;
	private: System::Windows::Forms::ComboBox^  attackPlayerTerritoryCombobox;
	private: System::Windows::Forms::Label^  attackLabel;
	private: System::Windows::Forms::Button^  finishReinforceButton;
	private: System::Windows::Forms::ComboBox^  reinforceArmyComboBox;
	private: System::Windows::Forms::ComboBox^  reinforceTerritoryComboBox;
	private: System::Windows::Forms::Label^  reinforceLabel;
	private: System::Windows::Forms::TextBox^  playerNameTextBox;
	private: System::Windows::Forms::Button^  finishFortificationPhaseButton;

	private: System::Windows::Forms::ComboBox^  fortifyArmyComboBox;
	private: System::Windows::Forms::ComboBox^  fortifyDestinationTerritoryComboBox;
	private: System::Windows::Forms::ComboBox^  fortifySourceTerritoryComboBox;
	private: System::Windows::Forms::Button^  fortifyButton;
	private: System::Windows::Forms::ListBox^  continentValuesListBox;
	private: System::Windows::Forms::Label^  infantryCardLabel;
	private: System::Windows::Forms::Label^  cavalryCardLabel;
	private: System::Windows::Forms::Label^  artilleryCardLabel;
	private: System::Windows::Forms::TextBox^  artilleryCardTextBox;

	private: System::Windows::Forms::TextBox^  cavalryCardTextBox;

	private: System::Windows::Forms::TextBox^  infantryCardTextBox;
	private: System::Windows::Forms::Button^  useCardsButton;

	private: System::Windows::Forms::TextBox^  cardsValueTextBox;

	private: System::Windows::Forms::Label^  cardsValueLabel;
	private: System::Windows::Forms::TextBox^  logTextBox;
	private: System::Windows::Forms::Button^  showStatsButton;
	private: System::Windows::Forms::Button^  saveExitButton;










			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->createButton = (gcnew System::Windows::Forms::Button());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->enterMapNameLabel = (gcnew System::Windows::Forms::Label());
			this->mapNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->yesButton = (gcnew System::Windows::Forms::Button());
			this->continentsLabel = (gcnew System::Windows::Forms::Label());
			this->territoriesLabel = (gcnew System::Windows::Forms::Label());
			this->bordersLabel = (gcnew System::Windows::Forms::Label());
			this->continentsComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->addContinentButton = (gcnew System::Windows::Forms::Button());
			this->deleteContinentButton = (gcnew System::Windows::Forms::Button());
			this->continentEditButton = (gcnew System::Windows::Forms::Button());
			this->continentNameLabel = (gcnew System::Windows::Forms::Label());
			this->continentEditTextBox = (gcnew System::Windows::Forms::TextBox());
			this->territoriesComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->territoryAddButton = (gcnew System::Windows::Forms::Button());
			this->territoryDeleteButton = (gcnew System::Windows::Forms::Button());
			this->territoryEditButton = (gcnew System::Windows::Forms::Button());
			this->territoryEditNameLabel = (gcnew System::Windows::Forms::Label());
			this->territoryEditTextBox = (gcnew System::Windows::Forms::TextBox());
			this->continentOkEditButton = (gcnew System::Windows::Forms::Button());
			this->territoryOkEditButton = (gcnew System::Windows::Forms::Button());
			this->bordersCheckList = (gcnew System::Windows::Forms::CheckedListBox());
			this->borderApplyChangesButton = (gcnew System::Windows::Forms::Button());
			this->saveMapAndPlayButton = (gcnew System::Windows::Forms::Button());
			this->numberOfPlayersLabel = (gcnew System::Windows::Forms::Label());
			this->numberOfPlayerComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->saveErrorMessage = (gcnew System::Windows::Forms::Label());
			this->mapPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->numberOfAIPlayersLabel = (gcnew System::Windows::Forms::Label());
			this->numberOfAIComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->gamePanel = (gcnew System::Windows::Forms::Panel());
			this->showStatsButton = (gcnew System::Windows::Forms::Button());
			this->saveExitButton = (gcnew System::Windows::Forms::Button());
			this->useCardsButton = (gcnew System::Windows::Forms::Button());
			this->cardsValueTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cardsValueLabel = (gcnew System::Windows::Forms::Label());
			this->artilleryCardTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cavalryCardTextBox = (gcnew System::Windows::Forms::TextBox());
			this->infantryCardTextBox = (gcnew System::Windows::Forms::TextBox());
			this->artilleryCardLabel = (gcnew System::Windows::Forms::Label());
			this->cavalryCardLabel = (gcnew System::Windows::Forms::Label());
			this->infantryCardLabel = (gcnew System::Windows::Forms::Label());
			this->fortifyButton = (gcnew System::Windows::Forms::Button());
			this->playerNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->finishFortificationPhaseButton = (gcnew System::Windows::Forms::Button());
			this->fortifyArmyComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->fortifyDestinationTerritoryComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->fortifySourceTerritoryComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->fortifyLabel = (gcnew System::Windows::Forms::Label());
			this->finishAttackingPhaseButton = (gcnew System::Windows::Forms::Button());
			this->attackButton = (gcnew System::Windows::Forms::Button());
			this->attackArmyCombobox = (gcnew System::Windows::Forms::ComboBox());
			this->attackEnemyTerritoryCombobox = (gcnew System::Windows::Forms::ComboBox());
			this->attackPlayerTerritoryCombobox = (gcnew System::Windows::Forms::ComboBox());
			this->attackLabel = (gcnew System::Windows::Forms::Label());
			this->finishReinforceButton = (gcnew System::Windows::Forms::Button());
			this->reinforceArmyComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->reinforceTerritoryComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->reinforceLabel = (gcnew System::Windows::Forms::Label());
			this->continentValuesListBox = (gcnew System::Windows::Forms::ListBox());
			this->logTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mapPictureBox))->BeginInit();
			this->gamePanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// loadButton
			// 
			this->loadButton->Location = System::Drawing::Point(37, 64);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(122, 40);
			this->loadButton->TabIndex = 0;
			this->loadButton->Text = L"Load Map";
			this->loadButton->UseVisualStyleBackColor = true;
			this->loadButton->Visible = false;
			this->loadButton->Click += gcnew System::EventHandler(this, &UI::loadButton_Click);
			// 
			// createButton
			// 
			this->createButton->Location = System::Drawing::Point(183, 64);
			this->createButton->Name = L"createButton";
			this->createButton->Size = System::Drawing::Size(122, 40);
			this->createButton->TabIndex = 1;
			this->createButton->Text = L"Create Map";
			this->createButton->UseVisualStyleBackColor = true;
			this->createButton->Visible = false;
			this->createButton->Click += gcnew System::EventHandler(this, &UI::createButton_Click);
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(154, 100);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(86, 30);
			this->okButton->TabIndex = 2;
			this->okButton->Text = L"Ok";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Visible = false;
			this->okButton->Click += gcnew System::EventHandler(this, &UI::okButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(246, 100);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(86, 30);
			this->cancelButton->TabIndex = 3;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Visible = false;
			this->cancelButton->Click += gcnew System::EventHandler(this, &UI::cancelButton_Click);
			// 
			// enterMapNameLabel
			// 
			this->enterMapNameLabel->AutoSize = true;
			this->enterMapNameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->enterMapNameLabel->Location = System::Drawing::Point(112, 19);
			this->enterMapNameLabel->Name = L"enterMapNameLabel";
			this->enterMapNameLabel->Size = System::Drawing::Size(128, 20);
			this->enterMapNameLabel->TabIndex = 4;
			this->enterMapNameLabel->Text = L"Welcome to Risk";
			this->enterMapNameLabel->Visible = false;
			// 
			// mapNameTextBox
			// 
			this->mapNameTextBox->Location = System::Drawing::Point(16, 54);
			this->mapNameTextBox->Name = L"mapNameTextBox";
			this->mapNameTextBox->Size = System::Drawing::Size(280, 20);
			this->mapNameTextBox->TabIndex = 5;
			this->mapNameTextBox->Visible = false;
			// 
			// yesButton
			// 
			this->yesButton->Location = System::Drawing::Point(62, 100);
			this->yesButton->Name = L"yesButton";
			this->yesButton->Size = System::Drawing::Size(86, 30);
			this->yesButton->TabIndex = 6;
			this->yesButton->Text = L"Yes";
			this->yesButton->UseVisualStyleBackColor = true;
			this->yesButton->Visible = false;
			this->yesButton->Click += gcnew System::EventHandler(this, &UI::yesButton_Click);
			// 
			// continentsLabel
			// 
			this->continentsLabel->AutoSize = true;
			this->continentsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->continentsLabel->Location = System::Drawing::Point(12, 19);
			this->continentsLabel->Name = L"continentsLabel";
			this->continentsLabel->Size = System::Drawing::Size(86, 20);
			this->continentsLabel->TabIndex = 7;
			this->continentsLabel->Text = L"Continents";
			this->continentsLabel->Visible = false;
			// 
			// territoriesLabel
			// 
			this->territoriesLabel->AutoSize = true;
			this->territoriesLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->territoriesLabel->Location = System::Drawing::Point(12, 153);
			this->territoriesLabel->Name = L"territoriesLabel";
			this->territoriesLabel->Size = System::Drawing::Size(79, 20);
			this->territoriesLabel->TabIndex = 8;
			this->territoriesLabel->Text = L"Territories";
			this->territoriesLabel->Visible = false;
			// 
			// bordersLabel
			// 
			this->bordersLabel->AutoSize = true;
			this->bordersLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->bordersLabel->Location = System::Drawing::Point(12, 275);
			this->bordersLabel->Name = L"bordersLabel";
			this->bordersLabel->Size = System::Drawing::Size(65, 20);
			this->bordersLabel->TabIndex = 9;
			this->bordersLabel->Text = L"Borders";
			this->bordersLabel->Visible = false;
			// 
			// continentsComboBox
			// 
			this->continentsComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->continentsComboBox->FormattingEnabled = true;
			this->continentsComboBox->Location = System::Drawing::Point(16, 53);
			this->continentsComboBox->Name = L"continentsComboBox";
			this->continentsComboBox->Size = System::Drawing::Size(237, 21);
			this->continentsComboBox->TabIndex = 10;
			this->continentsComboBox->Visible = false;
			this->continentsComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::continentsComboBox_SelectedIndexChanged);
			// 
			// addContinentButton
			// 
			this->addContinentButton->Location = System::Drawing::Point(16, 80);
			this->addContinentButton->Name = L"addContinentButton";
			this->addContinentButton->Size = System::Drawing::Size(75, 23);
			this->addContinentButton->TabIndex = 11;
			this->addContinentButton->Text = L"Add";
			this->addContinentButton->UseVisualStyleBackColor = true;
			this->addContinentButton->Visible = false;
			this->addContinentButton->Click += gcnew System::EventHandler(this, &UI::addContinentButton_Click);
			// 
			// deleteContinentButton
			// 
			this->deleteContinentButton->Location = System::Drawing::Point(97, 80);
			this->deleteContinentButton->Name = L"deleteContinentButton";
			this->deleteContinentButton->Size = System::Drawing::Size(75, 23);
			this->deleteContinentButton->TabIndex = 12;
			this->deleteContinentButton->Text = L"Delete";
			this->deleteContinentButton->UseVisualStyleBackColor = true;
			this->deleteContinentButton->Visible = false;
			this->deleteContinentButton->Click += gcnew System::EventHandler(this, &UI::deleteContinentButton_Click);
			// 
			// continentEditButton
			// 
			this->continentEditButton->Location = System::Drawing::Point(178, 80);
			this->continentEditButton->Name = L"continentEditButton";
			this->continentEditButton->Size = System::Drawing::Size(75, 23);
			this->continentEditButton->TabIndex = 13;
			this->continentEditButton->Text = L"Edit";
			this->continentEditButton->UseVisualStyleBackColor = true;
			this->continentEditButton->Visible = false;
			this->continentEditButton->Click += gcnew System::EventHandler(this, &UI::continentEditButton_Click);
			// 
			// continentNameLabel
			// 
			this->continentNameLabel->AutoSize = true;
			this->continentNameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->continentNameLabel->Location = System::Drawing::Point(12, 107);
			this->continentNameLabel->Name = L"continentNameLabel";
			this->continentNameLabel->Size = System::Drawing::Size(55, 20);
			this->continentNameLabel->TabIndex = 14;
			this->continentNameLabel->Text = L"Name:";
			this->continentNameLabel->Visible = false;
			// 
			// continentEditTextBox
			// 
			this->continentEditTextBox->Location = System::Drawing::Point(16, 130);
			this->continentEditTextBox->Name = L"continentEditTextBox";
			this->continentEditTextBox->Size = System::Drawing::Size(176, 20);
			this->continentEditTextBox->TabIndex = 15;
			this->continentEditTextBox->Visible = false;
			// 
			// territoriesComboBox
			// 
			this->territoriesComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->territoriesComboBox->FormattingEnabled = true;
			this->territoriesComboBox->Location = System::Drawing::Point(16, 176);
			this->territoriesComboBox->Name = L"territoriesComboBox";
			this->territoriesComboBox->Size = System::Drawing::Size(237, 21);
			this->territoriesComboBox->TabIndex = 16;
			this->territoriesComboBox->Visible = false;
			this->territoriesComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::territoriesComboBox_SelectedIndexChanged);
			// 
			// territoryAddButton
			// 
			this->territoryAddButton->Location = System::Drawing::Point(16, 203);
			this->territoryAddButton->Name = L"territoryAddButton";
			this->territoryAddButton->Size = System::Drawing::Size(75, 23);
			this->territoryAddButton->TabIndex = 17;
			this->territoryAddButton->Text = L"Add";
			this->territoryAddButton->UseVisualStyleBackColor = true;
			this->territoryAddButton->Visible = false;
			this->territoryAddButton->Click += gcnew System::EventHandler(this, &UI::territoryAddButton_Click);
			// 
			// territoryDeleteButton
			// 
			this->territoryDeleteButton->Location = System::Drawing::Point(97, 203);
			this->territoryDeleteButton->Name = L"territoryDeleteButton";
			this->territoryDeleteButton->Size = System::Drawing::Size(75, 23);
			this->territoryDeleteButton->TabIndex = 18;
			this->territoryDeleteButton->Text = L"Delete";
			this->territoryDeleteButton->UseVisualStyleBackColor = true;
			this->territoryDeleteButton->Visible = false;
			this->territoryDeleteButton->Click += gcnew System::EventHandler(this, &UI::territoryDeleteButton_Click);
			// 
			// territoryEditButton
			// 
			this->territoryEditButton->Location = System::Drawing::Point(178, 203);
			this->territoryEditButton->Name = L"territoryEditButton";
			this->territoryEditButton->Size = System::Drawing::Size(75, 23);
			this->territoryEditButton->TabIndex = 19;
			this->territoryEditButton->Text = L"Edit";
			this->territoryEditButton->UseVisualStyleBackColor = true;
			this->territoryEditButton->Visible = false;
			this->territoryEditButton->Click += gcnew System::EventHandler(this, &UI::territoryEditButton_Click);
			// 
			// territoryEditNameLabel
			// 
			this->territoryEditNameLabel->AutoSize = true;
			this->territoryEditNameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->territoryEditNameLabel->Location = System::Drawing::Point(12, 229);
			this->territoryEditNameLabel->Name = L"territoryEditNameLabel";
			this->territoryEditNameLabel->Size = System::Drawing::Size(55, 20);
			this->territoryEditNameLabel->TabIndex = 20;
			this->territoryEditNameLabel->Text = L"Name:";
			this->territoryEditNameLabel->Visible = false;
			// 
			// territoryEditTextBox
			// 
			this->territoryEditTextBox->Location = System::Drawing::Point(16, 252);
			this->territoryEditTextBox->Name = L"territoryEditTextBox";
			this->territoryEditTextBox->Size = System::Drawing::Size(176, 20);
			this->territoryEditTextBox->TabIndex = 21;
			this->territoryEditTextBox->Visible = false;
			// 
			// continentOkEditButton
			// 
			this->continentOkEditButton->Location = System::Drawing::Point(198, 128);
			this->continentOkEditButton->Name = L"continentOkEditButton";
			this->continentOkEditButton->Size = System::Drawing::Size(75, 23);
			this->continentOkEditButton->TabIndex = 22;
			this->continentOkEditButton->Text = L"Ok";
			this->continentOkEditButton->UseVisualStyleBackColor = true;
			this->continentOkEditButton->Visible = false;
			this->continentOkEditButton->Click += gcnew System::EventHandler(this, &UI::continentOkEditButton_Click);
			// 
			// territoryOkEditButton
			// 
			this->territoryOkEditButton->Location = System::Drawing::Point(198, 250);
			this->territoryOkEditButton->Name = L"territoryOkEditButton";
			this->territoryOkEditButton->Size = System::Drawing::Size(75, 23);
			this->territoryOkEditButton->TabIndex = 23;
			this->territoryOkEditButton->Text = L"Ok";
			this->territoryOkEditButton->UseVisualStyleBackColor = true;
			this->territoryOkEditButton->Visible = false;
			this->territoryOkEditButton->Click += gcnew System::EventHandler(this, &UI::territoryOkEditButton_Click);
			// 
			// bordersCheckList
			// 
			this->bordersCheckList->FormattingEnabled = true;
			this->bordersCheckList->Location = System::Drawing::Point(16, 298);
			this->bordersCheckList->Name = L"bordersCheckList";
			this->bordersCheckList->Size = System::Drawing::Size(237, 199);
			this->bordersCheckList->TabIndex = 24;
			this->bordersCheckList->Visible = false;
			this->bordersCheckList->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::bordersCheckList_SelectedIndexChanged);
			// 
			// borderApplyChangesButton
			// 
			this->borderApplyChangesButton->Location = System::Drawing::Point(154, 503);
			this->borderApplyChangesButton->Name = L"borderApplyChangesButton";
			this->borderApplyChangesButton->Size = System::Drawing::Size(99, 23);
			this->borderApplyChangesButton->TabIndex = 25;
			this->borderApplyChangesButton->Text = L"Apply Changes";
			this->borderApplyChangesButton->UseVisualStyleBackColor = true;
			this->borderApplyChangesButton->Visible = false;
			this->borderApplyChangesButton->Click += gcnew System::EventHandler(this, &UI::borderApplyChangesButton_Click);
			// 
			// saveMapAndPlayButton
			// 
			this->saveMapAndPlayButton->Location = System::Drawing::Point(16, 686);
			this->saveMapAndPlayButton->Name = L"saveMapAndPlayButton";
			this->saveMapAndPlayButton->Size = System::Drawing::Size(144, 40);
			this->saveMapAndPlayButton->TabIndex = 26;
			this->saveMapAndPlayButton->Text = L"Save Map And Play";
			this->saveMapAndPlayButton->UseVisualStyleBackColor = true;
			this->saveMapAndPlayButton->Visible = false;
			this->saveMapAndPlayButton->Click += gcnew System::EventHandler(this, &UI::saveMapAndPlayButton_Click);
			// 
			// numberOfPlayersLabel
			// 
			this->numberOfPlayersLabel->AutoSize = true;
			this->numberOfPlayersLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->numberOfPlayersLabel->Location = System::Drawing::Point(12, 663);
			this->numberOfPlayersLabel->Name = L"numberOfPlayersLabel";
			this->numberOfPlayersLabel->Size = System::Drawing::Size(179, 20);
			this->numberOfPlayersLabel->TabIndex = 30;
			this->numberOfPlayersLabel->Text = L"Total number of Players:";
			this->numberOfPlayersLabel->Visible = false;
			// 
			// numberOfPlayerComboBox
			// 
			this->numberOfPlayerComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->numberOfPlayerComboBox->FormattingEnabled = true;
			this->numberOfPlayerComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"2", L"3", L"4", L"5", L"6" });
			this->numberOfPlayerComboBox->Location = System::Drawing::Point(197, 665);
			this->numberOfPlayerComboBox->Name = L"numberOfPlayerComboBox";
			this->numberOfPlayerComboBox->Size = System::Drawing::Size(39, 21);
			this->numberOfPlayerComboBox->TabIndex = 31;
			this->numberOfPlayerComboBox->Visible = false;
			// 
			// saveErrorMessage
			// 
			this->saveErrorMessage->AutoSize = true;
			this->saveErrorMessage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->saveErrorMessage->Location = System::Drawing::Point(12, 729);
			this->saveErrorMessage->Name = L"saveErrorMessage";
			this->saveErrorMessage->Size = System::Drawing::Size(48, 20);
			this->saveErrorMessage->TabIndex = 32;
			this->saveErrorMessage->Text = L"Error:";
			this->saveErrorMessage->Visible = false;
			// 
			// mapPictureBox
			// 
			this->mapPictureBox->Location = System::Drawing::Point(302, 19);
			this->mapPictureBox->Name = L"mapPictureBox";
			this->mapPictureBox->Size = System::Drawing::Size(700, 700);
			this->mapPictureBox->TabIndex = 33;
			this->mapPictureBox->TabStop = false;
			this->mapPictureBox->Visible = false;
			this->mapPictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &UI::pictureBox1_Paint);
			// 
			// numberOfAIPlayersLabel
			// 
			this->numberOfAIPlayersLabel->AutoSize = true;
			this->numberOfAIPlayersLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->numberOfAIPlayersLabel->Location = System::Drawing::Point(12, 631);
			this->numberOfAIPlayersLabel->Name = L"numberOfAIPlayersLabel";
			this->numberOfAIPlayersLabel->Size = System::Drawing::Size(170, 20);
			this->numberOfAIPlayersLabel->TabIndex = 34;
			this->numberOfAIPlayersLabel->Text = L"Number of A.I. Players:";
			this->numberOfAIPlayersLabel->Visible = false;
			// 
			// numberOfAIComboBox
			// 
			this->numberOfAIComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->numberOfAIComboBox->FormattingEnabled = true;
			this->numberOfAIComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"0", L"1", L"2", L"3", L"4", L"5", L"6" });
			this->numberOfAIComboBox->Location = System::Drawing::Point(188, 633);
			this->numberOfAIComboBox->Name = L"numberOfAIComboBox";
			this->numberOfAIComboBox->Size = System::Drawing::Size(39, 21);
			this->numberOfAIComboBox->TabIndex = 35;
			this->numberOfAIComboBox->Visible = false;
			// 
			// gamePanel
			// 
			this->gamePanel->Controls->Add(this->showStatsButton);
			this->gamePanel->Controls->Add(this->saveExitButton);
			this->gamePanel->Controls->Add(this->useCardsButton);
			this->gamePanel->Controls->Add(this->cardsValueTextBox);
			this->gamePanel->Controls->Add(this->cardsValueLabel);
			this->gamePanel->Controls->Add(this->artilleryCardTextBox);
			this->gamePanel->Controls->Add(this->cavalryCardTextBox);
			this->gamePanel->Controls->Add(this->infantryCardTextBox);
			this->gamePanel->Controls->Add(this->artilleryCardLabel);
			this->gamePanel->Controls->Add(this->cavalryCardLabel);
			this->gamePanel->Controls->Add(this->infantryCardLabel);
			this->gamePanel->Controls->Add(this->fortifyButton);
			this->gamePanel->Controls->Add(this->playerNameTextBox);
			this->gamePanel->Controls->Add(this->finishFortificationPhaseButton);
			this->gamePanel->Controls->Add(this->fortifyArmyComboBox);
			this->gamePanel->Controls->Add(this->fortifyDestinationTerritoryComboBox);
			this->gamePanel->Controls->Add(this->fortifySourceTerritoryComboBox);
			this->gamePanel->Controls->Add(this->fortifyLabel);
			this->gamePanel->Controls->Add(this->finishAttackingPhaseButton);
			this->gamePanel->Controls->Add(this->attackButton);
			this->gamePanel->Controls->Add(this->attackArmyCombobox);
			this->gamePanel->Controls->Add(this->attackEnemyTerritoryCombobox);
			this->gamePanel->Controls->Add(this->attackPlayerTerritoryCombobox);
			this->gamePanel->Controls->Add(this->attackLabel);
			this->gamePanel->Controls->Add(this->finishReinforceButton);
			this->gamePanel->Controls->Add(this->reinforceArmyComboBox);
			this->gamePanel->Controls->Add(this->reinforceTerritoryComboBox);
			this->gamePanel->Controls->Add(this->reinforceLabel);
			this->gamePanel->Location = System::Drawing::Point(12, 12);
			this->gamePanel->Name = L"gamePanel";
			this->gamePanel->Size = System::Drawing::Size(284, 734);
			this->gamePanel->TabIndex = 36;
			this->gamePanel->Visible = false;
			// 
			// showStatsButton
			// 
			this->showStatsButton->Location = System::Drawing::Point(7, 667);
			this->showStatsButton->Name = L"showStatsButton";
			this->showStatsButton->Size = System::Drawing::Size(273, 29);
			this->showStatsButton->TabIndex = 28;
			this->showStatsButton->Text = L"Show Stats";
			this->showStatsButton->UseVisualStyleBackColor = true;
			this->showStatsButton->Visible = false;
			this->showStatsButton->Click += gcnew System::EventHandler(this, &UI::showStatsButton_Click);
			// 
			// saveExitButton
			// 
			this->saveExitButton->Location = System::Drawing::Point(7, 702);
			this->saveExitButton->Name = L"saveExitButton";
			this->saveExitButton->Size = System::Drawing::Size(273, 29);
			this->saveExitButton->TabIndex = 27;
			this->saveExitButton->Text = L"Save Game And Exit";
			this->saveExitButton->UseVisualStyleBackColor = true;
			this->saveExitButton->Visible = false;
			this->saveExitButton->Click += gcnew System::EventHandler(this, &UI::saveExitButton_Click);
			// 
			// useCardsButton
			// 
			this->useCardsButton->Location = System::Drawing::Point(157, 420);
			this->useCardsButton->Name = L"useCardsButton";
			this->useCardsButton->Size = System::Drawing::Size(93, 29);
			this->useCardsButton->TabIndex = 26;
			this->useCardsButton->Text = L"Use Cards";
			this->useCardsButton->UseVisualStyleBackColor = true;
			this->useCardsButton->Visible = false;
			this->useCardsButton->Click += gcnew System::EventHandler(this, &UI::useCardsButton_Click);
			// 
			// cardsValueTextBox
			// 
			this->cardsValueTextBox->Location = System::Drawing::Point(118, 465);
			this->cardsValueTextBox->Name = L"cardsValueTextBox";
			this->cardsValueTextBox->ReadOnly = true;
			this->cardsValueTextBox->Size = System::Drawing::Size(42, 20);
			this->cardsValueTextBox->TabIndex = 25;
			this->cardsValueTextBox->Text = L"0";
			this->cardsValueTextBox->Visible = false;
			// 
			// cardsValueLabel
			// 
			this->cardsValueLabel->AutoSize = true;
			this->cardsValueLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cardsValueLabel->Location = System::Drawing::Point(3, 465);
			this->cardsValueLabel->Name = L"cardsValueLabel";
			this->cardsValueLabel->Size = System::Drawing::Size(104, 20);
			this->cardsValueLabel->TabIndex = 24;
			this->cardsValueLabel->Text = L"Cards Value: ";
			this->cardsValueLabel->Visible = false;
			// 
			// artilleryCardTextBox
			// 
			this->artilleryCardTextBox->Location = System::Drawing::Point(118, 445);
			this->artilleryCardTextBox->Name = L"artilleryCardTextBox";
			this->artilleryCardTextBox->ReadOnly = true;
			this->artilleryCardTextBox->Size = System::Drawing::Size(14, 20);
			this->artilleryCardTextBox->TabIndex = 23;
			this->artilleryCardTextBox->Text = L"0";
			this->artilleryCardTextBox->Visible = false;
			// 
			// cavalryCardTextBox
			// 
			this->cavalryCardTextBox->Location = System::Drawing::Point(118, 425);
			this->cavalryCardTextBox->Name = L"cavalryCardTextBox";
			this->cavalryCardTextBox->ReadOnly = true;
			this->cavalryCardTextBox->Size = System::Drawing::Size(14, 20);
			this->cavalryCardTextBox->TabIndex = 22;
			this->cavalryCardTextBox->Text = L"0";
			this->cavalryCardTextBox->Visible = false;
			// 
			// infantryCardTextBox
			// 
			this->infantryCardTextBox->Location = System::Drawing::Point(118, 405);
			this->infantryCardTextBox->Name = L"infantryCardTextBox";
			this->infantryCardTextBox->ReadOnly = true;
			this->infantryCardTextBox->Size = System::Drawing::Size(14, 20);
			this->infantryCardTextBox->TabIndex = 21;
			this->infantryCardTextBox->Text = L"0";
			this->infantryCardTextBox->Visible = false;
			// 
			// artilleryCardLabel
			// 
			this->artilleryCardLabel->AutoSize = true;
			this->artilleryCardLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->artilleryCardLabel->Location = System::Drawing::Point(3, 445);
			this->artilleryCardLabel->Name = L"artilleryCardLabel";
			this->artilleryCardLabel->Size = System::Drawing::Size(106, 20);
			this->artilleryCardLabel->TabIndex = 20;
			this->artilleryCardLabel->Text = L"Artillery Card: ";
			this->artilleryCardLabel->Visible = false;
			// 
			// cavalryCardLabel
			// 
			this->cavalryCardLabel->AutoSize = true;
			this->cavalryCardLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cavalryCardLabel->Location = System::Drawing::Point(3, 425);
			this->cavalryCardLabel->Name = L"cavalryCardLabel";
			this->cavalryCardLabel->Size = System::Drawing::Size(106, 20);
			this->cavalryCardLabel->TabIndex = 19;
			this->cavalryCardLabel->Text = L"Cavalry Card: ";
			this->cavalryCardLabel->Visible = false;
			// 
			// infantryCardLabel
			// 
			this->infantryCardLabel->AutoSize = true;
			this->infantryCardLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->infantryCardLabel->Location = System::Drawing::Point(3, 405);
			this->infantryCardLabel->Name = L"infantryCardLabel";
			this->infantryCardLabel->Size = System::Drawing::Size(109, 20);
			this->infantryCardLabel->TabIndex = 18;
			this->infantryCardLabel->Text = L"Infantry Card: ";
			this->infantryCardLabel->Visible = false;
			// 
			// fortifyButton
			// 
			this->fortifyButton->Location = System::Drawing::Point(7, 338);
			this->fortifyButton->Name = L"fortifyButton";
			this->fortifyButton->Size = System::Drawing::Size(173, 29);
			this->fortifyButton->TabIndex = 17;
			this->fortifyButton->Text = L"Fortify!";
			this->fortifyButton->UseVisualStyleBackColor = true;
			this->fortifyButton->Click += gcnew System::EventHandler(this, &UI::fortifyButton_Click);
			// 
			// playerNameTextBox
			// 
			this->playerNameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->playerNameTextBox->Location = System::Drawing::Point(3, 3);
			this->playerNameTextBox->Name = L"playerNameTextBox";
			this->playerNameTextBox->Size = System::Drawing::Size(277, 31);
			this->playerNameTextBox->TabIndex = 16;
			this->playerNameTextBox->TextChanged += gcnew System::EventHandler(this, &UI::playerNameTextBox_TextChanged);
			// 
			// finishFortificationPhaseButton
			// 
			this->finishFortificationPhaseButton->Location = System::Drawing::Point(7, 373);
			this->finishFortificationPhaseButton->Name = L"finishFortificationPhaseButton";
			this->finishFortificationPhaseButton->Size = System::Drawing::Size(264, 29);
			this->finishFortificationPhaseButton->TabIndex = 15;
			this->finishFortificationPhaseButton->Text = L"Finish Fortification Phase";
			this->finishFortificationPhaseButton->UseVisualStyleBackColor = true;
			this->finishFortificationPhaseButton->Click += gcnew System::EventHandler(this, &UI::finishFortificationPhase_Click);
			// 
			// fortifyArmyComboBox
			// 
			this->fortifyArmyComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->fortifyArmyComboBox->FormattingEnabled = true;
			this->fortifyArmyComboBox->Location = System::Drawing::Point(186, 311);
			this->fortifyArmyComboBox->Name = L"fortifyArmyComboBox";
			this->fortifyArmyComboBox->Size = System::Drawing::Size(85, 21);
			this->fortifyArmyComboBox->TabIndex = 14;
			// 
			// fortifyDestinationTerritoryComboBox
			// 
			this->fortifyDestinationTerritoryComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->fortifyDestinationTerritoryComboBox->FormattingEnabled = true;
			this->fortifyDestinationTerritoryComboBox->Location = System::Drawing::Point(7, 311);
			this->fortifyDestinationTerritoryComboBox->Name = L"fortifyDestinationTerritoryComboBox";
			this->fortifyDestinationTerritoryComboBox->Size = System::Drawing::Size(173, 21);
			this->fortifyDestinationTerritoryComboBox->TabIndex = 13;
			// 
			// fortifySourceTerritoryComboBox
			// 
			this->fortifySourceTerritoryComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->fortifySourceTerritoryComboBox->FormattingEnabled = true;
			this->fortifySourceTerritoryComboBox->Location = System::Drawing::Point(7, 284);
			this->fortifySourceTerritoryComboBox->Name = L"fortifySourceTerritoryComboBox";
			this->fortifySourceTerritoryComboBox->Size = System::Drawing::Size(173, 21);
			this->fortifySourceTerritoryComboBox->TabIndex = 12;
			this->fortifySourceTerritoryComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::fortifySourceTerritoryComboBox_SelectedIndexChanged);
			// 
			// fortifyLabel
			// 
			this->fortifyLabel->AutoSize = true;
			this->fortifyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fortifyLabel->Location = System::Drawing::Point(3, 261);
			this->fortifyLabel->Name = L"fortifyLabel";
			this->fortifyLabel->Size = System::Drawing::Size(57, 20);
			this->fortifyLabel->TabIndex = 11;
			this->fortifyLabel->Text = L"Fortify:";
			// 
			// finishAttackingPhaseButton
			// 
			this->finishAttackingPhaseButton->Location = System::Drawing::Point(7, 229);
			this->finishAttackingPhaseButton->Name = L"finishAttackingPhaseButton";
			this->finishAttackingPhaseButton->Size = System::Drawing::Size(264, 29);
			this->finishAttackingPhaseButton->TabIndex = 10;
			this->finishAttackingPhaseButton->Text = L"Finish Attacking Phase";
			this->finishAttackingPhaseButton->UseVisualStyleBackColor = true;
			this->finishAttackingPhaseButton->Click += gcnew System::EventHandler(this, &UI::finishAttackingPhaseButton_Click);
			// 
			// attackButton
			// 
			this->attackButton->Location = System::Drawing::Point(7, 194);
			this->attackButton->Name = L"attackButton";
			this->attackButton->Size = System::Drawing::Size(173, 29);
			this->attackButton->TabIndex = 9;
			this->attackButton->Text = L"Attack!";
			this->attackButton->UseVisualStyleBackColor = true;
			this->attackButton->Click += gcnew System::EventHandler(this, &UI::attackButton_Click);
			// 
			// attackArmyCombobox
			// 
			this->attackArmyCombobox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->attackArmyCombobox->FormattingEnabled = true;
			this->attackArmyCombobox->Location = System::Drawing::Point(186, 164);
			this->attackArmyCombobox->Name = L"attackArmyCombobox";
			this->attackArmyCombobox->Size = System::Drawing::Size(85, 21);
			this->attackArmyCombobox->TabIndex = 8;
			// 
			// attackEnemyTerritoryCombobox
			// 
			this->attackEnemyTerritoryCombobox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->attackEnemyTerritoryCombobox->FormattingEnabled = true;
			this->attackEnemyTerritoryCombobox->Location = System::Drawing::Point(7, 164);
			this->attackEnemyTerritoryCombobox->Name = L"attackEnemyTerritoryCombobox";
			this->attackEnemyTerritoryCombobox->Size = System::Drawing::Size(173, 21);
			this->attackEnemyTerritoryCombobox->TabIndex = 7;
			// 
			// attackPlayerTerritoryCombobox
			// 
			this->attackPlayerTerritoryCombobox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->attackPlayerTerritoryCombobox->FormattingEnabled = true;
			this->attackPlayerTerritoryCombobox->Location = System::Drawing::Point(7, 137);
			this->attackPlayerTerritoryCombobox->Name = L"attackPlayerTerritoryCombobox";
			this->attackPlayerTerritoryCombobox->Size = System::Drawing::Size(173, 21);
			this->attackPlayerTerritoryCombobox->TabIndex = 6;
			this->attackPlayerTerritoryCombobox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::attackPlayerTerritoryCombobox_SelectedIndexChanged);
			// 
			// attackLabel
			// 
			this->attackLabel->AutoSize = true;
			this->attackLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->attackLabel->Location = System::Drawing::Point(3, 114);
			this->attackLabel->Name = L"attackLabel";
			this->attackLabel->Size = System::Drawing::Size(59, 20);
			this->attackLabel->TabIndex = 5;
			this->attackLabel->Text = L"Attack:";
			// 
			// finishReinforceButton
			// 
			this->finishReinforceButton->Location = System::Drawing::Point(7, 82);
			this->finishReinforceButton->Name = L"finishReinforceButton";
			this->finishReinforceButton->Size = System::Drawing::Size(264, 29);
			this->finishReinforceButton->TabIndex = 4;
			this->finishReinforceButton->Text = L"Finish Reinforcements Phase";
			this->finishReinforceButton->UseVisualStyleBackColor = true;
			this->finishReinforceButton->Click += gcnew System::EventHandler(this, &UI::finishReinforceButton_Click);
			// 
			// reinforceArmyComboBox
			// 
			this->reinforceArmyComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->reinforceArmyComboBox->FormattingEnabled = true;
			this->reinforceArmyComboBox->Location = System::Drawing::Point(186, 55);
			this->reinforceArmyComboBox->Name = L"reinforceArmyComboBox";
			this->reinforceArmyComboBox->Size = System::Drawing::Size(85, 21);
			this->reinforceArmyComboBox->TabIndex = 3;
			this->reinforceArmyComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::reinforceArmyComboBox_SelectedIndexChanged);
			// 
			// reinforceTerritoryComboBox
			// 
			this->reinforceTerritoryComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->reinforceTerritoryComboBox->FormattingEnabled = true;
			this->reinforceTerritoryComboBox->Location = System::Drawing::Point(7, 55);
			this->reinforceTerritoryComboBox->Name = L"reinforceTerritoryComboBox";
			this->reinforceTerritoryComboBox->Size = System::Drawing::Size(173, 21);
			this->reinforceTerritoryComboBox->TabIndex = 2;
			this->reinforceTerritoryComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::reinforceTerritoryComboBox_SelectedIndexChanged);
			// 
			// reinforceLabel
			// 
			this->reinforceLabel->AutoSize = true;
			this->reinforceLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reinforceLabel->Location = System::Drawing::Point(3, 37);
			this->reinforceLabel->Name = L"reinforceLabel";
			this->reinforceLabel->Size = System::Drawing::Size(82, 20);
			this->reinforceLabel->TabIndex = 0;
			this->reinforceLabel->Text = L"Reinforce:";
			// 
			// continentValuesListBox
			// 
			this->continentValuesListBox->FormattingEnabled = true;
			this->continentValuesListBox->Location = System::Drawing::Point(302, 719);
			this->continentValuesListBox->Name = L"continentValuesListBox";
			this->continentValuesListBox->Size = System::Drawing::Size(286, 30);
			this->continentValuesListBox->TabIndex = 18;
			this->continentValuesListBox->Visible = false;
			// 
			// logTextBox
			// 
			this->logTextBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->logTextBox->Location = System::Drawing::Point(1008, 23);
			this->logTextBox->MaxLength = 999999999;
			this->logTextBox->Multiline = true;
			this->logTextBox->Name = L"logTextBox";
			this->logTextBox->ReadOnly = true;
			this->logTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->logTextBox->Size = System::Drawing::Size(313, 696);
			this->logTextBox->TabIndex = 37;
			this->logTextBox->Visible = false;
			// 
			// UI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1334, 758);
			this->Controls->Add(this->logTextBox);
			this->Controls->Add(this->continentValuesListBox);
			this->Controls->Add(this->gamePanel);
			this->Controls->Add(this->numberOfAIComboBox);
			this->Controls->Add(this->numberOfAIPlayersLabel);
			this->Controls->Add(this->mapPictureBox);
			this->Controls->Add(this->saveErrorMessage);
			this->Controls->Add(this->numberOfPlayerComboBox);
			this->Controls->Add(this->numberOfPlayersLabel);
			this->Controls->Add(this->saveMapAndPlayButton);
			this->Controls->Add(this->borderApplyChangesButton);
			this->Controls->Add(this->bordersCheckList);
			this->Controls->Add(this->territoryOkEditButton);
			this->Controls->Add(this->continentOkEditButton);
			this->Controls->Add(this->territoryEditTextBox);
			this->Controls->Add(this->territoryEditNameLabel);
			this->Controls->Add(this->territoryEditButton);
			this->Controls->Add(this->territoryDeleteButton);
			this->Controls->Add(this->territoryAddButton);
			this->Controls->Add(this->territoriesComboBox);
			this->Controls->Add(this->continentEditTextBox);
			this->Controls->Add(this->continentNameLabel);
			this->Controls->Add(this->continentEditButton);
			this->Controls->Add(this->deleteContinentButton);
			this->Controls->Add(this->addContinentButton);
			this->Controls->Add(this->continentsComboBox);
			this->Controls->Add(this->bordersLabel);
			this->Controls->Add(this->territoriesLabel);
			this->Controls->Add(this->continentsLabel);
			this->Controls->Add(this->yesButton);
			this->Controls->Add(this->mapNameTextBox);
			this->Controls->Add(this->enterMapNameLabel);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->createButton);
			this->Controls->Add(this->loadButton);
			this->Name = L"UI";
			this->Text = L"RISK - Modern Warfare";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mapPictureBox))->EndInit();
			this->gamePanel->ResumeLayout(false);
			this->gamePanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void loadButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void createButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void yesButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void saveMapAndPlayButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void continentsComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void territoriesComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void bordersCheckList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void addContinentButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void territoryAddButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void continentEditButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void territoryEditButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void continentOkEditButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void territoryOkEditButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void deleteContinentButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void territoryDeleteButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void borderApplyChangesButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
		private: void UI::newTurn(int);
		private: System::Void playerNameTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void reinforceTerritoryComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void reinforceArmyComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void finishReinforceButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void attackPlayerTerritoryCombobox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void attackButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void finishAttackingPhaseButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void fortifySourceTerritoryComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		private: System::Void finishFortificationPhase_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void fortifyButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void useCardsButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void showStatsButton_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void saveExitButton_Click(System::Object^  sender, System::EventArgs^  e);
};
}
#endif