/*
 * HWFactory.h
 *
 *  Created on: 26 feb 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_SYS_HWFACTORY_H_
#define SRC_PORT_STM32H743_SYS_HWFACTORY_H_
#include "Port/Base/NullHWFactory.h"
#include "SerialInterface.h"
#include "Port/Base/Messages.h"
#include "main.h"
#include "stm32h7xx_hal_uart.h"

namespace Port {
namespace Stm32h743 {
namespace Sys {


class SerialUI: public ::Port::Base::UIRepr
{
public:
	inline SerialUI(::Port::Base::Master *_master,SerialInterface *_comms):UIRepr(_master,_comms){}
};



typedef enum __HC05State {
	UNKNOWN,
	INITIALIZED,
	READY,
	PAIRABLE,
	PAIRED,
	INQUIRING,
	CONNECTING,
	CONNECTED,
	DISCONNECTED
} HC05State;
/*class HC05BluetoothInterface: public SerialInterface {
public:
	static const char *RES_NOT_IN_AT_MODE;
	static const char *RES_UNEXPECTED_AT_RESULT;
	HC05BluetoothInterface(
			::GPIO_TypeDef *_enablePort,
			int _enablePin,
			::GPIO_TypeDef *_powerPort,
			int _powerPin,
			UART_HandleTypeDef *uart):SerialInterface("HC05BluetoothInterface",uart){
		enablePort=_enablePort;
		enablePin=_enablePin;
		powerPort=_powerPort;
		powerPin=_powerPin;
	}
	virtual void initialize(::Sys::Result *res);
	virtual void AT_sendCommand(const char *cmd,::Sys::Result *res);
	virtual void AT_receiveOK(::Sys::Result *res);
	void connect();
	void powerOff();
	void powerOn();
	void enterATMode();
	void enterDataMode();
	void getState(::Sys::Result *res);
	void isPaired();
	void beginPairing();
	void holdENKey();
	void releaseENKey();
	void reactToState();

private:
	::GPIO_TypeDef *enablePort;
	int enablePin;
	::GPIO_TypeDef *powerPort;
	int powerPin;
	HC05State hc05state;
};


*/
class StandAloneHWFactory : public ::Port::Base::NullHWFactory{
public:
	StandAloneHWFactory(
			::GPIO_TypeDef *_enablePort,
			int _enablePin,
			::GPIO_TypeDef *_powerPort,
			int _powerPin,
			UART_HandleTypeDef *uart);
	virtual ::Port::Base::UIRepr *getUIRepr(::Port::Base::Master *_master);
	virtual ~StandAloneHWFactory();
protected:
	UART_HandleTypeDef *huart1;
	::GPIO_TypeDef *enablePort;
	int enablePin;
	::GPIO_TypeDef *powerPort;
	int powerPin;
	::Port::Base::UIRepr *ui;
//	HC05BluetoothInterface *bt;
	bool btInitialized;
};


} /* namespace Sys */
} /* namespace Stm32h743 */
} /* namespace Port */

#endif /* SRC_PORT_STM32H743_SYS_HWFACTORY_H_ */
