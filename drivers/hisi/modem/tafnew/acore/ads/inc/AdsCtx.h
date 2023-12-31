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

#ifndef __ADSCTX_H__
#define __ADSCTX_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "AdsInterface.h"
#include "AdsDeviceInterface.h"
#include "CdsAdsInterface.h"
#include "AdsNdInterface.h"
#include "AdsTimerMgmt.h"
#include "AdsLog.h"
#include "mdrv.h"
#include "NVIM_Interface.h"
#include "acore_nv_stru_gucnas.h"
#include "rnic_dev_def.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/pm_wakeup.h>
#include <linux/version.h>
#else
#include "Linuxstub.h"
#endif /* VOS_OS_VER == VOS_LINUX */

#if (defined(CONFIG_BALONG_SPE))
#include <linux/spe/spe_interface.h>
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */

#include <linux/of_platform.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* ADS实例个数与Modem个数保持一致 */
#define ADS_INSTANCE_MAX_NUM            (MODEM_ID_BUTT)

/* ADS实例索引值 */
#define ADS_INSTANCE_INDEX_0            (0)
#define ADS_INSTANCE_INDEX_1            (1)
#define ADS_INSTANCE_INDEX_2            (2)

/*上下缓存队列的最大值 */
#define ADS_RAB_NUM_MAX                 (11)

/* 当前到网络的定义是5到15, 因此有一个5的偏移量 */
#define ADS_RAB_ID_OFFSET               (5)

/* Rab Id的最小值 */
#define ADS_RAB_ID_MIN                  (5)

/* Rab Id的最大值 */
#define ADS_RAB_ID_MAX                  (15)

/* Rab Id的无效值 */
#define ADS_RAB_ID_INVALID              (0xFF)

/* 为了避免频繁触发IPF中断，需要采用攒包机制，攒包的最大个数 */
#define ADS_UL_SEND_DATA_NUM_THREDHOLD          (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum)

#define ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(n)   (g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum = (n))

#define ADS_UL_RX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen)
#define ADS_DL_TX_WAKE_LOCK_TMR_LEN     (g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen)

/* 申请的AD需要偏移14作为IPF RD的目的地址，14为MAC头的长度 */
#define ADS_DL_AD_DATA_PTR_OFFSET       (14)

/* 默认的优先级加权数 */
#define ADS_UL_DEFAULT_PRI_WEIGHTED_NUM (0x01)

#define ADS_PKT_ERR_RATE_MIN_THRESHOLD      (50)
#define ADS_PKT_ERR_RATE_MAX_THRESHOLD      (100)
#define ADS_PKT_ERR_RATE_DEFAULT_THRESHOLD  (95)

#define ADS_PKT_ERR_DETECT_MIN_DURATION     (1000)
#define ADS_PKT_ERR_DETECT_MAX_DURATION     (10000)
#define ADS_PKT_ERR_DETECT_DEFAULT_DURATION (2000)
#define ADS_PKT_ERR_DETECT_DEFAULT_DELTA    (1000)

#define ADS_IS_PKT_ERR_RATE_THRESHOLD_VALID(val) \
            (((val) >= ADS_PKT_ERR_RATE_MIN_THRESHOLD) \
             && ((val) <= ADS_PKT_ERR_RATE_MAX_THRESHOLD))

#define ADS_IS_PKT_ERR_DETECT_DURATION_VALID(val) \
            (((val) >= ADS_PKT_ERR_DETECT_MIN_DURATION) \
             && ((val) <= ADS_PKT_ERR_DETECT_MAX_DURATION))

#define ADS_CURRENT_TICK                (jiffies)
#define ADS_TIME_AFTER(a,b)             time_after((a),(b))
#define ADS_TIME_AFTER_EQ(a,b)          time_after_eq((a),(b))
#define ADS_TIME_IN_RANGE(a,b,c)        time_in_range((a),(b),(c))

/* ADS ADQ的个数 */
#define ADS_DL_ADQ_MAX_NUM              (2)

/*启动ADQ空保护定时器的阈值，当可配置AD数量大于该值时则启动保护定时器*/
#define ADS_IPF_DLAD_START_TMR_THRESHOLD (IPF_DLAD0_DESC_SIZE - 6)

/* ADS使用的SPE端口号 */
#define ADS_IPF_SPE_PORT_0              (SPE_PORT_MAX + 128)
#define ADS_IPF_SPE_PORT_1              (SPE_PORT_MAX + 129)

/* AD内存队列大小 */
#define ADS_IPF_AD0_MEM_BLK_NUM         (IPF_DLAD0_DESC_SIZE * 3)
#define ADS_IPF_AD1_MEM_BLK_NUM         (IPF_DLAD1_DESC_SIZE * 4)
#define ADS_IPF_AD_MEM_RESV_BLK_NUM     (IPF_DLAD1_DESC_SIZE * 2)

