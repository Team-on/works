#include "stdafx.h"
#include "GameCell.h"
#include "resource.h"


GameCell::GameCell(){

}


GameCell::~GameCell(){

}

void GameCell::Init(){
	SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP,
		(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3)))
	);
	cellState = Empty;
}

void GameCell::PlaceX(){
	SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP,
		(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)))
	);
	cellState = X;
}

void GameCell::Place0(){
	SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP,
		(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)))
	);
	cellState = O;
}
