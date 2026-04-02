#include "spoutengage.h"
#include "spoutsender.h"
#include <iostream>
#include <d3d11.h>

class SpEnClass : public IGenPlugin {
private:

    IDataBus* data_bus;
    IEventManager* event_manager;
    std::string name = "Spout Engage. GPU textures transfer";

    std::deque<void*>* buf_ptr = nullptr;
    std::string active_back = "";
    std::any render_device;
    uintptr_t* window_handle_ptr = nullptr;

    SpoutSenderWrapper sender;
    bool spout_initialized = false;

    std::vector<std::function<void()>>* render_pipeline;
    std::function<void()> executable_function;
    bool has_started = false;

    std::string i_name = "SpoutEngage";

public:

    SpEnClass(IEventManager* eventManager, IDataBus* dataBus) {
        this->data_bus = dataBus;
        this->event_manager = eventManager;
        try { // трай-кетчи - неудобно
            auto a_render_pipeline = &data_bus->getData("render_pipeline"); // тут надо достать адрес на вектор в шине
            this->render_pipeline = std::any_cast<std::vector<std::function<void()>>>(a_render_pipeline);
        } catch (const char* e) {
            std::cerr << e;
        }

        this->event_manager->subscribe(i_name, "render_initialized", &SpEnClass::preStart, this);
    }

    ~SpEnClass() override {
    }

    void setDataBus(IDataBus* db) override {
        this->data_bus = db;
    }

    std::string getName() override {
        return this->name;
    }

    // момент по рефакторингу - классы и прочее можно вынести в классы так, чтобы start и update остался
    void preStart() {
        std::cout << "prestart 26" << std::endl;
        try {
            auto a_ren_back = data_bus->getData("render_backend");
            auto a_ren_dev = data_bus->getData("render_device");
            auto a_buf = data_bus->getData("frames_buffer");
            auto a_wnd = data_bus->getData("window_handle");

            active_back = *std::any_cast<std::string*>(a_ren_back);
            buf_ptr = std::any_cast<std::deque<void*>*>(a_buf);
            render_device = a_ren_dev;
            window_handle_ptr = std::any_cast<uintptr_t*>(a_wnd);
        } catch (...) {
            std::cerr << "SpoutEngage: Error obtaining data from bus.\n";
        }
        this->executable_function = [this]() {
            if (!this->has_started) {
                this->start();
                this->has_started = true;
            } else {
                this->update();
            }
        };
        render_pipeline->emplace_back(executable_function);
    }

    void start() {
        // Initialization is mostly lazy, because we need width and height from the first texture
        std::cout << "start 26" << std::endl;
    }

    void update() {
        // std::cout << "update 26" << std::endl;
        // std::cout << active_back << std::endl;
        // std::cout << !buf_ptr << std::endl;
        // std::cout << buf_ptr->empty() << std::endl;
        // std::cout << !window_handle_ptr << std::endl;

        if (!buf_ptr || buf_ptr->empty() || active_back != "dx11") return;

        void* texPtr = buf_ptr->back();
        buf_ptr->pop_back();
        if (!texPtr) return;


        ID3D11Texture2D* tex = static_cast<ID3D11Texture2D*>(texPtr);

        if (!spout_initialized) {
            D3D11_TEXTURE2D_DESC desc;
            tex->GetDesc(&desc);
            ID3D11Device* dev = static_cast<ID3D11Device*>(*std::any_cast<void**>(render_device));

            if (dev) {
                spout_initialized = sender.init(dev, desc.Width, desc.Height, "RCubiQ Spout Sender");
            }
        }


        if (spout_initialized) {
            sender.send(tex);
        }
    }

};


extern "C" __declspec(dllexport)
IGenPlugin* create(IEventManager* events, IDataBus* dbus) {
    return new SpEnClass(events, dbus);
}

extern "C" __declspec(dllexport)
void destroy(IGenPlugin* plugin) {
    delete plugin;
}
