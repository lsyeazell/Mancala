//#include <iostream>
#include "cMain.h"
#include "wx/colour.h"
#include "GameBoard.h"
#include "MovePicker.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	//EVT_BUTTON(10000, OnP1ButtonClicked)
	//EVT_BUTTON(10014, OnP2ButtonClicked)
	EVT_BUTTON(10003, On3ButtonClicked)
	EVT_BUTTON(10006, On6ButtonClicked)
	EVT_BUTTON(10009, On9ButtonClicked)
	EVT_BUTTON(10005, On5ButtonClicked)
	EVT_BUTTON(10008, On8ButtonClicked)
	EVT_BUTTON(100011, On11ButtonClicked)


wxEND_EVENT_TABLE()

GameBoard* myBoard = new GameBoard(3, 3, true);
MovePicker* myPicker = new MovePicker(myBoard);

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "LASA Mancala", wxPoint(30,30), wxSize(800,600))
{	
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
	myBoard->printCurrentBoard();
	
	

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);
		}
	}

	btn[0]->SetLabel("Player 2");
	//btn[0]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnP1ButtonClicked, this);
	btn[14]->SetLabel("Player 1");
	//btn[14]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnP2ButtonClicked, this);
	btn[0]->Enable(false);
	btn[14]->Enable(false);


	btn[2]->SetBackgroundColour(wxColour(240, 240, 240));
	btn[12]->SetBackgroundColour(wxColour(240, 240, 240));
	btn[2]->Enable(false);
	btn[12]->Enable(false);

	btn[4]->SetBackgroundColour(wxColour(240, 240, 240));
	btn[7]->SetBackgroundColour(wxColour(240, 240, 240));
	btn[10]->SetBackgroundColour(wxColour(240, 240, 240));
	btn[4]->Enable(false);
	btn[7]->Enable(false);
	btn[10]->Enable(false);
	
	btn[0]->SetBackgroundColour(wxColour(230, 250, 25));
	btn[1]->SetBackgroundColour(wxColour(230, 250, 25));
	btn[3]->SetBackgroundColour(wxColour(230, 250, 25));
	btn[6]->SetBackgroundColour(wxColour(230, 250, 25));
	btn[9]->SetBackgroundColour(wxColour(230, 250, 25));
	btn[1]->SetLabel(std::to_string(myBoard->getPiecesInPocket(4)));
	btn[3]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On3ButtonClicked, this);
	btn[3]->SetLabel(std::to_string(myBoard->getPiecesInPocket(5)));
	btn[6]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On6ButtonClicked, this);
	btn[6]->SetLabel(std::to_string(myBoard->getPiecesInPocket(6)));
	btn[9]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On9ButtonClicked, this);
	btn[9]->SetLabel(std::to_string(myBoard->getPiecesInPocket(7)));
	btn[1]->Enable(false);
	//btn[3]->Enable(false);
	//btn[6]->Enable(false);
	//btn[9]->Enable(false);
	
	btn[5]->SetBackgroundColour(wxColour(25, 250, 230));
	btn[8]->SetBackgroundColour(wxColour(25, 250, 230));
	btn[11]->SetBackgroundColour(wxColour(25, 250, 230));
	btn[13]->SetBackgroundColour(wxColour(25, 250, 230));
	btn[14]->SetBackgroundColour(wxColour(25, 250, 230));
	btn[5]->SetLabel(std::to_string(myBoard->getPiecesInPocket(3)));
	btn[5]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On5ButtonClicked, this);
	btn[8]->SetLabel(std::to_string(myBoard->getPiecesInPocket(2)));
	btn[8]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On8ButtonClicked, this);
	btn[11]->SetLabel(std::to_string(myBoard->getPiecesInPocket(1)));
	btn[11]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::On11ButtonClicked, this);
	btn[13]->SetLabel(std::to_string(myBoard->getPiecesInPocket(0)));
	//btn[5]->Enable(false);
	//btn[8]->Enable(false);
	//btn[11]->Enable(false);
	btn[13]->Enable(false);

	this->SetSizer(grid);
	grid->Layout();
	wxMessageBox("Instructions:\n You are Player 1. Click on the pockets to make your move.");
	
}

cMain::~cMain()
{
	delete[]btn;
}

/*void cMain::OnP1ButtonClicked(wxCommandEvent& evt)
{
	btn[1]->SetLabel(std::to_string(++x));
	evt.Skip();
}

void cMain::OnP2ButtonClicked(wxCommandEvent& evt)
{
	btn[13]->SetLabel(std::to_string(y++));
	evt.Skip();
}
*/
void cMain::display() {
	btn[13]->SetLabel(std::to_string(myBoard->getPiecesInPocket(0)));
	btn[11]->SetLabel(std::to_string(myBoard->getPiecesInPocket(1)));
	btn[8]->SetLabel(std::to_string(myBoard->getPiecesInPocket(2)));
	btn[5]->SetLabel(std::to_string(myBoard->getPiecesInPocket(3)));

	btn[1]->SetLabel(std::to_string(myBoard->getPiecesInPocket(4)));
	btn[3]->SetLabel(std::to_string(myBoard->getPiecesInPocket(5)));
	btn[6]->SetLabel(std::to_string(myBoard->getPiecesInPocket(6)));
	btn[9]->SetLabel(std::to_string(myBoard->getPiecesInPocket(7)));
}

void cMain::On3ButtonClicked(wxCommandEvent& evt)
{
	myBoard->makeMove(5);
	display();

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}

void cMain::On6ButtonClicked(wxCommandEvent& evt)
{
	myBoard->makeMove(6);
	display();

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}

void cMain::On9ButtonClicked(wxCommandEvent& evt)
{
	myBoard->makeMove(7);
	display();

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}

void cMain::On5ButtonClicked(wxCommandEvent& evt)
{
	myBoard->makeMove(3);
	display();

	if ((myBoard->getCurrentTurn())) {
		wxMessageBox("Player 2 is going now");
		myBoard->makeMove(myPicker->chooseMove());
		display();
	}

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}
void cMain::On8ButtonClicked(wxCommandEvent& evt)
{
	
	myBoard->makeMove(2);
	display();

	if ((myBoard->getCurrentTurn())) {
		wxMessageBox("Player 2 is going now");
		myBoard->makeMove(myPicker->chooseMove());
		display();
	}

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}
void cMain::On11ButtonClicked(wxCommandEvent& evt)
{
	
	myBoard->makeMove(1);
	display();

	if ((myBoard->getCurrentTurn())) {
		wxMessageBox("Player 2 is going now");
		myBoard->makeMove(myPicker->chooseMove());
		display();
	}

	if (myBoard->gameOver()) {
		if (myBoard->getCurrentScore() > 0) {
			wxMessageBox("Game Over! You Win");
		}
		else {
			wxMessageBox("Game Over! You Lose");
		}
	}

	evt.Skip();
}