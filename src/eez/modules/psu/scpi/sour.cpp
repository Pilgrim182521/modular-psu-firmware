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

#include <eez/modules/psu/psu.h>

#include <eez/modules/psu/channel_dispatcher.h>
#include <eez/modules/psu/io_pins.h>
#include <eez/modules/psu/list_program.h>
#include <eez/modules/psu/profile.h>
#include <eez/modules/psu/scpi/psu.h>
#include <eez/modules/psu/trigger.h>

#define I_STATE 1
#define P_STATE 2
#define U_STATE 3

namespace eez {
namespace psu {
namespace scpi {

////////////////////////////////////////////////////////////////////////////////

static scpi_result_t set_step(scpi_t *context, Channel::Value *cv, float min_value, float max_value,
                              float def, _scpi_unit_t unit) {
    scpi_number_t step_param;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &step_param, true)) {
        return SCPI_RES_ERR;
    }

    float step;

    if (step_param.special) {
        if (step_param.content.tag == SCPI_NUM_DEF) {
            step = def;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        if (step_param.unit != SCPI_UNIT_NONE && step_param.unit != unit) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        step = (float)step_param.content.value;
        if (step < min_value || step > max_value) {
            SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
            return SCPI_RES_ERR;
        }
    }

    cv->step = step;

    return SCPI_RES_OK;
}

scpi_result_t get_source_value(scpi_t *context, Channel &channel, Unit unit, float value, float min, float max, float def) {
    int32_t spec;
    if (!SCPI_ParamChoice(context, scpi_special_numbers_def, &spec, false)) {
        if (SCPI_ParamErrorOccurred(context)) {
            return SCPI_RES_ERR;
        }
    } else {
        if (spec == SCPI_NUM_MIN) {
            value = min;
        } else if (spec == SCPI_NUM_MAX) {
            value = max;
        } else if (spec == SCPI_NUM_DEF) {
            value = def;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    }

    return result_float(context, &channel, value, unit);
}

static scpi_result_t get_source_value(scpi_t *context, Channel &channel, Unit unit, float value, float def) {
    int32_t spec;
    if (!SCPI_ParamChoice(context, scpi_special_numbers_def, &spec, false)) {
        if (SCPI_ParamErrorOccurred(context)) {
            return SCPI_RES_ERR;
        }
    } else {
        if (spec == SCPI_NUM_DEF) {
            value = def;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    }

    return result_float(context, &channel, value, unit);
}

scpi_result_t get_delay(scpi_t *context, float delay) {
    SCPI_ResultFloat(context, delay);

    return SCPI_RES_OK;
}

scpi_result_t get_state(scpi_t *context, Channel *channel, int type) {
    switch (type) {
    case I_STATE:
        SCPI_ResultBool(context, channel->prot_conf.flags.i_state);
        break;
    case P_STATE:
        SCPI_ResultBool(context, channel->prot_conf.flags.p_state);
        break;
    default:
        SCPI_ResultBool(context, channel->prot_conf.flags.u_state);
        break;
    }

    return SCPI_RES_OK;
}

scpi_result_t get_tripped(scpi_t *context, ProtectionValue &cpv) {
    SCPI_ResultBool(context, cpv.flags.tripped);

    return SCPI_RES_OK;
}

////////////////////////////////////////////////////////////////////////////////

scpi_result_t scpi_cmd_sourceCurrentLevelImmediateAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel_dispatcher::getVoltageTriggerMode(*channel) != TRIGGER_MODE_FIXED &&
        !trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    float current;
    if (!get_current_param(context, current, channel, &channel->i)) {
        return SCPI_RES_ERR;
    }

    if (current > channel_dispatcher::getILimit(*channel)) {
        SCPI_ErrorPush(context, SCPI_ERROR_CURRENT_LIMIT_EXCEEDED);
        return SCPI_RES_ERR;
    }

    if (current * channel_dispatcher::getUSetUnbalanced(*channel) > channel_dispatcher::getPowerLimit(*channel)) {
        SCPI_ErrorPush(context, SCPI_ERROR_POWER_LIMIT_EXCEEDED);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setCurrent(*channel, current);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentLevelImmediateAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_AMPER, channel_dispatcher::getISet(*channel),
                            channel_dispatcher::getIMin(*channel),
                            channel_dispatcher::getIMax(*channel),
                            channel_dispatcher::getIDef(*channel));
}

scpi_result_t scpi_cmd_sourceVoltageLevelImmediateAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel_dispatcher::getVoltageTriggerMode(*channel) != TRIGGER_MODE_FIXED &&
        !trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    float voltage;
    if (!get_voltage_param(context, voltage, channel, &channel->u)) {
        return SCPI_RES_ERR;
    }

    if (channel->isRemoteProgrammingEnabled()) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    }