/* AD数据包的长度 */
#define ADS_IPF_AD0_MEM_BLK_SIZE        (448)
#define ADS_IPF_AD1_MEM_BLK_SIZE        (1536 + 14)

#define ADS_IPF_RD_BUFF_RECORD_NUM      (IPF_DLRD_DESC_SIZE * 2)
#define ADS_IPF_AD_BUFF_RECORD_NUM      (IPF_DLAD0_DESC_SIZE * 2)

/* ADS_UL_SendPacket和ADS_DL_RegDlDataCallback的rabid为扩展的rabid，
   高2bit作为MODEM ID，低6bit作为RAB ID。根据扩展的RABID获取MODEM ID */
#define ADS_GET_MODEMID_FROM_EXRABID(i) ((i >> 6) & 0x03)

#define ADS_GET_RABID_FROM_EXRABID(i)   (i & 0x3F)

#define ADS_BUILD_EXRABID(mid,rabid)    ((VOS_UINT8)((((mid) << 6) & 0xC0) | ((rabid) & 0x3F)))

#define ADS_BIT16_MASK(bit)             ((VOS_UINT16)(1 << (bit)))
#define ADS_BIT16_SET(val,bit)          ((val) | ADS_BIT16_MASK(bit))
#define ADS_BIT16_CLR(val,bit)          ((val) & ~ADS_BIT16_MASK(bit))
#define ADS_BIT16_IS_SET(val,bit)       ((val) & ADS_BIT16_MASK(bit))

/*******************************任务事件 Begin*******************************/

/* ADS上行任务事件 */
#define ADS_UL_EVENT_BASE               (0x00000000)
#define ADS_UL_EVENT_DATA_PROC          (ADS_UL_EVENT_BASE | 0x0001)

/* ADS下行任务事件 */
#define ADS_DL_EVENT_BASE               (0x00000000)
#define ADS_DL_EVENT_IPF_RD_INT         (ADS_DL_EVENT_BASE | 0x0001)
#define ADS_DL_EVENT_IPF_ADQ_EMPTY_INT  (ADS_DL_EVENT_BASE | 0x0002)
#define ADS_DL_EVENT_IPF_FILTER_DATA_PROC           (ADS_DL_EVENT_BASE | 0x0004)

/*******************************任务事件 End*******************************/

/*******************************速率统计 Begin*******************************/
/* 获取流量统计上下文 */
#define ADS_GET_DSFLOW_STATS_CTX_PTR()              (&(g_stAdsCtx.stDsFlowStatsCtx))

/* 设置当前上行速率 */
#define ADS_SET_CURRENT_UL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULCurDataRate = (n))

/* 设置当前下行速率 */
#define ADS_SET_CURRENT_DL_RATE(n)                  (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLCurDataRate = (n))

/* 统计上行周期性收到包的个数 */
#define ADS_RECV_UL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes += (n))

/* 统计下行周期性收到包的个数 */
#define ADS_RECV_DL_PERIOD_PKT_NUM(n)               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes += (n))

/* 获取上行周期性收到包的个数 */
#define ADS_GET_UL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes)

/* 获取下行周期性收到包的个数 */
#define ADS_GET_DL_PERIOD_PKT_NUM()                 (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes)

/* 将上行周期性收到包的个数清零 */
#define ADS_CLEAR_UL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stULDataStats.ulULPeriodSndBytes = 0)

/* 将下行周期性收到包的个数清零 */
#define ADS_CLEAR_DL_PERIOD_PKT_NUM()               (g_stAdsCtx.stDsFlowStatsCtx.stDLDataStats.ulDLPeriodRcvBytes = 0)

/*******************************速率统计 End*******************************/


/*******************************上行 Begin*******************************/
/* 获取ADS上行实体地址 */
#define ADS_UL_GET_CTX_PTR(i)                       (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx))

/* 获取上行队列指针 */
#define ADS_UL_GET_QUEUE_LINK_PTR(i, j)             (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)

/* 获取上行队列锁 */
#define ADS_UL_GET_QUEUE_LINK_SPINLOCK(i, j)        (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].stSpinLock))

/* 获取ADS上行BD配置参数地址 */
#define ADS_UL_GET_BD_CFG_PARA_PTR(index)           (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdCfgParam[index]))

/* 获取ADS上行BD缓存地址 */
#define ADS_UL_GET_BD_BUFF_PTR(index)               (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdBuff[index]))

/* 获取ADS上行发送保护定时器时长 */
#define ADS_UL_GET_PROTECT_TIMER_LEN()              (g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen)

/* 获取数据是否正在发送的标志位 */
#define ADS_UL_GET_SENDING_FLAG()                   (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg)

/* 设置数据是否正在发送的标志位 */
#define ADS_UL_SET_SENDING_FLAG(flg)                (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = flg)

/* 获取存储队列的索引 */
#define ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.aulPrioIndex[j])

