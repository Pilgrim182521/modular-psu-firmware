/*
 * EEZ Modular Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <float.h>
#include <assert.h>

#include <eez/modules/psu/psu.h>
#include <eez/modules/psu/calibration.h>
#include <eez/modules/psu/channel_dispatcher.h>
#include <eez/modules/psu/event_queue.h>
#include <eez/modules/psu/list_program.h>
#include <eez/modules/psu/gui/psu.h>
#include <eez/scpi/regs.h>
#include <eez/modules/psu/temperature.h>
#include <eez/modules/psu/trigger.h>
#include <eez/index.h>
#include <eez/system.h>
#include <eez/modules/bp3c/io_exp.h>

namespace eez {
namespace psu {
namespace channel_dispatcher {

static CouplingType g_couplingType = COUPLING_TYPE_NONE;

CouplingType getCouplingType() {
    return g_couplingType;
}

bool isTrackingAllowed(Channel &channel, int *err) {
    if (!channel.isOk()) {
        if (err) {
            *err = SCPI_ERROR_HARDWARE_ERROR;
        }
        return false;
    }

    if (CH_NUM < 2) {
        if (err) {
            *err = SCPI_ERROR_HARDWARE_MISSING;
        }
        return false;
    }

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        if (err) {
            *err = SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED;
        }
        return false;
    }

    return true;
}

bool isCouplingTypeAllowed(CouplingType couplingType, int *err) {
    if (couplingType == COUPLING_TYPE_NONE) {
        return true;
    }

    if (couplingType == COUPLING_TYPE_COMMON_GND) {
        int n = 0;

        for (int i = 0; i < CH_NUM; i++) {
            Channel &channel = Channel::get(i);
            if (channel.isOk() && channel.subchannelIndex == 0) {
                n++;
            }
        }

        if (n < 2) {
            if (err) {
                *err = SCPI_ERROR_HARDWARE_ERROR;
            }
            return false;
        }
    } else {
        if (CH_NUM < 2) {
            if (err) {
                *err = SCPI_ERROR_HARDWARE_MISSING;
            }
            return false;
        }

        if (
            !Channel::get(0).isOk() || 
            !(Channel::get(0).params.features & CH_FEATURE_COUPLING) || 
            !Channel::get(1).isOk() ||
            !(Channel::get(1).params.features & CH_FEATURE_COUPLING)
        ) {
            if (err) {
                *err = SCPI_ERROR_HARDWARE_ERROR;
            }
            return false;
        }
    }

    return true;
}

bool setCouplingType(CouplingType couplingType, int *err) {
    if (g_couplingType != couplingType) {
        if (!isCouplingTypeAllowed(couplingType, err)) {
            return false;
        }

        if (osThreadGetId() != g_psuTaskHandle) {
            osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_SET_COUPLING_TYPE, couplingType), osWaitForever);
        } else {
            setCouplingTypeInPsuThread(couplingType);
        }
    }

    return true;
}

void setCouplingTypeInPsuThread(CouplingType couplingType) {
    trigger::abort();

    g_couplingType = couplingType;

    disableOutputForAllChannels();

    for (int i = 0; i < 2; ++i) {
        Channel &channel = Channel::get(i);

        channel.remoteSensingEnable(false);
        channel.remoteProgrammingEnable(false);

        channel.setVoltageTriggerMode(TRIGGER_MODE_FIXED);
        channel.setCurrentTriggerMode(TRIGGER_MODE_FIXED);
        channel.setTriggerOutputState(true);
        channel.setTriggerOnListStop(TRIGGER_ON_LIST_STOP_OUTPUT_OFF);

        list::resetChannelList(channel);

        channel.setVoltage(getUMin(channel));
        channel.setVoltageLimit(MIN(Channel::get(0).getVoltageLimit(), Channel::get(1).getVoltageLimit()));

        channel.setCurrent(getIMin(channel));
        channel.setCurrentLimit(MIN(Channel::get(0).getCurrentLimit(), Channel::get(1).getCurrentLimit()));

        channel.u.triggerLevel = getUMin(channel);
        channel.i.triggerLevel = getIMin(channel);

        channel.prot_conf.flags.u_state = Channel::get(0).prot_conf.flags.u_state || Channel::get(1).prot_conf.flags.u_state ? 1 : 0;
        if (channel.params.features & CH_FEATURE_HW_OVP) {
            channel.prot_conf.flags.u_type = Channel::get(0).prot_conf.flags.u_type || Channel::get(1).prot_conf.flags.u_type ? 1 : 0;
        }
        channel.prot_conf.u_level = MIN(Channel::get(0).prot_conf.u_level, Channel::get(1).prot_conf.u_level);
        channel.prot_conf.u_delay = MIN(Channel::get(0).prot_conf.u_delay, Channel::get(1).prot_conf.u_delay);

        channel.prot_conf.flags.i_state = Channel::get(0).prot_conf.flags.i_state || Channel::get(1).prot_conf.flags.i_state ? 1 : 0;
        channel.prot_conf.i_delay = MIN(Channel::get(0).prot_conf.i_delay, Channel::get(1).prot_conf.i_delay);

        channel.prot_conf.flags.p_state = Channel::get(0).prot_conf.flags.p_state || Channel::get(1).prot_conf.flags.p_state ? 1 : 0;
        channel.prot_conf.p_level = MIN(Channel::get(0).prot_conf.p_level, Channel::get(1).prot_conf.p_level);
        channel.prot_conf.p_delay = MIN(Channel::get(0).prot_conf.p_delay, Channel::get(1).prot_conf.p_delay);

        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.state = temperature::sensors[temp_sensor::CH1].prot_conf.state || temperature::sensors[temp_sensor::CH2].prot_conf.state ? 1 : 0;
        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.level = MIN(temperature::sensors[temp_sensor::CH1].prot_conf.level, temperature::sensors[temp_sensor::CH2].prot_conf.level);
        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.delay = MIN(temperature::sensors[temp_sensor::CH1].prot_conf.delay, temperature::sensors[temp_sensor::CH2].prot_conf.delay);

        if (i == 1) {
            Channel &channel1 = Channel::get(0);
            channel.flags.displayValue1 = channel1.flags.displayValue1;
            channel.flags.displayValue2 = channel1.flags.displayValue2;
            channel.ytViewRate = channel1.ytViewRate;

            channel.u.rampDuration = channel1.u.rampDuration;
        }

        channel.setCurrentRangeSelectionMode(CURRENT_RANGE_SELECTION_USE_BOTH);
        channel.enableAutoSelectCurrentRange(false);

        channel.flags.trackingEnabled = false;

        channel.resetHistory();
    }

    if (g_couplingType == COUPLING_TYPE_PARALLEL || g_couplingType == COUPLING_TYPE_SERIES) {
        if (persist_conf::getMaxChannelIndex() ==  1) {
            persist_conf::setMaxChannelIndex(0);
        }
    }

    bp3c::io_exp::switchChannelCoupling(g_couplingType);

    if (g_couplingType == COUPLING_TYPE_PARALLEL) {
        event_queue::pushEvent(event_queue::EVENT_INFO_COUPLED_IN_PARALLEL);
    } else if (g_couplingType == COUPLING_TYPE_SERIES) {
        event_queue::pushEvent(event_queue::EVENT_INFO_COUPLED_IN_SERIES);
    } else if (g_couplingType == COUPLING_TYPE_COMMON_GND) {
        event_queue::pushEvent(event_queue::EVENT_INFO_COUPLED_IN_COMMON_GND);
    } else if (g_couplingType == COUPLING_TYPE_SPLIT_RAILS) {
        event_queue::pushEvent(event_queue::EVENT_INFO_COUPLED_IN_SPLIT_RAILS);
    } else {
        event_queue::pushEvent(event_queue::EVENT_INFO_CHANNELS_UNCOUPLED);
    }

    setOperBits(OPER_GROUP_PARALLEL, g_couplingType == COUPLING_TYPE_PARALLEL);
    setOperBits(OPER_GROUP_SERIAL, g_couplingType == COUPLING_TYPE_SERIES);
    setOperBits(OPER_GROUP_COMMON_GND, g_couplingType == COUPLING_TYPE_COMMON_GND);
    setOperBits(OPER_GROUP_SPLIT_RAILS, g_couplingType == COUPLING_TYPE_SPLIT_RAILS);

    delay(100); // Huge pause that allows relay contacts to debounce
}

void setTrackingChannels(uint16_t trackingEnabled) {
    if (osThreadGetId() != g_psuTaskHandle) {
        osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_SET_TRACKING_CHANNELS, trackingEnabled), osWaitForever);
    } else {
        bool resetTrackingChannels = false;
        for (int i = 0; i < CH_NUM; i++) {
            Channel &trackingChannel = Channel::get(i);
            unsigned wasEnabled = trackingChannel.flags.trackingEnabled;
            trackingChannel.flags.trackingEnabled = (trackingEnabled & (1 << i)) ? 1 : 0;
            if (!wasEnabled && trackingChannel.flags.trackingEnabled) {
                resetTrackingChannels = true;
            }
        }

        if (resetTrackingChannels) {
            event_queue::pushEvent(event_queue::EVENT_INFO_CHANNELS_TRACKED);

            trigger::abort();

            float uMin = 0;
            float iMin = 0;

            float voltageLimit = FLT_MAX;
            float currentLimit = FLT_MAX;

            float uDef = FLT_MAX;
            float iDef = FLT_MAX;

            int u_state = 0;
            int u_type = 0;
            float u_level = FLT_MAX;
            float u_delay = FLT_MAX;

            int i_state = 0;
            float i_delay = FLT_MAX;

            int p_state = 0;
            float p_level = FLT_MAX;
            float p_delay = FLT_MAX;

            int t_state = 0;
            float t_level = FLT_MAX;
            float t_delay = FLT_MAX;

            for (int i = 0; i < CH_NUM; i++) {
                Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    uMin = MAX(uMin, getUMin(trackingChannel));
                    iMin = MAX(iMin, getIMin(trackingChannel));
                    
                    voltageLimit = MIN(voltageLimit, trackingChannel.getVoltageLimit());
                    currentLimit = MIN(currentLimit, trackingChannel.getCurrentLimit());
                    
                    uDef = MIN(uDef, trackingChannel.u.def);
                    iDef = MIN(iDef, trackingChannel.i.def);

                    if (trackingChannel.prot_conf.flags.u_state) {
                        u_state = 1;
                    }
                    if (trackingChannel.prot_conf.flags.u_type) {
                        u_type = 1;
                    }
                    u_level = MIN(u_level, trackingChannel.prot_conf.u_level);
                    u_delay = MIN(u_delay, trackingChannel.prot_conf.u_delay);

                    if (trackingChannel.prot_conf.flags.i_state) {
                        i_state = 1;
                    }
                    i_delay = MIN(i_delay, trackingChannel.prot_conf.i_delay);

                    if (trackingChannel.prot_conf.flags.p_state) {
                        p_state = 1;
                    }
                    p_level = MIN(p_level, trackingChannel.prot_conf.p_level);
                    p_delay = MIN(p_delay, trackingChannel.prot_conf.p_delay);

                    if (temperature::sensors[temp_sensor::CH1 + i].prot_conf.state) {
                        t_state = 1;
                    }
                    t_level = MIN(t_level, temperature::sensors[temp_sensor::CH1 + i].prot_conf.level);
                    t_delay = MIN(t_delay, temperature::sensors[temp_sensor::CH1 + i].prot_conf.delay);
                }
            }

            disableOutputForAllTrackingChannels();

            for (int i = 0; i < CH_NUM; i++) {
                Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    trackingChannel.remoteSensingEnable(false);
                    trackingChannel.remoteProgrammingEnable(false);

                    trackingChannel.setVoltageTriggerMode(TRIGGER_MODE_FIXED);
                    trackingChannel.setCurrentTriggerMode(TRIGGER_MODE_FIXED);
                    trackingChannel.setTriggerOutputState(true);
                    trackingChannel.setTriggerOnListStop(TRIGGER_ON_LIST_STOP_OUTPUT_OFF);

                    list::resetChannelList(trackingChannel);

                    trackingChannel.setVoltage(MAX(uMin, getUMin(trackingChannel)));
                    trackingChannel.setVoltageLimit(MAX(voltageLimit, getUMin(trackingChannel)));

                    trackingChannel.setCurrent(MAX(iMin, getIMin(trackingChannel)));
                    trackingChannel.setCurrentLimit(MAX(currentLimit, getIMin(trackingChannel)));

                    trackingChannel.u.triggerLevel = uDef;
                    trackingChannel.i.triggerLevel = iDef;

                    trackingChannel.prot_conf.flags.u_state = u_state;
                    if (trackingChannel.params.features & CH_FEATURE_HW_OVP) {
                        trackingChannel.prot_conf.flags.u_type = u_type;
                    }
                    trackingChannel.prot_conf.u_level = u_level;
                    trackingChannel.prot_conf.u_delay = u_delay;

                    trackingChannel.prot_conf.flags.i_state = i_state;
                    trackingChannel.prot_conf.i_delay = i_delay;

                    trackingChannel.prot_conf.flags.p_state = p_state;
                    trackingChannel.prot_conf.p_level = p_level;
                    trackingChannel.prot_conf.p_delay = p_delay;

                    temperature::sensors[temp_sensor::CH1 + i].prot_conf.state = t_state;
                    temperature::sensors[temp_sensor::CH1 + i].prot_conf.level = t_level;
                    temperature::sensors[temp_sensor::CH1 + i].prot_conf.delay = t_delay;

                    trackingChannel.u.rampDuration = RAMP_DURATION_DEF_VALUE;

                    trackingChannel.i.rampDuration = RAMP_DURATION_DEF_VALUE;

                    trackingChannel.resetHistory();
                }
            }
        }
    }
}

CouplingType getType() {
    return g_couplingType;
}

////////////////////////////////////////////////////////////////////////////////

float getTrackingValuePrecision(Unit unit, float value) {
    float precision = 0;
    for (int i = 0; i < CH_NUM; ++i) {
        Channel &trackingChannel = Channel::get(i);
        if (trackingChannel.flags.trackingEnabled) {
            precision = MAX(precision, trackingChannel.getValuePrecision(unit, value));
        }
    }
    return precision;
}

float roundTrackingValuePrecision(Unit unit, float value) {
    return roundPrec(value, getTrackingValuePrecision(unit, value));
}

float getValuePrecision(const Channel &channel, Unit unit, float value) {
    if (channel.flags.trackingEnabled) {
        return getTrackingValuePrecision(unit, value);
    }
    return channel.getValuePrecision(unit, value);
}

float roundChannelValue(const Channel &channel, Unit unit, float value) {
    return roundPrec(value, getValuePrecision(channel, unit, value));
}

float getUSet(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.set + Channel::get(1).u.set;
    }
    return channel.u.set;
}

float getUSetUnbalanced(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).getUSetUnbalanced() + Channel::get(1).getUSetUnbalanced();
    }
    return channel.u.set;
}

float getUMon(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.mon + Channel::get(1).u.mon;
    }
    return channel.u.mon;
}

float getUMonLast(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.mon_last + Channel::get(1).u.mon_last;
    }
    return channel.u.mon_last;
}

float getUMonDac(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.mon_dac + Channel::get(1).u.mon_dac;
    }
    return channel.u.mon_dac;
}

float getUMonDacLast(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.mon_dac_last + Channel::get(1).u.mon_dac_last;
    }
    return channel.u.mon_dac_last;
}

float getULimit(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return 2 * MIN(Channel::get(0).getVoltageLimit(), Channel::get(1).getVoltageLimit());
    }
    return channel.getVoltageLimit();
}

float getUMaxLimit(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return 2 * MIN(Channel::get(0).getVoltageMaxLimit(), Channel::get(1).getVoltageMaxLimit());
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return MIN(Channel::get(0).getVoltageMaxLimit(), Channel::get(1).getVoltageMaxLimit());
    } else if (channel.flags.trackingEnabled) {
        float value = channel.getVoltageMaxLimit();
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MIN(value, trackingChannel.getVoltageMaxLimit());
                }
            }
        }
        return value;
    }
    return channel.getVoltageMaxLimit();
}

float getUMin(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return 2 * MAX(Channel::get(0).u.min, Channel::get(1).u.min);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return MAX(Channel::get(0).u.min, Channel::get(1).u.min);
    } else if (channel.flags.trackingEnabled) {
        float value = channel.u.min;
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MAX(value, trackingChannel.u.min);
                }
            }
        }
        return value;
    }
    return channel.u.min;
}

float getUDef(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).u.def + Channel::get(1).u.def;
    }
    return channel.u.def;
}

float getUMax(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return 2 * MIN(Channel::get(0).u.max, Channel::get(1).u.max);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return MIN(Channel::get(0).u.max, Channel::get(1).u.max);
    } else if (channel.flags.trackingEnabled) {
        float value = channel.u.max;
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MIN(value, trackingChannel.u.max);
                }
            }
        }
        return value;
    }
    return channel.u.max;
}

float getUMaxOvpLimit(const Channel &channel) {
    if (channel.flags.rprogEnabled) {
        return getUMax(channel) + 0.5f;    
    }
    return getUMax(channel);
}

float getUMaxOvpLevel(const Channel &channel) {
    return getUMax(channel) + 0.5f;
}

float getUProtectionLevel(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return Channel::get(0).prot_conf.u_level + Channel::get(1).prot_conf.u_level;
    }
    return channel.prot_conf.u_level;
}

static float g_setVoltageValues[CH_MAX];

void setVoltageInPsuThread(int channelIndex) {
    setVoltage(Channel::get(channelIndex), g_setVoltageValues[channelIndex]);
}

void setVoltage(Channel &channel, float voltage) {
    if (osThreadGetId() != g_psuTaskHandle) {
        g_setVoltageValues[channel.channelIndex] = voltage;
        osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_MESSAGE_TYPE_SET_VOLTAGE, channel.channelIndex), osWaitForever);
        return;
    }

    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        Channel::get(0).setVoltage(voltage / 2);
        Channel::get(1).setVoltage(voltage / 2);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        Channel::get(0).setVoltage(voltage);
        Channel::get(1).setVoltage(voltage);
    } else if (channel.flags.trackingEnabled) {
        voltage = roundTrackingValuePrecision(UNIT_VOLT, voltage);

        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setVoltage(voltage);
            }
        }
    } else {
        channel.setVoltage(voltage);
    }
}

void setVoltageStep(Channel &channel, float voltageStep) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).u.step = voltageStep;
        Channel::get(1).u.step = voltageStep;
    } else if (channel.flags.trackingEnabled) {
        voltageStep = roundTrackingValuePrecision(UNIT_VOLT, voltageStep);

        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.u.step = voltageStep;
            }
        }
    } else {
        channel.u.step = voltageStep;
    }
}

void setVoltageLimit(Channel &channel, float limit) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        Channel::get(0).setVoltageLimit(limit / 2);
        Channel::get(1).setVoltageLimit(limit / 2);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        Channel::get(0).setVoltageLimit(limit);
        Channel::get(1).setVoltageLimit(limit);
    } else if (channel.flags.trackingEnabled) {
        limit = roundTrackingValuePrecision(UNIT_VOLT, limit);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setVoltageLimit(limit);
            }
        }
    } else {
        channel.setVoltageLimit(limit);
    }
}

void setOvpParameters(Channel &channel, int state, int type, float level, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        float coupledLevel = g_couplingType == COUPLING_TYPE_SERIES ? level / 2 : level;

        coupledLevel = roundPrec(coupledLevel, Channel::get(0).getVoltageResolution());

        Channel::get(0).prot_conf.flags.u_state = state;
        if (Channel::get(0).params.features & CH_FEATURE_HW_OVP) {
            Channel::get(0).prot_conf.flags.u_type = type;
        }
        Channel::get(0).prot_conf.u_level = coupledLevel;
        Channel::get(0).prot_conf.u_delay = delay;

        Channel::get(1).prot_conf.flags.u_state = state;
        if (Channel::get(1).params.features & CH_FEATURE_HW_OVP) {
            Channel::get(1).prot_conf.flags.u_type = type;
        }
        Channel::get(1).prot_conf.u_level = coupledLevel;
        Channel::get(1).prot_conf.u_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        level = roundTrackingValuePrecision(UNIT_VOLT, level);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.u_state = state;
                if (trackingChannel.params.features & CH_FEATURE_HW_OVP) {
                    trackingChannel.prot_conf.flags.u_type = type;
                }
                trackingChannel.prot_conf.u_level = level;
                trackingChannel.prot_conf.u_delay = delay;
            }
        }
    } else {
        channel.prot_conf.flags.u_state = state;
        if (channel.params.features & CH_FEATURE_HW_OVP) {
            channel.prot_conf.flags.u_type = type;
        }
        channel.prot_conf.u_level = roundPrec(level, channel.getVoltageResolution());
        channel.prot_conf.u_delay = delay;
    }
}

void setOvpState(Channel &channel, int state) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.flags.u_state = state;
        Channel::get(1).prot_conf.flags.u_state = state;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.u_state = state;
            }
        }
    } else {
        channel.prot_conf.flags.u_state = state;
    }
}

void setOvpType(Channel &channel, int type) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        if (Channel::get(0).params.features & CH_FEATURE_HW_OVP) {
            Channel::get(0).prot_conf.flags.u_type = type;
        }
        if (Channel::get(1).params.features & CH_FEATURE_HW_OVP) {
            Channel::get(1).prot_conf.flags.u_type = type;
        }
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.params.features & CH_FEATURE_HW_OVP) {
                if (trackingChannel.flags.trackingEnabled) {
                    trackingChannel.prot_conf.flags.u_type = type;
                }
            }
        }
    } else {
        if (channel.params.features & CH_FEATURE_HW_OVP) {
            channel.prot_conf.flags.u_type = type;
        }
    }
}

void setOvpLevel(Channel &channel, float level) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        float coupledLevel = g_couplingType == COUPLING_TYPE_SERIES ? level / 2 : level;
        coupledLevel = roundPrec(coupledLevel, Channel::get(0).getVoltageResolution());
        Channel::get(0).prot_conf.u_level = coupledLevel;
        Channel::get(1).prot_conf.u_level = coupledLevel;
    } else if (channel.flags.trackingEnabled) {
        level = roundTrackingValuePrecision(UNIT_VOLT, level);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.u_level = level;
            }
        }
    } else {
        channel.prot_conf.u_level = roundPrec(level, channel.getVoltageResolution());
    }
}

void setOvpDelay(Channel &channel, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.u_delay = delay;
        Channel::get(1).prot_conf.u_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.u_delay = delay;
            }
        }
    } else {
        channel.prot_conf.u_delay = delay;
    }
}

float getISet(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).i.set + Channel::get(1).i.set;
    }
    return channel.i.set;
}

float getISetUnbalanced(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).getISetUnbalanced() + Channel::get(1).getISetUnbalanced();
    }
    return channel.i.set;
}

float getIMon(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).i.mon + Channel::get(1).i.mon;
    }
    return channel.i.mon;
}

float getIMonLast(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).i.mon_last + Channel::get(1).i.mon_last;
    }
    return channel.i.mon_last;
}

float getIMonDac(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).i.mon_dac + Channel::get(1).i.mon_dac;
    }
    return channel.i.mon_dac;
}

float getILimit(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return 2 * MIN(Channel::get(0).getCurrentLimit(), Channel::get(1).getCurrentLimit());
    }
    return channel.getCurrentLimit();
}

float getIMaxLimit(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return 2 * MIN(Channel::get(0).getMaxCurrentLimit(), Channel::get(1).getMaxCurrentLimit());
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return MIN(Channel::get(0).getMaxCurrentLimit(), Channel::get(1).getMaxCurrentLimit());
    } else if (channel.flags.trackingEnabled) {
        float value = channel.getMaxCurrentLimit();
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MIN(value, trackingChannel.getMaxCurrentLimit());
                }
            }
        }
        return value;
    }
    return channel.getMaxCurrentLimit();
}

float getIMin(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return 2 * MAX(Channel::get(0).i.min, Channel::get(1).i.min);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return MAX(Channel::get(0).i.min, Channel::get(1).i.min);
    } else if (channel.flags.trackingEnabled) {
        float value = channel.i.min;
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MAX(value, trackingChannel.i.min);
                }
            }
        }
        return value;
    }
    return channel.i.min;
}

float getIDef(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return Channel::get(0).i.def + Channel::get(1).i.def;
    }
    return channel.i.def;
}

float getIMax(const Channel &channel) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        return 2 * MIN(Channel::get(0).i.max, Channel::get(1).i.max);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        return MIN(Channel::get(0).i.max, Channel::get(1).i.max);
    } else if (channel.flags.trackingEnabled) {
        float value = channel.i.max;
        for (int i = 0; i < CH_NUM; ++i) {
            if (i != channel.channelIndex) {
                const Channel &trackingChannel = Channel::get(i);
                if (trackingChannel.flags.trackingEnabled) {
                    value = MIN(value, trackingChannel.i.max);
                }
            }
        }
        return value;
    }
    return channel.i.max;
}

static float g_setCurrentValues[CH_MAX];

void setCurrentInPsuThread(int channelIndex) {
    setCurrent(Channel::get(channelIndex), g_setCurrentValues[channelIndex]);
}

void setCurrent(Channel &channel, float current) {
    if (osThreadGetId() != g_psuTaskHandle) {
        g_setCurrentValues[channel.channelIndex] = current;
        osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_MESSAGE_TYPE_SET_CURRENT, channel.channelIndex), osWaitForever);
        return;
    }

    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        Channel::get(0).setCurrent(current / 2);
        Channel::get(1).setCurrent(current / 2);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        Channel::get(0).setCurrent(current);
        Channel::get(1).setCurrent(current);
    } else if (channel.flags.trackingEnabled) {
        current = roundTrackingValuePrecision(UNIT_AMPER, current);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setCurrent(current);
            }
        }
    } else {
        channel.setCurrent(current);
    }
}

void setCurrentStep(Channel &channel, float currentStep) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).i.step = currentStep;
        Channel::get(1).i.step = currentStep;
    } else if (channel.flags.trackingEnabled) {
        currentStep = roundTrackingValuePrecision(UNIT_AMPER, currentStep);

        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.i.step = currentStep;
            }
        }
    } else {
        channel.i.step = currentStep;
    }
}

void setCurrentLimit(Channel &channel, float limit) {
    if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_PARALLEL) {
        Channel::get(0).setCurrentLimit(limit / 2);
        Channel::get(1).setCurrentLimit(limit / 2);
    } else if (channel.channelIndex < 2 && g_couplingType == COUPLING_TYPE_SERIES) {
        Channel::get(0).setCurrentLimit(limit);
        Channel::get(1).setCurrentLimit(limit);
    } else if (channel.flags.trackingEnabled) {
        limit = roundTrackingValuePrecision(UNIT_AMPER, limit);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setCurrentLimit(limit);
            }
        }
    } else {
        channel.setCurrentLimit(limit);
    }
}

void setOcpParameters(Channel &channel, int state, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.flags.i_state = state;
        Channel::get(0).prot_conf.i_delay = delay;

        Channel::get(1).prot_conf.flags.i_state = state;
        Channel::get(1).prot_conf.i_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.i_state = state;
                trackingChannel.prot_conf.i_delay = delay;
            }
        }
    } else {
        channel.prot_conf.flags.i_state = state;
        channel.prot_conf.i_delay = delay;
    }
}

void setOcpState(Channel &channel, int state) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.flags.i_state = state;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.i_state = state;
            }
        }
    } else {
        channel.prot_conf.flags.i_state = state;
    }
}

void setOcpDelay(Channel &channel, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.i_delay = delay;
        Channel::get(1).prot_conf.i_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.i_delay = delay;
            }
        }
    } else {
        channel.prot_conf.i_delay = delay;
    }
}

float getPowerLimit(const Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return 2 * MIN(Channel::get(0).getPowerLimit(), Channel::get(1).getPowerLimit());
    }
    return channel.getPowerLimit();
}

float getPowerMinLimit(const Channel &channel) {
    return 0;
}

float getPowerMaxLimit(const Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return 2 * MIN(Channel::get(0).params.PTOT, Channel::get(1).params.PTOT);
    }
    return channel.params.PTOT;
}

float getPowerDefaultLimit(const Channel &channel) {
    return getPowerMaxLimit(channel);
}

float getPowerProtectionLevel(const Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).prot_conf.p_level + Channel::get(1).prot_conf.p_level;
    }
    return channel.prot_conf.p_level;
}

void setPowerLimit(Channel &channel, float limit) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setPowerLimit(limit / 2);
        Channel::get(1).setPowerLimit(limit / 2);
    } else if (channel.flags.trackingEnabled) {
        limit = roundTrackingValuePrecision(UNIT_WATT, limit);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setPowerLimit(limit);
            }
        }
    } else {
        channel.setPowerLimit(limit);
    }

    if (getOppLevel(channel) > getPowerLimit(channel)) {
        setOppLevel(channel, getPowerLimit(channel));
    }
}

float getOppLevel(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).prot_conf.p_level + Channel::get(1).prot_conf.p_level;
    }
    return channel.prot_conf.p_level;
}

float getOppMinLevel(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return 2 * MAX(Channel::get(0).params.OPP_MIN_LEVEL, Channel::get(1).params.OPP_MIN_LEVEL);
    }
    return channel.params.OPP_MIN_LEVEL;
}

float getOppMaxLevel(Channel &channel) {
    return getPowerLimit(channel);
}

float getOppDefaultLevel(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).params.OPP_DEFAULT_LEVEL + Channel::get(1).params.OPP_DEFAULT_LEVEL;
    }
    return channel.params.OPP_DEFAULT_LEVEL;
}

void setOppParameters(Channel &channel, int state, float level, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        float coupledLevel = level / 2;

        coupledLevel = roundPrec(coupledLevel, Channel::get(0).getPowerResolution());

        Channel::get(0).prot_conf.flags.p_state = state;
        Channel::get(0).prot_conf.p_level = coupledLevel;
        Channel::get(0).prot_conf.p_delay = delay;

        Channel::get(1).prot_conf.flags.p_state = state;
        Channel::get(1).prot_conf.p_level = coupledLevel;
        Channel::get(1).prot_conf.p_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        level = roundTrackingValuePrecision(UNIT_WATT, level);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.p_state = state;
                trackingChannel.prot_conf.p_level = level;
                trackingChannel.prot_conf.p_delay = delay;
            }
        }
    } else {
        channel.prot_conf.flags.p_state = state;
        channel.prot_conf.p_level = roundPrec(level, channel.getPowerResolution());
        channel.prot_conf.p_delay = delay;
    }
}

void setOppState(Channel &channel, int state) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.flags.p_state = state;
        Channel::get(1).prot_conf.flags.p_state = state;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.flags.p_state = state;
            }
        }
    } else {
        channel.prot_conf.flags.p_state = state;
    }
}

void setOppLevel(Channel &channel, float level) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        float coupledLevel = level / 2;

        coupledLevel = roundPrec(coupledLevel, Channel::get(0).getPowerResolution());

        Channel::get(0).prot_conf.p_level = coupledLevel;
        Channel::get(1).prot_conf.p_level = coupledLevel;
    } else if (channel.flags.trackingEnabled) {
        level = roundTrackingValuePrecision(UNIT_WATT, level);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.p_level = level;
            }
        }
    } else {
        channel.prot_conf.p_level = roundPrec(level, channel.getPowerResolution());
    }
}

void setOppDelay(Channel &channel, float delay) {
    delay = roundPrec(delay, 0.001f);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).prot_conf.p_delay = delay;
        Channel::get(1).prot_conf.p_delay = delay;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.prot_conf.p_delay = delay;
            }
        }
    } else {
        channel.prot_conf.p_delay = delay;
    }
}

void setVoltageRampDuration(Channel &channel, float duration) {
    duration = roundPrec(duration, RAMP_DURATION_PREC);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).u.rampDuration = duration;
        Channel::get(1).u.rampDuration = duration;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.u.rampDuration = duration;
            }
        }
    } else {
        channel.u.rampDuration = duration;
    }
}

void setCurrentRampDuration(Channel &channel, float duration) {
    duration = roundPrec(duration, RAMP_DURATION_PREC);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).i.rampDuration = duration;
        Channel::get(1).i.rampDuration = duration;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.i.rampDuration = duration;
            }
        }
    } else {
        channel.i.rampDuration = duration;
    }
}

void setOutputDelayDuration(Channel &channel, float duration) {
    duration = roundPrec(duration, RAMP_DURATION_PREC);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).outputDelayDuration = duration;
        Channel::get(1).outputDelayDuration = duration;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.outputDelayDuration = duration;
            }
        }
    } else {
        channel.outputDelayDuration = duration;
    }
}

void outputEnable(Channel &channel, bool enable) {
    outputEnableOnNextSync(channel, enable);
    syncOutputEnable();
}

void outputEnableOnNextSync(Channel &channel, bool enable) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).flags.doOutputEnableOnNextSync = 1;
        Channel::get(0).flags.outputEnabledValueOnNextSync = enable;

        Channel::get(1).flags.doOutputEnableOnNextSync = 1;
        Channel::get(1).flags.outputEnabledValueOnNextSync = enable;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.flags.doOutputEnableOnNextSync = 1;
                trackingChannel.flags.outputEnabledValueOnNextSync = enable;
            }
        }
    } else {
        channel.flags.doOutputEnableOnNextSync = 1;
        channel.flags.outputEnabledValueOnNextSync = enable;
    }
}

void syncOutputEnable() {
    if (osThreadGetId() != g_psuTaskHandle) {
        osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_SYNC_OUTPUT_ENABLE, 0), osWaitForever);
    } else {
        Channel::syncOutputEnable();
    }
}

bool testOutputEnable(Channel &channel, bool enable, bool &callTriggerAbort, int *err) {
    if (enable != channel.isOutputEnabled()) {
        bool triggerModeEnabled = getVoltageTriggerMode(channel) != TRIGGER_MODE_FIXED || getCurrentTriggerMode(channel) != TRIGGER_MODE_FIXED;

        if (channel.isOutputEnabled()) {
            if (calibration::isEnabled()) {
                if (err) {
                    *err = SCPI_ERROR_CAL_OUTPUT_DISABLED;
                }
                return false;
            }

            if (triggerModeEnabled && !trigger::isIdle()) {
                callTriggerAbort = true;
            }
        } else {
            if (isTripped(channel)) {
                if (err) {
                    *err = SCPI_ERROR_CANNOT_EXECUTE_BEFORE_CLEARING_PROTECTION;
                }
                return false;
            }

            if (triggerModeEnabled && !trigger::isIdle()) {
                if (trigger::isInitiated()) {
                    callTriggerAbort = true;
                } else {
                    if (err) {
                        *err = SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER;
                    }
                    return false;
                }
            }
        }
    }

    return true;
}

bool outputEnable(uint32_t channels, bool enable, int *err) {
    bool callTriggerAbort = false;

    for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
        if ((channels & (1 << channelIndex)) != 0) {
            if (!testOutputEnable(Channel::get(channelIndex), enable, callTriggerAbort, err)) {
                return false;
            }
        }
    }

    if (callTriggerAbort) {
        trigger::abort();
    } else {
        for (int channelIndex = 0; channelIndex < CH_NUM; channelIndex++) {
            if ((channels & (1 << channelIndex)) != 0) {
                outputEnableOnNextSync(Channel::get(channelIndex), enable);
            }
        }
        syncOutputEnable();
    }

    return true;
}

void disableOutputForAllChannels() {
    for (int i = 0; i < CH_NUM; i++) {
        Channel &channel = Channel::get(i);
        if (channel.isOutputEnabled()) {
            outputEnableOnNextSync(channel, false);
        }
    }

    syncOutputEnable();
}

void disableOutputForAllTrackingChannels() {
    for (int i = 0; i < CH_NUM; i++) {
        Channel &channel = Channel::get(i);
        if (channel.flags.trackingEnabled && channel.isOutputEnabled()) {
            outputEnableOnNextSync(channel, false);
        }
    }

    syncOutputEnable();
}

void remoteSensingEnable(Channel &channel, bool enable) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).remoteSensingEnable(enable);
        Channel::get(1).remoteSensingEnable(enable);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.remoteSensingEnable(enable);
            }
        }
    } else {
        channel.remoteSensingEnable(enable);
    }
}

bool isTripped(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).isTripped() || Channel::get(1).isTripped();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled && trackingChannel.isTripped()) {
                return true;
            }
        }
        return false;
    } else {
        return channel.isTripped();
    }
}

void clearProtection(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).clearProtection();
        Channel::get(1).clearProtection();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.clearProtection();
            }
        }
    } else {
        channel.clearProtection();
    }
}

void disableProtection(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).disableProtection();
        Channel::get(1).disableProtection();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.disableProtection();
            }
        }
    } else {
        channel.disableProtection();
    }
}

bool isOvpTripped(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).ovp.flags.tripped || Channel::get(1).ovp.flags.tripped;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled && trackingChannel.ovp.flags.tripped) {
                return true;
            }
        }
        return false;
    } else {
        return channel.ovp.flags.tripped;
    }
}

bool isOcpTripped(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).ocp.flags.tripped || Channel::get(1).ocp.flags.tripped;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled && trackingChannel.ocp.flags.tripped) {
                return true;
            }
        }
        return false;
    } else {
        return channel.ocp.flags.tripped;
    }
}

bool isOppTripped(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).opp.flags.tripped || Channel::get(1).opp.flags.tripped;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled && trackingChannel.opp.flags.tripped) {
                return true;
            }
        }
        return false;
    } else {
        return channel.opp.flags.tripped;
    }
}

bool isOtpTripped(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return temperature::sensors[temp_sensor::CH1].isTripped() || temperature::sensors[temp_sensor::CH2].isTripped();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled && temperature::sensors[temp_sensor::CH1 + i].isTripped()) {
                return true;
            }
        }
        return false;
    } else {
        return temperature::sensors[temp_sensor::CH1 + channel.channelIndex].isTripped();
    }
}

void clearOtpProtection(int sensor) {
    if ((sensor == temp_sensor::CH1 || sensor == temp_sensor::CH2) && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        temperature::sensors[temp_sensor::CH1].clearProtection();
        temperature::sensors[temp_sensor::CH2].clearProtection();
    } else if (sensor >= temp_sensor::CH1 && Channel::get(sensor - temp_sensor::CH1).flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                temperature::sensors[temp_sensor::CH1 + i].clearProtection();
            }
        }
    } else {
        temperature::sensors[sensor].clearProtection();
    }
}

void setOtpParameters(Channel &channel, int state, float level, float delay) {
    delay = roundPrec(delay, 0.001f);
    level = roundPrec(level, 1);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        temperature::sensors[temp_sensor::CH1].prot_conf.state = state ? true : false;
        temperature::sensors[temp_sensor::CH1].prot_conf.level = level;
        temperature::sensors[temp_sensor::CH1].prot_conf.delay = delay;

        temperature::sensors[temp_sensor::CH2].prot_conf.state = state ? true : false;
        temperature::sensors[temp_sensor::CH2].prot_conf.level = level;
        temperature::sensors[temp_sensor::CH2].prot_conf.delay = delay;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.state = state ? true : false;
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.level = level;
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.delay = delay;
            }
        }
    } else {
        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.state = state ? true : false;
        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.level = level;
        temperature::sensors[temp_sensor::CH1 + channel.channelIndex].prot_conf.delay = delay;
    }
}

void setOtpState(int sensor, int state) {
    if ((sensor == temp_sensor::CH1 || sensor == temp_sensor::CH2) && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        temperature::sensors[temp_sensor::CH1].prot_conf.state = state ? true : false;
        temperature::sensors[temp_sensor::CH2].prot_conf.state = state ? true : false;
    } else if (sensor >= temp_sensor::CH1 && Channel::get(sensor - temp_sensor::CH1).flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.state = state ? true : false;
            }
        }
    } else {
        temperature::sensors[sensor].prot_conf.state = state ? true : false;
    }
}

void setOtpLevel(int sensor, float level) {
    level = roundPrec(level, 1);

    if ((sensor == temp_sensor::CH1 || sensor == temp_sensor::CH2) && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        temperature::sensors[temp_sensor::CH1].prot_conf.level = level;
        temperature::sensors[temp_sensor::CH2].prot_conf.level = level;
    } else if (sensor >= temp_sensor::CH1 && Channel::get(sensor - temp_sensor::CH1).flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.level = level;
            }
        }
    } else {
        temperature::sensors[sensor].prot_conf.level = level;
    }
}

void setOtpDelay(int sensor, float delay) {
    delay = roundPrec(delay, 0.001f);

    if ((sensor == temp_sensor::CH1 || sensor == temp_sensor::CH2) && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        temperature::sensors[temp_sensor::CH1].prot_conf.delay = delay;
        temperature::sensors[temp_sensor::CH2].prot_conf.delay = delay;
    } else if (sensor >= temp_sensor::CH1 && Channel::get(sensor - temp_sensor::CH1).flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                temperature::sensors[temp_sensor::CH1 + i].prot_conf.delay = delay;
            }
        }
    } else {
        temperature::sensors[sensor].prot_conf.delay = delay;
    }
}

void setDisplayViewSettings(Channel &channel, int displayValue1, int displayValue2, float ytViewRate) {
    bool resetHistory = false;

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).flags.displayValue1 = displayValue1;
        Channel::get(0).flags.displayValue2 = displayValue2;
        if (Channel::get(0).ytViewRate != ytViewRate) {
            Channel::get(0).ytViewRate = ytViewRate;
            resetHistory = true;
        }

        Channel::get(1).flags.displayValue1 = displayValue1;
        Channel::get(1).flags.displayValue2 = displayValue2;
        if (Channel::get(1).ytViewRate != ytViewRate) {
            Channel::get(1).ytViewRate = ytViewRate;
            resetHistory = true;
        }
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.flags.displayValue1 = displayValue1;
                trackingChannel.flags.displayValue2 = displayValue2;
                if (trackingChannel.ytViewRate != ytViewRate) {
                    trackingChannel.ytViewRate = ytViewRate;
                    resetHistory = true;
                }
            }
        }
    } else {
        channel.flags.displayValue1 = displayValue1;
        channel.flags.displayValue2 = displayValue2;
        if (channel.ytViewRate != ytViewRate) {
            channel.ytViewRate = ytViewRate;
            resetHistory = true;
        }
    }
    
    if (resetHistory) {
        if (osThreadGetId() != g_psuTaskHandle) {
            osMessagePut(g_psuMessageQueueId, PSU_QUEUE_MESSAGE(PSU_QUEUE_RESET_CHANNELS_HISTORY, 0), osWaitForever);
        } else {
            Channel::resetHistoryForAllChannels();
        }
    }
}

TriggerMode getVoltageTriggerMode(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).getVoltageTriggerMode();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.getVoltageTriggerMode();
            }
        }
    }
    
    return channel.getVoltageTriggerMode();
}

void setVoltageTriggerMode(Channel &channel, TriggerMode mode) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setVoltageTriggerMode(mode);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setVoltageTriggerMode(mode);
            }
        }
    } else {
        channel.setVoltageTriggerMode(mode);
    }
}

TriggerMode getCurrentTriggerMode(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).getCurrentTriggerMode();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.getCurrentTriggerMode();
            }
        }
    }
    return channel.getCurrentTriggerMode();
}

void setCurrentTriggerMode(Channel &channel, TriggerMode mode) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setCurrentTriggerMode(mode);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setCurrentTriggerMode(mode);
            }
        }
    } else {
        channel.setCurrentTriggerMode(mode);
    }
}

bool getTriggerOutputState(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).getTriggerOutputState();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.getTriggerOutputState();
            }
        }
    }
    return channel.getTriggerOutputState();
}

void setTriggerOutputState(Channel &channel, bool enable) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setTriggerOutputState(enable);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setTriggerOutputState(enable);
            }
        }
    } else {
        channel.setTriggerOutputState(enable);
    }
}

TriggerOnListStop getTriggerOnListStop(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).getTriggerOnListStop();
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.getTriggerOnListStop();
            }
        }
    }
    return channel.getTriggerOnListStop();
}

void setTriggerOnListStop(Channel &channel, TriggerOnListStop value) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setTriggerOnListStop(value);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.setTriggerOnListStop(value);
            }
        }
    } else {
        channel.setTriggerOnListStop(value);
    }
}

float getTriggerVoltage(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).u.triggerLevel;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.u.triggerLevel;
            }
        }
    }
    return channel.u.triggerLevel;
}

void setTriggerVoltage(Channel &channel, float value) {
    value = roundChannelValue(channel, UNIT_VOLT, value);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).u.triggerLevel = value;
    } else if (channel.flags.trackingEnabled) {
        value = roundTrackingValuePrecision(UNIT_VOLT, value);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.u.triggerLevel = value;
            }
        }
    } else {
        channel.u.triggerLevel = value;
    }
}

float getTriggerCurrent(Channel &channel) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        return Channel::get(0).i.triggerLevel;
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                return trackingChannel.i.triggerLevel;
            }
        }
    }
    return channel.i.triggerLevel;
}

void setTriggerCurrent(Channel &channel, float value) {
    value = roundChannelValue(channel, UNIT_AMPER, value);

    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).i.triggerLevel = value;
    } else if (channel.flags.trackingEnabled) {
        value = roundTrackingValuePrecision(UNIT_AMPER, value);
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                trackingChannel.i.triggerLevel = value;
            }
        }
    } else {
        channel.i.triggerLevel = value;
    }
}

void setDwellList(Channel &channel, float *list, uint16_t listLength) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        list::setDwellList(Channel::get(0), list, listLength);
        list::setDwellList(Channel::get(1), list, listLength);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                list::setDwellList(trackingChannel, list, listLength);
            }
        }
    } else {
        list::setDwellList(channel, list, listLength);
    }
}

void setVoltageList(Channel &channel, float *list, uint16_t listLength) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        list::setVoltageList(Channel::get(0), list, listLength);
        list::setVoltageList(Channel::get(1), list, listLength);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                list::setVoltageList(trackingChannel, list, listLength);
            }
        }
    } else {
        list::setVoltageList(channel, list, listLength);
    }
}

void setCurrentList(Channel &channel, float *list, uint16_t listLength) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        list::setCurrentList(Channel::get(0), list, listLength);
        list::setCurrentList(Channel::get(1), list, listLength);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                list::setCurrentList(trackingChannel, list, listLength);
            }
        }
    } else {
        list::setCurrentList(channel, list, listLength);
    }
}

void setListCount(Channel &channel, uint16_t value) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        list::setListCount(Channel::get(0), value);
        list::setListCount(Channel::get(1), value);
    } else if (channel.flags.trackingEnabled) {
        for (int i = 0; i < CH_NUM; ++i) {
            Channel &trackingChannel = Channel::get(i);
            if (trackingChannel.flags.trackingEnabled) {
                list::setListCount(trackingChannel, value);
            }
        }
    } else {
        list::setListCount(channel, value);
    }
}

void setCurrentRangeSelectionMode(Channel &channel, CurrentRangeSelectionMode mode) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).setCurrentRangeSelectionMode(mode);
        Channel::get(1).setCurrentRangeSelectionMode(mode);
    } else {
        channel.setCurrentRangeSelectionMode(mode);
    }
}

void enableAutoSelectCurrentRange(Channel &channel, bool enable) {
    if (channel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL)) {
        Channel::get(0).enableAutoSelectCurrentRange(enable);
        Channel::get(1).enableAutoSelectCurrentRange(enable);
    } else {
        channel.enableAutoSelectCurrentRange(enable);
    }
}

#ifdef EEZ_PLATFORM_SIMULATOR
void setLoadEnabled(Channel &channel, bool state) {
    channel.simulator.setLoadEnabled(state);
}

void setLoad(Channel &channel, float load) {
    load = roundPrec(load, 0.001f);
    channel.simulator.setLoad(load);
}
#endif

const char *copyChannelToChannel(int srcChannelIndex, int dstChannelIndex) {
    Channel &srcChannel = Channel::get(srcChannelIndex);
    Channel &dstChannel = Channel::get(dstChannelIndex);

    float voltageLimit;
    if (srcChannel.u.limit < channel_dispatcher::getUMaxLimit(dstChannel)) {
        voltageLimit = srcChannel.u.limit;
    } else {
        voltageLimit = channel_dispatcher::getUMaxLimit(dstChannel);
    }

    float currentLimit;
    if (srcChannel.i.limit < channel_dispatcher::getIMaxLimit(dstChannel)) {
        currentLimit = srcChannel.i.limit;
    } else {
        currentLimit = channel_dispatcher::getIMaxLimit(dstChannel);
    }

    float powerLimit;
    if (srcChannel.p_limit < channel_dispatcher::getPowerMaxLimit(dstChannel)) {
        powerLimit = srcChannel.p_limit;
    } else {
        powerLimit = channel_dispatcher::getPowerMaxLimit(dstChannel);
    }

    if (srcChannel.u.set > voltageLimit) {
        return "Voltage overflow.";
    }

    if (srcChannel.i.set > currentLimit) {
        return "Current overflow.";
    }

    if (srcChannel.u.set * srcChannel.i.set > powerLimit) {
        return "Power overflow.";
    }

    if (
        srcChannel.flags.rprogEnabled &&
        (dstChannel.params.features & CH_FEATURE_RPROG) &&
        (
            dstChannel.flags.trackingEnabled || 
            (dstChannel.channelIndex < 2 && (g_couplingType == COUPLING_TYPE_SERIES || g_couplingType == COUPLING_TYPE_PARALLEL))
        )
    ) {
        return "Can not enable remote programming.";
    }

    uint16_t dwellListLength;
    float *dwellList = list::getDwellList(srcChannel, &dwellListLength);

    uint16_t voltageListLength;
    float *voltageList = list::getVoltageList(srcChannel, &voltageListLength);

    for (int i = 0; i < voltageListLength; i++) {
        if (voltageList[i] > channel_dispatcher::getUMaxLimit(dstChannel)) {
            return "Voltage list value overflow.";
        }
    }

    uint16_t currentListLength;
    float *currentList = list::getCurrentList(srcChannel, &currentListLength);

    for (int i = 0; i < currentListLength; i++) {
        if (currentList[i] > channel_dispatcher::getIMaxLimit(dstChannel)) {
            return "Current list value overflow.";
        }
    }

    channel_dispatcher::outputEnable(dstChannel, false);

    channel_dispatcher::setVoltage(dstChannel, srcChannel.u.set);
    channel_dispatcher::setVoltageStep(dstChannel, srcChannel.u.step);
    channel_dispatcher::setVoltageLimit(dstChannel, voltageLimit);

    channel_dispatcher::setCurrent(dstChannel, srcChannel.i.set);
    channel_dispatcher::setCurrentStep(dstChannel, srcChannel.i.step);
    channel_dispatcher::setCurrentLimit(dstChannel, currentLimit);

    channel_dispatcher::setPowerLimit(dstChannel, powerLimit);

    channel_dispatcher::setOvpParameters(dstChannel, srcChannel.prot_conf.flags.u_type, srcChannel.prot_conf.flags.u_state, srcChannel.prot_conf.u_level, srcChannel.prot_conf.u_delay);
    channel_dispatcher::setOcpParameters(dstChannel, srcChannel.prot_conf.flags.i_state, srcChannel.prot_conf.i_delay);
    channel_dispatcher::setOppParameters(dstChannel, srcChannel.prot_conf.flags.p_state, srcChannel.prot_conf.p_level, srcChannel.prot_conf.p_delay);

#ifdef EEZ_PLATFORM_SIMULATOR
    channel_dispatcher::setLoadEnabled(dstChannel, srcChannel.simulator.load_enabled);
    channel_dispatcher::setLoad(dstChannel, srcChannel.simulator.load);
#endif

    channel_dispatcher::remoteSensingEnable(dstChannel, srcChannel.flags.senseEnabled);

    if (dstChannel.params.features & CH_FEATURE_RPROG) {
        dstChannel.flags.rprogEnabled = srcChannel.flags.rprogEnabled;
    }

    auto displayValue1 = srcChannel.flags.displayValue1;
    auto displayValue2 = srcChannel.flags.displayValue2;
    auto ytViewRate = srcChannel.ytViewRate;
    if (displayValue1 == 0 && displayValue2 == 0) {
        displayValue1 = DISPLAY_VALUE_VOLTAGE;
        displayValue2 = DISPLAY_VALUE_CURRENT;
    }
    if (ytViewRate == 0) {
        ytViewRate = GUI_YT_VIEW_RATE_DEFAULT;
    }
    channel_dispatcher::setDisplayViewSettings(dstChannel, displayValue1, displayValue2, ytViewRate);

    channel_dispatcher::setVoltageTriggerMode(dstChannel, (TriggerMode)srcChannel.flags.voltageTriggerMode);
    channel_dispatcher::setCurrentTriggerMode(dstChannel, (TriggerMode)srcChannel.flags.currentTriggerMode);
    channel_dispatcher::setTriggerOutputState(dstChannel, srcChannel.flags.triggerOutputState);
    channel_dispatcher::setTriggerOnListStop(dstChannel, (TriggerOnListStop)srcChannel.flags.triggerOnListStop);

    channel_dispatcher::setTriggerVoltage(dstChannel, srcChannel.u.triggerLevel);
    channel_dispatcher::setTriggerCurrent(dstChannel, srcChannel.i.triggerLevel);

    channel_dispatcher::setListCount(dstChannel, list::getListCount(srcChannel));

    channel_dispatcher::setCurrentRangeSelectionMode(dstChannel, (CurrentRangeSelectionMode)srcChannel.flags.currentRangeSelectionMode);
    channel_dispatcher::enableAutoSelectCurrentRange(dstChannel, srcChannel.flags.autoSelectCurrentRange);

    dstChannel.setDprogState((DprogState)srcChannel.flags.dprogState);

    channel_dispatcher::setDwellList(dstChannel, dwellList, dwellListLength);
    channel_dispatcher::setVoltageList(dstChannel, voltageList, voltageListLength);
    channel_dispatcher::setCurrentList(dstChannel, currentList, currentListLength);

    return nullptr;
}

bool isEditEnabled(Channel &channel) {
    using namespace psu::gui;

    if (
        (getVoltageTriggerMode(channel) != TRIGGER_MODE_FIXED || getCurrentTriggerMode(channel) != TRIGGER_MODE_FIXED) &&
        g_psuAppContext.getActivePageId() == PAGE_ID_MAIN
    ) {
        return false;
    } 

    return true;
}

} // namespace channel_dispatcher
} // namespace psu
} // namespace eez
