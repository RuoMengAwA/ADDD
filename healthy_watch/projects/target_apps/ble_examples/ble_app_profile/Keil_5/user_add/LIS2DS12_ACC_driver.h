/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
*
* File Name          : LIS2DS12_ACC_driver.h
* Author             : MSH Application Team
* Version            : v1.4
* Date               : 04/27/2015
* Description        : LIS2DS12 ACC driver header file
*
* Reviewed by: Armando Visconti
*-------------------------------------------------------------------------------
*
*
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIS2DS12_ACC_DRIVER__H
#define __LIS2DS12_ACC_DRIVER__H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

//these could change accordingly with the architecture

#ifndef __ARCHDEP__TYPES
#define __ARCHDEP__TYPES

typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef unsigned int u32_t;
typedef int i32_t;
typedef short int i16_t;
typedef signed char i8_t;

#endif /*__ARCHDEP__TYPES*/

/* Exported common structure --------------------------------------------------------*/

#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef union{
	i16_t i16bit[3];
	u8_t u8bit[6];
} Type3Axis16bit_U;	

typedef union{
	i16_t i16bit;
	u8_t u8bit[2];
} Type1Axis16bit_U;

typedef union{
	i32_t i32bit;
	u8_t u8bit[4];
} Type1Axis32bit_U;

typedef enum {
  MEMS_SUCCESS				=		0x01,
  MEMS_ERROR				=		0x00	
} status_t;

#endif /*__SHARED__TYPES*/

/* Exported macro ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/************** I2C Address *****************/

#define LIS2DS12_ACC_I2C_ADDRESS         0x3A

/************** Who am I  *******************/

#define LIS2DS12_ACC_WHO_AM_I         0x43

/* Private Function Prototype -------------------------------------------------------*/

u8_t LIS2DS12_ACC_ReadReg(u8_t Reg, u8_t* Data);
u8_t LIS2DS12_ACC_WriteReg(u8_t Reg, u8_t Data); 
void LIS2DS12_ACC_SwapHighLowByte(u8_t *bufferToSwap, u8_t numberOfByte, u8_t dimension); 


/************** Device Register  *******************/
#define LIS2DS12_ACC_SENSORHUB_OUT1  	0X06
#define LIS2DS12_ACC_SENSORHUB_OUT2  	0X07
#define LIS2DS12_ACC_SENSORHUB_OUT3  	0X08
#define LIS2DS12_ACC_SENSORHUB_OUT4  	0X09
#define LIS2DS12_ACC_SENSORHUB_OUT5  	0X0A
#define LIS2DS12_ACC_SENSORHUB_OUT6  	0X0B
#define LIS2DS12_ACC_MODULE_8BIT  	0X0C
#define LIS2DS12_ACC_WHO_AM_I_REG  	0X0F
#define LIS2DS12_ACC_CTRL1  	0X20
#define LIS2DS12_ACC_CTRL2  	0X21
#define LIS2DS12_ACC_CTRL3  	0X22
#define LIS2DS12_ACC_CTRL4  	0X23
#define LIS2DS12_ACC_CTRL5  	0X24
#define LIS2DS12_ACC_FIFO_CTRL  	0X25
#define LIS2DS12_ACC_OUT_T  	0X26
#define LIS2DS12_ACC_STATUS  	0X27
#define LIS2DS12_ACC_OUT_X_L  	0X28
#define LIS2DS12_ACC_OUT_X_H  	0X29
#define LIS2DS12_ACC_OUT_Y_L  	0X2A
#define LIS2DS12_ACC_OUT_Y_H  	0X2B
#define LIS2DS12_ACC_OUT_Z_L  	0X2C
#define LIS2DS12_ACC_OUT_Z_H  	0X2D
#define LIS2DS12_ACC_FIFO_THS  	0X2E
#define LIS2DS12_ACC_FIFO_SRC  	0X2F
#define LIS2DS12_ACC_FIFO_SAMPLES  	0X30
#define LIS2DS12_ACC_TAP_6D_THS  	0X31
#define LIS2DS12_ACC_INT_DUR  	0X32
#define LIS2DS12_ACC_WAKE_UP_THS  	0X33
#define LIS2DS12_ACC_WAKE_UP_DUR  	0X34
#define LIS2DS12_ACC_FREE_FALL  	0X35
#define LIS2DS12_ACC_STATUS_DUP  	0X36
#define LIS2DS12_ACC_WAKE_UP_SRC  	0X37
#define LIS2DS12_ACC_TAP_SRC  	0X38
#define LIS2DS12_ACC_6D_SRC  	0X39
#define LIS2DS12_ACC_STEP_C_MINTHS  	0X3A
#define LIS2DS12_ACC_STEP_C_L  	0X3B
#define LIS2DS12_ACC_STEP_C_H  	0X3C
#define LIS2DS12_ACC_FUNC_CK_GATE  	0X3D
#define LIS2DS12_ACC_FUNC_SRC  	0X3E
#define LIS2DS12_ACC_FUNC_CTRL  	0X3F

/*******************************************************************************
* Register      : MODULE_8BIT
* Address       : 0X0C
* Bit Group Name: MODULE8_BIT
* Permission    : RO
*******************************************************************************/
#define  	LIS2DS12_ACC_MODULE8_BIT_MASK  	0xFF
#define  	LIS2DS12_ACC_MODULE8_BIT_POSITION  	0
status_t LIS2DS12_ACC_R_MODULE8_BIT(u8_t *value);

/*******************************************************************************
* Register      : WHO_AM_I_REG
* Address       : 0X0F
* Bit Group Name: WHO_AM_I_BIT
* Permission    : RO
*******************************************************************************/
#define  	LIS2DS12_ACC_WHO_AM_I_BIT_MASK  	0xFF
#define  	LIS2DS12_ACC_WHO_AM_I_BIT_POSITION  	0
status_t LIS2DS12_ACC_R_WHO_AM_I_BIT(u8_t *value);

