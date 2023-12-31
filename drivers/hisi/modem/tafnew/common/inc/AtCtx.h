/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may
* *    be used to endorse or promote products derived from this software
* *    without specific prior written permission.
*
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __ATCTX_H__
#define __ATCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"
#include "v_id.h"
#include "v_typdef.h"
#include "v_msg.h"
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "NVIM_Interface.h"
#include "MnClient.h"
#include "TafApi.h"
#include "MnMsgApi.h"
#include "MnCallApi.h"
#include "TafTypeDef.h"
#include "TafPsApi.h"
#include "TafAppMma.h"
#include "TafAppSsa.h"
#include "Taf_Tafm_Remote.h"
#include "AtMuxInterface.h"
#include "AtCtxPacket.h"
#include "AtTimer.h"
#include "AtInternalMsg.h"
#include "AtMntn.h"
#include "AtImsaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 广播ClientIndex说明，最高的2个bit位表示ModemId。
   Modem0对应的广播Client index为00111111(0x3F)，
   Modem1对应的广播Client index为01111111(0x7F)
   Modem2对应的广播Client index为10111111(0xBF)*/

/*广播Client Id对应的index值*/
/* Modem 0的广播Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_0  (0x3F)

/* Modem 1的广播Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_1  (0x7F)

/* Modem 2的广播Client Index */
#define AT_BROADCAST_CLIENT_INDEX_MODEM_2  (0xBF)

/* 判断是否为广播Client Id */
#define AT_IS_BROADCAST_CLIENT_INDEX(i)    ((AT_BROADCAST_CLIENT_INDEX_MODEM_0 == (i)) \
                                         || (AT_BROADCAST_CLIENT_INDEX_MODEM_1 == (i)) \
                                         || (AT_BROADCAST_CLIENT_INDEX_MODEM_2 == (i)))

/* Modem ID在NV项中的Bit位 */
#define AT_NV_CLIENT_CONFIG_MODEM_ID_OFFSET (2)


/*********************************PORT Begin*****************************/

#define AT_INVALID_SPE_PORT             (-1)

/*================================PORT NO Begin================================*/

typedef VOS_UINT8 AT_PORT_NO;
#define AT_BUTT_PORT_NO                 (0xFF)              /*无效PORT NO*/

#define AT_UART_PORT_NO                 (0)

/* MODEM口修改为always-on方式，modem链路的建立由AT在PID初始化时执行，那么所使用的PORT_TYPE与原先架构中底软所使用的一致 */
#define AT_PORT_TYPE_MODEM              (3)
#define AT_USB_MODEM_PORT_NO            (4)                 /*目前架构中，MODEM保持与B020之前的实现一致，该串口号目前无效*/
#define AT_SOCK_PORT_NO                 (5)                 /*增加SOCK端口*/
#define AT_APP_PORT_NO                  (6)                 /*增加APP端口*/
#define AT_APP_SOCK_PORT_NO             (7)                 /*增加APP SOCK端口*/
#if (VOS_WIN32 == VOS_OS_VER)
#define AT_USB_COM_PORT_NO              (2)
#else
#define AT_USB_COM_PORT_NO              (DMS_PHY_BEAR_USB_PCUI) /*值为8*/
#endif
#define AT_CTR_PORT_NO                  (DMS_PHY_BEAR_USB_CTRL)/*值为9，产品线需求，增加一个control端口*/
#define AT_PCUI2_PORT_NO                (DMS_PHY_BEAR_USB_PCUI2)/*值为10，天际通需求，增加一个PCUI2端口*/

#define AT_NDIS_PORT_NO                 (DMS_PHY_BEAR_USB_NCM)     /*值为11，NDIS AT端口号，该端口号无用*/
#define AT_HSIC1_PORT_NO                (12)                /*HSIC AT通道1端口*/
#define AT_HSIC2_PORT_NO                (13)                /*HSIC AT通道2端口*/
#define AT_HSIC3_PORT_NO                (14)                /*HSIC AT通道3端口*/
#define AT_HSIC4_PORT_NO                (15)                /*HSIC AT通道4端口*/
#define AT_MUX1_PORT_NO                 (16)                /*MUX AT通道1端口*/
#define AT_MUX2_PORT_NO                 (17)                /*MUX AT通道2端口*/
#define AT_MUX3_PORT_NO                 (18)                /*MUX AT通道3端口*/
#define AT_MUX4_PORT_NO                 (19)                /*MUX AT通道4端口*/
#define AT_MUX5_PORT_NO                 (20)                /*MUX AT通道5端口*/
#define AT_MUX6_PORT_NO                 (21)                /*MUX AT通道6端口*/
#define AT_MUX7_PORT_NO                 (22)                /*MUX AT通道7端口*/
#define AT_MUX8_PORT_NO                 (23)                /*MUX AT通道8端口*/
#define AT_HSIC_MODEM_PORT_NO           (24)                /* HSIC MODEM端口 */
#define AT_HSUART_PORT_NO               (25)                /* HSUART端口 */

#define AT_MIN_ABORT_TIME_INTERNAL      (13)
#define AT_MAX_TICK_TIME_VALUE          (0xFFFFFFFFU)

/*================================PORT NO End================================*/
/*********************************PORT End*****************************/

/*********************************COMM Begin*****************************/
typedef TAF_UINT8 AT_CMEE_TYPE;
#define AT_CMEE_ONLY_ERROR                0
#define AT_CMEE_ERROR_CODE                1
#define AT_CMEE_ERROR_CONTENT             2

/* AP-Modem 中，目前规格支持最大8个MUX AT通道 */
#define AT_MUX_AT_CHANNEL_MAX           (8)

#define AT_MUX_AT_CHANNEL_INDEX_1       (0)
#define AT_MUX_AT_CHANNEL_INDEX_2       (1)
#define AT_MUX_AT_CHANNEL_INDEX_3       (2)
#define AT_MUX_AT_CHANNEL_INDEX_4       (3)
#define AT_MUX_AT_CHANNEL_INDEX_5       (4)
#define AT_MUX_AT_CHANNEL_INDEX_6       (5)
#define AT_MUX_AT_CHANNEL_INDEX_7       (6)
#define AT_MUX_AT_CHANNEL_INDEX_8       (7)
#define AT_OCTET_MOVE_FOUR_BITS    (0x04)  /* 将一个字节移动4位 */
#define AT_OCTET_MOVE_EIGHT_BITS   (0x08)  /* 将一个字节移动8位 */
#define AT_OCTET_LOW_FOUR_BITS     (0x0f)  /* 获取一个字节中的低4位 */
#define AT_OCTET_HIGH_FOUR_BITS    (0xf0)  /* 获取一个字节中的高4位 */
#define AT_MIN(n1,n2)         (((n1) > (n2)) ? (n2):(n1))
/*********************************COMM End*****************************/

/*********************************CC/SS Begin*****************************/
typedef VOS_UINT8 AT_SALS_TYPE;
#define AT_SALS_DISABLE_TYPE            0
#define AT_SALS_ENABLE_TYPE             1

typedef VOS_UINT8 AT_CLIP_TYPE;
#define AT_CLIP_DISABLE_TYPE            0
#define AT_CLIP_ENABLE_TYPE             1

typedef VOS_UINT8 AT_COLP_TYPE;
#define AT_COLP_DISABLE_TYPE            0
#define AT_COLP_ENABLE_TYPE             1

typedef VOS_UINT8 AT_CLIR_TYPE;
#define AT_CLIR_AS_SUBSCRIPT            0
#define AT_CLIR_INVOKE                  1
#define AT_CLIR_SUPPRESS                2

typedef VOS_UINT8 AT_CRC_TYPE;
#define AT_CRC_DISABLE_TYPE             0
#define AT_CRC_ENABLE_TYPE              1

typedef VOS_UINT8 AT_CCWA_TYPE;
#define AT_CCWA_DISABLE_TYPE            0
#define AT_CCWA_ENABLE_TYPE             1

#define AT_SIMST_DISABLE_TYPE          (0)
#define AT_SIMST_ENABLE_TYPE           (1)


typedef VOS_UINT8 AT_CUSD_STATE_TYPE;
#define AT_CUSD_MT_IDL_STATE         0
#define AT_CUSD_MT_REQ_STATE         1
#define AT_CUSD_NT_IND_STATE         2

typedef MN_CALL_MODE_ENUM_U8     AT_CMOD_MODE_ENUM;

/*********************************CC/SS End*****************************/

/*********************************SMS Begin************************************/
#define AT_SMSMT_BUFFER_MAX             (2)

typedef VOS_UINT8 AT_CSCS_TYPE;
#define AT_CSCS_IRA_CODE            0
#define AT_CSCS_UCS2_CODE           1
#define AT_CSCS_GSM_7Bit_CODE       2

typedef VOS_UINT8 AT_CSDH_TYPE;
#define AT_CSDH_NOT_SHOW_TYPE           (0)
#define AT_CSDH_SHOW_TYPE               (1)

typedef VOS_UINT8 AT_CNMI_MODE_TYPE;
#define AT_CNMI_MODE_BUFFER_TYPE            0
#define AT_CNMI_MODE_SEND_OR_DISCARD_TYPE   1
#define AT_CNMI_MODE_SEND_OR_BUFFER_TYPE    2
#define AT_CNMI_MODE_EMBED_AND_SEND_TYPE    3

typedef VOS_UINT8 AT_CNMI_MT_TYPE;
#define AT_CNMI_MT_NO_SEND_TYPE             0
#define AT_CNMI_MT_CMTI_TYPE                1
#define AT_CNMI_MT_CMT_TYPE                 2
#define AT_CNMI_MT_CLASS3_TYPE              3
#define AT_CNMI_MT_TYPE_MAX                 4

typedef VOS_UINT8 AT_CNMI_BM_TYPE;
#define AT_CNMI_BM_NO_SEND_TYPE             0
#define AT_CNMI_BM_CBMI_TYPE                1
#define AT_CNMI_BM_CBM_TYPE                 2
#define AT_CNMI_BM_CLASS3_TYPE              3

typedef VOS_UINT8 AT_CNMI_DS_TYPE;
#define AT_CNMI_DS_NO_SEND_TYPE             0
#define AT_CNMI_DS_CDS_TYPE                 1
#define AT_CNMI_DS_CDSI_TYPE                2
#define AT_CNMI_DS_TYPE_MAX                 3

typedef VOS_UINT8 AT_CNMI_BFR_TYPE;
#define AT_CNMI_BFR_SEND_TYPE               0
#define AT_CNMI_BFR_CLEAR_TYPE              1


#define AT_BUFFER_CBM_EVENT_MAX             5
#define AT_BUFFER_SMT_EVENT_MAX             5


/*********************************SMS End************************************/

/*********************************NET Begin************************************/
typedef VOS_UINT8 AT_MODE_REPORT_TYPE;
#define AT_MODE_RESULT_CODE_NOT_REPORT_TYPE    0
#define AT_MODE_RESULT_CODE_REPORT_TYPE        1

typedef VOS_UINT8 AT_CREG_TYPE;
#define AT_CREG_RESULT_CODE_NOT_REPORT_TYPE    0
#define AT_CREG_RESULT_CODE_BREVITE_TYPE       1
#define AT_CREG_RESULT_CODE_ENTIRE_TYPE        2

