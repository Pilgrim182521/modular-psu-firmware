enum DataEnum {
    DATA_ID_NONE = 0,
    DATA_ID_CHANNELS = 1,
    DATA_ID_CHANNEL_STATUS = 2,
    DATA_ID_CHANNEL_OUTPUT_STATE = 3,
    DATA_ID_CHANNEL_IS_CC = 4,
    DATA_ID_CHANNEL_IS_CV = 5,
    DATA_ID_CHANNEL_U_SET = 6,
    DATA_ID_CHANNEL_U_MON = 7,
    DATA_ID_CHANNEL_U_MON_DAC = 8,
    DATA_ID_CHANNEL_U_LIMIT = 9,
    DATA_ID_CHANNEL_U_EDIT = 10,
    DATA_ID_CHANNEL_I_SET = 11,
    DATA_ID_CHANNEL_I_MON = 12,
    DATA_ID_CHANNEL_I_MON_DAC = 13,
    DATA_ID_CHANNEL_I_LIMIT = 14,
    DATA_ID_CHANNEL_I_EDIT = 15,
    DATA_ID_CHANNEL_P_MON = 16,
    DATA_ID_CHANNEL_OTHER_VALUE_MON = 17,
    DATA_ID_CHANNELS_IS_MAX_VIEW = 18,
    DATA_ID_CHANNELS_VIEW_MODE = 19,
    DATA_ID_CHANNELS_VIEW_MODE_IN_DEFAULT = 20,
    DATA_ID_CHANNELS_VIEW_MODE_IN_MAX = 21,
    DATA_ID_SLOT_MAX_CHANNEL_INDEX = 22,
    DATA_ID_SLOT_MAX_VIEW = 23,
    DATA_ID_SLOT_MIN1_CHANNEL_INDEX = 24,
    DATA_ID_SLOT_MIN1_VIEW = 25,
    DATA_ID_SLOT_MIN2_CHANNEL_INDEX = 26,
    DATA_ID_SLOT_MIN2_VIEW = 27,
    DATA_ID_SLOT_MICRO1_VIEW = 28,
    DATA_ID_SLOT_MICRO2_VIEW = 29,
    DATA_ID_SLOT_MICRO3_VIEW = 30,
    DATA_ID_CHANNEL_DISPLAY_VALUE1 = 31,
    DATA_ID_CHANNEL_DISPLAY_VALUE2 = 32,
    DATA_ID_OVP = 33,
    DATA_ID_OCP = 34,
    DATA_ID_OPP = 35,
    DATA_ID_OTP_CH = 36,
    DATA_ID_OTP_AUX = 37,
    DATA_ID_ALERT_MESSAGE = 38,
    DATA_ID_ALERT_MESSAGE_2 = 39,
    DATA_ID_ALERT_MESSAGE_3 = 40,
    DATA_ID_EDIT_VALUE = 41,
    DATA_ID_EDIT_UNIT = 42,
    DATA_ID_EDIT_INFO = 43,
    DATA_ID_EDIT_MODE_INTERACTIVE_MODE_SELECTOR = 44,
    DATA_ID_EDIT_STEPS = 45,
    DATA_ID_MASTER_INFO = 46,
    DATA_ID_MASTER_TEST_RESULT = 47,
    DATA_ID_FIRMWARE_INFO = 48,
    DATA_ID_KEYPAD_TEXT = 49,
    DATA_ID_KEYPAD_MODE = 50,
    DATA_ID_KEYPAD_OPTION1_TEXT = 51,
    DATA_ID_KEYPAD_OPTION1_ENABLED = 52,
    DATA_ID_KEYPAD_OPTION2_TEXT = 53,
    DATA_ID_KEYPAD_OPTION2_ENABLED = 54,
    DATA_ID_KEYPAD_SIGN_ENABLED = 55,
    DATA_ID_KEYPAD_DOT_ENABLED = 56,
    DATA_ID_KEYPAD_UNIT_ENABLED = 57,
    DATA_ID_CHANNEL_LABEL = 58,
    DATA_ID_CHANNEL_SHORT_LABEL = 59,
    DATA_ID_CHANNEL_TEMP_STATUS = 60,
    DATA_ID_CHANNEL_TEMP = 61,
    DATA_ID_CHANNEL_ON_TIME_TOTAL = 62,
    DATA_ID_CHANNEL_ON_TIME_LAST = 63,
    DATA_ID_CHANNEL_CALIBRATION_STATUS = 64,
    DATA_ID_CHANNEL_CALIBRATION_STATE = 65,
    DATA_ID_CHANNEL_CALIBRATION_DATE = 66,
    DATA_ID_CHANNEL_CALIBRATION_REMARK = 67,
    DATA_ID_CHANNEL_CALIBRATION_STEP_IS_SET_REMARK_STEP = 68,
    DATA_ID_CHANNEL_CALIBRATION_STEP_NUM = 69,
    DATA_ID_CHANNEL_CALIBRATION_STEP_STATUS = 70,
    DATA_ID_CHANNEL_CALIBRATION_STEP_LEVEL_VALUE = 71,
    DATA_ID_CHANNEL_CALIBRATION_STEP_VALUE = 72,
    DATA_ID_CHANNEL_CALIBRATION_STEP_PREV_ENABLED = 73,
    DATA_ID_CHANNEL_CALIBRATION_STEP_NEXT_ENABLED = 74,
    DATA_ID_CAL_CH_U_MIN = 75,
    DATA_ID_CAL_CH_U_MID = 76,
    DATA_ID_CAL_CH_U_MAX = 77,
    DATA_ID_CAL_CH_I0_MIN = 78,
    DATA_ID_CAL_CH_I0_MID = 79,
    DATA_ID_CAL_CH_I0_MAX = 80,
    DATA_ID_CAL_CH_I1_MIN = 81,
    DATA_ID_CAL_CH_I1_MID = 82,
    DATA_ID_CAL_CH_I1_MAX = 83,
    DATA_ID_CHANNEL_PROTECTION_STATUS = 84,
    DATA_ID_CHANNEL_PROTECTION_OVP_STATE = 85,
    DATA_ID_CHANNEL_PROTECTION_OVP_TYPE = 86,
    DATA_ID_CHANNEL_PROTECTION_OVP_LEVEL = 87,
    DATA_ID_CHANNEL_PROTECTION_OVP_DELAY = 88,
    DATA_ID_CHANNEL_PROTECTION_OVP_LIMIT = 89,
    DATA_ID_CHANNEL_PROTECTION_OCP_STATE = 90,
    DATA_ID_CHANNEL_PROTECTION_OCP_DELAY = 91,
    DATA_ID_CHANNEL_PROTECTION_OCP_LIMIT = 92,
    DATA_ID_CHANNEL_PROTECTION_OCP_MAX_CURRENT_LIMIT_CAUSE = 93,
    DATA_ID_CHANNEL_PROTECTION_OPP_STATE = 94,
    DATA_ID_CHANNEL_PROTECTION_OPP_LEVEL = 95,
    DATA_ID_CHANNEL_PROTECTION_OPP_DELAY = 96,
    DATA_ID_CHANNEL_PROTECTION_OPP_LIMIT = 97,
    DATA_ID_CHANNEL_PROTECTION_OTP_INSTALLED = 98,
    DATA_ID_CHANNEL_PROTECTION_OTP_STATE = 99,
    DATA_ID_CHANNEL_PROTECTION_OTP_LEVEL = 100,
    DATA_ID_CHANNEL_PROTECTION_OTP_DELAY = 101,
    DATA_ID_EVENT_QUEUE_LAST_EVENT_TYPE = 102,
    DATA_ID_EVENT_QUEUE_EVENTS = 103,
    DATA_ID_EVENT_QUEUE_EVENT_TYPE = 104,
    DATA_ID_EVENT_QUEUE_EVENT_MESSAGE = 105,
    DATA_ID_EVENT_QUEUE_SELECTED_EVENT_MESSAGE = 106,
    DATA_ID_CHANNEL_RSENSE_STATUS = 107,
    DATA_ID_CHANNEL_RPROG_INSTALLED = 108,
    DATA_ID_CHANNEL_RPROG_STATUS = 109,
    DATA_ID_CHANNEL_TRACKING_IS_ENABLED = 110,
    DATA_ID_CHANNEL_TRACKING_IS_ALLOWED = 111,
    DATA_ID_CHANNEL_IS_PAR_SER_COUPLED_OR_TRACKED = 112,
    DATA_ID_COUPLING_TYPE = 113,
    DATA_ID_CHANNEL_COUPLING_IS_SERIES = 114,
    DATA_ID_SYS_ON_TIME_TOTAL = 115,
    DATA_ID_SYS_ON_TIME_LAST = 116,
    DATA_ID_SYS_TEMP_AUX_STATUS = 117,
    DATA_ID_SYS_TEMP_AUX_OTP_STATE = 118,
    DATA_ID_SYS_TEMP_AUX_OTP_LEVEL = 119,
    DATA_ID_SYS_TEMP_AUX_OTP_DELAY = 120,
    DATA_ID_SYS_TEMP_AUX_OTP_IS_TRIPPED = 121,
    DATA_ID_SYS_TEMP_AUX = 122,
    DATA_ID_SYS_INFO_FIRMWARE_VER = 123,
    DATA_ID_SYS_INFO_SERIAL_NO = 124,
    DATA_ID_SYS_INFO_SCPI_VER = 125,
    DATA_ID_SYS_INFO_CPU = 126,
    DATA_ID_SYS_INFO_FAN_STATUS = 127,
    DATA_ID_SYS_INFO_FAN_SPEED = 128,
    DATA_ID_CHANNEL_BOARD_INFO_LABEL = 129,
    DATA_ID_CHANNEL_BOARD_INFO_REVISION = 130,
    DATA_ID_DATE_TIME_DATE = 131,
    DATA_ID_DATE_TIME_YEAR = 132,
    DATA_ID_DATE_TIME_MONTH = 133,
    DATA_ID_DATE_TIME_DAY = 134,
    DATA_ID_DATE_TIME_TIME = 135,
    DATA_ID_DATE_TIME_HOUR = 136,
    DATA_ID_DATE_TIME_MINUTE = 137,
    DATA_ID_DATE_TIME_SECOND = 138,
    DATA_ID_DATE_TIME_TIME_ZONE = 139,
    DATA_ID_DATE_TIME_DST = 140,
    DATA_ID_SET_PAGE_DIRTY = 141,
    DATA_ID_PROFILES_LIST = 142,
    DATA_ID_PROFILES_AUTO_RECALL_STATUS = 143,
    DATA_ID_PROFILES_AUTO_RECALL_LOCATION = 144,
    DATA_ID_PROFILE_STATUS = 145,
    DATA_ID_PROFILE_LABEL = 146,
    DATA_ID_PROFILE_REMARK = 147,
    DATA_ID_PROFILE_IS_AUTO_RECALL_LOCATION = 148,
    DATA_ID_PROFILE_CHANNEL_U_SET = 149,
    DATA_ID_PROFILE_CHANNEL_I_SET = 150,
    DATA_ID_PROFILE_CHANNEL_OUTPUT_STATE = 151,
    DATA_ID_ETHERNET_INSTALLED = 152,
    DATA_ID_ETHERNET_ENABLED = 153,
    DATA_ID_MQTT_ENABLED = 154,
    DATA_ID_ETHERNET_STATUS = 155,
    DATA_ID_MQTT_CONNECTION_STATE = 156,
    DATA_ID_ETHERNET_IP_ADDRESS = 157,
    DATA_ID_ETHERNET_DNS = 158,
    DATA_ID_ETHERNET_GATEWAY = 159,
    DATA_ID_ETHERNET_SUBNET_MASK = 160,
    DATA_ID_ETHERNET_SCPI_PORT = 161,
    DATA_ID_ETHERNET_IS_CONNECTED = 162,
    DATA_ID_ETHERNET_DHCP = 163,
    DATA_ID_ETHERNET_MAC = 164,
    DATA_ID_CHANNEL_IS_VOLTAGE_BALANCED = 165,
    DATA_ID_CHANNEL_IS_CURRENT_BALANCED = 166,
    DATA_ID_SYS_OUTPUT_PROTECTION_COUPLED = 167,
    DATA_ID_SYS_SHUTDOWN_WHEN_PROTECTION_TRIPPED = 168,
    DATA_ID_SYS_FORCE_DISABLING_ALL_OUTPUTS_ON_POWER_UP = 169,
    DATA_ID_SYS_PASSWORD_IS_SET = 170,
    DATA_ID_SYS_RL_STATE = 171,
    DATA_ID_SYS_SOUND_IS_ENABLED = 172,
    DATA_ID_SYS_SOUND_IS_CLICK_ENABLED = 173,
    DATA_ID_SYS_SOUND_ENABLED = 174,
    DATA_ID_CHANNEL_DISPLAY_VIEW_SETTINGS_DISPLAY_VALUE1 = 175,
    DATA_ID_CHANNEL_DISPLAY_VIEW_SETTINGS_DISPLAY_VALUE2 = 176,
    DATA_ID_CHANNEL_DISPLAY_VIEW_SETTINGS_YT_VIEW_RATE = 177,
    DATA_ID_SYS_ENCODER_CONFIRMATION_MODE = 178,
    DATA_ID_SYS_ENCODER_MOVING_UP_SPEED = 179,
    DATA_ID_SYS_ENCODER_MOVING_DOWN_SPEED = 180,
    DATA_ID_SYS_ENCODER_INSTALLED = 181,
    DATA_ID_SYS_DISPLAY_STATE = 182,
    DATA_ID_SYS_DISPLAY_BRIGHTNESS = 183,
    DATA_ID_CHANNEL_TRIGGER_MODE = 184,
    DATA_ID_CHANNEL_TRIGGER_ON_LIST_STOP = 185,
    DATA_ID_CHANNEL_U_TRIGGER_VALUE = 186,
    DATA_ID_CHANNEL_I_TRIGGER_VALUE = 187,
    DATA_ID_CHANNEL_LIST_COUNT = 188,
    DATA_ID_CHANNEL_LISTS = 189,
    DATA_ID_RAMP_AND_DELAY_LIST = 190,
    DATA_ID_CHANNEL_LIST_INDEX = 191,
    DATA_ID_CHANNEL_LIST_DWELL = 192,
    DATA_ID_CHANNEL_LIST_DWELL_ENABLED = 193,
    DATA_ID_CHANNEL_LIST_VOLTAGE = 194,
    DATA_ID_CHANNEL_LIST_VOLTAGE_ENABLED = 195,
    DATA_ID_CHANNEL_LIST_CURRENT = 196,
    DATA_ID_CHANNEL_LIST_CURRENT_ENABLED = 197,
    DATA_ID_CHANNEL_LISTS_PREVIOUS_PAGE_ENABLED = 198,
    DATA_ID_CHANNEL_LISTS_NEXT_PAGE_ENABLED = 199,
    DATA_ID_CHANNEL_LISTS_CURSOR = 200,
    DATA_ID_CHANNEL_LISTS_INSERT_MENU_ENABLED = 201,
    DATA_ID_CHANNEL_LISTS_DELETE_MENU_ENABLED = 202,
    DATA_ID_CHANNEL_LISTS_DELETE_ROW_ENABLED = 203,
    DATA_ID_CHANNEL_LISTS_CLEAR_COLUMN_ENABLED = 204,
    DATA_ID_CHANNEL_LISTS_DELETE_ROWS_ENABLED = 205,
    DATA_ID_TRIGGER_SOURCE = 206,
    DATA_ID_TRIGGER_DELAY = 207,
    DATA_ID_TRIGGER_INITIATE_CONTINUOUSLY = 208,
    DATA_ID_TRIGGER_IS_INITIATED = 209,
    DATA_ID_TRIGGER_IS_MANUAL = 210,
    DATA_ID_CHANNEL_HAS_SUPPORT_FOR_CURRENT_DUAL_RANGE = 211,
    DATA_ID_CHANNEL_RANGES_SUPPORTED = 212,
    DATA_ID_CHANNEL_RANGES_MODE = 213,
    DATA_ID_CHANNEL_RANGES_AUTO_RANGING = 214,
    DATA_ID_CHANNEL_RANGES_CURRENTLY_SELECTED = 215,
    DATA_ID_TEXT_MESSAGE = 216,
    DATA_ID_SERIAL_STATUS = 217,
    DATA_ID_SERIAL_ENABLED = 218,
    DATA_ID_SERIAL_IS_CONNECTED = 219,
    DATA_ID_CHANNEL_LIST_COUNTDOWN = 220,
    DATA_ID_CHANNEL_RAMP_COUNTDOWN = 221,
    DATA_ID_IO_PINS = 222,
    DATA_ID_IO_PINS_INHIBIT_STATE = 223,
    DATA_ID_IO_PIN_NUMBER = 224,
    DATA_ID_IO_PIN_POLARITY = 225,
    DATA_ID_IO_PIN_FUNCTION_NAME = 226,
    DATA_ID_NTP_ENABLED = 227,
    DATA_ID_NTP_SERVER = 228,
    DATA_ID_SYS_DISPLAY_BACKGROUND_LUMINOSITY_STEP = 229,
    DATA_ID_PROGRESS = 230,
    DATA_ID_TOUCH_CALIBRATION_POINT = 231,
    DATA_ID_SELECTED_THEME = 232,
    DATA_ID_CHANNEL_TITLE = 233,
    DATA_ID_CHANNEL_SHORT_TITLE = 234,
    DATA_ID_CHANNEL_SHORT_TITLE_WITH_COLON = 235,
    DATA_ID_CHANNEL_SHORT_TITLE_WITHOUT_TRACKING_ICON = 236,
    DATA_ID_CHANNEL_LONG_TITLE = 237,
    DATA_ID_ANIMATIONS_DURATION = 238,
    DATA_ID_SLOT1_INFO = 239,
    DATA_ID_SLOT2_INFO = 240,
    DATA_ID_SLOT3_INFO = 241,
    DATA_ID_SLOT1_TEST_RESULT = 242,
    DATA_ID_SLOT2_TEST_RESULT = 243,
    DATA_ID_SLOT3_TEST_RESULT = 244,
    DATA_ID_SLOT_DEFAULT1_VIEW = 245,
    DATA_ID_SLOT_DEFAULT2_VIEW = 246,
    DATA_ID_SLOT_DEFAULT3_VIEW = 247,
    DATA_ID_SLOT1_CHANNEL_INDEX = 248,
    DATA_ID_SLOT2_CHANNEL_INDEX = 249,
    DATA_ID_SLOT3_CHANNEL_INDEX = 250,
    DATA_ID_SLOT_DEF_2CH_VIEW = 251,
    DATA_ID_SLOT_MAX_2CH_VIEW = 252,
    DATA_ID_SLOT_MIN_2CH_VIEW = 253,
    DATA_ID_SLOT_MICRO_2CH_VIEW = 254,
    DATA_ID_SLOT_2CH_CH1_INDEX = 255,
    DATA_ID_SLOT_2CH_CH2_INDEX = 256,
    DATA_ID_BATTERY = 257,
    DATA_ID_IO_PIN_STATE = 258,
    DATA_ID_CHANNEL_DPROG = 259,
    DATA_ID_CHANNEL_DPROG_INSTALLED = 260,
    DATA_ID_SYS_INFO_SDCARD_STATUS = 261,
    DATA_ID_SYS_INFO_HAS_ERROR = 262,
    DATA_ID_SYS_INFO_BATTERY_STATUS = 263,
    DATA_ID_SYS_FAN_MODE = 264,
    DATA_ID_SYS_FAN_SPEED = 265,
    DATA_ID_IS_COUPLING_TYPE_UNCOUPLED = 266,
    DATA_ID_IS_COUPLING_TYPE_PARALLEL = 267,
    DATA_ID_IS_COUPLING_TYPE_COMMON_GND = 268,
    DATA_ID_IS_COUPLING_TYPE_SPLIT_RAILS = 269,
    DATA_ID_IS_TRACKING_ALLOWED = 270,
    DATA_ID_IS_COUPLING_PARALLEL_ALLOWED = 271,
    DATA_ID_IS_COUPLING_SERIES_ALLOWED = 272,
    DATA_ID_CHANNEL_COUPLING_ENABLE_TRACKING_MODE = 273,
    DATA_ID_CHANNEL_ACTIVE_COUPLED_LED = 274,
    DATA_ID_IS_COUPLING_TYPE_SERIES = 275,
    DATA_ID_IS_COUPLED_OR_TRACKED = 276,
    DATA_ID_OVERLAY = 277,
    DATA_ID_CHANNELS_WITH_LIST_COUNTER_VISIBLE = 278,
    DATA_ID_CHANNELS_WITH_RAMP_COUNTER_VISIBLE = 279,
    DATA_ID_DLOG_STATE = 280,
    DATA_ID_DLOG_TOGGLE_STATE = 281,
    DATA_ID_RECORDING = 282,
    DATA_ID_CHANNEL_HISTORY_VALUES = 283,
    DATA_ID_RECORDING_READY = 284,
    DATA_ID_NONDRAG_OVERLAY = 285,
    DATA_ID_DLOG_SINGLE_VALUE_OVERLAY = 286,
    DATA_ID_DLOG_MULTIPLE_VALUES_OVERLAY = 287,
    DATA_ID_DLOG_VISIBLE_VALUES = 288,
    DATA_ID_DLOG_VISIBLE_VALUE_LABEL = 289,
    DATA_ID_DLOG_VISIBLE_VALUE_DIV = 290,
    DATA_ID_DLOG_VISIBLE_VALUE_OFFSET = 291,
    DATA_ID_DLOG_VISIBLE_VALUE_CURSOR = 292,
    DATA_ID_DLOG_ALL_VALUES = 293,
    DATA_ID_DLOG_VALUE_LABEL = 294,
    DATA_ID_DLOG_CURRENT_TIME = 295,
    DATA_ID_DLOG_FILE_LENGTH = 296,
    DATA_ID_DLOG_X_AXIS_OFFSET = 297,
    DATA_ID_DLOG_X_AXIS_DIV = 298,
    DATA_ID_DLOG_X_AXIS_MAX_VALUE = 299,
    DATA_ID_DLOG_X_AXIS_MAX_VALUE_LABEL = 300,
    DATA_ID_IS_SINGLE_PAGE_ON_STACK = 301,
    DATA_ID_IS_SHOW_LIVE_RECORDING = 302,
    DATA_ID_DLOG_VIEW_STATE = 303,
    DATA_ID_DLOG_PERIOD = 304,
    DATA_ID_DLOG_DURATION = 305,
    DATA_ID_DLOG_VOLTAGE_ENABLED = 306,
    DATA_ID_DLOG_CURRENT_ENABLED = 307,
    DATA_ID_DLOG_POWER_ENABLED = 308,
    DATA_ID_DLOG_START_ENABLED = 309,
    DATA_ID_DLOG_FILE_NAME = 310,
    DATA_ID_DLOG_VALUE_STATE = 311,
    DATA_ID_SLOT_MAX_2CH_MIN_VIEW = 312,
    DATA_ID_CHANNEL_OFF_LABEL = 313,
    DATA_ID_FILE_MANAGER_FILES = 314,
    DATA_ID_FILE_MANAGER_FILE_NAME = 315,
    DATA_ID_FILE_MANAGER_FILE_DATE_TIME = 316,
    DATA_ID_FILE_MANAGER_FILE_SIZE = 317,
    DATA_ID_FILE_MANAGER_FILE_SELECTED = 318,
    DATA_ID_FILE_MANAGER_STATE = 319,
    DATA_ID_FILE_MANAGER_IS_ROOT_DIRECTORY = 320,
    DATA_ID_FILE_MANAGER_CURRENT_DIRECTORY = 321,
    DATA_ID_FILE_MANAGER_IS_DIRECTORY = 322,
    DATA_ID_FILE_MANAGER_FILE_TYPE = 323,
    DATA_ID_FILE_MANAGER_OPEN_FILE_ENABLED = 324,
    DATA_ID_FILE_MANAGER_UPLOAD_FILE_ENABLED = 325,
    DATA_ID_FILE_MANAGER_RENAME_FILE_ENABLED = 326,
    DATA_ID_FILE_MANAGER_DELETE_FILE_ENABLED = 327,
    DATA_ID_FILE_MANAGER_OPENED_IMAGE = 328,
    DATA_ID_SCRIPT_INFO = 329,
    DATA_ID_SCRIPT_IS_STARTED = 330,
    DATA_ID_KEYPAD_OK_ENABLED = 331,
    DATA_ID_ETHERNET_HOST_NAME = 332,
    DATA_ID_MQTT_HOST = 333,
    DATA_ID_MQTT_PORT = 334,
    DATA_ID_MQTT_USERNAME = 335,
    DATA_ID_MQTT_PASSWORD = 336,
    DATA_ID_MQTT_PERIOD = 337,
    DATA_ID_DLOG_VIEW_SHOW_LEGEND = 338,
    DATA_ID_DLOG_VIEW_SHOW_LABELS = 339,
    DATA_ID_IS_ANY_COUPLING_ALLOWED = 340,
    DATA_ID_IS_COUPLING_SPLIT_RAILS_ALLOWED = 341,
    DATA_ID_LIST_COUNTER_LABEL = 342,
    DATA_ID_RAMP_COUNTER_LABEL = 343,
    DATA_ID_MODULE_SPECIFIC_CH_SETTINGS = 344,
    DATA_ID_CHANNEL_FIRMWARE_VERSION = 345,
    DATA_ID_FILE_MANAGER_BROWSER_TITLE = 346,
    DATA_ID_CHANNEL_HAS_ERROR_SETTINGS = 347,
    DATA_ID_CHANNEL_SETTINGS_PAGE = 348,
    DATA_ID_IS_RESET_BY_IWDG = 349,
    DATA_ID_DLOG_ENABLED = 350,
    DATA_ID_FILE_MANAGER_BROWSER_IS_SAVE_DIALOG = 351,
    DATA_ID_CHANNEL_CALIBRATION_STEP_NOTE = 352,
    DATA_ID_CHANNEL_CALIBRATION_HAS_STEP_NOTE = 353,
    DATA_ID_FILE_MANAGER_STORAGE_INFO = 354,
    DATA_ID_FILE_MANAGER_STORAGE_ALARM = 355,
    DATA_ID_EVENT_QUEUE_IS_LONG_MESSAGE_TEXT = 356,
    DATA_ID_EVENT_QUEUE_EVENT_LONG_MESSAGE_OVERLAY = 357,
    DATA_ID_EVENT_QUEUE_EVENT_IS_SELECTED = 358,
    DATA_ID_DATE_TIME_FORMAT = 359,
    DATA_ID_DATE_TIME_FORMAT_IS_DMY = 360,
    DATA_ID_DATE_TIME_FORMAT_IS_24H = 361,
    DATA_ID_DATE_TIME_AM_PM = 362,
    DATA_ID_IS_MULTI_TRACKING = 363,
    DATA_ID_CHANNEL_COPY_AVAILABLE = 364,
    DATA_ID_CHANNEL_RSENSE_INSTALLED = 365,
    DATA_ID_FILE_MANAGER_SORT_FILES_OPTION = 366,
    DATA_ID_CHANNEL_INFO_BRAND = 367,
    DATA_ID_CHANNEL_INFO_SERIAL = 368,
    DATA_ID_FILE_MANAGER_LIST_VIEW = 369,
    DATA_ID_FILE_MANAGER_IS_LIST_VIEW_OPTION_AVAILABLE = 370,
    DATA_ID_FILE_MANAGER_FILE_ICON = 371,
    DATA_ID_FILE_MANAGER_LAYOUT = 372,
    DATA_ID_FILE_MANAGER_FILE_DESCRIPTION = 373,
    DATA_ID_TOUCH_RAW_X = 374,
    DATA_ID_TOUCH_RAW_Y = 375,
    DATA_ID_TOUCH_RAW_Z1 = 376,
    DATA_ID_TOUCH_RAW_PRESSED = 377,
    DATA_ID_TOUCH_CALIBRATED_X = 378,
    DATA_ID_TOUCH_CALIBRATED_Y = 379,
    DATA_ID_TOUCH_CALIBRATED_PRESSED = 380,
    DATA_ID_TOUCH_FILTERED_X = 381,
    DATA_ID_TOUCH_FILTERED_Y = 382,
    DATA_ID_TOUCH_FILTERED_PRESSED = 383,
    DATA_ID_CAN_SHOW_PREVIOUS_PAGE = 384,
    DATA_ID_FILE_MANAGER_FILE_HAS_DESCRIPTION = 385,
    DATA_ID_FILE_MANAGER_IMAGE_OPEN_STATE = 386,
    DATA_ID_FILE_MANAGER_IMAGE_OPEN_PROGRESS = 387,
    DATA_ID_ALERT_MESSAGE_IS_SET = 388,
    DATA_ID_ASYNC_PROGRESS = 389,
    DATA_ID_IO_PIN_FUNCTION = 390,
    DATA_ID_IO_PIN_PWM_FREQUENCY = 391,
    DATA_ID_IO_PIN_PWM_DUTY = 392,
    DATA_ID_CHANNEL_VOLTAGE_RAMP_DURATION = 393,
    DATA_ID_CHANNEL_CURRENT_RAMP_DURATION = 394,
    DATA_ID_CHANNEL_OUTPUT_DELAY = 395,
    DATA_ID_DEBUG_VARIABLES = 396,
    DATA_ID_DEBUG_VARIABLE_NAME = 397,
    DATA_ID_DEBUG_VARIABLE_VALUE = 398,
    DATA_ID_CHANNEL_RAMP_STATE = 399,
    DATA_ID_RAMP_AND_DELAY_LIST_SCROLLBAR_ENABLED = 400
};

