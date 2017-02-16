#include <avr/pgmspace.h>


byte syncPin = 0; //0=normal 1=tones&sync 4=beat&sync
byte mask = B00000010;
/*
    TO DO
    toggle AMP multiplier to turn dist on and off
    make it play arpeggios
    make it switch to neart ??? every 8 steps perhaps

*/

# define birthdate 31751 //birthdate

bool syncFlipFlop = false;

byte mode = 10;


//byte pinBstate =
#define numberOfModes 10
#define LED 1    //digital pin 1
#define LDR 1    //analog pin 1
#define LDRpin 2 //digital pin 2 
#define SW1 0
#define SW2 3
#define tonepin 4
#define portBpin 1

byte modulationSteps = 4;
int portBlength = 500;
byte playMode = 0; //BOTH, BASS, MELODY
byte octaveselect = 0;

unsigned long oldSyncPulseTime = 0;
unsigned long syncPeriod = 1;
unsigned int periodTimer = 10;


//byte oct;
int x = 0; //ldr value 0-600
byte diff = 0;
byte xMode = 0;
int oldX = 0;
byte selex = 0;
int t = 0;             //drum portB timer
int s = 0;

byte melodyOffset = 4;
byte melodyOffsetOffset = 4;
byte scalesOffset = 0;

int barTicker = 1;
//int scalesOffset = 10;   was used to select from premade scales, new code will generate scales on the fly ?
//byte selector = 1;//random(1, 17);
byte partTicker = 1;
byte songTicker = 1;
int modulationinterval = 2;
byte octOffset = 2;
byte distAmount = 0;
byte beatSeqSelex = 0;
//byte beatSeqSelexLookahead = 0;



struct bools {
  bool swing: 1;
  bool inSignal: 1;
  bool doubleTime: 1;
  bool oldInSignal: 1;
  bool syncTick: 1;
  bool sendSync: 1;
  bool receiveSync: 1;
  bool tonesMode: 1;
  bool portBMode: 1;                        //flag whether we are in a mode that supports portb or not
  bool transpose: 1;
  bool allowBDSeqMod: 1;
  bool allowSDSeqMod: 1;
  bool allowHHSeqMod: 1;
  bool leftSwitch: 1;
  bool rightSwitch: 1;
  bool slowMo: 1;
  bool portBticker: 1;
  bool oldLeftSwitch: 1;
  bool oldRightSwitch: 1;
  bool play: 1;
  bool doubleButt: 1;     //to make sure it only runs the doublebutt code once
  bool bend: 1;
  bool disablePortB: 1;
  bool firstRun: 1;
  bool myFirstSongMode: 1;
  bool myFirstBeatMode: 1;
  bool writeNote: 1;
  bool eraseNote: 1;
  bool noteWritten: 1;                 //not used
  bool preserveMelody: 1;
  bool preserveBeat: 1;               //not used (preservemelody does this too
  bool allowNoteAddition: 1;
  bool allowTranspose: 1;             //notUsed
  bool BANG_L: 1;
  bool BONG_L: 1;
  bool BANG_R: 1;
  bool BONG_R: 1;
  bool beatWrite: 1;
  bool beatErase: 1;
  bool ownBeat: 1;
  bool BASS: 1;
  bool MELODY: 1;
} bools = {
  .swing = false,
  .inSignal = false,
  .doubleTime = true,
  .oldInSignal = true,
  .syncTick = false,
  .sendSync = false,
  .receiveSync = false,								//false = internal sync , true = external sync
  .tonesMode = true,	
  .portBMode = true,                                //flag whether we are in a mode that supports portb or not
  .transpose = true,
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
  .myFirstBeatMode = false,
  .writeNote = false,
  .eraseNote = false,
  .noteWritten = false,
  .preserveMelody = false,
  .preserveBeat = false,
  .allowNoteAddition = false,
  .allowTranspose = true,
  .BANG_L = false,
  .BONG_L = false,
  .BANG_R = false,
  .BONG_R = false,
  .beatWrite = false,
  .beatErase = false,
  .ownBeat = false,
  .BASS = true,
  .MELODY = true,
};

byte decayArray[16] = {
	6,7,7,6,7,7,8,7,3,7,7,2,7,7,7,1
};



int bender = 0;

byte a = random(1, 20);
byte b = random(1, 20);
byte c = random(5, 31);

unsigned int BDseq =   0b1000000010000000;
unsigned int SDseq =   0b1111111111111111;
unsigned int HHseq =   0b0000000000000000;
//byte modsSeq[16] = {3,3,3,3,3,3,3,3,5,5,4,4,4,3,4,3};//0b1111000010000000;
int mood = 3; //how fast the t increases
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

byte bassTempo = 4;
byte scaleSelect = 0; //0 = minor    1 = major    2 = penta 


//can be moved to progmem
byte currentScale[15] {
  0, 3, 7, 10, 12,//minor
  0, 4, 7, 11, 12, //major
  0, 2, 5, 7, 9 //pentatonic
};

