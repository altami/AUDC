#ifndef AUDCDEFINES_H
#define AUDCDEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short int AudcWChar;
typedef void* AudcHandle;
typedef long AudcInteger;
typedef double AudcDouble;

enum AudcErrorType
{
	AudcError = 0x1000,
};

enum AudcStatusCode
{
	AudcBadStream = 0x0001 | AudcError,
	AudcBadCamera = 0x0002 | AudcError,
	AudcDeviceAlreadyIsLinked = 0x0003 | AudcError,
	AudcDeviceNotLinkedYet = 0x0004 | AudcError,
	AudcBadHandle = 0x0005 | AudcError,
	AudcCallBackAlreadyRegistred = 0x0006 | AudcError,
	AudcCallBackNotRegistred = 0x0007 | AudcError,
	AudcUnknownError = 0x0008 | AudcError,
	AudcPropertyListIsEmpty = 0x0009 | AudcError,
	AudcInvalidPosition = 0x0010 | AudcError,
	AudcCannotRunStream = 0x0100 | AudcError,
	AudcCannotStopStream = 0x0101 | AudcError,
	AudcCannotTakeSnapshot = 0x0102| AudcError,
	AudcBufferIsEmpty = 0x0103 | AudcError,
	AudcStreamInternalError = 0x0104 | AudcError,
	AudcStillPinNotSupported = 0x0104 | AudcError,
	AudcInvalidPropertyType = 0x0016 | AudcError,
	AudcFailedToLink = 0x0017 | AudcError,
	AudcFailedToUnlink = 0x0018 | AudcError,
	AudcOperationSuccesfull = 0x0000
};

enum AudcPropertyType
{
	AudcRangeInt,
	AudcRangeDouble,
	AudcEnumeration,
	AudcAction
};

enum AudcPropertyState
{
	PropertyEnabled = 0,
	PropertyDisabled = 1
};

enum AudcPropID
{
	//exposure
	audcPropID_ExposureAuto = 0,
	audcPropID_ExposureTarget,
	audcPropID_ExposureGain,
	audcPropID_ExposureTime,
	audcPropID_InitExposure, // not available

	//white balance
	audcPropID_Temp,
	audcPropID_Tint,
	audcPropID_InitWB,

	//color
	audcPropID_Chrome,
	audcPropID_Hue,
	audcPropID_Saturation,
	audcPropID_Gamma,
	audcPropID_Brightness,
	audcPropID_Contrast,

	audcPropID_VignetAmount,
	audcPropID_VignetMidPoint,
	audcPropID_VignetEnable,

	//roi
	audcPropID_ShowRect,
	audcPropID_RectLeft,
	audcPropID_RectRight,
	audcPropID_RectBottom,
	audcPropID_RectTop,

	//misc
	audcPropID_FlipH,
	audcPropID_FlipV,
	audcPropID_FrameSpeed,
	audcPropID_LightFreq,
};


struct AudcModeInfo
{
	AudcWChar *name;
	AudcInteger width;
	AudcInteger height;
};

struct AudcDeviceInfo
{
	AudcWChar  *vendorName;
	AudcWChar  *modelName;
};

struct AudcRangeProperty
{
	AudcInteger minValue;
	AudcInteger maxValue;
	AudcDouble minValueDouble;
	AudcDouble maxValueDouble;
};

struct AudcEnumerationItem
{
	AudcWChar * itemName;
};

struct AudcEnumerationProperty
{
	AudcEnumerationItem *values;
	AudcInteger count;
};

struct AudcPropertyInfo
{
	union
	{
		AudcRangeProperty *range;
		AudcEnumerationProperty *enumeration;
	};

	AudcWChar * name;
	AudcPropertyType type;
};

typedef AudcStatusCode(*audcCBDeviceListUpdated)( void *d );
typedef AudcStatusCode(*audcCBFrameArrived)( AudcHandle deviceHandle, AudcHandle bufferHandle, AudcInteger rasterSize , void *d );
typedef AudcStatusCode(*audcCBStillCaptureFrameArrived)( AudcHandle deviceHandle, AudcHandle bufferHandle, AudcInteger rasterSize , void *d );
typedef AudcStatusCode(*audcCBPropertyChanged)(AudcHandle deviceHandle, AudcHandle propertyHandle, void *d);
typedef AudcStatusCode(*audcCBUpdateDeviceProperty)(AudcHandle deviceHandle,void *d );
typedef AudcStatusCode(*audcCBPropertyStateChanged)(AudcHandle deviceHandle, AudcHandle propertyHandle, AudcPropertyState state, void *d);

#ifdef __cplusplus
};
#endif

#endif //AUDCDEFINES_H