/************************************************************************************
** File:  \\192.168.144.3\Linux_Share\12015\ics2\development\mediatek\custom\oplus77_12015\kernel\battery\battery
** VENDOR_EDIT
** Copyright (C), 2008-2012, OPLUS Mobile Comm Corp., Ltd
**
** Description:
**      for dc-dc sn111008 charg
**
** Version: 1.0
** Date created: 21:03:46,05/04/2012
** Author: Fanhong.Kong@ProDrv.CHG
**
** --------------------------- Revision History: ------------------------------------------------------------
* <version>       <date>        <author>              			<desc>
* Revision 1.0    2015-06-22    Fanhong.Kong@ProDrv.CHG   		Created for new architecture
************************************************************************************************************/


#ifndef __OPLUS_BQ24190_H__

#define __OPLUS_BQ24190_H__
#include <linux/power_supply.h>
#ifdef CONFIG_OPLUS_CHARGER_MTK
#include <mt-plat/charger_type.h>

#endif

#include "../oplus_charger.h"

/* Address:00h */
#define REG00_BQ24190_ADDRESS                                   0x00

#define REG00_BQ24190_SUSPEND_MODE_MASK                         BIT(7)
#define REG00_BQ24190_SUSPEND_MODE_DISABLE                      0x00
#define REG00_BQ24190_SUSPEND_MODE_ENABLE                       BIT(7)

#define REG00_BQ24190_VINDPM_MASK								(BIT(6) | BIT(5) | BIT(4) | BIT(3))
#define REG00_BQ24190_VINDPM_STEP_MV							80
#define REG00_BQ24190_VINDPM_OFFSET								3880
#define REG00_BQ24190_VINDPM_SHIFT								3

#define REG00_BQ24190_INPUT_CURRENT_LIMIT_MASK                  (BIT(2) | BIT(1) | BIT(0))
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_SHIFT                 0
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_100MA                 0x00
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_150MA                 BIT(0)
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_500MA                 BIT(1)
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_900MA                 (BIT(1) | BIT(0))
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_1200MA                BIT(2)
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_1500MA                (BIT(2) | BIT(0))
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_2000MA                (BIT(2) | BIT(1))
#define REG00_BQ24190_INPUT_CURRENT_LIMIT_3000MA                (BIT(2) | BIT(1) | BIT(0))


/* Address:01h */
#define REG01_BQ24190_ADDRESS                                   0x01

#define REG01_BQ24190_REGISTER_RESET_MASK                       BIT(7)
#define REG01_BQ24190_REGISTER_KEEP                             0x00
#define REG01_BQ24190_REGISTER_RESET                            BIT(7)

#define REG01_BQ24190_WDT_TIMER_RESET_MASK                      BIT(6)
#define REG01_BQ24190_WDT_TIMER_NORMAL                          0x00
#define REG01_BQ24190_WDT_TIMER_RESET                           BIT(6)

//#define REG01_BQ24190_CHARGING_MASK                             (BIT(5) | BIT(4))
#define REG01_BQ24190_CHARGING_MASK                             BIT(4)
#define REG01_BQ24190_CHARGING_DISABLE                          0x00
#define REG01_BQ24190_CHARGING_ENABLE                           BIT(4)
//#define REG01_BQ24190_CHARGING_OTG                              BIT(5)
#define REG01_BQ24190_OTG_MASK                              	BIT(5)
#define REG01_BQ24190_OTG_ENABLE                              	BIT(5)
#define REG01_BQ24190_OTG_DISABLE                              	0x00

