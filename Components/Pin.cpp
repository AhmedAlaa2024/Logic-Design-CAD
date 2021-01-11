#include "Pin.h"

Pin::Pin()
{
	m_Status = LOW;	//Default Status is LOW
}

void Pin::setStatus(STATUS r_Status)
{
	m_Status = r_Status;
}
bool Pin::ConnectTo(Connection* r_Conn)
{
	is_connected = true;

	return false;	//can't connect to any more connections
}

STATUS Pin::getStatus()
{
	return m_Status;
}