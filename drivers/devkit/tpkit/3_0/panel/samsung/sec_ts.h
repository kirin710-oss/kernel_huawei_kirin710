/* drivers/input/touchscreen/sec_ts.h
 *
 * Copyright (C) 2015 Samsung Electronics Co., Ltd.
 * http://www.samsungsemi.com/
 *
 * Core file for Samsung TSC driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SEC_TS_H__
#define __SEC_TS_H__

#include <asm/unaligned.h>
#include <linux/completion.h>
#include <linux/ctype.h>
#include <linux/delay.h>
#include <linux/firmware.h>
#include <linux/gpio.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/wakelock.h>

#include <linux/device.h>
#include "../../huawei_ts_kit.h"


#if defined(CONFIG_TRUSTONIC_TRUSTED_UI)
#include <linux/t-base-tui.h>
#endif
#if defined(CONFIG_TRUSTONIC_TRUSTED_UI_QC)
#include <linux/input/tui_hal_ts.h>
#endif
#ifdef CONFIG_SEC_SYSFS
#include <linux/sec_sysfs.h>
#endif

#ifdef CONFIG_INPUT_BOOSTER
#include <linux/input/input_booster.h>
#endif

#ifdef CONFIG_SECURE_TOUCH
#include <linux/atomic.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>
#include <soc/qcom/scm.h>

#define SECURE_TOUCH_ENABLE	1
#define SECURE_TOUCH_DISABLE	0
#endif

#define SEC_CMD_STR_LEN		1024

#define SEC_TS_I2C_NAME		"sec_ts"
#define SEC_TS_DEVICE_NAME	"SEC_TS"
#define SEC_TS_VENDOR_NAME	"sec_ts-"
#define SEC_TS_HW_PROJECTID "BLAC570900"

#define SEC_TS_IC_VENDOR		SEC_TS_I2C_NAME
#define SEC_TS_FW_VENDOR		SEC_TS_HW_PROJECTID
#define SEC_TS_MODULE_VENDOR	"sdc"


#define SEC_TS_REGULATOR_DVDD	"sec_ts-dvdd"
#define SEC_TS_REGULATOR_AVDD	"sec_ts-avdd"
#define SEC_TS_STR_FWPATH	"ts/"
#define SEC_TS_STR_UNDERSCORE	"-"
#define SEC_TS_STR_FWTYPE	".img"
/* samsung tp default i2c address:0x48,  differentiation from blanc i2c addr:0x17 */
#define SEC_TS_DEFAULT_I2C_ADDR	0x48
/* Distinguish from device name with i2c address 0x17 */
#define IC_SEC_Y761 "Y761_sec"

#define SEC_TS_POWER_ON_DEALY_MS 100
#define SEC_TS_BOOT_VER		0xBA
#define SEC_TS_BOOT_OLDVER	0xB2
#define SEC_TS_APP_VER		0xAC

#undef USE_OPEN_CLOSE
#undef USE_RESET_DURING_POWER_ON
#undef USE_RESET_EXIT_LPM
#undef USE_POR_AFTER_I2C_RETRY
#undef USER_OPEN_DWORK
#undef USE_PRESSURE_SENSOR
#undef PAT_CONTROL
#undef USE_COVER
#undef USE_STD_I2C_IF
#define USE_CUSTOM_I2C_IF
#undef USE_EXTENDED_EVENT
#ifdef SEC_TS_USE_LOWPOWER
#undef SEC_TS_USE_LOWPOWER
#endif

#define TOUCH_RESET_DWORK_TIME		10
#define BRUSH_Z_DATA		63	/* for ArtCanvas */

#define MASK_1_BITS			0x0001
#define MASK_2_BITS			0x0003
#define MASK_3_BITS			0x0007
#define MASK_4_BITS			0x000F
#define MASK_5_BITS			0x001F
#define MASK_6_BITS			0x003F
#define MASK_7_BITS			0x007F
#define MASK_8_BITS			0x00FF

#define SEC_TS_PROJECTID_MAX		11
#define SEC_TS_CAL_LIMITDATA_MAX	3
#define SEC_TS_NOLH_LIMITDATA_MAX	2


/* support feature */
#undef SEC_TS_SUPPORT_SPONGELIB	/* support display lab algorithm */

#define TYPE_STATUS_EVENT_CMD_DRIVEN	0
#define TYPE_STATUS_EVENT_ERR		1
#define TYPE_STATUS_EVENT_INFO		2
#define TYPE_STATUS_EVENT_USER_INPUT	3
#define TYPE_STATUS_EVENT_SPONGE_INFO	6
#define TYPE_STATUS_EVENT_VENDOR_INFO	7
#define TYPE_STATUS_CODE_SAR	0x28

#define BIT_STATUS_EVENT_CMD_DRIVEN(a)	(a << TYPE_STATUS_EVENT_CMD_DRIVEN)
#define BIT_STATUS_EVENT_ERR(a)		(a << TYPE_STATUS_EVENT_ERR)
#define BIT_STATUS_EVENT_INFO(a)	(a << TYPE_STATUS_EVENT_INFO)
#define BIT_STATUS_EVENT_USER_INPUT(a)	(a << TYPE_STATUS_EVENT_USER_INPUT)
#define BIT_STATUS_EVENT_VENDOR_INFO(a)	(a << TYPE_STATUS_EVENT_VENDOR_INFO)