typedef VOS_UINT8 AT_CGREG_TYPE;
#define AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE   0
#define AT_CGREG_RESULT_CODE_BREVITE_TYPE      1
#define AT_CGREG_RESULT_CODE_ENTIRE_TYPE       2


#define AT_ROAM_FEATURE_OFF                    0
#define AT_ROAM_FEATURE_ON                     1
/*********************************NET End************************************/

/*********************************CTRL Begin************************************/
/* 记录天线信号格数  */
#define AT_ANTENNA_LEVEL_MAX_NUM        3

#define AT_RSSI_RESULT_CODE_NOT_REPORT_TYPE    (0)

#define AT_CURC_RPT_CFG_MAX_SIZE        (8)
#define AT_CURC_RPT_CFG_PARA_LEN        (16)

/*********************************CTRL End************************************/

/*****************************************************************************
    以下为UART相关宏定义
*****************************************************************************/
/* 新短信RING脚波形高低电平持续时间(ms) */
#define AT_UART_DEFAULT_SMS_RI_ON_INTERVAL      (1000)
#define AT_UART_DEFAULT_SMS_RI_OFF_INTERVAL     (1000)

/* 来电RING脚波形低电平持续时间(ms) */
#define AT_UART_DEFAULT_VOICE_RI_ON_INTERVAL    (1000)
#define AT_UART_DEFAULT_VOICE_RI_OFF_INTERVAL   (4000)

/* 来电RING脚波形循环次数 */
#define AT_UART_DEFAULT_VOICE_RI_CYCLE_TIMES    (10)

#define AT_UART_DEFAULT_BAUDRATE        (AT_UART_BAUDRATE_115200)
#define AT_UART_DEFAULT_FORMAT          (AT_UART_FORMAT_8DATA_1STOP)
/*
 * 注: 不同版本选用的UART IP不同, 默认校验方式差异如下
 *
 * V3R3            --- 空校验 SPACE
 *
 * V7R11(or later) --- 奇校验 ODD
 *
 */
#define AT_UART_DEFAULT_PARITY          (AT_UART_PARITY_ODD)

#define AT_UART_DEFAULT_DCD_MODE        (AT_UART_DCD_MODE_CONNECT_ON)
#define AT_UART_DEFAULT_DTR_MODE        (AT_UART_DTR_MODE_HANGUP_CALL)
#define AT_UART_DEFAULT_DSR_MODE        (AT_UART_DSR_MODE_ALWAYS_ON)

#define AT_UART_DEFAULT_FC_DCE_BY_DTE   (AT_UART_FC_DCE_BY_DTE_NONE)
#define AT_UART_DEFAULT_FC_DTE_BY_DCE   (AT_UART_FC_DTE_BY_DCE_NONE)



#if !defined(AT_ARRAY_SIZE)
#define AT_ARRAY_SIZE(a)                (sizeof((a)) / sizeof((a[0])))
#endif

/* 将port对应的位设置为1 */
#define AT_SET_BIT32(n)       ((VOS_UINT32)1 << (n))

#define AT_SET_BIT32_SELECT0(n) (((n) < 32) ? AT_SET_BIT32((n) % 32) : 0)

#define AT_SET_BIT32_SELECT1(n) ((((n) >= 32) && ((n) < 64)) ? AT_SET_BIT32((n) % 32) : 0)

#define AT_SET_BIT32_SELECT2(n) ((((n) >= 64) && ((n) < 96)) ? AT_SET_BIT32((n) % 32) : 0)