/* 获取上行队列调度优先级*/
#define ADS_UL_GET_QUEUE_QCI(i, j)                  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].enPrio)

/* 获取上行队列信息 */
#define ADS_UL_GET_QUEUE_LINK_INFO(i, j)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].pstAdsUlLink)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* 获取IX OR HRPD的上行IPF过滤组标志 */
#define ADS_UL_GET_1X_OR_HRPD_UL_IPF_FLAG(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].uc1XorHrpdUlIpfFlag)
#endif

/* 获取上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum)

/* 设置上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(i, j, n)  (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum += n)

/* 清除上行队列一个加权数范围内记录的发送个数 */
#define ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum = 0)

/* 获取上行队列优先级的加权数 */
#define ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(i, j)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[ADS_UL_GET_QUEUE_QCI(i, j)])

/* 获取上行队列数据包的类型*/
#define ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) \
            (g_stAdsCtx.astAdsSpecCtx[InstanceIndex].stAdsUlCtx.astAdsUlQueue[RabId].enPktType)


/* 获取ADS上行发送保护定时器时长 */
#define ADS_UL_GET_STAT_TIMER_LEN()     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatTmrLen)

#define ADS_UL_ADD_STAT_PKT_NUM(n)      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum += (n))

#define ADS_UL_GET_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum)

#define ADS_UL_CLR_STAT_PKT_NUM()       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdStatInfo.ulStatPktNum = 0)

/* 获取上行赞包控制标记 */
#define ADS_UL_GET_THRESHOLD_ACTIVE_FLAG() \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulActiveFlag)

/* 获取上行赞包的jiffies的时间计数 */
#define ADS_UL_GET_JIFFIES_TMR_CNT()     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt)

/* 设置上行赞包的jiffies的时间计数 */
#define ADS_UL_SET_JIFFIES_TMR_CNT(n)     (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrCnt += (n))

/* 获取上行赞包的jiffies的超时长度 */
#define ADS_UL_GET_JIFFIES_EXP_TMR_LEN() (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.ulProtectTmrExpCnt)

/* 获取上行数据包水线等级 */
#define ADS_UL_GET_WATER_LEVEL_ONE()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel1)

#define ADS_UL_GET_WATER_LEVEL_TWO()    \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel2)

#define ADS_UL_GET_WATER_LEVEL_THREE()  \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel3)

#define ADS_UL_GET_WATER_LEVEL_FOUR()   \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stWaterMarkLevel.ulWaterLevel4)

/* 获取上行赞包门限 */
#define ADS_UL_DATA_THRESHOLD_ONE       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1)

#define ADS_UL_DATA_THRESHOLD_TWO       \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold2)

#define ADS_UL_DATA_THRESHOLD_THREE     \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold3)

#define ADS_UL_DATA_THRESHOLD_FOUR      \
            (g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold4)


/*******************************上行 End*******************************/

/* 上行IPF内存释放队列首地址 */
#define ADS_UL_IPF_SRCMEM_FREE_QUE()            (&(g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue))

/* IPF上行源内存释放QUEUE，定义限长为上行IPF BD描述符的2倍 */
#define ADS_UL_IPF_SRCMEM_FREE_QUE_SIZE         (2 * IPF_ULBD_DESC_SIZE)

/* 通过限制ADS上行队列长度，限制A核系统内存，队列限长初始化值 */
#if (defined(CONFIG_BALONG_SPE))
#define ADS_UL_MAX_QUEUE_LENGTH                 (448)
#else
#define ADS_UL_MAX_QUEUE_LENGTH                 (500)
#endif

/* 获取上行队列限长 */
#define ADS_UL_GET_MAX_QUEUE_LENGTH(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ulUlMaxQueueLength)

/* 获取ADS下行IPF AD BUFFER地址 */
#define ADS_DL_GET_IPF_AD_DESC_PTR(i, j)        (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdDesc[i][j]))
#define ADS_DL_GET_IPF_AD_RECORD_PTR(i)         (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdRecord[i]))

/*******************************下行 Begin*******************************/

/* 获取ADS下行实体地址 */
#define ADS_DL_GET_CTX_PTR(i)                   (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx))

/* 获取ADS下行IPF RD BUFFER地址 */
#define ADS_DL_GET_IPF_RD_DESC_PTR(index)       (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdDesc[index]))
#define ADS_DL_GET_IPF_RD_RECORD_PTR()          (&(g_stAdsCtx.stAdsIpfCtx.stIpfDlRdRecord))

/* 获取ADS下行RAB INFO地址 */
#define ADS_DL_GET_RAB_INFO_PTR(i, rabid)       (&(ADS_DL_GET_CTX_PTR(i)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET]))

/* 获取ADS下行RAB对应的数据包类型 */
#define ADS_DL_GET_PKT_TYPE(instance, rabid)    (ADS_DL_GET_CTX_PTR(instance)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET].enPktType)

