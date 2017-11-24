#ifndef ATCOMMAND_H_
#define ATCOMMAND_H_

#define YES       1
#define NO        0

class ATCommand
{
  public:
    void Setup(HardwareSerial &hws_SerialPort, uint32_t ui32_BaudRate);
    void cmd_write(String str_command);

    void AT(void);
    void E(boolean b_Value);
    void CGSN(void);

    void CPSI(String str_Command);

    void CGSOCKCONT(uint8_t ui8_Cid, String str_PDPType, String str_APN);
    void CIPMODE(boolean b_Mode);

    void NETOPEN(void);
    void CIPOPEN(uint8_t ui8_LinkNum, String str_Type, String str_ServerIP, uint16_t ui16_ServerPort);
    void CIPSEND(uint8_t ui8_LinkNum, uint8_t ui8_Length);
    void CIPCLOSE(uint8_t ui8_LinkNum);

    void CCLK(String str_Command);

    void CGPSINFO(void);

    String ReceivedResponse (String str_ExpectedResponse, boolean b_ToPrintResponse);
};

#endif  // ATCOMMAND_H_
