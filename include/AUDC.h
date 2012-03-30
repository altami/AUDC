/****************************************************************************
**	Проект AUDC, версия 1.2, 22.08.2011
**	
**	ВНИМАНИЕ!
**	Прочтите внимательно лицензионный договор, идущий в составе комплекта разработчика.
**
**	Исключительные права принадлежат ООО "Альтами" <support@altami.ru>.
** 
*******************************************************************************/

#ifndef AUCD_H
#define AUCD_H

#ifdef AUDC_EXPORTS
#define AUDCAPI __declspec(dllexport)
#else
#define AUDCAPI __declspec(dllimport)
#endif

typedef unsigned short int AudcWChar;
typedef void* AudcHandle;
typedef long AudcInteger;

#ifdef __cplusplus
extern "C" {
#endif


enum AudcErrorType
{
	AudcError = 0x1000,
	AudcWarning = 0x2000,
	AudcNotice = 0x3000
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
	AudcCannotRunStream = 0x0011 | AudcError,
	AudcCannotStopStream = 0x0012 | AudcError,
	AudcBufferIsEmpty = 0x0013 | AudcError,
	AudcHasNoReturnValue = 0x0014 | AudcError,
	AudcInvalidPropertyType = 0x0015 | AudcError,
	AudcOperationSuccesfull = 0x0000
};


enum AudcPropertyType
{
	AudcRange,
	AudcEnumeration,
	AudcAction
};

enum AudcPropertyState
{
	PropertyEnabled = 0,
	PropertyDisabled = 1
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
    AudcWChar * unit;	
};


typedef AudcStatusCode(*audcCBDeviceListUpdated)( void *d );
typedef AudcStatusCode(*audcCBDeviceArrived)(AudcHandle arrivedDeviceHandle, void *d );
typedef AudcStatusCode(*audcCBDeviceRemoved)(AudcHandle removedDeviceHandle, void *d );
typedef AudcStatusCode(*audcCBFrameArrived)( AudcHandle deviceHandle, AudcHandle bufferHandle, AudcInteger rasterSize , void *d );
typedef AudcStatusCode(*audcCBModeChanged)(AudcHandle deviceHandle, AudcHandle newMode, void *d );
typedef AudcStatusCode(*audcCBPropertyChanged)(AudcHandle deviceHandle, AudcHandle propertyHandle, void *d);
typedef void (*audcMappingFunctionType)(AudcInteger value, AudcInteger * mapped );
typedef AudcStatusCode(*audcCBWhiteBalance)(AudcInteger gain[3], void *d); 
typedef AudcStatusCode(*audcCBHistogram)(AudcInteger aHistY[256], AudcInteger aHistR[256], AudcInteger aHistG[256], AudcInteger aHistB[256],void *d); //todo
typedef AudcStatusCode(*audcCBUpdateDeviceProperty)(AudcHandle deviceHandle,void *d );
typedef AudcStatusCode(*audcCBPropertyStateChanged)(AudcHandle deviceHandle, AudcHandle propertyHandle, AudcPropertyState state, void *d);

AudcStatusCode AUDCAPI audcGetDeviceCount( AudcInteger *count );
AudcStatusCode AUDCAPI audcGetDevice( AudcInteger position, AudcHandle *deviceHandle );
AudcStatusCode AUDCAPI audcGetDeviceInfo( AudcHandle deviceHandle, AudcDeviceInfo *info );
AudcStatusCode AUDCAPI audcLinkDevice( AudcHandle handle );
AudcStatusCode AUDCAPI audcUnLinkDevice( AudcHandle handle );
AudcStatusCode AUDCAPI audcDevicePropertiesCount( AudcHandle deviceHandle, AudcInteger *count ); 
AudcStatusCode AUDCAPI audcGetDeviceProperty( AudcInteger position, AudcHandle deviceHandle, AudcHandle *propertyHandle );

AudcStatusCode AUDCAPI audcGetPropertyInformation( AudcHandle propertyHandle, AudcPropertyInfo **info );
AudcStatusCode AUDCAPI audcGetPropertyValue( AudcHandle propertyHandle, AudcInteger *value );
AudcStatusCode AUDCAPI audcGetDefaultPropertyValue( AudcHandle propertyHandle, AudcInteger *value );
AudcStatusCode AUDCAPI audcSetPropertyValue( AudcHandle propertyHandle, AudcInteger value );
AudcStatusCode AUDCAPI audcExecActionProperty( AudcHandle propertyHandle );
AudcStatusCode AUDCAPI audcStopPropertyExec( AudcHandle propertyHandle );
AudcStatusCode AUDCAPI audcGetPropertyMapper( AudcHandle propertyHandle, audcMappingFunctionType * mapFunction );


AudcStatusCode AUDCAPI audcSupportedModesCount( AudcHandle deviceHandle, AudcInteger *modesCount );
AudcStatusCode AUDCAPI audcGetModeHandle( AudcHandle deviceHandle, AudcInteger position, AudcHandle *modeHandle );
AudcStatusCode AUDCAPI audcGetModeInfo( AudcHandle modeHandle, AudcModeInfo **info );
AudcStatusCode AUDCAPI audcGetCurrentMode( AudcHandle deviceHandle,  AudcHandle *modeHandle );
AudcStatusCode AUDCAPI audcSetCurrentMode( AudcHandle deviceHandle,  AudcHandle modeHandle );


AudcStatusCode AUDCAPI audcStartStream( AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcStopStream( AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcGetFrame( AudcHandle deviceHandle, AudcInteger *bufferSize, void **data );

AudcStatusCode AUDCAPI audcRegisterDeviceListUpdatedCB(audcCBDeviceListUpdated func, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceListUpdatedCB(audcCBDeviceListUpdated func );
AudcStatusCode AUDCAPI audcRegisterDeviceArrivedCB( audcCBDeviceArrived func, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceArrivedCB( audcCBDeviceArrived func );
AudcStatusCode AUDCAPI audcRegisterDeviceRemovedCB( audcCBDeviceRemoved func, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceRemovedCB( audcCBDeviceRemoved func );
AudcStatusCode AUDCAPI audcRegisterFrameArrivedCB( audcCBFrameArrived func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterFrameArrivedCB( audcCBFrameArrived func, AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcRegisterModeChangedCB( audcCBModeChanged func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterModeChangedCB( audcCBModeChanged func, AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcRegisterPropertyChangedCB( audcCBPropertyChanged func, AudcHandle propertyHandle, void * ctx);
AudcStatusCode AUDCAPI audcUnregisterPropertyChangedCB( audcCBPropertyChanged func, AudcHandle propertyHandle);
AudcStatusCode AUDCAPI audcRegisterWhiteBalanceCB( audcCBWhiteBalance func, AudcHandle deviceHandle, void * ctx);
AudcStatusCode AUDCAPI audcUnregisterWhiteBalanceCB( audcCBWhiteBalance func, AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcRegisterHistogramCB( audcCBHistogram func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterHistogramCB( audcCBHistogram func, AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcRegisterDeviceUpdatePropertiesCB( audcCBUpdateDeviceProperty func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceUpdatePropertiesCB( audcCBUpdateDeviceProperty func, AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcRegisterPropertyStateChangedCB( audcCBPropertyStateChanged func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterPropertyStateChangedCB( audcCBPropertyStateChanged func, AudcHandle deviceHandle );

audcMappingFunctionType AUDCAPI audcGetMapperFunction( AudcHandle propertyHandle );


bool AUDCAPI audcIsError( AudcStatusCode errorCode );
AudcWChar AUDCAPI audcErrorDescription( AudcStatusCode errorCode );

#ifdef __cplusplus
}
#endif

#endif // AUDC_H