#define DO_FW_CHECKSUM			(1 << 0)
#define DO_PARA_CHECKSUM		(1 << 1)
#define MAX_SUPPORT_TOUCH_COUNT		10
#define MAX_SUPPORT_HOVER_COUNT		1
#define MAX_EVENT_COUNT 		32

#define SEC_TS_EVENTID_HOVER		10

#define SEC_TS_DEFAULT_FW_NAME		"tsp_sec/sec_hero.fw"
#define SEC_TS_DEFAULT_BL_NAME		"ts/touch_screen_blupdate.img"
#define SEC_TS_DEFAULT_PARA_NAME	"tsp_sec/s6smc41_para_REL_DGA0_V0106_150114_193317.bin"
#define SEC_TS_DEFAULT_UMS_FW		"/sdcard/Firmware/TSP/lsi.bin"
#define SEC_TS_DEFAULT_HW_FW		"ts/touch_screen_firmware.img"
#define SEC_TS_DEFAULT_FFU_FW		"ffu_tsp.bin"
#define SEC_TS_MAX_FW_PATH		64
#define SEC_TS_FW_BLK_SIZE_MAX		(512)
#define SEC_TS_FW_BLK_SIZE_DEFAULT	(256)
#define SEC_TS_SELFTEST_REPORT_SIZE	80
#define SEC_TS_DEBUGBUF_SIZE_MAX	1500

#define SEC_TS_I2C_ADDR				0x17
#define I2C_WRITE_BUFFER_SIZE		(256 - 1)

#define SEC_TS_FW_HEADER_SIGN		0x53494654
#define SEC_TS_FW_CHUNK_SIGN		0x53434654

#undef SEC_TS_FW_UPDATE_ON_PROBE
#define SEC_TS_FW_UPDATE_ON_BOOT

#define AMBIENT_CAL			0
#define OFFSET_CAL_SDC			1
#define OFFSET_CAL_SEC			2
#define PRESSURE_CAL			3

#define SEC_TS_SKIPTSP_DUTY		100

#define SEC_TS_NVM_OFFSET_FAC_RESULT		0
#define SEC_TS_NVM_OFFSET_CAL_COUNT		1
#define SEC_TS_NVM_OFFSET_DISASSEMBLE_COUNT	2
#define SEC_TS_NVM_OFFSET_TUNE_VERSION		3
#define SEC_TS_NVM_OFFSET_TUNE_VERSION_LENGTH	2

#define SEC_TS_NVM_OFFSET_PRESSURE_INDEX	5

#define SEC_TS_NVM_OFFSET_PRESSURE_STRENGTH	6
#define SEC_TS_NVM_OFFSET_PRESSURE_STRENGTH_1	6
#define SEC_TS_NVM_OFFSET_PRESSURE_STRENGTH_2	12
#define SEC_TS_NVM_OFFSET_PRESSURE_STRENGTH_3	18
#define SEC_TS_NVM_OFFSET_PRESSURE_STRENGTH_4	24

#define SEC_TS_NVM_OFFSET_PRESSURE_RAWDATA	30
#define SEC_TS_NVM_OFFSET_PRESSURE_RAWDATA_1	30
#define SEC_TS_NVM_OFFSET_PRESSURE_RAWDATA_2	36
#define SEC_TS_NVM_OFFSET_PRESSURE_RAWDATA_3	42
#define SEC_TS_NVM_OFFSET_PRESSURE_RAWDATA_4	48
#define SEC_TS_NVM_SIZE_PRESSURE_BLOCK		6

#define SEC_TS_NVM_OFFSET_PRESSURE_BASE_CAL_COUNT	54
#define SEC_TS_NVM_OFFSET_PRESSURE_DELTA_CAL_COUNT	55
#define SEC_TS_NVM_SIZE_PRESSURE_CAL_BLOCK		1

#define SEC_TS_NVM_LAST_BLOCK_OFFSET		SEC_TS_NVM_OFFSET_PRESSURE_DELTA_CAL_COUNT
#define SEC_TS_NVM_LAST_BLOCK_SIZE		SEC_TS_NVM_SIZE_PRESSURE_CAL_BLOCK

#define SEC_TS_NVM_OFFSET_LENGTH		(SEC_TS_NVM_LAST_BLOCK_OFFSET + SEC_TS_NVM_LAST_BLOCK_SIZE + 1)

/* SEC_TS READ REGISTER ADDRESS */
#define SEC_TS_CMD_SENSE_ON			0x10
#define SEC_TS_CMD_SENSE_OFF			0x11
#define SEC_TS_CMD_APP_SW_RESET			0x12
#define SEC_TS_CMD_BOOT_SW_RESET		0x42
#define SEC_TS_CMD_CALIBRATION_SEC		0x13
#define SEC_TS_CMD_FACTORY_PANELCALIBRATION	0x14

#define SEC_TS_READ_GPIO_STATUS			0x20
#define SEC_TS_READ_FIRMWARE_INTEGRITY		0x21
#define SEC_TS_READ_DEVICE_ID			0x22
#define SEC_TS_READ_PANEL_INFO			0x23
#define SEC_TS_READ_CORE_CONFIG_VERSION		0x24

