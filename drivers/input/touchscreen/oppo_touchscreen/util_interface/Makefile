#
# Makefile for the touchscreen drivers.
#

# Each configuration option enables a list of files.

obj-$(CONFIG_TOUCHPANEL_OPPO) += touch_interfaces.o

ifeq ($(SHIPPING_API_LEVEL), 28)
ccflags-y += -DSHIPPING_API_LEVEL=29
else
ccflags-y += -DSHIPPING_API_LEVEL=29
endif
#endif
