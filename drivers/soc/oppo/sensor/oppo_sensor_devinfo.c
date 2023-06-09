/************************************************************************************
** Copyright (C), 2008-2019, OPPO Mobile Comm Corp., Ltd
** VENDOR_EDIT
** File: oppo_sensor_devinfo.c
**
** Description:
**      Definitions for sensor devinfo.
**
** Version: 1.0
** Date created: 2019/09/14,17:02
** --------------------------- Revision History: ------------------------------------
* <version>     <date>      <author>        <desc>
**************************************************************************************/
#include "oppo_sensor_devinfo.h"
#include <soc/oplus/system/oppo_project.h>

struct sensor_info *g_chip = NULL;

struct proc_dir_entry *sensor_proc_dir = NULL;
static struct oppo_als_cali_data *gdata = NULL;

static struct devinfo _info[] = {
	{STK3A5X, "stk33502", "SensorTek"},
	{TCS3701, "tcs3701", "AMS"},
};
static char *als_feature[] = {
	"als-type",
	"is-unit-device",
	"is-als-dri",
	"als-factor",
	"is_als_initialed",
	"als_buffer_length"
};

int __attribute__((weak)) register_devinfo(char *name,
		struct manufacture_info *info)
{
	return 1;
}

struct delayed_work sensor_work;
__attribute__((weak)) void oppo_device_dir_redirect(struct sensor_info *chip)
{
	pr_info("%s oppo_device_dir_redirect \n", __func__);
};

static void parse_physical_sensor_common_dts(struct sensor_hw *hw,
		struct device_node *ch_node)
{
	int rc = 0;
	uint32_t chip_value = 0;
	rc = of_property_read_u32(ch_node, "sensor-name", &chip_value);

	if (rc) {
		hw->sensor_name = 0;
	} else {
		hw->sensor_name = chip_value;
	}

	rc = of_property_read_u32(ch_node, "bus-number", &chip_value);

	if (rc) {
		hw->bus_number = DEFAULT_CONFIG;//read from registry
	} else {
		hw->bus_number = chip_value;
	}

	rc = of_property_read_u32(ch_node, "sensor-direction", &chip_value);

	if (rc) {
		hw->direction = DEFAULT_CONFIG;//read from registry
	} else {
		hw->direction = chip_value;
	}

	rc = of_property_read_u32(ch_node, "irq-number", &chip_value);

	if (rc) {
		hw->irq_number = DEFAULT_CONFIG;//read from registry
	} else {
		hw->irq_number = chip_value;
	}

}

static void parse_magnetic_sensor_dts(struct sensor_hw *hw,
				      struct device_node *ch_node)
{
	int value = 0;
	int rc = 0;
	int i = 0;
	rc = of_property_read_u32(ch_node, "parameter-number", &value);

	if (!rc && value > 0 && value < PARAMETER_NUM) {
		if ((get_project() == 19328) || (get_project() == 19343)) {
			rc = of_property_read_u32_array(ch_node, "soft-mag-parameter-exception", &hw->feature.parameter[0], value);
			if (rc) {
				rc = of_property_read_u32_array(ch_node, "soft-mag-parameter", &hw->feature.parameter[0], value);
			}
		} else {
			rc = of_property_read_u32_array(ch_node, "soft-mag-parameter", &hw->feature.parameter[0], value);
		}
		for (i = 0; i < value; i++)
			SENSOR_DEVINFO_DEBUG("soft magnetic parameter[%d] : %d\n", i,
					     hw->feature.parameter[i]);
	} else {
		pr_info("parse soft magnetic parameter failed!\n");

	}
}

