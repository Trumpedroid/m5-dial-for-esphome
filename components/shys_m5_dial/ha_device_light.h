#pragma once
#include "ha_device.h"
#include "ha_device_mode_light_on_off.h"
#include "ha_device_mode_light_brightness.h"
#include "ha_device_mode_light_color.h"
#include "ha_device_mode_light_tunable_white.h"

namespace esphome
{
    namespace shys_m5_dial
    {
        class HaDeviceLight: public esphome::shys_m5_dial::HaDevice {
            protected:
                HaDeviceModeLightOnOff*             modeOnOff           = new HaDeviceModeLightOnOff(*this);
                HaDeviceModeLightBrightness*        modeBrightness      = new HaDeviceModeLightBrightness(*this);
                HaDeviceModeLightColor*             modeColor           = new HaDeviceModeLightColor(*this);
                HaDeviceModeLightTunableWhite*      modeTunableWhite    = new HaDeviceModeLightTunableWhite(*this);

            public:
                HaDeviceLight(const std::string& entity_id, const std::string& name, const std::string& modes) : HaDevice(entity_id, name, modes) {}

                void init() override {
                    ESP_LOGD("HA_DEVICE", "Init Light: %s", this->getEntityId().c_str());

                    bool brightnessModeActive = false;
                    JsonObject dimm_mode;
                    if (this->modeConfig.containsKey("dimm_mode")) {
                        dimm_mode = this->modeConfig["dimm_mode"];
                        if (dimm_mode.containsKey("enable") && dimm_mode["enable"].as<bool>()) {
                            brightnessModeActive = true;
                        }
                    }

                    if(brightnessModeActive){
                        ESP_LOGD("HA_DEVICE", "Dimm-Mode enabled");
                        modeBrightness->setRotaryStepWidth(dimm_mode["rotary_step_width"].as<int>());
                        this->addMode(modeBrightness);
                    } else {
                        this->addMode(modeOnOff);
                    }



                    if (this->modeConfig.containsKey("rgb_mode")) {
                        JsonObject rgb_mode = this->modeConfig["rgb_mode"];

                        if (rgb_mode.containsKey("enable") && rgb_mode["enable"].as<bool>()) {
                            modeColor->setRotaryStepWidth(rgb_mode["rotary_step_width"].as<int>());

                            this->addMode(modeColor);
                        }
                    }

                    if (this->modeConfig.containsKey("white_mode")) {
                        JsonObject white_mode = this->modeConfig["white_mode"];

                        if (white_mode.containsKey("enable") && white_mode["enable"].as<bool>()) {
                            modeTunableWhite->setRotaryStepWidth(white_mode["rotary_step_width"].as<int>());

                            this->addMode(modeTunableWhite);
                        }
                    }

                }

        };

    }
}