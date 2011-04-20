#include "Worm.hpp"

using namespace std;

CWorm::CWorm() {
	m_pWormSprite = NULL;
}

void CWorm::init(int WormID) {
	init(WormID, 0, 0, WC_RED);
}

void CWorm::init(int WormID, float X, float Y) {
	init(WormID, X, Y, WC_RED);
}

void CWorm::init(int WormID, WORMCOLORS WC){
	init(WormID, 0, 0, WC);
}


void CWorm::init(int WormID, float X, float Y, WORMCOLORS WC) {
	m_WormID = WormID;
	setCanJump(false);
	m_Color = WC;
	m_Money = 0;
	m_Points = 0;
	m_Energy = MAXENERGY;
	setCanMove(true);
	
	m_Name = ""; //getName(); --> TODO!!! Abfrage per Eingabe vom User!!!!
	
	m_pWormSprite = new CSprite();
	//m_pWormSprite->Load(_DIRDATA_+"/christmaswormjustwalk.bmp", 21, 32, 17);
	//New animation: //braucht auch anpassung in Animate!
	m_pWormSprite->Load(_DIRDATA_+"/christmaswormjustwalk.bmp", 3 , 25, 18);
	m_pWormSprite->SetColorKey(255, 0, 255);
	m_fAnimphase = 0.0f;
	m_isWalking = false;

	FloatRect FR; //TODO: per operator!
	SDL_Rect sdlrect = m_pWormSprite->GetRect();
	FR.x = sdlrect.x;
	FR.y = sdlrect.y;
	FR.w = sdlrect.w;
	FR.h = sdlrect.h;
	setRect(FR);
	setDir(CVec(0,0));

	m_Alive = true;
	CLogfile::get()->fTextout("New Worm; ID:%i<br />",m_WormID);
}

void CWorm::reset() { //HINT: resettet nicht die Position
	setDir(CVec(0,0));
	m_Money = 0;
	m_Points = 0;
	m_Energy = MAXENERGY;
}

void CWorm::render() {
	CVec newWormPos = CVec(getRect());
	m_pWormSprite->SetPos( newWormPos );
	m_pWormSprite->Render(m_fAnimphase);
}

void CWorm::ProcessMoving() {//FIXME nicht alle W�rmer d�rfen die selben Tasten nutzen!!!
	CVec newDir(0,0);
	if (g_pFramework->KeyDown(SDLK_UP) && getCanJump()) { //Jump!
		setCanJump(false);
		
		newDir.y = -500.0f; //TODO Jumpfactor = const!!
	}

	//Left or Right!!
	if (g_pFramework->KeyDown(SDLK_LEFT) == true) {
		newDir.x = -300.0f;
	} else if (g_pFramework->KeyDown(SDLK_RIGHT) == true ) {
		newDir.x = +300.0f;
	}
	setDir(newDir);
}

void CWorm::ProcessBuilding() {
	//TODO!!+Processweapons!!! for attacks of othe blocks!

}

void CWorm::ProcessAnim() {
	//TODO! Nicht immer nur die selbe animation
	m_fAnimphase += 10.0f*g_pTimer->getElapsed();
	if (m_fAnimphase >= 3.0f)
		m_fAnimphase -= 3.0f;
	//g_pFramework->showDebugValue("WormAnimPhase: %f", m_fAnimphase);
}

CWorm::~CWorm() {
	if (m_pWormSprite != NULL) {
		delete (m_pWormSprite);
	}
	m_pWormSprite = NULL;
	CLogfile::get()->fTextout("Deleted Worm; ID:%i<br />",m_WormID);
}

string CWorm::getWormColorString() {
	string result;
	switch (m_Color) {
		case WC_RED:
			result = "red";
			break;
		case WC_BLUE:
			result = "blue";
			break;
		case WC_GREEN:
			result = "green";
			break;
		case WC_YELLOW:
			result = "yellow";
			break;
		default:
			result = "noColor!";
			CLogfile::get()->Textout("Couldn't get the Colorstring!<br />");			
			break;
	}
	return result;
}

void CWorm::update() {
	ProcessMoving();

	ProcessBuilding();

	ProcessAnim();

	//Physics happens in do physics!
}

bool CWorm::isAlive() {
	return m_Alive;
}