static void parse_proximity_sensor_dts(struct sensor_hw *hw,
				       struct device_node *ch_node)
{
	int value = 0;
	int rc = 0;
	int i = 0;
	char *param[] = {
		"low_step",
		"high_step",
		"low_limit",
		"high_limit",
		"dirty_low_step",
		"dirty_high_step",
		"ps_dirty_limit",
		"ps_ir_limit",
		"ps_adjust_min",
		"ps_adjust_max",
		"sampling_count",
		"step_max",
		"step_min",
		"step_div",
		"anti_shake_delta",
		"dynamic_cali_max",
		"raw2offset_radio",
		"offset_max",
		"offset_range_min",
		"offset_range_max",
		"force_cali_limit",
		"cali_jitter_limit",
		"cal_offset_margin",
	};
	rc = of_property_read_u32(ch_node, "ps-cail-type", &value);

	if (!rc) {
		hw->feature.feature[0] = value;
	}

	rc = of_property_read_u32(ch_node, "ps-type", &value);

	if (!rc) {
		hw->feature.feature[1] = value;
	}

	rc = of_property_read_u32(ch_node, "is_ps_initialzed", &value);

	if (!rc) {
		hw->feature.feature[2] = value;
	}

	for (i = 0; i < ARRAY_SIZE(param); i++) {
		rc = of_property_read_u32(ch_node, param[i], &value);

		if (!rc) {
			hw->feature.parameter[i] = value;
		}

		SENSOR_DEVINFO_DEBUG("parameter[%d] : %d\n", i, hw->feature.parameter[i]);
	}


	SENSOR_DEVINFO_DEBUG("ps-cail-type:%d ps-type:%d is_ps_initialzed:%d\n",
			     hw->feature.feature[0], hw->feature.feature[1], hw->feature.feature[2]);
}

static void parse_light_sensor_dts(struct sensor_hw *hw,
				   struct device_node *ch_node)
{
	int rc = 0;
	int value = 0;
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(als_feature); i++) {
		rc = of_property_read_u32(ch_node, als_feature[i], &value);

		if (!rc) {
			hw->feature.feature[i] = value;
		} else {
			pr_info("parse %s failed!", als_feature[i]);
		}

		if(!strcmp(als_feature[i],"als-factor")) {
			SENSOR_DEVINFO_DEBUG("handle als-factor\n");
			if(strstr(saved_command_line, "dsi_nt36672a_tm_vid_display")) {
				rc = of_property_read_u32(ch_node, "tm-als-factor", &value);
				if (!rc) {
					hw->feature.feature[i] = value;
				} else {
					pr_info("parse tm-als-factor fail!");
				}
			}
			else if(strstr(saved_command_line, "dsi_hx83112a_huaxing_vid_display") 
				|| strstr(saved_command_line, "dsi_hx83112a_dongshan_vid_display")
				|| strstr(saved_command_line, "dsi_hx83112a_boe_vid_display")) {
				rc = of_property_read_u32(ch_node, "boe-als-factor", &value);
				if (!rc) {
					hw->feature.feature[i] = value;
				} else {
					pr_info("parse boe-als-factor fail!");
				}
			}
			else { //homer default boe 
				rc = of_property_read_u32(ch_node, "boe-als-factor", &value);
				if(!rc) {
					hw->feature.feature[i] = value;
				}
			}
		}

		SENSOR_DEVINFO_DEBUG("feature[%d] : %d\n", i, hw->feature.feature[i]);
	}
}

static void parse_sar_sensor_dts(struct sensor_hw *hw,
				 struct device_node *ch_node)
{
	int i = 0;
	int rc = 0;
	int value = 0;
	rc = of_property_read_u32(ch_node, "parameter-number", &value);

	if (!rc && value > 0 && value < PARAMETER_NUM) {
		rc = of_property_read_u32_array(ch_node,
						"sensor-reg", &hw->feature.parameter[0], value);

		for (i = 0; i < value / 2; i++) {
			SENSOR_DEVINFO_DEBUG("sensor reg 0x%x = 0x%x\n", hw->feature.parameter[i * 2],
					     hw->feature.parameter[2 * i + 1]);
		}

	} else {
		pr_info("parse sar sensor reg failed\n");
	}

}

