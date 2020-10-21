#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
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
}

void directoryFL::run()
{
	char m_select[1] = {};
	while (*m_select != '5')
	{
		MENU.menuCall();
		cin >> *m_select;
		switch (*m_select)
		{
		case '1':
		{
			std::cout << _path << std::endl;
			break;
		}
		case '2':
		{
			for (auto& p : fs::directory_iterator(_path))
			{
				std::cout << p.path().filename() << std::endl;
			}
			break;
		}
		case '3':
		{
			system("cls");
			char move[1] = {};
			while (*move != '3')
			{
				std::cout << "현재 디렉토리 주소 : " << _path << std::endl;
				std::cout << "상위폴더로 이동 : 1" << std::endl;
				std::cout << "하위폴더로 이동 : 2" << std::endl;
				std::cout << "메뉴 나가기 : 3" << std::endl;
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
		case '4':
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
			}
			break;
		}
		case '5':
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
	int rIndex = 0;
	int slushC = 0;
	for (unsigned int i = 0; i < _path.size(); i++)
	{
		if (_path[i] == '\\') slushC++;
	}
	if(!(slushC == 1))
	{
		for (int i = _path.size(); i != _path[0]; i--)
		{
			if (_path[i] != '\\') rIndex++;
			else break;
		}
		_path.erase(_path.end() - rIndex, _path.end());
	}
	else
	{
		for (int i = _path.size(); i != _path[0]; i--)
		{
			if (_path[i] != '\\') rIndex++;
			else break;
		}
		_path.erase(_path.end() - rIndex + 1, _path.end());
	}
}

void directoryFL::directoryDown()
{
	std::cout << "directoryDown" << std::endl;
}