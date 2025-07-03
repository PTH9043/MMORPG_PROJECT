#include "CoreDefines.h"
#include "ACoreGlobal.h"
#include "ACoreObject.h"

namespace Core
{
	class ACoreGlobal {
	public:
		ACoreGlobal()
		{
			AMemoryAdiminstor::InitializMemoryAdiminstor();
		}
		~ACoreGlobal()
		{
			AMemoryAdiminstor::ReleaseMemoryAdiminstor();
		}
	};

	static std::unique_ptr<ACoreGlobal> Unique_Global;

	void ServerCore::InitServer()
	{
		Unique_Global = std::make_unique<ACoreGlobal>();
		ACoreObject::InitializeGlobalData();
	}

	void ServerCore::EndServer()
	{
		Unique_Global.reset();
	}
}
