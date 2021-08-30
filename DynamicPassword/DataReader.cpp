#include <cstdio>
#include <string>
#include "PasswordData.h"

constexpr const wchar_t* path = L"data.idf";

bool ReadPasswordData(PasswordData* ptr)
{
	FILE* file;
	file = _wfopen(path, L"r");
	if (file == NULL) {
		return false;
	}
	uint32_t temp = 0;
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			fread(&temp, sizeof(uint32_t), 1, file);
			ptr->setData(i, j, (temp - 3) / 699);
		}
	}
	fclose(file);
	return true;
}

bool WritePasswordData(PasswordData data)
{
	FILE* file;
	file = _wfopen(path, L"w");
	if (file == NULL) {
		return false;
	}
	uint32_t temp = 0;
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			temp = data.getData(i, j) * 699 + 3;
			fwrite(&temp, sizeof(uint32_t), 1, file);
		}
	}
	fclose(file);
	return true;
}
