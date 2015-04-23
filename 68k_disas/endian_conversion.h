#pragma once

#include <cstdint>


inline bool isLittleEndian()
{
	uint16_t tv = 0xFF00;
	if(((uint8_t*)&tv)[0] == 0x00)
		return true;
	else
		return false;
}

inline bool isBigEndian()
{
	uint16_t tv = 0x00FF;
	if(((uint8_t*)&tv)[0] == 0x00)
		return true;
	else
		return false;
}

inline uint16_t swapEndian(uint16_t in)
{
	uint8_t temp;
	uint8_t temp1;

	uint16_t var = 0;

	temp = ((uint8_t*)&in)[0];
	temp1 = ((uint8_t*)&in)[1];

	((uint8_t*)&var)[0] = temp1;
	((uint8_t*)&var)[1] = temp;

	return var;
}

inline uint32_t swapEndian(const uint32_t in)
{
	uint16_t temp;
	uint16_t temp1;

	uint32_t var = 0;

	temp = swapEndian(((uint16_t*)&in)[0]);
	temp1 = swapEndian(((uint16_t*)&in)[1]);

	((uint16_t*)&var)[0] = temp1;
	((uint16_t*)&var)[1] = temp;

	return var;
}

inline uint64_t swapEndian(const uint64_t in)
{
	uint32_t temp;
	uint32_t temp1;

	uint64_t var = 0;

	temp = swapEndian(((uint32_t*)&in)[0]);
	temp1 = swapEndian(((uint32_t*)&in)[1]);

	((uint32_t*)&var)[0] = temp1;
	((uint32_t*)&var)[1] = temp;

	return var;
}

inline uint16_t littleToNative(const uint16_t in)
{
	if(isLittleEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline uint32_t littleToNative(const uint32_t in)
{
	if(isLittleEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline uint64_t littleToNative(const uint64_t in)
{
	if(isLittleEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline int16_t littleToNative(const int16_t in)
{
	return littleToNative((uint16_t)in);
}

inline int32_t littleToNative(const int32_t in)
{
	return littleToNative((uint32_t)in);
}

inline int64_t littleToNative(const int64_t in)
{
	return littleToNative((uint64_t)in);
}

inline uint16_t bigToNative(const uint16_t in)
{
	if(isBigEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline uint32_t bigToNative(const uint32_t in)
{
	if(isBigEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline uint64_t bigToNative(const uint64_t in)
{
	if(isBigEndian())
		return in;
	else
	{
		return swapEndian(in);
	}
}

inline int16_t bigToNative(const int16_t in)
{
	return bigToNative((uint16_t)in);
}

inline int32_t bigToNative(const int32_t in)
{
	return bigToNative((uint32_t)in);
}

inline int64_t bigToNative(const int64_t in)
{
	return bigToNative((uint64_t)in);
}