#include "Connector.hpp"

#include <iostream>
Connector::Connector(const std::string& type, const ConnectorInfos& infos): m_Type(type), m_Infos(infos) {}

toml::value Connector::getParameters()
{
  return m_Infos.getParameters();
}

void Connector::printParameters()
{
  m_Infos.printParameters();
}

std::int32_t Connector::Connect()
{
  verifyParameters();
  DoConnect();
  m_Infos.setHandle(m_Handle);
  m_Infos.addBoardConnected();
  return m_Handle;
}

void Connector::setInfos(const ConnectorInfos& infos)
{
  m_Infos = infos;
}

std::string Connector::getType()
{
  return m_Type;
}

void Connector::Disconnect()
{
  m_Infos.removeBoardConnected();
  if(m_Infos.getNumberBoardConnected() == 0) DoDisconnect();
}

void Connector::verifyParameters() {}
