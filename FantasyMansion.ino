//ONLY TEMPO CHANGE ON BOOT!
//TUNE MODE OSCCAL?
// ARBITRARY BARLENGTHS?
//some times hiccups
# define birthdate 10023 //birthdate

#include <avr/pgmspace.h>
#include <avr/wdt.h>
/*Required modes
L+R = wait for sync signal and choose
just L send sync on drums
just R send sync on tones
*/

// funcs i'd like to add:
// OSCCAL+=1 OSCCAL+-1 mode
//steam
byte syncPin = 0; //0=normal 1=tones&sync 4=beat&sync
byte mask = B00000010;
int correctedx = 0;  //x adjusted for current light
byte mode = 1;  // 1 = myfirstsong, 2 = myfirstbeat

#define LED 1    //digital pin 1
#define LDR 1    //analog pin 1
#define LDRpin 2 //digital pin 2 
#define SW1 0
#define SW2 3
#define tonepin 4
#define portBpin 1

byte modulationSteps = 4;  //set in refreshrandom
int portBlength = 500;		//set in refreshrandom
byte playMode = 0;        //BOTH, BASS, MELODY
byte octaveselect = 0;

//unsigned long oldSyncPulseTime = 0;
unsigned long syncPeriod = 1;
unsigned int periodTimer = 10;

byte pip = 0;
int x = 0; //ldr value 0-600
int purex = 0; //raw LDR value 0-1024
byte diff = 0; 
byte xMode = 1;  // 0 = normal , 1 = insane pitch range, 2 = megapitchrange
int oldX = 0;
byte selex = 0;
int t = 0;             //drum portB timer
int s = 0;
int modTempo = 8;
uint32_t watchdogcounter = 0;


byte portBselector = 4;
//byte scalesOffset = 0;                                        //is this doing the same as root ?



int barTicker = 1;
//int scalesOffset = 10;   was used to select from premade scales, new code will generate scales on the fly ?
//byte selector = 1;//random(1, 17);
byte partTicker = 1;
byte songTicker = 1;
int modulationinterval = 0; //will to be set to something else if allowtranspose is true when refreshrandom is called
byte octOffset = 2;
byte distAmount = 0;
byte beatSeqSelex = 0;
//byte beatSeqSelexLookahead = 0;