/* 获取ADS下行数据回调函数指针 */
#define ADS_DL_GET_DATA_CALLBACK_FUNC(i,j)      (ADS_DL_GET_RAB_INFO_PTR(i,j)->pRcvDlDataFunc)
#define ADS_DL_GET_DATA_EXPARAM(i,j)            (ADS_DL_GET_RAB_INFO_PTR(i,j)->ulExParam)

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
/* 获取ADS下行RD最后一个数据处理回调函数指针 */
#define ADS_DL_GET_RD_LST_DATA_CALLBACK_FUNC(i,j)       (ADS_DL_GET_RAB_INFO_PTR(i,j)->pRcvRdLstDataFunc)
#endif

/* get/set the last data buff ptr */
#define ADS_DL_GET_LST_DATA_PTR(mid,rabid)          (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt)
#define ADS_DL_SET_LST_DATA_PTR(mid,rabid, psPara)  (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt = (psPara))

#define ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId) \
            (ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId)->pRcvDlFilterDataFunc)

/* 获取ADS下行流控参数信息地址 */
#define ADS_DL_GET_FC_ASSEM_INFO_PTR(i)         (&(ADS_DL_GET_CTX_PTR(i)->stFcAssemInfo))

/* 获取ADS下行流控组包参数调整回调函数指针 */
#define ADS_DL_GET_FC_ASSEM_TUNE_FUNC(i)        (ADS_DL_GET_FC_ASSEM_INFO_PTR(i)->pFcAssemTuneFunc)

#define ADS_DL_GET_PKT_ERR_FEEDBACK_CFG_PTR()   (&(g_stAdsCtx.stPktErrFeedbackCfg))
#define ADS_DL_GET_PKT_ERR_STATS_PTR(mid,rabid) (&(g_stAdsCtx.astPktErrStats[mid][rabid - ADS_RAB_ID_OFFSET]))

/* 获取ADS下行C核单独复位延时定时器时长 */
#define ADS_DL_GET_CCORE_RESET_DELAY_TIMER_LEN()    (g_stAdsCtx.stAdsIpfCtx.ulCCoreResetDelayTmrLen)


/*******************************下行 End*******************************/

/*******************************IPF Begin*******************************/
/* 获取IPF相关的上下文 */
#define ADS_GET_IPF_CTX_PTR()           (&(g_stAdsCtx.stAdsIpfCtx))

#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
#define ADS_GET_IPF_DEV()               (&(g_stAdsCtx.stAdsIpfCtx.stDev))
#else
#define ADS_GET_IPF_DEV()               (g_pstDmaDev)
#endif

#define ADS_IMM_MEM_CB(pstImmZc)        ((ADS_IMM_MEM_CB_STRU *)((pstImmZc)->cb))

#if (defined(CONFIG_BALONG_SPE))
#define ADS_GET_IPF_SPE_WPORT()         (g_stAdsCtx.stAdsIpfCtx.lSpeWPort)
#define ADS_GET_IPF_MEM_POOL_CFG_PTR()  (&(g_stAdsCtx.stAdsIpfCtx.stMemPoolCfg))
#define ADS_GET_IPF_MEM_POOL_PTR(id)    (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id]))
#define ADS_GET_IPF_MEM_QUE(id)         (&(g_stAdsCtx.stAdsIpfCtx.astMemPool[id].stQue))
#define ADS_SPE_MEM_CB(pstImmZc)        ((ADS_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))
#endif

/*lint -emacro({717}, ADS_IPF_SPE_MEM_MAP)*/
#define ADS_IPF_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapByDmaRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/*lint -emacro({717}, ADS_IPF_SPE_MEM_UNMAP)*/
#define ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 0);\
                }\
            } while(0)

/* 获取IPF模式 */
#define ADS_GET_IPF_MODE()              (g_stAdsCtx.stAdsIpfCtx.ucIpfMode)

#define ADS_GET_IPF_FILTER_QUE()        (&(g_stAdsCtx.stAdsIpfCtx.stIpfFilterQue))

/*******************************IPF End*******************************/

/* 检查MODEMID有效性 */
#define ADS_IS_MODEMID_VALID(mid) \
            ((mid) < ADS_INSTANCE_MAX_NUM)

/* 检查RABIID有效性 */
#define ADS_IS_RABID_VALID(rabid) \
            (((rabid) >= ADS_RAB_ID_MIN) && ((rabid) <= ADS_RAB_ID_MAX))

#define ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ucSendingFlg) \
            ((0 != ulAllUlQueueDataNum) \
             && (ulAllUlQueueDataNum >= ADS_UL_SEND_DATA_NUM_THREDHOLD) \
             && (VOS_FALSE == ucSendingFlg))

#if !defined(ADS_ARRAY_SIZE)
#define ADS_ARRAY_SIZE(a)               (sizeof((a)) / sizeof((a[0])))
#endif