#define REG01_BQ24190_SYS_VOL_LIMIT_MASK                        (BIT(3) | BIT(2) | BIT(1))
#define REG01_BQ24190_SYS_VOL_LIMIT_3000MV                      0x00
#define REG01_BQ24190_SYS_VOL_LIMIT_3100MV                      BIT(1)
#define REG01_BQ24190_SYS_VOL_LIMIT_3200MV                      BIT(2)
#define REG01_BQ24190_SYS_VOL_LIMIT_3300MV                      (BIT(2) | BIT(1))
#define REG01_BQ24190_SYS_VOL_LIMIT_3400MV                      BIT(3)
#define REG01_BQ24190_SYS_VOL_LIMIT_3500MV                      (BIT(3) | BIT(1))
#define REG01_BQ24190_SYS_VOL_LIMIT_3600MV                      (BIT(3) | BIT(2))
#define REG01_BQ24190_SYS_VOL_LIMIT_3700MV                      (BIT(3) | BIT(2) | BIT(1))

#define REG01_BQ24190_BOOST_MODE_CURRENT_LIMIT_MASK             BIT(0)
#define REG01_BQ24190_BOOST_MODE_CURRENT_LIMIT_500MA            0x00
#define REG01_BQ24190_BOOST_MODE_CURRENT_LIMIT_1300MA           BIT(0)


/* Address:02h */
#define REG02_BQ24190_ADDRESS                                   0x02

#define REG02_BQ24190_FAST_CHARGING_CURRENT_LIMIT_MASK          (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2))
#define REG02_BQ24190_FAST_CHARGING_CURRENT_LIMIT_SHIFT         2
#define BQ24190_MIN_FAST_CURRENT_MA                             512
#define BQ24190_MIN_FAST_CURRENT_MA_ALLOWED                     1088
#define BQ24190_MIN_FAST_CURRENT_MA_20_PERCENT                  908
#define BQ24190_MAX_FAST_CURRENT_MA                             2048
#define BQ24190_FAST_CURRENT_STEP_MA                            64

#define REG02_BQ24190_FAST_CHARGING_CURRENT_FORCE20PCT_MASK     BIT(0)
#define REG02_BQ24190_FAST_CHARGING_CURRENT_FORCE20PCT_DISABLE  0x00
#define REG02_BQ24190_FAST_CHARGING_CURRENT_FORCE20PCT_ENABLE   BIT(0)


/* Address:03h */
#define REG03_BQ24190_ADDRESS                                   0x03

#define REG03_BQ24190_PRE_CHARGING_CURRENT_LIMIT_MASK           (BIT(7) | BIT(6) | BIT(5) | BIT(4))
#define REG03_BQ24190_PRE_CHARGING_CURRENT_LIMIT_SHIFT          4
#define BQ24190_MIN_PRE_CURRENT_MA                              128
#define BQ24190_MAX_PRE_CURRENT_MA                              2048
#define BQ24190_PRE_CURRENT_STEP_MA                             128

#define REG03_BQ24190_TERM_CHARGING_CURRENT_LIMIT_MASK          (BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define REG03_BQ24190_TERM_CHARGING_CURRENT_LIMIT_SHIFT         0
#define BQ24190_MIN_TERM_CURRENT_MA                              128
#define BQ24190_MAX_TERM_CURRENT_MA                              2048
#define BQ24190_TERM_CURRENT_STEP_MA                             128


/* Address:04h */
#define REG04_BQ24190_ADDRESS                                   0x04

#define REG04_BQ24190_CHARGING_VOL_LIMIT_MASK                   (BIT(7) | BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2))
#define REG04_BQ24190_CHARGING_VOL_LIMIT_SHIFT                  2
#define BQ24190_MIN_FLOAT_MV                                    3504
#define BQ24190_MAX_FLOAT_MV                                    4400
#define BQ24190_VFLOAT_STEP_MV                                  16

#define REG04_BQ24190_PRE_TO_FAST_CHARGING_VOL_MASK             BIT(1)
#define REG04_BQ24190_PRE_TO_FAST_CHARGING_VOL_2800MV           0x00
#define REG04_BQ24190_PRE_TO_FAST_CHARGING_VOL_3000MV           BIT(1)

