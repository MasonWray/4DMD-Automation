/*
 Name:		HingeTester.ino
 Created:	10/26/2022 7:48:02 PM
 Author:	Mason Wray
*/

#define CONFIG_FILE "data.csv"

#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>

#include "src/StatusIndicator.h"
#include "src/flash_config.h"

Adafruit_DotStar ds = Adafruit_DotStar(1, 8, 6, DOTSTAR_BGR);
StatusIndicator status = StatusIndicator(&ds);

Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;

void setup()
{
	status.begin();
	status.set(StatusIndicator::STARTING);

	Serial.begin(115200);
	while (!Serial)
	{
		status.update();
	}

	if (!flash.begin())
	{
		Serial.println("Error, failed to initialize flash chip!");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	Serial.print("JEDEC ID: 0x");
	Serial.println(flash.getJEDECID(), HEX);
	Serial.print("Flash size: ");
	Serial.print(flash.size() / 1024);
	Serial.println(" KB");

	if (!fatfs.begin(&flash))
	{
		Serial.println("Error, failed to mount newly formatted filesystem!");
		Serial.println("Was the flash chip formatted with the fatfs_format example?");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}
	status.set(StatusIndicator::UPDATING);
	Serial.println("MobileDemand Hinge Failure Tester");

	File32 dataFile = fatfs.open(CONFIG_FILE, FILE_WRITE);
	if (dataFile)
	{
		dataFile.print("Hello!\n");
		dataFile.close();
		Serial.println("Wrote new data to file!");
	}
	else
	{
		status.set(StatusIndicator::ERR);
	}

	File32 readFile = fatfs.open(CONFIG_FILE, FILE_READ);
	if (!readFile) {
		Serial.println("Error, failed to open for reading!");
		while (1) yield();
	}
	String line = readFile.readStringUntil('\n');
	Serial.print(F("First line of test.txt: ")); Serial.println(line);
}

void loop()
{
	status.update();
}