#if (defined(LLT_OS_VER))
typedef unsigned long         SPINLOCK_STRU;
#else
typedef VOS_SPINLOCK          SPINLOCK_STRU;
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名称  : ADS_IPF_MEM_POOL_ID_ENUM
 枚举说明  : IPF 内存队列
*****************************************************************************/
enum ADS_IPF_MEM_POOL_ID_ENUM
{
    ADS_IPF_MEM_POOL_ID_AD0             = 0,
    ADS_IPF_MEM_POOL_ID_AD1,

    ADS_IPF_MEM_POOL_ID_BUTT
};
typedef VOS_UINT32 ADS_IPF_MEM_POOL_ID_ENUM_UINT32;


enum ADS_IPF_MODE_ENUM
{
    ADS_IPF_MODE_INT  = 0x00,                                                   /* 中断上下文 */
    ADS_IPF_MODE_THRD = 0x01,                                                   /* 线程上下文 */
    ADS_IPF_MODE_BUTT
};
typedef VOS_UINT8 ADS_IPF_MODE_ENUM_UINT8;

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

/*****************************************************************************
 结构名称  : ADS_SPE_MEM_CB_STRU
 结构说明  : IPF CB结构
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} ADS_SPE_MEM_CB_STRU;

/*****************************************************************************
 结构名称  : ADS_IMM_MEM_CB_STRU
 结构说明  : IMM CB结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulPriv[2];
    dma_addr_t                          ulDmaAddr;

} ADS_IMM_MEM_CB_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_BD_BUFF_STRU
 结构说明  : IPF BD Buffer结构
*****************************************************************************/
typedef struct
{
    IMM_ZC_STRU                        *pstPkt;

} ADS_IPF_BD_BUFF_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_RD_BUFF_STRU
 结构说明  : IPF RD Buffer结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSlice;
    VOS_UINT16                          usAttr;
    VOS_UINT16                          usPktLen;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_VOID                           *pOutPtr;

} ADS_IPF_RD_BUFF_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_RD_RECORD_STRU
 结构说明  : IPF RD 描述符记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           aucRsv[4];
    ADS_IPF_RD_BUFF_STRU                astRdBuff[ADS_IPF_RD_BUFF_RECORD_NUM];

} ADS_IPF_RD_RECORD_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_AD_BUFF_STRU
 结构说明  : IPF AD Buffer结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSlice;
#ifndef CONFIG_NEW_PLATFORM
    VOS_UINT32                          ulPhyAddr;
#else
    VOS_UINT8                           aucRsv[4];
    VOS_VOID                           *pulPhyAddr;
#endif
    IMM_ZC_STRU                        *pstImmZc;
} ADS_IPF_AD_BUFF_STRU;

/*****************************************************************************
 结构名称  : ADS_IPF_AD_RECORD_STRU
 结构说明  : IPF AD 描述符记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           aucRsv[4];
    ADS_IPF_AD_BUFF_STRU                astAdBuff[ADS_IPF_AD_BUFF_RECORD_NUM];
} ADS_IPF_AD_RECORD_STRU;


typedef struct
{
    IMM_ZC_HEAD_STRU                   *pstAdsUlLink;                           /* Rab Id对应的队列 */
    SPINLOCK_STRU                       stSpinLock;                             /* 队列锁 */
    VOS_UINT8                           ucIsQueueValid;                         /* 队列是否激活，VOS_TRUE:激活，VOS_FALSE:未激活 */
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;                                 /* 调度优先级 */
    VOS_UINT16                          usRecordNum;                            /* 记录在一个加权数范围内发送数据的个数 */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* 数据包类型 */
    VOS_UINT8                           uc1XorHrpdUlIpfFlag;                    /* 1X OR HRPD模式下的IPF过滤组 */
    VOS_UINT8                           aucRsv[2];

}ADS_UL_QUEUE_STRU;


typedef struct
{
    VOS_UINT32                          ulRabId;                                /* Rab Id */
    VOS_UINT32                          ulExParam;                              /* RMNET数据接收扩展参数 */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* 数据包类型 */
    VOS_UINT8                           aucRsv[7];                              /* 保留 */
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc;                         /* 对应的下行接收函数 */
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc;                   /* 对应的下行过滤接收函数 */
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    RCV_RD_LAST_DATA_FUNC               pRcvRdLstDataFunc;                      /* 下行RD最后一个报文的处理函数 */
#endif
    IMM_ZC_STRU                        *pstLstPkt;

}ADS_DL_RAB_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulEnableMask;
    VOS_UINT32              ulFcActiveFlg;
    unsigned long           ulTmrCnt;
    VOS_UINT32              ulRdCnt;
    VOS_UINT32              ulRateUpLev;
    VOS_UINT32              ulRateDownLev;
    VOS_UINT32              ulExpireTmrLen;
} ADS_DL_FC_ASSEM_STRU;


