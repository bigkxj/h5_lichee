/*
************************************************************************************************************************
*                                                         eGON
*                                         the Embedded GO-ON Bootloader System
*
*                             Copyright(C), 2006-2008, SoftWinners Microelectronic Co., Ltd.
*											       All Rights Reserved
*
* File Name   : boot0.h
*
* Author      : Gary.Wang
*
* Version     : 1.1.0
*
* Date        : 2009.05.21
*
* Description :
*
* Others      : None at present.
*
*
* History     :
*
*  <Author>        <time>       <version>      <description>
*
* Gary.Wang      2009.05.21       1.1.0        build the file
*
************************************************************************************************************************
*/
#ifndef  __boot0_v2_h
#define  __boot0_v2_h

#include "type_def.h"
#include "gpio.h"

#define SYS_PARA_LOG                    0x4d415244

#define SUNXI_DRAM_PARA_MAX             32

#define MAGIC_SIZE						8
#define BOOT0_MAGIC                     "eGON.BT0"
#define EXTEND_CONFIG_MAGIC				"Extend"
#define STAMP_VALUE                     0x5F0A6C39

#define BOOT_PUB_HEAD_VERSION           "1100"    // X.X.XX
#define EGON_VERSION                    "1100"    // X.X.XX

typedef struct standard_Boot_file_head
{
	__u32  jump_instruction;   // one intruction jumping to real code
	__u8   magic[8];           // ="eGON.BT0" or "eGON.BT1",  not C-style string.
	__u32  check_sum;          // generated by PC
	__u32  length;             // generated by PC
	__u32  pub_head_size;      // the size of boot_file_head_t
	__u8   pub_head_vsn[4];    // the version of boot_file_head_t
	__u32  ret_addr;           // the return value
	__u32  run_addr;           // run addr
	__u8   eGON_vsn[4];        // eGON version
	__u8   platform[8];        // platform information
}standard_boot_file_head_t;
/******************************************************************************/
/*                              file head of Boot0                            */
/******************************************************************************/
typedef struct _boot0_private_head_t
{
	__u32                       prvt_head_size;
	char                        prvt_head_vsn[4];       // the version of boot0_private_head_t
	unsigned int                dram_para[32];          // DRAM patameters for initialising dram. Original values is arbitrary,
	__s32						uart_port;              // UART控制器编号
	normal_gpio_cfg             uart_ctrl[2];           // UART控制器(调试打印口)数据信息
	__s32                       enable_jtag;            // 1 : enable,  0 : disable
    normal_gpio_cfg	            jtag_gpio[5];           // 保存JTAG的全部GPIO信息
    normal_gpio_cfg             storage_gpio[32];       // 存储设备 GPIO信息
    char                        storage_data[512 - sizeof(normal_gpio_cfg) * 32];      // 用户保留数据信息
    //boot_nand_connect_info_t    nand_connect_info;
}boot0_private_head_t;


typedef struct _boot0_file_head_t
{
	standard_boot_file_head_t   boot_head;
	boot0_private_head_t  		prvt_head;
}boot0_file_head_t;

/******************************************************************************/
/*                              extend head of Boot0                          */
/******************************************************************************/
typedef struct _boot0_extend_config
{
	__u8   						magic[MAGIC_SIZE];			//="Extend"
	__s32						if_reduce_power_waste;		//1: reduce power waste, 0: do nothing
	char 						reserved[500];
}boot0_extend_config;


/******************************************************************************/
/*                              extend head of fes 		                      */
/******************************************************************************/
typedef struct _fes_extend_config
{
	__u8   						magic[MAGIC_SIZE];			//="Extend"
	__s32						if_reduce_power_waste;		//1: reduce power waste, 0: do nothing
	char 						reserved[500];
}fes_extend_config;


#endif     //  ifndef __boot0_h

/* end of boot0.h */
