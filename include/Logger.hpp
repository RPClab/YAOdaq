#pragma once

#include "Module.hpp"

class Logger : public Module
{
public:
  Logger(const std::string& name = "", const std::string& type = "Logger");
  virtual ~Logger() = default;
  virtual void   OnMessage(const ix::WebSocketMessagePtr& msg);
};
