#pragma once
#include "ha_device.h"
#include "ha_device_mode_plant_state.h"

namespace esphome
{
    namespace shys_m5_dial
    {
        class HaDevicePlantState: public esphome::shys_m5_dial::HaDevice {
            protected:
                HaDeviceModePlantState*             modePlant           = new HaDeviceModePlantState(*this);

            public:
                HaDevicePlantState(const std::string& entity_id, const std::string& name, const std::string& modes) : HaDevice(entity_id, name, modes) {}

                void init() override {
                    ESP_LOGD("HA_DEVICE", "Init Plant: %s", this->getEntityId().c_str());

                    this->addMode(modePlant);

                    if (this->modeConfig.containsKey("plant_state_mode")) {
                        JsonObject plant_mode = this->modeConfig["plant_state_mode"];

                        if (plant_mode.containsKey("rotary_step_width")) {
                            modePlant->setRotaryStepWidth(plant_mode["rotary_step_width"].as<int>());
                        }
                    }                    
                }

        };

    }
}