#define AT_CLIENT_CFG_ELEMENT(port) \
            { AT_CLIENT_ID_##port, TAF_NV_CLIENT_CFG_##port, #port, \
            {AT_SET_BIT32_SELECT0(TAF_NV_CLIENT_CFG_##port), AT_SET_BIT32_SELECT1(TAF_NV_CLIENT_CFG_##port), AT_SET_BIT32_SELECT2(TAF_NV_CLIENT_CFG_##port)} }


#define AT_GET_CLIENT_CFG_TAB_LEN()         (g_ucAtClientCfgMapTabLen)

#define AT_PORT_LEN_MAX                     (20)

/* WIFI n模式WL命令的速率值为0~7，共8个 */
#define AT_WIFI_N_RATE_NUM              (8)

#define AT_RELEASE_R11                  (0x00000b00)

#define AT_MAX_MSG_NUM                  (80)

#define AT_TEST_ECC_FILE_NAME_MAX_LEN   (75)

#define  AT_SET_SIMLOCK_DATA_HMAC_LEN   (64)

#define  AT_CONST_NUM_0                 (0)
#define  AT_CONST_NUM_1                 (1)
#define  AT_CONST_NUM_2                 (2)
#define  AT_CONST_NUM_3                 (3)
#define  AT_CONST_NUM_4                 (4)
#define  AT_CONST_NUM_5                 (5)
#define  AT_CONST_NUM_6                 (6)
#define  AT_CONST_NUM_22                (22)
#define  AT_CONST_NUM_23                (23)

#define  AT_CONST_ONE                   (1)
#define  AT_CONST_TEN                   (10)
#define  AT_CONST_HUNDRED               (100)
#define  AT_CONST_THOUSAND              (1000)
#define  AT_CONST_TEN_THOUSAND          (10000)
#define  AT_CONST_HUNDRED_THOUSAND      (100000)
#define  AT_CONST_MILLION               (1000000)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*********************************TIMER Begin*****************************/
enum AT_INTERNAL_TIMER_TYPE_ENUM
{
    AT_S0_TIMER               = 1,
    AT_HOLD_CMD_TIMER         = 2,
    AT_SHUTDOWN_TIMER         = 8,

    AT_VOICE_RI_TIMER         = 9,
    AT_SMS_RI_TIMER           = 10,

    AT_AUTH_PUBKEY_TIMER      = 11,

    AT_SIMLOCKWRITEEX_TIMER   = 12,

    AT_WAIT_WLAN_ACT_PDN_CNF_TIMER      = 13,
    AT_WAIT_WLAN_DEACT_PDN_CNF_TIMER    = 14,
    AT_PROTECT_PDN_IN_DATA_SYS_TIMER    = 15,

    AT_INTERNAL_TIMER_BUTT
};
/*********************************TIMER End*****************************/

/*********************************PORT Begin*****************************/


enum AT_IO_LEVEL_ENUM
{
    AT_IO_LEVEL_LOW                     = 0,
    AT_IO_LEVEL_HIGH                    = 1,

    AT_IO_LEVEL_BUTT
};
typedef VOS_UINT8 AT_IO_LEVEL_ENUM_UINT8;

/* 与AT^APRPTPORTSEL命令配合使用，标识指定HSIC AT通道是否允许AT命令主动上报 */
enum AT_HSIC_REPORT_TYPE_ENUM
{
    AT_HSIC_REPORT_ON,                  /* 允许主动上报 */
    AT_HSIC_REPORT_OFF,                 /* 不允许主动上报 */

    AT_HSIC_REPORT_BUTT
};
typedef VOS_UINT32 AT_HSIC_REPORT_TYPE_ENUM_UINT32;
/*********************************PROT End*****************************/

/*********************************CTRL Begin*****************************/


enum AT_CMD_ANTENNA_LEVEL_ENUM
{
    AT_CMD_ANTENNA_LEVEL_0,
    AT_CMD_ANTENNA_LEVEL_1,
    AT_CMD_ANTENNA_LEVEL_2,
    AT_CMD_ANTENNA_LEVEL_3,
    AT_CMD_ANTENNA_LEVEL_4,
    AT_CMD_ANTENNA_LEVEL_BUTT
};
typedef VOS_UINT8 AT_CMD_ANTENNA_LEVEL_ENUM_UINT8;
/*********************************CTRL End************************************/

/*********************************COMM Begin**********************************/
enum AT_CLCK_PARA_CLASS_ENUM
{
    AT_CLCK_PARA_CLASS_VOICE                    = 0x01,
    AT_CLCK_PARA_CLASS_DATA                     = 0x02,
    AT_CLCK_PARA_CLASS_FAX                      = 0x04,
    AT_CLCK_PARA_CLASS_VOICE_FAX                = 0x05,
    AT_CLCK_PARA_CLASS_VOICE_DATA_FAX           = 0x07,
    AT_CLCK_PARA_CLASS_SMS                      = 0x08,
    AT_CLCK_PARA_CLASS_FAX_SMS                  = 0x0C,
    AT_CLCK_PARA_CLASS_VOICE_FAX_SMS            = 0x0D,
    AT_CLCK_PARA_CLASS_VOICE_DATA_FAX_SMS       = 0x0F,
    AT_CLCK_PARA_CLASS_DATA_SYNC                = 0x10,
    AT_CLCK_PARA_CLASS_DATA_ASYNC               = 0x20,
    AT_CLCK_PARA_CLASS_DATA_PKT                 = 0x40,
    AT_CLCK_PARA_CLASS_DATA_SYNC_PKT            = 0x50,
    AT_CLCK_PARA_CLASS_DATA_PAD                 = 0x80,
    AT_CLCK_PARA_CLASS_DATA_ASYNC_PAD           = 0xA0,
    AT_CLCK_PARA_CLASS_DATA_SYNC_ASYNC_PKT_PKT  = 0xF0,
    AT_CLCK_PARA_CLASS_ALL                      = 0xFF,
};
typedef VOS_UINT8 AT_CLCK_PARA_CLASS_ENUM_UINT8;

/*********************************COMM End************************************/

/*********************************CC/SS Begin*****************************/


/*********************************CC/SS End*****************************/

/*********************************SMS Begin************************************/
enum AT_CMGF_MSG_FORMAT_ENUM
{
    AT_CMGF_MSG_FORMAT_PDU,
    AT_CMGF_MSG_FORMAT_TEXT
};
typedef TAF_UINT8 AT_CMGF_MSG_FORMAT_ENUM_U8;

/*********************************SMS End************************************/

/*********************************NET Begin************************************/


enum AT_CEREG_TYPE_ENUM
{
    AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE,    /* 禁止+CEREG 的主动上报 */
    AT_CEREG_RESULT_CODE_BREVITE_TYPE,       /* 网络注册状态发生改变时，使用+CEREG: <stat>的主动上报方式进行上报*/
    AT_CEREG_RESULT_CODE_ENTIRE_TYPE,        /* 小区信息发生改变时，使用+CEREG:<stat>[,<tac>,<ci>[,<AcT>]]的主动上报方式进行上报*/
    AT_CEREG_RESULT_CODE_TYPE_BUTT
};
typedef VOS_UINT8 AT_CEREG_TYPE_ENUM_UINT8;


enum AT_CERSSI_REPORT_TYPE_ENUM
{
    AT_CERSSI_REPORT_TYPE_NOT_REPORT,               /* 禁止^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_1DB_CHANGE_REPORT,        /* 信号质量改变超过1db时^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_2DB_CHANGE_REPORT,        /* 信号质量改变超过2db时^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_3DB_CHANGE_REPORT,        /* 信号质量改变超过3db时^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_4DB_CHANGE_REPORT,        /* 信号质量改变超过4db时^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT,        /* 信号质量改变超过5db时^CERSSI的主动上报 */
    AT_CERSSI_REPORT_TYPE_BUTT
};
typedef VOS_UINT8 AT_CERSSI_REPORT_TYPE_ENUM_UINT8;



enum AT_RPT_CMD_INDEX_ENUM
{
    AT_RPT_CMD_MODE                     = 0,
    AT_RPT_CMD_RSSI,
    AT_RPT_CMD_SRVST,
    AT_RPT_CMD_SIMST,
    AT_RPT_CMD_TIME,
    AT_RPT_CMD_SMMEMFULL,
    AT_RPT_CMD_CTZV,

    AT_RPT_CMD_CTZE,

    AT_RPT_CMD_DSFLOWRPT,
    AT_RPT_CMD_ORIG,
    AT_RPT_CMD_CONF,
    AT_RPT_CMD_CONN,
    AT_RPT_CMD_CEND,
    AT_RPT_CMD_STIN,

    AT_RPT_CMD_CERSSI,
    AT_RPT_CMD_ANLEVEL,
    AT_RPT_CMD_LWCLASH,
    AT_RPT_CMD_XLEMA,
    AT_RPT_CMD_ACINFO,

    AT_RPT_CMD_PLMN,

    /* call state的上报由CURC控制 */
    AT_RPT_CMD_CALLSTATE,

    /* 新增单个命令控制的主动上报命令 */
    AT_RPT_CMD_CREG,
    AT_RPT_CMD_CUSD,
    AT_RPT_CMD_CSSI,
    AT_RPT_CMD_CSSU,
    AT_RPT_CMD_LWURC,
    AT_RPT_CMD_CUUS1I,
    AT_RPT_CMD_CUUS1U,
    AT_RPT_CMD_CGREG,
    AT_RPT_CMD_CEREG,

    AT_RPT_CMD_BUTT
};
typedef VOS_UINT8 AT_RPT_CMD_INDEX_ENUM_UINT8;


enum AT_CMD_RPT_CTRL_TYPE_ENUM
{
    AT_CMD_RPT_CTRL_BY_CURC,               /* 主动上报受CURC控制 */
    AT_CMD_RPT_CTRL_BY_UNSOLICITED,        /* 主动上报受单独的命令控制 */
    AT_CMD_RPT_CTRL_BUTT
};
typedef VOS_UINT8 AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名    : AT_RATE_WCDMA_CATEGORY_ENUM
 协议表格  : 无
 结构说明  : WCDMA模式的能力枚举
*****************************************************************************/
enum AT_RATE_WCDMA_CATEGORY_ENUM
{
    AT_RATE_WCDMA_R99                   = 0,
    AT_RATE_WCDMA_CATEGORY_6            = 6,
    AT_RATE_WCDMA_CATEGORY_8            = 8,
    AT_RATE_WCDMA_CATEGORY_9            = 9,
    AT_RATE_WCDMA_CATEGORY_10           = 10,
    AT_RATE_WCDMA_CATEGORY_12           = 12,
    AT_RATE_WCDMA_CATEGORY_14           = 14,
    AT_RATE_WCDMA_CATEGORY_18           = 18,
    AT_RATE_WCDMA_CATEGORY_24           = 24,
    AT_RATE_WCDMA_CATEGORY_26           = 26,
    AT_RATE_WCDMA_CATEGORY_28           = 28
};
typedef VOS_UINT8 AT_RATE_WCDMA_CATEGORY_ENUM_UINT8;

/* VDF需求: CREG/CGREG命令<CI>域字节上报数枚举 */
enum ELF_CREG_CGREG_CI_RPT_BYTE_ENUM
{
    CREG_CGREG_CI_RPT_TWO_BYTE        = 0, /* CREG/CGREG的<CI>域以2字节方式上报*/
    CREG_CGREG_CI_RPT_FOUR_BYTE       = 1, /* CREG/CGREG的<CI>域以4字节方式上报*/
    CREG_CGREG_CI_RPT_BUTT
};
typedef VOS_UINT8   CREG_CGREG_CI_RPT_BYTE_ENUM;
/*********************************NET End************************************/

/*********************************AGPS Begin************************************/


enum AT_CPOSR_FLG_ENUM
{
    AT_CPOSR_DISABLE        = 0,                                                /* 不允许主动上报 */
    AT_CPOSR_ENABLE,                                                            /* 允许主动上报 */
    AT_CPOSR_BUTT
};
typedef VOS_UINT8 AT_CPOSR_FLG_ENUM_UNIT8;


enum AT_XCPOSR_FLG_ENUM
{
    AT_XCPOSR_DISABLE        = 0,                                                /* 不允许主动上报 */
    AT_XCPOSR_ENABLE,                                                            /* 允许主动上报 */
    AT_XCPOSR_BUTT
};
typedef VOS_UINT8 AT_XCPOSR_FLG_ENUM_UNIT8;


enum AT_CMOLRE_TYPE_ENUM
{
    AT_CMOLRE_NUMERIC        = 0,                                               /* 数字格式 */
    AT_CMOLRE_VERBOSE,                                                          /* 字符描述格式 */

    AT_CMOLRE_TYPE_BUTT
};
typedef VOS_UINT8 AT_CMOLRE_TYPE_ENUM_UNIT8;


enum AT_XML_END_CHAR_ENUM
{
    AT_XML_CTRL_Z        = 0,                                                   /* 结束字符为“ctrl-Z” */
    AT_XML_ESC,                                                                 /* 结束字符为“ESC” */
    AT_XML_BUTT
};
typedef VOS_UINT8 AT_XML_END_CHAR_ENUM_UNIT8;


enum AT_XML_PROC_TYPE_ENUM
{
    AT_XML_PROC_TYPE_FINISH             = 0,                                    /* 输入了"ctrl-Z"或"ESC"    */
    AT_XML_PROC_TYPE_CONTINUE           = 1,                                    /* 输入了回车符             */
    AT_XML_PROC_TYPE_BUTT
};
typedef VOS_UINT8 AT_XML_PROC_TYPE_ENUM_UINT8;
/*********************************AGPS End************************************/


enum AT_ANT_STATE_ENUM
{
    AT_ANT_AIRWIRE_MODE            =   0,  /* 天线模式 */
    AT_ANT_CONDUCTION_MODE         =   1,  /* 传导模式 */
    AT_ANT_MODE_BUTT
};
typedef VOS_UINT16 AT_ANT_STATE_ENUM_UINT16;


enum AT_UART_BAUDRATE_ENUM
{
    AT_UART_BAUDRATE_0                  = 0,                /* 表示波特率自适应 */
    AT_UART_BAUDRATE_300                = 300,              /* 对应波特率为300 */
    AT_UART_BAUDRATE_600                = 600,              /* 对应波特率为600 */
    AT_UART_BAUDRATE_1200               = 1200,             /* 对应波特率为1200 */
    AT_UART_BAUDRATE_2400               = 2400,             /* 对应波特率为2400 */
    AT_UART_BAUDRATE_4800               = 4800,             /* 对应波特率为4800 */
    AT_UART_BAUDRATE_9600               = 9600,             /* 对应波特率为9600 */
    AT_UART_BAUDRATE_19200              = 19200,            /* 对应波特率为19200 */
    AT_UART_BAUDRATE_38400              = 38400,            /* 对应波特率为38400 */
    AT_UART_BAUDRATE_57600              = 57600,            /* 对应波特率为57600 */
    AT_UART_BAUDRATE_115200             = 115200,           /* 对应波特率为115200 */
    AT_UART_BAUDRATE_230400             = 230400,           /* 对应波特率为230400 */
    AT_UART_BAUDRATE_250000             = 250000,           /* 对应波特率为250000 */
    AT_UART_BAUDRATE_300000             = 300000,           /* 对应波特率为300000 */
    AT_UART_BAUDRATE_375000             = 375000,           /* 对应波特率为375000 */
    AT_UART_BAUDRATE_460800             = 460800,           /* 对应波特率为460800 */
    AT_UART_BAUDRATE_600000             = 600000,           /* 对应波特率为600000 */
    AT_UART_BAUDRATE_750000             = 750000,           /* 对应波特率为750000 */
    AT_UART_BAUDRATE_921600             = 921600,           /* 对应波特率为921600 */
    AT_UART_BAUDRATE_1000000            = 1000000,          /* 对应波特率为1000000 */
    AT_UART_BAUDRATE_1152000            = 1152000,          /* 对应波特率为1152000 */
    AT_UART_BAUDRATE_1500000            = 1500000,          /* 对应波特率为1500000 */
    AT_UART_BAUDRATE_2000000            = 2000000,          /* 对应波特率为2000000 */
    AT_UART_BAUDRATE_2250000            = 2250000,          /* 对应波特率为2250000 */
    AT_UART_BAUDRATE_2764800            = 2764800,          /* 对应波特率为2764800 */
    AT_UART_BAUDRATE_3000000            = 3000000,          /* 对应波特率为3000000 */
    AT_UART_BAUDRATE_4000000            = 4000000,          /* 对应波特率为4000000 */

    AT_UART_BAUDRATE_BUTT
};
typedef VOS_UINT32 AT_UART_BAUDRATE_ENUM_UINT32;


enum AT_UART_FORMAT_ENUM
{
    AT_UART_FORMAT_AUTO_DETECT          = 0x00,             /* auto detect */
    AT_UART_FORMAT_8DATA_2STOP          = 0x01,             /* 8 data 2 stop */
    AT_UART_FORMAT_8DATA_1PARITY_1STOP  = 0x02,             /* 8 data 1 parity 1 stop*/
    AT_UART_FORMAT_8DATA_1STOP          = 0x03,             /* 8 data 1 stop */
    AT_UART_FORMAT_7DATA_2STOP          = 0x04,             /* 7 data 2 stop */
    AT_UART_FORMAT_7DATA_1PARITY_1STOP  = 0x05,             /* 7 data 1 parity 1 stop */
    AT_UART_FORMAT_7DATA_1STOP          = 0x06,             /* 7 data 1 stop */

    AT_UART_FORMAT_BUTT
};
typedef VOS_UINT8 AT_UART_FORMAT_ENUM_UINT8;


enum AT_UART_PARITY_ENUM
{
    AT_UART_PARITY_ODD                  = 0x00,             /* ODD 奇 */
    AT_UART_PARITY_EVEN                 = 0x01,             /* EVEN 偶 */
    AT_UART_PARITY_MARK                 = 0x02,             /* MARK */
    AT_UART_PARITY_SPACE                = 0x03,             /* SPACE */

    AT_UART_PARITY_BUTT
};
typedef VOS_UINT8 AT_UART_PARITY_ENUM_UINT8;


enum AT_UART_DATA_LEN_ENUM
{
    AT_UART_DATA_LEN_5_BIT              = 5,
    AT_UART_DATA_LEN_6_BIT              = 6,
    AT_UART_DATA_LEN_7_BIT              = 7,
    AT_UART_DATA_LEN_8_BIT              = 8,

    AT_UART_DATA_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_DATA_LEN_ENUM_UINT8;


enum AT_UART_STOP_LEN_ENUM
{
    AT_UART_STOP_LEN_1_BIT              = 1,
    AT_UART_STOP_LEN_2_BIT              = 2,

    AT_UART_STOP_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_STOP_LEN_ENUM_UINT8;


enum AT_UART_PARITY_LEN_ENUM
{
    AT_UART_PARITY_LEN_0_BIT            = 0,
    AT_UART_PARITY_LEN_1_BIT            = 1,

    AT_UART_PARITY_LEN_BUTT
};
typedef VOS_UINT8 AT_UART_PARITY_LEN_ENUM_UINT8;


enum AT_UART_DCD_MODE_ENUM
{
    AT_UART_DCD_MODE_ALWAYS_ON          = 0x00,
    AT_UART_DCD_MODE_CONNECT_ON         = 0x01,

    AT_UART_DCD_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DCD_MODE_ENUM_UINT8;


enum AT_UART_DTR_MODE_ENUM
{
    AT_UART_DTR_MODE_IGNORE             = 0x00,
    AT_UART_DTR_MODE_SWITCH_CMD_MODE    = 0x01,
    AT_UART_DTR_MODE_HANGUP_CALL        = 0x02,

    AT_UART_DTR_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DTR_MODE_ENUM_UINT8;


enum AT_UART_DSR_MODE_ENUM
{
    AT_UART_DSR_MODE_ALWAYS_ON          = 0x00,
    AT_UART_DSR_MODE_CONNECT_ON         = 0x01,

    AT_UART_DSR_MODE_BUTT
};
typedef VOS_UINT8 AT_UART_DSR_MODE_ENUM_UINT8;


enum AT_UART_FC_DCE_BY_DTE_ENUM
{
    AT_UART_FC_DCE_BY_DTE_NONE                  = 0x00,
    AT_UART_FC_DCE_BY_DTE_XON_OR_XOFF_REMOVE    = 0x01,
    AT_UART_FC_DCE_BY_DTE_RTS                   = 0x02,
    AT_UART_FC_DCE_BY_DTE_XON_OR_XOFF_PASS      = 0x03,

    AT_UART_FC_DCE_BY_DTE_BUTT
};
typedef VOS_UINT8 AT_UART_FC_DCE_BY_DTE_ENUM_UINT8;


enum AT_UART_FC_DTE_BY_DCE_ENUM
{
    AT_UART_FC_DTE_BY_DCE_NONE                  = 0x00,
    AT_UART_FC_DTE_BY_DCE_XON_OR_XOFF_REMOVE    = 0x01,
    AT_UART_FC_DTE_BY_DCE_CTS                   = 0x02,

    AT_UART_FC_DTE_BY_DCE_BUTT
};
typedef VOS_UINT8 AT_UART_FC_DTE_BY_DCE_ENUM_UINT8;


enum AT_UART_RI_TYPE_ENUM
{
    AT_UART_RI_TYPE_VOICE               = 0x00,
    AT_UART_RI_TYPE_SMS                 = 0x01,

    AT_UART_RI_TYPE_BUTT
};
typedef VOS_UINT32 AT_UART_RI_TYPE_ENUM_UINT32;


enum AT_UART_RI_STATUS_ENUM
{
    AT_UART_RI_STATUS_STOP                = 0x00,
    AT_UART_RI_STATUS_RINGING             = 0x01,

    AT_UART_RI_STATUS_BUTT
};
typedef VOS_UINT8 AT_UART_RI_STATUS_ENUM_UINT8;


enum AT_PORT_BUFF_CFG_ENUM
{
    AT_PORT_BUFF_DISABLE                     = 0,
    AT_PORT_BUFF_ENABLE,

    AT_PORT_BUFF_BUTT
};

typedef VOS_UINT8 AT_PORT_BUFF_CFG_ENUM_UINT8;

typedef VOS_VOID (*AT_UART_WM_LOW_FUNC)(VOS_UINT8 ucIndex);


enum AT_CNAP_TYPE_ENUM
{
    AT_CNAP_DISABLE_TYPE              = 0,
    AT_CNAP_ENABLE_TYPE               = 1,
    AT_CNAP_TYPE_BUTT,
};
typedef VOS_UINT8 AT_CNAP_TYPE_ENUM_UINT8;



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


typedef struct
{
    VOS_UINT32                           ulModem0Pid;
    VOS_UINT32                           ulModem1Pid;
    VOS_UINT32                           ulModem2Pid;
    VOS_UINT32                           ulReserved;
}AT_MODEM_PID_TAB_STRU;

/*********************************Modem CTX Begin*****************************/

typedef struct
{
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32 enCardType;                             /* 卡类型:SIM、USIM */
    USIMM_CARDAPP_SERVIC_ENUM_UINT32    enCardStatus;                           /* 卡状态*/
    USIMM_CARD_MEDIUM_TYPE_ENUM_UINT32  enCardMediumType;                       /* 卡MEDIUM类型 */
    VOS_UINT8                           aucIMSI[9];                             /* IMSI号*/
    VOS_UINT8                           ucIMSILen;                              /* IMSI长度 */
    VOS_UINT8                           aucReserve[2];
    TAF_MMA_SIMSQ_STATE_ENUM_UINT32     enSimsqStatus;
    VOS_UINT8                           aucRsv[4];
}AT_USIM_INFO_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucPlatformSptLte;
    VOS_UINT8                           ucPlatformSptWcdma;
    VOS_UINT8                           ucPlatformSptGsm;
    VOS_UINT8                           ucPlatformSptUtralTDD;
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    VOS_UINT8                           ucPlatformSptNR;
    VOS_UINT8                           aucReserved[3];
#else
    VOS_UINT8                           aucReserved[4];
#endif
}AT_MODEM_SPT_RAT_STRU;


typedef struct
{
    AT_MODEM_SPT_RAT_STRU               stPlatformRatList;
    VOS_UINT8                           ucIsCLMode;
    VOS_UINT8                           aucReserved[7];
}AT_MODEM_SPT_CAP_STRU;

/*********************************CTRL CTX Begin*****************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV是否激活标志, 0: 不激活，1: 激活 */
    VOS_UINT8                           ucAtStatusReportGeneralControl;         /* 私有命令是否允许状态上报*/
}NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU;


typedef struct
{
    AT_CLCK_PARA_CLASS_ENUM_UINT8       enClass;
    TAF_BASIC_SERVICE_TYPE              enServiceType;
    TAF_BASIC_SERVICE_CODE              enServiceCode;
} AT_CLCK_CLASS_SERVICE_TBL_STRU;

/*********************************CTRL CTX Begin*****************************/

/*********************************CC/SS CTX Begin*****************************/

typedef MN_CALL_CS_DATA_CFG_STRU AT_CBST_DATA_CFG_STRU;

typedef struct
{
    HTIMER                              s0Timer;
    VOS_BOOL                            bTimerStart;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucS0TimerLen;
    VOS_UINT8                           ucReserved;                             /* 保留 */
    VOS_UINT32                          ulTimerName;
    VOS_UINT8                           aucReserved[4];
}AT_S0_TIMER_INFO_STRU;

typedef MN_CALL_CUG_CFG_STRU     AT_CCUG_CFG_STRU;

/*********************************CC/SS CTX End*****************************/

/*********************************SMS CTX Begin*****************************/
typedef struct
{
    AT_CNMI_MODE_TYPE                   CnmiModeType;
    AT_CNMI_MT_TYPE                     CnmiMtType;
    AT_CNMI_BM_TYPE                     CnmiBmType;
    AT_CNMI_DS_TYPE                     CnmiDsType;
    AT_CNMI_BFR_TYPE                    CnmiBfrType;
    AT_CNMI_MODE_TYPE                   CnmiTmpModeType;
    AT_CNMI_MT_TYPE                     CnmiTmpMtType;
    AT_CNMI_BM_TYPE                     CnmiTmpBmType;
    AT_CNMI_DS_TYPE                     CnmiTmpDsType;
    AT_CNMI_BFR_TYPE                    CnmiTmpBfrType;
    VOS_UINT8                           aucReserved[6];
}AT_CNMI_TYPE_STRU;

typedef struct
{
    MN_MSG_EVENT_INFO_STRU              astEvent[AT_BUFFER_CBM_EVENT_MAX];
    VOS_UINT8                           aucUsed[AT_BUFFER_CBM_EVENT_MAX];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved[2];
}AT_CBM_BUFFER_STRU;



typedef struct
{
    VOS_UINT8                           ucActFlg;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;
    VOS_UINT8                           aucReserved[6];
}AT_SMS_MT_CUSTOMIZE_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;
    VOS_UINT8                           ucFo;
    VOS_UINT8                           ucTmpFo;
    VOS_UINT8                           aucReserve1[2];
}AT_MSG_FO_STRU;

typedef struct
{
    VOS_BOOL                            bFoUsed;
    VOS_UINT8                           ucFo;
    VOS_UINT8                           ucTmpFo;
    VOS_UINT8                           ucDefaultSmspIndex;
    VOS_UINT8                           aucReserve1[1];
    MN_MSG_VALID_PERIOD_STRU            stVp;
    MN_MSG_VALID_PERIOD_STRU            stTmpVp;
    AT_MSG_FO_STRU                      stFo;
    MN_MSG_SRV_PARAM_STRU               stParmInUsim;
}AT_CSCA_CSMP_INFO_STRU;

typedef struct
{
    MN_MSG_MEM_STORE_ENUM_U8            enMemReadorDelete;
    MN_MSG_MEM_STORE_ENUM_U8            enMemSendorWrite;
    MN_MSG_MEM_STORE_ENUM_U8            enTmpMemReadorDelete;
    MN_MSG_MEM_STORE_ENUM_U8            enTmpMemSendorWrite;
    VOS_UINT8                           aucReserved[4];
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   stUsimStorage;
    MN_MSG_STORAGE_LIST_EVT_INFO_STRU   stNvimStorage;
}AT_MSG_CPMS_STRU;

typedef struct
{
    TAF_BOOL                            bUsed;
    VOS_UINT8                           aucReserved[4];
    MN_MSG_EVENT_INFO_STRU             *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU           *pstTsDataInfo;
}AT_SMS_MT_BUFFER_STRU;

typedef struct
{
    MN_MSG_EVENT_INFO_STRU              astEvent[AT_BUFFER_SMT_EVENT_MAX];
    VOS_UINT8                           aucUsed[AT_BUFFER_SMT_EVENT_MAX];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucReserved[2];
}AT_SMT_BUFFER_STRU;


/*********************************SMS CTX End*****************************/

/*********************************NET CTX Begin*****************************/
typedef struct
{
    AT_COPS_FORMAT_TYPE                 FormatType;
}AT_COPS_TYPE_STRU;

/*********************************NET CTX End*****************************/


/*********************************AGPS CTX Begin*****************************/
/*****************************************************************************
 结构名    : AT_XML_STRU
 结构说明  : AT模块XML文本结构
*****************************************************************************/
typedef struct
{
    VOS_CHAR                           *pcXmlTextHead;                          /* XML码流存储区 */
    VOS_CHAR                           *pcXmlTextCur;                           /* 指示当前XML文本长度 */
}AT_XML_STRU;

/*********************************AGPS CTX End*****************************/




typedef struct
{
    VOS_UINT8                           ucNumOfCalls;                           /* 所有正在通话的个数 */
    VOS_UINT8                           aucReserved[7];
    TAF_CALL_ECONF_INFO_PARAM_STRU      astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];  /* 每一个成员的信息 */
}AT_ECONF_INFO_STRU;


typedef struct
{
    /*  1 DD-MMM-YYYY
        2 DD-MM-YY
        3 MM/DD/YY
        4 DD/MM/YY
        5 DD.MM.YY
        6 YYMMDD
        7 YY-MM-DD  */
    VOS_UINT8                           ucMode;
    /*  1 yy/MM/dd
        2 yyyy/MM/dd */
    VOS_UINT8                           ucAuxMode;
    VOS_UINT8                           aucReserved[6];
}AT_CSDF_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucBfr;
    VOS_UINT8                           aucReserved[6];
}AT_CGEREP_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulCurIsExistCallFlag;                   /* 当前是否存在呼叫标志 */
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause;                           /* 用于记录CS域错误码 */

    AT_S0_TIMER_INFO_STRU               stS0TimeInfo;                           /* 自动应答时间，0表示关闭自动应答，1~255，启动自动应答的时间 */

    AT_ECONF_INFO_STRU                  stEconfInfo;

    TAF_CALL_ERROR_INFO_TEXT_STRU       stErrInfoText;                          /* SIP CANCEL消息错误原因值对应的文本信息 */

    AT_CVHU_MODE_ENUM_UINT8             enCvhuMode;                             /* CVHU参数定制，控制是否支持ATH挂断语音 */
    VOS_UINT8                           aucReserved[3];

}AT_MODEM_CC_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usUssdTransMode;                        /* USSD传输模式 */
    AT_CMOD_MODE_ENUM                   enCModType;                             /* 呼叫模式类型 */
    AT_SALS_TYPE                        ucSalsType;                             /* 使能/禁止线路选择 */
    AT_CLIP_TYPE                        ucClipType;                             /* 使能/禁止主叫号码显示 */
    AT_CLIR_TYPE                        ucClirType;                             /* 使能/禁止主叫号码限制 */
    AT_COLP_TYPE                        ucColpType;                             /* 使能/禁止连接号码显示 */
    AT_CRC_TYPE                         ucCrcType;                              /* 使能/禁止来电指示扩展上报格式 */
    AT_CCWA_TYPE                        ucCcwaType;                             /* 使能/禁止呼叫等待 */
    AT_CNAP_TYPE_ENUM_UINT8             enCnapType;                             /* 使能/禁止主叫名称显示 */
    VOS_UINT8                           aucReserved[6];

    AT_CBST_DATA_CFG_STRU               stCbstDataCfg;                          /* 承载(CBST)类型*/
    AT_CCUG_CFG_STRU                    stCcugCfg;                              /* 闭合用户群(CUG)参数 */
}AT_MODEM_SS_CTX_STRU;


