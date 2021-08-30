#include "PasswordData.h"
#include <memory>

PasswordData::PasswordData()
{
	memset(data, 0, 64 * sizeof(uint32_t));
}

void PasswordData::setData(size_t x, size_t y, uint32_t val)
{
	data[x][y] = val;
}

uint32_t PasswordData::getData(size_t x, size_t y)
{
	 return data[x][y];
}
