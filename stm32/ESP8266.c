#include "ESP8266.h"

void initESP(void){
	/********* AT **********/
	sendString("AT\r\n");
	delayUs(1000);
	
	while (!waitFor("OK\r\n"));
	
	/********* AT+CWMODE=1 **********/
	sendString("AT+CWMODE=1\r\n");
	delayUs(1000);
	
	while (!waitFor("OK\r\n"));
	
	
	/********* AT+CWJAP="SSID","PASSWD" **********/
	sprintf(wifi_info, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASS);
	sendString(wifi_info);
	
	while (!waitFor("OK\r\n"));
	sendStringToPC("hihi");
	
	/********* AT+CIFSR **********/
	sendString("AT+CIFSR\r\n");

	sendString("idx = %d, ", idx);
}