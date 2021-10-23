#pragma once
#ifndef _ORION_H_
#define _ORION_H_

#include "yelp.h"

#ifdef __cplusplus

namespace sk {

	template<typename T>
	void swap (T* a, T* b) {
		T c = *a;
		 *a = *b;
		 *b =  c;
	}

};

#endif

#endif /*_ORION_H_*/
