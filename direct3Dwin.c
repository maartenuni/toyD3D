
#define WIN_32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <assert.h>

IDXGISwapChain*         swapchain   = NULL;
ID3D11Device*           dev         = NULL;
ID3D11DeviceContext*    devcon      = NULL;
ID3D11RenderTargetView* backbuffer  = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitD3D(HWND hwnd);
void CleanD3D(void);

void InitD3D(HWND hWnd)
{
    /*
     * Initialize D3D.
     */

    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd = { 0 };

    // fill the swap chain description struct
    scd.BufferCount         = 1;                               // one back buffer
    scd.BufferDesc.Format   = DXGI_FORMAT_R8G8B8A8_UNORM;      // use 32-bit color
    scd.BufferUsage         = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how swap chain is to be used
    scd.OutputWindow        = hWnd;                            // the window to be used
    scd.SampleDesc.Count    = 4;                               // how many multisamples
    scd.Windowed            = TRUE;                            // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  0,
                                  NULL,
                                  0,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon
                                  );

    /*
     * Create a render target.
     */

    ID3D10Texture2D* pBackBuffer = NULL;
    swapchain->lpVtbl->GetBuffer(swapchain, 0, &IID_ID3D11Texture2D, &pBackBuffer);
    assert(pBackBuffer != NULL);

    dev->lpVtbl->CreateRenderTargetView(dev, (ID3D11Resource *) pBackBuffer, NULL, &backbuffer);
    pBackBuffer->lpVtbl->Release(pBackBuffer);

    devcon->lpVtbl->OMSetRenderTargets(devcon, 1, &backbuffer, NULL);

    //
    // Set the default viewport.
    //
    D3D11_VIEWPORT viewport = {
        .TopLeftX = 0,
        .TopLeftY = 0,
        .Width = 800,
        .Height = 600
    };

    devcon->lpVtbl->RSSetViewports(devcon, 1, &viewport);
}

void CleanD3D()
{
    swapchain->lpVtbl->Release(swapchain);
    backbuffer->lpVtbl->Release(backbuffer);
    dev->lpVtbl->Release(dev);
    devcon->lpVtbl->Release(devcon);
}

void RenderFrame(void)
{
    float color[4] = {
        0.0f,
        0.2f,
        0.4f,
        1.0f
    };

    devcon->lpVtbl->ClearRenderTargetView(devcon, backbuffer, color);

    swapchain->lpVtbl->Present(swapchain, 0, 0);
}

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE unused,
    PWSTR pCmdLine,
    int nCmdShow
    )
{
    (void) unused;

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

    WNDCLASS wc = { 0 };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    //wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    InitD3D(hwnd);

    // Run the message loop.
    int keep_running = 1;
    MSG msg = {0};
    while (keep_running)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                keep_running = 0;
        }

        RenderFrame();
    }

    return 0;
}

int paint_window(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            OutputDebugString(L"Painting.\n");
            RenderFrame();
        default:
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}