    if (voltage > channel_dispatcher::getULimit(*channel)) {
        SCPI_ErrorPush(context, SCPI_ERROR_VOLTAGE_LIMIT_EXCEEDED);
        return SCPI_RES_ERR;
    }

    if (voltage * channel_dispatcher::getISetUnbalanced(*channel) > channel_dispatcher::getPowerLimit(*channel)) {
        SCPI_ErrorPush(context, SCPI_ERROR_POWER_LIMIT_EXCEEDED);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setVoltage(*channel, voltage);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageLevelImmediateAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float u;
    if (channel->isRemoteProgrammingEnabled()) {
        u = channel->u.mon_dac;
    } else {
        u = channel_dispatcher::getUSet(*channel);
    }

    return get_source_value(context, *channel, UNIT_VOLT, u, channel_dispatcher::getUMin(*channel),
                            channel_dispatcher::getUMax(*channel),
                            channel_dispatcher::getUDef(*channel));
}

////////////////////////////////////////////////////////////////////////////////

scpi_result_t scpi_cmd_sourceCurrentLevelImmediateStepIncrement(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return set_step(context, &channel->i, channel->params.I_MIN_STEP, channel->params.I_MAX_STEP, channel->params.I_DEF_STEP, SCPI_UNIT_AMPER);
}

scpi_result_t scpi_cmd_sourceCurrentLevelImmediateStepIncrementQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_AMPER, channel->i.step, channel->params.I_DEF_STEP);
}

scpi_result_t scpi_cmd_sourceVoltageLevelImmediateStepIncrement(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return set_step(context, &channel->u, channel->params.U_MIN_STEP, channel->params.U_MAX_STEP, channel->params.U_DEF_STEP, SCPI_UNIT_VOLT);
}

scpi_result_t scpi_cmd_sourceVoltageLevelImmediateStepIncrementQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_VOLT, channel->u.step, channel->params.U_DEF_STEP);
}

////////////////////////////////////////////////////////////////////////////////

