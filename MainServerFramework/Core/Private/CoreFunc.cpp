#include "CoreDefines.h"
#include "CoreFunc.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <cstring>
#include <errno.h>
#endif

namespace Core
{
    uint64 CoreFunc::CreateCurrentTime()
    {
        using namespace std::chrono;
        auto now = system_clock::now();  // UTC 기준 (또는 localtime 변환 가능)
        auto now_sec = time_point_cast<seconds>(now);
        return  now_sec.time_since_epoch().count();  // 초 단위
    }

    String CoreFunc::FormatTimeFromTime(uint64 secondsSinceEpoch)
    {
        std::time_t raw = static_cast<std::time_t>(secondsSinceEpoch);
        std::tm timeinfo;

#if defined(_WIN32)
        localtime_s(&timeinfo, &raw);
#else
        localtime_r(&raw, &timeinfo);
#endif
        static constexpr uint64 buffer_size{ 32 };
        static byte buffer[buffer_size]{};

        std::strftime(&buffer[0], buffer_size, "%Y-%m-%d %H:%M:%S", &timeinfo);
        String str(buffer);
        ClearMemory(buffer, buffer_size);
        return buffer;
    }

    void CoreFunc::OutSystemErrorMsg(const std::exception& ex, const char* file, int line, const char* function) {
        std::cout << MakeSystemErrorMsg(ex, file, line, function) << "\n";
    }

    String CoreFunc::MakeSystemErrorMsg(const std::exception& ex, const char* file, int line, const char* function)
    {
        std::ostringstream oss;

        oss << "[Exception] " << ex.what() << "\n"
            << "[Location] " << file << ":" << line << " in " << function;

#ifdef _WIN32
        DWORD errCode = ::GetLastError();
        if (errCode != 0) {
            LPVOID lpMsgBuf = nullptr;
            DWORD len = ::FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                errCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPSTR>(&lpMsgBuf),
                0, nullptr
            );

            if (len && lpMsgBuf) {
                oss << "\n[SystemError] Code=" << errCode
                    << ", Message=" << static_cast<const char*>(lpMsgBuf);
                ::LocalFree(lpMsgBuf);
            }
            else {
                oss << "\n[SystemError] Code=" << errCode
                    << ", Message=Unknown Windows error.";
            }
        }
#else
        int errCode = errno;
        if (errCode != 0) {
            oss << "\n[SystemError] Code=" << errCode
                << ", Message=" << std::strerror(errCode);
        }
#endif

        return String(oss.str());
    }
}