#include "pch.h"
#include "BWindow.h"
#include "Core.h"
#include "Resource.h"
BWindow::BWindow() : m_hWnd(0), m_hInstance(0)
{
}

BWindow::~BWindow()
{
}

LRESULT BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0); // WM_QUIT
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance; 
	this->MyRegisterClass();
	this->WindowCreate();
	this->WindowShow(nCmdShow);
	this->WindowUpdate();

	// Core 초기화
	if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{ 1100, 320 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
		return FALSE;
	}
	return this->MessageLoop(); // 여기서 무한루프. 끝나면 프로그램 종료(exitcode와 함게)
}

ATOM BWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WINDOW_NAME;
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

void BWindow::WindowCreate()
{
	m_hWnd = CreateWindowW(WINDOW_NAME, L"록맨 달리기", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
	//SetMenu(m_hWnd, NULL);
}

void BWindow::WindowShow(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

void BWindow::WindowUpdate()
{
	UpdateWindow(m_hWnd);
}

int BWindow::MessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	// PeekMessage
	while (true)
	{
		// 메시지가 있으면 여기
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// 우리의 게임 루프가 돌거야.
		else
		{
			// "게임을 진행하지."
			Core::GetInst()->Progress();
		}

	}

	return (int)msg.wParam;
}
