#pragma once 


using int8 = signed char;
using byte = char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

using tchar = wchar_t;

template <class T, int64 size>
using ARRAY = std::array<T, size>;

template<class T>
using ATOMIC = std::atomic<T>;

template<class Type, class Other>
using CONUNORMAP = concurrency::concurrent_unordered_map<Type, Other>;

template<class Type>
using CONUNORSET = concurrency::concurrent_unordered_set<Type>;

template<class Type>
using CONVECTOR = concurrency::concurrent_vector<Type>;

template<class Type>
using CONQUEUE = concurrency::concurrent_queue<Type>;

template<class Type>
using CONPRIORITYQUEUE = concurrency::concurrent_priority_queue<Type>;

using Atomic_long = std::atomic_long;

using Atomic_int64 = std::atomic_llong;

using Atomic_uint64 = std::atomic_ullong;

using Atomic_int32 = std::atomic_int;

using Atomic_uint32 = std::atomic_uint;

using Atomic_bool = std::atomic_bool;

using THREADFUNC = std::function<void(void*)>;

using IOContext = boost::asio::io_context;

using IOService = boost::asio::io_service;

using TIMEPOINT = std::chrono::system_clock::time_point;

using TCPACCEPTOR = boost::asio::ip::tcp::acceptor;

using TCPSOCKET = boost::asio::ip::tcp::socket;

using UDPSOCKET = boost::asio::ip::udp::socket;

using SPIN_LOCK = std::shared_mutex;

using SHARED_SPIN_LOCK = std::lock_guard<SPIN_LOCK>;

using LOCK = std::mutex;

using SHARED_LOCK = std::lock_guard<LOCK>;

#define ALIGN(num) alignas(num)