#define SEC_TS_CMD_SET_TOUCHFUNCTION		0x30
#define SEC_TS_CMD_SET_TSC_MODE			0x31
#define SET_TS_CMD_SET_CHARGER_MODE		0x32
#define SET_TS_CMD_SET_NOISE_MODE		0x33
#define SET_TS_CMD_SET_REPORT_RATE		0x34
#define SEC_TS_CMD_TOUCH_MODE_FOR_THRESHOLD	0x35
#define SEC_TS_CMD_TOUCH_THRESHOLD		0x36
#define SET_TS_CMD_KEY_THRESHOLD		0x37
#define SEC_TS_CMD_SET_COVERTYPE		0x38
#define SEC_TS_CMD_WAKEUP_GESTURE_MODE		0x39
#define SEC_TS_WRITE_POSITION_FILTER		0x3A
#define SEC_TS_CMD_WET_MODE			0x3B
#define SEC_TS_CMD_ERASE_FLASH			0x45
#define SEC_TS_READ_ID				0x52
#define SEC_TS_READ_BOOT_STATUS			0x55
#define SEC_TS_CMD_ENTER_FW_MODE		0x57
#define SEC_TS_READ_ONE_EVENT			0x60
#define SEC_TS_READ_ALL_EVENT			0x61
#define SEC_TS_CMD_CLEAR_EVENT_STACK		0x62
#define SEC_TS_CMD_MUTU_RAW_TYPE		0x70
#define SEC_TS_CMD_SELF_RAW_TYPE		0x71
#define SEC_TS_READ_TOUCH_RAWDATA		0x72
#define SEC_TS_READ_TOUCH_SELF_RAWDATA		0x73
#define SEC_TS_READ_SELFTEST_RESULT		0x80
#define SEC_TS_CMD_DOZE_PARAM			0x77
#define SEC_TS_CMD_CALIBRATION_AMBIENT		0x81
#define SEC_TS_CMD_RUN_NOLH			0x82
#define SEC_TS_CMD_ENTER_TESTMODE		0x83
#define SEC_TS_CMD_NVM				0x85
#define SEC_TS_CMD_STATEMANAGE_ON		0x8E
#define SEC_TS_CMD_CALIBRATION_OFFSET_SDC	0x8F
#define SEC_TS_READ_SELFCHECK_RESULT		0x94

/* SEC_TS SPONGE OPCODE COMMAND */
#define SEC_TS_CMD_SPONGE_GET_INFO	0x90
#define SEC_TS_CMD_SPONGE_WRITE_PARAM	0x91
#define SEC_TS_CMD_SPONGE_READ_PARAM	0x92
#define SEC_TS_CMD_SPONGE_NOTIFY_PACKET	0x93
#define SEC_TS_CMD_SPONGE_OFFSET_PRESSURE_LEVEL		0x5E
#define SEC_TS_CMD_SPONGE_OFFSET_PRESSURE_THD_HIGH	0x84
#define SEC_TS_CMD_SPONGE_OFFSET_PRESSURE_THD_LOW	0x86

#define SEC_TS_CMD_STATUS_EVENT_TYPE	0xA0
#define SEC_TS_READ_FW_INFO		0xA2
#define SEC_TS_READ_FW_VERSION		0xA3
#define SEC_TS_READ_PARA_VERSION	0xA4
#define SEC_TS_READ_IMG_VERSION		0xA5
#define SEC_TS_CMD_GET_CHECKSUM		0xA6
#define SEC_TS_CMD_MIS_CAL_CHECK	0xA7
#define SEC_TS_CMD_MIS_CAL_READ		0xA8
#define SEC_TS_CMD_MIS_CAL_SPEC		0xA9
#define SEC_TS_CMD_DEADZONE_RANGE	0xAA
#define SEC_TS_CMD_LONGPRESSZONE_RANGE	0xAB
#define SEC_TS_CMD_LONGPRESS_DROP_AREA	0xAC
#define SEC_TS_CMD_LONGPRESS_DROP_DIFF	0xAD
#define SEC_TS_READ_TS_STATUS		0xAF
#define SEC_TS_CMD_SELFTEST		0xAE

/* SEC_TS FLASH COMMAND */
#define SEC_TS_CMD_FLASH_READ_ADDR	0xD0
#define SEC_TS_CMD_FLASH_READ_SIZE	0xD1
#define SEC_TS_CMD_FLASH_READ_DATA	0xD2
#define SEC_TS_CMD_SELFTEST_DATA	0xD5
#define SEC_TS_CMD_CHG_SYSMODE		0xD7
#define SEC_TS_CMD_FLASH_ERASE		0xD8
#define SEC_TS_CMD_FLASH_WRITE		0xD9
#define SEC_TS_CMD_FLASH_PADDING	0xDA