struct bools {
	bool limbo : 1;							//define whether we are supposed to do a mode or not
	bool TMelOrFBass : 1;
	bool swing : 1;							//play with swing or not RANDOMIZE!
	bool inSignal : 1;							//state of sync in pin
	bool oldInSignal : 1;						//old state of insignal
	// bool doubleTime: 1;					// not used? not used
	bool syncTick : 1;							//ticker to make sure we only change sync pinstate once per tick
	bool sendSync : 1;							//flag to say we are sending sync
	bool receiveSync : 1;						//flag to say we are receiving sync
	bool tonesMode : 1;						//flag to say whether we are bothered with generating poly tones
	bool portBMode : 1;                        //flag whether we are in a mode that supports portb or not
   // bool transpose: 1;						//not needed was always true
	bool allowBDSeqMod : 1;					//will we allow BD seq to be changed ?
	bool allowSDSeqMod : 1;					//will we allow SD seq to be changed ?
	bool allowHHSeqMod : 1;					//will we allow HH seq to be changed ?
	bool leftSwitch : 1;						//STATE OF LEFT SWITCH
	bool rightSwitch : 1;						//STATE OF RIGHT SWITCH
	bool slowMo : 1;							//PLAY HALFTIME? IS USED BY SWING 
	bool portBticker : 1;						//TICKER FOR PORTBLENGTH COMPARISIN ONLY USED FOR LENGTH 
	bool oldLeftSwitch : 1;					//old state of leftSwitch
	bool oldRightSwitch : 1;					//old state of rightSwitch
	bool play : 1;								//are we playing
	bool doubleButt : 1;						//to make sure it only runs the doublebutt code once
	bool bend : 1;								//are we pitchbending?
	bool disablePortB : 1;						//portB (drums included) on or off
	bool firstRun : 1;							//first run of a mode, run the mode setup 
	bool myFirstSongMode : 1;					//user made melody?
   // bool myFirstBeatMode: 1;					//user made beat?      this one is used to determine whether to remake beats after partTicker goes past 2)
	bool writeNote : 1;						//flag the watchdoc function to add a note
	bool eraseNote : 1;						//flag the watchdog to remove a note
	//bool noteWritten: 1;					//not used
	bool preserveMelody : 1;					//flag to not overwrite melody
	//bool preserveBeat: 1;						//not used (preservemelody does this too
	bool allowNoteAddition : 1;				//are we allowed to add notes? 
	bool allowTranspose : 1;					 //notUsed
	bool BANG_L : 1;							//trigger once when left button is pressed
	bool BONG_L : 1;							//trigger once when left button is released
	bool BANG_R : 1;							//trigger once when right button is pressed
	bool BONG_R : 1;							//trigger once when right button is released
	bool beatWrite : 1;						//write to the beat
	bool beatErase : 1;						//erase this step of the beat
	bool ownBeat : 1;							//user made beat (is used by musicbox to determine whether to make new beats when beats are toggled back on)
	bool BASS : 1;								//bassline on off CONTROLLED BY NOTE PLAYER AND PART TICKER
	bool MELODY : 1;							//melody on off CONTROLLED BY NOTHING YET, CONTROL ME!!!!!!!!!!!!!!!!!!!!!!!!
	bool Arp : 1;								//if true chords are broken into arpeggios
	bool BASSOCT : 1;							//if true bass is one octave down
} bools = {
	.limbo = false,					//define whether we are supposed to do a mode or not
  .TMelOrFBass = true,
  .swing = false,
  .inSignal = false,
  .oldInSignal = true,
  .syncTick = false,
  .sendSync = false,
  .receiveSync = false,								//false = internal sync , true = external sync
  .tonesMode = true,
  .portBMode = true,                                //flag whether we are in a mode that supports portb or not
  .allowBDSeqMod = true,
  .allowSDSeqMod = true,
  .allowHHSeqMod = true,
  .leftSwitch = false,
  .rightSwitch = false,
  .slowMo = false,
  .portBticker = true,
  .oldLeftSwitch = false,
  .oldRightSwitch = false,
  .play = false,
  .doubleButt = false,
  .bend = false,
  .disablePortB = false,
  .firstRun = true,
  .myFirstSongMode = false,
  .writeNote = false,
  .eraseNote = false,
  .preserveMelody = false,
  .allowNoteAddition = false, //needs implementing properly
  .allowTranspose = false,
  .BANG_L = false,
  .BONG_L = false,
  .BANG_R = false,
  .BONG_R = false,
  .beatWrite = false,
  .beatErase = false,
  .ownBeat = false,
  .BASS = true,
  .MELODY = true,
  .Arp = true,
  .BASSOCT = true,
};

int bender = 0;

byte a = random(1, 20);
byte b = random(1, 20);
byte c = random(5, 31);

unsigned int BDseq = 0b1000000010000000;
unsigned int SDseq = 0b1111111111111111;
unsigned int HHseq = 0b0000000000000000;
//byte modsSeq[16] = {3,3,3,3,3,3,3,3,5,5,4,4,4,3,4,3};//0b1111000010000000;
byte mood = 4; //how fast the t increases
//byte portBlengths[8] = {50000,1000,500,600,2500,300,500,666};




byte arpLength = 9;
#define initBarLength 32
byte barLength = initBarLength;

// here are the notes pitches bitches
const uint16_t PROGMEM Scale[32] = {
  681,  721,  764,  809,  858,  909,  963, 1020, 1080, 1145, 1213, 1286,
  1362, 1429, 1529, 1620, 1716, 1818, 1926, 2041, 2162, 2291, 2427, 2571,
  2724, 2886, 3058, 3240, 3432, 3636, 3850, 4080
};

//byte bassTempo = 4;
byte scaleSelect = 0; //0 = minor    1 = major    2 = penta 


//can be moved to progmem
byte currentScale[15]{														//5 per scale!!!
  0, 3, 7, 10, 12,//minor
  0, 4, 7, 11, 12, //major
  0, 2, 5, 7, 9 //pentatonic
};

