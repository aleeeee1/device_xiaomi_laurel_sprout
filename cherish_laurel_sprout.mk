#
# Copyright (C) 2018-2019 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit some common Lineage stuff
$(call inherit-product, vendor/cherish/config/common_full_phone.mk)

SKIP_ABI_CHECKS := true

# Inherit from laurel_sprout device
$(call inherit-product, $(LOCAL_PATH)/device.mk)


PRODUCT_BRAND := Xiaomi
PRODUCT_DEVICE := laurel_sprout
PRODUCT_MANUFACTURER := Xiaomi
PRODUCT_NAME := cherish_laurel_sprout
PRODUCT_MODEL := Mi A3

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

TARGET_VENDOR_PRODUCT_NAME := laurel_sprout

BUILD_FINGERPRINT := Xiaomi/laurel_sprout/laurel_sprout:11/RKQ1.200903.002/V12.0.26.0.RFQMIXM:user/release-keys

# FOD Animation
EXTRA_UDFPS_ANIMATIONS := true
EXTRA_FOD_ANIMATIONS := true
HAS_FOD := true

# Props
WITH_GMS := true
TARGET_BOOT_ANIMATION_RES := 720
TARGET_SUPPORTS_GOOGLE_RECORDER := true
TARGET_GAPPS_ARCH := arm64
TARGET_SUPPORTS_QUICK_TAP := true
TARGET_FACE_UNLOCK_SUPPORTED := true
TARGET_SUPPORTS_CALL_RECORDING := true
TARGET_INCLUDE_LIVE_WALLPAPERS := true

# Pixel charging animation
TARGET_INCLUDE_PIXEL_CHARGER := true


# Cherish
CHERISH_MAINTAINER := BASUBHAJANTRI
CHERISH_CHIPSET := SM6125
CHERISH_BATTERY := 4030mAh
CHERISH_DISPLAY := 1560x720
