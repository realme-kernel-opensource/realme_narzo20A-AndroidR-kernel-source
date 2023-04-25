# SPDX-License-Identifier: GPL-2.0
ifeq ($(CONFIG_BUILD_ARM64_DT_OVERLAY),y)
	dtbo-$(CONFIG_ARCH_TRINKET) += \
		trinket-rumi-overlay.dtbo \
		trinket-idp-overlay.dtbo \
		trinket-qrd-overlay.dtbo \
		trinket-external-codec-idp-overlay.dtbo \
		trinket-usbc-external-codec-idp-overlay.dtbo \
		trinket-usbc-idp-overlay.dtbo \
		trinket-dp-idp-overlay.dtbo

trinket-rumi-overlay.dtbo-base := trinket.dtb
trinket-idp-overlay.dtbo-base := trinket.dtb
trinket-qrd-overlay.dtbo-base := trinket.dtb
trinket-external-codec-idp-overlay.dtbo-base := trinket.dtb
trinket-usbc-external-codec-idp-overlay.dtbo-base := trinket.dtb
trinket-usbc-idp-overlay.dtbo-base := trinket.dtb
trinket-dp-idp-overlay.dtbo-base := trinket.dtb

dtbo-$(CONFIG_ARCH_TRINKET) += trinket-idp-overlay-19021.dtbo
trinket-idp-overlay-19021.dtbo-base := trinket-19021.dtb
dtbo-$(CONFIG_ARCH_TRINKET) += trinket-idp-overlay-19026.dtbo
trinket-idp-overlay-19026.dtbo-base := trinket-19026.dtb
	
dtbo-$(CONFIG_ARCH_TRINKET) += trinket-idp-overlay-19321.dtbo
trinket-idp-overlay-19321.dtbo-base := trinket-19321.dtb
	
dtbo-$(CONFIG_ARCH_TRINKET) += trinket-idp-overlay-19328.dtbo
trinket-idp-overlay-19328.dtbo-base := trinket-19328.dtb
else
dtb-$(CONFIG_ARCH_TRINKET)	+= trinket-rumi.dtb \
	trinket-idp.dtb \
	trinket-qrd.dtb \
	trinket-external-codec-idp.dtb \
	trinket-usbc-external-codec-idp.dtb \
	trinket-usbc-idp.dtb \
	trinket-dp-idp.dtb
	
dtb-$(CONFIG_ARCH_TRINKET)	+= trinket-idp-19021.dtb
dtb-$(CONFIG_ARCH_TRINKET)	+= trinket-idp-19026.dtb
dtb-$(CONFIG_ARCH_TRINKET)	+= trinket-idp-19321.dtb
dtb-$(CONFIG_ARCH_TRINKET)	+= trinket-idp-19328.dtb	
endif

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
