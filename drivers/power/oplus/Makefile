ifeq ($(CONFIG_OPLUS_CHARGER_MTK),y)
subdir-ccflags-y += -Werror
subdir-ccflags-y += -Wno-unused-variable
endif

obj-y      += charger_ic/
obj-y      += gauge_ic/
obj-y      += vooc_ic/
obj-y      += adapter_ic/

obj-y	+= oplus_charger.o
obj-y	+= oplus_gauge.o
obj-y	+= oplus_vooc.o
obj-y	+= oplus_adapter.o
obj-y	+= oplus_short.o
obj-y   += oplus_debug_info.o