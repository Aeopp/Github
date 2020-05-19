#pragma once

#include <Windows.h>
#include <utility>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>K

#include "Macro.h"
#include "../resource.h"
#include "Types.h"
#include "Flag.h"
using namespace std;

template<typename T>
static void Safe_Delete_VecList(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE((*iter));
	}
	p.clear();
};

template<typename T>
static void Safe_Release_VecList(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_RELEASE((*iter));
	}
	p.clear();
};





