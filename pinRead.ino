void pinRead() {
  //GET x

  if (plex) {                           //plex makes it read LDR

    x = (analogRead(LDR) * -1) + 1024; //invert the range (because it is pullup)
    x = x - 400;
    if (x < 0) {                      
      x = 0;                          //make 400 the floor
    } else if (x > 600) { 
      x = 600;                        //make 600 the ceiling 
    }
    if (bend) {
      bender = x;
    } else {
      bender = 0;
    }
    plex = false;                     //this simply makes it pause for one iteration. not useful?
  } else {
    plex = true;                      //this simply makes it pause for one iteration. not useful?
  }

  byte pinState = PINB;
  leftSwitch = !bitRead(pinState, 0); // "Obey"
  rightSwitch = !bitRead(pinState, 3); // "Purify + eyeWhite
}

void BANGdetectors(){

 // BANG A
    if (leftSwitch && !oldLeftSwitch) {
    BANG_L = true;
    oldLeftSwitch = true;
    } else if (!leftSwitch && oldLeftSwitch){
      oldLeftSwitch = false;
      BONG_L = true;
    } else {
      BANG_L = false;
      BONG_L = false;
    }


 // BANG B
    if (rightSwitch && !oldRightSwitch) {
    BANG_R = true;
    oldRightSwitch = true;
    } else if (!rightSwitch && oldRightSwitch){
      oldRightSwitch = false;
      BONG_R = true;
    } else {
      BANG_R = false;
      BONG_R = false;
    }
}

void modeHandle() {

  if (leftSwitch & rightSwitch) {
    if (!doubleButt) {
      doubleButt = true;
      
      mode++;
      if (!preserveMelody) {
        refreshRandom();                //refresh the melody if preserveMelody isn't flagged
      } else {
        Decay = random(5,10);
      }
      xMode = 0;
      play = false;
      bend = false;
      t = 0;
      Blink = false;
      firstRun = true;
      myFirstSongMode = false;
      writeNote = false;
      eraseNote = false;
      disablePortB=false;
      beatWrite = false;
      beatErase = false;
      distAmount = 0;

    }


    PORTB = (PORTB & B11111101) | t * (t >> x) >> (t >> 4);
    t++;
    playNoteNow(random(0, 2000), 0, 1);
    if (mode > numberOfModes) {
      mode = 1;
    }

  } else {
    doubleButt = false;
  }
}


