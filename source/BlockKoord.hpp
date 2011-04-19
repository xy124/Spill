#ifndef _BLOCKKOORD_HPP_
#define _BLOCKKOORD_HPP_

#include "FloatRect.hpp"




class CBlockKoord {
	public:
		int x;
		int y;
		CBlockKoord() { };
		CBlockKoord(int X, int Y) {
			x = X;
			y = Y;
		}
		CBlockKoord (FloatRect &FR) {
			x = static_cast<int>(FR.x);
			y = static_cast<int>(FR.y);
		}
		~CBlockKoord() {};

		
//wozu ist nur das zweite const in der folgenden zeile???
		bool operator < (const CBlockKoord &right) const { //da immer gilt: left.operator<(right)
			if (y  == right.y)//wenn gleichen y-Wert entscheide nach xwert
				return (x < right.x);
			else //sonst entscheide nach y-Wert :) - danke Albert
				return (y < right.y);
		};

		CBlockKoord operator + (const CBlockKoord &rhs) {//rhs=right hand side
			return CBlockKoord(x+rhs.x, y+rhs.y);
		};

		CBlockKoord operator - (const CBlockKoord &rhs) {
			return CBlockKoord(x-rhs.x, y-rhs.y);
		};

		/*CVec toVec() {
			CVec result(CBlock::BlockSize*x, CBlock::BlockSize*y);
			return (result);
		};*/ //Circledeclaration not allowed in c++, use instead constructor of CVec(CBlockKoord)
			
};

#endif