typedef struct
{
    AT_CMGF_MSG_FORMAT_ENUM_U8          enCmgfMsgFormat;                        /* 短信格式 TXT or PDU */
    AT_CSDH_TYPE                        ucCsdhType;                             /* 文本模式下参数显示类型 */
    VOS_UINT8                           ucParaCmsr;                             /* 读取短信标记 */
    VOS_UINT8                           ucSmsAutoReply;                         /* 自动回复标志 */
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     enCsmsMsgVersion;                       /* 短信服务类型 */
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMsgMeStorageStatus;                   /* ME存储状态标志 */
    VOS_UINT8                           ucLocalStoreFlg;
    VOS_UINT8                           ucReserve2;

    AT_CNMI_TYPE_STRU                   stCnmiType;                             /* CNMI类型 */
    AT_CSCA_CSMP_INFO_STRU              stCscaCsmpInfo;                         /* 文本模式参数 */
    AT_MSG_CPMS_STRU                    stCpmsInfo;                             /* 短信存储器 */
    AT_SMS_MT_BUFFER_STRU               astSmsMtBuffer[AT_SMSMT_BUFFER_MAX];    /* 收到短信的缓存 */
    AT_SMT_BUFFER_STRU                  stSmtBuffer;                            /* 短信或状态报告不存储直接上报PDU缓存 */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    AT_CBM_BUFFER_STRU                  stCbmBuffer;
    TAF_CBA_CBMI_RANGE_LIST_STRU        stCbsDcssInfo;                          /* 语言相关信息直接保留在AT中 */
#endif
    AT_SMS_MT_CUSTOMIZE_STRU            stSmMeFullCustomize;                    /* 短信接收定制类型 */
}AT_MODEM_SMS_CTX_STRU;