static void parse_color_temperature_sensor_dts(struct sensor_hw *hw,
		struct device_node *ch_node)
{
	int rc = 0;
	int value = 0;
	rc = of_property_read_u32(ch_node, "cfg-num", &value);

	if (!rc) {
		hw->feature.parameter[0] = value;
	}

	SENSOR_DEVINFO_DEBUG("cctsensor cfg-num: %d\n", hw->feature.parameter[0]);
}

static void parse_each_physical_sensor_dts(struct sensor_hw *hw,
		struct device_node *ch_node)
{
	if (0 == strncmp(ch_node->name, "msensor", 7)) {
		parse_magnetic_sensor_dts(hw, ch_node);
	} else if (0 == strncmp(ch_node->name, "psensor", 7)) {
		parse_proximity_sensor_dts(hw, ch_node);
	} else if (0 == strncmp(ch_node->name, "lsensor", 7)) {
		parse_light_sensor_dts(hw, ch_node);
	} else if (0 == strncmp(ch_node->name, "ssensor", 7)) {
		parse_sar_sensor_dts(hw, ch_node);
	} else if (0 == strncmp(ch_node->name, "cctsensor", 7)) {
		parse_color_temperature_sensor_dts(hw, ch_node);
	} else {
		//do nothing
	}

}

static void parse_pickup_sensor_dts(struct sensor_algorithm *algo,
				    struct device_node *ch_node)
{
	int rc = 0;
	int value = 0;
	rc = of_property_read_u32(ch_node, "is-need-prox", &value);

	if (!rc) {
		algo->feature[0] = value;
	}

	rc = of_property_read_u32(ch_node, "prox-type", &value);

	if (!rc) {
		algo->parameter[0] = value;
	}

	SENSOR_DEVINFO_DEBUG("is-need-prox: %d, prox-type: %d\n",
			     algo->feature[0], algo->parameter[0]);
}

static void parse_lux_aod_sensor_dts(struct sensor_algorithm *algo,
				     struct device_node *ch_node)
{
	int rc = 0;
	int value = 0;
	rc = of_property_read_u32(ch_node, "thrd-low", &value);

	if (!rc) {
		algo->parameter[0] = value;
	}

	rc = of_property_read_u32(ch_node, "thrd-high", &value);

	if (!rc) {
		algo->parameter[1] = value;
	}

	rc = of_property_read_u32(ch_node, "als-type", &value);

	if (!rc) {
		algo->parameter[2] = value;
	}

	SENSOR_DEVINFO_DEBUG("thrd-low: %d, thrd-high: %d, als-type: %d\n",
			     algo->parameter[0], algo->parameter[1], algo->parameter[2]);

}

static void parse_fp_display_sensor_dts(struct sensor_algorithm *algo,
					struct device_node *ch_node)
{
	int rc = 0;
	int value = 0;
	rc = of_property_read_u32(ch_node, "prox-type", &value);

	if (!rc) {
		algo->parameter[0] = value;
	}

	SENSOR_DEVINFO_DEBUG("prox-type :%d\n", algo->parameter[0]);
}

static void parse_each_virtual_sensor_dts(struct sensor_algorithm *algo,
		struct device_node *ch_node)
{
	if (0 == strncmp(ch_node->name, "pickup", 6)) {
		parse_pickup_sensor_dts(algo, ch_node);
	} else if (0 == strncmp(ch_node->name, "lux_aod", 6)) {
		parse_lux_aod_sensor_dts(algo, ch_node);
	} else if (0 == strncmp(ch_node->name, "fp_display", 6)) {
		parse_fp_display_sensor_dts(algo, ch_node);
	} else {
		// do nothing
	}

}