#define SEC_TS_READ_BL_UPDATE_STATUS	0xDB
#define SEC_TS_READ_PROTOCOL_ID		0xDD
#define SEC_TS_CMD_SET_POWER_MODE	0xE4
#define SEC_TS_CMD_EDGE_DEADZONE	0xE5
#define SEC_TS_CMD_SET_DEX_MODE		0xE7
#define SEC_TS_CMD_CALIBRATION_PRESSURE		0xE9
/* Have to need delay 30msec after writing 0xEA command */
/* Do not write Zero with 0xEA command */
#define SEC_TS_CMD_SET_GET_PRESSURE		0xEA
#define SEC_TS_CMD_SET_USER_PRESSURE		0xEB
#define SEC_TS_CMD_SET_TEMPERATURE_COMP_MODE	0xEC
#define SEC_TS_CMD_SET_BRUSH_MODE	0xEF

#define SEC_TS_READ_CALIBRATION_REPORT		0xF1
#define SEC_TS_CMD_SET_VENDOR_EVENT_LEVEL	0xF2
#define SEC_TS_CMD_SET_SPENMODE			0xF3
#define SEC_TS_CMD_SELECT_PRESSURE_TYPE		0xF5
#define SEC_TS_CMD_READ_PRESSURE_DATA		0xF6

#define SEC_TS_FLASH_SIZE_64		64
#define SEC_TS_FLASH_SIZE_128		128
#define SEC_TS_FLASH_SIZE_256		256

#define SEC_TS_FLASH_SIZE_CMD		1
#define SEC_TS_FLASH_SIZE_ADDR		2
#define SEC_TS_FLASH_SIZE_CHECKSUM	1

#define SEC_TS_STATUS_BOOT_MODE		0x10
#define SEC_TS_STATUS_APP_MODE		0x20

#define SEC_TS_FIRMWARE_PAGE_SIZE_256	256
#define SEC_TS_FIRMWARE_PAGE_SIZE_128	128

/* SEC status event id */
#define SEC_TS_COORDINATE_EVENT		0
#define SEC_TS_STATUS_EVENT		1
#define SEC_TS_GESTURE_EVENT		2
#define SEC_TS_EMPTY_EVENT		3
#define SEC_TS_COORDINATE_WET		6

#define SEC_TS_STATUSEVENT_SIZE		8
#define SEC_TS_EVENT_BUFF_SIZE		13
#define SEC_TS_EVENT_BUFF_LONGSIZE	15
#define SEC_TS_SELFCHECK_BUFF_SIZE	17

#define SEC_TS_SID_GESTURE		0x14
#define SEC_TS_GESTURE_CODE_SPAY		0x00
#define SEC_TS_GESTURE_CODE_DOUBLE_TAP		0x01

#define SEC_TS_COORDINATE_ACTION_NONE		0
#define SEC_TS_COORDINATE_ACTION_PRESS		1
#define SEC_TS_COORDINATE_ACTION_MOVE		2
#define SEC_TS_COORDINATE_ACTION_RELEASE	3

#define SEC_TS_TOUCHTYPE_NORMAL		0
#define SEC_TS_TOUCHTYPE_HOVER		1
#define SEC_TS_TOUCHTYPE_FLIPCOVER	2
#define SEC_TS_TOUCHTYPE_GLOVE		3
#define SEC_TS_TOUCHTYPE_STYLUS		4
#define SEC_TS_TOUCHTYPE_PALM		5
#define SEC_TS_TOUCHTYPE_WET		6
#define SEC_TS_TOUCHTYPE_PROXIMITY	7
#define SEC_TS_TOUCHTYPE_JIG		8

#define SEC_TS_PARA_AMBTEST			0
#define SEC_TS_PARA_CALTEST			1

#define NO_FWUP				0
#define DO_FWUP				1

#define SEC_TS_PID_ADDR			0x2AA00
#define SEC_TS_Y761_PID_ADDR			0x2F800
/* SEC_TS_INFO : Info acknowledge event */
#define SEC_TS_ACK_BOOT_COMPLETE	0x00
#define SEC_TS_ACK_WET_MODE	0x1

/* SEC_TS_VENDOR_INFO : Vendor acknowledge event */
#define SEC_TS_VENDOR_ACK_OFFSET_CAL_DONE	0x40
#define SEC_TS_VENDOR_ACK_SELF_TEST_DONE	0x41
#define SEC_TS_VENDOR_ACK_NOLH_DONE		0x42
#define SEC_TS_VENDOR_ACK_SELFCHECK_DONE	0x69

/* SEC_TS_STATUS_EVENT_USER_INPUT */
#define SEC_TS_EVENT_FORCE_KEY	0x1

/* SEC_TS_STATUS_EVENT_SPONGE_INFO */
#define SEC_TS_EVENT_SPONGE_FORCE_KEY	0x00

/* SEC_TS_ERROR : Error event */
#define SEC_TS_ERR_EVNET_CORE_ERR	0x0
#define SEC_TS_ERR_EVENT_QUEUE_FULL	0x01
#define SEC_TS_ERR_EVENT_ESD		0x2

#define SEC_TS_BIT_SETFUNC_TOUCH		(1 << 0)
#define SEC_TS_BIT_SETFUNC_MUTUAL		(1 << 0)
#define SEC_TS_BIT_SETFUNC_HOVER		(1 << 1)
#define SEC_TS_BIT_SETFUNC_COVER		(1 << 2)
#define SEC_TS_BIT_SETFUNC_GLOVE		(1 << 3)
#define SEC_TS_BIT_SETFUNC_STYLUS		(1 << 4)
#define SEC_TS_BIT_SETFUNC_PALM			(1 << 5)
#define SEC_TS_BIT_SETFUNC_WET			(1 << 6)
#define SEC_TS_BIT_SETFUNC_PROXIMITY		(1 << 7)

