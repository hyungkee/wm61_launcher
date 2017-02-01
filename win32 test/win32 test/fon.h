#pragma once
#include "ON.h"

//#include "atlconv.h"
//#include "atlbace.h"
#pragma comment(lib,"atlsd.lib")

class fon
{
public:
	fon(void);
	~fon(void);
	void Init(HWND m_hWnd);
	void Main(HWND hWnd, HINSTANCE g_Inst, int SIGNAL);
	void Exit();
	void MODEPRINT();
	HBITMAP MakeDIBSection(HDC hdc, int width, int height);
	HDC Pout(int target,HDC Surface);
	void Reseat(int touch);
	int bh(int t);
	int MAX;
	int k;
	int TopNumber;
	int MODE;
	HBITMAP sect;

	int PlusX[16],PlusY[16];

	int x[4],y[4];

	HDC hdc,Surface;
	RECT rect,rt;
	CON cons[16];
	HINSTANCE hInstance;
};