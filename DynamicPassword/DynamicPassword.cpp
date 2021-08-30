#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <algorithm>
#include <iomanip>
#include "PasswordData.h"
using std::wcout;
using std::wcin;
using std::endl;

constexpr const wchar_t* path = L"data.idf";

std::wstring& trim(std::wstring& s);
bool WritePasswordData(PasswordData data);
bool ReadPasswordData(PasswordData* ptr);

int main()
{
	wcout << L"ISLStudio Dynamic Password Manager v1.0" << endl;
	wcout << L"Copyright (C) ISLStudio 2014-2021. All rights reserved." << endl << endl;

	std::wstring buffer;

	FILE* fhandle;
	fhandle = _wfopen(path, L"r");
	PasswordData data;
	if (!fhandle) {
		wcout << L"No dynamic password file detected. Do you want to create it?  [y/n] ";
		wcin >> buffer;
		trim(buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), towupper);
		if (buffer == L"Y") {
			wcout << L"* Password File Generator *" << endl;
			uint32_t pwd;
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					while(true) {
						wcout << "Enter the number of " << wchar_t(L'A' + i) << wchar_t(L'1' + j) << L": ";
						wcin >> buffer;
						pwd = (uint32_t)_wtoi(buffer.c_str());
						if (pwd == 0 || pwd >= 1000) {
							wcout << L"Invalid value. Please retry." << endl;
							continue;
						}
						data.setData(i, j, pwd);
						break;
					}
				}
			}
			std::wregex reg(L"[A-H][1-8]");
			wcout << L"Please review the data you\'ve inputed:" << endl;
			while (true) {
				wcout << L"   1   2   3   4   5   6   7   8" << endl;
				for (int i = 0; i < 8; ++i) {
					wcout << wchar_t(L'A' + i) << L' ';
					for (int j = 0; j < 8; ++j) {
						wcout << std::setw(3) << std::setfill(L'0') << data.getData(i, j) << L' ';
					}
					wcout << endl;
				}
				wcout << L"Is this OK? [y/n] ";
				wcin >> buffer;
				trim(buffer);
				std::transform(buffer.begin(), buffer.end(), buffer.begin(), towupper);
				if (buffer == L"Y") {
					break;
				}
				while (true) {
					wcout << L"Input the coordinate you want to change: ";
					wcin >> buffer;
					trim(buffer);
					std::transform(buffer.begin(), buffer.end(), buffer.begin(), towupper);
					if (!std::regex_match(buffer, reg)) {
						wcout << L"Syntax error. Please enter a correct coordinate." << endl;
						continue;
					}
					break;
				}
				std::wstring cood = buffer;
				while (true) {
					wcout << "Enter the new value of " << cood << L": ";
					wcin >> buffer;
					pwd = (uint32_t)_wtoi(buffer.c_str());
					if (pwd == 0 || pwd >= 1000) {
						wcout << L"Invalid value. Please retry." << endl;
						continue;
					}
					data.setData(cood[0] - L'A', cood[1] - L'1', pwd);
					break;
				}
				wcout << L"Now review the data currently:" << endl;
			}
			wcout << endl;
			bool res = WritePasswordData(data);
			if (!res) {
				wcout << L"Failure when writing into data file. Please report this error to the developer." << endl
					<< L"Press enter to exit...";
				getwchar();
				return -1;
			}
			else {
				wcout << L"Congratulations! Data file written successfully." << endl;
			}
		}
		else {
			return 0;
		}
	}
	else {
		fclose(fhandle);
		bool res = ReadPasswordData(&data);
		if (!res) {
			wcout << L"Failure when reading data file. Please report this error to the developer." << endl
				<< L"Press enter to exit...";
			getwchar();
			return -1;
		}
	}

	wcout << L"* Dynamic Password Reader *" << endl << L"Syntax: [Coordinate]:[Coordinate]  e.g. A1:G5" << endl << endl;
	std::wregex reg(L"[A-H][1-8]:[A-H][1-8]");
	while (true) {
		wcout << L"Enter Position Required: ";
		wcin >> buffer;
		trim(buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), towupper);
		if (!std::regex_match(buffer, reg)) {
			wcout << L"Syntax error. Please enter a correct position." << endl << L"Syntax: [Coordinate]:[Coordinate]  e.g. A1:G5" << endl;
			continue;
		}
		std::wstringstream ss;
		ss << std::setw(3) << std::setfill(L'0') << data.getData(buffer[0] - L'A', buffer[1] - L'1');
		ss << std::setw(3) << std::setfill(L'0') << data.getData(buffer[3] - L'A', buffer[4] - L'1');
		ss >> buffer;
		wcout << L"Result: " << buffer << endl;
		wcout << L"Do you want to continue? [y/n] ";
		wcin >> buffer;
		trim(buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), towupper);
		if (buffer != L"Y")
			break;
	}
	return 0;
}