/*******************************************************************************
* Register      : CTRL1
* Address       : 0X20
* Bit Group Name: BDU
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_BDU_OFF 		 =0x00,
  	LIS2DS12_ACC_BDU_ON 		 =0x01,
} LIS2DS12_ACC_BDU_t;

#define  	LIS2DS12_ACC_BDU_MASK  	0x01
status_t  LIS2DS12_ACC_W_BDU(LIS2DS12_ACC_BDU_t newValue);
status_t LIS2DS12_ACC_R_BDU(LIS2DS12_ACC_BDU_t *value);

/*******************************************************************************
* Register      : CTRL1
* Address       : 0X20
* Bit Group Name: HF_ODR
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_HF_ODR_OFF 		 =0x00,
  	LIS2DS12_ACC_HF_ODR_ON 		 =0x02,
} LIS2DS12_ACC_HF_ODR_t;

#define  	LIS2DS12_ACC_HF_ODR_MASK  	0x02
status_t  LIS2DS12_ACC_W_HF_ODR(LIS2DS12_ACC_HF_ODR_t newValue);
status_t LIS2DS12_ACC_R_HF_ODR(LIS2DS12_ACC_HF_ODR_t *value);

/*******************************************************************************
* Register      : CTRL1
* Address       : 0X20
* Bit Group Name: FS
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FS_2G 		 =0x00,
  	LIS2DS12_ACC_FS_16G 		 =0x04,
  	LIS2DS12_ACC_FS_4G 		 =0x08,
  	LIS2DS12_ACC_FS_8G 		 =0x0C,
} LIS2DS12_ACC_FS_t;

#define  	LIS2DS12_ACC_FS_MASK  	0x0C
status_t  LIS2DS12_ACC_W_FullScale(LIS2DS12_ACC_FS_t newValue);
status_t LIS2DS12_ACC_R_FullScale(LIS2DS12_ACC_FS_t *value);

/*******************************************************************************
* Register      : CTRL1
* Address       : 0X20
* Bit Group Name: ODR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LIS2DS12_ACC_ODR_PowerDown 		 =0x00,
	LIS2DS12_ACC_ODR_HR_14bit_12_5Hz	=0x10,
	LIS2DS12_ACC_ODR_HR_14bit_25Hz		=0x20,
	LIS2DS12_ACC_ODR_HR_50Hz		=0x30,
	LIS2DS12_ACC_ODR_HR_14bit_100Hz		=0x40,
	LIS2DS12_ACC_ODR_HR_14bit_200Hz		=0x50, /* if HF is on it is HF_12b@1600Hz*/
	LIS2DS12_ACC_ODR_HR_14bit_400Hz		=0x60, /* if HF is on it is HF_12b@3200Hz*/
	LIS2DS12_ACC_ODR_HR_14bit_800Hz		=0x70, /* if HF is on it is HF_12b@6400Hz*/
	LIS2DS12_ACC_ODR_LP_10bit_1Hz		=0x80,
	LIS2DS12_ACC_ODR_LP_10bit_12_5Hz	=0x90,
	LIS2DS12_ACC_ODR_LP_10bit_25Hz		=0xA0,
	LIS2DS12_ACC_ODR_LP_10bit_50Hz		=0xB0,
	LIS2DS12_ACC_ODR_LP_10bit_100Hz 	=0xC0,
	LIS2DS12_ACC_ODR_LP_10bit_200Hz		=0xD0,
	LIS2DS12_ACC_ODR_LP_10bit_400Hz		=0xE0,
	LIS2DS12_ACC_ODR_LP_10bit_800Hz		=0xF0,
} LIS2DS12_ACC_ODR_t;

#define  	LIS2DS12_ACC_ODR_MASK  	0xF0
status_t  LIS2DS12_ACC_W_ODR(LIS2DS12_ACC_ODR_t newValue);
status_t LIS2DS12_ACC_R_ODR(LIS2DS12_ACC_ODR_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: SIM
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SIM_4_wire 		 =0x00,
  	LIS2DS12_ACC_SIM_3_wire 		 =0x01,
} LIS2DS12_ACC_SIM_t;

#define  	LIS2DS12_ACC_SIM_MASK  	0x01
status_t  LIS2DS12_ACC_W_SIM(LIS2DS12_ACC_SIM_t newValue);
status_t LIS2DS12_ACC_R_SIM(LIS2DS12_ACC_SIM_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: I2C_DISABLE
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_I2C_DISABLE_OFF 		 =0x00,
  	LIS2DS12_ACC_I2C_DISABLE_ON 		 =0x02,
} LIS2DS12_ACC_I2C_DISABLE_t;

#define  	LIS2DS12_ACC_I2C_DISABLE_MASK  	0x02
status_t  LIS2DS12_ACC_W_I2C_DISABLE(LIS2DS12_ACC_I2C_DISABLE_t newValue);
status_t LIS2DS12_ACC_R_I2C_DISABLE(LIS2DS12_ACC_I2C_DISABLE_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: IF_ADD_INC
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_IF_ADD_INC_OFF 		 =0x00,
  	LIS2DS12_ACC_IF_ADD_INC_ON 		 =0x04,
} LIS2DS12_ACC_IF_ADD_INC_t;

#define  	LIS2DS12_ACC_IF_ADD_INC_MASK  	0x04
status_t  LIS2DS12_ACC_W_IF_ADD_INC(LIS2DS12_ACC_IF_ADD_INC_t newValue);
status_t LIS2DS12_ACC_R_IF_ADD_INC(LIS2DS12_ACC_IF_ADD_INC_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: FDS_SLOPE
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FDS_SLOPE_OFF 		 =0x00,
  	LIS2DS12_ACC_FDS_SLOPE_ON 		 =0x08,
} LIS2DS12_ACC_FDS_SLOPE_t;

#define  	LIS2DS12_ACC_FDS_SLOPE_MASK  	0x08
status_t  LIS2DS12_ACC_W_FDS_SLOPE(LIS2DS12_ACC_FDS_SLOPE_t newValue);
status_t LIS2DS12_ACC_R_FDS_SLOPE(LIS2DS12_ACC_FDS_SLOPE_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: SOFT_RESET
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SOFT_RESET_OFF 		 =0x00,
  	LIS2DS12_ACC_SOFT_RESET_ON 		 =0x40,
} LIS2DS12_ACC_SOFT_RESET_t;

#define  	LIS2DS12_ACC_SOFT_RESET_MASK  	0x40
status_t  LIS2DS12_ACC_W_SOFT_RESET(LIS2DS12_ACC_SOFT_RESET_t newValue);
status_t LIS2DS12_ACC_R_SOFT_RESET(LIS2DS12_ACC_SOFT_RESET_t *value);