typedef struct
{
    /* 控制上报相关 */
    AT_CERSSI_REPORT_TYPE_ENUM_UINT8    ucCerssiReportType;                     /* VOS_TRUE: ^CERSSI上报，VOS_FALSE: 不上报 */
    AT_CREG_TYPE                        ucCregType;                             /* VOS_TRUE: CS域服务状态上报，VOS_FALSE: 不上报 */
    AT_CGREG_TYPE                       ucCgregType;                            /* VOS_TRUE: PS域服务状态上报，VOS_FALSE: 不上报 */
    AT_COPS_FORMAT_TYPE                 ucCopsFormatType;                       /* COPS命令PLMN的格式 */

    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;                         /* CPOL命令PLMN的类型 */
    AT_COPS_FORMAT_TYPE                 ucCpolFormatType;                       /* CPOL命令PLMN的格式 */
    VOS_UINT8                           ucRoamFeature;                          /* 漫游特性是否使能 */
    VOS_UINT8                           ucSpnType;                              /* 记录AT^SPN查询的SPN类型 */

    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enCalculateAntennaLevel;                /* 磁滞处理后的天线格数 */
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM]; /* 记录3次天线格数 */
    VOS_UINT8                           ucCerssiMinTimerInterval;               /* 信号上报的最小间隔时间 */
    VOS_UINT8                           ucReserve1[3];

    NAS_MM_INFO_IND_STRU                stTimeInfo;                             /* 时间信息 */

#if(FEATURE_ON == FEATURE_LTE)
    AT_CEREG_TYPE_ENUM_UINT8            ucCeregType;                            /* VOS_TRUE: EPS域服务状态上报，VOS_FALSE: 不上报 */
    VOS_UINT8                           ucReserve2[7];
#endif

    AT_CSDF_CFG_STRU                    stCsdfCfg;

    AT_CGEREP_CFG_STRU                  stCgerepCfg;
    VOS_UINT32                          ulNwSecond;
    VOS_UINT8                           ucReserve3[4];

}AT_MODEM_NET_CTX_STRU;


typedef struct
{
    AT_CPOSR_FLG_ENUM_UNIT8             enCposrReport;                          /* +CPOSR命令主动上报控制，上电开机默认为不允许主动上报 */
    AT_XCPOSR_FLG_ENUM_UNIT8            enXcposrReport;                         /* +XCPOSR命令主动上报控制，上电开机默认为不允许主动上报 */
    AT_CMOLRE_TYPE_ENUM_UNIT8           enCmolreType;                           /* +CMOLRE命令错误码上报格式，默认为数字格式 */
    VOS_UINT8                           ucAtCgpsClockEnableFlag;                /* AT^CGPSCLOCK中第一个参数 */
    VOS_UINT8                           aucReserve[4];

    AT_XML_STRU                         stXml;                                  /* XML码流结构，存储AGPS下发的数据信息 */
}AT_MODEM_AGPS_CTX_STRU;


typedef struct
{
    AT_IMSA_BATTERY_STATUS_ENUM_UINT8   enTempBatteryInfo;
    AT_IMSA_BATTERY_STATUS_ENUM_UINT8   enCurrBatteryInfo;
    VOS_UINT8                           aucReserved[6];
}AT_MODEM_IMS_BATTERYINFO_STRU;


typedef struct
{
    AT_MODEM_IMS_BATTERYINFO_STRU       stBatteryInfo;
}AT_MODEM_IMS_CONTEXT_STRU;

/*********************************Modem CTX End*****************************/

/*********************************Client CTX Begin*****************************/

typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;                              /* 该端口属于哪个modem */
    VOS_UINT8                           ucReportFlg;                            /* 该端口是否允许主动上报，VOS_TRUE为允许，VOS_FALSE为不允许，默认允许 */
    VOS_UINT8                           aucRsv[1];
}AT_CLIENT_CONFIGURATION_STRU;
/*********************************Client CTX End*****************************/

/*********************************COMM CTX Begin*****************************/

typedef struct
{
    RCV_UL_DLCI_DATA_FUNC               pReadDataCB;                            /* 注册给MUX的接口，用于获取MUX发送给协议栈的AT码流 */

    AT_HSIC_REPORT_TYPE_ENUM_UINT32     enRptType;                              /* MUX通道都是复用HSIC通道。指定HSIC AT通道是否允许AT命令主动上报，
                                                                                   ^APRPTPORTSEL命令配套使用，上电时默认为AT_HSIC_REPORT_ON*/

    AT_CLIENT_ID_ENUM_UINT16            enAtClientId;                           /* MUX AT通道所对应的AT CLIENT ID*/

    AT_CLIENT_TAB_INDEX_UINT8           enAtClientTabIdx;                       /* MUX所使用的gastAtClientTab的index索引 */

    AT_USER_TYPE                        ucMuxUser;                              /* MUX AT通道所对应的AT USER type */

    AT_PORT_NO                          ucMuxPort;                              /* MUX AT通道所对应的AT PORT NO */

    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;                                 /* 目前MUX AT通道所用的通道ID*/

    VOS_UINT8                           aucRsv[6];
}AT_MUX_CLIENT_TAB_STRU;

typedef struct
{
    AT_MUX_CLIENT_TAB_STRU              astMuxClientTab[AT_MUX_AT_CHANNEL_MAX]; /* MUX 8个通道表 */
    VOS_UINT8                           ucMuxSupportFlg;                        /* 是否支持MUX特性 */
    VOS_UINT8                           aucRsv[7];
}AT_MUX_CTX_STRU;
/*********************************COMM CTX End*****************************/


typedef struct
{
    VOS_UINT32                          ulSarReduction;
    VOS_UINT8                           aucRsv[4];
}AT_MODEM_MT_INFO_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucFilterEnableFlg;                      /* 隐私过滤功能是否使能标识 */
    VOS_UINT8                           aucReserved[7];
}AT_MODEM_PRIVACY_FILTER_CTX_STRU;


typedef struct
{
    VOS_UINT8                               ucEnableFlg;                                 /* 开启CDMAMODEMSWITCH不重启特性 */
    VOS_UINT8                               aucReserved[7];                              /* 保留位 */
} AT_MODEM_CDMAMODEMSWITCH_CTX_STRU;

/*********************************Modem CTX End*****************************/



typedef struct
{
    VOS_SEM                             hResetSem;                              /* 二进制信号量，用于复位处理  */
    VOS_UINT32                          ulResetingFlag;                         /* 复位标志 */
    VOS_UINT32                          ulReserved;
}AT_RESET_CTX_STRU;


typedef struct
{
    AT_UART_FORMAT_ENUM_UINT8           enFormat;
    AT_UART_DATA_LEN_ENUM_UINT8         enDataBitLength;
    AT_UART_STOP_LEN_ENUM_UINT8         enStopBitLength;
    AT_UART_PARITY_LEN_ENUM_UINT8       enParityBitLength;

} AT_UART_FORMAT_PARAM_STRU;


