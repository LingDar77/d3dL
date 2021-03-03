#ifndef C894AFEB_B47C_4A36_BC68_FFE66EAF2D47
#define C894AFEB_B47C_4A36_BC68_FFE66EAF2D47
#include <d3d11.h>
#include "window.h"
class graphics
{
private:
    ID3D11Device *pDevice = nullptr;
    IDXGISwapChain *pSwap = nullptr;
    ID3D11DeviceContext *pContext = nullptr;
public:
    graphics(HWND hWnd);
    graphics(const graphics &) = delete;
    graphics &operator==(const graphics &) = delete;
    ~graphics() noexcept
    {
        if (pDevice!=nullptr)
            pDevice->Release();
        if (pSwap!=nullptr)
            pSwap->Release();
        if (pContext!=nullptr)
            pContext->Release();
    }
};

#endif /* C894AFEB_B47C_4A36_BC68_FFE66EAF2D47 */
