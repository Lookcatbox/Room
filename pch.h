#ifndef PCH_H
#define PCH_H

#define VER_MAJOR 3
#define VER_MINOR 0
#define VER_RELEASE 2
#define VER_BUILD 6
#define VER_STRING "2.1.0"
#define VER_DESCRIPTION "NOIPÇ°ÌØ±ð°æ"

#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>

//#include "wchar.h"
#include <Windows.h>
#include <conio.h>
#include <sys\timeb.h>//GetTime()

#ifdef MSVC

#pragma comment(lib, "winmm.lib")//Sound()

#endif

using std::string;
using std::max;
using std::min;

#include "inter.h"
#include "lexicon.h"
#include "var.h"
#include "function.h"
#include "act.h"
#include "zone.h"

#endif
