#include "spoutengage.h"

class SpEnClass : public IGenPlugin {
private:

    IDataBus* data_bus;
    std::string name = "Spout Engage. GPU textures transfer";

    std::deque<void*> buf;
    std::string active_back = "";
    std::any render_device;

public:

    SpEnClass() {
    }

    ~SpEnClass() override {
    }

    void setDataBus(IDataBus* db) override {
        this->data_bus = db;
        try {
        auto a_ren_back = data_bus->getData("render_backend");
        auto a_ren_dev = data_bus->getData("render_device");
        auto a_buf = data_bus->getData("frames_buffer");
        active_back = std::any_cast<std::string>(a_ren_back);
        buf = std::any_cast<std::deque<void*>>(a_buf);
        render_device = a_ren_dev;
        } catch (...) {

        }
    }

    std::string getName() override {
        return this->name;
    }

};

extern "C" __declspec(dllexport)
IGenPlugin* create() {
    return new SpEnClass();
}

extern "C" __declspec(dllexport)
void destroy(IGenPlugin* plugin) {
    delete plugin;
}
