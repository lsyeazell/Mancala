#pragma once
#include "wx/wx.h"

class cMain : public wxFrame 
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = 3;
	int nFieldHeight = 5;
	int x = 0;//to be changed
	int y = 0;//to be changed
	wxButton** btn;

	//void OnP1ButtonClicked(wxCommandEvent& evt);
	//void OnP2ButtonClicked(wxCommandEvent& evt);
	void display();
	void On3ButtonClicked(wxCommandEvent& evt);
	void On6ButtonClicked(wxCommandEvent& evt);
	void On9ButtonClicked(wxCommandEvent& evt);
	void On5ButtonClicked(wxCommandEvent& evt);
	void On8ButtonClicked(wxCommandEvent& evt);
	void On11ButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

