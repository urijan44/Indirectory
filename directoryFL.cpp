#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <conio.h>
#include "directoryFL.h"
#include "menu.h"

namespace fs = std::filesystem;
using namespace dFL;
directoryFL::directoryFL()
{
	init();
}

void directoryFL::init()
{
	_path = fs::current_path().string();
	indexLimit = false;
}

void directoryFL::run()
{
	char m_select[1] = {};
	while (*m_select != '4')
	{
		system("cls");
		std::cout << "현재 디렉토리 주소 : " << _path << std::endl;
		MENU.menuCall();
		cin >> *m_select;
		switch (*m_select)
		{
		case '1':
		{
			system("cls");
			for (auto& p : fs::directory_iterator(_path))
			{
				std::cout << p.path().filename() << std::endl;
			}
			if (_getch())std::cout << std::endl;
			break;
		}
		case '2':
		{
			system("cls");
			char move[1] = {};
			while (*move != '4')
			{
				system("cls");
				std::cout << "현재 디렉토리 주소 : " << _path << std::endl;
				std::cout << "상위폴더로 이동 : 1" << std::endl;
				std::cout << "하위폴더로 이동 : 2" << std::endl;
				std::cout << "DISK 레이블 변경 : 3" << std::endl;
				std::cout << "메뉴 나가기 : 4" << std::endl;
				std::cout << "동작입력 : ";
				cin >> *move;
				switch (*move)
				{
				case '1':
				{
					directoryUp();
					break;
				}
				case '2':
				{
					directoryDown();
					break;
				}
				case '3':
				{
					directoryLableChange();
					break;
				}
				case '4':
				{
					break;
				}
				default:
				{
					break;
				}
				}
			}
			break;
		}
		case '3':
		{
			string buffer;
			filePath = _path + "\\List.csv";
			std::cout << filePath << std::endl;
			ofstream list_out(filePath);
			if (list_out.is_open())
			{
				for (auto& p : fs::directory_iterator(_path))
				{
					buffer = p.path().filename().string();
					fileList += buffer + '\n';
				}
				std::cout << "create list file SUCCESS" << std::endl;
				list_out << fileList;
				if (_getch()) std::cout << std::endl;
			}
			break;
		}
		case '4':
		{
			break;
		}
		default:
		{
			system("cls");
			break;
		}
		}
	}
}

void directoryFL::directoryUp()
{
	system("cls");
	int rIndex = 0;	//path의 뒤에서부터 \\가 몇번 째에 있는지 저장할 변수
	int slushC = 0;	//slushC가 1이면 상위 디렉토리가 없다는 뜻
	//indexLimit 가 true 일 경우 상위 디렉토리가 없는 상태로 아래 루틴이 동작하지 않습니다.
	//디렉토리를 맨 앞에서부터 검색해서 \\가 나올때 마다 slushC를 1씩 증가시킨다.
	for (unsigned int i = 0; i < _path.size(); i++)
	{
		if (_path[i] == '\\') slushC++;
	}
	//slushC의 개수가 1보다 많다면 상위 디렉토리가 존재함
	if (slushC > 1) indexLimit = false;
	//상위 디렉토리가 있을때 루틴
	if (!indexLimit)
	{
		
		if (slushC > 1) //상위 디렉토리가 있다.
		{
			for (size_t i = _path.size(); i != _path[0]; i--)
			{
				if (_path[i] != '\\') rIndex++;
				else break;
			}
			_path.erase(_path.end() - rIndex, _path.end());
		}
		else if (slushC == 1)
		{
			for (size_t i = 0; i != _path.size(); i++)
			{
				if (_path[i] != '\\') rIndex++;
				else break;
			}
			_path.erase(_path.begin() + rIndex, _path.end());
			indexLimit = true; //최상위 디렉토리 까지 간 후 해당 루틴을 잠급니다.
		}
	}
	else
	{
		std::cout << "더이상 상위 디렉토리가 없습니다." << std::endl;
		if (_getch())std::cout << std::endl;
	}
}

void directoryFL::directoryDown()
{
	system("cls");
	int oneSlushCheck = 0;
	for (auto& p : _path)
	{
		if (p == '\\') oneSlushCheck++;
	}
	if (oneSlushCheck == 0)
	{
		_path += '\\';
		oneSlushCheck++;
	}
	else if (oneSlushCheck == 1)
	{
		oneSlushCheck++;
	}
	for (auto& p : fs::directory_iterator(_path))
	{
		std::cout << p.path().filename() << std::endl;
	}
	std::cout << "이동하고자 하는 디렉토리 명을 입력하세요 : " << std::endl;
	std::cout << "exit = 입력취소" << std::endl;
	std::cout << "현재 디렉토리 주소 : " << _path << std::endl;
	std::string dName;
	cin >> dName;
	if (dName != "exit")
	{
		std::string temp_path;
		if (oneSlushCheck==1)
		{
			temp_path = _path + dName;
			fs::directory_entry dp(temp_path);
			if (dp.is_directory()) _path = temp_path;
			else {
				std::cout << "존재하지 않는 디렉토리 입니다." << std::endl;
				if (_getch())std::cout << std::endl;
			}
		}
		else
		{
			temp_path = _path + '\\' + dName;
			fs::directory_entry dp(temp_path);
			if (dp.is_directory()) _path = temp_path;
			else {
				std::cout << "존재하지 않는 디렉토리 입니다." << std::endl;
				if (_getch())std::cout << std::endl;
			}
		}
	}
}

void directoryFL::directoryLableChange()
{
	system("cls");
	std::cout << "현재 디렉토리 레이블 : " << _path[0] << "드라이브" << std::endl;
	std::cout << "EX) D:\\로 이동시 D 입력" << std::endl;
	std::cout << "변경할 레이블을 입력하세요 : ";
	std::string lable;
	cin >> lable;
	fs::directory_entry lp(lable + ":\\");
	if (lp.is_directory()) _path = lable + ":";
	else {
		std::cout << "존재하지 않는 디렉토리 입니다." << std::endl;
		if (_getch()) std::cout << std::endl;
	}
}