/*******************************************************************************
* Register      : CTRL2
* Address       : 0X21
* Bit Group Name: BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_BOOT_OFF 		 =0x00,
  	LIS2DS12_ACC_BOOT_ON 		 =0x80,
} LIS2DS12_ACC_BOOT_t;

#define  	LIS2DS12_ACC_BOOT_MASK  	0x80
status_t  LIS2DS12_ACC_W_BOOT(LIS2DS12_ACC_BOOT_t newValue);
status_t LIS2DS12_ACC_R_BOOT(LIS2DS12_ACC_BOOT_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: PP_OD
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_PP_OD_push_pull 		 =0x00,
  	LIS2DS12_ACC_PP_OD_open_drain 		 =0x01,
} LIS2DS12_ACC_PP_OD_t;

#define  	LIS2DS12_ACC_PP_OD_MASK  	0x01
status_t  LIS2DS12_ACC_W_PP_OD(LIS2DS12_ACC_PP_OD_t newValue);
status_t LIS2DS12_ACC_R_PP_OD(LIS2DS12_ACC_PP_OD_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: H_LACTIVE
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_H_LACTIVE_high 		 =0x00,
  	LIS2DS12_ACC_H_LACTIVE_low 		 =0x02,
} LIS2DS12_ACC_H_LACTIVE_t;

#define  	LIS2DS12_ACC_H_LACTIVE_MASK  	0x02
status_t  LIS2DS12_ACC_W_H_LACTIVE(LIS2DS12_ACC_H_LACTIVE_t newValue);
status_t LIS2DS12_ACC_R_H_LACTIVE(LIS2DS12_ACC_H_LACTIVE_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: LIR
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_LIR_OFF 		 =0x00,
  	LIS2DS12_ACC_LIR_ON 		 =0x04,
} LIS2DS12_ACC_LIR_t;

#define  	LIS2DS12_ACC_LIR_MASK  	0x04
status_t  LIS2DS12_ACC_W_LIR(LIS2DS12_ACC_LIR_t newValue);
status_t LIS2DS12_ACC_R_LIR(LIS2DS12_ACC_LIR_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: TAP_Z_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TAP_Z_EN_OFF 		 =0x00,
  	LIS2DS12_ACC_TAP_Z_EN_ON 		 =0x08,
} LIS2DS12_ACC_TAP_Z_EN_t;

#define  	LIS2DS12_ACC_TAP_Z_EN_MASK  	0x08
status_t  LIS2DS12_ACC_W_TAP_Z_EN(LIS2DS12_ACC_TAP_Z_EN_t newValue);
status_t LIS2DS12_ACC_R_TAP_Z_EN(LIS2DS12_ACC_TAP_Z_EN_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: TAP_Y_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TAP_Y_EN_OFF 		 =0x00,
  	LIS2DS12_ACC_TAP_Y_EN_ON 		 =0x10,
} LIS2DS12_ACC_TAP_Y_EN_t;

#define  	LIS2DS12_ACC_TAP_Y_EN_MASK  	0x10
status_t  LIS2DS12_ACC_W_TAP_Y_EN(LIS2DS12_ACC_TAP_Y_EN_t newValue);
status_t LIS2DS12_ACC_R_TAP_Y_EN(LIS2DS12_ACC_TAP_Y_EN_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: TAP_X_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TAP_X_EN_OFF 		 =0x00,
  	LIS2DS12_ACC_TAP_X_EN_ON 		 =0x20,
} LIS2DS12_ACC_TAP_X_EN_t;

#define  	LIS2DS12_ACC_TAP_X_EN_MASK  	0x20
status_t  LIS2DS12_ACC_W_TAP_X_EN(LIS2DS12_ACC_TAP_X_EN_t newValue);
status_t LIS2DS12_ACC_R_TAP_X_EN(LIS2DS12_ACC_TAP_X_EN_t *value);

/*******************************************************************************
* Register      : CTRL3
* Address       : 0X22
* Bit Group Name: ST
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_ST_normal 		 =0x00,
  	LIS2DS12_ACC_ST_pos_sign 		 =0x40,
  	LIS2DS12_ACC_ST_neg_sign 		 =0x80,
  	LIS2DS12_ACC_ST_NOT_AVAIL 		 =0xC0,
} LIS2DS12_ACC_ST_t;

#define  	LIS2DS12_ACC_ST_MASK  	0xC0
status_t  LIS2DS12_ACC_W_ST(LIS2DS12_ACC_ST_t newValue);
status_t LIS2DS12_ACC_R_ST(LIS2DS12_ACC_ST_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_DRDY
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_DRDY_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_DRDY_ON 		 =0x01,
} LIS2DS12_ACC_INT1_DRDY_t;

#define  	LIS2DS12_ACC_INT1_DRDY_MASK  	0x01
status_t  LIS2DS12_ACC_W_INT1_DRDY(LIS2DS12_ACC_INT1_DRDY_t newValue);
status_t LIS2DS12_ACC_R_INT1_DRDY(LIS2DS12_ACC_INT1_DRDY_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_FTH_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_FTH_ON 		 =0x02,
} LIS2DS12_ACC_INT1_FTH_t;

#define  	LIS2DS12_ACC_INT1_FTH_MASK  	0x02
status_t  LIS2DS12_ACC_W_INT1_FTH(LIS2DS12_ACC_INT1_FTH_t newValue);
status_t LIS2DS12_ACC_R_INT1_FTH(LIS2DS12_ACC_INT1_FTH_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_6D_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_6D_ON 		 =0x04,
} LIS2DS12_ACC_INT1_6D_t;

#define  	LIS2DS12_ACC_INT1_6D_MASK  	0x04
status_t  LIS2DS12_ACC_W_INT1_6D(LIS2DS12_ACC_INT1_6D_t newValue);
status_t LIS2DS12_ACC_R_INT1_6D(LIS2DS12_ACC_INT1_6D_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_TAP_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_TAP_ON 		 =0x08,
} LIS2DS12_ACC_INT1_TAP_t;

#define  	LIS2DS12_ACC_INT1_TAP_MASK  	0x08
status_t  LIS2DS12_ACC_W_INT1_TAP(LIS2DS12_ACC_INT1_TAP_t newValue);
status_t LIS2DS12_ACC_R_INT1_TAP(LIS2DS12_ACC_INT1_TAP_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_FF
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_FF_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_FF_ON 		 =0x10,
} LIS2DS12_ACC_INT1_FF_t;

#define  	LIS2DS12_ACC_INT1_FF_MASK  	0x10
status_t  LIS2DS12_ACC_W_INT1_FF(LIS2DS12_ACC_INT1_FF_t newValue);
status_t LIS2DS12_ACC_R_INT1_FF(LIS2DS12_ACC_INT1_FF_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_WU
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_WU_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_WU_ON 		 =0x20,
} LIS2DS12_ACC_INT1_WU_t;

#define  	LIS2DS12_ACC_INT1_WU_MASK  	0x20
status_t  LIS2DS12_ACC_W_INT1_WU(LIS2DS12_ACC_INT1_WU_t newValue);
status_t LIS2DS12_ACC_R_INT1_WU(LIS2DS12_ACC_INT1_WU_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_S_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_S_TAP_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_S_TAP_ON 		 =0x40,
} LIS2DS12_ACC_INT1_S_TAP_t;

#define  	LIS2DS12_ACC_INT1_S_TAP_MASK  	0x40
status_t  LIS2DS12_ACC_W_INT1_S_TAP(LIS2DS12_ACC_INT1_S_TAP_t newValue);
status_t LIS2DS12_ACC_R_INT1_S_TAP(LIS2DS12_ACC_INT1_S_TAP_t *value);

/*******************************************************************************
* Register      : CTRL4
* Address       : 0X23
* Bit Group Name: INT1_DRDY
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_MASTER_DRDY_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_MASTER_DRDY_ON 		 =0x80,
} LIS2DS12_ACC_INT1_MASTER_DRDY_t;

#define  	LIS2DS12_ACC_INT1_MASTER_DRDY_MASK  	0x80
status_t  LIS2DS12_ACC_W_INT1_MASTER_DRDY(LIS2DS12_ACC_INT1_DRDY_t newValue);
status_t LIS2DS12_ACC_R_INT1_MASTER_DRDY(LIS2DS12_ACC_INT1_DRDY_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_DRDY
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_DRDY_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_DRDY_ON 		 =0x01,
} LIS2DS12_ACC_INT2_DRDY_t;

#define  	LIS2DS12_ACC_INT2_DRDY_MASK  	0x01
status_t  LIS2DS12_ACC_W_INT2_DRDY(LIS2DS12_ACC_INT2_DRDY_t newValue);
status_t LIS2DS12_ACC_R_INT2_DRDY(LIS2DS12_ACC_INT2_DRDY_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_FTH_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_FTH_ON 		 =0x02,
} LIS2DS12_ACC_INT2_FTH_t;

#define  	LIS2DS12_ACC_INT2_FTH_MASK  	0x02
status_t  LIS2DS12_ACC_W_INT2_FTH(LIS2DS12_ACC_INT2_FTH_t newValue);
status_t LIS2DS12_ACC_R_INT2_FTH(LIS2DS12_ACC_INT2_FTH_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_STEP_DET
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_STEP_DET_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_STEP_DET_ON 		 =0x04,
} LIS2DS12_ACC_INT2_STEP_DET_t;

#define  	LIS2DS12_ACC_INT2_STEP_DET_MASK  	0x04
status_t  LIS2DS12_ACC_W_INT2_STEP_DET(LIS2DS12_ACC_INT2_STEP_DET_t newValue);
status_t LIS2DS12_ACC_R_INT2_STEP_DET(LIS2DS12_ACC_INT2_STEP_DET_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_SIG_MOT
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_SIG_MOT_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_SIG_MOT_ON 		 =0x08,
} LIS2DS12_ACC_INT2_SIG_MOT_t;

#define  	LIS2DS12_ACC_INT2_SIG_MOT_MASK  	0x08
status_t  LIS2DS12_ACC_W_INT2_SIG_MOT(LIS2DS12_ACC_INT2_SIG_MOT_t newValue);
status_t LIS2DS12_ACC_R_INT2_SIG_MOT(LIS2DS12_ACC_INT2_SIG_MOT_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_TILT_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_TILT_ON 		 =0x10,
} LIS2DS12_ACC_INT2_TILT_t;

#define  	LIS2DS12_ACC_INT2_TILT_MASK  	0x10
status_t  LIS2DS12_ACC_W_INT2_TILT(LIS2DS12_ACC_INT2_TILT_t newValue);
status_t LIS2DS12_ACC_R_INT2_TILT(LIS2DS12_ACC_INT2_TILT_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_ON_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_ON_INT1_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_ON_INT1_ON 		 =0x20,
} LIS2DS12_ACC_INT2_ON_INT1_t;

#define  	LIS2DS12_ACC_INT2_ON_INT1_MASK  	0x20
status_t  LIS2DS12_ACC_W_INT2_ON_INT1(LIS2DS12_ACC_INT2_ON_INT1_t newValue);
status_t LIS2DS12_ACC_R_INT2_ON_INT1(LIS2DS12_ACC_INT2_ON_INT1_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: INT2_BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT2_BOOT_OFF 		 =0x00,
  	LIS2DS12_ACC_INT2_BOOT_ON 		 =0x40,
} LIS2DS12_ACC_INT2_BOOT_t;

#define  	LIS2DS12_ACC_INT2_BOOT_MASK  	0x40
status_t  LIS2DS12_ACC_W_INT2_BOOT(LIS2DS12_ACC_INT2_BOOT_t newValue);
status_t LIS2DS12_ACC_R_INT2_BOOT(LIS2DS12_ACC_INT2_BOOT_t *value);

/*******************************************************************************
* Register      : CTRL5
* Address       : 0X24
* Bit Group Name: DRDY_PULSED
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DRDY_PULSED_OFF 		 =0x00,
  	LIS2DS12_ACC_DRDY_PULSED_ON 		 =0x80,
} LIS2DS12_ACC_DRDY_PULSED_t;

#define  	LIS2DS12_ACC_DRDY_PULSED_MASK  	0x80
status_t  LIS2DS12_ACC_W_DRDY_PULSED(LIS2DS12_ACC_DRDY_PULSED_t newValue);
status_t LIS2DS12_ACC_R_DRDY_PULSED(LIS2DS12_ACC_DRDY_PULSED_t *value);

/*******************************************************************************
* Register      : FIFO_CTRL
* Address       : 0X25
* Bit Group Name: IF_CS_PU_DIS
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_IF_CS_PU_DIS_OFF 		 =0x00,
  	LIS2DS12_ACC_IF_CS_PU_DIS_ON 		 =0x01,
} LIS2DS12_ACC_IF_CS_PU_DIS_t;

#define  	LIS2DS12_ACC_IF_CS_PU_DIS_MASK  	0x01
status_t  LIS2DS12_ACC_W_PullUP_Disc(LIS2DS12_ACC_IF_CS_PU_DIS_t newValue);
status_t LIS2DS12_ACC_R_PullUP_Disc(LIS2DS12_ACC_IF_CS_PU_DIS_t *value);

/*******************************************************************************
* Register      : FIFO_CTRL
* Address       : 0X25
* Bit Group Name: MODULE_TO_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_MODULE_TO_FIFO_OFF 		 =0x00,
  	LIS2DS12_ACC_MODULE_TO_FIFO_ON 		 =0x08,
} LIS2DS12_ACC_MODULE_TO_FIFO_t;

#define  	LIS2DS12_ACC_MODULE_TO_FIFO_MASK  	0x08
status_t  LIS2DS12_ACC_W_MODULE_TO_FIFO(LIS2DS12_ACC_MODULE_TO_FIFO_t newValue);
status_t LIS2DS12_ACC_R_MODULE_TO_FIFO(LIS2DS12_ACC_MODULE_TO_FIFO_t *value);

/*******************************************************************************
* Register      : FIFO_CTRL
* Address       : 0X25
* Bit Group Name: FMODE
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FMODE_BYPASS 		 =0x00,
  	LIS2DS12_ACC_FMODE_FIFO 		 =0x20,
  	LIS2DS12_ACC_FMODE_STF	 		 =0x60,
  	LIS2DS12_ACC_FMODE_BTS 			 =0x80,
  	LIS2DS12_ACC_FMODE_STREAM 		 =0xC0,
} LIS2DS12_ACC_FMODE_t;

#define  	LIS2DS12_ACC_FMODE_MASK  	0xE0
status_t  LIS2DS12_ACC_W_FMODE(LIS2DS12_ACC_FMODE_t newValue);
status_t LIS2DS12_ACC_R_FMODE(LIS2DS12_ACC_FMODE_t *value);

/*******************************************************************************
* Register      : OUT_T
* Address       : 0X26
* Bit Group Name: TEMP_BIT
* Permission    : RO
*******************************************************************************/
#define  	LIS2DS12_ACC_TEMP_BIT_MASK  	0xFF
#define  	LIS2DS12_ACC_TEMP_BIT_POSITION  	0
status_t LIS2DS12_ACC_R_Temperature(u8_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: DRDY
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DRDY_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_DRDY_EV_ON 		 =0x01,
} LIS2DS12_ACC_DRDY_t;

