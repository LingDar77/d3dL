#include "graphics.h"
graphics::graphics(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height=0;
    sd.BufferDesc.Format=DXGI_FORMAT_B8G8R8A8_UNORM;//or RGBA
    sd.BufferDesc.RefreshRate.Numerator=0;
    sd.BufferDesc.RefreshRate.Denominator=0;
    sd.BufferDesc.Scaling=DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering=DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count=0;
    sd.SampleDesc.Quality=1;
    sd.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount=1;
    sd.OutputWindow=hWnd;
    sd.Windowed=TRUE;
    sd.SwapEffect=DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags=0;
    auto ret=D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_SOFTWARE,
        nullptr, 0,
        nullptr, 0,
        D3D11_SDK_VERSION,
        &sd, &pSwap, &pDevice,
        nullptr, &pContext);
}