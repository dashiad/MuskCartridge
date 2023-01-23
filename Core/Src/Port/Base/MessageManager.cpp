#include "MessageManager.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include <string.h>
namespace Port {
    namespace Base {
        MessageManager::MessageManager(){}
        void MessageManager::init(CommsInterface *_serial)
        {
            serial=_serial;
            reqId=0;
            status=0;

            messageFlag=false;
        }
        boolean MessageManager::hasMessage()
        {
        	return messageFlag;
        }
        void MessageManager::onMessage()
        {
        	messageFlag=true;
        }
        int MessageManager::getReqId()
        {
            reqId++;
            return reqId;
        }
        bool MessageManager::sendACK(uint8_t _slaveId,uint8_t _deviceId,int reqId)
        {
            _reset(MessageCode::ACK);
            _sendByte(_slaveId);
            _sendByte(_deviceId);
            _sendInt(reqId);
        }
        
        bool MessageManager::sendHello(uint8_t *deviceName)
        {
            
            _reset(MessageCode::Hello);
            _sendInt(getReqId());
            _sendString(deviceName);                        
            _flush();
            return true;
        }
        bool MessageManager::sendDeviceSpecs(SlaveId slaveId,
								uint8_t *name,
								uint8_t	majorVersion,
								uint8_t	minorVersion)
        {
            _reset(MessageCode::DeviceSpecs);
            _sendInt(getReqId());
            _sendByte(slaveId);
            _sendByte(majorVersion);
            _sendByte(minorVersion);
            _sendString(name);
            _flush();
            return true;            
        }
		bool MessageManager::sendRegister(
			
			SlaveId slaveId,
            DeviceId deviceId,
			uint8_t *deviceName,
			int fileMask,
			int deviceMask
		){
            _reset(MessageCode::Register);
            _sendInt(getReqId());
            _sendByte(slaveId);
            _sendByte(deviceId);
            _sendInt(fileMask);
            _sendInt(deviceMask);
            _sendString(deviceName);
            _flush();
        }
/*        bool MessageManager::getMessage()
        {
            int length;
            int code;
            if(lastCode==0)
            	return false;
            code=curMessage.ACK.code;
            switch(code)
            {
                case MessageCode::ACK :{
                    curMessage.ACK.slaveId=_readByte();
                    curMessage.ACK.deviceId=_readByte();
                    curMessage.ACK.reqId=_readInt();

                }break;
                case MessageCode::FileTransfer:{
                    curMessage.fileTransfer.slaveId=_readByte();
                    curMessage.fileTransfer.deviceId=_readByte();
                    curMessage.fileTransfer.reqId=_readInt();
                    _readString(curMessage.fileTransfer.fileName);
                    curMessage.fileTransfer.fileSize=_readInt();
                    ILI9341_DrawText("FILETRANSFER", FONT4, 90, 110, BLACK, WHITE);
                    ILI9341_DrawText((const char *)curMessage.fileTransfer.fileName, FONT4, 90, 130, BLACK, WHITE);

                }break;
                case MessageCode::FileBlock:{
                    curMessage.fileBlock.slaveId=_readByte();
                    curMessage.fileBlock.deviceId=_readByte();
                    curMessage.fileBlock.reqId=_readInt();
                    curMessage.fileBlock.length=_readInt();
                    _readBytes(curMessage.fileBlock.block,curMessage.fileBlock.length);                    
                }break;
                default:
                {

                }break;
            }
            lastCode=0;
            return true;
        }
*/
        void MessageManager::_reset(MessageCode code)
        {

            _sendInt((int)code);

        }
        int MessageManager::_sendInt(int number)
        {
        	serial->sendBytes((unsigned char *)&number,sizeof(int),2000);

        }
        int MessageManager::_sendByte(uint8_t b)
        {
        	serial->sendBytes((unsigned char *)&b,1,2000);

        }
        int MessageManager::_sendString(uint8_t *str)
        {
            int l=strlen((char *)str);            
            _sendBytes(str,l);            
        }
        int MessageManager::_sendBytes(uint8_t *str,int l)
        {
            _sendInt(l);
            serial->sendBytes((unsigned char *)str,l,2000);

        }
        int MessageManager::_readInt()
        {
            int i;
            if(_readBytes((uint8_t *)&i,sizeof(int))==sizeof(int))
            {
                return i;
            }
            // Todo: Lanzar excepcion.

        }
        int MessageManager::_readBytes(uint8_t *buf, int length)
        {

        	int nread;
        	int totalRead=0;
        	while(totalRead < length)
        	{
        		nread=serial->receiveBytes(buf+totalRead,length-totalRead,2000);

        		totalRead+=nread;
        		if(totalRead > length)
        		{
        			totalRead=0;
        		}
        	}
            return totalRead;
        }
        uint8_t MessageManager::_readByte()
        {
            uint8_t b;
            int nread=serial->receiveBytes(&b,1,2000);
            return b;
        }
        int MessageManager::_readString(uint8_t *b)
        {
            int l=_readInt();
            return _readBytes(b,l);
        }
        int MessageManager::_flush()
        {


            return 0;
            //return serial->getWriteError();
        }
    }
}