static void oppo_sensor_parse_dts(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct sensor_info *chip = platform_get_drvdata(pdev);
	int rc = 0;
	int value = 0;
	bool is_virtual_sensor = false;
	struct device_node *ch_node = NULL;
	int sensor_type = 0;
	int sensor_index = 0;
	struct sensor_hw *hw = NULL;
	struct sensor_algorithm *algo = NULL;
	pr_info("start \n");

	for_each_child_of_node(node, ch_node) {
		is_virtual_sensor = false;

		if (of_property_read_bool(ch_node, "is-virtual-sensor")) {
			is_virtual_sensor = true;
		}

		rc = of_property_read_u32(ch_node, "sensor-type", &value);

		if (rc || (is_virtual_sensor && value >= SENSOR_ALGO_NUM)
				|| value >= SENSORS_NUM) {
			pr_info("parse sensor type failed!\n");
			continue;
		} else {
			sensor_type = value;
		}

		if (!is_virtual_sensor) {
			chip->s_vector[sensor_type].sensor_id = sensor_type;
			rc = of_property_read_u32(ch_node, "sensor-index", &value);

			if (rc || value >= SOURCE_NUM) {
				pr_info("parse sensor index failed!\n");
				continue;
			} else {
				sensor_index = value;
			}

			hw = &chip->s_vector[sensor_type].hw[sensor_index];
			parse_physical_sensor_common_dts(hw, ch_node);
			if ((get_project() == 19328) || (get_project() == 19343)) {
				if (sensor_type == 2) {
					chip->s_vector[sensor_type].hw[sensor_index].direction = 0;
				}
			}
			SENSOR_DEVINFO_DEBUG("chip->s_vector[%d].hw[%d] : sensor-name %d,\
						bus-number %d, sensor-direction %d,\
						irq-number %d\n",
					     sensor_type, sensor_index,
					     chip->s_vector[sensor_type].hw[sensor_index].sensor_name,
					     chip->s_vector[sensor_type].hw[sensor_index].bus_number,
					     chip->s_vector[sensor_type].hw[sensor_index].direction,
					     chip->s_vector[sensor_type].hw[sensor_index].irq_number);
			parse_each_physical_sensor_dts(hw, ch_node);
		} else {
			chip->a_vector[sensor_type].sensor_id = sensor_type;
			SENSOR_DEVINFO_DEBUG("chip->a_vector[%d].sensor_id : sensor_type %d",
					     sensor_type, chip->a_vector[sensor_type].sensor_id, sensor_type);
			algo = &chip->a_vector[sensor_type];
			parse_each_virtual_sensor_dts(algo, ch_node);
		}
	}//for_each_child_of_node

	rc = of_property_read_u32(node, "als-row-coe", &value);

	if (rc) {
		gdata->row_coe = 1000;
	} else {
		gdata->row_coe = value;
	}

	oppo_device_dir_redirect(chip);
}

static void sensor_dev_work(struct work_struct *work)
{
	int i = 0;
	int ret = 0;

	if (!g_chip) {
		pr_info("g_chip null\n");
		return;
	}

	pr_info("%s  match_id %d\n", __func__,
		g_chip->s_vector[OPPO_PROXIMITY].hw[0].sensor_name);

	//need check sensor inited
	for (i = 0; i < sizeof(_info) / sizeof(struct devinfo); i++) {
		if (_info[i].id == g_chip->s_vector[OPPO_PROXIMITY].hw[0].sensor_name) {
			do {
				ret = register_device_proc("Sensor_alsps", _info[i].ic_name,
							   _info[i].vendor_name);
				pr_info("%s ret %d\n", __func__, ret);
				msleep(5000);
			} while (--retry_count && ret);

			break;
		}
	}
}

static ssize_t als_type_read_proc(struct file *file, char __user *buf,
				  size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!g_chip) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d",
		      g_chip->s_vector[OPPO_LIGHT].hw[0].feature.feature[0]);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}

static struct file_operations als_type_fops = {
	.read = als_type_read_proc,
};