#define REG04_BQ24190_RECHARGING_THRESHOLD_VOL_MASK             BIT(0)
#define REG04_BQ24190_RECHARGING_THRESHOLD_VOL_100MV            0x00
#define REG04_BQ24190_RECHARGING_THRESHOLD_VOL_300MV            BIT(0)


/* Address:05h */
#define REG05_BQ24190_ADDRESS                                   0x05

#define REG05_BQ24190_TERMINATION_MASK                          BIT(7)
#define REG05_BQ24190_TERMINATION_DISABLE                       0x00
#define REG05_BQ24190_TERMINATION_ENABLE                        BIT(7)

#define REG05_BQ24190_TERMINATION_STAT_MASK                     BIT(6)
#define REG05_BQ24190_TERMINATION_STAT_DISABLE                  0x00
#define REG05_BQ24190_TERMINATION_STAT_ENABLE                   BIT(6)

#define REG05_BQ24190_I2C_WATCHDOG_TIME_MASK                    (BIT(5) | BIT(4))
#define REG05_BQ24190_I2C_WATCHDOG_TIME_DISABLE                 0x00
#define REG05_BQ24190_I2C_WATCHDOG_TIME_40S                     BIT(4)
#define REG05_BQ24190_I2C_WATCHDOG_TIME_80S                     BIT(5)
#define REG05_BQ24190_I2C_WATCHDOG_TIME_160S                    (BIT(5) | BIT(4))

#define REG05_BQ24190_CHARGING_SAFETY_TIME_MASK                 BIT(3)
#define REG05_BQ24190_CHARGING_SAFETY_TIME_DISABLE              0x00
#define REG05_BQ24190_CHARGING_SAFETY_TIME_ENABLE               BIT(3)

#define REG05_BQ24190_FAST_CHARGING_TIMEOUT_MASK                (BIT(2) | BIT(1))
#define REG05_BQ24190_FAST_CHARGING_TIMEOUT_5H                  0x00
#define REG05_BQ24190_FAST_CHARGING_TIMEOUT_8H                  BIT(1)
#define REG05_BQ24190_FAST_CHARGING_TIMEOUT_12H                 BIT(2)
#define REG05_BQ24190_FAST_CHARGING_TIMEOUT_20H                 (BIT(2) | BIT(1)


/* Address:06h */
#define REG06_BQ24190_ADDRESS                                   0x06

#define REG06_BQ24190_COMPENSATION_RESISTOR_MASK                (BIT(7) | BIT(6) | BIT(5))
#define REG06_BQ24190_COMPENSATION_RESISTOR_0MO                 0x00
#define REG06_BQ24190_COMPENSATION_RESISTOR_10MO                BIT(5)
#define REG06_BQ24190_COMPENSATION_RESISTOR_20MO                BIT(6)
#define REG06_BQ24190_COMPENSATION_RESISTOR_30MO                (BIT(6) | BIT(5))
#define REG06_BQ24190_COMPENSATION_RESISTOR_40MO                BIT(7)
#define REG06_BQ24190_COMPENSATION_RESISTOR_50MO                (BIT(7) | BIT(5))
#define REG06_BQ24190_COMPENSATION_RESISTOR_60MO                (BIT(7) | BIT(6))
#define REG06_BQ24190_COMPENSATION_RESISTOR_70MO                (BIT(7) | BIT(6) | BIT(5))

#define REG06_BQ24190_COMPENSATION_VOLTAGE_MASK                (BIT(4) | BIT(3) | BIT(2))
#define REG06_BQ24190_COMPENSATION_VOLTAGE_0MV                 0x00
#define REG06_BQ24190_COMPENSATION_VOLTAGE_16MV                BIT(2)
#define REG06_BQ24190_COMPENSATION_VOLTAGE_32MV                BIT(3)
#define REG06_BQ24190_COMPENSATION_VOLTAGE_48MV                (BIT(3) | BIT(2))
#define REG06_BQ24190_COMPENSATION_VOLTAGE_64MV                BIT(4)
#define REG06_BQ24190_COMPENSATION_VOLTAGE_80MV                (BIT(4) | BIT(2))
#define REG06_BQ24190_COMPENSATION_VOLTAGE_96MV                (BIT(4) | BIT(3))
#define REG06_BQ24190_COMPENSATION_VOLTAGE_112MV                (BIT(4) | BIT(3) | BIT(2))

