#pragma once

SPACE_BEGIN(Core)

class ILogEntity {
public:
	ILogEntity();
	virtual ~ILogEntity();

	virtual String GetTypeName() const = 0;
	virtual String ToContext() const = 0;
};

SPACE_END
