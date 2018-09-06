#pragma once
#include "global.h"

#ifndef __HALCON__
#define __HALCON__

#ifdef _WIN64

#pragma comment(lib,"../third_party/lib/halcon/x64/halconcpp.lib")
#else
#pragma comment(lib,"../third_party/lib/halcon/x86/halconcpp.lib")
#endif

#endif

namespace MSerials
{




}