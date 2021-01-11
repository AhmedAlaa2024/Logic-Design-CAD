#ifndef _PIN_H
#define _PIN_H

#include "..\Defs.h"

class Connection;

class Pin
{
protected:
	STATUS m_Status;	//Status of the Pin
	bool is_connected;
public:
	Pin();
	virtual bool ConnectTo(Connection* r_Conn);	//connect to a new connection
	
	void setStatus(STATUS r_Status);
	STATUS getStatus();
};

#endif