typedef struct
{
    ADS_DL_RAB_INFO_STRU                astAdsDlRabInfo[ADS_RAB_NUM_MAX];       /*下行Rab信息 */
    ADS_DL_FC_ASSEM_STRU                stFcAssemInfo;

} ADS_DL_CTX_STRU;


typedef struct
{
    ADS_UL_QUEUE_STRU                   astAdsUlQueue[ADS_RAB_ID_MAX + 1];      /* 上行队列管理，只用5-15 */
    ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU  stQueuePriNv;                           /* 从NV中读取的上行队列优先级对应的加权数 */
    VOS_UINT32                          aulPrioIndex[ADS_RAB_NUM_MAX];          /* 存储已排好优先级的上行队列的索引 */
    VOS_UINT32                          ulAdsUlCurIndex;                        /* 记录当前调度的队列 */
    VOS_UINT32                          ulUlMaxQueueLength;                     /* 上行队列限长 */
    VOS_UINT32                          ulReserved;
}ADS_UL_CTX_STRU;


typedef struct ADS_UL_DATA_STATS
{
    VOS_UINT32                          ulULCurDataRate;                        /* 当前上行速率，保存PDP激活后2秒的速率，去激活后清空 */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* 一个流量统计周期内发送的byte数 */
}ADS_UL_DATA_STATS_STRU;


typedef struct ADS_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* 当前下行速率，保存PDP激活后2秒的速率，去激活后清空 */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* 一个流量统计周期内收到的byte数 */
}ADS_DL_DATA_STATS_STRU;


typedef struct
{
    ADS_UL_DATA_STATS_STRU              stULDataStats;                          /* ADS上行数据统计 */
    ADS_DL_DATA_STATS_STRU              stDLDataStats;                          /* ADS下行数据统计 */
}ADS_STATS_INFO_CTX_STRU;


typedef struct
{
    VOS_UINT32                          ulStatTmrLen;                           /* 统计定时器长度 */
    VOS_UINT32                          ulStatPktNum;                           /* 在单位时间内上行统计包的个数 */
}ADS_UL_THRESHOLD_STAT_STRU;


typedef struct
{
    VOS_UINT32                          ulActiveFlag;                           /* 使能标识: 0表示去使能,1表示使能 */
    VOS_UINT32                          ulProtectTmrExpCnt;                     /* 保护定时器超时时长 */
    unsigned long                       ulProtectTmrCnt;                        /* 保护定时器的计数 */
    ADS_UL_WATER_MARK_LEVEL_STRU        stWaterMarkLevel;                       /* 动态水线值 */
    ADS_UL_THRESHOLD_LEVEL_STRU         stThresholdLevel;                       /* 动态赞包门限值 */
    ADS_UL_THRESHOLD_STAT_STRU          stThresholdStatInfo;                    /* 赞包状态统计 */
}ADS_UL_DYNAMIC_ASSEM_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usBlkNum;
    VOS_UINT16                          usBlkSize;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];

} ADS_IPF_MEM_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulEnable;
    VOS_UINT8                           aucReserved[4];
    ADS_IPF_MEM_CFG_STRU                astMemCfg[ADS_IPF_MEM_POOL_ID_BUTT];

} ADS_IPF_MEM_POOL_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usBlkSize;
    VOS_UINT16                          usBlkNum;
    VOS_UINT8                           ucPort;
    VOS_UINT8                           aucReserved[3];
    IMM_ZC_HEAD_STRU                    stQue;

} ADS_IPF_MEM_POOL_STRU;


