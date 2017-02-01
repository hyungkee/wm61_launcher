#include "StdAfx.h"
#include "fon.h"
#include "resourceppc.h"
#define Max(x,y) (x>y?x:y)
#define Min(x,y) (x>y?y:x)

fon::fon(void)
{
}

fon::~fon(void)
{
}


HBITMAP fon::MakeDIBSection(HDC hdc, int width, int height)
{
 BITMAPINFO bmi;
 LPVOID  pBits;
 HBITMAP  hBitmap;
 memset(&bmi.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
 bmi.bmiHeader.biSize  = sizeof(BITMAPINFOHEADER);
 bmi.bmiHeader.biBitCount = 24;
 bmi.bmiHeader.biWidth  = width;
 bmi.bmiHeader.biHeight  = height;
 bmi.bmiHeader.biPlanes  = 1;
 hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);
 return hBitmap;


}


void fon::Init(HWND m_hWnd)
{

	int i;
	for(i=0;i<4;i++)
		x[i]=24+(2*i+1)*45+24*i;
	for(i=0;i<4;i++)
		y[i]=150+(2*i+1)*45+40*i-120;

	MAX=12;
	for(i=0;i<MAX;i++){
		cons[i].xi=i%4;
		cons[i].yi=i/4;
		cons[i].px=x[i%4];
		cons[i].py=y[i/4];
		cons[i].fx=cons[i].px;
		cons[i].fy=cons[i].py;
		cons[i].icon_num=i;
		cons[i].icon_bitmap=IDB_BITMAP4+i;
		cons[i].used=1;
	}
//	printf(cons[0].stat,"\windows\iexplore.exe");
	rect.left=0,rect.top=0,rect.right=480,rect.bottom=640;
	TopNumber=-1;
	k=0;

	MODE=1;
}



//	char pName[]="";
//	char k[]=CA2W(pName);
//	LPCWSTR k=CA2W(pName);//=A2CW(pName);
//	WideCharToMultiByte(
//	;


void fon::Main(HWND hWnd, HINSTANCE g_Inst, int SIGNAL)
{
	hInstance=g_Inst;

	PAINTSTRUCT ps;
	HBRUSH BlackB;

	if(SIGNAL==0)	Surface=CreateCompatibleDC(hdc);
	hdc=BeginPaint(hWnd, &ps);
	Surface=CreateCompatibleDC(hdc);

	if(sect==NULL)	sect=CreateCompatibleBitmap(hdc,480,640);

	SelectObject(Surface, sect);

	BlackB=(HBRUSH)GetStockObject(BLACK_BRUSH);
	FillRect(Surface, &rect, BlackB);
	DeleteObject(BlackB);
	int i;

//배경
//	{
//		HDC MemDC;
//		MemDC=CreateCompatibleDC(Surface);
//		SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BACKGROUND)));
//		BitBlt(Surface,0,0,480,640,MemDC,0,0,SRCPAINT);
//		DeleteDC(MemDC);
//	}


	MODEPRINT();
	for(i=0;i<MAX;i++)
		if(i!=TopNumber && cons[i].used==1)	Surface=Pout(i,Surface);


	if(TopNumber!=-1){

		HDC MemDC;
		MemDC=CreateCompatibleDC(Surface);
		SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP26)));
		BitBlt(Surface,cons[TopNumber].px-55,cons[TopNumber].py-55,110,110,MemDC,0,0,SRCPAINT);
		SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(cons[TopNumber].icon_bitmap)));

		StretchBlt(Surface,cons[TopNumber].px-55,cons[TopNumber].py-55,110,110,MemDC,0,0,90,90,SRCAND);
		rt.left=cons[TopNumber].px-50,rt.right=cons[TopNumber].px+50;
		rt.top=cons[TopNumber].py+55,rt.bottom=cons[TopNumber].py+90;
		if(TopNumber==0)	DrawText(Surface,L"날씨",-1,&rt,DT_CENTER);
		if(TopNumber==1)	DrawText(Surface,L"인터넷",-1,&rt,DT_CENTER);
		if(TopNumber==2)	DrawText(Surface,L"달력",-1,&rt,DT_CENTER);
		if(TopNumber==3)	DrawText(Surface,L"계산기",-1,&rt,DT_CENTER);
		if(TopNumber==4)	DrawText(Surface,L"twitter",-1,&rt,DT_CENTER);
		if(TopNumber==5)	DrawText(Surface,L"시계",-1,&rt,DT_CENTER);
		if(TopNumber==6)	DrawText(Surface,L"주식",-1,&rt,DT_CENTER);
		if(TopNumber==7)	DrawText(Surface,L"Ipod",-1,&rt,DT_CENTER);
		if(TopNumber==8)	DrawText(Surface,L"메일",-1,&rt,DT_CENTER);
		if(TopNumber==9)	DrawText(Surface,L"지도",-1,&rt,DT_CENTER);
		if(TopNumber==10)	DrawText(Surface,L"메모",-1,&rt,DT_CENTER);
		if(TopNumber==11)	DrawText(Surface,L"전화",-1,&rt,DT_CENTER);
		if(TopNumber==12)	DrawText(Surface,L"카메라",-1,&rt,DT_CENTER);
		if(TopNumber==13)	DrawText(Surface,L"문자",-1,&rt,DT_CENTER);
		if(TopNumber==14)	DrawText(Surface,L"설정",-1,&rt,DT_CENTER);
		if(TopNumber==15)	DrawText(Surface,L"사진",-1,&rt,DT_CENTER);
		DeleteDC(MemDC);
	}


	BitBlt(hdc,0,0,480,640,Surface,0,0,SRCCOPY);
	
	EndPaint(hWnd, &ps);
	DeleteDC(hdc);
	DeleteDC(Surface);
}


