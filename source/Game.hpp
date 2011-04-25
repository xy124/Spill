#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Block.hpp"
#include "Worm.hpp"
#include "BlockKoord.hpp"
#include <vector>
#include <map>
#include "Sprite.hpp"
#include "Logfile.hpp"

#include "Physics.hpp"

#include "consts.hpp"

#include "CBackGround.hpp"

#include <vector>

class CWorm;
class CPhysics;

class CGame
{
	private:
		//in Blocks:
		int m_GBWidth;
		int m_GBHeight;


		int m_WormAmount;

		bool m_bIsRunning;

		void renderGameboard();

		void ProcessEvents();

		CBackGround * m_pBackGround;

	public:

		std::vector<CWorm*> m_vWorms;
		std::map<CBlockKoord,CBlock*> m_Gameboard;
		CGame(int AmountOfPlayers, int GameBoardWidth, int GameBoardHeight);
		void save(const char *sFilename);
		void load(const char *sFilename);
		void run();
		void quit();
		~CGame();

		CBlock* getBlock(CBlockKoord Where);
		bool BuildBlock(CBlockKoord Where, CBlock::BlockType Type, int BuilderID, int TeamID);

		//Getters and Setters:
		int getGBHeight() const;
		int getGBWidth() const;
		void setGBHeight(int m_GBHeight);
		void setGBWidth(int m_GBWidth);
};

#endif
