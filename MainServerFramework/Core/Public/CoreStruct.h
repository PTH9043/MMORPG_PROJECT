#pragma once 

struct FPacketHead
{
	int16		PacketSize;
	int16		PacketType;

	FPacketHead() : PacketSize{ 0 }, PacketType{ 0 } {}
	FPacketHead(const int16 size, const int16 type) : PacketSize(size), PacketType(type) {}
};