#define REG06_BQ24190_TEMP_THRESHOLD_MASK                       (BIT(1) | BIT(0))
#define REG06_BQ24190_TEMP_THRESHOLD_60C                        0x00
#define REG06_BQ24190_TEMP_THRESHOLD_80C                        BIT(0)
#define REG06_BQ24190_TEMP_THRESHOLD_100C                       BIT(1)
#define REG06_BQ24190_TEMP_THRESHOLD_120C                       (BIT(1) | BIT(0))


/* Address:07h */
#define REG07_BQ24190_ADDRESS                                   0x07


/* Address:08h */
#define REG08_BQ24190_ADDRESS                                   0x08

#define REG08_BQ24190_VBUS_STAT_MASK                            (BIT(7) | BIT(6))
#define REG08_BQ24190_VBUS_STAT_UNKNOWN                         0x00
#define REG08_BQ24190_VBUS_STAT_USB_HOST_MODE                   BIT(6)
#define REG08_BQ24190_VBUS_STAT_AC_HOST_MODE                    BIT(7)
#define REG08_BQ24190_VBUS_STAT_OTG_MODE                        (BIT(7) | BIT(6))

#define REG08_BQ24190_CHARGING_STATUS_CHARGING_MASK             (BIT(5) | BIT(4))
#define REG08_BQ24190_CHARGING_STATUS_NO_CHARGING               0x00
#define REG08_BQ24190_CHARGING_STATUS_PRE_CHARGING              BIT(4)
#define REG08_BQ24190_CHARGING_STATUS_FAST_CHARGING             BIT(5)
#define REG08_BQ24190_CHARGING_STATUS_TERM_CHARGING             (BIT(5) | BIT(4))

#define REG08_BQ24190_CHARGING_STATUS_DPM_MASK                  BIT(3)
#define REG08_BQ24190_CHARGING_STATUS_DPM_OUT                   0x00
#define REG08_BQ24190_CHARGING_STATUS_DPM_IN                    BIT(3)

#define REG08_BQ24190_CHARGING_STATUS_POWER_MASK                BIT(2)
#define REG08_BQ24190_CHARGING_STATUS_POWER_OUT                 0x00
#define REG08_BQ24190_CHARGING_STATUS_POWER_IN                  BIT(2)


/* Address:09h */
#define REG09_BQ24190_ADDRESS                                   0x09

#define REG09_BQ24190_WDT_FAULT_MASK                            BIT(7)
#define REG09_BQ24190_WDT_FAULT_NORMAL                          0x00
#define REG09_BQ24190_WDT_FAULT_EXPIRATION                      BIT(7)

#define REG09_BQ24190_CHARGING_MASK                             (BIT(5) | BIT(4))
#define REG09_BQ24190_CHARGING_NORMAL                           0x00
#define REG09_BQ24190_CHARGING_INPUT_ERROR                      BIT(4)
#define REG09_BQ24190_CHARGING_THER_SHUTDOWN                    BIT(5)
#define REG09_BQ24190_CHARGING_TIMEOUT_ERROR                    (BIT(5) | BIT(4))

#define REG09_BQ24190_BATTERY_VOLATGE_MASK                      BIT(3)
#define REG09_BQ24190_BATTERY_VOLATGE_HIGH_ERROR                BIT(3)

