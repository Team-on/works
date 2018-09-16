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
	isActive = true;
}

void GameCell::PlaceX(){
	if(isActive){
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP,
			(LPARAM) (LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)))
		);
		cellState = X;
	}
}

void GameCell::Place0(){
	if(isActive){
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP,
			(LPARAM) (LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)))
		);
		cellState = O;
	}
}
