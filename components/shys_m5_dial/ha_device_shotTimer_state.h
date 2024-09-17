#pragma once
#include "ha_device.h"
#include "ha_device_mode_shotTimer_state.h"

namespace esphome
{
    namespace shys_m5_dial
    {
        class HaDeviceshotTimerState: public esphome::shys_m5_dial::HaDevice {
            protected:
                HaDeviceModeshotTimerState*             modeshotTimer           = new HaDeviceModeshotTimerState(*this);

            public:
                HaDeviceshotTimerState(const std::string& entity_id, const std::string& name, const std::string& modes) : HaDevice(entity_id, name, modes) {}

                void init() override {
                    ESP_LOGD("HA_DEVICE", "Init shotTimer: %s", this->getEntityId().c_str());

                    this->addMode(modeshotTimer);

                    if (this->modeConfig.containsKey("shotTimer_state_mode")) {
                        JsonObject shotTimer_mode = this->modeConfig["shotTimer_state_mode"];

                        if (shotTimer_mode.containsKey("rotary_step_width")) {
                            modeshotTimer->setRotaryStepWidth(shotTimer_mode["rotary_step_width"].as<int>());
                        }
                    }                    
                }

        };

    }
}