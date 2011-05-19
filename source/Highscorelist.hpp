#ifndef _HIGHSCORELIST_HPP_
#define _HIGHSCORELIST_HPP_

#include <map>
#include <string>
#include "Worm.hpp"
#include "Singleton.hpp"
#include "Logfile.hpp"
#include <fstream>
#include "Menu/Menu.hpp"

class CHighscorelist : public TSingleton<CHighscorelist> {
	private:
		//				<Punkte, Name>
		std::multimap<int, std::string> m_map;
	public:		
		void SaveToFile(const char * sFilename);
		void LoadFromFile(const char * sFilename);
		void generateHighscoreMenu(CMenu * pMenu);
		bool isHighscore(CWorm &worm);
		~CHighscorelist();
};

#define g_pHighscorelist CHighscorelist::get()

#endif