#define  	LIS2DS12_ACC_DRDY_MASK  	0x01
status_t LIS2DS12_ACC_R_DRDY(LIS2DS12_ACC_DRDY_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: FF_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FF_IA_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_FF_IA_EV_ON 		 =0x02,
} LIS2DS12_ACC_FF_IA_t;

#define  	LIS2DS12_ACC_FF_IA_MASK  	0x02
status_t LIS2DS12_ACC_R_FF_IA(LIS2DS12_ACC_FF_IA_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: 6D_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_6D_IA_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_6D_IA_EV_ON 		 =0x04,
} LIS2DS12_ACC_6D_IA_t;

#define  	LIS2DS12_ACC_6D_IA_MASK  	0x04
status_t LIS2DS12_ACC_R_6D_IA(LIS2DS12_ACC_6D_IA_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: SINGLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SINGLE_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SINGLE_TAP_EV_ON 		 =0x08,
} LIS2DS12_ACC_SINGLE_TAP_t;

#define  	LIS2DS12_ACC_SINGLE_TAP_MASK  	0x08
status_t LIS2DS12_ACC_R_SINGLE_TAP(LIS2DS12_ACC_SINGLE_TAP_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: DOUBLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DOUBLE_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_DOUBLE_TAP_EV_ON 		 =0x10,
} LIS2DS12_ACC_DOUBLE_TAP_t;

#define  	LIS2DS12_ACC_DOUBLE_TAP_MASK  	0x10
status_t LIS2DS12_ACC_R_DOUBLE_TAP(LIS2DS12_ACC_DOUBLE_TAP_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: SLEEP_STATE
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SLEEP_STATE_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SLEEP_STATE_EV_ON 		 =0x20,
} LIS2DS12_ACC_SLEEP_STATE_t;

#define  	LIS2DS12_ACC_SLEEP_STATE_MASK  	0x20
status_t LIS2DS12_ACC_R_SLEEP_STATE(LIS2DS12_ACC_SLEEP_STATE_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: WU_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_WU_IA_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_WU_IA_EV_ON 		 =0x40,
} LIS2DS12_ACC_WU_IA_t;

#define  	LIS2DS12_ACC_WU_IA_MASK  	0x40
status_t LIS2DS12_ACC_R_WU_IA(LIS2DS12_ACC_WU_IA_t *value);