typedef struct
{
    AT_UART_FORMAT_ENUM_UINT8           enFormat;
    AT_UART_PARITY_ENUM_UINT8           enParity;
    VOS_UINT8                           aucReserved[2];

} AT_UART_FRAME_STRU;


typedef struct
{
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate;
    AT_UART_FRAME_STRU                  stFrame;

} AT_UART_PHY_CFG_STRU;


typedef struct
{
    AT_UART_FC_DCE_BY_DTE_ENUM_UINT8    enDceByDte;
    AT_UART_FC_DTE_BY_DCE_ENUM_UINT8    enDteByDce;
    VOS_UINT8                           aucReserved[2];

} AT_UART_FLOW_CTRL_STRU;


typedef struct
{
    AT_UART_DCD_MODE_ENUM_UINT8         enDcdMode;
    AT_UART_DTR_MODE_ENUM_UINT8         enDtrMode;
    AT_UART_DSR_MODE_ENUM_UINT8         enDsrMode;
    VOS_UINT8                           aucReserved[1];

} AT_UART_LINE_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          ulSmsRiOnInterval;      /* 短信RI拉高持续时间(ms) */
    VOS_UINT32                          ulSmsRiOffInterval;     /* 短信RI拉低持续时间(ms) */

    VOS_UINT32                          ulVoiceRiOnInterval;    /* 语音RI拉高持续时间(ms) */
    VOS_UINT32                          ulVoiceRiOffInterval;   /* 语音RI拉低持续时间(ms) */
    VOS_UINT8                           ucVoiceRiCycleTimes;    /* 语音RI波形周期次数     */
    VOS_UINT8                           aucReserved[7];

} AT_UART_RI_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulRunFlg;           /* 标示是否有短信或语音呼叫 */
    AT_UART_RI_TYPE_ENUM_UINT32         enType;             /* RI 类型 */

    HTIMER                              hVoiceRiTmrHdl;     /* 语音RI定时器句柄 */
    AT_TIMER_STATUS_ENUM_UINT32         enVoiceRiTmrStatus; /* 语音RI定时器状态 */
    VOS_UINT32                          ulVoiceRiCycleCount;/* 语音上报周期计数 */
    AT_UART_RI_STATUS_ENUM_UINT8        aenVoiceRiStatus[MN_CALL_MAX_NUM + 1];
                                                            /* 语音RI状态(多个CALLID) */

    HTIMER                              hSmsRiTmrHdl;       /* 短信RI定时器句柄 */
    AT_TIMER_STATUS_ENUM_UINT32         enSmsRiTmrStatus;   /* 短信RI定时器状态 */
    VOS_UINT32                          ulSmsRiOutputCount; /* 短信RI输出计数 */

} AT_UART_RI_STATE_INFO_STRU;


typedef struct
{
    AT_UART_PHY_CFG_STRU                stPhyConfig;            /* UART 物理配置 */
    AT_UART_LINE_CTRL_STRU              stLineCtrl;             /* UART 管脚控制模式 */
    AT_UART_FLOW_CTRL_STRU              stFlowCtrl;             /* UART 流控模式 */
    AT_UART_RI_CFG_STRU                 stRiConfig;             /* UART RI 配置 */
    AT_UART_RI_STATE_INFO_STRU          stRiStateInfo;          /* UART RI 状态 */
    AT_UART_WM_LOW_FUNC                 pWmLowFunc;             /* UART TX低水线处理函数指针 */
    VOS_UINT32                          ulTxWmHighFlg;          /* UART TX高水线标识 */
    VOS_UINT8                           aucReserved[4];

} AT_UART_CTX_STRU;


typedef struct
{
    AT_PORT_BUFF_CFG_ENUM_UINT8         enSmsBuffCfg;
    VOS_UINT8                           ucNum;                                  /* 当前表中的个数 */
    VOS_UINT8                           aucRcv[2];
    VOS_UINT32                          ulUsedClientID[AT_MAX_CLIENT_NUM];      /* 已经使用的client ID记录 */
}AT_PORT_BUFF_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usCurrIdx;          /* 电话本读取当前索引 */
    VOS_UINT16                          usLastIdx;          /* 电话本读取目标索引 */
    VOS_UINT32                          ulSingleReadFlg;    /* 电话本读取单条标识 */
} AT_COMM_PB_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucClientId;
    VOS_UINT8                           ucSettingFlag;
    VOS_UINT8                           ucCurIdx;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT16                          usParaLen;
    VOS_UINT16                          usReserve;
    VOS_UINT8                          *pucData;
    HTIMER                              hAuthPubkeyProtectTimer;
} AT_AUTH_PUBKEYEX_CMD_PROC_CTX;


typedef struct
{
    VOS_UINT8                           ucNetWorkFlg;
    VOS_UINT8                           aucReserve[7];
    VOS_UINT8                           ucClientId;
    VOS_UINT8                           ucSettingFlag;
    VOS_UINT8                           ucLayer;
    VOS_UINT8                           ucCurIdx;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucHmacLen;
    VOS_UINT16                          usSimlockDataLen;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucHmac[AT_SET_SIMLOCK_DATA_HMAC_LEN];
    HTIMER                              hSimLockWriteExProtectTimer;
} AT_SIMLOCKDATAWRITEEX_CMD_PROC_CTX;


typedef struct
{
    VOS_UINT32                          ulReportedModemNum;
    VOS_UINT32                          ulResult;
} AT_VMSET_CMD_CTX_STRU;

typedef struct
{
    AT_AUTH_PUBKEYEX_CMD_PROC_CTX       stAuthPubkeyExCmdCtx;
    AT_VMSET_CMD_CTX_STRU               stVmSetCmdCtx;
    AT_SIMLOCKDATAWRITEEX_CMD_PROC_CTX  stSimLockWriteExCmdCtx;
} AT_CMD_PROC_CTX_STRU;


typedef struct
{
    VOS_SPINLOCK                        stSpinLock;
    VOS_UINT32                          ulMsgCount;
}AT_CMD_MSG_NUM_CTRL_STRU;


typedef struct
{
    VOS_UINT8                           ucSystemAppConfigAddr;                  /* 保存后台版本 */
    VOS_UINT8                           aucReserve[7];

    AT_MUX_CTX_STRU                     stMuxCtx;                               /* MUX AT通道上下文 */
    AT_COMM_PS_CTX_STRU                 stPsCtx;                                /* PS域相关的公共上下文 */
    AT_UART_CTX_STRU                    stUartCtx;                              /* UART相关上下文 */
    AT_PORT_BUFF_CFG_STRU               stPortBuffCfg;

    AT_COMM_PB_CTX_STRU                 stCommPbCtx;                            /* 电话本相关公共上下文 */

    AT_CMD_PROC_CTX_STRU                stCmdProcCtx;

    AT_CMD_MSG_NUM_CTRL_STRU            stMsgNumCtrlCtx;

    NAS_NVIM_CUSTOM_USIMM_CFG_STRU      stCustomUsimmCfg;
    VOS_UINT8                           aucRsv[4];
}AT_COMM_CTX_STRU;


typedef struct
{
    AT_USIM_INFO_CTX_STRU               stAtUsimInfoCtx;                      /* 卡状态 */
    AT_MODEM_SPT_CAP_STRU               stPlatformCapList;                      /* AT Modem配置模式 */
    AT_MODEM_CC_CTX_STRU                stCcCtx;                                /* 呼叫相关的上下文 */
    AT_MODEM_SS_CTX_STRU                stSsCtx;                                /* 补充业务相关的上下文 */
    AT_MODEM_SMS_CTX_STRU               stSmsCtx;                               /* 短信相关的上下文 */
    AT_MODEM_NET_CTX_STRU               stNetCtx;                               /* 网络相关的上下文 */
    AT_MODEM_AGPS_CTX_STRU              stAgpsCtx;                              /* AGPS相关的上下文*/
    AT_MODEM_PS_CTX_STRU                stPsCtx;                                /* PS相关的上下文 */
    AT_MODEM_MT_INFO_CTX_STRU           stMtInfoCtx;                            /* 终端信息的上下文 */
    AT_MODEM_IMS_CONTEXT_STRU           stAtImsCtx;                             /* IMS信息的上下文 */
    AT_MODEM_PRIVACY_FILTER_CTX_STRU    stFilterCtx;                            /* 隐私信息过滤的上下文 */
    AT_MODEM_CDMAMODEMSWITCH_CTX_STRU   stCdmaModemSwitchCtx;                   /* CdmaModemSwitch不重启特性上下文 */
}AT_MODEM_CTX_STRU;


typedef struct
{
    AT_CLIENT_CONFIGURATION_STRU        stClientConfiguration;                  /* 每个端口的配置信息 */
}AT_CLIENT_CTX_STRU;

/*********************************后续需要调整的*************************************/
/*********************************Other Begin*****************************/

enum  AT_E5_RIGHT_FLAG_ENUM
{
    AT_E5_RIGHT_FLAG_NO,
    AT_E5_RIGHT_FLAG_YES,
    AT_E5_RIGHT_FLAG_BUTT
} ;
typedef  VOS_UINT32  AT_E5_RIGHT_FLAG_ENUM_U32;

enum AT_RIGHT_OPEN_FLAG_ENUM
{
    AT_RIGHT_OPEN_FLAG_CLOSE,
    AT_RIGHT_OPEN_FLAG_OPEN,
    AT_RIGHT_OPEN_FLAG_BUTT
};
typedef VOS_UINT32 AT_RIGHT_OPEN_FLAG_ENUM_U32;

#define AT_RIGHT_PWD_LEN                (16)

typedef struct
{
    AT_RIGHT_OPEN_FLAG_ENUM_U32         enRightOpenFlg;
    VOS_INT8                            acPassword[AT_RIGHT_PWD_LEN];
}AT_RIGHT_OPEN_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           ucAbortEnableFlg;                               /* AT打断开关标志. VOS_TRUE: 使能; VOS_FALE: 未使能 */
    VOS_UINT8                           aucAbortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN+1];   /* 比NV中的结构过一个字节用于保证有字符串结束符 */
    VOS_UINT8                           aucAbortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN+1];
    VOS_UINT8                           ucAnyAbortFlg;
}AT_ABORT_CMD_PARA_STRU;



typedef struct
{
    VOS_UINT32                          ulAtSetTick[AT_MAX_CLIENT_NUM];
}AT_CMD_ABORT_TICK_INFO;

typedef struct
{
    AT_ABORT_CMD_PARA_STRU              stAtAbortCmdPara;
    AT_CMD_ABORT_TICK_INFO              stCmdAbortTick;
}AT_ABORT_CMD_CTX_STRU;



/* 拨号错误码上报 */
enum
{
    PPP_DIAL_ERR_CODE_DISABLE         = 0, /* 错误码不上报，*/
    PPP_DIAL_ERR_CODE_ENABLE          = 1, /* 错误码上报*/
    PPP_DIAL_ERR_CODE_BUTT
};
typedef VOS_UINT8   PPP_DIAL_ERR_CODE_ENUM;

typedef struct
{

    VOS_UINT8   ucGsmConnectRate;
    VOS_UINT8   ucGprsConnectRate;
    VOS_UINT8   ucEdgeConnectRate;
    VOS_UINT8   ucWcdmaConnectRate;
    VOS_UINT8   ucDpaConnectRate;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}AT_DIAL_CONNECT_DISPLAY_RATE_STRU;

