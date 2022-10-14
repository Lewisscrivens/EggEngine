#pragma once

/* Include api. */
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <optional>
#include <codecvt>
#include <filesystem>
#include <shlobj.h>

/* Include common types. */
#include <string>
#include <sstream>
#include <ostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/* Windows include. */
#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
#endif