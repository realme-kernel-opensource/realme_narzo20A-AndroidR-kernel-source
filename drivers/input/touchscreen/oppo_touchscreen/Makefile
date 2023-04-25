#
# Makefile for the touchscreen drivers.
#
subdir-ccflags-$(CONFIG_TOUCHPANEL_MTK_PLATFORM) += -I$(srctree)/drivers/misc/mediatek/include/

obj-$(CONFIG_TOUCHPANEL_OPPO) += util_interface/

ifeq ($(SHIPPING_API_LEVEL), 29)
obj-$(CONFIG_TOUCHPANEL_OPPO) += touchpanel_common_driver.o
else
obj-$(CONFIG_TOUCHPANEL_OPPO) += touchpanel_common_driver.o
endif

ifeq ($(SHIPPING_API_LEVEL), 28)
ccflags-y += -DSHIPPING_API_LEVEL=29
else
ccflags-y += -DSHIPPING_API_LEVEL=29
endif

obj-$(CONFIG_TOUCHPANEL_GOODIX) += Goodix/
obj-$(CONFIG_TOUCHPANEL_NOVA) += Novatek/
obj-$(CONFIG_TOUCHPANEL_HIMAX) += Himax/
obj-$(CONFIG_TOUCHPANEL_ILITEK) += ilitek/
