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

#include <eez/modules/mcu/touch.h>

#include <eez/platform/simulator/events.h>

#include <eez/gui/gui.h>

using namespace eez::platform::simulator;

namespace eez {
namespace mcu {
namespace touch {

void read(bool &isPressed, int &x, int &y) {
    readEvents();

    if (g_mouseButton1IsPressed) {
        isPressed = true;
    } else {
        isPressed = false;
    }

	x = g_mouseX;
	y = g_mouseY;
}

} // namespace touch
} // namespace mcu

namespace gui {

void data_touch_raw_x(data::DataOperationEnum operation, data::Cursor &cursor, data::Value &value) {
    if (operation == data::DATA_OPERATION_GET) {
        value = g_mouseX;
    }
}

void data_touch_raw_y(data::DataOperationEnum operation, data::Cursor &cursor, data::Value &value) {
    if (operation == data::DATA_OPERATION_GET) {
        value = g_mouseY;
    }
}

void data_touch_raw_z1(data::DataOperationEnum operation, data::Cursor &cursor, data::Value &value) {
    if (operation == data::DATA_OPERATION_GET) {
        value = 0;
    }
}

void data_touch_raw_pressed(data::DataOperationEnum operation, data::Cursor &cursor, data::Value &value) {
    if (operation == data::DATA_OPERATION_GET) {
        value = g_mouseButton1IsPressed;
    }
}

} // namespace gui

} // namespace eez
