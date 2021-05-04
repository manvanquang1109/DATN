#include "ESP8266.h"
volatile uint8_t tx_string[BUFF_LEN];

void initESP(void){
	int lenGET = strlen(GET_REQ);
	
	/********* AT **********/
	sendString("AT\r\n");
	delayUs(1000);
	
	while (!waitFor("OK\r\n"));
	
	/********* AT+CWMODE=1 **********/
	sendString("AT+CWMODE=1\r\n");
	delayUs(1000);
	
	while (!waitFor("OK\r\n"));
	
	
	/********* AT+CWJAP="SSID","PASSWD" **********/
	sprintf(tx_string, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASS);
	sendString(tx_string);
	
	while (!waitFor("OK\r\n"));
	sendStringToPC("PC: 1");
	
//	/********* AT+CIFSR **********/
//	sendString("AT+CIFSR\r\n");

	/********* AT+CIPSTART="TCP","http://esp8266-sendreq.herokuapp.com",80 **********/
	
	sprintf(tx_string, "AT+CIPSTART=\"TCP\",\"%s\",80\r\n", URL);
	sendString(tx_string);
	while (!waitFor("OK\r\n"));
	
	sendStringToPC("PC: 2");
	
	
	/********* AT+CIPSEND=22 **********/
	sprintf(tx_string, "AT+CIPSEND=%d\r\n", lenGET + 4);
	sendString(tx_string);
	while	(!waitFor(">"));
	
	sendStringToPC("PC: 3");
	
	
	/********* GET /test HTTP/1.0 **********/
	sprintf(tx_string, "%s\r\n\r\n", GET_REQ);
	sendString(tx_string);
	while	(!waitFor("</html>"));
//	delayMs(3000);
	
	sendStringToPC("PC: 4");
	sendString("idx = %d", idx);
}

