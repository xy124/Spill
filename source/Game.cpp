#include "Game.hpp"

using namespace std;

CGame::CGame(int AmountOfPlayers, int GameBoardWidth, int GameBoardHeight) {
	g_pFramework->InitWorld(GameBoardWidth * BLOCKSIZE, GameBoardHeight * BLOCKSIZE, 16);

	if (AmountOfPlayers > 4) {
		AmountOfPlayers = 4;
		CLogfile::get()->Textout("Can't Create so many Players, will create 4<br />");
	}

	for (int i=1; i<=AmountOfPlayers; i++) {//w�rmer auff�llen
		CWorm* pWorm = new CWorm();
		pWorm->init(i, 40.0f, 40.0f, CWorm::WC_RED); //wir machen alle Würmer rot....
		m_vWorms.push_back(pWorm); //MBE: evtl Teams
	}
	m_WormAmount = AmountOfPlayers;

	if (GameBoardWidth > MAXGAMEBOARDWIDTH) {
		m_GBWidth = MAXGAMEBOARDWIDTH;
		CLogfile::get()->Textout("Can't Create Gameboard with this WIDTH, will create Gameboard with width MAXGAMEBOARDWIDTH<br />");
	} else
		m_GBWidth = GameBoardWidth;

	if (GameBoardHeight > MAXGAMEBOARDHEIGHT) {
		m_GBHeight = MAXGAMEBOARDHEIGHT;
		CLogfile::get()->Textout("Can't Create Gameboard with this HEIGHT, will create Gameboard with HEIGHT MAXGAMEBOARDHEIGHT<br />");
	} else
		m_GBHeight = GameBoardHeight;

	g_pLogfile->Textout("Created Gameboard <br />");

	
	//map<CKoord, CBlock*>::iterator it; den brauch ma hier ncih
	pair<CBlockKoord, CBlock*> Gamefield;
	for (int x=0; x<m_GBWidth; x++) {	//Das gesamte Gameboard zu Luft machen
		for (int y=0; y<m_GBHeight; y++) {	
			CBlockKoord pos(x,y);						
			Gamefield = make_pair( pos, new CBlock(CBlock::AIR));
			Gamefield.second->setBuilderID(NOBODY);
			Gamefield.second->setTeamID(NOBODY);
			m_Gameboard.insert(Gamefield);
		}
	}
	g_pLogfile->Textout("Gameboard filled with NULL... <br />");
	//TODO: load World...
	//ok infact might be good to generate an sensfull empty World at first:
	//with a GROUND!
	for (int x = 0; x < m_GBWidth; x++) {
		CBlockKoord pos(x,18);
		BuildBlock(pos, CBlock::NORMAL, NOBODY, NOBODY);
	}

	//build a wall
	for (int y = 0; y < m_GBHeight-5; y++) {
		CBlockKoord pos(22,y);
		BuildBlock(pos, CBlock::SHOOTING, NOBODY, NOBODY);
	}

	//build a single block
	CBlockKoord pos(14, 14);
	BuildBlock(pos, CBlock::JUMPBOARD, NOBODY, NOBODY);
	pos.x = 3;
	BuildBlock(pos, CBlock::JUMPBOARD, NOBODY, NOBODY);

	pos.x = 4;
	pos.y = 17;
	BuildBlock(pos, CBlock::INVISIBLE, NOBODY, NOBODY);

	//"Stairs"
	pos.x = 19;
	pos.y = 14;
	BuildBlock(pos, CBlock::JUMPBOARD, NOBODY, NOBODY);
	pos.x = 20;
	pos.y = 10;
	BuildBlock(pos, CBlock::JUMPBOARD, NOBODY, NOBODY);
	pos.x = 21;
	pos.y = 7;
	BuildBlock(pos, CBlock::JUMPBOARD, NOBODY, NOBODY);




	CBlock::InitBlockSprites();

	m_bIsRunning = true;
	g_pLogfile->Textout(RED, true, "End Of CGame::CGame");

}