scpi_result_t scpi_cmd_sourceCurrentProtectionDelayTime(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float delay;
    if (!get_duration_param(context, delay, channel->params.OCP_MIN_DELAY, channel->params.OCP_MAX_DELAY, channel->params.OCP_DEFAULT_DELAY)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOcpDelay(*channel, delay);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentProtectionDelayTimeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_delay(context, channel->prot_conf.i_delay);
}

scpi_result_t scpi_cmd_sourceCurrentProtectionState(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    bool state;
    if (!SCPI_ParamBool(context, &state, TRUE)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOcpState(*channel, state);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentProtectionStateQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_state(context, channel, I_STATE);
}

scpi_result_t scpi_cmd_sourceCurrentProtectionTrippedQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_tripped(context, channel->ocp);
}

scpi_result_t scpi_cmd_sourcePowerProtectionLevel(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float power;
    if (!get_power_param(context, power, channel_dispatcher::getOppMinLevel(*channel),
                         channel_dispatcher::getOppMaxLevel(*channel),
                         channel_dispatcher::getOppDefaultLevel(*channel))) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOppLevel(*channel, power);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourcePowerProtectionLevelQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(
        context, *channel, UNIT_WATT, channel_dispatcher::getPowerProtectionLevel(*channel),
        channel_dispatcher::getOppMinLevel(*channel), channel_dispatcher::getOppMaxLevel(*channel),
        channel_dispatcher::getOppDefaultLevel(*channel));
}

scpi_result_t scpi_cmd_sourcePowerProtectionDelayTime(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float delay;
    if (!get_duration_param(context, delay, channel->params.OPP_MIN_DELAY, channel->params.OPP_MAX_DELAY, channel->params.OPP_DEFAULT_DELAY)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOppDelay(*channel, delay);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourcePowerProtectionDelayTimeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_delay(context, channel->prot_conf.p_delay);
}

scpi_result_t scpi_cmd_sourcePowerProtectionState(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    bool state;
    if (!SCPI_ParamBool(context, &state, TRUE)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOppState(*channel, state);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourcePowerProtectionStateQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_state(context, channel, P_STATE);
}

scpi_result_t scpi_cmd_sourcePowerProtectionTrippedQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_tripped(context, channel->opp);
}

scpi_result_t scpi_cmd_sourceVoltageProtectionLevel(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float voltage;
    if (!get_voltage_protection_level_param(
        context, 
        voltage, 
        channel_dispatcher::getUSet(*channel),
        channel_dispatcher::getUMax(*channel),
        channel_dispatcher::getUMaxOvpLevel(*channel)
    )) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOvpLevel(*channel, voltage);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProtectionLevelQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(
        context, *channel, UNIT_VOLT, channel_dispatcher::getUProtectionLevel(*channel),
        channel_dispatcher::getUSet(*channel), channel_dispatcher::getUMax(*channel),
        channel_dispatcher::getUMax(*channel));
}

scpi_result_t scpi_cmd_sourceVoltageProtectionDelayTime(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float delay;
    if (!get_duration_param(context, delay, channel->params.OVP_MIN_DELAY, channel->params.OVP_MAX_DELAY, channel->params.OVP_DEFAULT_DELAY)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOvpDelay(*channel, delay);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProtectionDelayTimeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_delay(context, channel->prot_conf.u_delay);
}

scpi_result_t scpi_cmd_sourceVoltageProtectionState(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    bool state;
    if (!SCPI_ParamBool(context, &state, TRUE)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOvpState(*channel, state);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProtectionStateQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_state(context, channel, U_STATE);
}

scpi_result_t scpi_cmd_sourceVoltageProtectionTrippedQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_tripped(context, channel->ovp);
}

static scpi_choice_def_t voltageProtectionType[] = {
    { "HW", VOLTAGE_PROTECTION_TYPE_HW },
    { "SW", VOLTAGE_PROTECTION_TYPE_SW },
    SCPI_CHOICE_LIST_END /* termination of option list */
};

scpi_result_t scpi_cmd_sourceVoltageProtectionType(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (!(channel->params.features & CH_FEATURE_HW_OVP)) {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    int32_t type;
    if (!SCPI_ParamChoice(context, voltageProtectionType, &type, true)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setOvpType(*channel, type);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProtectionTypeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (!(channel->params.features & CH_FEATURE_HW_OVP)) {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    resultChoiceName(context, voltageProtectionType, channel->prot_conf.flags.u_type);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageSenseSource(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->channelIndex < 2 && channel_dispatcher::getCouplingType() == channel_dispatcher::COUPLING_TYPE_SERIES) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED);
        return SCPI_RES_ERR;
    }

    int32_t choice;
    if (!SCPI_ParamChoice(context, internal_external_choice, &choice, TRUE)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::remoteSensingEnable(*channel, choice == 0 ? false : true);

    return SCPI_RES_OK;}

scpi_result_t scpi_cmd_sourceVoltageSenseSourceQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->channelIndex < 2 && channel_dispatcher::getCouplingType() == channel_dispatcher::COUPLING_TYPE_SERIES) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED);
        return SCPI_RES_ERR;
    }

    SCPI_ResultBool(context, channel->isRemoteSensingEnabled());

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProgramSource(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->channelIndex < 2 && channel_dispatcher::getCouplingType() != channel_dispatcher::COUPLING_TYPE_NONE) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED);
        return SCPI_RES_ERR;
    }

    if (channel->flags.trackingEnabled) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_IN_TRACKING_MODE);
        return SCPI_RES_ERR;
    }

    if (!(channel->params.features & CH_FEATURE_RPROG)) {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    int32_t choice;
    if (!SCPI_ParamChoice(context, internal_external_choice, &choice, TRUE)) {
        return SCPI_RES_ERR;
    }

    channel->remoteProgrammingEnable(choice == 0 ? false : true);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageProgramSourceQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    if (channel->channelIndex < 2 && channel_dispatcher::getCouplingType() != channel_dispatcher::COUPLING_TYPE_NONE) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_CHANNELS_ARE_COUPLED);
        return SCPI_RES_ERR;
    }

    if (channel->flags.trackingEnabled) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTE_ERROR_IN_TRACKING_MODE);
        return SCPI_RES_ERR;
    }

    if (!(channel->params.features & CH_FEATURE_RPROG)) {
        SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_MISSING);
        return SCPI_RES_ERR;
    }

    SCPI_ResultBool(context, channel->isRemoteProgrammingEnabled());

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentLimitPositiveImmediateAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float limit;
    if (!get_current_limit_param(context, limit, channel, &channel->i)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setCurrentLimit(*channel, limit);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentLimitPositiveImmediateAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_AMPER, channel_dispatcher::getILimit(*channel),
                            0, channel_dispatcher::getIMaxLimit(*channel),
                            channel_dispatcher::getIMaxLimit(*channel));
}

