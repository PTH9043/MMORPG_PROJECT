#pragma once

namespace Core
{
	class ServerCore{
	public:
		/// <summary>
		/// 서버를 시작하기 위해서는 반드시 호출해야 하는 함수
		/// </summary>
		static void InitServer();

		static void EndServer();
	};
}
