#include "Game.hpp"

using namespace std;

CGame::CGame(int AmountOfPlayers, int GameBoardWidth, int GameBoardHeight) {
	if (AmountOfPlayers > 4) {
		AmountOfPlayers = 4;
		CLogfile::get()->Textout("Can't Create so many Players, will create 4<br />");
	}

	for (int i=1; i<=AmountOfPlayers; i++) {//w�rmer auff�llen
		m_vWorms.push_back(new CWorm(i)); //MBE: evtl Teams
	}
	m_WormAmount = AmountOfPlayers;

	if (GameBoardWidth > MAXGAMEBOARDWIDTH) {
		m_GBWidth = MAXGAMEBOARDWIDTH;
		CLogfile::get()->Textout("Can't Create Gameboard with this WIDTH, will create Gameboard with width MAXGAMEBOARDWIDTH<br />");
	} else
		m_GBWidth = GameBoardSizeX;

	if (GameBoardHeight > MAXGAMEBOARDHEIGHT) {
		m_GBHeight = MAXGAMEBOARDHEIGHT;
		CLogfile::get()->Textout("Can't Create Gameboard with this HEIGHT, will create Gameboard with HEIGHT MAXGAMEBOARDHEIGHT<br />");
	} else
		m_GBHeight = GameBoardSizeY;

	g_pLogfile->Textout("Created Gameboard <br />");

	
	//map<CKoord, CBlock*>::iterator it; den brauch ma hier ncih
	pair<CBlockKoord, CBlock*> Gamefield;
	for (int x=0; x<m_GBWidth; x++) {	//Das gesamte Gameboard zu Luft machen
		for (int y=0; y<m_GBHeight; y++) {	
			CBlockKoord pos(x,y);						
			Gamefield = make_pair( pos, new CBlock(AIR));
			m_Gameboard.insert(Gamefield);
		}
	}
	g_pLogfile->Textout("Gameboard filled with NULL... <br />");
	//TODO: load World...
	//ok infact might be good to generate an sensfull empty World at first:
	//with a GROUND!
	map<CBlockKoord, CBlock*>::iterator it;
	for (int x = 0; x < m_GBWidth; x++) {
		CBlockKoord pos(x,2);
		it = m_Gameboard.find(pos);
		if (it != m_Gameboard.end()) {
			it->second->setBlockType(CBlock::NORMAL);
			it->second->setBuilderID(-1); //BuilderID -1 means its from levelbuilder!
			it->second->setTeamID(-1);
		}
	}
	//TODO: unsch�n die blocks hier zu laden
	//FIXME eigentlich kein pointer, wozu also das p im namen???
	CBlock::m_pBlockSprites.

	m_bIsRunning = true;

}

///////////////////////////////////////////////////////////////////////////////////
void CGame::run() {
	while (m_bIsRunning) {
		//Spielen!

		//tasten holen, screen flippen, Zeit holen:
		g_pFramework->Update();
		g_pTimer->Update();
		//W�rmer verschieben, abbremsen usw.
		CPhysics::doPhysics(this);
		//w�rmer zeichnen!
		vector<CWorm*>::iterator i;
		for (i = m_vWorms.begin(); i<=m_vWorms.end(); i++) {
			(*i)->update();
			(*i)->render();
		}

		renderGameboard();
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

vector<CWorm*> CGame::getVWorms() const
{
    return m_vWorms;
}

void CGame::setGBHeight(int m_GBHeight)
{
    this->m_GBHeight = m_GBHeight;
}

void CGame::setGBWidth(int m_GBWidth)
{
    this->m_GBWidth = m_GBWidth;
}

void CGame::setVWorms(vector<CWorm*> m_vWorms)
{
    this->m_vWorms = m_vWorms;
}

