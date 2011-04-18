#ifndef _HIGHSCORELIST_HPP_
#define _HIGHSCORELIST_HPP_

#include <map>
#include <string>
#include "Worm.hpp"
#include "Singleton.hpp"
#include "Logfile.hpp"
#include <fstream>

class CHighscorelist : public TSingleton<CHighscorelist> {
	private:
		//				<Punkte, Name>
		std::multimap<int, std::string> m_map;
	public:		
		void SaveToFile(char * filename);
		void LoadFromFile(char * filename);
		void show(); //TODO!
		bool isHighscore(CWorm &worm);
		~CHighscorelist();
};

#endif
