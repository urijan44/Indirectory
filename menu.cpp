#include "menu.h"
using namespace _menu;
menu::menu()
{
	menuList[0] = "���� ���� ���� ����Ʈ ���� : 1\n";
	menuList[1] = "���丮 �̵��ϱ� : 2\n";
	menuList[2] = "���� ���� ���� ����Ʈ ����ϱ� : 3\n";
	menuList[3] = "���α׷� ���� : 4\n";
	menuList[4] = "�����Է� : ";
}

void menu::menuCall()
{
	for (int i = 0; i < 5; i++)
	{
		cout << this->menuList[i];
	}
}

void menu::menuCall(int index)
{
	cout << this->menuList[index - 1];
}