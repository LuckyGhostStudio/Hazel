#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <utility>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hazel/Core/Log.h"

#include "Hazel/Debug/Instrumentor.h"

#ifdef HZ_PLATFORM_WINDOWS	//windows平台
	#include <Windows.h>
#endif