typedef struct
{
    IPF_CONFIG_ULPARAM_S                astIpfUlBdCfgParam[IPF_ULBD_DESC_SIZE]; /* 上行BD DESC */
    IPF_RD_DESC_S                       astIpfDlRdDesc[IPF_DLRD_DESC_SIZE];     /* 下行RD DESC */
    ADS_IPF_RD_RECORD_STRU              stIpfDlRdRecord;
    IPF_AD_DESC_S                       astIpfDlAdDesc[ADS_DL_ADQ_MAX_NUM][IPF_DLAD0_DESC_SIZE];   /* 下行AD DESC */
    ADS_IPF_AD_RECORD_STRU              astIpfDlAdRecord[ADS_DL_ADQ_MAX_NUM];
    ADS_IPF_BD_BUFF_STRU                astIpfUlBdBuff[IPF_ULBD_DESC_SIZE];     /* 上行BD */
    IMM_ZC_HEAD_STRU                    stUlSrcMemFreeQue;                      /* IPF上行内存释放BUFF */
    ADS_UL_DYNAMIC_ASSEM_INFO_STRU      stUlAssemParmInfo;                      /* 上行动态组包信息 */
    VOS_UINT32                          ulThredHoldNum;                         /* 上行赞包门限值 */
    VOS_UINT32                          ulProtectTmrLen;
    VOS_UINT8                           ucSendingFlg;                           /* 正在发送标志 */
    VOS_UINT8                           ucIpfMode;                              /* IPF处理ADS下行数据的模式, 0: 中断上下文(默认)，1：线程上下文 */
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulWakeLockEnable;                       /* wake lock 使能标识 */

    struct wakeup_source                stUlBdWakeLock;                         /* wake lock BD */
    struct wakeup_source                stDlRdWakeLock;                         /* wake lock RD */

    struct wakeup_source                stRxWakeLock;                           /* wake lock RX */
    struct wakeup_source                stTxWakeLock;                           /* wake lock TX */

    VOS_UINT32                          ulUlBdWakeLockCnt;                      /* wake lock BD 计数 */
    VOS_UINT32                          ulDlRdWakeLockCnt;                      /* wake lock BD 计数 */

    VOS_UINT32                          ulRxWakeLockTimeout;                    /* wake lock RX 超时时间 */
    VOS_UINT32                          ulTxWakeLockTimeout;                    /* wake lock TX 超时时间 */

    VOS_UINT32                          ulTxWakeLockTmrLen;                     /* wake lock TX 超时配置 */
    VOS_UINT32                          ulRxWakeLockTmrLen;                     /* wake lock RX 超时配置 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
    struct device                       stDev;
#endif
#if (defined(CONFIG_BALONG_SPE))
    VOS_INT32                           lSpeWPort;
    VOS_UINT8                           aucReserved[4];
    ADS_IPF_MEM_POOL_CFG_STRU           stMemPoolCfg;
    ADS_IPF_MEM_POOL_STRU               astMemPool[ADS_IPF_MEM_POOL_ID_BUTT];
#endif
    IMM_ZC_HEAD_STRU                    stIpfFilterQue;

    SPINLOCK_STRU                       stAdqSpinLock;                          /* 下行AD描述符自旋锁 */

    VOS_UINT32                          ulCCoreResetDelayTmrLen;
    VOS_UINT8                           aucReserved1[4];

}ADS_IPF_CTX_STRU;


typedef struct
{
    ADS_UL_CTX_STRU                     stAdsUlCtx;                             /* 上行上下文 */
    ADS_DL_CTX_STRU                     stAdsDlCtx;                             /* 下行上下文 */

} ADS_SPEC_CTX_STRU;

/*****************************************************************************
 结构名称  : ADS_BEARER_PACKET_ERROR_STATS_STRU
 结构说明  : 承载数据错误统计结构
*****************************************************************************/
typedef struct
{
    VOS_ULONG                           ulMinDetectExpires;                     /* 最小超时时间 */
    VOS_ULONG                           ulMaxDetectExpires;                     /* 最大超时时间 */

    VOS_UINT32                          ulErrorPktNum;                          /* 错包数量 */
    VOS_UINT32                          ulTotalPktNum;                          /* 数据总量 */

} ADS_BEARER_PACKET_ERROR_STATS_STRU;

/*****************************************************************************
 结构名称  : ADS_PACKET_ERROR_FEEDBACK_CFG_STRU
 结构说明  : 承载数据错误反馈配置结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnabled;                              /* 使能标识 */
    VOS_UINT32                          ulPktErrRateThres;                      /* 反馈门限(错包率) */
    VOS_ULONG                           ulMinDetectDuration;                    /* 最小检测持续时间(TICK) */
    VOS_ULONG                           ulMaxDetectDuration;                    /* 最大检测持续时间(TICK) */

} ADS_PACKET_ERROR_FEEDBACK_CFG_STRU;


typedef struct
{
    ADS_SPEC_CTX_STRU                   astAdsSpecCtx[ADS_INSTANCE_MAX_NUM];    /* 每个实例专有的上下文 */
    ADS_STATS_INFO_CTX_STRU             stDsFlowStatsCtx;                       /* 流量统计 */
    ADS_IPF_CTX_STRU                    stAdsIpfCtx;                            /* 与IPF相关的上下文 */
    ADS_TIMER_CTX_STRU                  astAdsTiCtx[ADS_MAX_TIMER_NUM];         /* 定时器上下文 */
    VOS_UINT32                          ulAdsCurInstanceIndex;                  /* 当前实例的index */
    VOS_UINT8                           ucUlResetFlag;
    VOS_UINT8                           aucRsv[3];
    VOS_SEM                             hULResetSem;                            /* 二进制信号量，用于UL复位处理  */
    VOS_SEM                             hDLResetSem;                            /* 二进制信号量，用于DL复位处理  */

    ADS_PACKET_ERROR_FEEDBACK_CFG_STRU  stPktErrFeedbackCfg;
    ADS_BEARER_PACKET_ERROR_STATS_STRU  astPktErrStats[ADS_INSTANCE_MAX_NUM][ADS_RAB_NUM_MAX];

} ADS_CTX_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