#define REG09_BQ24190_BATTERY_TEMP_MASK                         (BIT(2) | BIT(1) | BIT(0))
#define REG09_BQ24190_BATTERY_TEMP_GOOD                         0x00
#define REG09_BQ24190_BATTERY_TEMP_LOW_ERROR                    (BIT(2) | BIT(0))
#define REG09_BQ24190_BATTERY_TEMP_HIGH_ERROR                   (BIT(2) | BIT(1))


/* Address:0Ah */
#define REG0A_BQ24190_ADDRESS                                   0x0A

// config register
#define BQ24190_LAST_CNFG_REG                                   0x07
// command register
#define BQ24190_FIRST_CMD_REG                                   0x08
#define BQ24190_LAST_CMD_REG                                    0x0A
// status register
#define BQ24190_FIRST_STATUS_REG                                0x0A
#define BQ24190_LAST_STATUS_REG                                 0x0A

#define BQ24190_FIRST_REG										0x00
#define BQ24190_LAST_REG										0x0A
#define BQ24190_REG_NUMBER										11

enum {
	OVERTIME_AC = 0,
	OVERTIME_USB,
	OVERTIME_DISABLED,
};

struct chip_bq24190 {
	struct i2c_client	*client;
	struct device		*dev;
	int				hw_aicl_point;
	int				sw_aicl_point;
	atomic_t			charger_suspended;
};

void bq24190_dump_registers(void);
int bq24190_kick_wdt(void);
int bq24190_hardware_init(void);
int bq24190_charging_current_set(void);
int bq24190_input_current_limit_set(void);
int bq24190_float_voltage_write(int vfloat_mv);
int bq24190_enable_charging(void);
int bq24190_disable_charging(void);
int bq24190_suspend_charger(void);
int bq24190_unsuspend_charger(void);
int bq24190_reset_charger(void);
int bq24190_registers_read_full(void);
int bq24190_otg_enable(void);
int bq24190_otg_disable(void);

extern volatile bool chargin_hw_init_done_bq24190;

#ifdef CONFIG_OPLUS_CHARGER_MTK
//extern CHARGER_TYPE mt_charger_type_detection(void);
extern int mt_power_supply_type_check(void);
extern bool pmic_chrdet_status(void);
extern int battery_meter_get_charger_voltage(void);
extern int charger_pretype_get(void);

extern int get_rtc_spare_fg_value(void);
extern int set_rtc_spare_fg_value(int val);
extern int get_rtc_spare_oplus_fg_value(void);
extern int set_rtc_spare_oplus_fg_value(int val);

extern void mt_usb_connect(void);
extern void mt_usb_disconnect(void);

extern int mt_get_chargerid_volt (void);

//#ifdef CONFIG_MTK_HAFG_20
extern void mt_set_chargerid_switch_val(int value);
extern int mt_get_chargerid_switch_val(void);
extern int oplus_usb_switch_gpio_gpio_init(void);

//#endif /* CONFIG_OPLUS_CHARGER_MTK */

#if defined(CONFIG_OPLUS_CHARGER_MTK6763) || defined(CONFIG_OPLUS_CHARGER_MTK6771)
extern int oplus_battery_meter_get_battery_voltage(void);
extern bool meter_fg_30_get_battery_authenticate(void);
#endif /* CONFIG_OPLUS_CHARGER_MTK6763 */

#else /* CONFIG_OPLUS_CHARGER_MTK */
extern int qpnp_charger_type_get(void);
extern bool qpnp_lbc_is_usb_chg_plugged_in(void);
extern int qpnp_get_prop_charger_voltage_now(void);
extern int qpnp_get_prop_battery_voltage_now(void);
extern int qpnp_set_pmic_soc_memory(int soc);
extern int qpnp_get_pmic_soc_memory(void);
#endif /* CONFIG_OPLUS_CHARGER_MTK */

bool oplus_pmic_check_chip_is_null(void);

#endif /* __OPLUS_BQ24190_H__ */
