#include "menu.h"
using namespace _menu;
menu::menu()
{
	menuList[0] = "���� ���� Ȯ���ϱ� : 1\n";
	menuList[1] = "���� ���� ���� ����Ʈ ���� : 2\n";
	menuList[2] = "���丮 �̵��ϱ� : 3\n";
	menuList[3] = "���� ���� ���� ����Ʈ ����ϱ� : 4\n";
	menuList[4] = "���α׷� ���� : 5\n";
	menuList[5] = "�����Է� : ";
}

void menu::menuCall()
{
	for (int i = 0; i < 6; i++)
	{
		cout << this->menuList[i];
	}
}

void menu::menuCall(int index)
{
	cout << this->menuList[index - 1];
}