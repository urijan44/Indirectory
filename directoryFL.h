#pragma once

#include <string>
#include "menu.h"

namespace dFL {
	class directoryFL
	{
	private:
		std::string _path;
		std::string filePath;
		int fileCount;
		_menu::menu MENU;
		std::string fileList;
		bool indexLimit;
	public:
		directoryFL();
		void init();
		void run();
		void directoryUp();
		void directoryDown();
		void directoryLableChange();
	};
}

