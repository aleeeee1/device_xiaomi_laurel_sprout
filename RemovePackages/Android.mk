LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemovePackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
	AmbientSensePrebuilt \
	AndroidAutoStubPrebuilt \
	AppDirectedSMSService \
	arcore \
	CalendarGooglePrebuilt \
	CalculatorGooglePrebuilt \
	Camera2 \
	CarrierSetup \
	Chrome \
	Chrome-Stub \
	ConnMO \
	DCMO \
	DMService \
	DevicePolicyPrebuilt \
	DiagnosticsToolPrebuilt \
	Drive \
	FilesPrebuilt \
	GCS \
	Gallery2 \
	GoogleCamera \
	GoogleContacts \
	GoogleContactsSyncAdapter \
	GoogleTTS \
	LocationHistoryPrebuilt \
	HelpRtcPrebuilt \
	Maps \
	MarkupGoogle \
	Music \
	MyVerizonServices \
	NgaResources \
	OBDM_Permissions \
	obdm_stub \
	OdadPrebuilt \
	OemDmTrigger \
	Photos \
	PixelBuds \
	PixelLiveWallpaperPrebuilt \
	PixelWallpapers2021 \
	PrebuiltGmail \
	PrebuiltBugle \
	PrebuiltDeskClockGoogle
	RecorderPrebuilt \
	SCONE \
	SafetyHubPrebuilt \
	ScribePrebuilt \
	Showcase \
	Snap \
	Snap2 \
	SnapdragonCamera \
	SoundAmplifierPrebuilt \
	SprintDM \
	SprintHM \
	Tycho \
	USCCDM \
	VZWAPNLib \
	ViaBrowser \
	Videos \
	VzwOmaTriger \
	VzwOmaTrigger \
	YouTube \
	YouTubeMusicPrebuilt \

LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)