#pragma once

namespace esphome
{
    namespace shys_m5_dial
    {
        class HaDeviceModeshotTimerState: public esphome::shys_m5_dial::HaDeviceMode {
            protected:
                std::string hvac_mode = "none";

                std::string getHvacMode(){
                    return this->hvac_mode;
                }

                void setHvacMode(const std::string& newMode){
                    this->hvac_mode = newMode;
                }

                void sendValueToHomeAssistant(int value) override {
                    haApi.setClimateTemperature(this->device.getEntityId(), value);
                }

                void showshotTimerStateMenu(M5DialDisplay& display){
                    
                    LovyanGFX* gfx = display.getGfx();

                    int currentValue = getValue();
                    ESP_LOGD("DISPLAY", "showshotTimerStateMenu Function call");
                    uint16_t height = gfx->height();
                    uint16_t width  = gfx->width();

                    gfx->setTextColor(MAROON);
                    gfx->setTextDatum(middle_center);
                    
                    gfx->startWrite();                      // Secure SPI bus
                    //upper block
                    gfx->fillRect(0, 0, width, this->getDisplayPositionY(currentValue) , CYAN);
                    //lower block
                    gfx->fillRect(0, this->getDisplayPositionY(currentValue), width, height, ORANGE);
                    ESP_LOGD("DISPLAY", "-------------------------- ALL FINE now get device.name");
                    display.setFontsize(3);
                    gfx->drawString(String(currentValue).c_str(),
                                    width / 2,
                                    height / 2 - 30);                        
                    
                    display.setFontsize(1);
                    ESP_LOGD("DISPLAY", "-------------------------- STILL  ALL FINE now get device.name");
                    gfx->drawString(this->device.getName().c_str(),
                                    width / 2,
                                    height / 2 + 20);
                    ESP_LOGD("DISPLAY", "-------------------------- STILL ALL FINE 2 now get device.name");
                    gfx->drawString("shotTimer State",
                                    width / 2,
                                    height / 2 + 50);  


                    gfx->endWrite();                      // Release SPI bus
                }

            public:
                HaDeviceModeshotTimerState(HaDevice& device) : HaDeviceMode(device){
                    this->maxValue = 40;
                }

                void refreshDisplay(M5DialDisplay& display, bool init) override {
                    this->showshotTimerStateMenu(display);
                    ESP_LOGD("DISPLAY", "shotTimer State-Modus");
                }

                void registerHAListener() override {
                    std::string attrNameState = "MR022480 Shot timer";
                    api::global_api_server->subscribe_home_assistant_state(
                                this->device.getEntityId().c_str(),
                                attrNameState, 
                                [this](const std::string &state) {

                        if(this->isValueModified()){
                            return;
                        }
                        int newState = std::stoi(state.c_str());

                        this->setReceivedValue(newState);

                        //this->setHvacMode(state.c_str());
                        //This listener gets called
                        ESP_LOGI("HA_API", "Got shotTimer State Mode %s in int %i for %s", state.c_str(), int(state.c_str()), this->device.getEntityId().c_str());
                    });

                   
                   
                }           

        };
    }
}