/*
 * IEmpty.hpp
 *
 *  Created on: 24.05.2011
 *      Author: Sebastian
 */

#ifndef IEMPTY_HPP_
#define IEMPTY_HPP_

#include "Item.hpp"

class CIEmpty: public CItem {
public:
	CIEmpty() {};
	void init();
	virtual ~CIEmpty() {};
};

#endif /* IEMPTY_HPP_ */
