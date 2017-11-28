```
Set up done

START          -> SIM5320E is alive

+STIN: 25      -> SAT has return to Main Menu (AT+STIN)

+STIN: 25      -> SAT has return to Main Menu (AT+STIN)

+CPIN: READY   -> Not pending for any password (AT+CPIN)

SMS DONE       -> Detects SMS memory (AT Commands for SMS)
```
Wait for ~12 seconds upon power up of SIM5320E before message 'PB Done' appears
```
PB DONE        -> Detects PhoneBook memory (AT Commands for Phonebook)

OK

OK
```
Wait for ~65 seconds upon power up of SIM5320 before message '+STIN: 25' appears
```
+STIN: 25 -> Notification that SIM Application has returned to main menu.

+CPSI: System Mode,Operation Mode,MCC-MNC,LAC,Cell ID,Frequency Band,PSC,Freq,SCC,Ec/Io,RSCP,Qual,RxLev,TXPWR
OK
```
**AT+CPSI?**

 1.System Mode   : 'NO SERVICE', 'GSM', 'WCDMA'
 2.Operation Mode: 'Online', 'Offline', 'Factory Test Mode', 'Reset', 'Low Power Mode'
 3.MCC           : Mobile Country Code (first part of PLMN code)
 4.MNC           : Mobile Network Code (second part of PLMN code)
 5.LAC           : Location Area Code (hexadecimal digits)
 6.Cell ID       : Service-cell ID
 7.Frequency Band: Frequency Band of active set
 8.PSC           : Primary synchronization code of active set
 9.Freq          : Downlink frequency of active set
10.SSC           : Secondary synchronization code of active set
11.EC/IO         : Ec/Io value
12.RSCP          : Received Signal Code Power
13.Qual          : Quality value for base station selection
14.RxLev         : RX level value for base station selection
15.TXPWR         : UE TX power in dBm. If no TX, the value is 500
