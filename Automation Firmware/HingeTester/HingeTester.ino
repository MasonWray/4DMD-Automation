/*
 Name:		HingeTester.ino
 Created:	10/26/2022 7:48:02 PM
 Author:	Mason Wray
*/

#include <Adafruit_DotStar.h>

#include "src/StatusIndicator.h"


Adafruit_DotStar ds = Adafruit_DotStar(1, 8, 6, DOTSTAR_BGR);
StatusIndicator status = StatusIndicator(&ds);

void setup()
{
	status.begin();
	status.set(StatusIndicator::STARTING);
	Serial.begin(115200);
	while (!Serial)
	{
		status.update();
	}
	status.set(StatusIndicator::UPDATING);
	Serial.println("MobileDemand Hinge Failure Tester");
}

void loop()
{
	status.update();
}
