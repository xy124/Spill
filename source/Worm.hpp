//Yes also in this games are worms on screen :P:P:P
#ifndef _WORM_HPP_
#define _WORM_HPP_

#include <string>
#include "PhysicalObject.hpp"
#include "Sprite.hpp"
#include <SDL.h>
#include "Logfile.hpp"
#include "consts.hpp"
#include "Collision.hpp"
#include "Game.hpp"

#include "Block.hpp"


class CGame;



class CWorm : public CPhysicalObject {
	public:
		enum WORMCOLORS {
				WC_RED,
				WC_BLUE,
				WC_GREEN,
				WC_YELLOW
		};
	private:
		CGame* m_pGame;

		int m_WormID;
		int m_ViewPort;
		WORMCOLORS m_Color;
		int m_TeamID;
		int m_Energy;
		int m_Money;
		int m_Points;		
		bool m_Alive;
		bool m_isWalking;
		bool m_bJumpKeyLock;
		bool m_bBuildKeyLock;
		bool m_bOrientation;
		S_Collision m_lastCollisionY;

		bool m_bNextBTypeKeyLock;
		CBlock::BlockType m_selectedBType;

		std::string m_Name;

		std::string getWormColorString();

		CSprite * m_pWormSprite;
		float m_fAnimphase;

		void ProcessMoving();
		void ProcessBuilding();
		void ProcessAnim();

	public:
		CWorm(CGame *pGame);
		void init(int WormID);
		void init(int WormID, float X, float Y);
		void init(int WormID, float X, float Y, WORMCOLORS WC);
		void init(int WormID, WORMCOLORS WC);
		void render();
		void update();
		void reset();
		bool isAlive();
		void ProcessView();
		~CWorm();

		void setViewPort(int Viewport) {
			m_ViewPort = Viewport;
		}

		int getWormID()
		{
			return m_WormID;
		}

		void setWormID(int WormID)
		{
			m_WormID = WormID;
		}

		WORMCOLORS getColor()
		{
			return m_Color;
		}

		void setColor(WORMCOLORS Color)
		{
			m_Color = Color;
		}

		int getPoints()
		{
			return m_Points;
		}

		void setPoints(int Points)
		{
			m_Points = Points;
		}

		int getMoney()
		{
			return m_Money;
		}

		void setMoney(int Money)
		{
			m_Money = Money;
		}

		int getEnergy()
		{
			return m_Energy;
		}

		void setEnergy(int Energy)
		{
			m_Energy = Energy;
		}

		std::string getName()
		{
			return m_Name;
		}

		void setName(std::string Name)
		{
			m_Name = Name;
		}


		void setName(bool Alive)
		{
			m_Alive = Alive;
		}


		S_Collision getLastCollisionY() const;
		void setLastCollisionY(S_Collision &m_lastCollisionY);

		
};

#endif
