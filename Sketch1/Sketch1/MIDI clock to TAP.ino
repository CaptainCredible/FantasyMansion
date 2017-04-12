#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This example shows the old way of checking for input messages.
// It's simpler to use the callbacks now, check out the dedicated example.

#define LED 10                   // LED pin on Arduino Uno
unsigned int ledTimer = 0;

// -----------------------------------------------------------------------------

void BlinkLed()         // Basic blink function
{
	
	
		digitalWrite(LED, HIGH);
		ledTimer = millis();
	
}

void handleLedOff() {
	if (millis() - ledTimer > 100) {
		digitalWrite(LED, LOW);
	}
}

// -----------------------------------------------------------------------------

void setup()
{
	pinMode(LED, OUTPUT);
	MIDI.begin();           // Launch MIDI, by default listening to channel 1.
}

void loop()
{
	if (MIDI.read())                // Is there a MIDI message incoming ?
	{
		switch (MIDI.getType())      // Get the type of the message we caught
		{
		case midi::Clock// If it is a Program Change,
			BlinkLed();  // blink the LED a number of times
			break;
			// See the online reference for other message types
		default:
			break;
		}
		handleLedOff();
	}
}