#define SEC_TS_DEFAULT_ENABLE_BIT_SETFUNC	(SEC_TS_BIT_SETFUNC_TOUCH | SEC_TS_BIT_SETFUNC_PALM | SEC_TS_BIT_SETFUNC_WET)

#define SEC_TS_BIT_CHARGER_MODE_NO			(0x1 << 0)
#define SEC_TS_BIT_CHARGER_MODE_WIRE_CHARGER		(0x1 << 1)
#define SEC_TS_BIT_CHARGER_MODE_WIRELESS_CHARGER	(0x1 << 2)
#define SEC_TS_BIT_CHARGER_MODE_WIRELESS_BATTERY_PACK	(0x1 << 3)

#define STATE_MANAGE_ON			1
#define STATE_MANAGE_OFF		0

#define SEC_TS_STATUS_NOT_CALIBRATION	0x50
#define SEC_TS_STATUS_CALIBRATION_SDC	0xA1
#define SEC_TS_STATUS_CALIBRATION_SEC	0xA2

#define SEC_TS_CMD_EDGE_HANDLER		0xAA
#define SEC_TS_CMD_EDGE_AREA		0xAB
#define SEC_TS_CMD_DEAD_ZONE		0xAC
#define SEC_TS_CMD_LANDSCAPE_MODE	0xAD

#define SEC_TS_EVENT_CONTINUE		1
#define SEC_TS_EVENT_STOP		0

enum {
	BUILT_IN = 0,
	UMS,
	BL,
	FFU,
};

enum grip_write_mode {
	G_NONE				= 0,
	G_SET_EDGE_HANDLER		= 1,
	G_SET_EDGE_ZONE			= 2,
	G_SET_NORMAL_MODE		= 4,
	G_SET_LANDSCAPE_MODE	= 8,
	G_CLR_LANDSCAPE_MODE	= 16,
};
enum grip_set_data {
	ONLY_EDGE_HANDLER		= 0,
	GRIP_ALL_DATA			= 1,
};

typedef enum {
	SEC_TS_STATE_POWER_OFF = 0,
	SEC_TS_STATE_LPM_SUSPEND,
	SEC_TS_STATE_LPM_RESUME,
	SEC_TS_STATE_POWER_ON
} TOUCH_POWER_MODE;

typedef enum {
	TOUCH_SYSTEM_MODE_BOOT		= 0,
	TOUCH_SYSTEM_MODE_CALIBRATION	= 1,
	TOUCH_SYSTEM_MODE_TOUCH		= 2,
	TOUCH_SYSTEM_MODE_SELFTEST	= 3,
	TOUCH_SYSTEM_MODE_FLASH		= 4,
	TOUCH_SYSTEM_MODE_LOWPOWER	= 5,
	TOUCH_SYSTEM_MODE_LISTEN
} TOUCH_SYSTEM_MODE;

typedef enum {
	TOUCH_MODE_STATE_IDLE		= 0,
	TOUCH_MODE_STATE_HOVER		= 1,
	TOUCH_MODE_STATE_TOUCH		= 2,
	TOUCH_MODE_STATE_NOISY		= 3,
	TOUCH_MODE_STATE_CAL		= 4,
	TOUCH_MODE_STATE_CAL2		= 5,
	TOUCH_MODE_STATE_WAKEUP		= 10
} TOUCH_MODE_STATE;

enum switch_system_mode {
	TO_TOUCH_MODE			= 0,
	TO_LOWPOWER_MODE		= 1,
	TO_SELFTEST_MODE		= 2,
	TO_FLASH_MODE			= 3,
	TO_SLEEP_MODE			= 4,
};

typedef enum {
	TOUCH_BOOT			= 0,
	TOUCH_APP			= 1,
	TOUCH_APP_FLASH			= 2,
} TOUCH_BOOT_MODE;

enum {
	TYPE_RAW_DATA			= 0,	/* Total - Offset : delta data */
	TYPE_SIGNAL_DATA		= 1,	/* Signal - Filtering & Normalization */
	TYPE_AMBIENT_BASELINE	= 2,	/* Cap Baseline */
	TYPE_AMBIENT_DATA		= 3,	/* Cap Ambient */
	TYPE_REMV_BASELINE_DATA	= 4,
	TYPE_DECODED_DATA		= 5,	/* Raw */
	TYPE_REMV_AMB_DATA		= 6,	/*  TYPE_RAW_DATA - TYPE_AMBIENT_DATA */
	TYPE_NO_COMNOISE_DATA		= 15,	/*  No Common Noise Data */
	TYPE_OFFSET_DATA_SEC	= 19,	/* Cap Offset in SEC Manufacturing Line */
	TYPE_OFFSET_DATA_SDC	= 29,	/* Cap Offset in SDC Manufacturing Line */
	TYPE_MIN_NOISE_DATA	= 30,	/* NOL : Noise Min data */
	TYPE_MAX_NOISE_DATA	= 31,	/* NOH : Noise Max data */
	TYPE_INVALID_DATA		= 0xFF,	/* Invalid data type for release factory mode */
};

