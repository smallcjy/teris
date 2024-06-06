#include"seviceHeadFileSet.h"
#include"game.h"

int 
main(void) {

	game::gameMenuDraw();
	MOUSEMSG msg;
	//while (true) {
	//	msg = GetMouseMsg();
	//	if (msg.uMsg == WM_LBUTTONDOWN) {
	//		std::cout << msg.x << ' ' << msg.y << std::endl;
	//	}
	//}
	BeginBatchDraw();
	while (1) {
		game::gameStateSelect();
		FlushBatchDraw();
	}
	EndBatchDraw();
	
	return 0;
}