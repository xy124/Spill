#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Block.hpp"
#include "Worm.hpp"
#include "BlockKoord.hpp"
#include "Physics.hpp"
#include <vector>
#include <map>
#include "Sprite.hpp"
#include "Logfile.hpp"

#define MAXGAMEBOARDWIDTH 500
#define MAXGAMEBOARDHEIGHT 50


class CGame
{
	private:
		int m_GBWidth;
		int m_GBHeight;

		vector<CWorm*> m_vWorms;
		int m_WormAmount;

		bool m_bIsRunning;

		void renderGameboard();

	public:
		map<CBlockKoord,CBlock*> m_Gameboard;
		CGame(int AmountOfPlayers, int GameBoardWidth, int GameBoardHeight);
		void save(const char *Filename);
		void load(const char *Filename);
		void run();
		void quit();
		~CGame();

		//Getters and Setters:
		int getGBHeight() const;
		int getGBWidth() const;
		vector<CWorm*> getVWorms() const;
		void setGBHeight(int m_GBHeight);
		void setGBWidth(int m_GBWidth);
		void setVWorms(vector<CWorm*> m_vWorms);
};

#endif
