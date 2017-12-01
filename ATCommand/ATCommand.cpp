#include <Arduino.h>
#include "ATCommand.h"

#define COM       Serial

HardwareSerial* hws_SerialPortSelected;

// Set up baud rate with selected serial port
void ATCommand::Setup(HardwareSerial &hws_SerialPort, uint32_t ui32_BaudRate)
{
  hws_SerialPortSelected = &hws_SerialPort;
  hws_SerialPortSelected->begin(ui32_BaudRate);
  while (!hws_SerialPortSelected);
  COM.println("Set up done");
}

void ATCommand::cmd_write(String str_command)
{
  str_command = str_command + "\r\n";
  hws_SerialPortSelected->print(str_command);
  delay(10);
  while (!hws_SerialPortSelected);
}

// Basic AT Commands according V.25TER

// Test AT startup
void ATCommand::AT(void)
{
  cmd_write("AT");
}

/*
 * ATE Enable command echo
 * Description: This command sets whether or not the AT echoes characters.
 * Defined values:
 * 0 - Echo mode off
 * 1 - Echo mode on
 */
void ATCommand::E(boolean b_Value)
{
  cmd_write("ATE"+(String)b_Value);
}

/* AT+CGSN Request product serial number identification
 * Decription: This command requests product serial number identification text,
 * which is intended to permit the user of the Module to identify the individual
 * ME to which it is connected to.
 */
void ATCommand::CGSN(void)
{
  cmd_write("AT+CGSN");
}

// AT Commands for Network

/* AT+CPSI Inquiring UE system information
 * Decription: This command is used to return the UE system information.
 * str_Command: "=?", "?", "=<time>"
 */
void ATCommand::CPSI(String str_Command)
{
  cmd_write("AT+CPSI"+str_Command);
}

// AT Commands for Internet Service - Common
/* AT+CGSOCKCONT
 *
 */
void ATCommand::CGSOCKCONT(uint8_t ui8_Cid, String str_PDPType, String str_APN)
{
  cmd_write("AT+CGSOCKCONT="+(String)ui8_Cid+",\""+str_PDPType+"\",\""+str_APN+"\"");
}

// AT Commands for Internet Service - TCP/UDP
/* AT+CIPMODE
 *
 */
void ATCommand::CIPMODE(boolean b_Mode)
{
  cmd_write("AT+CIPMODE="+(String)b_Mode);
}

/* AT+NETOPEN
 *
 */
 void ATCommand::NETOPEN(void)
 {
   cmd_write("AT+NETOPEN");
 }

 /* AT+CIPOPEN
  *
  */
  void ATCommand::CIPOPEN(uint8_t ui8_LinkNum, String str_Type, String str_ServerIP, uint16_t ui16_ServerPort)
  {
    cmd_write("AT+CIPOPEN="+(String)ui8_LinkNum+",\""+str_Type+"\",\""+str_ServerIP+"\","+(String)ui16_ServerPort);
  }

  /* AT+CIPSEND
   *
   */
   void ATCommand::CIPSEND(uint8_t ui8_LinkNum, uint8_t ui8_Length)
   {
     //cmd_write("AT+CIPSEND=0,42");
     cmd_write("AT+CIPSEND="+(String)ui8_LinkNum+","+(String)ui8_Length);
   }

  /* AT+CIPCLOSE
   *
   */
   void ATCommand::CIPCLOSE(uint8_t ui8_LinkNum)
   {
     cmd_write("AT+CIPCLOSE="+(String)ui8_LinkNum);
   }

// AT Commands for Status Control

/* AT+CCLK Real time clock management
 * Description: This command is used to manage Real Time Clock of the module.
 * str_Command: "=?", "?", "=<time>"
 */
void ATCommand::CCLK(String str_Command)
{
  cmd_write("AT+CCLK"+str_Command);
}

// AT Commands for GPS
/* AT+CGPSINFO Get GPS fixed position information
 * Description: This command is used to get current position information.
 */
void ATCommand::CGPSINFO(void)
{
  cmd_write("AT+CGPSINFO");
}

// Response from AT commands
// ReturnResponse to read string from serial port
String ATCommand::ReceivedResponse (String str_ExpectedResponse, boolean b_ToPrintResponse)
{
  String str_ATCommandResponse;

  boolean b_RRFlag = false;
  //COM.print(str_ExpectedResponse);
  while (b_RRFlag == false)
  {
    str_ATCommandResponse = hws_SerialPortSelected->readString();

    for (uint16_t ui16_index=0; ui16_index<str_ATCommandResponse.length(); ui16_index++)
    {
      if(b_ToPrintResponse == NO)
        COM.print(str_ATCommandResponse[ui16_index]);
      if(str_ATCommandResponse[ui16_index]== str_ExpectedResponse[0] && str_ATCommandResponse[ui16_index+1]==str_ExpectedResponse[1])
      {
        if(b_ToPrintResponse == YES)
          COM.println(str_ExpectedResponse);
        b_RRFlag = true;
      }
    }
  }
  return str_ATCommandResponse;
}
