/*
** Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V2_3/include/nic/hif_rx.h#1
*/

/*! \file   "hif_rx.h"
    \brief  Provide HIF RX Header Information between F/W and Driver

    N/A
*/

/*
** Log: hif_rx.h
**
** 03 29 2013 cp.wu
** [BORA00002227] [MT6630 Wi-Fi][Driver] Update for Makefile and HIFSYS modifications
** 1. remove unused HIF definitions
** 2. enable NDIS 5.1 build success
**
** 03 12 2013 tsaiyuan.hsu
** [BORA00002222] MT6630 unified MAC RXM
** remove hif_rx_hdr usage.
**
** 09 17 2012 cm.chang
** [BORA00002149] [MT6630 Wi-Fi] Initial software development
** Duplicate source from MT6620 v2.3 driver branch
** (Davinci label: MT6620_WIFI_Driver_V2_3_120913_1942_As_MT6630_Base)
 *
 * 09 01 2010 kevin.huang
 * NULL
 * Use LINK LIST operation to process SCAN result
 *
 * 07 16 2010 yarco.yang
 *
 * 1. Support BSS Absence/Presence Event
 * 2. Support STA change PS mode Event
 * 3. Support BMC forwarding for AP mode.
 *
 * 07 08 2010 cp.wu
 *
 * [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
 *
 * 06 14 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration
 * follow-ups for HIF_RX_HEADER_T update:
 * 1) add TCL
 * 2) add RCPI
 * 3) add ChannelNumber
 *
 * 06 11 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration
 * 1) migrate assoc.c.
 * 2) add ucTxSeqNum for tracking frames which needs TX-DONE awareness
 * 3) add configuration options for CNM_MEM and RSN modules
 * 4) add data path for management frames
 * 5) eliminate rPacketInfo of MSDU_INFO_T
 *
 * 06 09 2010 cp.wu
 * [WPD00003833][MT6620 and MT5931] Driver migration
 * add necessary changes to driver data paths.
 *
 * 06 06 2010 kevin.huang
 * [WPD00003832][MT6620 5931] Create driver base
 * [MT6620 5931] Create driver base
**  \main\maintrunk.MT6620WiFiDriver_Prj\10 2009-12-10 16:44:00 GMT mtk02752
**  code clean
**  \main\maintrunk.MT6620WiFiDriver_Prj\9 2009-12-09 13:59:20 GMT MTK02468
**  Added HIF_RX_HDR parsing macros
**  \main\maintrunk.MT6620WiFiDriver_Prj\8 2009-11-24 19:54:54 GMT mtk02752
**  adopt HIF_RX_HEADER_T in new data path
**  \main\maintrunk.MT6620WiFiDriver_Prj\7 2009-10-29 19:51:19 GMT mtk01084
**  modify FW/ driver interface
**  \main\maintrunk.MT6620WiFiDriver_Prj\6 2009-04-28 10:33:58 GMT mtk01461
**  Add define of HW_APPENED_LEN
**  \main\maintrunk.MT6620WiFiDriver_Prj\5 2009-04-01 10:51:02 GMT mtk01461
**  Rename ENUM_HIF_RX_PKT_TYPE_T
**  \main\maintrunk.MT6620WiFiDriver_Prj\4 2009-03-19 12:05:03 GMT mtk01426
**  Remove __KAL_ATTRIB_PACKED__ and add hifDataTypeCheck()
**  \main\maintrunk.MT6620WiFiDriver_Prj\3 2009-03-17 20:18:52 GMT mtk01426
**  Add comment to HIF_RX_HEADER_T
**  \main\maintrunk.MT6620WiFiDriver_Prj\2 2009-03-10 20:16:23 GMT mtk01426
**  Init for develop
**
*/

#ifndef _HIF_RX_H
#define _HIF_RX_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*! HIF_RX_HEADER_T */
/* DW 0, Byte 1 */
#define HIF_RX_HDR_PACKET_TYPE_MASK      BITS(0, 1)

/* DW 1, Byte 0 */
#define HIF_RX_HDR_HEADER_LEN            BITS(2, 7)
#define HIF_RX_HDR_HEADER_LEN_OFFSET     2
#define HIF_RX_HDR_HEADER_OFFSET_MASK    BITS(0, 1)

/* DW 1, Byte 1 */
#define HIF_RX_HDR_80211_HEADER_FORMAT   BIT(0)
#define HIF_RX_HDR_DO_REORDER            BIT(1)
#define HIF_RX_HDR_PAL                   BIT(2)
#define HIF_RX_HDR_TCL                   BIT(3)
#define HIF_RX_HDR_NETWORK_IDX_MASK      BITS(4, 7)
#define HIF_RX_HDR_NETWORK_IDX_OFFSET    4

/* DW 1, Byte 2, 3 */
#define HIF_RX_HDR_SEQ_NO_MASK           BITS(0, 11)
#define HIF_RX_HDR_TID_MASK              BITS(12, 14)
#define HIF_RX_HDR_TID_OFFSET            12
#define HIF_RX_HDR_BAR_FRAME             BIT(15)

#define HIF_RX_HDR_FLAG_AMP_WDS             BIT(0)
#define HIF_RX_HDR_FLAG_802_11_FORMAT       BIT(1)
#define HIF_RX_HDR_FLAG_BAR_FRAME           BIT(2)
#define HIF_RX_HDR_FLAG_DO_REORDERING       BIT(3)
#define HIF_RX_HDR_FLAG_CTRL_WARPPER_FRAME  BIT(4)

#define HIF_RX_HW_APPENDED_LEN              4

/* For DW 2, Byte 3 - ucHwChannelNum */
#define HW_CHNL_NUM_MAX_2G4                 14
#define HW_CHNL_NUM_MAX_4G_5G               (255 - HW_CHNL_NUM_MAX_2G4)

/*******************************************************************************
*                         D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
static __KAL_INLINE__ VOID hifDataTypeCheck(VOID);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

/* Kevin: we don't have to call following function to inspect the data structure.
 * It will check automatically while at compile time.
 * We'll need this for porting driver to different RTOS.
 */
static __KAL_INLINE__ VOID hifDataTypeCheck(VOID)
{
}

#endif