byte chordIntervalSelector = 0; //0 Minor, 1 Major, 3 Power

//can be moved to progmem
const byte chordIntevals[9]{
  0, 3,  7,      //MINOR
  0, 4,  7,      //MAJOR
  0, 5, 12       //POWER
};

#define Channels 4
//byte baseTempo = 3;
//byte Tempo = 4;      // 4 = 4 beats per second
byte Decay = 10;    // Length of note decay; max 10

unsigned int Acc[Channels];   //should be volatile ?
unsigned int Freq[Channels];  //should be volatile ?
unsigned int Amp[Channels];

//unsigned long Chords[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //This is the chords we will be playing and modifying
unsigned long Chords[initBarLength] = {
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000010000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000010000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000010000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000010000,
  0B00000000000000000000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000000000000000000000,
  0B00000000000000000000000000010000,
  0B00000000000000000000000000000000
  /* 0B00000000000000001000000000000000,
   0B00000000000000000100000000000000,
   0B00000000000000000010000000000000,
   0B00000000000000000001000000000000,
   0B00000000000000000000100000000000,
   0B00000000000000000000010000000000,
   0B00000000000000000000001000000000,
   0B00000000000000000000000100000000,
   0B00000000000000000000000010000000,
   0B00000000000000000000000001000000,
   0B00000000000000000000000000100000,
   0B00000000000000000000000000010000,
   0B00000000000000000000000000001000,
   0B00000000000000000000000000000100,
   0B00000000000000000000000000000010,
   0B00000000000000000000000000000001,
   */
};
/*

*/



//int doublers = 0B0001000100000000;                                                                            //NOT YET IMPLEMENTED
//byte amps[16]{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };                                             //DECAYS ARE ACTUALLY LOUDNESS!
//int dists = 0B0001000100010001;
//int dists = 0B0010010010010001;
int dists = 0B0000000000000000;

//byte octArray[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//byte octArray = 0B1010101010101010;
int octArray = 0B0000000000000000;
byte root = 12;


unsigned int ChordsB[initBarLength] = {
  0B0000000000001000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000001000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000001000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000
  /*
  0B0000000100000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000100000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000100000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000100000000,
  0B0000000000000000,
  0B0000000000000000,
  0B0000000100000000,
  0B0000000000000000,
  0B0000000000000000
  */

};





const uint8_t  soloScales[15]{
  0, 3, 7, 10, 12, //minor
  0, 4, 7, 11, 12, //major
  0, 2, 5, 7, 9 //pentatonic
};


//Globals persist throughout tune
byte TunePtr = 0, Chan = 0;