typedef enum {
	SPONGE_EVENT_TYPE_SPAY			= 0x04,
	SPONGE_EVENT_TYPE_PRESSURE_TOUCHED = 0x05,
	SPONGE_EVENT_TYPE_PRESSURE_RELEASED	= 0x06,
	SPONGE_EVENT_TYPE_AOD			= 0x08,
	SPONGE_EVENT_TYPE_AOD_PRESS		= 0x09,
	SPONGE_EVENT_TYPE_AOD_LONGPRESS		= 0x0A,
	SPONGE_EVENT_TYPE_AOD_DOUBLETAB		= 0x0B,
	SPONGE_EVENT_TYPE_AOD_HOMEKEY_PRESS	= 0x0C,
	SPONGE_EVENT_TYPE_AOD_HOMEKEY_RELEASE	= 0x0D,
	SPONGE_EVENT_TYPE_AOD_HOMEKEY_RELEASE_NO_HAPTIC	= 0x0E
} SPONGE_EVENT_TYPE;

enum sec_ic_name {
	DEFAULT  = 0,
	S6SY761X = 1,
};

#define CMD_RESULT_WORD_LEN		10

#define SEC_TS_I2C_RETRY_CNT		3
#define SEC_TS_WAIT_RETRY_CNT		10

#define SEC_TS_MODE_SPONGE_SPAY			(1 << 1)
#define SEC_TS_MODE_SPONGE_AOD			(1 << 2)
#define SEC_TS_MODE_SPONGE_FORCE_KEY	(1 << 6)

#define SEC_TS_MODE_LOWPOWER_FLAG			(SEC_TS_MODE_SPONGE_SPAY | SEC_TS_MODE_SPONGE_AOD \
											| SEC_TS_MODE_SPONGE_FORCE_KEY)

#define SEC_TS_AOD_GESTURE_PRESS		(1 << 7)
#define SEC_TS_AOD_GESTURE_LONGPRESS		(1 << 6)
#define SEC_TS_AOD_GESTURE_DOUBLETAB		(1 << 5)

#define SEC_TS_SPONGE_EVENT_PRESSURE_TOUCHED		(1 << 6)
#define SEC_TS_SPONGE_EVENT_PRESSURE_RELEASED		(1 << 7)

#define SEC_TS_SELFTEST_EXE_DELAY 800

enum sec_ts_self_test_item {
	SEC_TS_RAWCAP_TEST,
	SEC_TS_RAWCAPGAP_TEST,
	SEC_TS_DETLA_TEST,
	SEC_TS_SELF_CAP_TEST,
	SEC_TS_SELF_DETLA_TEST,
	SEC_TS_CALDATA_TEST,
	SEC_TS_SELFTEST_ITEM_MAX,
};

enum sec_ts_cover_id {
	SEC_TS_FLIP_WALLET = 0,
	SEC_TS_VIEW_COVER,
	SEC_TS_COVER_NOTHING1,
	SEC_TS_VIEW_WIRELESS,
	SEC_TS_COVER_NOTHING2,
	SEC_TS_CHARGER_COVER,
	SEC_TS_VIEW_WALLET,
	SEC_TS_LED_COVER,
	SEC_TS_CLEAR_FLIP_COVER,
	SEC_TS_QWERTY_KEYBOARD_EUR,
	SEC_TS_QWERTY_KEYBOARD_KOR,
	SEC_TS_MONTBLANC_COVER = 100,
};

enum sec_fw_update_status {
	SEC_NOT_UPDATE = 0,
	SEC_NEED_FW_UPDATE,
	SEC_NEED_CALIBRATION_ONLY,
	SEC_NEED_FW_UPDATE_N_CALIBRATION,
};

enum tsp_hw_parameter {
	TSP_ITO_CHECK		= 1,
	TSP_RAW_CHECK		= 2,
	TSP_MULTI_COUNT		= 3,
	TSP_WET_MODE		= 4,
	TSP_COMM_ERR_COUNT	= 5,
	TSP_MODULE_ID		= 6,
};

#define TEST_MODE_MIN_MAX		false
#define TEST_MODE_ALL_NODE		true
#define TEST_MODE_READ_FRAME		false
#define TEST_MODE_READ_CHANNEL		true

/* factory test mode */
struct sec_ts_test_mode {
	u8 type;
	int min;
	int max;
	int short_min;
	int short_max;
	int avg;
	int short_avg;
	bool allnode;
	bool frame_channel;
};

struct sec_ts_fw_file {
	u8 *data;
	u32 pos;
	size_t size;
};

struct sec_ts_test_result {
	union {
		struct {
			u8 assy_count:2;
			u8 assy_result:2;
			u8 module_count:2;
			u8 module_result:2;
		} __attribute__ ((packed));
		unsigned char data[1];
	};
};

/* 13 byte */
struct sec_ts_gesture_status {
	u8 eid:2;
	u8 stype:4;
	u8 sf:2;
	u8 gesture_id;
	u8 gesture_data_1;
	u8 gesture_data_2;
	u8 gesture_data_3;
	u8 gesture_data_4;
	u8 reserved_1;
	u8 left_event_5_0:6;
	u8 reserved_2:2;
	u8 reserved_3[5];
} __attribute__ ((packed));

