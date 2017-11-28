/*  Author      : Tan Xin Ji Alan
 *  Description : Initialising of SIM5320E Shield
 *                Try changing the value assigned to b_PrintShortResponse and b_EchoMode
 *                Value: YES/NO
 *  Date        : 27 November 2017
 */

#include "ATCommand.h"

#define         COM                   Serial

#define         COM_BAUDRATE          9600
#define         SIM5320E_BAUDRATE     9600

//Type         | VariableName         | Value
//----------------------------------------------
HardwareSerial  &hws_SIM5320E_Serial  = Serial1;
ATCommand       AT;

String          str_SIM5320E_Response;
boolean         b_PrintShortResponse  = YES;
boolean         b_EchoMode            = NO;

String          str_Timestamp;

uint8_t         ui8_AdditionalLength  = 0;

void setup() {
  // put your setup code here, to run once:
  // Initialize COM serial port and wait for connection
  COM.begin(COM_BAUDRATE);
  while (!COM);
  // Initialize SIM5320E serial port and wait for connection
  InitSIM5320E();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void InitSIM5320E (void)
{
  // Initialising SIM5320E to link with serial port and setting baudrate
  // Received 'Set up done'
  AT.Setup(hws_SIM5320E_Serial, SIM5320E_BAUDRATE);
  
  /*  Response received:
   *  START          -> SIM5320E is alive
   *  +STIN: 25      -> SAT has return to Main Menu (AT+STIN)
   *  +STIN: 25      -> SAT has return to Main Menu (AT+STIN)
   *  +CPIN: READY   -> Not pending for any password (AT+CPIN)
   *  SMS DONE       -> Detects SMS memory (AT Commands for SMS)
   *  PB DONE        -> Detects PhoneBook memory (AT Commands for Phonebook)
   */
  // Wait for ~12 seconds upon power up of SIM5320E before message 'PB Done' appears
  AT.ReceivedResponse("PB DONE",b_PrintShortResponse);

  // Simple test of connectivity
  AT.AT();
  AT.ReceivedResponse("OK", b_PrintShortResponse);

  // Switch on/off AT echoes        
  AT.E(b_EchoMode);
  AT.ReceivedResponse("OK", b_PrintShortResponse);

  /*  AT+STIN (SAT Indication, SAT:SIM Application Toolkit)
   *  +STIN: 25 -> Notification that SIM Application has returned to main menu.
   *               If user doesn' do any action in 2 minutes, application will
   *               return to main menu automatically.
   */
  // Wait for ~65 seconds upon power up of SIM5320 before message '+STIN: 25' appears
  AT.ReceivedResponse("+STIN: 25",b_PrintShortResponse);

  // Read the UE system information on a 3G cell
  AT.CPSI("?");
  
  /*  Response received:
   *  +CPSI: WCDMA      ,Online        ,525-01 ,0x0152,20190399,WCDMA IMT 2000,14 ,
   *  10812,0  ,6.5  ,64  ,27  ,35   ,500
   *  +CPSI: System Mode,Operation Mode,MCC-MNC,LAC   ,Cell ID ,Frequency Band,PSC,
   *  Freq ,SCC,Ec/Io,RSCP,Qual,RxLev,TXPWR
   *  
   *  System Mode   : 'NO SERVICE', 'GSM', 'WCDMA'
   *  Operation Mode: 'Online', 'Offline', 'Factory Test Mode', 'Reset', 'Low Power Mode'
   *  MCC           : Mobile Country Code (first part of PLMN code)
   *  MNC           : Mobile Network Code (second part of PLMN code)
   *  LAC           : Location Area Code (hexadecimal digits)
   *  Cell ID       : Service-cell ID
   *  Frequency Band: Frequency Band of active set
   *  PSC           : Primary synchronization code of active set
   *  Freq          : Downlink frequency of active set
   *  SSC           : Secondary synchronization code of active set
   *  EC/IO         : Ec/Io value
   *  RSCP          : Received Signal Code Power
   *  Qual          : Quality value for base station selection
   *  RxLev         : RX level value for base station selection
   *  TXPWR         : UE TX power in dBm. If no TX, the value is 500
   */
  str_SIM5320E_Response = AT.ReceivedResponse("OK", b_PrintShortResponse);
  // Getting MCC-MNC, 525-01 is Singtel
  ui8_AdditionalLength = GetAddtionalLengthDueToEchoOnOff(b_EchoMode, str_SIM5320E_Response, '?');
  COM.println(str_SIM5320E_Response.substring(ui8_AdditionalLength+22,ui8_AdditionalLength+28));

}

uint8_t GetAddtionalLengthDueToEchoOnOff (boolean b_Mode,
                                          String  str_ATCommandResponse,
                                          char    c_CharToLookoutFor)
{
  uint8_t ui8_AddLength = 0;
  
  if(b_Mode == YES)
  {
    for (uint16_t ui16_index=0; ui16_index<str_ATCommandResponse.length(); ui16_index++)
    {
      if(str_SIM5320E_Response[ui16_index]== c_CharToLookoutFor)
        ui8_AddLength = ui16_index+2;
    }
  }
  else  ui8_AddLength = 0;
  
  return ui8_AddLength;
}
