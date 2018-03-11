#include "precompiledHeaders.h"

#include "game.h"

int main(int argc, char ** argv) {
	srand(uint(time(0)));
	setlocale(NULL, "RUS");
	atexit( []() -> void {
		cout << "Press any key to exit...";
		//Sleep(1000);
		//_getch();
	});

	uchar screenSizex, screenSizey;
	screenSizex = 150;
	screenSizey = 50;

	game chess(screenSizex, screenSizey, argv);
	while (chess.MainLoop());

	return EXIT_SUCCESS;
}