/* 13 byte */
struct sec_ts_event_status {
	u8 eid:2;
	u8 stype:4;
	u8 sf:2;
	u8 status_id;
	u8 status_data_1;
	u8 status_data_2;
	u8 status_data_3;
	u8 status_data_4;
	u8 status_data_5;
	u8 left_event_5_0:6;
	u8 reserved_2:2;
	u8 reserved_3[5];
} __attribute__ ((packed));

/* 13 byte */
struct sec_ts_event_coordinate {
	u8 eid:2;
	u8 tid:4;
	u8 tchsta:2;
	u8 x_11_4;
	u8 y_11_4;
	u8 y_3_0:4;
	u8 x_3_0:4;
	u8 major;
	u8 minor;
	u8 z:6;
	u8 ttype_3_2:2;
	u8 left_event:6;
	u8 ttype_1_0:2;
	u8 wx;
	u8 wy;
	u8 ewx;
	u8 ewy;
	u8 orient;
	u8 sgx;
	u8 sgy;
} __attribute__ ((packed));

/* not fixed */
struct sec_ts_coordinate {
	u8 id;
	u8 ttype;
	u8 action;
	u8 old_action;
	u16 x;
	u16 y;
	u8 z;
	u8 hover_flag;
	u8 glove_flag;
	u8 touch_height;
	u16 mcount;
	u8 major;
	u8 minor;
	bool palm;
	int palm_count;
	u8 left_event;
	u8 wx;
	u8 wy;
	u8 ewx;
	u8 ewy;
	u8 xer;
	u8 yer;
};

struct sec_ts_selfcheck {
	u8 result;
	u16 mt_diff_tx;
	u16 mt_diff_rx;
	u16 mt_peak_max;
	u16 mt_peak_min;
	u16 sf_txpeak_max;
	u16 sf_txpeak_min;
	u16 sf_rxpeak_max;
	u16 sf_rxpeak_min;
};
struct sec_ts_data {
	u32 flash_page_size;
	u8 boot_ver[3];
	struct device *dev;
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct input_dev *input_dev_pad;
	struct input_dev *input_dev_touch;
	struct sec_ts_plat_data *plat_data;
	struct ts_kit_device_data *chip_data;
	struct platform_device *sec_ts_pdev;
	struct sec_ts_coordinate coord[MAX_SUPPORT_TOUCH_COUNT + MAX_SUPPORT_HOVER_COUNT];
	struct timeval time_pressed[MAX_SUPPORT_TOUCH_COUNT + MAX_SUPPORT_HOVER_COUNT];
	struct timeval time_released[MAX_SUPPORT_TOUCH_COUNT + MAX_SUPPORT_HOVER_COUNT];
	int charger_notify_gpio;
	u8 *event_buff;
	long time_longest;
	u8 lowpower_mode;
	u8 lowpower_status;
	unsigned char project_id[SEC_TS_PROJECTID_MAX];
	u8 brush_mode;
	volatile bool input_closed;
	const char *module_name;
	int irq;
	int touch_count;
	int buff_count;
	int tx_count;
	int tx_default_num;
	int rx_default_num;
	int rx_count;
	int i2c_burstmax;
	int event_length;
	int ta_status;
	volatile int power_status;
	int raw_status;
	int touchkey_glove_mode_status;
	u16 touch_functions;
	u8 charger_mode;
	struct sec_ts_event_coordinate touchtype;
	bool touched[11];
	u8 gesture_status[6];
	u8 cal_limit[SEC_TS_CAL_LIMITDATA_MAX];
	u8 nolh_limit[SEC_TS_NOLH_LIMITDATA_MAX];
	u8 cal_status;
	struct mutex lock;
	struct mutex device_mutex;
	struct mutex i2c_mutex;
	struct mutex eventlock;
	struct delayed_work work_read_info;
	struct completion resume_done;
	struct wake_lock wakelock;
	int frame_size;
	int *pFrame;
	bool probe_done;
	bool reinit_done;
	bool flip_enable;
	bool fw_sd_enable;
	int cover_type;
	u8 cover_cmd;
	u16 rect_data[4];
	int tspid_val;
	int tspicid_val;
	bool use_sponge;
	unsigned int scrub_id;
	unsigned int scrub_x;
	unsigned int scrub_y;
	u8 grip_edgehandler_direction;
	int grip_edgehandler_start_y;
	int grip_edgehandler_end_y;
	u16 grip_edge_range;
	u8 grip_deadzone_up_x;
	u8 grip_deadzone_dn_x;
	int grip_deadzone_y;
	u8 grip_landscape_mode;
	int grip_landscape_edge;
	u16 grip_landscape_deadzone;
	int nv;
	int cal_count;
	int tune_fix_ver;
	bool external_factory;
	int wet_mode;
	u8 boot_mode;
	unsigned char ito_test[4];		/* ito panel tx/rx chanel */
	unsigned char check_multi;
	unsigned int multi_count;		/* multi touch count */
	unsigned int wet_count;			/* wet mode count */
	unsigned int dive_count;		/* dive mode count */
	unsigned int checksum_result;	/* checksum result */
	unsigned char module_id[4];
	unsigned int all_finger_count;
	unsigned int all_force_count;
	unsigned int all_aod_tap_count;
	unsigned int all_spay_count;
	unsigned int max_z_value;
	unsigned int min_z_value;
	unsigned int sum_z_value;
	unsigned int idle_delay;
	unsigned char pressure_cal_base;
	unsigned char pressure_cal_delta;
	int debug_flag;
	const char *cap_test_type;
	int (*sec_ts_i2c_write)(struct sec_ts_data *ts, u8 reg, u8 *data, int len);
	int (*sec_ts_i2c_read)(struct sec_ts_data *ts, u8 reg, u8 *data, int len);
	int (*sec_ts_i2c_write_burst)(struct sec_ts_data *ts, u8 *data, int len);
	int (*sec_ts_i2c_read_bulk)(struct sec_ts_data *ts, u8 *data, int len);
	int (*sec_ts_read_sponge)(struct sec_ts_data *ts, u8 *data);
	struct regulator *regulator_dvdd;
	struct regulator *regulator_avdd;

	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
	int ic_name;
	int is_need_set_pinctrl;
	int is_need_set_reseved_bit;
	const char *default_projectid;
	int is_need_calibrate_after_update_fw;
};

