#include "CAENCommError.hpp"
#include "CAENComm.h"
#include<cstdint>

namespace CAEN
{
    
const char* CAENCommError::ErrorStrings(const std::int_least32_t& code)
{ 
    switch (code) 
    {
        case CAENComm_Success :  return "Operation completed successfully";
        case CAENComm_VMEBusError : return "VME bus error during the cycle";
        case CAENComm_CommError : return "Communication error";
        case CAENComm_GenericError : return "Unspecified error";
        case CAENComm_InvalidParam : return "Invalid parameter";
        case CAENComm_InvalidLinkType : return "Invalid Link Type";
        case CAENComm_InvalidHandler : return "Invalid device handler";
        case CAENComm_CommTimeout : return "Communication Timeout";
        case CAENComm_DeviceNotFound : return "Unable to Open the requested Device";
        case CAENComm_MaxDevicesError : return "Maximum number of devices exceeded";
        case CAENComm_DeviceAlreadyOpen : return "The device is already opened";
        case CAENComm_NotSupported : return "Not supported function";
        case CAENComm_UnusedBridge : return "There aren't board controlled by that CAEN Bridge";
        case CAENComm_Terminated : return "Communication terminated by the Device";
    }
    return "Unknown error";
}

#if experimental_have_source_location == 1
CAENCommError::CAENCommError(const int& code,std::experimental::source_location loc):Error(code,ErrorStrings(code),loc)
{
    if(code!=CAENComm_Success) throw *this;
};
#elif have_source_location == 1
CAENCommError::CAENCommError(const int& code,std::source_location loc):Error(code,ErrorStrings(code),loc)
{
    if(code!=CAENComm_Success) throw *this;
};
#else
CAENCommError::CAENCommError(const int& code):Error(code,ErrorStrings(code))
{
    if(code!=CAENComm_Success) throw *this;
};
#endif

}