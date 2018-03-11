#include "precompiledHeaders.h"

#include "GAME.h"

int main(int argc, char ** argv) {
	srand(uint(time(0)));
	atexit( []() -> void {
		cout << "Press any key to exit...";
		//_getch();
	});

	uchar screenSizex, screenSizey;
	screenSizex = 150;
	screenSizey = 45;

	GAME game(screenSizex, screenSizey);

	if (game.MainMenu()) {
		game.PrintCurrState();

		while (game.GetIsRunning()) {
			game.MainLoop();
		}

	}

	return EXIT_END_OF_MAIN;
}
