#pragma once
#include <cstdint>

class PasswordData
{
public:
	PasswordData();
	
	void setData(size_t x, size_t y, uint32_t val);
	uint32_t getData(size_t x, size_t y);

protected:
	uint32_t data[8][8];
};

