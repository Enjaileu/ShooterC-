#pragma once
#include "Ennemi.h"
#include "Boss.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Vague {
public:
	Vague(int id);
	void ParametrerVague(vector<Ennemi>& ennemis, Boss& boss);
	float chrono{ 0.0f };
private:
	CoteEcran GetCoteEcran(string s);
	vector<string> lignesFichier;
};