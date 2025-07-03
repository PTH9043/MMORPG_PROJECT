#pragma once

#pragma warning (disable : 4251)
#pragma warning (disable : 6031)
#pragma warning (disable : 4150)
#pragma warning (disable : 4200)

#define USE_DEBUG 0
//#define USE_STOMP 0

/*
@ Date: 2023-12-30
@ Writer: ������
@ Explain
- ���� ����Ǵ� �ڵ��� ��Ȳ�� Window OS���� Linux OS���� �����Ѵ�.
*/

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#else
#include <stdlib.h>
#include <sys/mman.h>
#endif

/*
@ Date: 2023-12-26
@ Writer: ������
@ Explain
- DLL ���� �����ϴ� ��ũ��, EXPORT �϶��� Exprot �ƴ� �� �����ϰ� ���ش�.
*/
#ifdef CORE_EXPORTS
#define CORE_DLL   _declspec(dllexport)
#define MATHDLL_ENABLE
#else
#define CORE_DLL  _declspec(dllimport)
#endif

#define STATIC_CONCPP
#define _STOMP

#pragma comment (lib, "libcrypto")
#pragma comment (lib, "libssl")
#pragma comment(lib, "liblua54")

#include <iostream>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/lockfree_forward.hpp>
#include <shared_mutex>
#include <thread>
#include <string>
#include <array>
#include <concepts>
#include <chrono>
#include <mutex>
#include <random>
#include <queue>
#include <vector>
#include <fstream>
#include <regex>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <concurrent_priority_queue.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_unordered_set.h>
#include <concurrent_vector.h>


extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include "DefaultTypedef.h"
#include "CoreEnum.h"
#include "CoreConcept.h"
#include "CoreStruct.h"
#include "CoreMacro.h"
#include "CoreStatic.h"
#include "Memory.h"
#include "Allocator.h"
#include "ACoreGlobal.h"
#include "SmartPointer.h"
#include "CustomString.h"
#include "STLTypedef.h"
#include "IDGenerator.h"
#include "CoreFunc.h"

namespace Asio = boost::asio;
