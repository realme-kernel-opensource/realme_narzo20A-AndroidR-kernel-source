#
# Makefile for the touchscreen drivers.
#

# Each configuration option enables a list of files.
ifeq ($(SHIPPING_API_LEVEL), 28)
obj-$(CONFIG_TOUCHPANEL_NOVA) += novatek_common.o
else
obj-$(CONFIG_TOUCHPANEL_NOVA) += novatek_common.o
endif
obj-$(CONFIG_TOUCHPANEL_NOVA_NT36525B_NOFLASH) += NT36525B_noflash/
obj-$(CONFIG_TOUCHPANEL_NOVA_NT36672A_NOFLASH) += NT36672A_noflash/
#endif