/*
 * Events.h
 *
 *  Created on: 20 feb 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_EVENTS_H_
#define SRC_PORT_BASE_EVENTS_H_

namespace Port::Base {
	typedef enum _Event {
		EVENT_STATUS_OK,
		EVENT_STATUS_ERRORED,
		EVENT_STATUS_BUSY,
		EVENT_STATUS_WORKING
	};
	class EventDispatcher
	{
		void
	};
}

#endif /* SRC_PORT_BASE_EVENTS_H_ */
