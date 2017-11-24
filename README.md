# SIM5320E-3G-Module

Initial Settings to be done to SIM5320E before connecting to Teensy 3.2 or any microcontroller

**Step 1:**
1. Start CoolTerm

2. Set baud rate to 115200 (Under “Options->Serial Port Options-> Baudrate:”)

3. Set terminal mode to “Line Mode” (Under “Options->Terminal Options-> Terminal Mode:”)

4. Click “Connect”

**Step 2:**
Wait for initial boot messages from SIM3520E.

**Info:** Below messages will appear after 15 seconds
```
START

+STIN: 25

+STIN: 25

+CPIN: READY

SMS DONE

PB DONE
```
**Info:** Below message will appear after 55 seconds

(Total waiting time: 70 secs = 15 + 55)
```
+STIN: 25
```
**Step 3**:
Set baud rate permanently using AT+IPREX
```
Send :	AT+IPREX=9600
Reply:	OK
```
**Step 4:**
Change baud rate to 9600 (Under “Options->Serial Port Options-> Baudrate:”)

**Step 5:**
Start GPS automatically upon next boot up of SIM5320E (AT+CGPSAUTO)
```
Send : 	AT+CGPSAUTO=1
Reply: 	OK
```
**Step 6:**
Enable automatic time and time zone via NITZ (AT+CTZU)
```
Send :	AT+CTZU=1
Reply:	OK
```
**Step 7:**
1. Click “Disconnect”

2. Click “Clear Data”

3. Unplug USB cable

4. Plug USB cable

5. Click “Connect”

6. Wait for initial boot messages (same as Step 2) from SIM3520E

**Step 8:**
Check if settings remain permanent
```
Send : 	AT+CGPSAUTO?
Reply: 	+CGPSAUTO:1
	
	OK
	
Send : 	AT+CTZU?
Reply: 	+CTZU: 1
	
	OK
```
**Step 9:**
Check Real Time Clock (AT+CCLK)
```
Send :	AT+CCLK?
Reply:	+CCLK: "yy/MM/dd,hh:mm:ss±zz"

	OK
```
**Step 10:**
Stop GPS session (AT+CGPS)
```	
Send :	AT+CGPS=0
Reply:	OK
```
**Info:** Below message will appear after 35 seconds
```
	+CGPS: 0
```
**Step 10:**
Cold start GPS session (AT+CGPSCOLD)
```
Send:	AT+CGPSCOLD
Reply:	OK
```
**Step 11:**
1. Wait for 120 seconds

2. Get GPS fixed position information (AT+CGPSINFO)
```
Send :	AT+CGPSCOLD
Reply:	+CGPSINFO: [<lat>],[<N/S>],[<log>],[<E/W>],[<date>],[<UTC time>],[<alt>],[<speed>],[<course>]

	AmpI/AmpQ: <AmpI>/<AmpQ>

	OK
```
