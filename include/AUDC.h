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

#include "AUDCDefines.h"

#ifdef __cplusplus
extern "C" {
#endif

AudcStatusCode AUDCAPI audcGetDeviceCount( AudcInteger *count );
AudcStatusCode AUDCAPI audcGetDevice( AudcInteger position, AudcHandle *deviceHandle );
AudcStatusCode AUDCAPI audcGetDeviceInfo( AudcHandle deviceHandle, AudcDeviceInfo *info );
AudcStatusCode AUDCAPI audcLinkDevice( AudcHandle handle );
AudcStatusCode AUDCAPI audcUnLinkDevice( AudcHandle handle );

AudcStatusCode AUDCAPI audcDevicePropertiesCount( AudcHandle deviceHandle, AudcInteger *count ); 
AudcStatusCode AUDCAPI audcGetDeviceProperty( AudcInteger position, AudcHandle deviceHandle, AudcHandle *propertyHandle );
AudcStatusCode AUDCAPI audcGetDevicePropertyById( AudcHandle deviceHandle, AudcPropID propId, AudcHandle *propertyHandle );

AudcStatusCode AUDCAPI audcGetPropertyInformation( AudcHandle propertyHandle, AudcPropertyInfo **info );
AudcStatusCode AUDCAPI audcGetPropertyValueInteger( AudcHandle propertyHandle, AudcInteger *value );
AudcStatusCode AUDCAPI audcGetPropertyValueDouble( AudcHandle propertyHandle, AudcDouble *value );
AudcStatusCode AUDCAPI audcGetDefaultPropertyValueInterger( AudcHandle propertyHandle, AudcInteger *value );
AudcStatusCode AUDCAPI audcGetDefaultPropertyValueDouble( AudcHandle propertyHandle, AudcDouble *value );
AudcStatusCode AUDCAPI audcSetPropertyValueInteger( AudcHandle propertyHandle, AudcInteger value );
AudcStatusCode AUDCAPI audcSetPropertyValueDouble( AudcHandle propertyHandle, AudcDouble value );
AudcStatusCode AUDCAPI audcExecActionProperty( AudcHandle propertyHandle );
AudcStatusCode AUDCAPI audcStopPropertyExec( AudcHandle propertyHandle );

AudcStatusCode AUDCAPI audcSupportedModesCount( AudcHandle deviceHandle, AudcInteger *modesCount );
AudcStatusCode AUDCAPI audcGetModeHandle( AudcHandle deviceHandle, AudcInteger position, AudcHandle *modeHandle );
AudcStatusCode AUDCAPI audcGetModeInfo( AudcHandle modeHandle, AudcModeInfo **info );
AudcStatusCode AUDCAPI audcGetCurrentMode( AudcHandle deviceHandle,  AudcHandle *modeHandle );
AudcStatusCode AUDCAPI audcSetCurrentMode( AudcHandle deviceHandle,  AudcHandle modeHandle );

AudcStatusCode AUDCAPI audcStartStream( AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcStopStream( AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcStillCapture( AudcHandle deviceHandle );
AudcStatusCode AUDCAPI audcIsStillCaptureSupported( AudcHandle deviceHande, bool * supported );

AudcStatusCode AUDCAPI audcRegisterDeviceListUpdatedCB(audcCBDeviceListUpdated func, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceListUpdatedCB(audcCBDeviceListUpdated func );

AudcStatusCode AUDCAPI audcRegisterFrameArrivedCB( audcCBFrameArrived func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterFrameArrivedCB( audcCBFrameArrived func, AudcHandle deviceHandle );

AudcStatusCode AUDCAPI audcRegisterStillCaptureFrameArrivedCB( audcCBStillCaptureFrameArrived func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterStillCaptureFrameArrivedCB( audcCBStillCaptureFrameArrived func, AudcHandle deviceHandle );

AudcStatusCode AUDCAPI audcRegisterDeviceUpdatePropertiesCB( audcCBUpdateDeviceProperty func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterDeviceUpdatePropertiesCB( audcCBUpdateDeviceProperty func, AudcHandle deviceHandle );

AudcStatusCode AUDCAPI audcRegisterPropertyStateChangedCB( audcCBPropertyStateChanged func, AudcHandle deviceHandle, void * ctx );
AudcStatusCode AUDCAPI audcUnregisterPropertyStateChangedCB( audcCBPropertyStateChanged func, AudcHandle deviceHandle );

bool AUDCAPI audcIsError( AudcStatusCode errorCode );

#ifdef __cplusplus
}
#endif

#endif // AUDC_H