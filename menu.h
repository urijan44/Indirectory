#pragma once
#include <iostream>

using namespace std;
namespace _menu {
	class menu {
	private:
		string menuList[6];

	public:
		menu();
		void menuCall();
		void menuCall(int index);
	};
}