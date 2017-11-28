## SimpleSIM5320E
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
```
AT+CPSI?
```
+CPSI: System Mode,Operation Mode,MCC-MNC,LAC,Cell ID,Frequency Band,PSC,Freq,SCC,Ec/Io,RSCP,Qual,RxLev,TXPWR
OK
```
**AT+CPSI**

+ System Mode   : 'NO SERVICE', 'GSM', 'WCDMA'
+ Operation Mode: 'Online', 'Offline', 'Factory Test Mode', 'Reset', 'Low Power Mode'
+ MCC           : Mobile Country Code (first part of PLMN code)
+ MNC           : Mobile Network Code (second part of PLMN code)
+ LAC           : Location Area Code (hexadecimal digits)
+ Cell ID       : Service-cell ID
+ Frequency Band: Frequency Band of active set
+ PSC           : Primary synchronization code of active set
+ Freq          : Downlink frequency of active set
+ SSC           : Secondary synchronization code of active set
+ EC/IO         : Ec/Io value
+ RSCP          : Received Signal Code Power
+ Qual          : Quality value for base station selection
+ RxLev         : RX level value for base station selection
+ TXPWR         : UE TX power in dBm. If no TX, the value is 500
