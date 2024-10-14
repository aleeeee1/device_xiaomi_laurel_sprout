LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemovePackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
    Aperture \
    CalculatorGooglePrebuilt \
    CalendarGooglePrebuilt \
    Camera2 \
    DevicePolicyPrebuilt \
    GoogleContacts \
    GoogleTTS \
    Maps \
    Photos \
    PixelThemesStub \
    PixelThemesStub2022_and_newer \
    PrebuiltGmail \
    Snap \
    Snap2 \
    talkback \
    Velvet \
    YouTube \
    YouTubeMusicPrebuilt \
    YTMusic

LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)