scpi_result_t scpi_cmd_sourceVoltageLimitPositiveImmediateAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float limit;
    if (!get_voltage_limit_param(context, limit, channel, &channel->i)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setVoltageLimit(*channel, limit);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageLimitPositiveImmediateAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_VOLT, channel_dispatcher::getULimit(*channel),
                            0, channel_dispatcher::getUMaxLimit(*channel),
                            channel_dispatcher::getUMaxLimit(*channel));
}

scpi_result_t scpi_cmd_sourcePowerLimit(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float limit;
    if (!get_power_limit_param(context, limit, channel, &channel->i)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setPowerLimit(*channel, limit);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourcePowerLimitQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_WATT,
                            channel_dispatcher::getPowerLimit(*channel),
                            channel_dispatcher::getPowerMinLimit(*channel),
                            channel_dispatcher::getPowerMaxLimit(*channel),
                            channel_dispatcher::getPowerDefaultLimit(*channel));
}

////////////////////////////////////////////////////////////////////////////////

scpi_result_t scpi_cmd_sourceCurrentLevelTriggeredAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float current;
    if (!get_current_param(context, current, channel, &channel->i)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setTriggerCurrent(*channel, current);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentLevelTriggeredAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(
        context, *channel, UNIT_AMPER, channel_dispatcher::getTriggerCurrent(*channel),
        channel_dispatcher::getIMin(*channel), channel_dispatcher::getIMax(*channel),
        channel_dispatcher::getIDef(*channel));
}

