#pragma once
#include "ha_device.h"
#include "ha_device_mode_plantHappy.h"

namespace esphome
{
    namespace shys_m5_dial
    {
        class HaDevicePlantHappyState: public esphome::shys_m5_dial::HaDevice {
            protected:
                HaDeviceModePlantHappy*             modePlantHappy           = new HaDeviceModePlantHappy(*this);

            public:
                HaDevicePlantHappyState(const std::string& entity_id, const std::string& name, const std::string& modes) : HaDevice(entity_id, name, modes) {}

                void init() override {
                    ESP_LOGD("HA_DEVICE", "Init Plant Happy Mode: %s", this->getEntityId().c_str());

                    this->addMode(modePlantHappy);

                    if (this->modeConfig.containsKey("plantHappy_mode")) {
                        JsonObject plantHappy_mode = this->modeConfig["plantHappy_mode"];

                        if (plantHappy_mode.containsKey("rotary_step_width")) {
                            modePlantHappy->setRotaryStepWidth(plantHappy_mode["rotary_step_width"].as<int>());
                        }
                    }                    
                }

        };

    }
}