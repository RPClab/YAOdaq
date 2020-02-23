#pragma once

#include "Exception.hpp"

#include <cstdint>

namespace CAEN
{
class CAENDigitizerException: public Exception
{
public:
#if experimental_have_source_location == 1
  CAENDigitizerException(const int&                         code = 0,
                     std::experimental::source_location loc =
                         std::experimental::source_location::current());
#elif have_source_location == 1
  CAENDigitizerException(const int& code = 0, std::source_location loc =
                                              std::source_location::current());
#else
  CAENDigitizerException(const int& code = 0)
#endif
private:
  CAENDigitizerException() = delete;
  virtual const char* errorStrings(const std::int_least32_t& code) final;
};

}  // namespace CAEN
