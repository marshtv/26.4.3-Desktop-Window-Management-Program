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
		int display_width = 60;
		int display_height = 20;
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
			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (x > display_width - window->getWin_width())
				win_coord_upper_left.x = display_width - window->getWin_width();
			else if (x <= display_width - window->getWin_width())
				win_coord_upper_left.x = x;
			if (y > display_height - window->getWin_height())
				win_coord_upper_left.y = display_height - window->getWin_height();
			else if (y <= display_height - window->getWin_height())
				win_coord_upper_left.y = y;
		}

		void moveWindowPosition(int x_shift, int y_shift) {
			initWinPosition(win_coord_upper_left.x + x_shift, win_coord_upper_left.y + y_shift);
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

		Window* getWindowSize() {
			return window;
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

bool checkValidCommand(std::string in_command) {
	if (in_command != "move" && in_command != "resize" && in_command != "display" && in_command != "close")
		return false;
	return true;
}

int main() {
	auto* display = new Display;
	int w_width, w_height, x_shift, y_shift;

	std::cout << "Input size of window (width height):";
	std::cin >> w_width >> w_height;
	display->initWindowSize(w_width, w_height);
	std::cout 	<< "Current window size: "
				 << display->getWindowSize()->getWin_width() << " x "
				 << display->getWindowSize()->getWin_height() << std::endl;

	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "You have 4 commands for operate window on display:" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << '"' << "move" << '"' << " . . . . . for move window," << std::endl;
	std::cout << '"' << "resize" << '"' << " . . . . for resize window," << std::endl;
	std::cout << '"' << "display" << '"' << ". . . . for display window," << std::endl;
	std::cout << '"' << "close" << '"' << ". . . . . for close window and exit program." << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;

	std::string command = inputCommand();
	while (!checkValidCommand(command)) {
		std::cout << "ERROR input. Try again." << std::endl;
		std::cout << "---------------------------------------------------" << std::endl;
		command = inputCommand();
		std::cout << "---------------------------------------------------" << std::endl;
	}
	while (command != "close") {
		if (command == "move") {
			std::cout << "Input offset for move window (x_shift y_shift):";
			std::cin >> x_shift >> y_shift;
			display->moveWindowPosition(x_shift, y_shift);
			std::cout 	<< "Current position of window's upper left corner: "
						<< display->getWindowPosition().x << ", "
						<< display->getWindowPosition().y << std::endl;
		} else if (command == "resize") {
			std::cout << "Input new size of window (width height):";
			std::cin >> w_width >> w_height;
			display->initWindowSize(w_width, w_height);
			std::cout 	<< "Current window size: "
						 << display->getWindowSize()->getWin_width() << " x "
						 << display->getWindowSize()->getWin_height() << std::endl;
		} else {
			display->showDisplay();
		}
		std::cout << "---------------------------------------------------" << std::endl;
		command = inputCommand();
		std::cout << "---------------------------------------------------" << std::endl;
	}

	display->initWindowSize(0, 0);
	display->showDisplay();
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Exit program. Good by." << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;

	delete display;
	display = nullptr;
	return 0;
}
