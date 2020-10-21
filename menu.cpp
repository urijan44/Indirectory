#include "menu.h"
using namespace _menu;
menu::menu()
{
	menuList[0] = "현재 폴더 파일 리스트 보기 : 1\n";
	menuList[1] = "디렉토리 이동하기 : 2\n";
	menuList[2] = "현재 폴더 파일 리스트 출력하기 : 3\n";
	menuList[3] = "프로그램 종료 : 4\n";
	menuList[4] = "동작입력 : ";
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