/*****************************************************************************
 结构名    : AT_DOWNLINK_RATE_CATEGORY_STRU
 协议表格  : 无
 结构说明  : UE能力信息
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cWasRelIndicator;                       /* Access Stratum Release Indicator */
    VOS_UINT8                           ucWasCategory;
    VOS_UINT8                           ucGasMultislotClass33Flg;
    VOS_UINT8                           ucLteUeDlCategory;                      /* LTE下UE下行category */
    VOS_UINT8                           ucLteUeUlCategory;                      /* LTE下UE上行category */
    VOS_UINT8                           aucReserve[3];                          /* 保留位 */

} AT_DOWNLINK_RATE_CATEGORY_STRU;


typedef struct
{
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgID;
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgID;
} AT_TRACE_MSGID_TAB_STRU;

#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_RSRP_CFG_STRU;

typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_ECIO_CFG_STRU;

typedef struct
{
    TAF_INT16 ssLevel[4];
    TAF_INT16 ssValue[4];
}NVIM_RSCP_CFG_STRU;
#endif


typedef enum
{
    AT_SS_CUSTOMIZE_CCWA_QUERY,
    AT_SS_CUSTOMIZE_CLCK_QUERY,
    AT_SS_CUSTOMIZE_BUTT,
}AT_SS_CUSTOMIZE_TYPE;
typedef VOS_UINT8 AT_SS_CUSTOMIZE_TYPE_UINT8;

#define AT_SS_CUSTOMIZE_SERVICE_MASK          (0x1)


enum AT_ACCESS_STRATUM_REL_ENUM
{
    AT_ACCESS_STRATUM_REL8            = 0,
    AT_ACCESS_STRATUM_REL9            = 1,
    AT_ACCESS_STRATUM_REL10           = 2,
    AT_ACCESS_STRATUM_REL11           = 3,
    AT_ACCESS_STRATUM_REL12           = 4,
    AT_ACCESS_STRATUM_REL13           = 5,
    AT_ACCESS_STRATUM_REL14           = 6,
    AT_ACCESS_STRATUM_REL_SPARE1      = 7
};
typedef VOS_UINT8 AT_ACCESS_STRATUM_REL_ENUM_UINT8;

/*********************************Other End*****************************/


typedef struct
{
    VOS_UINT8                           ucModemId   : 2;
    VOS_UINT8                           ucReportFlg : 1;
    VOS_UINT8                           ucReserved  : 5;
}AT_CLINET_CONFIG_DESC_STRU;


typedef struct
{
    VOS_UINT32                          aulRptCfgBit32[3];
} AT_PORT_RPT_CFG_STRU;

enum TAF_NV_CLIENT_CFG_ENUM
{
    TAF_NV_CLIENT_CFG_PCUI              = 0,
    TAF_NV_CLIENT_CFG_CTRL              = 1,
    TAF_NV_CLIENT_CFG_MODEM             = 2,
    TAF_NV_CLIENT_CFG_NDIS              = 3,
    TAF_NV_CLIENT_CFG_UART              = 4,
    TAF_NV_CLIENT_CFG_SOCK              = 5,
    TAF_NV_CLIENT_CFG_APPSOCK           = 6,
    TAF_NV_CLIENT_CFG_HSIC1             = 7,
    TAF_NV_CLIENT_CFG_HSIC2             = 8,
    TAF_NV_CLIENT_CFG_HSIC3             = 9,
    TAF_NV_CLIENT_CFG_HSIC4             = 10,
    TAF_NV_CLIENT_CFG_MUX1              = 11,
    TAF_NV_CLIENT_CFG_MUX2              = 12,
    TAF_NV_CLIENT_CFG_MUX3              = 13,
    TAF_NV_CLIENT_CFG_MUX4              = 14,
    TAF_NV_CLIENT_CFG_MUX5              = 15,
    TAF_NV_CLIENT_CFG_MUX6              = 16,
    TAF_NV_CLIENT_CFG_MUX7              = 17,
    TAF_NV_CLIENT_CFG_MUX8              = 18,
    TAF_NV_CLIENT_CFG_APP               = 19,
    TAF_NV_CLIENT_CFG_APP1              = 20,
    TAF_NV_CLIENT_CFG_APP2              = 21,
    TAF_NV_CLIENT_CFG_APP3              = 22,
    TAF_NV_CLIENT_CFG_APP4              = 23,
    TAF_NV_CLIENT_CFG_APP5              = 24,
    TAF_NV_CLIENT_CFG_APP6              = 25,
    TAF_NV_CLIENT_CFG_APP7              = 26,
    TAF_NV_CLIENT_CFG_APP8              = 27,
    TAF_NV_CLIENT_CFG_APP9              = 28,
    TAF_NV_CLIENT_CFG_APP10             = 29,
    TAF_NV_CLIENT_CFG_APP11             = 30,
    TAF_NV_CLIENT_CFG_APP12             = 31,
    TAF_NV_CLIENT_CFG_APP13             = 32,
    TAF_NV_CLIENT_CFG_APP14             = 33,
    TAF_NV_CLIENT_CFG_APP15             = 34,
    TAF_NV_CLIENT_CFG_APP16             = 35,
    TAF_NV_CLIENT_CFG_APP17             = 36,
    TAF_NV_CLIENT_CFG_APP18             = 37,
    TAF_NV_CLIENT_CFG_APP19             = 38,
    TAF_NV_CLIENT_CFG_APP20             = 39,
    TAF_NV_CLIENT_CFG_APP21             = 40,
    TAF_NV_CLIENT_CFG_APP22             = 41,
    TAF_NV_CLIENT_CFG_APP23             = 42,
    TAF_NV_CLIENT_CFG_APP24             = 43,
    TAF_NV_CLIENT_CFG_APP25             = 44,
    TAF_NV_CLIENT_CFG_APP26             = 45,
    TAF_NV_CLIENT_CFG_HSIC_MODEM        = 46,
    TAF_NV_CLIENT_CFG_HSUART            = 47,
    TAF_NV_CLIENT_CFG_PCUI2             = 48,

    TAF_NV_CLIENT_CFG_APP27             = 49,
    TAF_NV_CLIENT_CFG_APP28             = 50,
    TAF_NV_CLIENT_CFG_APP29             = 51,
    TAF_NV_CLIENT_CFG_APP30             = 52,
    TAF_NV_CLIENT_CFG_APP31             = 53,
    TAF_NV_CLIENT_CFG_APP32             = 54,
    TAF_NV_CLIENT_CFG_APP33             = 55,
    TAF_NV_CLIENT_CFG_APP34             = 56,
    TAF_NV_CLIENT_CFG_APP35             = 57,
    TAF_NV_CLIENT_CFG_APP36             = 58,
    TAF_NV_CLIENT_CFG_APP37             = 59,
    TAF_NV_CLIENT_CFG_APP38             = 60,
    TAF_NV_CLIENT_CFG_APP39             = 61,
    TAF_NV_CLIENT_CFG_APP40             = 62,
    TAF_NV_CLIENT_CFG_APP41             = 63,
    TAF_NV_CLIENT_CFG_APP42             = 64,
    TAF_NV_CLIENT_CFG_APP43             = 65,
    TAF_NV_CLIENT_CFG_APP44             = 66,
    TAF_NV_CLIENT_CFG_APP45             = 67,
    TAF_NV_CLIENT_CFG_APP46             = 68,
    TAF_NV_CLIENT_CFG_APP47             = 69,
    TAF_NV_CLIENT_CFG_APP48             = 70,
    TAF_NV_CLIENT_CFG_APP49             = 71,
    TAF_NV_CLIENT_CFG_APP50             = 72,
    TAF_NV_CLIENT_CFG_APP51             = 73,
    TAF_NV_CLIENT_CFG_APP52             = 74,
    TAF_NV_CLIENT_CFG_MAX               = 96,           /* TAF_AT_NVIM_CLIENT_CFG_LEN */
};
typedef VOS_UINT16 TAF_NV_CLIENT_CFG_ENUM_UINT16;


typedef struct
{
    AT_CLIENT_ID_ENUM_UINT16            enClientId;
    TAF_NV_CLIENT_CFG_ENUM_UINT16       enNvIndex;
    VOS_UINT8                           aucPortName[AT_PORT_LEN_MAX];
    VOS_UINT32                          ulRptCfgBit32[3];
}AT_CLIENT_CFG_MAP_TAB_STRU;


#if ( VOS_WIN32 == VOS_OS_VER )

typedef struct
{
    VOS_UINT32                          ulFileNum;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId;
}AT_USIMM_FILE_NUM_TO_ID_STRU;
#endif


typedef struct
{
    AT_ACCESS_STRATUM_REL_ENUM_UINT8    enAccessStratumRel; /* 接入层的协议版本 */
    VOS_UINT8                           aucRsv[3];
}AT_ACCESS_STRATUM_RELEASE_STRU;


typedef struct
{
    VOS_UINT8                           ucGsmSupportFlg;
    VOS_UINT8                           ucWcdmaSupportFlg;
    VOS_UINT8                           ucLteSupportFlg;
    VOS_UINT8                           ucWs46No;
}AT_WS46_RAT_TRANSFORM_TBL_STRU;

typedef VOS_UINT32 (*AT_USER_RESEL_PROC_FUNC)(VOS_UINT8 ucIndex);


typedef struct
{
    VOS_UINT32                          ulUserResel;
    VOS_UINT32                          ulReserved;
    AT_USER_RESEL_PROC_FUNC             pfUserReselProc;
}AT_USER_RESEL_PROC_TBL_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern AT_COMM_CTX_STRU                        g_stAtCommCtx;

extern AT_MODEM_CTX_STRU                       g_astAtModemCtx[];

extern AT_CLIENT_CTX_STRU                      g_astAtClientCtx[];

/*********************************后续需要调整的*************************************/
extern AT_E5_RIGHT_FLAG_ENUM_U32               g_enATE5RightFlag;

extern VOS_INT8                                g_acATOpwordPwd[];

extern AT_RIGHT_OPEN_FLAG_STRU                 g_stAtRightOpenFlg;

extern VOS_INT8                                g_acATE5DissdPwd[];

extern VOS_UINT8                               gaucAtCmdNotSupportStr[];

extern PPP_DIAL_ERR_CODE_ENUM                  gucPppDialErrCodeRpt;

extern AT_DIAL_CONNECT_DISPLAY_RATE_STRU       g_stDialConnectDisplayRate;

extern AT_DOWNLINK_RATE_CATEGORY_STRU          g_stAtDlRateCategory;

extern VOS_UINT8                               ucAtS3;
extern VOS_UINT8                               ucAtS4;
extern VOS_UINT8                               ucAtS5;
extern VOS_UINT8                               ucAtS6;
extern VOS_UINT8                               ucAtS7;

extern AT_CMEE_TYPE                            gucAtCmeeType;                   /* 指示错误命令返回码类型 */

extern TAF_UINT32                              g_ulSTKFunctionFlag;



/*********************************SMS Begin*************************************/
extern MN_MSG_CLASS0_TAILOR_U8                 g_enClass0Tailor;
/*********************************SMS End*************************************/

/*********************************NET Begin*************************************/
extern VOS_UINT16                              g_usReportCregActParaFlg;

