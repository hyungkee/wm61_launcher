// win32 test.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "win32 test.h"
//#include "fon.cpp"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE			g_hInst;			// 현재 인스턴스입니다.
HWND				g_hWndMenuBar;		// 메뉴 모음 핸들입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM			MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

fon Fon;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
	MSG msg;

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TEST));


	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
//		InvalidateRect(hWnd,NULL,FALSE);

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	Fon.Exit();
	Fon.~fon();
	return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TEST));
	wc.hCursor       = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClass;

	return RegisterClass(&wc);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd;

	TCHAR szTitle[MAX_LOADSTRING];		// 제목 표시줄 텍스트
    TCHAR szWindowClass[MAX_LOADSTRING];	// 주 창 클래스 이름

    g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // CAPEDIT 및 SIPPREF와 같은 모든 장치 특수 컨트롤을 초기화하기 위해
    // 응용 프로그램을 초기화하는 동안 SHInitExtraControls를 한 번 호출해야 합니다.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_WIN32TEST, szWindowClass, MAX_LOADSTRING);

    //이미 실행 중인 경우 창에 포커스를 둔 다음 끝냅니다.
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // 맨 앞 자식 창에 포커스를 설정합니다.
        // "| 0x00000001"을 사용하여 소유한 모든 창을 전경으로 보낸 다음
        // 활성화합니다.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
    	return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

	Fon.Init(hWnd);

    // CW_USEDEFAULT를 사용하여 주 창을 만드는 경우 메뉴 모음의 높이는
    // 고려되지 않습니다. 따라서 메뉴 모음이 있는 경우
    // 창을 만든 후 창의 크기를 조정합니다.
    if (g_hWndMenuBar)
    {
        RECT rc;
        RECT rcMenuBar;

        GetWindowRect(hWnd, &rc);
        GetWindowRect(g_hWndMenuBar, &rcMenuBar);
        rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);
		
        MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
	static int i,j,q,dx,dy;
	static int touch=0, speed,x,y;
	static int sw=1,SIGNAL=0;
    static SHACTIVATEINFO s_sai;
	
    switch (message) 
    {

		case WM_LBUTTONDOWN:


			if(165<=LOWORD(lParam) && LOWORD(lParam)<=314 && 476<=HIWORD(lParam) && HIWORD(lParam)<=540 && Fon.MODE!=0)	Fon.MODE=0;
			else if(165<=LOWORD(lParam) && LOWORD(lParam)<=314 && 476<=HIWORD(lParam) && HIWORD(lParam)<=540 && Fon.MODE==0)	Fon.MODE=1;

			else if(Fon.MODE!=0){

				Fon.TopNumber=-1;
				if(touch==0){
					for(i=0;i<4;i++){
						for(j=0;j<5;j++)
							if(    Fon.cons[j*4+i].fx-45<LOWORD(lParam) && LOWORD(lParam)<Fon.cons[j*4+i].fx+45 && Fon.cons[j*4+i].used==1)
								if(Fon.cons[j*4+i].fy-45<HIWORD(lParam) && HIWORD(lParam)<Fon.cons[j*4+i].fy+45){
									Fon.cons[j*4+i].px=LOWORD(lParam);
									Fon.cons[j*4+i].py=HIWORD(lParam);
									Fon.PlusX[j*4+i]=Fon.PlusY[j*4+i]=0;
									Fon.TopNumber=j*4+i;
									Fon.MODE=1;
									break;
								}
						if(j!=5)	break;
					}
					touch=1;
				}

			}
			break;

		case WM_LBUTTONUP:
			touch=0;

/*			if(Fon.MODE==0){
				for(i=0;i<4;i++){
						for(j=0;j<5;j++)
						if(    Fon.cons[j*4+i].fx-65<LOWORD(lParam) && LOWORD(lParam)<Fon.cons[j*4+i].fx+65 && Fon.cons[j*4+i].used==1)
							if(Fon.cons[j*4+i].fy-65<HIWORD(lParam) && HIWORD(lParam)<Fon.cons[j*4+i].fy+65){
								
							}
				}
			}*/

			if(Fon.MODE==-1){
				Fon.MODE=1;
				Fon.cons[Fon.TopNumber].used=0;
				Fon.cons[Fon.TopNumber].px=-100;
				Fon.cons[Fon.TopNumber].py=-100;
			}
			if(Fon.MODE!=0){

				speed=40;
				if(Fon.TopNumber>=0){
					x=Fon.cons[Fon.TopNumber].fx-Fon.cons[Fon.TopNumber].px;
					y=Fon.cons[Fon.TopNumber].fy-Fon.cons[Fon.TopNumber].py;
					Fon.PlusX[Fon.TopNumber]=speed*x/sqrt(x*x+y*y);
					Fon.PlusY[Fon.TopNumber]=speed*y/sqrt(x*x+y*y);
				}
			}

			Fon.TopNumber=-1;

			break;

		case WM_MOUSEMOVE:
			touch=1;

			if(Fon.MODE!=0){

				if(Fon.TopNumber>=0){
					Fon.cons[Fon.TopNumber].px=LOWORD(lParam);
					Fon.cons[Fon.TopNumber].py=HIWORD(lParam);

					if(Fon.MODE==1 && 165<=LOWORD(lParam) && LOWORD(lParam)<=314 && 476<=HIWORD(lParam) && HIWORD(lParam)<=540)	Fon.MODE=-1;
					if(Fon.MODE==-1 && (165>LOWORD(lParam) || LOWORD(lParam)>314 || 476>HIWORD(lParam) || HIWORD(lParam)>540))	Fon.MODE=1;

					for(i=0;i<4;i++){
						for(j=0;j<5;j++)
						if(    Fon.cons[j*4+i].fx-65<LOWORD(lParam) && LOWORD(lParam)<Fon.cons[j*4+i].fx+65 && j*4+i!=Fon.TopNumber && Fon.cons[j*4+i].used==1)
							if(Fon.cons[j*4+i].fy-65<HIWORD(lParam) && HIWORD(lParam)<Fon.cons[j*4+i].fy+65){

								dx=Fon.cons[j*4+i].xi;
								dy=Fon.cons[j*4+i].yi;
			;

								if(Fon.cons[j*4+i].yi*4+Fon.cons[j*4+i].xi>Fon.cons[Fon.TopNumber].yi*4+Fon.cons[Fon.TopNumber].xi){
									for(q=0;q<Fon.MAX;q++)
										if(Fon.cons[q].yi*4+Fon.cons[q].xi>Fon.cons[Fon.TopNumber].yi*4+Fon.cons[Fon.TopNumber].xi && Fon.cons[q].yi*4+Fon.cons[q].xi<=Fon.cons[j*4+i].yi*4+Fon.cons[j*4+i].xi){
											Fon.cons[q].xi-=1;
											speed=40;
											if(Fon.cons[q].xi<=-1)	Fon.cons[q].xi=3,Fon.cons[q].yi-=1,speed=120;

											Fon.cons[q].fx=Fon.x[Fon.cons[q].xi];
											Fon.cons[q].fy=Fon.y[Fon.cons[q].yi];
											x=Fon.cons[q].fx-Fon.cons[q].px;
											y=Fon.cons[q].fy-Fon.cons[q].py;
											Fon.PlusX[q]=speed*x/sqrt(x*x+y*y);
											Fon.PlusY[q]=speed*y/sqrt(x*x+y*y);
										}
								}

								if(Fon.cons[j*4+i].yi*4+Fon.cons[j*4+i].xi<Fon.cons[Fon.TopNumber].yi*4+Fon.cons[Fon.TopNumber].xi){
									for(q=0;q<Fon.MAX;q++)
										if(Fon.cons[q].yi*4+Fon.cons[q].xi<Fon.cons[Fon.TopNumber].yi*4+Fon.cons[Fon.TopNumber].xi && Fon.cons[q].yi*4+Fon.cons[q].xi>=Fon.cons[j*4+i].yi*4+Fon.cons[j*4+i].xi){
											Fon.cons[q].xi+=1;
											speed=40;
											if(Fon.cons[q].xi>=4)	Fon.cons[q].xi=0,Fon.cons[q].yi+=1,speed=120;

											Fon.cons[q].fx=Fon.x[Fon.cons[q].xi];
											Fon.cons[q].fy=Fon.y[Fon.cons[q].yi];
											x=Fon.cons[q].fx-Fon.cons[q].px;
											y=Fon.cons[q].fy-Fon.cons[q].py;
											Fon.PlusX[q]=speed*x/sqrt(x*x+y*y);
											Fon.PlusY[q]=speed*y/sqrt(x*x+y*y);
										}
								}

								speed=40;

								q=Fon.TopNumber;
								Fon.cons[q].xi=dx;
								Fon.cons[q].yi=dy;
									Fon.cons[q].fx=Fon.x[Fon.cons[q].xi];
									Fon.cons[q].fy=Fon.y[Fon.cons[q].yi];
									x=Fon.cons[q].fx-Fon.cons[q].px;
									y=Fon.cons[q].fy-Fon.cons[q].py;
									Fon.PlusX[q]=speed*x/sqrt(x*x+y*y);
									Fon.PlusY[q]=speed*y/sqrt(x*x+y*y);
									j=-1;
									break;
								}
						}
						if(j==-1)	break;
				}

			}
			break;

        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // 메뉴의 선택 영역을 구문 분석합니다.
            switch (wmId)
            {
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);
                    break;
                case IDM_OK:
                    SendMessage (hWnd, WM_CLOSE, 0, 0);				
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:

			SetTimer(hWnd,1,1,NULL);

            SHMENUBARINFO mbi;

            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDR_MENU;
            mbi.hInstRes   = g_hInst;

            if (!SHCreateMenuBar(&mbi)) 
            {
                g_hWndMenuBar = NULL;
            }
            else
            {
                g_hWndMenuBar = mbi.hwndMB;
            }

            // 셸 활성화 정보 구조 초기화
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
            break;

		case WM_TIMER:
			Fon.Reseat(touch);

			InvalidateRect(hWnd,NULL,FALSE);
			break;

        case WM_PAINT:
			Fon.Main(hWnd,g_hInst,SIGNAL);


			break;
        case WM_DESTROY:
            CommandBar_Destroy(g_hWndMenuBar);
			KillTimer(hWnd,1);
			Fon.Exit();
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            // 활성화 메시지를 셸에 알립니다.
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                // [완료] 단추를 만들고 크기를 조정합니다.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;

        case WM_CLOSE:
			Fon.Exit();
            EndDialog(hDlg, message);
            return TRUE;

    }
    return (INT_PTR)FALSE;
}
