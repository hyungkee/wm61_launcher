// win32 test.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "win32 test.h"
//#include "fon.cpp"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE			g_hInst;			// ���� �ν��Ͻ��Դϴ�.
HWND				g_hWndMenuBar;		// �޴� ���� �ڵ��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TEST));


	// �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd;

	TCHAR szTitle[MAX_LOADSTRING];		// ���� ǥ���� �ؽ�Ʈ
    TCHAR szWindowClass[MAX_LOADSTRING];	// �� â Ŭ���� �̸�

    g_hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // CAPEDIT �� SIPPREF�� ���� ��� ��ġ Ư�� ��Ʈ���� �ʱ�ȭ�ϱ� ����
    // ���� ���α׷��� �ʱ�ȭ�ϴ� ���� SHInitExtraControls�� �� �� ȣ���ؾ� �մϴ�.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_WIN32TEST, szWindowClass, MAX_LOADSTRING);

    //�̹� ���� ���� ��� â�� ��Ŀ���� �� ���� �����ϴ�.
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // �� �� �ڽ� â�� ��Ŀ���� �����մϴ�.
        // "| 0x00000001"�� ����Ͽ� ������ ��� â�� �������� ���� ����
        // Ȱ��ȭ�մϴ�.
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

    // CW_USEDEFAULT�� ����Ͽ� �� â�� ����� ��� �޴� ������ ���̴�
    // ������� �ʽ��ϴ�. ���� �޴� ������ �ִ� ���
    // â�� ���� �� â�� ũ�⸦ �����մϴ�.
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
            // �޴��� ���� ������ ���� �м��մϴ�.
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

            // �� Ȱ��ȭ ���� ���� �ʱ�ȭ
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
            // Ȱ��ȭ �޽����� �п� �˸��ϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                // [�Ϸ�] ���߸� ����� ũ�⸦ �����մϴ�.  
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