void data_none(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_output_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_is_cc(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_is_cv(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_mon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_mon_dac(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_limit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_edit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_mon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_mon_dac(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_limit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_edit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_p_mon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_other_value_mon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_is_max_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_view_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_view_mode_in_default(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_view_mode_in_max(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_max_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_max_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_min1_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_min1_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_min2_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_min2_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_micro1_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_micro2_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_micro3_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_display_value1(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_display_value2(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ovp(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ocp(DataOperationEnum operation, Cursor cursor, Value &value);
void data_opp(DataOperationEnum operation, Cursor cursor, Value &value);
void data_otp_ch(DataOperationEnum operation, Cursor cursor, Value &value);
void data_otp_aux(DataOperationEnum operation, Cursor cursor, Value &value);
void data_alert_message(DataOperationEnum operation, Cursor cursor, Value &value);
void data_alert_message_2(DataOperationEnum operation, Cursor cursor, Value &value);
void data_alert_message_3(DataOperationEnum operation, Cursor cursor, Value &value);
void data_edit_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_edit_unit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_edit_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_edit_mode_interactive_mode_selector(DataOperationEnum operation, Cursor cursor, Value &value);
void data_edit_steps(DataOperationEnum operation, Cursor cursor, Value &value);
void data_master_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_master_test_result(DataOperationEnum operation, Cursor cursor, Value &value);
void data_firmware_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_text(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_option1_text(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_option1_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_option2_text(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_option2_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_sign_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_dot_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_unit_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_short_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_temp_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_temp(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_on_time_total(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_on_time_last(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_date(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_remark(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_is_set_remark_step(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_num(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_level_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_prev_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_next_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_u_min(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_u_mid(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_u_max(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i0_min(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i0_mid(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i0_max(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i1_min(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i1_mid(DataOperationEnum operation, Cursor cursor, Value &value);
void data_cal_ch_i1_max(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ovp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ovp_type(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ovp_level(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ovp_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ovp_limit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ocp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ocp_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ocp_limit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_ocp_max_current_limit_cause(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_opp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_opp_level(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_opp_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_opp_limit(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_otp_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_otp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_otp_level(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_protection_otp_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_last_event_type(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_events(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_event_type(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_event_message(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_selected_event_message(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_rsense_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_rprog_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_rprog_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_tracking_is_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_tracking_is_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_is_par_ser_coupled_or_tracked(DataOperationEnum operation, Cursor cursor, Value &value);
void data_coupling_type(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_coupling_is_series(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_on_time_total(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_on_time_last(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux_otp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux_otp_level(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux_otp_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux_otp_is_tripped(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_temp_aux(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_firmware_ver(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_serial_no(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_scpi_ver(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_cpu(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_fan_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_fan_speed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_board_info_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_board_info_revision(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_date(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_year(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_month(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_day(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_time(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_hour(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_minute(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_second(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_time_zone(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_dst(DataOperationEnum operation, Cursor cursor, Value &value);
void data_set_page_dirty(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profiles_list(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profiles_auto_recall_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profiles_auto_recall_location(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_remark(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_is_auto_recall_location(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_channel_u_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_channel_i_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_profile_channel_output_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_connection_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_ip_address(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_dns(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_gateway(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_subnet_mask(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_scpi_port(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_is_connected(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_dhcp(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_mac(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_is_voltage_balanced(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_is_current_balanced(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_output_protection_coupled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_shutdown_when_protection_tripped(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_force_disabling_all_outputs_on_power_up(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_password_is_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_rl_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_sound_is_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_sound_is_click_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_sound_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_display_view_settings_display_value1(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_display_view_settings_display_value2(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_display_view_settings_yt_view_rate(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_encoder_confirmation_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_encoder_moving_up_speed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_encoder_moving_down_speed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_encoder_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_display_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_display_brightness(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_trigger_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_trigger_on_list_stop(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_u_trigger_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_i_trigger_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_count(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ramp_and_delay_list(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_dwell(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_dwell_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_voltage(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_voltage_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_current(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_current_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_previous_page_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_next_page_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_cursor(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_insert_menu_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_delete_menu_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_delete_row_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_clear_column_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_lists_delete_rows_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_trigger_source(DataOperationEnum operation, Cursor cursor, Value &value);
void data_trigger_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_trigger_initiate_continuously(DataOperationEnum operation, Cursor cursor, Value &value);
void data_trigger_is_initiated(DataOperationEnum operation, Cursor cursor, Value &value);
void data_trigger_is_manual(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_has_support_for_current_dual_range(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ranges_supported(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ranges_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ranges_auto_ranging(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ranges_currently_selected(DataOperationEnum operation, Cursor cursor, Value &value);
void data_text_message(DataOperationEnum operation, Cursor cursor, Value &value);
void data_serial_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_serial_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_serial_is_connected(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_list_countdown(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ramp_countdown(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pins(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pins_inhibit_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_number(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_polarity(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_function_name(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ntp_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ntp_server(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_display_background_luminosity_step(DataOperationEnum operation, Cursor cursor, Value &value);
void data_progress(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_calibration_point(DataOperationEnum operation, Cursor cursor, Value &value);
void data_selected_theme(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_title(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_short_title(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_short_title_with_colon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_short_title_without_tracking_icon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_long_title(DataOperationEnum operation, Cursor cursor, Value &value);
void data_animations_duration(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot1_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot2_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot3_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot1_test_result(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot2_test_result(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot3_test_result(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_default1_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_default2_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_default3_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot1_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot2_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot3_channel_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_def_2ch_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_max_2ch_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_min_2ch_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_micro_2ch_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_2ch_ch1_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_2ch_ch2_index(DataOperationEnum operation, Cursor cursor, Value &value);
void data_battery(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_dprog(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_dprog_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_sdcard_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_has_error(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_info_battery_status(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_fan_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_sys_fan_speed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_type_uncoupled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_type_parallel(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_type_common_gnd(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_type_split_rails(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_tracking_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_parallel_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_series_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_coupling_enable_tracking_mode(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_active_coupled_led(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_type_series(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupled_or_tracked(DataOperationEnum operation, Cursor cursor, Value &value);
void data_overlay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_with_list_counter_visible(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channels_with_ramp_counter_visible(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_toggle_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_recording(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_history_values(DataOperationEnum operation, Cursor cursor, Value &value);
void data_recording_ready(DataOperationEnum operation, Cursor cursor, Value &value);
void data_nondrag_overlay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_single_value_overlay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_multiple_values_overlay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_visible_values(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_visible_value_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_visible_value_div(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_visible_value_offset(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_visible_value_cursor(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_all_values(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_value_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_current_time(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_file_length(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_x_axis_offset(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_x_axis_div(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_x_axis_max_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_x_axis_max_value_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_single_page_on_stack(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_show_live_recording(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_view_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_period(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_duration(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_voltage_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_current_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_power_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_start_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_file_name(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_value_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_slot_max_2ch_min_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_off_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_files(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_name(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_date_time(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_size(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_selected(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_is_root_directory(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_current_directory(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_is_directory(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_type(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_open_file_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_upload_file_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_rename_file_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_delete_file_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_opened_image(DataOperationEnum operation, Cursor cursor, Value &value);
void data_script_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_script_is_started(DataOperationEnum operation, Cursor cursor, Value &value);
void data_keypad_ok_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ethernet_host_name(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_host(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_port(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_username(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_password(DataOperationEnum operation, Cursor cursor, Value &value);
void data_mqtt_period(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_view_show_legend(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_view_show_labels(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_any_coupling_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_coupling_split_rails_allowed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_list_counter_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ramp_counter_label(DataOperationEnum operation, Cursor cursor, Value &value);
void data_module_specific_ch_settings(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_firmware_version(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_browser_title(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_has_error_settings(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_settings_page(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_reset_by_iwdg(DataOperationEnum operation, Cursor cursor, Value &value);
void data_dlog_enabled(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_browser_is_save_dialog(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_step_note(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_calibration_has_step_note(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_storage_info(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_storage_alarm(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_is_long_message_text(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_event_long_message_overlay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_event_queue_event_is_selected(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_format(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_format_is_dmy(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_format_is_24h(DataOperationEnum operation, Cursor cursor, Value &value);
void data_date_time_am_pm(DataOperationEnum operation, Cursor cursor, Value &value);
void data_is_multi_tracking(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_copy_available(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_rsense_installed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_sort_files_option(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_info_brand(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_info_serial(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_list_view(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_is_list_view_option_available(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_icon(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_layout(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_description(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_raw_x(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_raw_y(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_raw_z1(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_raw_pressed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_calibrated_x(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_calibrated_y(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_calibrated_pressed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_filtered_x(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_filtered_y(DataOperationEnum operation, Cursor cursor, Value &value);
void data_touch_filtered_pressed(DataOperationEnum operation, Cursor cursor, Value &value);
void data_can_show_previous_page(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_file_has_description(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_image_open_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_file_manager_image_open_progress(DataOperationEnum operation, Cursor cursor, Value &value);
void data_alert_message_is_set(DataOperationEnum operation, Cursor cursor, Value &value);
void data_async_progress(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_function(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_pwm_frequency(DataOperationEnum operation, Cursor cursor, Value &value);
void data_io_pin_pwm_duty(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_voltage_ramp_duration(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_current_ramp_duration(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_output_delay(DataOperationEnum operation, Cursor cursor, Value &value);
void data_debug_variables(DataOperationEnum operation, Cursor cursor, Value &value);
void data_debug_variable_name(DataOperationEnum operation, Cursor cursor, Value &value);
void data_debug_variable_value(DataOperationEnum operation, Cursor cursor, Value &value);
void data_channel_ramp_state(DataOperationEnum operation, Cursor cursor, Value &value);
void data_ramp_and_delay_list_scrollbar_enabled(DataOperationEnum operation, Cursor cursor, Value &value);

typedef void (*DataOperationsFunction)(DataOperationEnum operation, Cursor cursor, Value &value);

extern DataOperationsFunction g_dataOperationsFunctions[];

enum ActionsEnum {
    ACTION_ID_NONE = 0,
    ACTION_ID_CHANNEL_TOGGLE_OUTPUT = 1,
    ACTION_ID_EDIT = 2,
    ACTION_ID_EDIT_MODE_SLIDER = 3,
    ACTION_ID_EDIT_MODE_STEP = 4,
    ACTION_ID_EDIT_MODE_KEYPAD = 5,
    ACTION_ID_EXIT_EDIT_MODE = 6,
    ACTION_ID_TOGGLE_INTERACTIVE_MODE = 7,
    ACTION_ID_NON_INTERACTIVE_ENTER = 8,
    ACTION_ID_NON_INTERACTIVE_DISCARD = 9,
    ACTION_ID_KEYPAD_KEY = 10,
    ACTION_ID_KEYPAD_SPACE = 11,
    ACTION_ID_KEYPAD_BACK = 12,
    ACTION_ID_KEYPAD_CLEAR = 13,
    ACTION_ID_TOGGLE_KEYPAD_MODE = 14,
    ACTION_ID_KEYPAD_OK = 15,
    ACTION_ID_KEYPAD_CANCEL = 16,
    ACTION_ID_KEYPAD_SIGN = 17,
    ACTION_ID_KEYPAD_UNIT = 18,
    ACTION_ID_KEYPAD_OPTION1 = 19,
    ACTION_ID_KEYPAD_OPTION2 = 20,
    ACTION_ID_ENTER_TOUCH_CALIBRATION = 21,
    ACTION_ID_YES = 22,
    ACTION_ID_NO = 23,
    ACTION_ID_OK = 24,
    ACTION_ID_CANCEL = 25,
    ACTION_ID_LATER = 26,
    ACTION_ID_STAND_BY = 27,
    ACTION_ID_SHOW_PREVIOUS_PAGE = 28,
    ACTION_ID_SHOW_MAIN_PAGE = 29,
    ACTION_ID_SHOW_EVENT_QUEUE = 30,
    ACTION_ID_SHOW_SYS_SETTINGS = 31,
    ACTION_ID_SHOW_SYS_SETTINGS_TRIGGER = 32,
    ACTION_ID_SHOW_SYS_SETTINGS_IO = 33,
    ACTION_ID_SHOW_SYS_SETTINGS_DATE_TIME = 34,
    ACTION_ID_SHOW_SYS_SETTINGS_SCREEN_CALIBRATION = 35,
    ACTION_ID_SHOW_SYS_SETTINGS_DISPLAY = 36,
    ACTION_ID_SHOW_SYS_SETTINGS_SERIAL = 37,
    ACTION_ID_SHOW_SYS_SETTINGS_ETHERNET = 38,
    ACTION_ID_SHOW_SYS_SETTINGS_PROTECTIONS = 39,
    ACTION_ID_SHOW_SYS_SETTINGS_AUX_OTP = 40,
    ACTION_ID_SHOW_SYS_SETTINGS_SOUND = 41,
    ACTION_ID_SHOW_SYS_SETTINGS_ENCODER = 42,
    ACTION_ID_SHOW_SYS_INFO = 43,
    ACTION_ID_SHOW_MAIN_HELP_PAGE = 44,
    ACTION_ID_SHOW_EDIT_MODE_STEP_HELP = 45,
    ACTION_ID_SHOW_EDIT_MODE_SLIDER_HELP = 46,
    ACTION_ID_SHOW_CH_SETTINGS = 47,
    ACTION_ID_SHOW_CH_SETTINGS_PROT_CLEAR = 48,
    ACTION_ID_SHOW_CH_SETTINGS_PROT_OCP = 49,
    ACTION_ID_SHOW_CH_SETTINGS_PROT_OVP = 50,
    ACTION_ID_SHOW_CH_SETTINGS_PROT_OPP = 51,
    ACTION_ID_SHOW_CH_SETTINGS_PROT_OTP = 52,
    ACTION_ID_SHOW_CH_SETTINGS_TRIGGER = 53,
    ACTION_ID_SHOW_CH_SETTINGS_LISTS = 54,
    ACTION_ID_SHOW_CH_SETTINGS_ADV_OPTIONS = 55,
    ACTION_ID_SHOW_CH_SETTINGS_ADV_RANGES = 56,
    ACTION_ID_SHOW_CH_SETTINGS_ADV_VIEW = 57,
    ACTION_ID_SHOW_CH_SETTINGS_INFO = 58,
    ACTION_ID_SHOW_CH_SETTINGS_CAL = 59,
    ACTION_ID_EDIT_CALIBRATION_PASSWORD = 60,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_START = 61,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STEP_PREVIOUS = 62,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STEP_NEXT = 63,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STOP_AND_SHOW_PREVIOUS_PAGE = 64,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STOP_AND_SHOW_MAIN_PAGE = 65,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STEP_SET = 66,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_STEP_SET_LEVEL_VALUE = 67,
    ACTION_ID_CH_SETTINGS_CALIBRATION_WIZ_SAVE = 68,
    ACTION_ID_CH_SETTINGS_CALIBRATION_TOGGLE_ENABLE = 69,
    ACTION_ID_CH_SETTINGS_PROT_CLEAR = 70,
    ACTION_ID_CH_SETTINGS_PROT_CLEAR_AND_DISABLE = 71,
    ACTION_ID_CH_SETTINGS_PROT_TOGGLE_STATE = 72,
    ACTION_ID_CH_SETTINGS_PROT_TOGGLE_TYPE = 73,
    ACTION_ID_CH_SETTINGS_PROT_EDIT_LIMIT = 74,
    ACTION_ID_CH_SETTINGS_PROT_EDIT_LEVEL = 75,
    ACTION_ID_CH_SETTINGS_PROT_EDIT_DELAY = 76,
    ACTION_ID_SET = 77,
    ACTION_ID_DISCARD = 78,
    ACTION_ID_EDIT_FIELD = 79,
    ACTION_ID_CH_SETTINGS_ADV_REMOTE_TOGGLE_SENSE = 80,
    ACTION_ID_CH_SETTINGS_ADV_REMOTE_TOGGLE_PROGRAMMING = 81,
    ACTION_ID_DATE_TIME_SELECT_DST_RULE = 82,
    ACTION_ID_SHOW_USER_PROFILES = 83,
    ACTION_ID_SHOW_USER_PROFILE_SETTINGS = 84,
    ACTION_ID_PROFILES_TOGGLE_AUTO_RECALL = 85,
    ACTION_ID_PROFILE_TOGGLE_IS_AUTO_RECALL_LOCATION = 86,
    ACTION_ID_PROFILE_RECALL = 87,
    ACTION_ID_PROFILE_SAVE = 88,
    ACTION_ID_PROFILE_DELETE = 89,
    ACTION_ID_PROFILE_EDIT_REMARK = 90,
    ACTION_ID_TOGGLE_CHANNELS_VIEW_MODE = 91,
    ACTION_ID_ETHERNET_TOGGLE = 92,
    ACTION_ID_MQTT_TOGGLE = 93,
    ACTION_ID_ETHERNET_TOGGLE_DHCP = 94,
    ACTION_ID_ETHERNET_EDIT_MAC_ADDRESS = 95,
    ACTION_ID_ETHERNET_EDIT_STATIC_ADDRESS = 96,
    ACTION_ID_ETHERNET_EDIT_IP_ADDRESS = 97,
    ACTION_ID_ETHERNET_EDIT_DNS = 98,
    ACTION_ID_ETHERNET_EDIT_GATEWAY = 99,
    ACTION_ID_ETHERNET_EDIT_SUBNET_MASK = 100,
    ACTION_ID_ETHERNET_EDIT_SCPI_PORT = 101,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_TOGGLE_OUTPUT_PROTECTION_COUPLE = 102,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_TOGGLE_SHUTDOWN_WHEN_PROTECTION_TRIPPED = 103,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_TOGGLE_FORCE_DISABLING_ALL_OUTPUTS_ON_POWER_UP = 104,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_AUX_OTP_TOGGLE_STATE = 105,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_AUX_OTP_EDIT_LEVEL = 106,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_AUX_OTP_EDIT_DELAY = 107,
    ACTION_ID_SYS_SETTINGS_PROTECTIONS_AUX_OTP_CLEAR = 108,
    ACTION_ID_EDIT_SYSTEM_PASSWORD = 109,
    ACTION_ID_SYS_FRONT_PANEL_LOCK = 110,
    ACTION_ID_SYS_FRONT_PANEL_UNLOCK = 111,
    ACTION_ID_SYS_SETTINGS_SOUND_TOGGLE = 112,
    ACTION_ID_SYS_SETTINGS_SOUND_TOGGLE_CLICK = 113,
    ACTION_ID_CH_SETTINGS_ADV_VIEW_EDIT_DISPLAY_VALUE1 = 114,
    ACTION_ID_CH_SETTINGS_ADV_VIEW_EDIT_DISPLAY_VALUE2 = 115,
    ACTION_ID_CH_SETTINGS_ADV_VIEW_SWAP_DISPLAY_VALUES = 116,
    ACTION_ID_CH_SETTINGS_ADV_VIEW_EDIT_YTVIEW_RATE = 117,
    ACTION_ID_SYS_SETTINGS_ENCODER_TOGGLE_CONFIRMATION_MODE = 118,
    ACTION_ID_TURN_DISPLAY_OFF = 119,
    ACTION_ID_CH_SETTINGS_TRIGGER_EDIT_TRIGGER_MODE = 120,
    ACTION_ID_CH_SETTINGS_LISTS_EDIT_LIST_COUNT = 121,
    ACTION_ID_CH_SETTINGS_LISTS_EDIT_ON_LIST_STOP = 122,
    ACTION_ID_CHANNEL_LISTS_PREVIOUS_PAGE = 123,
    ACTION_ID_CHANNEL_LISTS_NEXT_PAGE = 124,
    ACTION_ID_CHANNEL_LISTS_EDIT = 125,
    ACTION_ID_SHOW_CHANNEL_LISTS_INSERT_MENU = 126,
    ACTION_ID_SHOW_CHANNEL_LISTS_DELETE_MENU = 127,
    ACTION_ID_CHANNEL_LISTS_INSERT_ROW_ABOVE = 128,
    ACTION_ID_CHANNEL_LISTS_INSERT_ROW_BELOW = 129,
    ACTION_ID_CHANNEL_LISTS_DELETE_ROW = 130,
    ACTION_ID_CHANNEL_LISTS_CLEAR_COLUMN = 131,
    ACTION_ID_CHANNEL_LISTS_DELETE_ROWS = 132,
    ACTION_ID_CHANNEL_LISTS_DELETE_ALL = 133,
    ACTION_ID_TRIGGER_SELECT_SOURCE = 134,
    ACTION_ID_TRIGGER_EDIT_DELAY = 135,
    ACTION_ID_TRIGGER_TOGGLE_INITIATE_CONTINUOUSLY = 136,
    ACTION_ID_TRIGGER_GENERATE_MANUAL = 137,
    ACTION_ID_TRIGGER_SHOW_GENERAL_SETTINGS = 138,
    ACTION_ID_SHOW_STAND_BY_MENU = 139,
    ACTION_ID_RESET = 140,
    ACTION_ID_CH_SETTINGS_ADV_RANGES_SELECT_MODE = 141,
    ACTION_ID_CH_SETTINGS_ADV_RANGES_TOGGLE_AUTO_RANGING = 142,
    ACTION_ID_IO_PIN_TOGGLE_POLARITY = 143,
    ACTION_ID_IO_PIN_SELECT_FUNCTION = 144,
    ACTION_ID_SERIAL_TOGGLE = 145,
    ACTION_ID_NTP_TOGGLE = 146,
    ACTION_ID_NTP_EDIT_SERVER = 147,
    ACTION_ID_SELECT_THEME = 148,
    ACTION_ID_TOGGLE_CHANNELS_MAX_VIEW = 149,
    ACTION_ID_EDIT_ANIMATIONS_DURATION = 150,
    ACTION_ID_RESTART = 151,
    ACTION_ID_USER_SWITCH_CLICKED = 152,
    ACTION_ID_IO_PIN_TOGGLE_STATE = 153,
    ACTION_ID_CH_SETTINGS_ADV_TOGGLE_DPROG = 154,
    ACTION_ID_SYS_SETTINGS_FAN_TOGGLE_MODE = 155,
    ACTION_ID_SYS_SETTINGS_FAN_EDIT_SPEED = 156,
    ACTION_ID_SHOW_SYS_SETTINGS_TRACKING = 157,
    ACTION_ID_SHOW_SYS_SETTINGS_COUPLING = 158,
    ACTION_ID_SET_COUPLING_UNCOUPLED = 159,
    ACTION_ID_SET_COUPLING_PARALLEL = 160,
    ACTION_ID_SET_COUPLING_SERIES = 161,
    ACTION_ID_SET_COUPLING_COMMON_GND = 162,
    ACTION_ID_SET_COUPLING_SPLIT_RAILS = 163,
    ACTION_ID_TOGGLE_CHANNEL_TRACKING = 164,
    ACTION_ID_TOGGLE_ENABLE_TRACKING_MODE_IN_COUPLING = 165,
    ACTION_ID_DRAG_OVERLAY = 166,
    ACTION_ID_DLOG_TOGGLE = 167,
    ACTION_ID_SHOW_DLOG_VIEW = 168,
    ACTION_ID_SELECT_USER_SWITCH_ACTION = 169,
    ACTION_ID_SHOW_FILE_MANAGER = 170,
    ACTION_ID_FILE_MANAGER_SELECT_FILE = 171,
    ACTION_ID_FILE_MANAGER_GO_TO_PARENT_DIRECTORY = 172,
    ACTION_ID_FILE_MANAGER_OPEN_FILE = 173,
    ACTION_ID_FILE_MANAGER_UPLOAD_FILE = 174,
    ACTION_ID_FILE_MANAGER_RENAME_FILE = 175,
    ACTION_ID_FILE_MANAGER_DELETE_FILE = 176,
    ACTION_ID_SHOW_DLOG_PARAMS = 177,
    ACTION_ID_DLOG_VOLTAGE_TOGGLE = 178,
    ACTION_ID_DLOG_CURRENT_TOGGLE = 179,
    ACTION_ID_DLOG_POWER_TOGGLE = 180,
    ACTION_ID_DLOG_VALUE_TOGGLE = 181,
    ACTION_ID_DLOG_EDIT_PERIOD = 182,
    ACTION_ID_DLOG_EDIT_DURATION = 183,
    ACTION_ID_DLOG_EDIT_FILE_NAME = 184,
    ACTION_ID_DLOG_START_RECORDING = 185,
    ACTION_ID_DLOG_VIEW_SHOW_OVERLAY_OPTIONS = 186,
    ACTION_ID_FILE_MANAGER_SORT_BY = 187,
    ACTION_ID_DLOG_AUTO_SCALE = 188,
    ACTION_ID_DLOG_UPLOAD = 189,
    ACTION_ID_ETHERNET_EDIT_HOST_NAME = 190,
    ACTION_ID_MQTT_EDIT_HOST = 191,
    ACTION_ID_MQTT_EDIT_PORT = 192,
    ACTION_ID_MQTT_EDIT_USERNAME = 193,
    ACTION_ID_MQTT_EDIT_PASSWORD = 194,
    ACTION_ID_MQTT_EDIT_PERIOD = 195,
    ACTION_ID_SHOW_SYS_SETTINGS_MQTT = 196,
    ACTION_ID_DLOG_SCALE_TO_FIT = 197,
    ACTION_ID_DLOG_VIEW_TOGGLE_LEGEND = 198,
    ACTION_ID_DLOG_VIEW_TOGGLE_LABELS = 199,
    ACTION_ID_DLOG_VIEW_SELECT_VISIBLE_VALUE = 200,
    ACTION_ID_CHANNEL_UPDATE_FIRMWARE = 201,
    ACTION_ID_SHUTDOWN = 202,
    ACTION_ID_SHOW_CHANNEL_LISTS_FILE_MENU = 203,
    ACTION_ID_CHANNEL_LISTS_FILE_IMPORT = 204,
    ACTION_ID_CHANNEL_LISTS_FILE_EXPORT = 205,
    ACTION_ID_FILE_MANAGER_NEW_FILE = 206,
    ACTION_ID_PROFILE_IMPORT = 207,
    ACTION_ID_PROFILE_EXPORT = 208,
    ACTION_ID_EVENT_QUEUE_FILTER = 209,
    ACTION_ID_EVENT_QUEUE_SELECT_EVENT = 210,
    ACTION_ID_DATE_TIME_SELECT_FORMAT = 211,
    ACTION_ID_DATE_TIME_TOGGLE_AM_PM = 212,
    ACTION_ID_EDIT_NO_FOCUS = 213,
    ACTION_ID_UNTRACK_ALL = 214,
    ACTION_ID_CH_SETTINGS_COPY = 215,
    ACTION_ID_SHOW_SYS_SETTINGS_ETHERNET_ERROR = 216,
    ACTION_ID_FILE_MANAGER_SELECT_LIST_VIEW = 217,
    ACTION_ID_SHOW_SYS_SETTINGS_RAMP_AND_DELAY = 218,
    ACTION_ID_CHANNEL_TOGGLE_RAMP_STATE = 219
};

void action_channel_toggle_output();
void action_edit();
void action_edit_mode_slider();
void action_edit_mode_step();
void action_edit_mode_keypad();
void action_exit_edit_mode();
void action_toggle_interactive_mode();
void action_non_interactive_enter();
void action_non_interactive_discard();
void action_keypad_key();
void action_keypad_space();
void action_keypad_back();
void action_keypad_clear();
void action_toggle_keypad_mode();
void action_keypad_ok();
void action_keypad_cancel();
void action_keypad_sign();
void action_keypad_unit();
void action_keypad_option1();
void action_keypad_option2();
void action_enter_touch_calibration();
void action_yes();
void action_no();
void action_ok();
void action_cancel();
void action_later();
void action_stand_by();
void action_show_previous_page();
void action_show_main_page();
void action_show_event_queue();
void action_show_sys_settings();
void action_show_sys_settings_trigger();
void action_show_sys_settings_io();
void action_show_sys_settings_date_time();
void action_show_sys_settings_screen_calibration();
void action_show_sys_settings_display();
void action_show_sys_settings_serial();
void action_show_sys_settings_ethernet();
void action_show_sys_settings_protections();
void action_show_sys_settings_aux_otp();
void action_show_sys_settings_sound();
void action_show_sys_settings_encoder();
void action_show_sys_info();
void action_show_main_help_page();
void action_show_edit_mode_step_help();
void action_show_edit_mode_slider_help();
void action_show_ch_settings();
void action_show_ch_settings_prot_clear();
void action_show_ch_settings_prot_ocp();
void action_show_ch_settings_prot_ovp();
void action_show_ch_settings_prot_opp();
void action_show_ch_settings_prot_otp();
void action_show_ch_settings_trigger();
void action_show_ch_settings_lists();
void action_show_ch_settings_adv_options();
void action_show_ch_settings_adv_ranges();
void action_show_ch_settings_adv_view();
void action_show_ch_settings_info();
void action_show_ch_settings_cal();
void action_edit_calibration_password();
void action_ch_settings_calibration_wiz_start();
void action_ch_settings_calibration_wiz_step_previous();
void action_ch_settings_calibration_wiz_step_next();
void action_ch_settings_calibration_wiz_stop_and_show_previous_page();
void action_ch_settings_calibration_wiz_stop_and_show_main_page();
void action_ch_settings_calibration_wiz_step_set();
void action_ch_settings_calibration_wiz_step_set_level_value();
void action_ch_settings_calibration_wiz_save();
void action_ch_settings_calibration_toggle_enable();
void action_ch_settings_prot_clear();
void action_ch_settings_prot_clear_and_disable();
void action_ch_settings_prot_toggle_state();
void action_ch_settings_prot_toggle_type();
void action_ch_settings_prot_edit_limit();
void action_ch_settings_prot_edit_level();
void action_ch_settings_prot_edit_delay();
void action_set();
void action_discard();
void action_edit_field();
void action_ch_settings_adv_remote_toggle_sense();
void action_ch_settings_adv_remote_toggle_programming();
void action_date_time_select_dst_rule();
void action_show_user_profiles();
void action_show_user_profile_settings();
void action_profiles_toggle_auto_recall();
void action_profile_toggle_is_auto_recall_location();
void action_profile_recall();
void action_profile_save();
void action_profile_delete();
void action_profile_edit_remark();
void action_toggle_channels_view_mode();
void action_ethernet_toggle();
void action_mqtt_toggle();
void action_ethernet_toggle_dhcp();
void action_ethernet_edit_mac_address();
void action_ethernet_edit_static_address();
void action_ethernet_edit_ip_address();
void action_ethernet_edit_dns();
void action_ethernet_edit_gateway();
void action_ethernet_edit_subnet_mask();
void action_ethernet_edit_scpi_port();
void action_sys_settings_protections_toggle_output_protection_couple();
void action_sys_settings_protections_toggle_shutdown_when_protection_tripped();
void action_sys_settings_protections_toggle_force_disabling_all_outputs_on_power_up();
void action_sys_settings_protections_aux_otp_toggle_state();
void action_sys_settings_protections_aux_otp_edit_level();
void action_sys_settings_protections_aux_otp_edit_delay();
void action_sys_settings_protections_aux_otp_clear();
void action_edit_system_password();
void action_sys_front_panel_lock();
void action_sys_front_panel_unlock();
void action_sys_settings_sound_toggle();
void action_sys_settings_sound_toggle_click();
void action_ch_settings_adv_view_edit_display_value1();
void action_ch_settings_adv_view_edit_display_value2();
void action_ch_settings_adv_view_swap_display_values();
void action_ch_settings_adv_view_edit_ytview_rate();
void action_sys_settings_encoder_toggle_confirmation_mode();
void action_turn_display_off();
void action_ch_settings_trigger_edit_trigger_mode();
void action_ch_settings_lists_edit_list_count();
void action_ch_settings_lists_edit_on_list_stop();
void action_channel_lists_previous_page();
void action_channel_lists_next_page();
void action_channel_lists_edit();
void action_show_channel_lists_insert_menu();
void action_show_channel_lists_delete_menu();
void action_channel_lists_insert_row_above();
void action_channel_lists_insert_row_below();
void action_channel_lists_delete_row();
void action_channel_lists_clear_column();
void action_channel_lists_delete_rows();
void action_channel_lists_delete_all();
void action_trigger_select_source();
void action_trigger_edit_delay();
void action_trigger_toggle_initiate_continuously();
void action_trigger_generate_manual();
void action_trigger_show_general_settings();
void action_show_stand_by_menu();
void action_reset();
void action_ch_settings_adv_ranges_select_mode();
void action_ch_settings_adv_ranges_toggle_auto_ranging();
void action_io_pin_toggle_polarity();
void action_io_pin_select_function();
void action_serial_toggle();
void action_ntp_toggle();
void action_ntp_edit_server();
void action_select_theme();
void action_toggle_channels_max_view();
void action_edit_animations_duration();
void action_restart();
void action_user_switch_clicked();
void action_io_pin_toggle_state();
void action_ch_settings_adv_toggle_dprog();
void action_sys_settings_fan_toggle_mode();
void action_sys_settings_fan_edit_speed();
void action_show_sys_settings_tracking();
void action_show_sys_settings_coupling();
void action_set_coupling_uncoupled();
void action_set_coupling_parallel();
void action_set_coupling_series();
void action_set_coupling_common_gnd();
void action_set_coupling_split_rails();
void action_toggle_channel_tracking();
void action_toggle_enable_tracking_mode_in_coupling();
void action_drag_overlay();
void action_dlog_toggle();
void action_show_dlog_view();
void action_select_user_switch_action();
void action_show_file_manager();
void action_file_manager_select_file();
void action_file_manager_go_to_parent_directory();
void action_file_manager_open_file();
void action_file_manager_upload_file();
void action_file_manager_rename_file();
void action_file_manager_delete_file();
void action_show_dlog_params();
void action_dlog_voltage_toggle();
void action_dlog_current_toggle();
void action_dlog_power_toggle();
void action_dlog_value_toggle();
void action_dlog_edit_period();
void action_dlog_edit_duration();
void action_dlog_edit_file_name();
void action_dlog_start_recording();
void action_dlog_view_show_overlay_options();
void action_file_manager_sort_by();
void action_dlog_auto_scale();
void action_dlog_upload();
void action_ethernet_edit_host_name();
void action_mqtt_edit_host();
void action_mqtt_edit_port();
void action_mqtt_edit_username();
void action_mqtt_edit_password();
void action_mqtt_edit_period();
void action_show_sys_settings_mqtt();
void action_dlog_scale_to_fit();
void action_dlog_view_toggle_legend();
void action_dlog_view_toggle_labels();
void action_dlog_view_select_visible_value();
void action_channel_update_firmware();
void action_shutdown();
void action_show_channel_lists_file_menu();
void action_channel_lists_file_import();
void action_channel_lists_file_export();
void action_file_manager_new_file();
void action_profile_import();
void action_profile_export();
void action_event_queue_filter();
void action_event_queue_select_event();
void action_date_time_select_format();
void action_date_time_toggle_am_pm();
void action_edit_no_focus();
void action_untrack_all();
void action_ch_settings_copy();
void action_show_sys_settings_ethernet_error();
void action_file_manager_select_list_view();
void action_show_sys_settings_ramp_and_delay();
void action_channel_toggle_ramp_state();

extern ActionExecFunc g_actionExecFunctions[];

enum FontsEnum {
    FONT_ID_NONE = 0,
    FONT_ID_SHADOW = 1,
    FONT_ID_OSWALD24 = 2,
    FONT_ID_OSWALD17 = 3,
    FONT_ID_OSWALD14 = 4,
    FONT_ID_HEYDINGS14 = 5,
    FONT_ID_OSWALD20 = 6,
    FONT_ID_WEB_HOSTING_HUB24 = 7,
    FONT_ID_OSWALD48 = 8,
    FONT_ID_OSWALD38 = 9,
    FONT_ID_ROBOTO_CONDENSED_REGULAR = 10
};

enum BitmapsEnum {
    BITMAP_ID_NONE = 0,
    BITMAP_ID_PSU_ICON = 1,
    BITMAP_ID_SETTINGS_ICON = 2,
    BITMAP_ID_LOGO = 3,
    BITMAP_ID_PROTECTION_CURVE = 4,
    BITMAP_ID_VOUT = 5,
    BITMAP_ID_PROTECTION_HW_TRIP_LEVEL = 6,
    BITMAP_ID_VSET = 7,
    BITMAP_ID_PROTECTION_TRIP_LEVEL = 8,
    BITMAP_ID_PROTECTION_DELAY = 9,
    BITMAP_ID_IOUT = 10,
    BITMAP_ID_POUT = 11,
    BITMAP_ID_COUPLED_PARALLEL = 12,
    BITMAP_ID_COUPLED_SERIES = 13,
    BITMAP_ID_COUPLED_CGND = 14,
    BITMAP_ID_COUPLED_SPLIT_RAILS = 15
};

enum StylesEnum {
    STYLE_ID_NONE = 0,
    STYLE_ID_DEFAULT = 1,
    STYLE_ID_DEFAULT_M_LEFT = 2,
    STYLE_ID_EDIT_VALUE_ACTIVE_M_CENTER = 3,
    STYLE_ID_EDIT_VALUE_ACTIVE_M_LEFT = 4,
    STYLE_ID_EDIT_VALUE_ACTIVE_S_LEFT = 5,
    STYLE_ID_EDIT_VALUE_ACTIVE_S_CENTER = 6,
    STYLE_ID_DEFAULT_S = 7,
    STYLE_ID_DEFAULT_S_LEFT = 8,
    STYLE_ID_STATUS_ICON_ENABLED = 9,
    STYLE_ID_STATUS_TITLE = 10,
    STYLE_ID_STATUS_BGND = 11,
    STYLE_ID_BUTTON_M = 12,
    STYLE_ID_BUTTON_M_DISABLED = 13,
    STYLE_ID_ERROR_ALERT = 14,
    STYLE_ID_ERROR_ALERT_BUTTON = 15,
    STYLE_ID_YT_GRAPH_U_DEFAULT = 16,
    STYLE_ID_YT_GRAPH_I_DEFAULT = 17,
    STYLE_ID_YT_GRAPH_P_DEFAULT = 18,
    STYLE_ID_YT_GRAPH_UNREGULATED = 19,
    STYLE_ID_YT_GRAPH_Y1 = 20,
    STYLE_ID_YT_GRAPH_Y2 = 21,
    STYLE_ID_YT_GRAPH_Y3 = 22,
    STYLE_ID_YT_GRAPH_Y4 = 23,
    STYLE_ID_YT_GRAPH_Y5 = 24,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_CONTAINER = 25,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_CONTAINER_S = 26,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_ITEM = 27,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_ITEM_S = 28,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_DISABLED_ITEM = 29,
    STYLE_ID_SELECT_ENUM_ITEM_POPUP_DISABLED_ITEM_S = 30,
    STYLE_ID_ENCODER_CURSOR_14_DISABLED = 31,
    STYLE_ID_ENCODER_CURSOR_14_RIGHT_DISABLED = 32,
    STYLE_ID_INFO_ALERT = 33,
    STYLE_ID_MENU_WITH_BUTTONS_MESSAGE = 34,
    STYLE_ID_MENU_WITH_BUTTONS_CONTAINER = 35,
    STYLE_ID_MENU_WITH_BUTTONS_BUTTON = 36,
    STYLE_ID_CHANNEL1 = 37,
    STYLE_ID_CHANNEL2 = 38,
    STYLE_ID_CHANNEL3 = 39,
    STYLE_ID_CHANNEL4 = 40,
    STYLE_ID_CHANNEL5 = 41,
    STYLE_ID_CHANNEL6 = 42,
    STYLE_ID_CHANNEL1_INVERSE = 43,
    STYLE_ID_CHANNEL2_INVERSE = 44,
    STYLE_ID_CHANNEL3_INVERSE = 45,
    STYLE_ID_CHANNEL4_INVERSE = 46,
    STYLE_ID_CHANNEL5_INVERSE = 47,
    STYLE_ID_CHANNEL6_INVERSE = 48,
    STYLE_ID_STATUS_ICON_ENABLED_AND_ERROR = 82,
    STYLE_ID_TOUCH_CALIBRATION = 101,
    STYLE_ID_STATUS_ICON_ENABLED_WITH_NEED_ATTENTION = 106,
    STYLE_ID_STATUS_ICON_ENABLED_AND_ACTIVE = 108,
    STYLE_ID_STATUS_ICON_ENABLED_BLINK = 110,
    STYLE_ID_STATUS_ICON_DISABLED = 111,
    STYLE_ID_STATUS_ICON_DISABLED_BLINK = 112,
    STYLE_ID_OVERLAY = 113,
    STYLE_ID_EDIT_VALUE_S_LEFT = 116,
    STYLE_ID_BOTTOM_BUTTON_BACKGROUND = 117,
    STYLE_ID_BOTTOM_BUTTON = 118,
    STYLE_ID_VALUE_S = 119,
    STYLE_ID_EDIT_VALUE_M_LEFT = 120,
    STYLE_ID_KEY_ICONS = 121,
    STYLE_ID_KEY = 122,
    STYLE_ID_TAB_PAGE_SELECTED = 125,
    STYLE_ID_TAB_PAGE = 126,
    STYLE_ID_DEFAULT_INVERSE = 133,
    STYLE_ID_BUTTON_S = 134,
    STYLE_ID_SLIDER_SHADE_1 = 135,
    STYLE_ID_SLIDER_SHADE_2 = 136,
    STYLE_ID_SLIDER_SHADE_3 = 137,
    STYLE_ID_SLIDER_SHADE_4 = 138,
    STYLE_ID_SLIDER_SHADE_5 = 139,
    STYLE_ID_YES_NO = 140,
    STYLE_ID_YES_NO_BUTTON = 141,
    STYLE_ID_YES_NO_MESSAGE = 142,
    STYLE_ID_TEXT_MESSAGE = 144,
    STYLE_ID_ASYNC_OPERATION = 147,
    STYLE_ID_PROGRESS = 148,
    STYLE_ID_SCROLLBAR_THUMB = 158,
    STYLE_ID_SCROLLBAR_BUTTON = 159,
    STYLE_ID_BOTTOM_BUTTON_TEXTUAL_S_LEFT = 160,
    STYLE_ID_KEY_SPEC_ICONS = 163,
    STYLE_ID_KEY_SPEC_ICONS_DISABLED = 165,
    STYLE_ID_KEY_DISABLED = 166,
    STYLE_ID_EDIT_VALUE_S_CENTERED = 167,
    STYLE_ID_VALUE_M = 175,
    STYLE_ID_DEFAULT_DISABLED_M_LEFT = 178,
    STYLE_ID_ENCODER_CURSOR_17_ENABLED = 180,
    STYLE_ID_YT_GRAPH = 182,
    STYLE_ID_LIST_GRAPH_CURSOR = 183,
    STYLE_ID_YT_GRAPH_U_DEFAULT_LABEL = 184,
    STYLE_ID_YT_GRAPH_I_DEFAULT_LABEL = 185,
    STYLE_ID_ENCODER_CURSOR_14_ENABLED = 186,
    STYLE_ID_VALUE = 190,
    STYLE_ID_DEFAULT_M = 194,
    STYLE_ID_OPTION_TOGGLE_L_CENTER = 195,
    STYLE_ID_EVENT_ERROR = 196,
    STYLE_ID_DEFAULT_DISABLED_S_LEFT = 197,
    STYLE_ID_ICON_AND_TEXT_S = 199,
    STYLE_ID_ICON_AND_TEXT_S_DISABLED = 200,
    STYLE_ID_DEFAULT_DISABLED = 206,
    STYLE_ID_EDIT_VALUE_M_CENTERED = 209,
    STYLE_ID_EDIT_S = 210,
    STYLE_ID_EVENT_WARNING = 231,
    STYLE_ID_DISPLAY_OFF = 232,
    STYLE_ID_DISPLAY_OFF_S = 233,
    STYLE_ID_MON_VALUE_48_RIGHT = 236,
    STYLE_ID_MON_VALUE_20_LEFT = 238,
    STYLE_ID_BAR_GRAPH_U_DEFAULT = 239,
    STYLE_ID_BAR_GRAPH_TEXT = 240,
    STYLE_ID_BAR_GRAPH_LIMIT_LINE = 242,
    STYLE_ID_BAR_GRAPH_I_DEFAULT = 243,
    STYLE_ID_TRIGGER_BUTTON_24 = 246,
    STYLE_ID_MON_VALUE_14_RIGHT = 248,
    STYLE_ID_ENCODER_CURSOR_14_RIGHT_ENABLED = 249,
    STYLE_ID_CHANNEL_OFF_BUTTON_20 = 250,
    STYLE_ID_TRIGGER_BUTTON_14 = 251,
    STYLE_ID_CHANNEL_OFF_BUTTON_38 = 257,
    STYLE_ID_INST_SELECTED = 258,
    STYLE_ID_MON_VALUE_38_RIGHT = 259,
    STYLE_ID_CH_PROT_OFF = 261,
    STYLE_ID_CH_PROT_ON = 262,
    STYLE_ID_CH_PROT_TRIPPED = 263,
    STYLE_ID_BUTTON_BGND = 264,
    STYLE_ID_MON_VALUE_24_RIGHT = 266,
    STYLE_ID_MON_VALUE_14_CENTER = 267,
    STYLE_ID_MON_VALUE_20_RIGHT = 273,
    STYLE_ID_MON_VALUE_14_LEFT = 274,
    STYLE_ID_CHANNEL_OFF_BUTTON_14 = 275,
    STYLE_ID_STATUS_LINE_SMALL_TITLE = 279,
    STYLE_ID_EDIT_VALUE_S_CENTERED_STATUS_LINE = 280,
    STYLE_ID_SCROLLBAR_TRACK = 281,
    STYLE_ID_BUTTON_S_DISABLED = 293
};

enum ThemesEnum {
    THEME_ID_LEGACY = 0,
    THEME_ID_LIGHT = 1,
    THEME_ID_DARK = 2
};

enum ColorsEnum {
    COLOR_ID_BACKGROUND = 0,
    COLOR_ID_TEXT_REGULAR = 1,
    COLOR_ID_TEXT_ENABLED = 2,
    COLOR_ID_TEXT_SELECTED = 3,
    COLOR_ID_TEXT_ENABLE_BACKGROUND = 4,
    COLOR_ID_STATUS_LINE_TEXT = 5,
    COLOR_ID_STATUS_LINE_TEXT_DISABLED = 6,
    COLOR_ID_TEXT_DISABLED_BACKGROUND = 7,
    COLOR_ID_STATUS_LINE_BACKGROUND = 8,
    COLOR_ID_STATUS_OK = 9,
    COLOR_ID_STATUS_WARNING = 10,
    COLOR_ID_INST_MAX_HEADER_BGND = 11,
    COLOR_ID_INST_MIN_HEADER_BGND = 12,
    COLOR_ID_INST_MAX_HEADER_TEXT = 13,
    COLOR_ID_INST_MIN_HEADER_TEXT = 14,
    COLOR_ID_TEXT_SELECTABLE_BACKGROUND = 15,
    COLOR_ID_PROTECTION_TEXT = 16,
    COLOR_ID_TEXT_DISABLED = 17,
    COLOR_ID_BAR_GRAPH_VOLTAGE = 18,
    COLOR_ID_BAR_GRAPH_CURRENT = 19,
    COLOR_ID_BAR_GRAPH_POWER = 20,
    COLOR_ID_BAR_GRAPH_BACKGROUND = 21,
    COLOR_ID_BAR_GRAPH_TEXT = 22,
    COLOR_ID_BAR_GRAPH_TEXT_INSIDE = 23,
    COLOR_ID_BAR_GRAPH_SET_LINE = 24,
    COLOR_ID_ACTION_COLOR = 25,
    COLOR_ID_POPUP_BACKGROUND_REGULAR = 26,
    COLOR_ID_POPUP_TEXT_SELECTED = 27,
    COLOR_ID_POPUP_BACKGROUND_WARNING = 28,
    COLOR_ID_POPUP_BACKGROUND_INFO = 29,
    COLOR_ID_TEXT_EDITED = 30,
    COLOR_ID_TEXT_VALUE = 31,
    COLOR_ID_DATA_LOGGING = 32,
    COLOR_ID_OVERLAY_BACKGROUND = 33,
    COLOR_ID_OVERLAY_DRAG_BACKGROUND = 34,
    COLOR_ID_OVERLAY_TEXT = 35,
    COLOR_ID_CHANNEL1 = 36,
    COLOR_ID_CHANNEL2 = 37,
    COLOR_ID_CHANNEL3 = 38,
    COLOR_ID_CHANNEL4 = 39,
    COLOR_ID_CHANNEL5 = 40,
    COLOR_ID_CHANNEL6 = 41,
    COLOR_ID_SCROLLBAR_TRACK = 42,
    COLOR_ID_SCROLLBAR_THUMB = 43,
    COLOR_ID_SCROLLBAR_BUTTON = 44,
    COLOR_ID_YT_GRAPH_GRID = 45,
    COLOR_ID_YT_GRAPH_BACKGROUND = 46,
    COLOR_ID_YT_GRAPH_CURSOR = 47,
    COLOR_ID_YT_GRAPH_Y1 = 48,
    COLOR_ID_YT_GRAPH_Y2 = 49,
    COLOR_ID_YT_GRAPH_Y3 = 50,
    COLOR_ID_YT_GRAPH_Y4 = 51,
    COLOR_ID_YT_GRAPH_Y5 = 52,
    COLOR_ID_LOADING = 53,
    COLOR_ID_PROGRESS = 54,
    COLOR_ID_PROGRESS_BACKGROUND = 55,
    COLOR_ID_BACKDROP = 56
};

enum PagesEnum {
    PAGE_ID_NONE = 0,
    PAGE_ID_A_MAIN = 1,
    PAGE_ID_A_MAIN_1 = 2,
    PAGE_ID_WELCOME = 3,
    PAGE_ID_TOUCH_CALIBRATION_INTRO = 4,
    PAGE_ID_TOUCH_CALIBRATION = 5,
    PAGE_ID_TOUCH_CALIBRATION_YES_NO = 6,
    PAGE_ID_TOUCH_CALIBRATION_YES_NO_CANCEL = 7,
    PAGE_ID_MAIN = 8,
    PAGE_ID_MAIN_HELP = 9,
    PAGE_ID_EDIT_MODE_KEYPAD = 10,
    PAGE_ID_EDIT_MODE_STEP = 11,
    PAGE_ID_EDIT_MODE_STEP_HELP = 12,
    PAGE_ID_EDIT_MODE_SLIDER = 13,
    PAGE_ID_EDIT_MODE_SLIDER_HELP = 14,
    PAGE_ID_YES_NO = 15,
    PAGE_ID_YES_NO_L = 16,
    PAGE_ID_ARE_YOU_SURE_WITH_MESSAGE = 17,
    PAGE_ID_YES_NO_LATER = 18,
    PAGE_ID_YES_NO_FLASH_SLAVE = 19,
    PAGE_ID_INFO_RESTART = 20,
    PAGE_ID_TEXT_MESSAGE = 21,
    PAGE_ID_ASYNC_OPERATION_IN_PROGRESS = 22,
    PAGE_ID_PROGRESS = 23,
    PAGE_ID_PROGRESS_WITHOUT_ABORT = 24,
    PAGE_ID_EVENT_QUEUE = 25,
    PAGE_ID_KEYPAD = 26,
    PAGE_ID_NUMERIC_KEYPAD = 27,
    PAGE_ID_CH_SETTINGS = 28,
    PAGE_ID_CH_SETTINGS_OK = 29,
    PAGE_ID_CH_SETTINGS_ERROR = 30,
    PAGE_ID_CH_SETTINGS_ERROR_DCM220 = 31,
    PAGE_ID_CH_SETTINGS_DCP405_SPECIFIC = 32,
    PAGE_ID_CH_SETTINGS_DCP405B_SPECIFIC = 33,
    PAGE_ID_CH_SETTINGS_DCM220_SPECIFIC = 34,
    PAGE_ID_CH_SETTINGS_PROT_CLEAR = 35,
    PAGE_ID_CH_SETTINGS_PROT_OVP = 36,
    PAGE_ID_CH_SETTINGS_PROT_OCP = 37,
    PAGE_ID_CH_SETTINGS_PROT_OPP = 38,
    PAGE_ID_CH_SETTINGS_PROT_OTP = 39,
    PAGE_ID_CH_SETTINGS_TRIGGER = 40,
    PAGE_ID_CH_SETTINGS_LISTS = 41,
    PAGE_ID_CH_SETTINGS_LISTS_INSERT_MENU = 42,
    PAGE_ID_CH_SETTINGS_LISTS_FILE_MENU = 43,
    PAGE_ID_CH_SETTINGS_LISTS_DELETE_MENU = 44,
    PAGE_ID_CH_SETTINGS_CALIBRATION = 45,
    PAGE_ID_CH_SETTINGS_CALIBRATION_WIZ_STEP = 46,
    PAGE_ID_CH_SETTINGS_CALIBRATION_WIZ_FINISH = 47,
    PAGE_ID_CH_SETTINGS_ADV_OPTIONS = 48,
    PAGE_ID_CH_SETTINGS_ADV_RANGES = 49,
    PAGE_ID_CH_SETTINGS_ADV_VIEW = 50,
    PAGE_ID_CH_SETTINGS_INFO = 51,
    PAGE_ID_SYS_SETTINGS = 52,
    PAGE_ID_SYS_SETTINGS_TEMPERATURE = 53,
    PAGE_ID_SYS_SETTINGS_PROTECTIONS = 54,
    PAGE_ID_SYS_SETTINGS_TRIGGER = 55,
    PAGE_ID_SYS_SETTINGS_IO = 56,
    PAGE_ID_SYS_SETTINGS_DATE_TIME = 57,
    PAGE_ID_SYS_SETTINGS_ENCODER = 58,
    PAGE_ID_SYS_SETTINGS_SERIAL = 59,
    PAGE_ID_SYS_SETTINGS_ETHERNET = 60,
    PAGE_ID_SYS_SETTINGS_MQTT = 61,
    PAGE_ID_SYS_SETTINGS_ETHERNET_STATIC = 62,
    PAGE_ID_SYS_SETTINGS_SCREEN_CALIBRATION = 63,
    PAGE_ID_SYS_SETTINGS_DISPLAY = 64,
    PAGE_ID_SYS_SETTINGS_SOUND = 65,
    PAGE_ID_SYS_SETTINGS_TRACKING = 66,
    PAGE_ID_SYS_SETTINGS_COUPLING = 67,
    PAGE_ID_SYS_SETTINGS_RAMP_AND_DELAY = 68,
    PAGE_ID_USER_PROFILES = 69,
    PAGE_ID_USER_PROFILE_SETTINGS = 70,
    PAGE_ID_USER_PROFILE_0_SETTINGS = 71,
    PAGE_ID_PROFILE_BASIC_INFO = 72,
    PAGE_ID_SYS_INFO = 73,
    PAGE_ID_STAND_BY_MENU = 74,
    PAGE_ID_ENTERING_STANDBY = 75,
    PAGE_ID_STANDBY = 76,
    PAGE_ID_SAVING = 77,
    PAGE_ID_SHUTDOWN = 78,
    PAGE_ID_DISPLAY_OFF = 79,
    PAGE_ID_MINIMIZED_CHANNELS = 80,
    PAGE_ID_SLOT_DEF_VERT = 81,
    PAGE_ID_SLOT_DEF_VERT_TITLE = 82,
    PAGE_ID_SLOT_DEF_1CH_NUM_ON = 83,
    PAGE_ID_SLOT_DEF_1CH_VBAR_ON = 84,
    PAGE_ID_SLOT_DEF_1CH_VERT_OFF = 85,
    PAGE_ID_SLOT_DEF_1CH_VERT_COUPLED_SERIES = 86,
    PAGE_ID_SLOT_DEF_1CH_VERT_COUPLED_PARALLEL = 87,
    PAGE_ID_SLOT_DEF_2CH_VERT = 88,
    PAGE_ID_SLOT_DEF_2CH_VERT_ON = 89,
    PAGE_ID_SLOT_DEF_2CH_VERT_OFF = 90,
    PAGE_ID_SLOT_DEF_VERT_ERROR = 91,
    PAGE_ID_SLOT_DEF_VERT_NOT_INSTALLED = 92,
    PAGE_ID_SLOT_DEF_HORZ = 93,
    PAGE_ID_SLOT_DEF_HORZ_TITLE = 94,
    PAGE_ID_SLOT_DEF_1CH_HBAR_ON = 95,
    PAGE_ID_SLOT_DEF_1CH_YT_ON = 96,
    PAGE_ID_SLOT_DEF_1CH_HORZ_OFF = 97,
    PAGE_ID_SLOT_DEF_1CH_HORZ_COUPLED_SERIES = 98,
    PAGE_ID_SLOT_DEF_1CH_HORZ_COUPLED_PARALLEL = 99,
    PAGE_ID_SLOT_DEF_2CH_HORZ = 100,
    PAGE_ID_SLOT_DEF_2CH_HORZ_ON = 101,
    PAGE_ID_SLOT_DEF_2CH_HORZ_OFF = 102,
    PAGE_ID_SLOT_DEF_HORZ_ERROR = 103,
    PAGE_ID_SLOT_DEF_HORZ_NOT_INSTALLED = 104,
    PAGE_ID_SLOT_MAX_1CH_TITLE = 105,
    PAGE_ID_SLOT_MAX_1CH_NUM_ON = 106,
    PAGE_ID_SLOT_MAX_1CH_NUM_OFF = 107,
    PAGE_ID_SLOT_MAX_1CH_HBAR_ON = 108,
    PAGE_ID_SLOT_MAX_1CH_HBAR_OFF = 109,
    PAGE_ID_SLOT_MAX_1CH_YT_ON = 110,
    PAGE_ID_SLOT_MAX_1CH_YT_OFF = 111,
    PAGE_ID_SLOT_MAX_2CH = 112,
    PAGE_ID_SLOT_MAX_2CH_TITLE = 113,
    PAGE_ID_SLOT_MAX_2CH_NUM_ON = 114,
    PAGE_ID_SLOT_MAX_2CH_NUM_OFF = 115,
    PAGE_ID_SLOT_MAX_2CH_HBAR_ON = 116,
    PAGE_ID_SLOT_MAX_2CH_HBAR_OFF = 117,
    PAGE_ID_SLOT_MAX_2CH_YT_ON = 118,
    PAGE_ID_SLOT_MAX_2CH_YT_OFF = 119,
    PAGE_ID_SLOT_MAX_2CH_MIN_TITLE = 120,
    PAGE_ID_SLOT_MAX_2CH_MIN_ON = 121,
    PAGE_ID_SLOT_MAX_2CH_MIN_OFF = 122,
    PAGE_ID_SLOT_MAX_ERROR = 123,
    PAGE_ID_SLOT_MAX_NOT_INSTALLED = 124,
    PAGE_ID_SLOT_MIN_1CH_TITLE = 125,
    PAGE_ID_SLOT_MIN_1CH_ON = 126,
    PAGE_ID_SLOT_MIN_1CH_OFF = 127,
    PAGE_ID_SLOT_MIN_1CH_COUPLED_SERIES = 128,
    PAGE_ID_SLOT_MIN_1CH_COUPLED_PARALLEL = 129,
    PAGE_ID_SLOT_MIN_2CH_TITLE = 130,
    PAGE_ID_SLOT_MIN_2CH = 131,
    PAGE_ID_SLOT_MIN_2CH_ON = 132,
    PAGE_ID_SLOT_MIN_2CH_OFF = 133,
    PAGE_ID_SLOT_MIN_ERROR = 134,
    PAGE_ID_SLOT_MIN_NOT_INSTALLED = 135,
    PAGE_ID_SLOT_MICRO_1CH_TITLE = 136,
    PAGE_ID_SLOT_MICRO_1CH_ON = 137,
    PAGE_ID_SLOT_MICRO_1CH_OFF = 138,
    PAGE_ID_SLOT_MICRO_1CH_COUPLED_SERIES = 139,
    PAGE_ID_SLOT_MICRO_1CH_COUPLED_PARALLEL = 140,
    PAGE_ID_SLOT_MICRO_2CH = 141,
    PAGE_ID_SLOT_MICRO_2CH_TITLE = 142,
    PAGE_ID_SLOT_MICRO_2CH_ON = 143,
    PAGE_ID_SLOT_MICRO_2CH_OFF = 144,
    PAGE_ID_SLOT_MICRO_ERROR = 145,
    PAGE_ID_SLOT_MICRO_NOT_INSTALLED = 146,
    PAGE_ID_DLOG_VIEW = 147,
    PAGE_ID_IMAGE_VIEW = 148,
    PAGE_ID_DLOG_PARAMS = 149,
    PAGE_ID_DLOG_VIEW_OVERLAY_OPTIONS = 150,
    PAGE_ID_FILE_MANAGER = 151,
    PAGE_ID_FILE_BROWSER = 152,
    PAGE_ID_FILE_MENU = 153,
    PAGE_ID_FRONT_PANEL_EMPTY_SLOT = 154,
    PAGE_ID_DCM220_FRONT_PANEL_LED = 155,
    PAGE_ID_FILE_MANAGER_DETAILS_VIEW = 156,
    PAGE_ID_FILE_MANAGER_SCRIPTS_VIEW = 157,
    PAGE_ID_FILE_MANAGER_SCRIPTS_ALTER_VIEW = 158,
    PAGE_ID_FILE_MANAGER_LARGE_ICONS_VIEW = 159,
    PAGE_ID_TOUCH_TEST = 160,
    PAGE_ID_DEBUG_VARIABLES = 161,
    PAGE_ID_FOCUS_VALUE_OVERLAY = 162
};

extern const uint8_t assets[310597];