extern VOS_UINT32                       g_ulAdsULTaskId;
extern VOS_UINT32                       g_ulAdsDLTaskId;
extern VOS_UINT32                       g_ulAdsULTaskReadyFlag;
extern VOS_UINT32                       g_ulAdsDLTaskReadyFlag;
extern ADS_CTX_STRU                     g_stAdsCtx;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
extern struct device                   *g_pstDmaDev;
#endif

/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 ADS_UL_IsAllRabNotSndPermitFlg(VOS_VOID);
VOS_UINT32 ADS_UL_GetSpecInstanceSndPermitFlg(VOS_UINT32 ulInstanceIndex);
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent);
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT32 ulInstanceIndex);
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID);
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT32 ulInstanceIndex);
VOS_VOID ADS_InitCtx(VOS_VOID);
VOS_VOID ADS_InitDlCtx(VOS_UINT32 ulInstance);
VOS_VOID ADS_InitIpfCtx(VOS_VOID);
VOS_VOID ADS_InitSpecCtx(VOS_VOID);
VOS_VOID ADS_InitStatsInfoCtx(VOS_VOID);
VOS_VOID ADS_InitTiCtx(VOS_VOID);
VOS_VOID ADS_InitUlCtx(VOS_UINT32 ulInstanceIndex);
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT32 ulInstanceIndex);
VOS_VOID ADS_UL_ClearQueue(
    IMM_ZC_HEAD_STRU                    *pstQueue
);
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulRabId,
    ADS_QCI_TYPE_ENUM_UINT8              enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8      enPdpType,
    VOS_UINT8                            uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulRabId
);
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID);
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulRabId
);
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT32 ucInstanceIndex);
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT32                          ulInstance,
    IMM_ZC_STRU                        *pstData,
    VOS_UINT32                          ulRabId
);
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulRabId
);
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulIndex
);
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen);
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT32                          ulInstanceIndex,
    VOS_UINT32                          ulRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType,
    VOS_UINT8                           uc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT32                           ulInstanceIndex,
    VOS_UINT32                           ulRabId
);
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
           VOS_UINT32                           ulInstanceIndex,
           ADS_QCI_TYPE_ENUM_UINT8              enPrio,
           VOS_UINT32                           ulRabId
);
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID);

VOS_UINT32 ADS_UL_EnableRxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_UL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_UL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_UL_WakeUnLock(VOS_VOID);
VOS_UINT32 ADS_DL_EnableTxWakeLockTimeout(VOS_UINT32 ulValue);
VOS_UINT32 ADS_DL_WakeLockTimeout(VOS_VOID);
VOS_UINT32 ADS_DL_WakeLock(VOS_VOID);
VOS_UINT32 ADS_DL_WakeUnLock(VOS_VOID);

VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID);
VOS_SEM ADS_GetULResetSem(VOS_VOID);
VOS_SEM ADS_GetDLResetSem(VOS_VOID);
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID);
VOS_VOID ADS_ResetSpecUlCtx(VOS_UINT32 ulInstance);
VOS_VOID ADS_ResetUlCtx(VOS_VOID);
VOS_VOID ADS_ResetSpecDlCtx(VOS_UINT32 ulInstance);
VOS_VOID ADS_ResetDlCtx(VOS_VOID);
VOS_VOID ADS_ResetIpfCtx(VOS_VOID);

VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_VOID);

VOS_UINT8 ADS_GetUlResetFlag(VOS_VOID);
VOS_VOID  ADS_SetUlResetFlag(VOS_UINT8 ucFlag);

VOS_UINT32 ADS_IPF_IsSpeMem(IMM_ZC_STRU *pstImmZc);
IMM_ZC_STRU* ADS_IPF_AllocMem(VOS_UINT32 ulPoolId, VOS_UINT32 ulLen, VOS_UINT32 ulReserveLen);
dma_addr_t ADS_IPF_GetMemDma(IMM_ZC_STRU *pstImmZc);
VOS_VOID ADS_IPF_SetMemDma(IMM_ZC_STRU *pstImmZc, dma_addr_t ulDmaAddr);
VOS_VOID ADS_IPF_MemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemMapByDmaRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);
VOS_VOID ADS_IPF_MemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen, VOS_UINT8 ucIsIn);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID ADS_IPF_InitMemPoolCfg(VOS_VOID);
VOS_VOID ADS_IPF_CreateMemPool(VOS_VOID);
#endif

VOS_VOID ADS_DL_ProcIpfFilterQue(VOS_VOID);
VOS_VOID ADS_DL_ProcIpfFilterData(
    IMM_ZC_STRU                        *pstImmZc
);


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
VOS_INT32 ADS_PlatDevProbe(struct platform_device *pstDev);
VOS_INT32 ADS_PlatDevRemove(struct platform_device *pstDev);
VOS_INT32 __init ADS_PlatDevInit(void);
VOS_VOID __exit ADS_PlatDevExit(void);
#endif

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

#endif


