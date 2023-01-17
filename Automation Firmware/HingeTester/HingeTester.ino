/*
 Name:		HingeTester.ino
 Created:	10/26/2022 7:48:02 PM
 Author:	Mason Wray
*/

#define EN_PIN 11
#define DR_PIN 12
#define ST_PIN 13
#define M0_PIN 7
#define M1_PIN 9
#define M2_PIN 10

#define CONFIG_FILE "data.csv"
#define SERIAL_DELAY 15000
#define DRIVER_DELAY 500

#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>
#include <ArduinoJson.h>
#include "src/StatusIndicator.h"
#include "src/flash_config.h"

Adafruit_DotStar ds = Adafruit_DotStar(1, 8, 6, DOTSTAR_BGR);
StatusIndicator status = StatusIndicator(&ds);

Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;
StaticJsonDocument<256> cfg;

int cfg_num_steps = 800;
int cfg_period = 10;
int cfg_interval_base = 150;
int cfg_interval_variance = 1000;
int cfg_cycles = 1000;

bool dir = false;
int pos = 0;
int cycle_count = 0;

bool enter_config = false;
//String command = "";
String input = "";

void setup()
{
	// Configure microstepping
	pinMode(M0_PIN, OUTPUT);
	pinMode(M1_PIN, OUTPUT);
	pinMode(M2_PIN, OUTPUT);
	digitalWrite(M0_PIN, HIGH);
	digitalWrite(M1_PIN, LOW);
	digitalWrite(M2_PIN, HIGH);

	// Configure driver step pins
	pinMode(EN_PIN, OUTPUT);
	pinMode(ST_PIN, OUTPUT);
	pinMode(DR_PIN, OUTPUT);
	delay(DRIVER_DELAY);
	digitalWrite(EN_PIN, HIGH);
	digitalWrite(DR_PIN, HIGH);
	dir = true;

	// Start status LED controller
	status.begin();
	status.set(StatusIndicator::STARTING);

	// Wait for serial connection
	Serial.begin(115200);
	int serial_timer = millis();
	while (millis() - serial_timer < SERIAL_DELAY)
	{
		status.update();
		if (Serial)
		{
			enter_config = true;
			break;
		}
	}

	// Initialize flash chip
	if (!flash.begin())
	{
		Serial.println("Error, failed to initialize flash chip!");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	if (!fatfs.begin(&flash))
	{
		Serial.println("Error, failed to mount newly formatted filesystem!");
		Serial.println("Was the flash chip formatted with the fatfs_format example?");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	status.set(StatusIndicator::NORMAL);
	loadConfig();
	Serial.println("MobileDemand Hinge Failure Tester");
}

void loadConfig()
{
	if (!fatfs.exists(CONFIG_FILE))
	{
		Serial.println("Config file not found, restoring defaults");
		saveConfig();
	}

	File32 readFile = fatfs.open(CONFIG_FILE, FILE_READ);
	if (!readFile)
	{
		status.set(StatusIndicator::ERR);
		Serial.println("Error, failed to open config file");
		return;
	}

	String json = readFile.readStringUntil('\n\r');
	DeserializationError deser_status = deserializeJson(cfg, json);

	if (deser_status != DeserializationError::Ok)
	{
		status.set(StatusIndicator::ERR);
		Serial.println("Error, failed to parse config JSON");
		return;
	}

	cfg_num_steps = cfg["steps"];
	cfg_cycles = cfg["cycles"];
	cfg_interval_base = cfg["interval_base"];
}

void saveConfig()
{
	cfg["steps"] = cfg_num_steps;
	cfg["cycles"] = cfg_cycles;
	cfg["interval_base"] = cfg_interval_base;

	String output;
	serializeJson(cfg, output);

	if (fatfs.exists(CONFIG_FILE))
	{
		fatfs.remove(CONFIG_FILE);
	}

	File32 dataFile = fatfs.open(CONFIG_FILE, FILE_WRITE);
	if (dataFile)
	{
		dataFile.println(output.c_str());
		dataFile.close();
	}
	else
	{
		status.set(StatusIndicator::ERR);
	}
}

void step()
{
	digitalWrite(ST_PIN, HIGH);
	delayMicroseconds(cfg_period);
	digitalWrite(ST_PIN, LOW);
}

int calcDelay(int period, int base, int variance, int length, int pos)
{
	double x = (double)pos / (double)length;
	double adj = ((cos(2.0 * PI * x) / 2.0) + 0.5) * (double)variance;
	return base + round(adj) - period;
}

void loop()
{
	// Enter REPL is serial connection exists
	if (enter_config)
	{
		status.update();
		if (Serial.available())
		{
			char i = Serial.read();
			if (i != '\n' && i != '\r')
			{
				Serial.print(i);
				input.concat(i);
			}
			else
			{
				Serial.println();
				int separator = input.indexOf(' ');
				String cmd = separator > -1 ? input.substring(0, separator) : input;
				String arg = separator > -1 && separator != input.length() - 1 ? input.substring(separator + 1, input.length()) : "";

				if (cmd.equalsIgnoreCase("STEPS"))
				{
					cfg_num_steps = arg.toInt();
					Serial.printf("Setting step count to %d\n\r", cfg_num_steps);
					saveConfig();
				}
				else if (cmd.equalsIgnoreCase("CYCLES"))
				{
					cfg_cycles = arg.toInt();
					Serial.printf("Setting cycle count to %d\n\r", cfg_cycles);
					saveConfig();
				}
				else if (cmd.equalsIgnoreCase("INTERVAL"))
				{
					cfg_interval_base = arg.toInt();
					Serial.printf("Setting base interval duration to %d\n\r", cfg_interval_base);
					saveConfig();
				}
				else if (cmd.equalsIgnoreCase("VIEW"))
				{
					loadConfig();
					Serial.printf("\n\rCurrent Config\n\r--------------\n\r");
					Serial.printf("CYCLES   : %d\n\r", cfg_cycles);
					Serial.printf("STEPS    : %d\n\r", cfg_num_steps);
					Serial.printf("INTERVAL : %dms\n\r", cfg_interval_base);
				}
				else if (cmd.equalsIgnoreCase("HELP"))
				{
					Serial.println();
					Serial.println("Enter a command followed my an numeric argument, if applicable (specified by [n]). Commands are case-insensitive. Do not include the [] when using commands.\n\r");
					Serial.println("STEPS [n]   \n\r   Define the number of steps in one half sweep, top-to-bottom or bottom-to-top.\n\r");
					Serial.println("CYCLES [n]  \n\r   Define the number of full sweeps the tester should make before concluding the test.\n\r");
					Serial.println("INTERVAL [n]\n\r   The base (minimum) delay between steps. Correspends to inverse of sweep speed. Will be increased at ends of sweep according to acceleration curve.\n\r");
					Serial.println("VIEW        \n\r   Load and display the current test configuration.");
					Serial.println("HELP        \n\r   Display this help message over serial.\n\r");
					Serial.println("EXIT        \n\r   Exit the configuration menu. Start the execution sequence immediately.\n\r");
				}
				else if (cmd.equalsIgnoreCase("EXIT"))
				{
					Serial.println("Exiting config");
					enter_config = false;
				}
				else
				{
					Serial.printf("Unrecognized command: '%s'\n\r", cmd.c_str());
				}
				input = "";
			}
		}
	}

	// Start operation if config session is not requested
	else
	{
		status.update();
		if (cycle_count <= cfg_cycles)
		{
			if (pos <= 0)
			{
				pos = 0;
				dir = true;
				digitalWrite(DR_PIN, HIGH);
				status.set(StatusIndicator::NORMAL);
				cycle_count++;
			}

			if (pos >= cfg_num_steps)
			{
				pos = cfg_num_steps;
				dir = false;
				digitalWrite(DR_PIN, LOW);
				status.set(StatusIndicator::WARN);
			}

			if (dir)
			{
				pos++;
			}
			else
			{
				pos--;
			}

			step();
			int t = calcDelay(cfg_period, cfg_interval_base, cfg_interval_variance, cfg_num_steps, pos);
			delayMicroseconds(t);
		}
	}
}
