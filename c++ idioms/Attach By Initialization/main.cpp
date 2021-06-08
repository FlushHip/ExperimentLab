#include <afxwin.h>

class HelloApp: public CWinApp
{
public:
  virtual BOOL InitInstance ();
};

BOOL HelloApp::InitInstance ()
{
    auto frame_wnd_ptr = new CFrameWnd();
    frame_wnd_ptr->Create(nullptr, L"Hello, World");
    frame_wnd_ptr->ShowWindow(SW_SHOW);

    m_pMainWnd = frame_wnd_ptr;
    return TRUE;
}

HelloApp myApp;