#pragma once 

namespace Core
{
	class CoreStatic {
	public:
		static constexpr int32 MAX_THREAD_NUM = 16;
		static thread_local int32 ThreadID_RW;

		constexpr static unsigned int PACKETHEAD_SIZE{ sizeof(FPacketHead) };
	};

}