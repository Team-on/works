#ifndef _TETRIS_FIGURE_H_
#define _TETRIS_FIGURE_H_

class tetrisFigure{
public:
	static int MaxSize;
private:
	enum TYPE {I, J, L, O, S, T, Z, Rotatable, UnRotatable, Transportable, TypeOther};
	TYPE type;
	
	hgeQuad **figure;
	bool **isUsed;

	static bool xmlLoaded;
	static TYPE *masksTypes;
	static unsigned int masksCnt;
	static bool ***masks;
public:
	tetrisFigure();
	~tetrisFigure();

	void Rotate();
	bool **RotateSample();

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	hgeQuad ** GetQuads() { return figure;}
	bool** GetMask() { return isUsed; }
private:
	void BasicRotate(bool **mtx);

	//------------------------------- Generator ----------------------------------
	void FillWithRandFigure(hgeColor color);

	void FillWithJ(hgeColor color);
	void FillWithL(hgeColor color);
	void FillWithO(hgeColor color);
	void FillWithT(hgeColor color);
	void FillWithZ(hgeColor color);
	void FillWithS(hgeColor color);
	void FillWithI(hgeColor color);
	void FillWithMaskById(hgeColor color, int id);

	void SetQuad(hgeColor color, int idy, int idx);

public:
	static void LoadFromXml();
};

#endif