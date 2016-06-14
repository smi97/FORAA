// dz2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "dz2.h"
//#include "func.cpp"

#define ED 1
#define FLIGHTCONTROL 2
#define SIMPLEFLIGHT 3
#define PREP 4
#define SMTH 5
#define IDM_OPEN 101
#define IDM_SAVE 102
#define MAX_LOADSTRING 100
#define KEY_BKCOLOUR RGB(255,255,255)
#define KEY_TEXTCOLOUR RGB(0,0,0)
using namespace std;

struct MESSAGE {
	TCHAR event[300];
	int lenght;
	int BKcolour;
	int TEXTcolour;
	int num;
	friend ostream& operator<<(std::ostream&, MESSAGE &);
};

ostream& operator<<(std::ostream& out, MESSAGE & message)
{
	wstring ws(message.event);
	string str(ws.begin(), ws.end());
	out << str << "\n";
	return out;
}

list<MESSAGE> Mes;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
static HWND hDlg, hDlgEditб, SotrDialog;										// хэндл диалогового окна


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog1(HWND, UINT, WPARAM, LPARAM);
UINT WINAPI SetTimer(HWND hwnd, UINT idTimer, UINT uTimeout, TIMERPROC tmprc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DZ2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ2));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DZ2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
int sm = 0, difference = 5, position;
static int pos = 0, page = 0;
OPENFILENAME ofn;
TCHAR NameFile[256] = L"MyFile.txt"; // Сюда будет записано имя файла
int len = 0, TimeFlag = 0;
std::ofstream flight_log("flight_log.txt");


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hCompatibleDC;
	PAINTSTRUCT PaintStruct;
	HANDLE hBitmap, hOldBitmap;
	RECT Rect;
	BITMAP Bitmap;
	hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, Dialog1);

	static HWND hwndButton, hwndEdit, hwndSearch, hwndMove;
	switch (message)
	{
	case WM_CREATE:
		hwndButton = CreateWindow(L"button", L"FLIGHT CONTROL",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 15,
			200, 70,
			hWnd, (HMENU)FLIGHTCONTROL, NULL, NULL);
			
		hwndSearch = CreateWindow(L"button", L"SIMPLE FLIGHT",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 100,
			200, 20,
			hWnd, (HMENU)SIMPLEFLIGHT, NULL, NULL);
			
		ShowWindow(hDlg, SW_SHOWDEFAULT);
		
		break;
	case WM_SETFOCUS:
		SetFocus(hWnd);
		break;
	case WM_TIMER:
		SendMessage(hDlg, WM_PAINT, 0, 0);
		InvalidateRect(hDlg, NULL, TRUE);
		break;
	
	case WM_COMMAND:
	{
					   int wmId = LOWORD(wParam);
					   switch (wmId)
					   {
					 /*  case ID_32771: // Открыть
						   ZeroMemory(&ofn, sizeof(ofn));
						   ofn.lStructSize = sizeof(ofn);
						   ofn.hwndOwner = hWnd;
						   ofn.lpstrFile = NameFile;
						   // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
						   // use the contents of szFile to initialize itself.
						   ofn.lpstrFile[0] = '\0';
						   ofn.nMaxFile = 255;
						   ofn.lpstrFilter = L"Текстовые файлы (*.txt)\0*.txt\0Все файлы\0*.*\0";
						   ofn.nFilterIndex = 0;
						   ofn.lpstrFileTitle = NULL;
						   ofn.nMaxFileTitle = 0;
						   ofn.lpstrInitialDir = NULL;
						   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
						   ofn.lpstrDefExt = L"txt"; // Строка расширение по умолчанию

						   if (GetOpenFileName(&ofn))
						   {
							   FILE *f1;
							   f1 = _wfopen(NameFile, L"rb");
							   if (!f1)
							   {
								   MessageBox(hWnd, L"Ошибка открытия файла. Возможно файл не существует", L"Сообщение об ошибке", MB_OK | MB_ICONHAND);
								   return TRUE;
							   }
							   
							  /* List *pP = pFirst;
							   int i, kol;
							   fscanf(f1, "%d ", &kol);
							   for (i = 0; i < kol; i++) {
								   pP = (List*)malloc(sizeof(List));
								   fscanf(f1, " %d ", &pP->M.num);
								   fscanf(f1, "%d ", &pP->M.TEXTcolour);
								   fscanf(f1, "%d ", &pP->M.BKcolour);
								   fscanf(f1, "%d ", &pP->M.lenght);
								   fread(pP->M.event, sizeof(TCHAR), pP->M.lenght, f1);
								   AddInStack(&pFirst, pP, &iLen);
							   }
							   
							   fclose(f1);
							   InvalidateRect(hWnd, 0, TRUE);
						   }



						   break;

					   case ID_32772: // Сохранить
						   ofn.lStructSize = sizeof(OPENFILENAME);
						   ofn.hwndOwner = hWnd; // родительское окно 
						   ofn.lpstrFilter = L"Текстовые файлы (*.txt)\0*.txt\0Все файлы\0*.*\0";
						   ofn.lpstrFile = NameFile;  // Сюда будет записано полное имя файла
						   ofn.nMaxFile = 255;
						   ofn.lpstrFileTitle = NULL;//
						   ofn.nMaxFileTitle = 0;
						   ofn.lpstrInitialDir = NULL;
						   ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
						   ofn.lpstrTitle = NULL;
						   ofn.lpstrDefExt = L"txt"; // Строка расширение по умолчанию
						   if (GetSaveFileName(&ofn))
						   {
							   // Перед записью строку зашифровать
							   // Далее в диалоговом окне вводится секретный ключ, ключ записывается в глобальную переменную Key
							   FILE *f1;
							   f1 = _wfopen(NameFile, L"wb");
							   
							   if (!f1)
							   {
								   MessageBox(hWnd, L"Ошибка открытия файла.", L"Сообщение об ошибке", MB_OK | MB_ICONHAND);
								   return TRUE;
							   }
							   

							//   int i;
							   /*
							   fprintf(f1, "%d ", iLen);
							   List *pP = pFirst;				// текущий элемент для вывода
							   for (i = 0; i < iLen; i++) {
								   fprintf(f1, " %d ", pP->M.num);
								   fprintf(f1, "%d ", pP->M.TEXTcolour);
								   fprintf(f1, "%d ", pP->M.BKcolour);
								   fprintf(f1, "%d ", pP->M.lenght);
								   fwrite(pP->M.event, sizeof(TCHAR), pP->M.lenght, f1);
								   pP = pP->pPnext;
							   }
							   
							   fclose(f1);
							   MessageBox(hWnd, L"Данные успешно сохранены.", L"Сообщение", MB_OK | MB_ICONINFORMATION);
						   }

						   break;
						   */
					   case SIMPLEFLIGHT:
					   {
						   try
						   {
							   Plane plane("Simple_Plane", 123, 234, 3456, 6543);
							   AirportInsideWorker InWorker(19, 1000, 10, 1, "Simple_Inside_Worker");
							   AirportOutsideWorker OutWorker(19, 1000, 10, 1, "Simple_Outside_Worker");
							   OutWorker.PreparePlane(1230, &plane);
							   InWorker.MakeBoarding(109, 300, &plane);
							   Flight fli(&plane, "Simple_Destination", 1000);
							   flight_log << "Plane: \nSimple_Plane \nBoarding person: \nSimple_Inside_Worker \nRefueller: \nSimple_Outside_Worker\nDestination: \nSimple_Destination\nDistance: \n1000 \n\n";
							   string log = fli.MakeFlight();
							   auto it = log.begin();
							   auto it1 = it;
							   for (it; it != log.end(); ++it)
							   {
								   if ((*it) == '\n') 
								   {
									   wstring unic(it1, it);
									   MESSAGE message;
									   lstrcpy(message.event, unic.c_str());
									   message.lenght = lstrlen(message.event);
									   message.TEXTcolour = KEY_TEXTCOLOUR;
									   message.BKcolour = KEY_BKCOLOUR;
									   Mes.push_back(message);
									   flight_log << message;
									   SendMessage(hDlg, WM_PAINT, 0, 0);
									   InvalidateRect(hDlg, NULL, TRUE);
									   it1 = it;
								   }
							   }
							   
						   }

						   catch (const char * a)
						   {
							   wchar_t* wc = new wchar_t[strlen(a) + 1];
							   mbstowcs(wc, a, strlen(a) + 1);
							   MessageBox(hWnd, wc, L"Error", MB_OK);
						   }
						   catch (...)
						   {
							   MessageBox(hWnd, L"ERRR", L"Error", MB_OK);
						   }
						
							break;
					   }

					   case FLIGHTCONTROL:
					   {
						   if (SotrDialog)
							   DestroyWindow(SotrDialog);

						   page = 0;
						   SotrDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
						  // SendMessage(SotrDialog, WM_INITDIALOG, 101, 0);

						   
						   if (!SotrDialog)
						   {
							   MessageBox(hWnd, L"Диалоговое окно не открылось", L"Ошибка", MB_OK);
							   PostQuitMessage(0);
						   }

						   ShowWindow(SotrDialog, SW_SHOWDEFAULT);
						   SetFocus(hWnd);
						   break;
					   }
					   case IDM_ABOUT:
						   DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
						   break;
						   /* case IDM_OPEN: {

										 FILE *f1;
										 f1 = fopen("example.txt", "rb");
										 if (!f1) {
											 MessageBox(hWnd, L"ОШИБКА!", L"Привет", MB_OK);
											 break;
										 }
										 /*List *pP = pFirst;
										 int i, kol;
										 fscanf(f1, "%d ", &kol);
										 for (i = 0; i < kol; i++) {
											 pP = (List*)malloc(sizeof(List));
											 fscanf(f1, " %d ", &pP->M.num);
											 fscanf(f1, "%d ", &pP->M.TEXTcolour);
											 fscanf(f1, "%d ", &pP->M.BKcolour);
											 fscanf(f1, "%d ", &pP->M.lenght);
											 fread(pP->M.event, sizeof(TCHAR), pP->M.lenght, f1);
											 AddInStack(&pFirst, pP, &iLen);
										 }
										 
										 MessageBox(hWnd, L"Файл открыт", L"Успешно!", MB_OK);
										 SendMessage(hDlg, WM_PAINT, 0, 0);
										 InvalidateRect(hDlg, NULL, TRUE);
										 fclose(f1);
										 break;
					   }
					   
					   case IDM_SAVE:{
										 FILE *f1;
										 f1 = fopen("example.txt", "wb");
										// int i;
										/* fprintf(f1, "%d ", iLen);
										 List *pP = pFirst;				// текущий элемент для вывода
										 for (i = 0; i < iLen; i++) {
											 fprintf(f1, " %d ", pP->M.num);
											 fprintf(f1, "%d ", pP->M.TEXTcolour);
											 fprintf(f1, "%d ", pP->M.BKcolour);
											 fprintf(f1, "%d ", pP->M.lenght);
											 fwrite(pP->M.event, sizeof(TCHAR), pP->M.lenght, f1);
											 pP = pP->pPnext;
										 }
										 MessageBox(hWnd, L"Файл сохранен", L"Успешно!", MB_OK);
										 fclose(f1);

										 break;
					   }
						   
					   */
						   
					   case IDM_EXIT:
						   DestroyWindow(hWnd);
						   break;
					   default:
						   return DefWindowProc(hWnd, message, wParam, lParam);
					   }

	}

		break;
	case WM_PAINT:
	{
					 

					 PAINTSTRUCT PS;
					 HDC hDc;
					 hDc = BeginPaint(hWnd, &PS);
					 EndPaint(hWnd, &PS);
	}
		break;
	case WM_DESTROY:{
						
						PostQuitMessage(0);
						break;
	}
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



INT_PTR CALLBACK Dialog(HWND SDialog, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int plane_number = 0, in_number = 0, out_number = 0, passangers_count = 1, baggage_count = 3, fuel_quantity = 1, distance = 0;
	static string destination;
	static vector<Plane> plane;
	static vector<AirportInsideWorker> inworkers;
	static vector<AirportOutsideWorker> outworkers;
	static HWND Editer, Editer1, Text1, Text2, Text, Button1, hwndList;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{

		if (wParam == 101)
		{
			page = 0;
		}
		hwndList = GetDlgItem(SDialog, IDC_LISTBOX_EXAMPLE);
		switch (page)
		{
		case 0:
		{
			Text = CreateWindow(L"STATIC", L"Select plane: ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				20, 10,
				140, 20,
				SDialog, 0, 0, 0);
			plane = get_planes();
			int i = 0;
			for (auto it = plane.begin(); it != plane.end(); it++, i++)
			{
				std::string multi = it->get_model_name();
				std::wstring unic(multi.begin(), multi.end());

				int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
					(LPARAM)unic.c_str());

				SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
				SendMessage(hwndList, LB_SETCURSEL, 0, 0);

			}
			break;
		}
		case 1:
		{
			Text = CreateWindow(L"STATIC", L"Select boarding person: ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				20, 10,
				155, 20,
				SDialog, 0, 0, 0);
			inworkers = get_inside_workers();
			int i = 0;
			for (auto it = inworkers.begin(); it != inworkers.end(); it++, i++)
			{
				std::string multi = it->get_name();
				std::wstring unic(multi.begin(), multi.end());

				int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
					(LPARAM)unic.c_str());

				SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
				SendMessage(hwndList, LB_SETCURSEL, 0, 0);
			}

			Text1 = CreateWindow(L"STATIC", L"How many people? ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				10, 300,
				140, 20,
				SDialog, 0, 0, 0);
			Text2 = CreateWindow(L"STATIC", L"How many luggage? ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				10, 350,
				140, 20,
				SDialog, 0, 0, 0);
			Editer = CreateWindow(L"Edit", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				10, 320,
				150, 30,
				SDialog, (HMENU)ED, NULL, NULL);

			Editer1 = CreateWindow(L"Edit", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				10, 370,
				150, 30,
				SDialog, (HMENU)ED, NULL, NULL);

			break;
		}
		case 2:
		{
			Text = CreateWindow(L"STATIC", L"Select plane refueller: ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				20, 10,
				155, 20,
				SDialog, 0, 0, 0);
			outworkers = get_outside_workers();
			int i = 0;
			for (auto it = outworkers.begin(); it != outworkers.end(); it++, i++)
			{
				std::string multi = it->get_name();
				std::wstring unic(multi.begin(), multi.end());

				int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
					(LPARAM)unic.c_str());

				SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
				SendMessage(hwndList, LB_SETCURSEL, 0, 0);

			}
			Text1 = CreateWindow(L"STATIC", L"How much fuel? ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				10, 300,
				140, 20,
				SDialog, 0, 0, 0);

			Editer = CreateWindow(L"Edit", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				10, 320,
				150, 30,
				SDialog, (HMENU)ED, NULL, NULL);
			break;
		}
		case 3:
		{
			DestroyWindow(hwndList);
			Text1 = CreateWindow(L"STATIC", L"             ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				10, 10,
				160, 20,
				SDialog, 0, 0, 0);

			Text = CreateWindow(L"STATIC", L"Please enter destination ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				130, 100,
				160, 20,
				SDialog, 0, 0, 0);

			Editer = CreateWindow(L"Edit", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				130, 130,
				150, 30,
				SDialog, (HMENU)ED, NULL, NULL);

			Text1 = CreateWindow(L"STATIC", L"Please enter distance ",
				WS_VISIBLE | WS_CHILD | BS_CENTER,
				130, 160,
				140, 20,
				SDialog, 0, 0, 0);

			Editer1 = CreateWindow(L"Edit", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				130, 180,
				150, 30,
				SDialog, (HMENU)ED, NULL, NULL);

			
			break;
		}
		case 4:
		{
			try
			{
				Flight fl(&plane[plane_number], destination, distance);
				int result = MessageBox(SDialog, L"Plane is ready!\n Make a flight?", L"Ready", MB_YESNO);
				if (result == 6)
				{
					flight_log << "Plane: " << "\n";
					flight_log << plane[plane_number].get_model_name() << "\n";
					flight_log << "Boarding person: " << "\n";
					flight_log << inworkers[in_number].get_name() << "\n";
					flight_log << "Refueller: " << "\n";
					flight_log << outworkers[out_number].get_name() << "\n";
					flight_log << "Destination: " << "\n";
					flight_log << destination << "\n";
					flight_log << "Distance: " << "\n";
					flight_log << distance << "\n\n";
					string log = fl.MakeFlight();
					auto it = log.begin();
					auto it1 = it;
					for (it; it != log.end(); ++it)
					{
						if ((*it) == '\n')
						{
							wstring unic(it1, it);
							MESSAGE message;
							lstrcpy(message.event, unic.c_str());
							message.lenght = lstrlen(message.event);
							message.TEXTcolour = KEY_TEXTCOLOUR;
							message.BKcolour = KEY_BKCOLOUR;
							Mes.push_back(message);
							flight_log << message;
							SendMessage(hDlg, WM_PAINT, 0, 0);
							InvalidateRect(hDlg, NULL, TRUE);
							it1 = it;
						}
					}

				}
			}
			catch (const char * a)
			{
				wchar_t* wc = new wchar_t[strlen(a) + 1];
				mbstowcs(wc, a, strlen(a) + 1);
				MessageBox(SDialog, wc, L"Error", MB_OK);
			}
			catch (int)
			{
				MessageBox(SDialog, L"Plane landed in the nearest airport\n", L"Error", MB_OK);
			}
			SendMessage(SDialog, WM_CLOSE, 0, 0);
			break;
		}
		}
		SetFocus(hwndList);
		return TRUE;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(SDialog, LOWORD(wParam));
			return TRUE;
		case PREP:
		{
			switch (page)
			{
			case 0:
			{
				DestroyWindow(Text);
				Text = nullptr;
				break;
			}
			case 1:
			{
				wchar_t text_buf[100], text_buf1[100];
				SendMessage(Editer, WM_GETTEXT, 100, (LPARAM)text_buf);
				SendMessage(Editer1, WM_GETTEXT, 100, (LPARAM)text_buf1);
				passangers_count = _wtoi(text_buf);
				baggage_count = _wtoi(text_buf1);
				inworkers[in_number].MakeBoarding(passangers_count, baggage_count, &plane[plane_number]);
				DestroyWindow(Editer);
				DestroyWindow(Editer1);
				DestroyWindow(Text);
				DestroyWindow(Text1);
				DestroyWindow(Text2);

				break;
			}
			case 2:
			{
				wchar_t text_buf[100];
				SendMessage(Editer, WM_GETTEXT, 100, (LPARAM)text_buf);
				fuel_quantity = _wtoi(text_buf);
				outworkers[out_number].PreparePlane(fuel_quantity, &plane[plane_number]);
				DestroyWindow(Editer);
				DestroyWindow(Text);
				DestroyWindow(Text1);

				break;
			}
			case 3:
			{
				wchar_t text_buf[100], text_buf1[100];
				SendMessage(Editer, WM_GETTEXT, 100, (LPARAM)text_buf1);
				SendMessage(Editer1, WM_GETTEXT, 100, (LPARAM)text_buf);
				distance = _wtoi(text_buf);
				wstring ws(text_buf1);
				string str(ws.begin(), ws.end());
				destination = str;
				DestroyWindow(Editer);
				DestroyWindow(Editer1);
				DestroyWindow(Text);
				DestroyWindow(Text1);

				break;
			}
			}
			page++;
			
			hwndList = GetDlgItem(SDialog, IDC_LISTBOX_EXAMPLE);
			SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
			SendMessage(SDialog, WM_INITDIALOG, 0, 0);
			break;
		}
		case IDC_LISTBOX_EXAMPLE:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{


				HWND hwndList = GetDlgItem(SDialog, IDC_LISTBOX_EXAMPLE);

				int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
				std::string multi;
				std::wstring unic;
				switch (page)
				{
				case 0:
					plane_number = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
					multi = plane[plane_number].info();
					unic = std::wstring(multi.begin(), multi.end());
					break;
				
				case 1:
				{
					in_number = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
					multi = inworkers[in_number].info();
					unic = std::wstring(multi.begin(), multi.end());
					break;
				}
				case 2:
				{
					out_number = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
					multi = outworkers[out_number].info();
					unic = std::wstring(multi.begin(), multi.end());
					break;
				}
				}
				int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

				

				Button1 = CreateWindow(L"button", L"Next",
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					250, 260,
					150, 30,
					SDialog, (HMENU)PREP, NULL, NULL);

				Text = CreateWindow(L"STATIC", unic.c_str(),
					WS_BORDER | WS_VISIBLE | WS_CHILD,
					250, 45,
					150, 210,
					SDialog, 0, 0, 0);
				
				

				return TRUE;
			}

			}
		}

		}
		break;

	}
	case WM_CLOSE:
		Editer = Editer1 = Text1 = Text2 = Text = Button1 = hwndList = nullptr;
		EndDialog(SDialog, 0);
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Dialog1(HWND LogDialog, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto it = Mes.begin();
	PAINTSTRUCT ps;
	RECT Rect;
	HDC hDC;
	int iH = 10;
	int k = 3;
	static int H;
	static HWND hScroll;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_LBUTTONDOWN: {
		SetFocus(LogDialog);
		break;
	}
	
	case WM_PAINT:
		int i, c;
		c = 1;
		hDC = BeginPaint(LogDialog, &ps);
		GetClientRect(LogDialog, &Rect);
		H = (Rect.bottom - Rect.top) / 20;
		if ((difference = Mes.size() - H) > 0)
			SetScrollRange(LogDialog, SB_VERT, 0, difference, TRUE);
		else
			SetScrollRange(LogDialog, SB_VERT, 0, 0, TRUE);
		for (i = 0; i < position; i++) {
			it++;
		}
		for (i = 0; i < Mes.size() - position; i++) {

			SetTextColor(hDC, it->TEXTcolour);
			SetBkColor(hDC, it->BKcolour);
			TextOut(hDC, 30, k, it->event, it->lenght);
			k += 20;
			it++;
		}
		EndPaint(LogDialog, &ps);
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{

		case SB_LINEDOWN:
			if (difference > position)
				position++;
			SetScrollPos(LogDialog, SB_VERT, position, TRUE);
			InvalidateRect(LogDialog, NULL, TRUE);
			break;
		case SB_LINEUP:
			if (position > 0)
				position--;

			SetScrollPos(LogDialog, SB_VERT, position, TRUE);

			InvalidateRect(LogDialog, NULL, TRUE);
			break;
		case SB_PAGEDOWN:
			if (difference > position)
				if (difference < position + 5)
					position = difference;
				else
					position += 5;
			SetScrollPos(LogDialog, SB_VERT, position, TRUE);

			InvalidateRect(LogDialog, NULL, TRUE);
			break;
		case SB_PAGEUP:
			if (position > 0)
				if (position < 5)
					position = 0;
				else
					position -= 5;
			SetScrollPos(LogDialog, SB_VERT, position, TRUE);

			InvalidateRect(LogDialog, NULL, TRUE);
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			position = HIWORD(wParam);
			SetScrollPos(LogDialog, SB_VERT, position, TRUE);

			InvalidateRect(LogDialog, NULL, TRUE);
			break;
		}


		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

UINT WINAPI SetTimer(HWND hwnd, UINT idTimer,
	UINT uTimeout, TIMERPROC tmprc)
{
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND AboutDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(AboutDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