static ssize_t red_max_lux_read_proc(struct file *file, char __user *buf,
				     size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->red_max_lux);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t red_max_lux_write_proc(struct file *file, const char __user *buf,
				      size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->red_max_lux) {
		gdata->red_max_lux = input;
	}

	return count;
}
static struct file_operations red_max_lux_fops = {
	.read = red_max_lux_read_proc,
	.write = red_max_lux_write_proc,
};
static ssize_t white_max_lux_read_proc(struct file *file, char __user *buf,
				       size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->white_max_lux);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t white_max_lux_write_proc(struct file *file,
					const char __user *buf,
					size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->white_max_lux) {
		gdata->white_max_lux = input;
	}

	return count;
}
static struct file_operations white_max_lux_fops = {
	.read = white_max_lux_read_proc,
	.write = white_max_lux_write_proc,
};
static ssize_t blue_max_lux_read_proc(struct file *file, char __user *buf,
				      size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->blue_max_lux);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t blue_max_lux_write_proc(struct file *file,
				       const char __user *buf,
				       size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->blue_max_lux) {
		gdata->blue_max_lux = input;
	}

	return count;
}
static struct file_operations blue_max_lux_fops = {
	.read = blue_max_lux_read_proc,
	.write = blue_max_lux_write_proc,
};
static ssize_t green_max_lux_read_proc(struct file *file, char __user *buf,
				       size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->green_max_lux);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t green_max_lux_write_proc(struct file *file,
					const char __user *buf,
					size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->green_max_lux) {
		gdata->green_max_lux = input;
	}

	return count;
}
static struct file_operations green_max_lux_fops = {
	.read = green_max_lux_read_proc,
	.write = green_max_lux_write_proc,
};
static ssize_t cali_coe_read_proc(struct file *file, char __user *buf,
				  size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->cali_coe);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t cali_coe_write_proc(struct file *file, const char __user *buf,
				   size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->cali_coe) {
		gdata->cali_coe = input;
	}

	return count;
}
static struct file_operations cali_coe_fops = {
	.read = cali_coe_read_proc,
	.write = cali_coe_write_proc,
};
static ssize_t row_coe_read_proc(struct file *file, char __user *buf,
				 size_t count, loff_t *off)
{
	char page[256] = {0};
	int len = 0;

	if (!gdata) {
		return -ENOMEM;
	}

	len = sprintf(page, "%d", gdata->row_coe);

	if (len > *off) {
		len -= *off;
	} else {
		len = 0;
	}

	if (copy_to_user(buf, page, (len < count ? len : count))) {
		return -EFAULT;
	}

	*off += len < count ? len : count;
	return (len < count ? len : count);
}
static ssize_t row_coe_write_proc(struct file *file, const char __user *buf,
				  size_t count, loff_t *off)

{
	char page[256] = {0};
	unsigned int input = 0;

	if (!gdata) {
		return -ENOMEM;
	}


	if (count > 256) {
		count = 256;
	}

	if (count > *off) {
		count -= *off;
	} else {
		count = 0;
	}

	if (copy_from_user(page, buf, count)) {
		return -EFAULT;
	}

	*off += count;

	if (sscanf(page, "%u", &input) != 1) {
		count = -EINVAL;
		return count;
	}

	if (input != gdata->row_coe) {
		gdata->row_coe = input;
	}

	return count;
}
static struct file_operations row_coe_fops = {
	.read = row_coe_read_proc,
	.write = row_coe_write_proc,
};