void setup() {


	//DDRB = B00010010;
	pinMode(tonepin, OUTPUT);
	pinMode(portBpin, OUTPUT);
	pinMode(SW1, INPUT_PULLUP);
	pinMode(SW2, INPUT_PULLUP);
	pinMode(LDRpin, INPUT_PULLUP);


	///BOOTMODES///

	if (!digitalRead(SW1) && !digitalRead(SW2)) { // if both buttons are pushed upon boot
		pinMode(tonepin, INPUT);
		pinMode(portBpin, INPUT);
		bools.allowTranspose = true;
		while (syncPin == 0) {                    //check witch one is released first to decide sync mode  //0=normal 1=tones&sync 4=beat&sync
			if (digitalRead(portBpin)) {			  //if the portBpin recieves a pulse, set mode to sync in on portBpin
				bools.portBMode = false;
				bools.receiveSync = true;
				syncPin = portBpin;
				pinMode(tonepin, OUTPUT);
				mask = B00000000; // if we are in tones and sync mode, we dont want to let portBs out of the portBpin! ALL PORTB GENERATORS SHOULD BE MUTED
			}
			else if (digitalRead(tonepin)) {
				bools.tonesMode = false;
				syncPin = tonepin;                          //received sync on tonepin means syncPin 40, listen to sync on tones pin and play portB ///////////////////////////////////////////////////////////////////////////
				pinMode(portBpin, OUTPUT);
				bools.receiveSync = true;
				bools.portBMode = true;
				mode = 4;
				
			}
			while (!digitalRead(SW1) || !digitalRead(SW2)) {
				//wait
	}

			/*
//OLD CODE TO CHECK WHAT BUTT IS RELEASED FIRST
			if (digitalRead(SW1)) {                 // TONES OUT AND SYNC OUT /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				bools.portBMode = false;
				bools.tonesMode = true;
				bools.sendSync = true;
				syncPin = 1;
				mask = B00000000; // if we are in tones and sync mode, we dont want to let portBs out of the portBpin! ALL PORTB GENERATORS SHOULD BE MUTED

			}
			else if (digitalRead(SW2)) {          // PORTB OUT AND SYNC OUT /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				bools.portBMode = true;
				bools.tonesMode = false;
				bools.sendSync = true;
				syncPin = 4;
				mask = B00000010;

			}
			*/
		}

	}
	else if (!digitalRead(SW1)) {             //only SW1 means mode 10  START RIGHT IN TONES WRITING MODE PERHAPS? ////////////////////////////////////////////////////////////////////////////////
		bools.portBMode = false;
		bools.tonesMode = true;
		bools.sendSync = true;
		syncPin = 1;
		mask = B00000000; // if we are in tones and sync mode, we dont want to let portBs out of the portBpin! ALL PORTB GENERATORS SHOULD BE MUTED


	}
	else if (!digitalRead(SW2)) {             //only SW2 means mode 20 start right on beats prog pergaps? /////////////////////////////////////////////////////////////////////////////////////////
		bools.portBMode = true;
		bools.tonesMode = false;
		bools.sendSync = true;
		syncPin = 4;
		mask = B00000010;

	}
	else {
		bools.allowTranspose = true;
		//bools.portBMode = true;
		//bools.tonesMode = true;
		//TESTZONE///
		// bools.portBMode = true;
		// bools.tonesMode = false;
		// bools.sendSync = true;
		// syncPin = 4;
		// mask = B00000010;
		//TESTZONE///
	}




	int randSeed = (analogRead(LDR));
	digitalWrite(portBpin, HIGH); //turn on a light to get reflection info to use as second part of randseed
	//delay(200);

	randSeed = randSeed + (analogRead(LDR)) + birthdate;
	randomSeed(randSeed);
	
	PLLCSR = 1 << PCKE | 1 << PLLE;                                                       //can remove
	// Set up Timer/Counter1 for PWM output
	TIMSK = 0;                     // Timer interrupts OFF
	TCCR1 = 1 << CS10;             // 1:1 prescale
	GTCCR = 1 << PWM1B | 2 << COM1B0; // PWM B, clear on match

	OCR1B = 128;  //timer counts to 128 then loops back


	// Set up Timer/Counter0 for 20kHz interrupt to output samples.
	//TCCR0A = 3 << WGM00;           // Fast PWM                                            //can remove
	TCCR0B = 1 << WGM02 | 2 << CS00; // 1/8 prescale
	OCR0A = 99;                    // Divide by 100
	TIMSK = 1 << OCIE0A;           // Enable compare match, disable overflow
	OSCCAL += 2;

	// Set up Watchdog timer for 4 Hz interrupt for note output.
	WDTCR = 1 << WDIE | 0 << WDP0; // 4 Hz interrupt
	//setup_watchdog
	sei();


	//generate beats and melodie  gener8BDbeat();
	gener8SDbeat();
	gener8hats();
	//gener8Melody();
	//melodyTEST();
	refreshRandom();
	generateDists();

}


void loop() {
	//if(periodTimer<syncPeriod){
	//playNoteNow(periodTimer, octaveselect, 2);
	//}

	if (bools.portBMode) {
		portB();
	}
	pinRead();          //check the states of the pins
	BANGdetectors();
	modeHandle();       //cycle throuth the modes when necessary


	if (bools.syncTick) {
		digitalWrite(syncPin, !((selex + 1) % 2));
		bools.syncTick = false;
	}
	modeSelect();
}



ISR(TIMER0_COMPA_vect) {
	if (bools.tonesMode) {
		generatePolyTones();
	}
	s++;
	periodTimer++;
}