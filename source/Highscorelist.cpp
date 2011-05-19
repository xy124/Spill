#include "Highscorelist.hpp"

#include "Menu/MenuSystem.hpp" //include menusystem for menuentryID's

#define HIGHSCORESIZE 15
//die besten 15 sind in der Highscoreliste aufgef�hrt

using namespace std;

void CHighscorelist::LoadFromFile(const char * sFilename) {
	ifstream Input(sFilename, ios::binary);
	if (Input == NULL) {
		CLogfile::get()->FunctionResult("CHighscorelist::LoadFromFile", L_OK, "could not open inputstream, Highscorelist is empty.");
		return;
	}
	Input.read((char *) &m_map, sizeof(multimap<int, string>));//hoffen wir mal dass das geht, weil multimaps ja je nach inhalt unterschiedlich gro� sein d�rften. notfalls muss man die multimap erst in nen array werfen und dann mit ner schleife wieder in die map werfen....
	Input.close();
}

void CHighscorelist::SaveToFile(const char * sFilename) {
	ofstream Output(sFilename, ios::binary);
	if (Output == NULL) {
		CLogfile::get()->FunctionResult("CHighscorelist::SaveToFile", L_FAIL, "could not open outputstream. Can't Save Hioghscore!");
		return;
	}
	Output.write((char *) &m_map, sizeof(multimap<int, string>));
	Output.close();
}

void CHighscorelist::generateHighscoreMenu(CMenu * pMenu) {
	//TODO: Sortieren!

	pMenu->init("Highscores");

	multimap<int, std::string>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
		char buffer[40];
		sprintf(buffer, "%s : %i", it->second.c_str(), it->first);

		pMenu->addItem(string(buffer), NULL, CMenu::BUTTON);
	}
	pMenu->addItem("back", ENTRY_BACKMAIN, CMenu::BUTTON);
	CLogfile::get()->FunctionResult("CHighscorelist::generate...", L_OK, "generates Highscorelist");
}

bool CHighscorelist::isHighscore(CWorm &worm) {
	int points = worm.getPoints();

	//get lowest points-item	
	multimap<int, string>::iterator i;
	int smallest = 10000; //TODO wieviele punkte gibts maximal...
	for (i = m_map.begin(); i!=m_map.end(); i++) {
		if (i->first < smallest) smallest = i->first;
	}

	i = m_map.find(smallest); //item mit dem kleinsten wert raussuchen

	if ((i->first < points) || (m_map.size() < HIGHSCORESIZE)) { //hinzuf�gen, evtl. nach namen Fragen		
		if (i->first < points) { //"i" rausl�schen
			m_map.erase(i);
		}
		m_map.insert(make_pair(points, worm.getName()));
		CLogfile::get()->Textout(RED, "Neuer Highscore!");
		return true;
	} else return false;
}

CHighscorelist::~CHighscorelist() {
	//Highscorelist wird gel�scht
	m_map.clear();
}