int fon::bh(int t){
	if(t>0)	return 1;
	if(t<0)	return -1;
	return 0;
}


void fon::Reseat(int touch){
	static int i;
	for(i=0;i<MAX;i++)
	if(touch==0 || i!=TopNumber){
		cons[i].px+=PlusX[i];
		cons[i].py+=PlusY[i];
		if(Min(cons[i].px-PlusX[i],cons[i].px+PlusX[i])<=cons[i].fx && cons[i].fx<=Max(cons[i].px-PlusX[i],cons[i].px+PlusX[i]))	cons[i].px=cons[i].fx, PlusX[i]=0;
		if(Min(cons[i].py-PlusY[i],cons[i].py+PlusY[i])<=cons[i].fy && cons[i].fy<=Max(cons[i].py-PlusY[i],cons[i].py+PlusY[i]))	cons[i].py=cons[i].fy, PlusY[i]=0;
	}
}

HDC fon::Pout(int target,HDC Surface)
{
	HDC MemDC;
	MemDC=CreateCompatibleDC(Surface);
	SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3)));
	BitBlt(Surface,cons[target].px-45,cons[target].py-45,90,90,MemDC,0,0,SRCPAINT);
	SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(cons[target].icon_bitmap)));

	BitBlt(Surface,cons[target].px-45,cons[target].py-45,90,90,MemDC,0,0,SRCAND);
	DeleteDC(MemDC);
	rt.left=cons[target].px-50,rt.right=cons[target].px+50;
	rt.top=cons[target].py+45,rt.bottom=cons[target].py+80;
	if(target==0)	DrawText(Surface,L"날씨",-1,&rt,DT_CENTER);
	if(target==1)	DrawText(Surface,L"인터넷",-1,&rt,DT_CENTER);
	if(target==2)	DrawText(Surface,L"달력",-1,&rt,DT_CENTER);
	if(target==3)	DrawText(Surface,L"계산기",-1,&rt,DT_CENTER);
	if(target==4)	DrawText(Surface,L"twitter",-1,&rt,DT_CENTER);
	if(target==5)	DrawText(Surface,L"시계",-1,&rt,DT_CENTER);
	if(target==6)	DrawText(Surface,L"주식",-1,&rt,DT_CENTER);
	if(target==7)	DrawText(Surface,L"Ipod",-1,&rt,DT_CENTER);
	if(target==8)	DrawText(Surface,L"메일",-1,&rt,DT_CENTER);
	if(target==9)	DrawText(Surface,L"지도",-1,&rt,DT_CENTER);
	if(target==10)	DrawText(Surface,L"메모",-1,&rt,DT_CENTER);
	if(target==11)	DrawText(Surface,L"전화",-1,&rt,DT_CENTER);
	if(target==12)	DrawText(Surface,L"카메라",-1,&rt,DT_CENTER);
	if(target==13)	DrawText(Surface,L"문자",-1,&rt,DT_CENTER);
	if(target==14)	DrawText(Surface,L"설정",-1,&rt,DT_CENTER);
	if(target==15)	DrawText(Surface,L"사진",-1,&rt,DT_CENTER);
	return Surface;
}

void fon::MODEPRINT()
{

	HDC MemDC;
	MemDC=CreateCompatibleDC(Surface);
	SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP23)));
	BitBlt(Surface,0,476,480,64,MemDC,0,0,SRCPAINT);
	if(MODE==-1)	SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP25)));
	if(MODE==0)		SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP22)));
	if(MODE==1)		SelectObject(MemDC, LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP24)));


	BitBlt(Surface,0,476,480,64,MemDC,0,0,SRCAND);
	DeleteDC(MemDC);
}


void fon::Exit(void)
{
	DeleteDC(Surface);
	DeleteDC(hdc);
}