static int oppo_devinfo_probe(struct platform_device *pdev)
{
	struct sensor_info *chip = NULL;
	size_t smem_size = 0;
	void *smem_addr = NULL;
	int rc = 0;
	struct proc_dir_entry *pentry;
	struct oppo_als_cali_data *data = NULL;

	pr_info("%s call\n", __func__);

	smem_addr = qcom_smem_get(QCOM_SMEM_HOST_ANY,
				  SMEM_SENSOR,
				  &smem_size);

	if (IS_ERR(smem_addr)) {
		pr_err("unable to acquire smem SMEM_SENSOR entry\n");
		return -EPROBE_DEFER;
	}

	chip = (struct sensor_info *)(smem_addr);

	if (chip == ERR_PTR(-EPROBE_DEFER)) {
		chip = NULL;
		pr_err("unable to acquire entry\n");
		return -ENOMEM;
	}

	memset(chip, 0, sizeof(struct sensor_info));

	if (gdata) {
		printk("%s:just can be call one time\n", __func__);
		return 0;
	}

	data = kzalloc(sizeof(struct oppo_als_cali_data), GFP_KERNEL);

	if (data == NULL) {
		rc = -ENOMEM;
		printk("%s:kzalloc fail %d\n", __func__, rc);
		return rc;
	}

	gdata = data;

	platform_set_drvdata(pdev, chip);

	oppo_sensor_parse_dts(pdev);

	INIT_DELAYED_WORK(&sensor_work, sensor_dev_work);
	g_chip = chip;

	schedule_delayed_work(&sensor_work, msecs_to_jiffies(SENSOR_DEVINFO_SYNC_TIME));
	pr_info("%s success\n", __func__);

	if (gdata->proc_oppo_als) {
		printk("proc_oppo_als has alread inited\n");
		return 0;
	}

        sensor_proc_dir =  proc_mkdir("sensor", NULL);

	if (!sensor_proc_dir) {
		pr_err("can't create sensor_proc_dir proc\n");
		rc = -EFAULT;
		return rc;
	}

        gdata->proc_oppo_als =  proc_mkdir("als_cali", sensor_proc_dir);

        if (!gdata->proc_oppo_als) {
                pr_err("can't create proc_oppo_als proc\n");
                rc = -EFAULT;
                return rc;
        }

	pentry = proc_create("red_max_lux", 0666, gdata->proc_oppo_als,
			     &red_max_lux_fops);

	if (!pentry) {
		pr_err("create red_max_lux proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("green_max_lux", 0666, gdata->proc_oppo_als,
			     &green_max_lux_fops);

	if (!pentry) {
		pr_err("create green_max_lux proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("blue_max_lux", 0666, gdata->proc_oppo_als,
			     &blue_max_lux_fops);

	if (!pentry) {
		pr_err("create blue_max_lux proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("white_max_lux", 0666, gdata->proc_oppo_als,
			     &white_max_lux_fops);

	if (!pentry) {
		pr_err("create white_max_lux proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("cali_coe", 0666, gdata->proc_oppo_als,
			     &cali_coe_fops);

	if (!pentry) {
		pr_err("create cali_coe proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("row_coe", 0666, gdata->proc_oppo_als,
			     &row_coe_fops);

	if (!pentry) {
		pr_err("create row_coe proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	pentry = proc_create("als_type", 0666, gdata->proc_oppo_als,
			     &als_type_fops);

	if (!pentry) {
		pr_err("create als_type_fops proc failed.\n");
		rc = -EFAULT;
		return rc;
	}

	return 0;
}

static int oppo_devinfo_remove(struct platform_device *pdev)
{
	if (gdata) {
		kfree(gdata);
		gdata = NULL;
	}

	return 0;
}

static const struct of_device_id of_drv_match[] = {
	{ .compatible = "oppo,sensor-devinfo"},
	{},
};
MODULE_DEVICE_TABLE(of, of_motor_match);

static struct platform_driver _driver = {
	.probe      = oppo_devinfo_probe,
	.remove     = oppo_devinfo_remove,
	.driver     = {
		.name   = "sensor_devinfo",
		.of_match_table = of_drv_match,
	},
};

static int __init oppo_devinfo_init(void)
{
	pr_info("oppo_devinfo_init call\n");

	platform_driver_register(&_driver);
	return 0;
}

core_initcall(oppo_devinfo_init);

MODULE_DESCRIPTION("sensor devinfo");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Murphy@oppo.com");

