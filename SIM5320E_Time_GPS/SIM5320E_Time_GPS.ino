/*  Author      : Tan Xin Ji Alan
 *  Description : Acquiring TimeStamp and GPS Info
 *                Try changing the value assigned to b_PrintShortResponse and b_EchoMode
 *                Value: YES/NO
 *  Date        : 28 November 2017
 */

#include "ATCommand.h"

#define         COM                   Serial

#define         COM_BAUDRATE          9600
#define         SIM5320E_BAUDRATE     9600

#define         ASCII_ZERO            48

//Type         | VariableName         | Value
//----------------------------------------------
HardwareSerial  &hws_SIM5320E_Serial  = Serial1;
ATCommand       AT;

String          str_SIM5320E_Response;
boolean         b_PrintShortResponse  = YES;
boolean         b_EchoMode            = NO;

String          str_Timestamp;

uint8_t         ui8_AdditionalLength  = 0;

double          d_Latitude            = 0.0;
double          d_Longitude           = 0.0;
 
void setup() {
  // put your setup code here, to run once:
  // Initialize COM serial port and wait for connection
  COM.begin(COM_BAUDRATE);
  while (!COM);
  // Initialize SIM5320E serial port and wait for connection
  InitSIM5320E();
  GettingGPSReading();
}

void loop() {
  // put your main code here, to run repeatedly:
  // AT+CCLK?
  AT.CCLK("?");
  str_SIM5320E_Response = AT.ReceivedResponse("+32", b_PrintShortResponse);
  ui8_AdditionalLength = GetAddtionalLengthDueToEchoOnOff(b_EchoMode, str_SIM5320E_Response, '?');
  GetTimeStamp(str_SIM5320E_Response);
  COM.println(str_Timestamp);

  GettingGPSReading();
  COM.println(d_Latitude,6);
  COM.println(d_Longitude,6);

  delay(5000);
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
   */
  // Wait for ~65 seconds upon power up of SIM5320 before message '+STIN: 25' appears
  AT.ReceivedResponse("+STIN: 25",b_PrintShortResponse);

  // Read the UE system information on a 3G cell
  AT.CPSI("?");
  
  /*  Response received:
   *  +CPSI: System Mode,Operation Mode,MCC-MNC,LAC,Cell ID,Frequency Band,PSC,
   *  Freq,SCC,Ec/Io,RSCP,Qual,RxLev,TXPWR 
   */
  str_SIM5320E_Response = AT.ReceivedResponse("OK", b_PrintShortResponse);
  // Getting MCC-MNC, 525-01 is Singtel
  ui8_AdditionalLength = GetAddtionalLengthDueToEchoOnOff(b_EchoMode, str_SIM5320E_Response, '?');
  COM.println(str_SIM5320E_Response.substring(ui8_AdditionalLength+22,ui8_AdditionalLength+28));
}

void GettingGPSReading (void)
{
  boolean b_DidGPSReceivedInfo  = NO;     // Default Value
  String  str_ReceivedResponse;
  
  while (b_DidGPSReceivedInfo == NO)
  {
    AT.CGPSINFO();
    str_ReceivedResponse = AT.ReceivedResponse("OK", b_PrintShortResponse);
    ui8_AdditionalLength = GetAddtionalLengthDueToEchoOnOff(b_EchoMode, str_ReceivedResponse, 'O');
    if (str_ReceivedResponse[ui8_AdditionalLength+12] == ',')
    {
      b_DidGPSReceivedInfo = NO;
      COM.println("No GPS Signal");
    }
    else
    {
      b_DidGPSReceivedInfo = YES;
      COM.println("GPS Signal Found");
      ConvertLatLng (str_ReceivedResponse);
    }
  }
}

void ConvertLatLng (String str_ReceivedResponse)
{
  String str_Latitude;
  String str_Longitude;
  str_Latitude = str_ReceivedResponse.substring(ui8_AdditionalLength+12,ui8_AdditionalLength+23); // latitude
  str_Longitude = str_ReceivedResponse.substring(ui8_AdditionalLength+26,ui8_AdditionalLength+38); // longitude
  COM.println(str_Latitude + "," + str_Longitude);
  
  // Latitude Conversion
  d_Latitude = ((str_Latitude[0] - ASCII_ZERO)*10.0)
             + ((str_Latitude[1] - ASCII_ZERO)*1.0)
             + ((((str_Latitude[2] - ASCII_ZERO)*10.0)
                +((str_Latitude[3] - ASCII_ZERO)*1.0)
                +((str_Latitude[5] - ASCII_ZERO)/10.0)
                +((str_Latitude[6] - ASCII_ZERO)/100.0)
                +((str_Latitude[7] - ASCII_ZERO)/1000.0)
                +((str_Latitude[8] - ASCII_ZERO)/10000.0)
                +((str_Latitude[9] - ASCII_ZERO)/100000.0)
                +((str_Latitude[10] - ASCII_ZERO)/1000000.0))/60.0);
                
  // Longitude Conversion
  d_Longitude = ((str_Longitude[0] - ASCII_ZERO)*100.0)
              + ((str_Longitude[1] - ASCII_ZERO)*10.0)
              + ((str_Longitude[2] - ASCII_ZERO)*1.0)
              + ((((str_Longitude[3] - ASCII_ZERO)*10.0)
                 +((str_Longitude[4] - ASCII_ZERO)*1.0)
                 +((str_Longitude[6] - ASCII_ZERO)/10.0)
                 +((str_Longitude[7] - ASCII_ZERO)/100.0)
                 +((str_Longitude[8] - ASCII_ZERO)/1000.0)
                 +((str_Longitude[9] - ASCII_ZERO)/10000.0)
                 +((str_Longitude[10] - ASCII_ZERO)/100000.0)
                 +((str_Longitude[11] - ASCII_ZERO)/1000000.0))/60.0);
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
      if(str_ATCommandResponse[ui16_index]== c_CharToLookoutFor)
      {
        ui8_AddLength = ui16_index+2;
        return ui8_AddLength;
      }
    }
  }
  else  ui8_AddLength = 0;
  
  return ui8_AddLength;
}

void GetTimeStamp (String str_ReceivedResponse)
{
  str_Timestamp = str_SIM5320E_Response.substring(ui8_AdditionalLength+10,ui8_AdditionalLength+12) // YY
                + str_SIM5320E_Response.substring(ui8_AdditionalLength+13,ui8_AdditionalLength+15) // MM
                + str_SIM5320E_Response.substring(ui8_AdditionalLength+16,ui8_AdditionalLength+18) // DD
                + str_SIM5320E_Response.substring(ui8_AdditionalLength+19,ui8_AdditionalLength+21) // hh
                + str_SIM5320E_Response.substring(ui8_AdditionalLength+22,ui8_AdditionalLength+24) // mm
                + str_SIM5320E_Response.substring(ui8_AdditionalLength+25,ui8_AdditionalLength+27);// ss
}
