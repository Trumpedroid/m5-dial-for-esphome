import json

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID, CONF_NAME

# LIMITS
MAXICONS = 10


# PARAMETER
CONF_DEVICES                        = "devices"
CONF_DEVICE_ENTRY_ID                = "entity"
CONF_DEVICE_ENTRY_NAME              = "name"
CONF_DEVICE_MODES                   = "modes"

CONF_DEVICE_LIGHTS                  = "lights"
CONF_DEVICE_LIGHT_RGB_MODE          = "rgb_mode"
CONF_DEVICE_LIGHT_DIMM_MODE         = "dimm_mode"
CONF_DEVICE_LIGHT_WHITE_MODE        = "white_mode"


CONF_DEVICE_MODE_ENABLE             = "enable"
CONF_DEVICE_MODE_ROTARY_STEPWIDTH   = "rotary_step_width"

CONF_SCREEN_OFF_TIME                = "screen_off_time"
CONF_LONG_PRESS_DURATION            = "long_press_duration"
CONF_SEND_VALUE_DELAY               = "send_value_delay"
CONF_RECEIVE_VALUE_DELAY            = "receive_value_delay"
CONF_ROTARY_STEP_WIDTH              = "rotary_step_width"


# DEFAULTS
DEFAULT_NAME                = "M5 Stack Dial"
DEFAULT_SCREEN_OFF_TIME     = 30000
DEFAULT_LONG_PRESS_DURATION = 1200
DEFAULT_SEND_VALUE_DELAY    = 1200
DEFAULT_RECEIVE_VALUE_DELAY = 3000
DEFAULT_ROTARY_STEP_WIDTH   = 10


shys_m5_dial_ns = cg.esphome_ns.namespace('shys_m5_dial')
ShysM5Dial = shys_m5_dial_ns.class_('ShysM5Dial', cg.Component)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ShysM5Dial),
    cv.Optional(CONF_NAME, default=DEFAULT_NAME): cv.string,

    cv.Optional(CONF_SCREEN_OFF_TIME, default=DEFAULT_SCREEN_OFF_TIME): cv.int_range(0, 999999),
    cv.Optional(CONF_LONG_PRESS_DURATION, default=DEFAULT_LONG_PRESS_DURATION): cv.int_range(0, 5000),
    cv.Optional(CONF_SEND_VALUE_DELAY, default=DEFAULT_SEND_VALUE_DELAY): cv.int_range(0, 999999),
    cv.Optional(CONF_RECEIVE_VALUE_DELAY, default=DEFAULT_RECEIVE_VALUE_DELAY): cv.int_range(0, 999999),
    cv.Optional(CONF_ROTARY_STEP_WIDTH, default=DEFAULT_ROTARY_STEP_WIDTH): cv.int_range(0, 100),


    cv.Optional(CONF_DEVICES, default=dict()): cv.All(dict({
    
        cv.Optional(CONF_DEVICE_LIGHTS, default=[]): cv.All([dict({
            cv.Required(CONF_DEVICE_ENTRY_ID): cv.string,
            cv.Required(CONF_DEVICE_ENTRY_NAME): cv.string,

            cv.Optional(CONF_DEVICE_MODES, default=dict()): cv.All(dict({
                cv.Optional(CONF_DEVICE_LIGHT_RGB_MODE, default=dict()): cv.All(dict({
                    cv.Optional(CONF_DEVICE_MODE_ENABLE, default=False): cv.boolean,
                    cv.Optional(CONF_DEVICE_MODE_ROTARY_STEPWIDTH, default=20): cv.int_range(1, 100)
                })),

                cv.Optional(CONF_DEVICE_LIGHT_DIMM_MODE, default=dict()): cv.All(dict({
                    cv.Optional(CONF_DEVICE_MODE_ENABLE, default=False): cv.boolean,
                    cv.Optional(CONF_DEVICE_MODE_ROTARY_STEPWIDTH, default=10): cv.int_range(1, 100)
                })),
                
                cv.Optional(CONF_DEVICE_LIGHT_WHITE_MODE, default=dict()): cv.All(dict({
                    cv.Optional(CONF_DEVICE_MODE_ENABLE, default=False): cv.boolean,
                    cv.Optional(CONF_DEVICE_MODE_ROTARY_STEPWIDTH, default=100): cv.int_range(1, 500)
                }))
            }))
        })])

    }))


}).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    if CONF_SCREEN_OFF_TIME in config:
        screenOffTime = config[CONF_SCREEN_OFF_TIME]
        cg.add(var.setScreenOffTime(screenOffTime))

    if CONF_LONG_PRESS_DURATION in config:
        longPressDuration = config[CONF_LONG_PRESS_DURATION]
        cg.add(var.setLongPressDuration(longPressDuration))

    if CONF_SEND_VALUE_DELAY in config:
        sendValueDelay = config[CONF_SEND_VALUE_DELAY]
        cg.add(var.setSendValueDelay(sendValueDelay))

    if CONF_RECEIVE_VALUE_DELAY in config:
        receiveValuedelay = config[CONF_RECEIVE_VALUE_DELAY]
        cg.add(var.setReceiveValueDelay(receiveValuedelay))

    if CONF_ROTARY_STEP_WIDTH in config:
        rotaryStepWidth = config[CONF_ROTARY_STEP_WIDTH]
        cg.add(var.setRotaryStepWidth(rotaryStepWidth))

    if CONF_DEVICES in config:
        confDevices = config[CONF_DEVICES]

        if CONF_DEVICE_LIGHTS in confDevices:
            confLights = confDevices[CONF_DEVICE_LIGHTS]
            for lightEntry in confLights:
                cg.add(var.addLight(lightEntry[CONF_DEVICE_ENTRY_ID], 
                                    lightEntry[CONF_DEVICE_ENTRY_NAME], 
                                    json.dumps(lightEntry[CONF_DEVICE_MODES])
                                    ))

