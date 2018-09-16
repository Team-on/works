#pragma once
class GameCell{
public:
	enum CellState  : char {Empty, X, O};

	bool isActive;
	HWND hButton;

	GameCell();
	~GameCell();

	CellState GetCellState() { return cellState; }

	void Init();

	void PlaceX();
	void Place0();
private:
	CellState cellState;
};

