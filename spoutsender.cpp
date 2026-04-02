#include "spoutsender.h"

#ifdef WIN32
#if defined(USE_SPOUT_DX) || defined(USE_SPOUT_DX12) || defined(USE_SPOUT_DX9)
#include <d3d11.h>
#include "SpoutDX/SpoutDX.h"
#elif defined(USE_SPOUT_GL)
#include <GL/gl.h>
#include "SpoutGL/Spout.h"
#endif
#include <iostream>
#endif

SpoutSenderWrapper::SpoutSenderWrapper() {
#if !defined(WIN32) || !(defined(USE_SPOUT_DX) || defined(USE_SPOUT_DX12) || defined(USE_SPOUT_DX9) || defined(USE_SPOUT_GL))
    std::cout << "Not able to create Spout sender: not Windows or no Spout backend enabled.\n";
#endif
}

SpoutSenderWrapper::~SpoutSenderWrapper()
{
#if defined(WIN32) && (defined(USE_SPOUT_DX) || defined(USE_SPOUT_DX12) || defined(USE_SPOUT_DX9) || defined(USE_SPOUT_GL))
    shutdown();
#endif
}

#if defined(WIN32) && (defined(USE_SPOUT_DX) || defined(USE_SPOUT_DX12) || defined(USE_SPOUT_DX9) || defined(USE_SPOUT_GL))

bool SpoutSenderWrapper::init(ID3D11Device* device,
                              int w,
                              int h,
                              const std::string& name)
{

    width = w;
    height = h;

    sender.OpenDirectX11(device);
    sender.SetSenderName("RCubiQWSender");

    initialized = true;
    return true;
}

void SpoutSenderWrapper::send(ID3D11Texture2D* texture)
{
    if (!initialized || !texture) {
        return;
    }

    if (!sender.SendTexture(texture)) {
        std::cerr << "SpoutSenderWrapper: Failed to send texture.\n";
    }
}

void SpoutSenderWrapper::shutdown()
{
    if (initialized) {
        sender.ReleaseSender();

        initialized = false;
        device = nullptr;
        width = 0;
        height = 0;
    }
}

#endif // WIN32 && SPOUT_BACKENDS