/*******************************************************************************
* Register      : STATUS
* Address       : 0X27
* Bit Group Name: FIFO_THS
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FIFO_THS_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_FIFO_THS_EV_ON 		 =0x80,
} LIS2DS12_ACC_FIFO_THS_t;

#define  	LIS2DS12_ACC_FIFO_THS_MASK  	0x80
status_t LIS2DS12_ACC_R_FIFO_THS(LIS2DS12_ACC_FIFO_THS_t *value);

/*******************************************************************************
* Register      : FIFO_THS
* Address       : 0X2E
* Bit Group Name: FTH
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_FTH_MASK  	0xFF
#define  	LIS2DS12_ACC_FTH_POSITION  	0
status_t  LIS2DS12_ACC_W_FifoThsld(u8_t newValue);
status_t LIS2DS12_ACC_R_FifoThsld(u8_t *value);

/*******************************************************************************
* Register      : FIFO_SRC
* Address       : 0X2F
* Bit Group Name: FIFO_OVR
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FIFO_OVR_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_FIFO_OVR_EV_ON 		 =0x40,
} LIS2DS12_ACC_FIFO_OVR_t;

#define  	LIS2DS12_ACC_FIFO_OVR_MASK  	0x40
status_t LIS2DS12_ACC_R_FIFO_OVR(LIS2DS12_ACC_FIFO_OVR_t *value);

/*******************************************************************************
* Register      : FIFO_SRC
* Address       : 0X2F
* Bit Group Name: FTH
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FTH_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_FTH_EV_ON 		 =0x80,
} LIS2DS12_ACC_FTH_STATUS_t;

#define  	LIS2DS12_ACC_FTH_STATUS_MASK  	0x80
status_t LIS2DS12_ACC_R_FTH(LIS2DS12_ACC_FTH_STATUS_t *value);

/*******************************************************************************
* Register      : FIFO_SAMPLES
* Address       : 0X30
* Bit Group Name: SAMPLE
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_SAMPLE_L_MASK  	0xFF
#define  	LIS2DS12_ACC_SAMPLE_L_POSITION  	0
#define  	LIS2DS12_ACC_SAMPLE_H_MASK  	0x20
#define  	LIS2DS12_ACC_SAMPLE_H_POSITION  	5
status_t LIS2DS12_ACC_R_SamplesNum(u16_t *value);

/*******************************************************************************
* Register      : TAP_6D_THS
* Address       : 0X31
* Bit Group Name: TAP_THS
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_TAP_THS_MASK  	0x1F
#define  	LIS2DS12_ACC_TAP_THS_POSITION  	0
status_t  LIS2DS12_ACC_W_TAP_THS(u8_t newValue);
status_t LIS2DS12_ACC_R_TAP_THS(u8_t *value);

/*******************************************************************************
* Register      : TAP_6D_THS
* Address       : 0X31
* Bit Group Name: 6D_THS
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_6D_THS_80_degrees 		 =0x00,
  	LIS2DS12_ACC_6D_THS_70_degrees 		 =0x20,
  	LIS2DS12_ACC_6D_THS_60_degrees 		 =0x40,
  	LIS2DS12_ACC_6D_THS_50_degrees 		 =0x60,
} LIS2DS12_ACC_6D_THS_t;

#define  	LIS2DS12_ACC_6D_THS_MASK  	0x60
status_t  LIS2DS12_ACC_W_6D_THS(LIS2DS12_ACC_6D_THS_t newValue);
status_t LIS2DS12_ACC_R_6D_THS(LIS2DS12_ACC_6D_THS_t *value);

/*******************************************************************************
* Register      : TAP_6D_THS
* Address       : 0X31
* Bit Group Name: 4D_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_4D_EN_OFF 		 =0x00,
  	LIS2DS12_ACC_4D_EN_ON 		 =0x80,
} LIS2DS12_ACC_4D_EN_t;

#define  	LIS2DS12_ACC_4D_EN_MASK  	0x80
status_t  LIS2DS12_ACC_W_4D_EN(LIS2DS12_ACC_4D_EN_t newValue);
status_t LIS2DS12_ACC_R_4D_EN(LIS2DS12_ACC_4D_EN_t *value);

/*******************************************************************************
* Register      : INT_DUR
* Address       : 0X32
* Bit Group Name: SHOCK
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_SHOCK_MASK  	0x03
#define  	LIS2DS12_ACC_SHOCK_POSITION  	0
status_t  LIS2DS12_ACC_W_SHOCK(u8_t newValue);
status_t LIS2DS12_ACC_R_SHOCK(u8_t *value);

/*******************************************************************************
* Register      : INT_DUR
* Address       : 0X32
* Bit Group Name: QUIET
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_QUIET_MASK  	0x0C
#define  	LIS2DS12_ACC_QUIET_POSITION  	2
status_t  LIS2DS12_ACC_W_QUIET(u8_t newValue);
status_t LIS2DS12_ACC_R_QUIET(u8_t *value);

/*******************************************************************************
* Register      : INT_DUR
* Address       : 0X32
* Bit Group Name: LAT
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_LAT_MASK  	0xF0
#define  	LIS2DS12_ACC_LAT_POSITION  	4
status_t  LIS2DS12_ACC_W_LAT(u8_t newValue);
status_t LIS2DS12_ACC_R_LAT(u8_t *value);

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X33
* Bit Group Name: WU_THS
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_WU_THS_MASK  	0x3F
#define  	LIS2DS12_ACC_WU_THS_POSITION  	0
status_t  LIS2DS12_ACC_W_WU_THS(u8_t newValue);
status_t LIS2DS12_ACC_R_WU_THS(u8_t *value);

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X33
* Bit Group Name: SLEEP_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SLEEP_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_SLEEP_ON_ON 		 =0x40,
} LIS2DS12_ACC_SLEEP_ON_t;

#define  	LIS2DS12_ACC_SLEEP_ON_MASK  	0x40
status_t  LIS2DS12_ACC_W_SLEEP_ON(LIS2DS12_ACC_SLEEP_ON_t newValue);
status_t LIS2DS12_ACC_R_SLEEP_ON(LIS2DS12_ACC_SLEEP_ON_t *value);

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X33
* Bit Group Name: SINGLE_DOUBLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SINGLE_DOUBLE_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SINGLE_DOUBLE_TAP_EV_ON 		 =0x80,
} LIS2DS12_ACC_SINGLE_DOUBLE_TAP_t;

#define  	LIS2DS12_ACC_SINGLE_DOUBLE_TAP_MASK  	0x80
status_t  LIS2DS12_ACC_W_SINGLE_DOUBLE_TAP(LIS2DS12_ACC_SINGLE_DOUBLE_TAP_t newValue);
status_t LIS2DS12_ACC_R_SINGLE_DOUBLE_TAP(LIS2DS12_ACC_SINGLE_DOUBLE_TAP_t *value);

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X34
* Bit Group Name: SLEEP_DUR
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_SLEEP_DUR_MASK  	0x0F
#define  	LIS2DS12_ACC_SLEEP_DUR_POSITION  	0
status_t  LIS2DS12_ACC_W_SleepDuration(u8_t newValue);
status_t LIS2DS12_ACC_R_SleepDuration(u8_t *value);

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X34
* Bit Group Name: INT1_FIFO_FULL
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_INT1_FIFO_FULL_OFF 		 =0x00,
  	LIS2DS12_ACC_INT1_FIFO_FULL_ON 		 =0x10,
} LIS2DS12_ACC_INT1_FIFO_FULL_t;

#define  	LIS2DS12_ACC_INT1_FIFO_FULL_MASK  	0x10
status_t  LIS2DS12_ACC_W_INT1_FIFO_FULL(LIS2DS12_ACC_INT1_FIFO_FULL_t newValue);
status_t LIS2DS12_ACC_R_INT1_FIFO_FULL(LIS2DS12_ACC_INT1_FIFO_FULL_t *value);

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X34
* Bit Group Name: WU_DUR
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_WU_DUR_MASK  	0x60
#define  	LIS2DS12_ACC_WU_DUR_POSITION  	5
status_t  LIS2DS12_ACC_W_WakeUpDuration(u8_t newValue);
status_t LIS2DS12_ACC_R_WakeUpDuration(u8_t *value);

/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X35
* Bit Group Name: FF_THS
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_FF_THS_MASK  	0x07
#define  	LIS2DS12_ACC_FF_THS_POSITION  	0
status_t  LIS2DS12_ACC_W_FreeFallDuration(u8_t newValue);
status_t LIS2DS12_ACC_R_FreeFallDuration(u8_t *value);

/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X35
* Bit Group Name: FF_DUR
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_FF_DUR_LOW_MASK  	0xF8
#define  	LIS2DS12_ACC_FF_DUR_LOW_POSITION  	3
#define  	LIS2DS12_ACC_FF_DUR_HIGH_MASK  	0x80
#define  	LIS2DS12_ACC_FF_DUR_HIGH_POSITION  	7
status_t  LIS2DS12_ACC_W_FF_DUR(u8_t newValue);
status_t LIS2DS12_ACC_R_FF_DUR(u8_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: DRDY
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DRDY_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_DRDY_EV_DUP_ON 		 =0x01,
} LIS2DS12_ACC_DRDY_DUP_t;

#define  	LIS2DS12_ACC_DRDY_DUP_MASK  	0x01
status_t LIS2DS12_ACC_R_DRDY_DUP(LIS2DS12_ACC_DRDY_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: FF_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FF_IA_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_FF_IA_EV_DUP_ON 		 =0x02,
} LIS2DS12_ACC_FF_IA_DUP_t;

#define  	LIS2DS12_ACC_FF_IA_DUP_MASK  	0x02
status_t LIS2DS12_ACC_R_FF_IA_DUP(LIS2DS12_ACC_FF_IA_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: 6D_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_6D_IA_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_6D_IA_EV_DUP_ON 		 =0x04,
} LIS2DS12_ACC_6D_IA_DUP_t;

#define  	LIS2DS12_ACC_6D_IA_DUP_MASK  	0x04
status_t LIS2DS12_ACC_R_6D_IA_DUP(LIS2DS12_ACC_6D_IA_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: SINGLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SINGLE_TAP_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_SINGLE_TAP_EV_vON 		 =0x08,
} LIS2DS12_ACC_SINGLE_TAP_DUP_t;

#define  	LIS2DS12_ACC_SINGLE_TAP_DUP_MASK  	0x08
status_t LIS2DS12_ACC_R_SINGLE_TAP_DUP(LIS2DS12_ACC_SINGLE_TAP_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: DOUBLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DOUBLE_TAP_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_DOUBLE_TAP_EV_DUP_ON 		 =0x10,
} LIS2DS12_ACC_DOUBLE_TAP_DUP_t;

#define  	LIS2DS12_ACC_DOUBLE_TAP_DUP_MASK  	0x10
status_t LIS2DS12_ACC_R_DOUBLE_TAP_DUP(LIS2DS12_ACC_DOUBLE_TAP_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: SLEEP_STATE
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SLEEP_STATE_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_SLEEP_STATE_EV_DUP_ON 		 =0x20,
} LIS2DS12_ACC_SLEEP_STATE_DUP_t;

#define  	LIS2DS12_ACC_SLEEP_STATE_DUP_MASK  	0x20
status_t LIS2DS12_ACC_R_SLEEP_STATE_DUP(LIS2DS12_ACC_SLEEP_STATE_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: WU_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_WU_IA_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_WU_IA_EV_DUP_ON 		 =0x40,
} LIS2DS12_ACC_WU_IA_DUP_t;

#define  	LIS2DS12_ACC_WU_IA_DUP_MASK  	0x40
status_t LIS2DS12_ACC_R_WU_IA_DUP(LIS2DS12_ACC_WU_IA_DUP_t *value);

/*******************************************************************************
* Register      : STATUS_DUP
* Address       : 0X36
* Bit Group Name: OVR
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_OVR_EV_DUP_OFF 		 =0x00,
  	LIS2DS12_ACC_OVR_EV_DUP_ON 		 =0x80,
} LIS2DS12_ACC_OVR_DUP_t;

#define  	LIS2DS12_ACC_OVR_DUP_MASK  	0x80
status_t LIS2DS12_ACC_R_OVR_DUP(LIS2DS12_ACC_OVR_DUP_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: Z_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_Z_WU_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_Z_WU_EV_ON 		 =0x01,
} LIS2DS12_ACC_Z_WU_t;

#define  	LIS2DS12_ACC_Z_WU_MASK  	0x01
status_t LIS2DS12_ACC_R_Z_WU(LIS2DS12_ACC_Z_WU_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: Y_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_Y_WU_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_Y_WU_EV_ON 		 =0x02,
} LIS2DS12_ACC_Y_WU_t;

#define  	LIS2DS12_ACC_Y_WU_MASK  	0x02
status_t LIS2DS12_ACC_R_Y_WU(LIS2DS12_ACC_Y_WU_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: X_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_X_WU_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_X_WU_EV_ON 		 =0x04,
} LIS2DS12_ACC_X_WU_t;

#define  	LIS2DS12_ACC_X_WU_MASK  	0x04
status_t LIS2DS12_ACC_R_X_WU(LIS2DS12_ACC_X_WU_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: WU_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_WU_IA_DUP2_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_WU_IA_DUP2_EV_ON 		 =0x08,
} LIS2DS12_ACC_WU_IA_DUP2_t;

#define  	LIS2DS12_ACC_WU_IA_DUP2_MASK  	0x08
status_t LIS2DS12_ACC_R_WU_IA_DUP2(LIS2DS12_ACC_WU_IA_DUP2_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: SLEEP_STATE_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SLEEP_STATE_IA_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SLEEP_STATE_IA_EV_ON 		 =0x10,
} LIS2DS12_ACC_SLEEP_STATE_IA_t;

#define  	LIS2DS12_ACC_SLEEP_STATE_IA_MASK  	0x10
status_t LIS2DS12_ACC_R_SLEEP_STATE_IA(LIS2DS12_ACC_SLEEP_STATE_IA_t *value);

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X37
* Bit Group Name: FF_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FF_IA_DUP2_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_FF_IA_DUP2_EV_ON 		 =0x20,
} LIS2DS12_ACC_FF_IA_DUP2_t;

#define  	LIS2DS12_ACC_FF_IA_DUP2_MASK  	0x20
status_t LIS2DS12_ACC_R_FF_IA_DUP2(LIS2DS12_ACC_FF_IA_DUP2_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: Z_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_Z_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_Z_TAP_EV_ON 		 =0x01,
} LIS2DS12_ACC_Z_TAP_t;

#define  	LIS2DS12_ACC_Z_TAP_MASK  	0x01
status_t LIS2DS12_ACC_R_Z_TAP(LIS2DS12_ACC_Z_TAP_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: Y_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_Y_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_Y_TAP_EV_ON 		 =0x02,
} LIS2DS12_ACC_Y_TAP_t;

#define  	LIS2DS12_ACC_Y_TAP_MASK  	0x02
status_t LIS2DS12_ACC_R_Y_TAP(LIS2DS12_ACC_Y_TAP_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: X_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_X_TAP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_X_TAP_EV_ON 		 =0x04,
} LIS2DS12_ACC_X_TAP_t;

#define  	LIS2DS12_ACC_X_TAP_MASK  	0x04
status_t LIS2DS12_ACC_R_X_TAP(LIS2DS12_ACC_X_TAP_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: TAP_SIGN
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TAP_SIGN_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_TAP_SIGN_EV_ON 		 =0x08,
} LIS2DS12_ACC_TAP_SIGN_t;

#define  	LIS2DS12_ACC_TAP_SIGN_MASK  	0x08
status_t LIS2DS12_ACC_R_TAP_SIGN(LIS2DS12_ACC_TAP_SIGN_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: DOUBLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_DOUBLE_TAP_DUP2_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_DOUBLE_TAP_DUP2_EV_ON 		 =0x10,
} LIS2DS12_ACC_DOUBLE_TAP_DUP2_t;

#define  	LIS2DS12_ACC_DOUBLE_TAP_DUP2_MASK  	0x10
status_t LIS2DS12_ACC_R_DOUBLE_TAP_DUP2(LIS2DS12_ACC_DOUBLE_TAP_DUP2_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: SINGLE_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SINGLE_TAP_DUP2_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SINGLE_TAP_DUP2_EV_ON 		 =0x20,
} LIS2DS12_ACC_SINGLE_TAP_DUP2_t;

#define  	LIS2DS12_ACC_SINGLE_TAP_DUP2_MASK  	0x20
status_t LIS2DS12_ACC_R_SINGLE_TAP_DUP2(LIS2DS12_ACC_SINGLE_TAP_DUP2_t *value);

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X38
* Bit Group Name: TAP_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TAP_IA_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_TAP_IA_EV_ON 		 =0x40,
} LIS2DS12_ACC_TAP_IA_t;

#define  	LIS2DS12_ACC_TAP_IA_MASK  	0x40
status_t LIS2DS12_ACC_R_TAP_IA(LIS2DS12_ACC_TAP_IA_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: XL
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_XL_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_XL_EV_ON 		 =0x01,
} LIS2DS12_ACC_XL_t;

#define  	LIS2DS12_ACC_XL_MASK  	0x01
status_t LIS2DS12_ACC_R_XL(LIS2DS12_ACC_XL_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: XH
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_XH_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_XH_EV_ON 		 =0x02,
} LIS2DS12_ACC_XH_t;

#define  	LIS2DS12_ACC_XH_MASK  	0x02
status_t LIS2DS12_ACC_R_XH(LIS2DS12_ACC_XH_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: YL
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_YL_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_YL_EV_ON 		 =0x04,
} LIS2DS12_ACC_YL_t;

#define  	LIS2DS12_ACC_YL_MASK  	0x04
status_t LIS2DS12_ACC_R_YL(LIS2DS12_ACC_YL_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: YH
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_YH_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_YH_EV_ON 		 =0x08,
} LIS2DS12_ACC_YH_t;

#define  	LIS2DS12_ACC_YH_MASK  	0x08
status_t LIS2DS12_ACC_R_YH(LIS2DS12_ACC_YH_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: ZL
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_ZL_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_ZL_EV_ON 		 =0x10,
} LIS2DS12_ACC_ZL_t;

#define  	LIS2DS12_ACC_ZL_MASK  	0x10
status_t LIS2DS12_ACC_R_ZL(LIS2DS12_ACC_ZL_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: ZH
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_ZH_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_ZH_EV_ON 		 =0x20,
} LIS2DS12_ACC_ZH_t;

#define  	LIS2DS12_ACC_ZH_MASK  	0x20
status_t LIS2DS12_ACC_R_ZH(LIS2DS12_ACC_ZH_t *value);

/*******************************************************************************
* Register      : 6D_SRC
* Address       : 0X39
* Bit Group Name: 6D_IA
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_6D_IA_EV_DUP2_OFF 		 =0x00,
  	LIS2DS12_ACC_6D_IA_DUP2_EV_ON 		 =0x40,
} LIS2DS12_ACC_6D_IA_DUP2_t;

#define  	LIS2DS12_ACC_6D_IA_DUP2_MASK  	0x40
status_t LIS2DS12_ACC_R_6D_IA_DUP2(LIS2DS12_ACC_6D_IA_DUP2_t *value);

/*******************************************************************************
* Register      : STEP_C_MINTHS
* Address       : 0X3A
* Bit Group Name: SC_MTHS
* Permission    : RW
*******************************************************************************/
#define  	LIS2DS12_ACC_SC_MTHS_MASK  	0x3F
#define  	LIS2DS12_ACC_SC_MTHS_POSITION  	0
status_t  LIS2DS12_ACC_W_SC_MTHS(u8_t newValue);
status_t LIS2DS12_ACC_R_SC_MTHS(u8_t *value);

