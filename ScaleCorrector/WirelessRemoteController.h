/*
 * \brief Receive data from wireless remote controller (asynchronously or/and synchronously)
 *
 * This library has been tested with IC2272/2272 (315MHz and 433MHz) also called SC2272.
 * but it should be usable with any similar remote controller.
 *
 * \author Quentin Comte-Gaz <quentin@comte-gaz.com>
 * \date 1 July 2016
 * \license MIT License (contact me if too restrictive)
 * \copyright Copyright (c) 2016 Quentin Comte-Gaz
 * \version 1.0
 */

#ifndef WirelessRemoteController_h
#define WirelessRemoteController_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PIN_D0 0
#define PIN_D1 1
#define PIN_D2 2
#define PIN_D3 3
#define PIN_VT 4  /*! PORD4*/

#define PLUS_CALIBRATION	12	/*! Нажаты две кнопки C and A*/
#define MINUS_CALIBRATION	9	/*! Нажаты две кнопки C and B*/
#define ACTION_BUTTON_A		4	/*! Нажата кнопка A*/
#define ACTION_BUTTON_B		1	/*! Нажата кнопка B*/
#define ACTION_BUTTON_C		8	/*! Нажата кнопка C*/
#define ACTION_BUTTON_D		2	/*! Нажата кнопка D*/

class WirelessRemoteController{
	public:
    /*!
     * \brief WirelessRemoteController Initialize wireless remote controller
     *
     * \param pin_D0 (int) Digital input pins connected to D0 remote controller device
     * \param pin_D1 (int) Digital input pins connected to D1 remote controller device
     * \param pin_D2 (int) Digital input pins connected to D2 remote controller device
     * \param pin_D3 (int) Digital input pins connected to D3 remote controller device
     */
	WirelessRemoteController();
	~WirelessRemoteController();
    /*!
     * \brief getCurrentValue Get current data sent by wireless remote controller
     *
     * \param (bool[4])[out] Data received from wireless remote controller ([A button, B button, C button, D button])
     *
     * \return (bool) Did remote controller send data?
     */
	bool getCurrentValue(bool data[4]);
	bool readBitsFromPort();
	byte getBits(){return _pinsBit;};

    /*!
     * \brief addTrigger Launch a function every time remote controller send data
     *
     * \param trigger_pin (int) DT digital trigger input pin (must be an interruptable pin: https://www.arduino.cc/en/Reference/AttachInterrupt)
     * \param (void function()) Function that will be launched every time a data is sent from remote controller
     */
	void addTrigger( void (*function)());

	private:
	int _pins[4];
	byte _pinsBit;	
	bool flagVT;
};

extern WirelessRemoteController remoteController;

#endif //WirelessRemoteController_h