scpi_result_t scpi_cmd_sourceVoltageLevelTriggeredAmplitude(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float voltage;
    if (!get_voltage_param(context, voltage, channel, &channel->u)) {
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setTriggerVoltage(*channel, voltage);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageLevelTriggeredAmplitudeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(
        context, *channel, UNIT_VOLT, channel_dispatcher::getTriggerVoltage(*channel),
        channel_dispatcher::getUMin(*channel), channel_dispatcher::getUMax(*channel),
        channel_dispatcher::getUDef(*channel));
}

static scpi_choice_def_t triggerModeChoice[] = {
    { "FIXed", TRIGGER_MODE_FIXED },
    { "LIST", TRIGGER_MODE_LIST },
    { "STEP", TRIGGER_MODE_STEP },
    SCPI_CHOICE_LIST_END /* termination of option list */
};

scpi_result_t scpi_cmd_sourceCurrentMode(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    int32_t triggerMode;
    if (!SCPI_ParamChoice(context, triggerModeChoice, &triggerMode, true)) {
        return SCPI_RES_ERR;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setCurrentTriggerMode(*channel, (TriggerMode)triggerMode);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentModeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    resultChoiceName(context, triggerModeChoice,
                     channel_dispatcher::getCurrentTriggerMode(*channel));

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageMode(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    int32_t triggerMode;
    if (!SCPI_ParamChoice(context, triggerModeChoice, &triggerMode, true)) {
        return SCPI_RES_ERR;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setVoltageTriggerMode(*channel, (TriggerMode)triggerMode);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageModeQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    resultChoiceName(context, triggerModeChoice,
                     channel_dispatcher::getVoltageTriggerMode(*channel));

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListCount(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    scpi_number_t param;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param, true)) {
        return SCPI_RES_ERR;
    }

    uint16_t count;

    if (param.special) {
        if (param.content.tag == SCPI_NUM_INF) {
            count = 0;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        int value = (int)param.content.value;
        if (value < 0 || value > MAX_LIST_COUNT) {
            SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
            return SCPI_RES_ERR;
        }

        count = value;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setListCount(*channel, count);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListCountQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    SCPI_ResultInt(context, list::getListCount(*channel));

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListCurrentLevel(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float list[MAX_LIST_LENGTH];
    uint16_t listLength = 0;

    uint16_t voltageListLength;
    float *voltageList = list::getCurrentList(*channel, &voltageListLength);

    for (int i = 0;; ++i) {
        scpi_number_t param;
        if (!SCPI_ParamNumber(context, 0, &param, false)) {
            break;
        }

        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_AMPER) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        float current = (float)param.content.value;

        if (listLength >= MAX_LIST_LENGTH) {
            SCPI_ErrorPush(context, SCPI_ERROR_TOO_MANY_LIST_POINTS);
            return SCPI_RES_ERR;
        }

        if (current > channel_dispatcher::getIMaxLimit(*channel)) {
            SCPI_ErrorPush(context, SCPI_ERROR_CURRENT_LIMIT_EXCEEDED);
            return SCPI_RES_ERR;
        }

        if (voltageListLength > 0) {
            if (current * voltageList[i % voltageListLength] > channel_dispatcher::getPowerMaxLimit(*channel)) {
                SCPI_ErrorPush(context, SCPI_ERROR_POWER_LIMIT_EXCEEDED);
                return SCPI_RES_ERR;
            }
        }

        list[listLength++] = current;
    }

    if (listLength == 0) {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setCurrentList(*channel, list, listLength);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListCurrentLevelQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    uint16_t listLength;
    float *list = list::getCurrentList(*channel, &listLength);
    SCPI_ResultArrayFloat(context, list, listLength, SCPI_FORMAT_ASCII);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListDwell(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float list[MAX_LIST_LENGTH];
    uint16_t listLength = 0;

    while (true) {
        scpi_number_t param;
        if (!SCPI_ParamNumber(context, 0, &param, false)) {
            break;
        }

        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_SECOND) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        float dwell = (float)param.content.value;

        if (listLength >= MAX_LIST_LENGTH) {
            SCPI_ErrorPush(context, SCPI_ERROR_TOO_MANY_LIST_POINTS);
            return SCPI_RES_ERR;
        }

        list[listLength++] = dwell;
    }

    if (listLength == 0) {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setDwellList(*channel, list, listLength);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListDwellQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    uint16_t listLength;
    float *list = list::getDwellList(*channel, &listLength);
    SCPI_ResultArrayFloat(context, list, listLength, SCPI_FORMAT_ASCII);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListVoltageLevel(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    float list[MAX_LIST_LENGTH];
    uint16_t listLength = 0;

    uint16_t currentListLength;
    float *currentList = list::getCurrentList(*channel, &currentListLength);

    for (int i = 0;; ++i) {
        scpi_number_t param;
        if (!SCPI_ParamNumber(context, 0, &param, false)) {
            break;
        }

        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_VOLT) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        float voltage = (float)param.content.value;

        if (listLength >= MAX_LIST_LENGTH) {
            SCPI_ErrorPush(context, SCPI_ERROR_TOO_MANY_LIST_POINTS);
            return SCPI_RES_ERR;
        }

        if (voltage > channel_dispatcher::getUMaxLimit(*channel)) {
            SCPI_ErrorPush(context, SCPI_ERROR_VOLTAGE_LIMIT_EXCEEDED);
            return SCPI_RES_ERR;
        }

        if (currentListLength > 0) {
            if (voltage * currentList[i % currentListLength] > channel_dispatcher::getPowerMaxLimit(*channel)) {
                SCPI_ErrorPush(context, SCPI_ERROR_POWER_LIMIT_EXCEEDED);
                return SCPI_RES_ERR;
            }
        }

        list[listLength++] = voltage;
    }

    if (listLength == 0) {
        SCPI_ErrorPush(context, SCPI_ERROR_MISSING_PARAMETER);
        return SCPI_RES_ERR;
    }

    if (!trigger::isIdle()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CANNOT_CHANGE_TRANSIENT_TRIGGER);
        return SCPI_RES_ERR;
    }

    channel_dispatcher::setVoltageList(*channel, list, listLength);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceListVoltageLevelQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    uint16_t listLength;
    float *list = list::getVoltageList(*channel, &listLength);
    SCPI_ResultArrayFloat(context, list, listLength, SCPI_FORMAT_ASCII);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentRampDuration(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    scpi_number_t param;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param, true)) {
        return SCPI_RES_ERR;
    }
    float duration;
    if (param.special) {
        if (param.content.tag == SCPI_NUM_MIN) {
            duration = RAMP_DURATION_MIN_VALUE;
        } else if (param.content.tag == SCPI_NUM_MAX) {
            duration = RAMP_DURATION_MAX_VALUE;
        } else if (param.content.tag == SCPI_NUM_DEF) {
            duration = RAMP_DURATION_DEF_VALUE;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_SECOND) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        duration = (float)param.content.value;
    }

    channel_dispatcher::setCurrentRampDuration(*channel, duration);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceCurrentRampDurationQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_SECOND, channel->i.rampDuration, RAMP_DURATION_MIN_VALUE, RAMP_DURATION_MAX_VALUE, RAMP_DURATION_DEF_VALUE);
}

scpi_result_t scpi_cmd_sourceVoltageRampDuration(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    scpi_number_t param;
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param, true)) {
        return SCPI_RES_ERR;
    }
    float duration;
    if (param.special) {
        if (param.content.tag == SCPI_NUM_MIN) {
            duration = RAMP_DURATION_MIN_VALUE;
        } else if (param.content.tag == SCPI_NUM_MAX) {
            duration = RAMP_DURATION_MAX_VALUE;
        } else if (param.content.tag == SCPI_NUM_DEF) {
            duration = RAMP_DURATION_DEF_VALUE;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE && param.unit != SCPI_UNIT_SECOND) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return SCPI_RES_ERR;
        }

        duration = (float)param.content.value;
    }

    channel_dispatcher::setVoltageRampDuration(*channel, duration);

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sourceVoltageRampDurationQ(scpi_t *context) {
    Channel *channel = set_channel_from_command_number(context);
    if (!channel) {
        return SCPI_RES_ERR;
    }

    return get_source_value(context, *channel, UNIT_SECOND, channel->u.rampDuration, RAMP_DURATION_MIN_VALUE, RAMP_DURATION_MAX_VALUE, RAMP_DURATION_DEF_VALUE);
}

} // namespace scpi
} // namespace psu
} // namespace eez