/*******************************************************************************
* Register      : STEP_C_MINTHS
* Address       : 0X3A
* Bit Group Name: PEDO4G
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_PEDO4G_OFF 		 =0x00,
  	LIS2DS12_ACC_PEDO4G_ON 		 =0x40,
} LIS2DS12_ACC_PEDO4G_t;

#define  	LIS2DS12_ACC_PEDO4G_MASK  	0x40
status_t  LIS2DS12_ACC_W_PEDO4G(LIS2DS12_ACC_PEDO4G_t newValue);
status_t LIS2DS12_ACC_R_PEDO4G(LIS2DS12_ACC_PEDO4G_t *value);

/*******************************************************************************
* Register      : STEP_C_MINTHS
* Address       : 0X3A
* Bit Group Name: RST_NSTEP
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_RST_NSTEP_OFF 		 =0x00,
  	LIS2DS12_ACC_RST_NSTEP_ON 		 =0x80,
} LIS2DS12_ACC_RST_NSTEP_t;

#define  	LIS2DS12_ACC_RST_NSTEP_MASK  	0x80
status_t  LIS2DS12_ACC_W_RST_NSTEP(LIS2DS12_ACC_RST_NSTEP_t newValue);
status_t LIS2DS12_ACC_R_RST_NSTEP(LIS2DS12_ACC_RST_NSTEP_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: CK_GATE_FUNC
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_CK_GATE_FUNC_OFF 		 =0x00,
  	LIS2DS12_ACC_CK_GATE_FUNC_ON 		 =0x01,
} LIS2DS12_ACC_CK_GATE_FUNC_t;

#define  	LIS2DS12_ACC_CK_GATE_FUNC_MASK  	0x01
status_t LIS2DS12_ACC_R_CK_GATE_FUNC(LIS2DS12_ACC_CK_GATE_FUNC_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: STEP_DETECT
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_STEP_DETECT_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_STEP_DETECT_EV_ON 		 =0x02,
} LIS2DS12_ACC_STEP_DETECT_t;

#define  	LIS2DS12_ACC_STEP_DETECT_MASK  	0x02
status_t LIS2DS12_ACC_R_STEP_DETECT(LIS2DS12_ACC_STEP_DETECT_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: RST_PEDO
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_RST_PEDO_OFF 		 =0x00,
  	LIS2DS12_ACC_RST_PEDO_ON 		 =0x04,
} LIS2DS12_ACC_RST_PEDO_t;

#define  	LIS2DS12_ACC_RST_PEDO_MASK  	0x04
status_t LIS2DS12_ACC_R_RST_PEDO(LIS2DS12_ACC_RST_PEDO_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: RST_SIGN_MOT
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_RST_SIGN_MOT_OFF 		 =0x00,
  	LIS2DS12_ACC_RST_SIGN_MOT_ON 		 =0x08,
} LIS2DS12_ACC_RST_SIGN_MOT_t;

#define  	LIS2DS12_ACC_RST_SIGN_MOT_MASK  	0x08
status_t LIS2DS12_ACC_R_RST_SIGN_MOT(LIS2DS12_ACC_RST_SIGN_MOT_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: SIG_MOT_DETECT
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SIG_MOT_DETECT_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SIG_MOT_DETECT_EV_ON 		 =0x10,
} LIS2DS12_ACC_SIG_MOT_DETECT_t;

#define  	LIS2DS12_ACC_SIG_MOT_DETECT_MASK  	0x10
status_t LIS2DS12_ACC_R_SIG_MOT_DETECT(LIS2DS12_ACC_SIG_MOT_DETECT_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: FS_SRC
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_FS_SRC_NO_SCALING 		 =0x00,
  	LIS2DS12_ACC_FS_SRC_2G 		 =0x20,
  	LIS2DS12_ACC_FS_SRC_4G 		 =0x40,
  	LIS2DS12_ACC_FS_SRC_NO_SCALING2 		 =0x60,
} LIS2DS12_ACC_FS_SRC_t;

#define  	LIS2DS12_ACC_FS_SRC_MASK  	0x60
status_t LIS2DS12_ACC_R_FS_SRC(LIS2DS12_ACC_FS_SRC_t *value);

/*******************************************************************************
* Register      : FUNC_CK_GATE
* Address       : 0X3D
* Bit Group Name: TILT_INT
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TILT_INT_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_TILT_INT_EV_ON 		 =0x80,
} LIS2DS12_ACC_TILT_INT_t;

#define  	LIS2DS12_ACC_TILT_INT_MASK  	0x80
status_t LIS2DS12_ACC_R_TILT_INT(LIS2DS12_ACC_TILT_INT_t *value);

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X3E
* Bit Group Name: SENS_HUB_END_OP
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SENS_HUB_END_OP_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_SENS_HUB_END_OP_EV_ON 		 =0x01,
} LIS2DS12_ACC_SENS_HUB_END_OP_t;

#define  	LIS2DS12_ACC_SENS_HUB_END_OP_MASK  	0x01
status_t LIS2DS12_ACC_R_SENS_HUB_END_OP(LIS2DS12_ACC_SENS_HUB_END_OP_t *value);

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X3E
* Bit Group Name: MODULE_READY
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_MODULE_READY_EV_OFF 		 =0x00,
  	LIS2DS12_ACC_MODULE_READY_EV_ON 		 =0x02,
} LIS2DS12_ACC_MODULE_READY_t;

#define  	LIS2DS12_ACC_MODULE_READY_MASK  	0x02
status_t LIS2DS12_ACC_R_MODULE_READY(LIS2DS12_ACC_MODULE_READY_t *value);

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X3E
* Bit Group Name: RST_TILT
* Permission    : RO
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_RST_TILT_OFF 		 =0x00,
  	LIS2DS12_ACC_RST_TILT_ON 		 =0x04,
} LIS2DS12_ACC_RST_TILT_t;

#define  	LIS2DS12_ACC_RST_TILT_MASK  	0x04
status_t LIS2DS12_ACC_R_RST_TILT(LIS2DS12_ACC_RST_TILT_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: STEP_CNT_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_STEP_CNT_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_STEP_CNT_ON_ON 		 =0x01,
} LIS2DS12_ACC_STEP_CNT_ON_t;

#define  	LIS2DS12_ACC_STEP_CNT_ON_MASK  	0x01
status_t  LIS2DS12_ACC_W_STEP_CNT_ON(LIS2DS12_ACC_STEP_CNT_ON_t newValue);
status_t LIS2DS12_ACC_R_STEP_CNT_ON(LIS2DS12_ACC_STEP_CNT_ON_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: SIGN_MOT_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_SIGN_MOT_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_SIGN_MOT_ON_ON 		 =0x02,
} LIS2DS12_ACC_SIGN_MOT_ON_t;

#define  	LIS2DS12_ACC_SIGN_MOT_ON_MASK  	0x02
status_t  LIS2DS12_ACC_W_SIGN_MOT_ON(LIS2DS12_ACC_SIGN_MOT_ON_t newValue);
status_t LIS2DS12_ACC_R_SIGN_MOT_ON(LIS2DS12_ACC_SIGN_MOT_ON_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: MASTER_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_MASTER_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_MASTER_ON_ON 		 =0x04,
} LIS2DS12_ACC_MASTER_ON_t;

#define  	LIS2DS12_ACC_MASTER_ON_MASK  	0x04
status_t  LIS2DS12_ACC_W_MASTER_ON(LIS2DS12_ACC_MASTER_ON_t newValue);
status_t LIS2DS12_ACC_R_MASTER_ON(LIS2DS12_ACC_MASTER_ON_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: TUD_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TUD_EN_OFF 		 =0x00,
  	LIS2DS12_ACC_TUD_EN_ON 		 =0x08,
} LIS2DS12_ACC_TUD_EN_t;

#define  	LIS2DS12_ACC_TUD_EN_MASK  	0x08
status_t  LIS2DS12_ACC_W_TUD_EN(LIS2DS12_ACC_TUD_EN_t newValue);
status_t LIS2DS12_ACC_R_TUD_EN(LIS2DS12_ACC_TUD_EN_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: TILT_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_TILT_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_TILT_ON_ON 		 =0x10,
} LIS2DS12_ACC_TILT_ON_t;

#define  	LIS2DS12_ACC_TILT_ON_MASK  	0x10
status_t  LIS2DS12_ACC_W_TILT_ON(LIS2DS12_ACC_TILT_ON_t newValue);
status_t LIS2DS12_ACC_R_TILT_ON(LIS2DS12_ACC_TILT_ON_t *value);

/*******************************************************************************
* Register      : FUNC_CTRL
* Address       : 0X3F
* Bit Group Name: MODULE_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
  	LIS2DS12_ACC_MODULE_ON_OFF 		 =0x00,
  	LIS2DS12_ACC_MODULE_ON_ON 		 =0x20,
} LIS2DS12_ACC_MODULE_ON_t;

#define  	LIS2DS12_ACC_MODULE_ON_MASK  	0x20
status_t  LIS2DS12_ACC_W_MODULE_ON(LIS2DS12_ACC_MODULE_ON_t newValue);
status_t LIS2DS12_ACC_R_MODULE_ON(LIS2DS12_ACC_MODULE_ON_t *value);
/*******************************************************************************
* Register      : <REGISTER_L> - <REGISTER_H>
* Output Type   : ExternalSensor
* Permission    : RO 
*******************************************************************************/
status_t LIS2DS12_ACC_Get_ExternalSensor(u8_t *buff); 
/*******************************************************************************
* Register      : <REGISTER_L> - <REGISTER_H>
* Output Type   : Acceleration
* Permission    : RO 
*******************************************************************************/
status_t LIS2DS12_ACC_Get_Raw_Acceleration(u8_t *buff);
status_t LIS2DS12_ACC_Get_Acceleration(int *buff);

/*******************************************************************************
* Register      : <REGISTER_L> - <REGISTER_H>
* Output Type   : StepCounter
* Permission    : RO 
*******************************************************************************/
status_t LIS2DS12_ACC_Get_StepCounter(u8_t *buff); 
#endif
