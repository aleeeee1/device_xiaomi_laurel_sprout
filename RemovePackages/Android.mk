LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemovePackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
        Chrome-Stub \
        Chrome \
        Drive \
        Maps \
        Photos \
        PrebuiltGmail \
        Videos \
        YouTube \
        FilesPrebuilt \
        AndroidAutoStubPrebuilt \
        AmbientSensePrebuilt \
	AppDirectedSMSService \
	CalendarGooglePrebuilt \
	Camera2 \
	CarrierSetup \
	ConnMO \
	DCMO \
	DMService \
	DevicePolicyPrebuilt \
	DiagnosticsToolPrebuilt \
	SafetyHubPrebuilt \
	HelpRtcPrebuilt \
	GCS \
	MyVerizonServices \
	NgaResources \
	OBDM_Permissions \
	OemDmTrigger \
	PixelLiveWallpaperPrebuilt \
	PixelWallpapers2021 \
	Music \
	RecorderPrebuilt \
	ScribePrebuilt \
	Showcase \
	SoundAmplifierPrebuilt \
	SprintDM \
	SprintHM \
	Tycho \
	USCCDM \
	VZWAPNLib \
        SCONE \
        YouTubeMusicPrebuilt \
        arcore \
	VzwOmaTriger

LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)