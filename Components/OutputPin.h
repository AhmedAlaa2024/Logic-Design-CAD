#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

/*class OutputPin
  ---------------
 An output pin obtains its value as a result of calculating the outputs of
 a component. The output pin propagates its value immediately to the associated connections
*/


#include "Pin.h"
class Connection;	//Forward class declartion
class Component; //Forward class declaration


class OutputPin : public Pin	//inherited from class Pin
{
private:
	//Array of connections (poniters) to be connected to that OutputPin
	//For simplicity, we consider it a constant length
	Connection** m_Connections;
	int m_FanOut;	//Maximum No. of connections connected to that output pin (depends on the component)
	int m_Conn;		//Actual No. of connections connected to that output pin

	//Rufaidah
	Component* pComp; //Component at which this pin is associated

	//==========DOAA==========
	bool is_connected;

public:
	OutputPin(int r_FanOut);
	bool ConnectTo(Connection* r_Conn);	//connect to a new connection

	Connection** get_connections(int& m_conn) const ;

	void setComponent(Component* pCmp);

	Component* getComponent() const;


	
	////============DOAA===========
	//bool get_is_connected();
	//void set_is_connected(bool);
	
};

#endif