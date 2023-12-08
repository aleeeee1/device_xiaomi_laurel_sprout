LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemovePackages
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
	AmbientSensePrebuilt \
	AppDirectedSMSService \
	arcore \
	BasicDreams \
	Calculator \
	Contacts \
	CalendarGooglePrebuilt \
	CalculatorGooglePrebuilt \
	Camera2 \
	CarrierSetup \
	Chrome \
	Duo \
	Chrome-Stub \
	ConnMO \
	DCMO \
	DMService \
	DevicePolicyPrebuilt \
	DiagnosticsToolPrebuilt \
	Drive \
	DeskClockGoogle \
	FilesPrebuilt \
	FilesGoogle \
	GCS \
	Gallery2 \
	GoogleCamera \
	GoogleContacts \
	GoogleContactsSyncAdapter \
	GoogleTTS \
	LocationHistoryPrebuilt \
	LatinImeGoogle \
	HelpRtcPrebuilt \
	Keep \
	Maps \
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
	PixelSetupWizard \
	PrebuiltGmail \
	PrebuiltBugle \
	PrebuiltDeskClockGoogle \
	RecorderPrebuilt \
	SCONE \
	ScribePrebuilt \
	Showcase \
	Snap \
	Snap2 \
	SnapdragonCamera \
	SoundAmplifierPrebuilt \
	SprintDM \
	SafetyHubPrebuilt \
 	SprintHM \
	Tycho \
	talkback \
	TagGoogle \
	LatinImeGoogle \
	USCCDM \
	VZWAPNLib \
	ViaBrowser \
	Videos \
	VZWAPNLib \
	Velvet \
	VzwOmaTriger \
	VzwOmaTrigger \
	YouTube \
	YouTubeMusicPrebuilt \
	YTMusic \
	WallpaperCropper \


LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)
