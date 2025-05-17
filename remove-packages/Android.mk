LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemovePackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
    Aperture \
    CalculatorGooglePrebuilt_85005407 \
    CalendarGooglePrebuilt \
    Camera2 \
    Chrome \
    Chrome-Stub \
    DevicePolicyPrebuilt-v10052480 \
    GoogleContacts \
    Maps \
    Photos \
    PrebuiltGmail \
    RecorderPrebuilt_675788680 \
    Snap \
    Snap2 \
    Velvet \
    YouTube \
    YouTubeMusicPrebuilt \
    YTMusic

LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)