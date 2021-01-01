//#ifndef LOAD_H
//#define LOAD_H
//
//#include "Action.h"
//#include <fstream>
//#include <iostream>
//using namespace std;
//
//class Load : public Action
//{
//
//public:
//	Load(ApplicationManager* pApp);
//	Load(string name);
//
//	ifstream& getInFile();
//	void setInFile(string name);
//	virtual void ReadActionParameters();
//
//	//Execute action (code depends on action type)
//	virtual void Execute();
//
//	//To undo this action (code depends on action type)
//	virtual void Undo();
//
//	//To redo this action (code depends on action type)
//	virtual void Redo();
//
//	virtual ~Load();
//};
//
//#endif