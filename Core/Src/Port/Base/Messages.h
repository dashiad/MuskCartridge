/*
 * Messages.h
 *
 *  Created on: 19 feb 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_MESSAGES_H_
#define SRC_PORT_BASE_MESSAGES_H_

#define MESSAGE_MAX_BOARD_NAME		 50
#define MESSAGE_MAX_DEVICE_NAME      50
#define MESSAGE_MAX_FILE_NAME       256
#define MESSAGE_MAX_FILE_BLOCK_SIZE 1500
#include <stdint.h>

/*****************************************************************************
 *****************************************************************************
 *****************************************************************************
 *
 *    COMMON MESSAGES
 *
 *****************************************************************************
 *****************************************************************************
 *****************************************************************************
 */
namespace Port
{
    namespace Base {

typedef enum _MessageCode : uint32_t
{

	ACK=1,
	Error,
	FileTransfer,
	FileBlock,
	FileRequest,

	Ping,
	Mount,
	DeviceAction,
	Reset,
	Hello,
	DeviceSpecs,
	DeviceStatus,
	Register,
	__LAST_MESSAGE__
}MessageCode;
extern char *messageEncoding[__LAST_MESSAGE__];
typedef uint32_t RequestId;
typedef uint8_t  DeviceId;
typedef uint8_t  SlaveId;

/*
 * ACKMessage : Returned to ack message reception/execution, if needed.
 *
 */
typedef struct __attribute__ ((packed)) _ACKMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	RequestId reqId;
}ACKMessage;

/*
 * ErrorMessage : For all your error message needs!
 *
 */
typedef enum _ErrorSeverity {
	 ERROR_NONE,
	 ERROR_INFO,
	 ERROR_WARNING,
	 ERROR_FATAL
} ErrorSeverity;


typedef struct __attribute__ ((packed)) _ErrorMessage {
	MessageCode code;
	DeviceId deviceId;
	RequestId reqId;
	ErrorSeverity severity;
	uint8_t errorMessage[256];
}ErrorMessage;


/*
 * FileTransferMessage: Sent to initiate a file transfer request, in any direction.
 * A FileTransferMessage is followed by a number or FileBlockMessages.
 *
 */
typedef struct __attribute__ ((packed)) _FileTransferMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	RequestId reqId;
	uint32_t fileSize;
	uint8_t fileName[MESSAGE_MAX_FILE_NAME];

}FileTransferMessage;

typedef struct __attribute__ ((packed)) _FileBlockMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	RequestId reqId;
	uint32_t length;
	uint8_t block[MESSAGE_MAX_FILE_BLOCK_SIZE];

}FileBlockMessage;

/*
 * FileRequestMessage: Sent to request a file from a Slave. The Slave may contain different HTML/javascript/CSS files
 * required to build custom UIs.This is normally sent by the Master
 * A FileTransferMessage is followed by a number or FileBlockMessages.
 *
 */
typedef struct __attribute__ ((packed)) _FileRequestMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	uint32_t requestId;
	uint8_t  fileName[MESSAGE_MAX_FILE_NAME];
} FileRequestMessage;






/*****************************************************************************
 *****************************************************************************
 *****************************************************************************
 *
 *    MASTER->SLAVE MESSAGES
 *
 *****************************************************************************
 *****************************************************************************
 *****************************************************************************
 */

/**
 *  PingMessage is sent by the Master to discover slaves.
 *  Slaves should reply with a Hello message before a timeout.
 *  It has no additional parameters
 */
typedef struct __attribute__ ((packed)) _PingMessage {
	MessageCode code;
	SlaveId id;
}PingMessage;
/**
 *  Mount tells the slave to "activate" the currently selected file.
 *  Slaves should reply with an ACK, or an ErrorMessage
 */
typedef struct __attribute__ ((packed)) _MountMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	RequestId reqId;
	uint8_t fileName[MESSAGE_MAX_FILE_NAME];
}MountMessage;

/**
 *  DeviceAction encodes device specific requests. Each device can encode its own subset of messages,
 *  which are sent from the custom UI pages for the device.
 */
typedef struct __attribute__ ((packed)) _DeviceActionMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
	RequestId reqId;
	uint8_t internalMessage[MESSAGE_MAX_FILE_BLOCK_SIZE];
}DeviceActionMessage;

/**
 * Reset Requires the target DeviceId to be reset. This could also be a hardware reset,
 * using a dedicated pin to the target slave reset line. This is more secure, but requires more pins.
 */
typedef struct __attribute__ ((packed)) _ResetMessage {
	MessageCode code;
	SlaveId slaveId;
	DeviceId deviceId;
}ResetMessage;

typedef union _MSMessage {

}MSMessage;



/*****************************************************************************
 *****************************************************************************
 *****************************************************************************
 *
 *    SLAVE->MASTER MESSAGES
 *
 *****************************************************************************
 *****************************************************************************
 *****************************************************************************
 */


typedef struct __attribute__ ((packed)) _helloMessage {
	MessageCode type;
	RequestId reqId;
	uint8_t boardName[MESSAGE_MAX_DEVICE_NAME];	
}HelloMessage;


typedef enum _SupportedFile {
	CRT_SUPPORT=0x01
}SupportedFile;
typedef enum _SupportedDevice {
	RESET_SUPPORT=0x01,
	REU_512K_SUPPORT=0x02
}SupportedDevice;

/* Field fileMask indicates a certain file type support by this slave (from SupportedFileType enum) */
/* Field deviceMask indicates device types supported by this slave (from SupportedDevices enum).*/
typedef struct __attribute__ ((packed)) _DeviceSpecsMessage {
	MessageCode type;
	RequestId 	reqId;
	SlaveId 	slaveId;
	uint8_t 	name[MESSAGE_MAX_DEVICE_NAME];
	uint8_t		majorVersion;
	uint8_t		minorVersion;	
}DeviceSpecsMessage;

typedef enum _DeviceStatusCode {
	STATUS_OK,
	STATUS_BUSY,
	STATUS_ERRORED,
	STATUS_DONT_INTERRUPT
}DeviceStatusCode;
typedef struct __attribute__ ((packed)) _DeviceStatusMessage {
	MessageCode type;
	SlaveId slaveId;
	DeviceId deviceId;
	DeviceStatusCode code;
}DeviceStatusMessage;

typedef struct __attribute__ ((packed)) _RegisterMessage {
	MessageCode type;
	RequestId reqId;
	SlaveId slaveId;
	DeviceId deviceId;
	uint8_t deviceName [MESSAGE_MAX_DEVICE_NAME];
	int fileMask;
	int deviceMask;

}RegisterMessage;

typedef union __attribute__ ((packed)) _Message {
	ACKMessage 			ACK;
	ErrorMessage		error;
	FileTransferMessage fileTransfer;
	FileBlockMessage    fileBlock;
	FileRequestMessage	fileRequest;
	PingMessage ping;
	MountMessage mount;
	DeviceActionMessage deviceAction;
	ResetMessage resetMessage;
	HelloMessage 		 hello;
	DeviceSpecsMessage deviceSpecs;
	DeviceStatusMessage deviceStatus;
	RegisterMessage registerM;


}Message;

    }
}
#endif /* SRC_PORT_BASE_MESSAGES_H_ */
