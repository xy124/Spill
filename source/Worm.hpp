//Yes also in this games are worms on screen :P:P:P
#ifndef _WORM_HPP_
#define _WORM_HPP_

#include <string>
#include "PhysicalObject.hpp"
#include "Sprite.hpp"
#include <SDL.h>
#include "Logfile.hpp"
#include "consts.hpp"
#include "Game.hpp"
#include "Settings.hpp"

#include "Block.hpp"

#include "items/Item.hpp"

#include <list>


class CGame;



class CWorm : public CPhysicalObject {
	public:
	//FIXME use WormColors!
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
		float m_Energy;//energy as float for blocks that might steal energy per second.
		int m_Money;
		int m_Points;		
		bool m_Alive;
		bool m_isWalking;
		bool m_bJumpKeyLock;
		bool m_bBuildKeyLock;
		bool m_bOrientation;

		bool m_bIsVisible;

		S_WormSettings * m_pSettings;

		std::string getWormColorString();

		CSprite * m_pWormSprite;
		float m_fAnimphase;
		void ProcessMining();
		void ProcessMoving();
		void ProcessAnim();
		void ProcessNextItemKey();
		void ProcessUseItemKey();
		void ProcessPickDropItem();

	public:
		CWorm(CGame *pGame);
		void init(int WormID);
		void init(int WormID, float X, float Y);
		void init(int WormID, int TeamID, float X, float Y, WORMCOLORS WC);
		void init(int WormID, WORMCOLORS WC);
		void render();
		void update();
		void reset();
		bool isAlive();
		void ProcessView();
		~CWorm();

		std::list<CBlockKoord> m_BuiltBlocks;

		std::list<CItem*> m_pItems;
		std::list<CItem*>::iterator m_SelectedpItem;

		void setViewPort(int Viewport) {
			m_ViewPort = Viewport;
		}

		int getTeamID()
		{
			return m_TeamID;
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

		float getEnergy()
		{
			return m_Energy;
		}

		void setEnergy(float Energy)
		{
			m_Energy = Energy;
		}

		std::string getName()
		{
			return g_pSettings->getName(m_WormID);
		}

		void setName(std::string Name)
		{
			g_pSettings->setName(m_WormID, Name);
		}

		void changeEnergyBy(float v) {
			m_Energy += v;
		}

		void changePointsBy(int v) {
			m_Points += v;
		}

		void changeMoneyBy(int v) {
			m_Money += v;
		}

		void setVisibility(bool isVisible) {
			m_bIsVisible = isVisible;
		}

		int getViewPortID() {
			return m_ViewPort;
		}

		bool getOrientation() {
			return m_bOrientation;
		}

		
};

#endif
