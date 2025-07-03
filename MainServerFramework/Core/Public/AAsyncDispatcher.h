#pragma once
#include "ACoreUnit.h"

SPACE_BEGIN(Core)

class AAsyncDispatcher : public ACoreUnit<AAsyncDispatcher> {
public:
	AAsyncDispatcher(int32 dataSize, byte* data);
	virtual ~AAsyncDispatcher();

	DECLARE_GET_TYPENAME(AAsyncDispatcher)
	virtual String ToContext() const override;
public:
	template<class T>
	void CombineProto(IN BUFFER& buffer, IN FPacketHead& packetHead, const T& data, int32 tag)
	{
		data.SerializePartialToArray((void*)&buffer[0], static_cast<int>(data.ByteSizeLong()));
		packetHead.PacketSize = static_cast<short>(data.ByteSizeLong());
		packetHead.PacketType = static_cast<short>(tag);
	}

	template<class T> 
	T* CastingData() { return reinterpret_cast<T*>(_DataContainer.data()); }
private:
	int32							_DataSize;
	VECTOR<byte>		_DataContainer;
};

SPACE_END