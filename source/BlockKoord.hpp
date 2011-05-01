#ifndef _BLOCKKOORD_HPP_
#define _BLOCKKOORD_HPP_

#include "FloatRect.hpp"
#include "consts.hpp"

class CBlockKoord {
	public:
		int x;
		int y;
		CBlockKoord() { };
		CBlockKoord(int X, int Y) {
			x = X;
			y = Y;
		}
		CBlockKoord (FloatRect &fr) {
			x = static_cast<int>(fr.x/BLOCKSIZE);
			y = static_cast<int>(fr.y/BLOCKSIZE);
		}
		~CBlockKoord() {};

		
//wozu ist nur das zweite const in der folgenden zeile???
		bool operator < (const CBlockKoord &rhs) const { //da immer gilt: left.operator<(right)
			if (y  == rhs.y)//wenn gleichen y-Wert entscheide nach xwert
				return (x < rhs.x);
			else //sonst entscheide nach y-Wert :) - danke Albert
				return (y < rhs.y);
		};

		bool operator == (const CBlockKoord &rhs) const {
			return ((x == rhs.x) && (y == rhs.y));
		};

		CBlockKoord operator + (const CBlockKoord &rhs) {//rhs=right hand side
			return CBlockKoord(x+rhs.x, y+rhs.y);
		};

		CBlockKoord operator - (const CBlockKoord &rhs) {
			return CBlockKoord(x-rhs.x, y-rhs.y);
		};

			
};

#endif