/*CREG/CGREG的<CI>域以4字节上报是否使能(VDF需求)*/
extern CREG_CGREG_CI_RPT_BYTE_ENUM             gucCiRptByte;

/*********************************NET End*************************************/
#if (FEATURE_ON == FEATURE_LTE)
extern NVIM_RSRP_CFG_STRU g_stRsrpCfg;
extern NVIM_RSCP_CFG_STRU g_stRscpCfg;
extern NVIM_ECIO_CFG_STRU g_stEcioCfg;

extern AT_ACCESS_STRATUM_RELEASE_STRU      g_stReleaseInfo;
#endif

extern AT_SS_CUSTOMIZE_PARA_STRU           g_stAtSsCustomizePara;

extern AT_CLIENT_CFG_MAP_TAB_STRU          g_astAtClientCfgMapTbl[];
extern const VOS_UINT8                     g_ucAtClientCfgMapTabLen;
extern VOS_UINT32                          g_ulCtzuFlag;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID AT_InitUsimStatus(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitPlatformRatList(MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_VOID AT_InitCommPbCtx(VOS_VOID);

extern VOS_VOID AT_InitCommCtx(VOS_VOID);
extern VOS_VOID AT_InitModemCcCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemSmsCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemNetCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemAgpsCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitModemImsCtx(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitCtx(VOS_VOID);
extern VOS_VOID AT_InitModemCtx(MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_VOID AT_InitClientConfiguration(VOS_VOID);
extern VOS_VOID AT_InitClientCtx(VOS_VOID);
MODEM_ID_ENUM_UINT16 AT_GetModemIDFromPid(VOS_UINT32 ulPid);
extern AT_USIM_INFO_CTX_STRU* AT_GetUsimInfoCtxFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern AT_MODEM_SPT_RAT_STRU* AT_GetSptRatFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern VOS_UINT8 AT_IsModemSupportRat(
           MODEM_ID_ENUM_UINT16                enModemId,
           TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat
       );

extern VOS_UINT8 AT_IsModemSupportUtralTDDRat(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern AT_COMM_CTX_STRU* AT_GetCommCtxAddr(VOS_VOID);
extern AT_COMM_PS_CTX_STRU* AT_GetCommPsCtxAddr(VOS_VOID);
#if (FEATURE_ON == FEATURE_IMS)
extern AT_IMS_EMC_RDP_STRU* AT_GetImsEmcRdpByClientId(VOS_UINT16 usClientId);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
extern VOS_UINT32 AT_GetPsIPv6IIDTestModeConfig(VOS_VOID);
extern AT_PS_IPV6_IID_MGR_INFO_STRU* AT_GetPsIPv6IIDMgrInfoByModemId(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitPsIPv6IIDMgrInfoByModemId(MODEM_ID_ENUM_UINT16 enModemId);
extern AT_PS_PDP_TYPE_CHG_MGR_INFO_STRU* AT_GetPsPdpTypeChgMgrInfoByModemId(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID AT_InitPsPdpTypeChgMgrInfoByModemId(MODEM_ID_ENUM_UINT16 enModemId);
#endif

extern AT_COMM_PB_CTX_STRU* AT_GetCommPbCtxAddr(VOS_VOID);

extern AT_CMD_MSG_NUM_CTRL_STRU* AT_GetMsgNumCtrlCtxAddr(VOS_VOID);

extern AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_CC_CTX_STRU* AT_GetModemCcCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern AT_MODEM_SS_CTX_STRU* AT_GetModemSsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
);
extern AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_SMS_CTX_STRU* AT_GetModemSmsCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_NET_CTX_STRU* AT_GetModemNetCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );
extern AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromModemId(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern AT_MODEM_AGPS_CTX_STRU* AT_GetModemAgpsCtxAddrFromClientId(
           VOS_UINT16                          usClientId
       );

extern AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern AT_MODEM_PS_CTX_STRU* AT_GetModemPsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
);

extern AT_MODEM_IMS_CONTEXT_STRU* AT_GetModemImsCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
extern AT_MODEM_IMS_CONTEXT_STRU* AT_GetModemImsCtxAddrFromClientId(
    VOS_UINT16                          usClientId
);

extern AT_CLIENT_CTX_STRU* AT_GetClientCtxAddr(
           AT_CLIENT_ID_ENUM_UINT16            enClientId
       );
extern AT_MODEM_CTX_STRU* AT_GetModemCtxAddr(
           MODEM_ID_ENUM_UINT16                enModemId
       );
extern VOS_UINT8* AT_GetSystemAppConfigAddr(VOS_VOID);
extern VOS_UINT32 AT_GetDestPid(
           MN_CLIENT_ID_T                      usClientId,
           VOS_UINT32                          ulRcvPid
       );



extern TAF_CS_CAUSE_ENUM_UINT32 AT_GetCsCallErrCause(
           VOS_UINT16                          usClientId
       );

extern AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID);
extern VOS_UINT8* AT_GetAbortRspStr(VOS_VOID);

extern VOS_UINT32 AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_TYPE_UINT8 enSsCustomizeType);

extern VOS_VOID AT_InitResetCtx(VOS_VOID);
extern AT_RESET_CTX_STRU* AT_GetResetCtxAddr(VOS_VOID);
extern VOS_SEM AT_GetResetSem(VOS_VOID);
extern VOS_UINT32 AT_GetResetFlag(VOS_VOID);
extern VOS_VOID AT_SetResetFlag(VOS_UINT32 ulFlag);

AT_MODEM_PRIVACY_FILTER_CTX_STRU* AT_GetModemPrivacyFilterCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

AT_MODEM_CDMAMODEMSWITCH_CTX_STRU* AT_GetModemCdmaModemSwitchCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern AT_MODEM_MT_INFO_CTX_STRU* AT_GetModemMtInfoCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

extern VOS_VOID AT_ClearSimLockWriteExCtx(VOS_VOID);
extern AT_SIMLOCKDATAWRITEEX_CMD_PROC_CTX* AT_GetSimLockWriteExCmdCtxAddr(VOS_VOID);

VOS_VOID AT_InitUartCtx(VOS_VOID);
AT_UART_CTX_STRU* AT_GetUartCtxAddr(VOS_VOID);
AT_UART_PHY_CFG_STRU* AT_GetUartPhyCfgInfo(VOS_VOID);
AT_UART_LINE_CTRL_STRU* AT_GetUartLineCtrlInfo(VOS_VOID);
AT_UART_FLOW_CTRL_STRU* AT_GetUartFlowCtrlInfo(VOS_VOID);
AT_UART_RI_CFG_STRU* AT_GetUartRiCfgInfo(VOS_VOID);
AT_UART_RI_STATE_INFO_STRU* AT_GetUartRiStateInfo(VOS_VOID);


VOS_VOID AT_InitTraceMsgTab(VOS_VOID);
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetResultMsgID(VOS_UINT8 ucIndex);
AT_INTER_MSG_ID_ENUM_UINT32 AT_GetCmdMsgID(VOS_UINT8 ucIndex);

VOS_VOID AT_ConfigTraceMsg(
    VOS_UINT8                           ucIndex,
    AT_INTER_MSG_ID_ENUM_UINT32         enCmdMsgId,
    AT_INTER_MSG_ID_ENUM_UINT32         enResultMsgId
);

VOS_VOID At_SetAtCmdAbortTickInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulTick
);
AT_CMD_ABORT_TICK_INFO* At_GetAtCmdAbortTickInfo(VOS_VOID);
VOS_UINT8 At_GetAtCmdAnyAbortFlg(VOS_VOID);
VOS_VOID At_SetAtCmdAnyAbortFlg(
    VOS_UINT8                           ucFlg
);

AT_PORT_BUFF_CFG_STRU* AT_GetPortBuffCfgInfo(VOS_VOID);

AT_PORT_BUFF_CFG_ENUM_UINT8  AT_GetPortBuffCfg(VOS_VOID);

VOS_VOID AT_InitPortBuffCfg(VOS_VOID);

VOS_VOID AT_AddUsedClientId2Tab(VOS_UINT16 usClientId);

VOS_VOID AT_RmUsedClientIdFromTab(VOS_UINT16 usClientId);

AT_CLIENT_CONFIGURATION_STRU* AT_GetClientConfig(
    AT_CLIENT_ID_ENUM_UINT16            enClientId
);
AT_CLIENT_CFG_MAP_TAB_STRU* AT_GetClientCfgMapTbl(VOS_UINT8 ucIndex);


VOS_UINT8 AT_GetPrivacyFilterEnableFlg(VOS_VOID);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT8* AT_GetModemCLModeCtxAddrFromModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
#endif
VOS_UINT8 AT_IsSupportReleaseRst(
    AT_ACCESS_STRATUM_REL_ENUM_UINT8    enReleaseType
);

VOS_VOID AT_InitReleaseInfo(VOS_VOID);

VOS_VOID AT_ClearAuthPubkeyCtx(VOS_VOID);
VOS_VOID AT_InitCmdProcCtx(VOS_VOID);
AT_AUTH_PUBKEYEX_CMD_PROC_CTX* AT_GetAuthPubkeyExCmdCtxAddr(VOS_VOID);
AT_CMD_PROC_CTX_STRU* AT_GetCmdProcCtxAddr(VOS_VOID);

AT_VMSET_CMD_CTX_STRU* AT_GetCmdVmsetCtxAddr(VOS_VOID);
VOS_VOID AT_InitVmSetCtx(VOS_VOID);

VOS_VOID AT_UpdateCallErrInfo(
    VOS_UINT16                          usClientId,
    TAF_CS_CAUSE_ENUM_UINT32            enCsErrCause,
    TAF_CALL_ERROR_INFO_TEXT_STRU      *pstErrInfoText
);

TAF_CALL_ERROR_INFO_TEXT_STRU * AT_GetCallErrInfoText(
    VOS_UINT16                          usClientId
);

VOS_UINT8 AT_GetCgpsCLockEnableFlgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_VOID AT_SetCgpsCLockEnableFlgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucEnableFLg
);

VOS_VOID AT_InitMsgNumCtrlCtx(VOS_VOID);
VOS_UINT8 At_GetGsmConnectRate(VOS_VOID);

VOS_UINT8 At_GetGprsConnectRate(VOS_VOID);

VOS_UINT8 At_GetEdgeConnectRate(VOS_VOID);

VOS_UINT8 At_GetWcdmaConnectRate(VOS_VOID);

VOS_UINT8 At_GetDpaConnectRate(VOS_VOID);

VOS_VOID AT_RcvTiSimlockWriteExExpired(REL_TIMER_MSG *pstTmrMsg);
VOS_VOID AT_RcvTiAuthPubkeyExpired(REL_TIMER_MSG *pstTmrMsg);


extern TAF_MMA_SIMSQ_STATE_ENUM_UINT32 At_GetSimsqStatus(MODEM_ID_ENUM_UINT16 enModemId);


extern VOS_VOID At_SetSimsqStatus(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MMA_SIMSQ_STATE_ENUM_UINT32     enSimsqStatus
);


extern VOS_UINT8 At_GetSimsqEnable(VOS_VOID);


extern VOS_VOID At_SetSimsqEnable(VOS_UINT8 ucSimsqEnable);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtCtx.h */