///////////////////////////////////////////////////////////////////////////////////
void CGame::run() {
	while (m_bIsRunning) {
		//Play!
		g_pLogfile->fTextout(BLUE,"<br/> Lalala <br/>");


		float time;
		time = SDL_GetTicks();
		//nimmt unwesentliche Zeit von 1ms:
		//g_pFramework->Clear(); //Clear current surface
		g_pFramework->Update();//Update Timer and Framework!
		ProcessEvents();//react on escape for close...

		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section1: /%fms", time);



		time = SDL_GetTicks();
		//Move Worms, slow them down and so on...
		g_pPhysics->doPhysics();//schnell!!

		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section2: /%fms", time);

		time = SDL_GetTicks();
		//render gameboard before you render worms xD
		renderGameboard();
		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section3: /%fms", time);

		time = SDL_GetTicks();
		//Draw Worms and react on keys...
		vector<CWorm*>::iterator i;
		for (i = m_vWorms.begin(); i<m_vWorms.end(); i++) {
			(*i)->update();
			(*i)->render();
		}
		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section4: /%fms", time);

		time = SDL_GetTicks();
		//TODO: je nach spieler...
		i = m_vWorms.begin(); //hier für spieler 1
		(*i)->ProcessView();
		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section5: /%fms", time);
		time = SDL_GetTicks();

		g_pFramework->showDebugValue("Fasd: %f", (g_pTimer->getElapsed()) );

		g_pFramework->RenderDebugText();
		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section6: /%fms", time);
		time = SDL_GetTicks();

		g_pFramework->BlitView();
		time = SDL_GetTicks() - time;
		g_pLogfile->fTextout("<br />Section7: /%fms", time);

		g_pFramework->Flip();
	}
}
////////////////////////////////////////////////////////////////////////////////////

void CGame::renderGameboard() {
	map<CBlockKoord, CBlock*>::iterator it;
	for (it=m_Gameboard.begin() ; it!=m_Gameboard.end(); ++it) {//alle Bl�cke rendern!
		CBlockKoord pos = it->first;
		it->second->render(pos);
	}
}

void CGame::ProcessEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case (SDL_QUIT): {
				m_bIsRunning = false;
			} break;
			case (SDL_KEYDOWN): {
				switch (event.key.keysym.sym) {
					case (SDLK_ESCAPE): {
						m_bIsRunning = false;
					} break;
					default: //nothing
						break;
				} //switch event.key.keysym.sym
			} break;
		} //Switch event.type
	} //if
}

void CGame::quit() {
	//DeleteWorms
	//free Gameboard
	//free Blockimages!

	vector<CWorm*>::iterator wit;
	for (wit = m_vWorms.begin(); wit!=m_vWorms.end(); wit++) {
		if ((*wit)!=NULL) {
			delete ((*wit));
			(*wit) = NULL;
		}
	}
	m_vWorms.clear();

	map<CBlockKoord, CBlock*>::iterator mit;
	for (mit = m_Gameboard.begin(); mit != m_Gameboard.end(); ++mit) {
		if (mit->second != NULL) {
			delete (mit->second);
			mit->second = NULL;
		}
	}

	CBlock::FreeBlockSprites();
}

bool CGame::BuildBlock(CBlockKoord Where, CBlock::BlockType Type, int BuilderID, int TeamID) {
	map<CBlockKoord, CBlock*>::iterator it;
	it = m_Gameboard.find(Where);
	if (it != m_Gameboard.end()) {
		it->second->setBlockType(Type);
		it->second->setBuilderID(BuilderID);
		it->second->setTeamID(TeamID);
		return true;
	} else return false;
}

CGame::~CGame() {
	//nichts :P
	CLogfile::get()->Textout("Destroyed CGame </ br>");
}

int CGame::getGBHeight() const
{
    return m_GBHeight;
}

int CGame::getGBWidth() const
{
    return m_GBWidth;
}

void CGame::setGBHeight(int m_GBHeight)
{
    this->m_GBHeight = m_GBHeight;
}

void CGame::setGBWidth(int m_GBWidth)
{
    this->m_GBWidth = m_GBWidth;
}