byte chordIntervalSelector = 0; //0 Minor, 1 Major, 3 Power

//can be moved to progmem
const byte chordIntevals[9] {
  0, 3,  7,      //MINOR
  0, 4,  7,      //MAJOR
  0, 5, 12       //POWER
};

#define Channels 4
byte baseTempo = 3;
byte Tempo = 4;      // 4 = 4 beats per second
byte Decay = 6;    // Length of note decay; max 10

unsigned int Acc[Channels];   //should be volatile ?
unsigned int Freq[Channels];  //should be volatile ?
unsigned int Amp[Channels];

//unsigned long Chords[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //This is the chords we will be playing and modifying
unsigned long Chords[32] = {
  0B10000000000000000000000000000000,
  0B01000000000000000000000000000000,
  0B00100000000000000000000000000000,
  0B00010000000000000000000000000000,
  0B00001000000000000000000000000000,
  0B00000100000000000000000000000000,
  0B00000010000000000000000000000000,
  0B00000001000000000000000000000000,
  0B00000000100000000000000000000000,
  0B00000000010000000000000000000000,
  0B00000000001000000000000000000000,
  0B00000000000100000000000000000000,
  0B00000000000010000000000000000000,
  0B00000000000001000000000000000000,
  0B00000000000000100000000000000000,
  0B00000000000000010000000000000000,
  0B00000000000000001000000000000000,
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
};
/*

*/



int doublers = 0B0001000100000000;                                                                            //NOT YET IMPLEMENTED
byte decays[16] {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};                                             //DECAYS ARE ACTUALLY LOUDNESS!
unsigned long dists = 0B00000000000000000000000000000000;
//byte octArray[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
byte octArray = 0B0000000000000000;
byte root = 12;


unsigned int ChordsB[32] = {
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
  0B0000000000000000,
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

};





const uint8_t PROGMEM soloScales[15] {
  0, 3, 7, 10, 12,//minor
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
    while (syncPin == 0) {                    //check witch one is released first to decide sync mode  //0=normal 1=tones&sync 4=beat&sync

      if (digitalRead(SW1)) {                 // TONES OUT AND SYNC OUT /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bools.portBMode = false;
        bools.tonesMode = true;
        bools.sendSync = true;
        syncPin = 1;
        mask = B00000000; // if we are in tones and sync mode, we dont want to let portBs out of the portBpin! ALL PORTB GENERATORS SHOULD BE MUTED

      } else if (digitalRead(SW2)) {          // PORTB OUT AND SYNC OUT /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bools.portBMode = true;
        bools.tonesMode = false;
        bools.sendSync = true;
        syncPin = 4;
        mask = B00000010;

      }
    }
  } else if (!digitalRead(SW1)) {             //only SW1 means mode 10  START RIGHT IN TONES WRITING MODE PERHAPS? ////////////////////////////////////////////////////////////////////////////////
    syncPin = 100;
    bools.portBMode = true;
    bools.tonesMode = true;
    while (!digitalRead(SW1)) {


      if (!digitalRead(SW2)) {                //SW1 + SW2 means mode 10, SYNCIN ON PORTBPIN!!! ////////////////////////////////////////////////////////////////////////////////////////////////////
        syncPin = 1;  //syncPin 30 is listen to sync and play tones
        pinMode(portBpin, INPUT);
        bools.receiveSync = true;
        bools.portBMode = false;
        bools.tonesMode = true;
      }
    }

  } else if (!digitalRead(SW2)) {             //only SW2 means mode 20 start right on beats prog pergaps? /////////////////////////////////////////////////////////////////////////////////////////
    syncPin = 100;
    bools.portBMode = true;
    bools.tonesMode = true;
    while (!digitalRead(SW2)) {
      if (!digitalRead(SW1)) {
        syncPin = 4;                          //switch2 + 1 means syncPin 40, listen to sync on tones pin and play portB ///////////////////////////////////////////////////////////////////////////
        pinMode(tonepin, INPUT);
        bools.receiveSync = true;
        bools.tonesMode = false;
        bools.portBMode = true;
      }
    }
  } else {

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
  delay(200);

  randSeed = randSeed + (analogRead(LDR)) + birthdate;
  digitalWrite(portBpin, LOW);
  randomSeed(randSeed);
  //randomSeed(100);
  //refreshRandom();
  //gener8BD();
  //Enable 64 MHz PLL and use as source for Timer1
  //PLLCSR = 1 << PCKE | 1 << PLLE;                                                       //can remove
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
  WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt

  
  //generate beats and melodie  gener8BDbeat();
  gener8SDbeat();
  gener8hats();
  //gener8Melody();
  //melodyTEST();
  refreshRandom();
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
  xManip(xMode);   // manipulate x value : 1=insanepitchrange 2=megapitchrange 0 = donothing
  if (!bools.bend) {
    bender = 0;
  }
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
