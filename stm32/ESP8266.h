#ifndef	_ESP8266
#define _ESP8266

#include "stm32f10x.h"                  // Device header
#include "main.h"
#include "UART.h"

#define WIFI_SSID	"VIETTEL_2.4G_NP3DgK"
#define	WIFI_PASS	"thichanga"

#define URL				"http://esp8266-sendreq.herokuapp.com"
#define GET_REQ		"GET / HTTP/1.1\r\nHost: esp8266-sendreq.herokuapp.com"

void initESP(void);

#endif
