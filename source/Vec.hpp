/*
 * CVec.hpp
 *
 *  Created on: 17.04.2011
 *      Author: Sebastian
 */

#ifndef _CVEC_HPP_
#define _CVEC_HPP_

#include "BlockKoord.hpp"
#include "FloatRect.hpp"
#include "consts.hpp"
//HINT: Vec DARF NICHT Block includieren da sonst kreisincludierung!


//class CBlockKoord; // forward declaration


class CVec { //real Koords in Pixels!
	public:
		float x;
		float y;
		CVec() { };
		CVec(const float X, const float Y) {
			x = X;
			y = Y;
		}
		CVec(const FloatRect &fr, bool getCenter = false) {
			if (getCenter) {
				x = fr.x+(fr.w/2.0f);
				y = fr.y+(fr.h/2.0f);
			} else {
				x = fr.x;
				y = fr.y;
			}
		}
		CVec(const CBlockKoord &blockKoord) {
			x = BLOCKSIZE*blockKoord.x;
			y = BLOCKSIZE*blockKoord.y;
		}


	//wozu ist nur das zweite const in der folgenden zeile???

		CVec operator + (const CVec &rhs) {//rhs=right hand side
			return CVec(x+rhs.x, y+rhs.y);
		}

		CVec operator - (const CVec &rhs) {
			return CVec(x-rhs.x, y-rhs.y);
		}

		CVec operator * (const float &rhs) {
			return CVec(x*rhs, y*rhs);
		}

		CVec operator / (const float &rhs) {
			return CVec(x/rhs, y/rhs);
		}

		void operator -= (const CVec &rhs) {
			x -= rhs.x;
			y -= rhs.y;
		}

		void operator += (const CVec &rhs) {
			x += rhs.x;
			y += rhs.y;
		}

		CBlockKoord toBlockKoord() {//MBE as reference????? see to blockrect too!!
			int xx = static_cast<int>(x/(BLOCKSIZE));
			int yy = static_cast<int>(y/(BLOCKSIZE));
			CBlockKoord result(xx, yy);
			return result;
		}

		float quad_abs() {//Quadrat des Betrags (da ich nciht weiß wie wurzeln geht)
			return (x*x+y*y);
		}

		FloatRect toBlockFloatRect() {
			FloatRect res;
			res.x = x;
			res.y = y;
			res.w = static_cast<float>(BLOCKSIZE);
			res.h = static_cast<float>(BLOCKSIZE);
			return res;
		}

		bool inRect(SDL_Rect &SR) {
			return ((SR.x < x) && (x < SR.x+SR.w) &&
					(SR.y < y) && (y < SR.y+SR.h)
					);
		}

		FloatRect toFloatRect(FloatRect old = FloatRect()) {//Warning: sets only x and y!
			old.x = x;
			old.y = y;
			return old;
		}


};

#endif
