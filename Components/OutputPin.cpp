#include "OutputPin.h"
#include "Connection.h"
#include "Component.h"
OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
	m_Connections = new Connection*[MAX_CONNS];
	//=========DOAA========
	is_connected = false;
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.

bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

Connection** OutputPin::get_connections(int& m_conn) const
{
	m_conn = m_Conn;
	return m_Connections;
}


//===========DOAA===========
//bool OutputPin::get_is_connected()
//{
//	return is_connected;
//}
//void OutputPin::set_is_connected(bool)
//{
//	is_connected = test;
//}
void OutputPin::setComponent(Component* pCmp)
{
	this->pComp = pCmp;

	is_connected = false;
}

Component* OutputPin::getComponent() const
{
	return pComp;
}