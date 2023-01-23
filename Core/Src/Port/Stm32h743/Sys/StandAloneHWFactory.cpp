/*
 * HWFactory.cpp
 *
 *  Created on: 26 feb 2022
 *      Author: Jose
 */

#include <Port/Stm32h743/Sys/StandAloneHWFactory.h>
#include <string.h>



/**
  * @brief This function handles USART1 global interrupt.
  */


namespace Port {
namespace Stm32h743 {
namespace Sys {
/*
const char *HC05BluetoothInterface::RES_UNEXPECTED_AT_RESULT="Unexpected AT result";
const char *HC05BluetoothInterface::RES_NOT_IN_AT_MODE="Not in at mode";

void HC05BluetoothInterface::initialize(::Sys::Result *res)
{
	SerialInterface::initialize(res);
	//HAL_UART_Receive_DMA (&huart, UART1_rxBuffer, 12);
	enterATMode();
	hc05state=UNKNOWN;

	AT_sendCommand("AT\r\n",res);
	if(!res->isOk())
	{
		res->setError(getModuleName(), HC05BluetoothInterface::RES_NOT_IN_AT_MODE);
		return;
	}
	AT_receiveOK(res);
	if(!res->isOk())
		return;

	HAL_Delay(1000);
	getState(res);
	if(res->isOk())
		reactToState();

}
void HC05BluetoothInterface::reactToState()
{
	::Sys::Result res;
	switch(hc05state)
	{
	case INITIALIZED:{
		AT_sendCommand("AT+NAME=MuskCart\r\n",&res);
		AT_receiveOK(&res);
		AT_sendCommand("AT+ROLE=0\r\n",&res);
		AT_receiveOK(&res);
		AT_sendCommand("AT+UART=230400,0,0\r\n",&res);
		AT_receiveOK(&res);
		this->enterDataMode();
	}break;
	case PAIRABLE:{

	}break;
	case PAIRED:{

	}break;

	}
}
void HC05BluetoothInterface::powerOff()
{
	HAL_GPIO_WritePin(powerPort, powerPin, GPIO_PIN_RESET);
}

void HC05BluetoothInterface::powerOn()
{
	HAL_Delay(50);
	HAL_GPIO_WritePin(powerPort, powerPin, GPIO_PIN_SET);

}
void HC05BluetoothInterface::connect()
{
	uint8_t tempBuf[10];
	tempBuf[0]=0;
	::Sys::Result res;
	changeBaudRate(230400);
	while(1)
	{
		if(receiveBytes(tempBuf,10,10000,&res)!=HAL_TIMEOUT)
		{
		//		res.setError(getModuleName(),SerialInterface::RES_SERIAL_ERROR);

		if(tempBuf[0]!=0)
		{
			// Si se reciben 3 signos "+", estamos conectados
			if(tempBuf[0]=='+' && tempBuf[1]=='+')
				return;
		}
		}
		HAL_Delay(100);

	}
}
void HC05BluetoothInterface::enterATMode()
{
	powerOff();
	holdENKey();
	HAL_Delay(100);
	powerOn();
	HAL_Delay(1000);
	releaseENKey();

}

void HC05BluetoothInterface::enterDataMode()
{

	powerOff();
	HAL_Delay(1000);
	releaseENKey();
	HAL_Delay(1000);
	powerOn();
}

void HC05BluetoothInterface::getState(::Sys::Result *res)
{
	AT_sendCommand("AT+STATE?\r\n",res);
	if(!res->isOk())
		return;
	HC05State oldState;
	oldState=hc05state;
	uint8_t buf[100];
	receiveBytes(buf, 100, 500, res);
	if(!res->isOk())
		return;
	hc05state=UNKNOWN;
	uint8_t *r=buf+7;

	switch(*r)
	{
	case 'I':
	{
		switch(*(r+2))
		{
		case 'I':{hc05state=INITIALIZED;}break;
		case 'Q':{hc05state=INQUIRING;}break;
		}
	}break;
	case 'R':{
		hc05state=READY;
	}break;
	case 'P':{
		switch(*(r+4))
		{
		case 'A':{hc05state=PAIRABLE;}break;
		case 'E':{hc05state=PAIRED;}break;
		}

	}break;
	case 'C':{
		hc05state=CONNECTING;
	}break;
	case 'D':{
		hc05state=DISCONNECTED;
	}break;

	}
	int hh;
	if(oldState!=hc05state)
		hh=11;
	uint8_t *p;
	int i=0;
	for(p=buf;i<30 && (*p)!='\n';p++,i++);
	if((*p)=='\n')
	{
		if(*(p+1)=='O' && *(p+2)=='K')

			return;
	}
	res->setError(getModuleName(),HC05BluetoothInterface::RES_UNEXPECTED_AT_RESULT);
}

void HC05BluetoothInterface::isPaired()
{

}
void HC05BluetoothInterface::beginPairing()
{

}

void HC05BluetoothInterface::holdENKey()
{
	HAL_GPIO_WritePin(enablePort, enablePin, GPIO_PIN_SET);
}

void HC05BluetoothInterface::releaseENKey()
{
	HAL_GPIO_WritePin(enablePort, enablePin, GPIO_PIN_RESET);
}

void HC05BluetoothInterface::AT_sendCommand(const char *cmd,::Sys::Result *res)
{
	sendBytes((unsigned char *)cmd, strlen((const char *)cmd), 2000, res);
}
void HC05BluetoothInterface::AT_receiveOK(::Sys::Result *res)
{
	uint8_t buf[10];
	if(receiveBytes(buf,10,1000,res)!=HAL_OK)
		res->setError(getModuleName(),SerialInterface::RES_SERIAL_ERROR);
	else
	{
		if(res->isOk())
		{
			if(buf[0]!='O' || buf[1]!='K')
				res->setError(getModuleName(),HC05BluetoothInterface::RES_UNEXPECTED_AT_RESULT);
		}
	}
}
*/
StandAloneHWFactory::StandAloneHWFactory(
		::GPIO_TypeDef *_enablePort,
		 int _enablePin,
		 ::GPIO_TypeDef *_powerPort,
		int _powerPin,
		UART_HandleTypeDef *uart) {
	// TODO Auto-generated constructor stub

	// USART1
	huart1=uart;
	enablePort=_enablePort;
	enablePin=_enablePin;
	powerPort=_powerPort;
	powerPin=_powerPin;
	btInitialized=false;
	/*bt=new HC05BluetoothInterface(
			enablePort,enablePin,
			powerPort,powerPin,
			huart1);*/
	ui=0;

}
::Port::Base::UIRepr *StandAloneHWFactory::getUIRepr(::Port::Base::Master *_master)
{
	if(!btInitialized)
	{
		/*ui=new ::Port::Base::UIRepr(_master,bt);
		::Sys::Result res;
		bt->initialize(&res);
		if(!res.isOk())
		{
			return 0;
		}*/

	}
	return ui;

}
StandAloneHWFactory::~StandAloneHWFactory() {
	// TODO Auto-generated destructor stub
}

} /* namespace Sys */
} /* namespace Stm32h743 */
} /* namespace Port */