struct sec_ts_plat_data {
	int max_x;
	int max_y;
	unsigned irq_gpio;
	int irq_type;
	int i2c_burstmax;
	int always_lpmode;
	int mis_cal_check;
	const char firmware_name[SEC_TS_MAX_FW_PATH];
	const char *model_name;
	const char *project_name;
	char *regulator_dvdd;
	char *regulator_avdd;
	u32 panel_revision;
	u8 core_version_of_ic[4];
	u8 core_version_of_bin[4];
	u8 config_version_of_ic[4];
	u8 config_version_of_bin[4];
	u8 img_version_of_ic[4];
	u8 img_version_of_bin[4];
	struct pinctrl *pinctrl;
	int (*power)(struct sec_ts_data *data, bool on);
	void (*enable_sync)(bool on);
	int tsp_icid;
	int tsp_id;
	int tsp_vsync;
	bool regulator_boot_on;
	bool support_mt_pressure;
	bool support_dex;
	bool support_sidegesture;
};

int sec_ts_stop_device(struct sec_ts_data *ts);
int sec_ts_start_device(struct sec_ts_data *ts);
void sec_ts_set_lowpowermode(struct sec_ts_data *ts, u8 mode);
int sec_ts_load_fw_request(struct sec_ts_data *ts, u8 sd_enable);
int sec_ts_firmware_update_on_probe(struct sec_ts_data *ts, bool force_update);
int sec_ts_firmware_update_on_hidden_menu(struct sec_ts_data *ts, int update_type);
int sec_ts_glove_mode_enables(struct sec_ts_data *ts, bool enable);
int sec_ts_cover_mode_enalbes(struct sec_ts_data *ts, bool enable);
int sec_ts_charger_mode_enables(struct sec_ts_data *ts, bool enable);
int sec_ts_wait_for_ready(struct sec_ts_data *ts, unsigned int ack);
int sec_ts_function(int (*func_init)(void *device_data), void (*func_remove)(void));
int sec_ts_fn_init(struct sec_ts_data *ts);
int sec_ts_read_calibration_report(struct sec_ts_data *ts);
int sec_ts_execute_force_calibration(struct sec_ts_data *ts, int cal_mode);
int sec_ts_fix_tmode(struct sec_ts_data *ts, u8 mode, u8 state);
int sec_ts_release_tmode(struct sec_ts_data *ts);
int get_tsp_nvm_data(struct sec_ts_data *ts, u8 offset);
void set_tsp_nvm_data_clear(struct sec_ts_data *ts, u8 offset);
int sec_ts_set_custom_library(struct sec_ts_data *ts);

void sec_ts_unlocked_release_all_finger(struct sec_ts_data *ts);
void sec_ts_fn_remove(struct sec_ts_data *ts);
void sec_ts_delay(unsigned int ms);
int sec_ts_read_information(struct sec_ts_data *ts);
#ifdef PAT_CONTROL
void set_pat_magic_number(struct sec_ts_data *ts);
#endif
int sec_ts_run_rawdata_all(struct sec_ts_data *ts, struct sec_ts_test_mode *mode);
int execute_selftest(struct sec_ts_data *ts, bool save_result);
int sec_ts_read_raw_data(struct sec_ts_data *ts, struct sec_ts_test_mode *mode);
int sec_ts_run_self_test(struct sec_ts_data *ts, struct ts_rawdata_info *info);
int sec_ts_read_pid(struct sec_ts_data *ts);
int sec_ts_get_rawcap_debug(struct sec_ts_data *ts, struct ts_diff_data_info *info);
int sec_ts_get_delta_debug(struct sec_ts_data *ts, struct ts_diff_data_info *info);
int sec_ts_do_once_calibrate(void);


#if !defined(CONFIG_SAMSUNG_PRODUCT_SHIP)
int sec_ts_raw_device_init(struct sec_ts_data *ts);
#endif

extern struct class *sec_class;

extern bool tsp_init_done;

extern struct sec_ts_data *ts_dup;


extern void set_grip_data_to_ic(struct sec_ts_data *ts, u8 flag);
extern void sec_ts_set_grip_type(struct sec_ts_data *ts, u8 set_type);


#endif
