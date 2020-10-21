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
		std::cout << "���� ���丮 �ּ� : " << _path << std::endl;
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
				std::cout << "���� ���丮 �ּ� : " << _path << std::endl;
				std::cout << "���������� �̵� : 1" << std::endl;
				std::cout << "���������� �̵� : 2" << std::endl;
				std::cout << "DISK ���̺� ���� : 3" << std::endl;
				std::cout << "�޴� ������ : 4" << std::endl;
				std::cout << "�����Է� : ";
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
	int rIndex = 0;	//path�� �ڿ������� \\�� ��� °�� �ִ��� ������ ����
	int slushC = 0;	//slushC�� 1�̸� ���� ���丮�� ���ٴ� ��
	//indexLimit �� true �� ��� ���� ���丮�� ���� ���·� �Ʒ� ��ƾ�� �������� �ʽ��ϴ�.
	//���丮�� �� �տ������� �˻��ؼ� \\�� ���ö� ���� slushC�� 1�� ������Ų��.
	for (unsigned int i = 0; i < _path.size(); i++)
	{
		if (_path[i] == '\\') slushC++;
	}
	//slushC�� ������ 1���� ���ٸ� ���� ���丮�� ������
	if (slushC > 1) indexLimit = false;
	//���� ���丮�� ������ ��ƾ
	if (!indexLimit)
	{
		
		if (slushC > 1) //���� ���丮�� �ִ�.
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
			indexLimit = true; //�ֻ��� ���丮 ���� �� �� �ش� ��ƾ�� ��޴ϴ�.
		}
	}
	else
	{
		std::cout << "���̻� ���� ���丮�� �����ϴ�." << std::endl;
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
	std::cout << "�̵��ϰ��� �ϴ� ���丮 ���� �Է��ϼ��� : " << std::endl;
	std::cout << "exit = �Է����" << std::endl;
	std::cout << "���� ���丮 �ּ� : " << _path << std::endl;
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
				std::cout << "�������� �ʴ� ���丮 �Դϴ�." << std::endl;
				if (_getch())std::cout << std::endl;
			}
		}
		else
		{
			temp_path = _path + '\\' + dName;
			fs::directory_entry dp(temp_path);
			if (dp.is_directory()) _path = temp_path;
			else {
				std::cout << "�������� �ʴ� ���丮 �Դϴ�." << std::endl;
				if (_getch())std::cout << std::endl;
			}
		}
	}
}

void directoryFL::directoryLableChange()
{
	system("cls");
	std::cout << "���� ���丮 ���̺� : " << _path[0] << "����̺�" << std::endl;
	std::cout << "EX) D:\\�� �̵��� D �Է�" << std::endl;
	std::cout << "������ ���̺��� �Է��ϼ��� : ";
	std::string lable;
	cin >> lable;
	fs::directory_entry lp(lable + ":\\");
	if (lp.is_directory()) _path = lable + ":";
	else {
		std::cout << "�������� �ʴ� ���丮 �Դϴ�." << std::endl;
		if (_getch()) std::cout << std::endl;
	}
}