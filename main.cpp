#include <iostream>

struct Grid {
	int x = 0;
	int y = 0;
};

class Window {
	private:
		int win_width = 5;
		int win_height = 5;
	public:
		void initWinSize(int width, int height) {
			win_width = width;
			win_height = height;
		}

		int getWin_width() {
			return win_width;
		}

		int getWin_height() {
			return win_height;
		}
};

class Display {
	private:
		int display_width = 80;
		int display_height = 50;
		Window* window = new Window;
		Grid win_coord_upper_left = {0, 0};
	public:
		void initDisplaySize(int d_width, int d_height) {
			display_width = d_width;
			display_height = d_height;
		}

		void initWindowSize(int w_width, int w_height) {
			if (w_width > display_width)
				w_width = display_width;
			if (w_height > display_height)
				w_height = display_height;
			window->initWinSize(w_width, w_height);
			int x = win_coord_upper_left.x, y = win_coord_upper_left.y;
			initWinPosition(x, y);
		}

		void initWinPosition(int x, int y) {
			if (x > display_width - window->getWin_width())
				win_coord_upper_left.x = display_width - window->getWin_width();
			else if (x + display_width - window->getWin_width() < 0)
				win_coord_upper_left.x = 0;
			else
				win_coord_upper_left.x = x;
			if (y > display_height - window->getWin_height())
				win_coord_upper_left.y = display_height - window->getWin_height();
			else if (y + display_height - window->getWin_height() < 0)
				win_coord_upper_left.y = 0;
			else
				win_coord_upper_left.y = y;
		}

		Grid getWindowPosition() {
			return win_coord_upper_left;
		}

		int getDisplayWidth() {
			return display_width;
		}

		int getDisplayHeight() {
			return display_height;
		}

		void showDisplay() {
			std::cout << std::endl;
			for (int i = 0; i < getDisplayHeight(); i++) {
				for (int j = 0; j < getDisplayWidth(); j++) {
					if ((j < win_coord_upper_left.x ||
						j >= win_coord_upper_left.x + window->getWin_width()) ||
						(i < win_coord_upper_left.y ||
						i >= win_coord_upper_left.y + window->getWin_height()))
						std::cout << "0";
					else
						std::cout << "1";
				}
				std::cout << std::endl;
			}
		}
};

std::string inputCommand() {
	std::cout << "Input command (move/resize/display/close):";
	std::string command;
	std::cin >> command;
	return command;
}

bool checkCommand(std::string in_command) {
	if (in_command != "move" && in_command != "resize" && in_command != "display" && in_command != "close")
		return false;
	return true;
}

int main() {
	auto* display = new Display;
	display->initWindowSize(0, 0);
	display->initWinPosition(0, 0);

	std::cout << "You have 4 commands for operate window on display:" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << '"' << "move" << '"' << " . . . . - for move window," << std::endl;
	std::cout << '"' << "resize" << '"' << " . . . - for resize window," << std::endl;
	std::cout << '"' << "display" << '"' << ". . . - for display window," << std::endl;
	std::cout << '"' << "close" << '"' << ". . . . - for close window and exit program." << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;

	std::string in_command = inputCommand();
	while (!checkCommand(in_command)) {
		std::cout << "ERROR input. Try again." << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
		in_command = inputCommand();
		std::cout << "--------------------------------------------------" << std::endl;
	}



	/*std::cout << "Input size of window (width, height):";
	int w_width, w_height;
	std::cin >> w_width >> w_height;
	display->initWindowSize(w_width, w_height);

	std::cout << "Input window's position on display (x, y):";
	int x, y;
	std::cin >> x >> y;
	display->initWinPosition(x, y);

	std::cout << "Input new window's Size (width, height):";
	std::cin >> w_width >> w_height;
	display->initWindowSize(w_width, w_height);

	std::cout << "Input offset for change window's position on display (x, y):";
	std::cin >> x >> y;
	display->initWinPosition((display->getWindowPosition().x + x), (display->getWindowPosition().y + y));*/

	delete display;
	display = nullptr;
	return 0;
}
