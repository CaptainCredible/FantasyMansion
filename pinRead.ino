void pinRead() {
  //GET x
  x = (analogRead(LDR) * -1) + 1024; //invert the range (because it is pullup)
  x = x - 400;
  if (x < 0) {
    x = 0;                          //make 400 the floor
  } else if (x > 600) {
    x = 600;                        //make 600 the ceiling
  }
  if (bools.bend) {
    bender = x;
  } else {
    bender = 0;
  }


  byte pinState = PINB;
  bools.leftSwitch = !bitRead(pinState, 0); // "Obey"
  bools.rightSwitch = !bitRead(pinState, 3); // "Purify + eyeWhite

  //SYNC RECEIVE
  if (bools.receiveSync) {
    bools.inSignal = (digitalRead(syncPin));

    if (bools.inSignal && !bools.oldInSignal) { //if the sync pin is HIGH and it was flagged as LOW
      bools.oldInSignal = true;                 //flag that we have detected the signal going high so now we need to wait for it to go low
      syncPeriod = periodTimer >> 1;            //set the syncPeriod to be half og how far we have counted with the periodTimer             I THINK PERIODTIMER NEEDS TO BE VOLATILE!!!!!
      periodTimer = 0;                          //now reset the periodTimer
      notePlayer();                           //play A Note
    } else if (bools.oldInSignal && periodTimer > syncPeriod) { //if either the inSignal isn't high, or if we have allready done whats necessary to do when it went high, check if periodTimer has exeeded what we counted foir last time and make sure we didnt allready do that
      bools.oldInSignal = false;                //flag that we have detected the state where the offbeat note should be triggered by writing oldInSignal to false

      if (bools.doubleTime) {
        notePlayer();                             //play a note
        //optionaly make doubleTime selectable
      }
    }
  }
}

void BANGdetectors() {

  // BANG A
  if (bools.leftSwitch && !bools.oldLeftSwitch) {
    bools.BANG_L = true;
    bools.oldLeftSwitch = true;
  } else if (!bools.leftSwitch && bools.oldLeftSwitch) {
    bools.oldLeftSwitch = false;
    bools.BONG_L = true;
  } else {
    bools.BANG_L = false;
    bools.BONG_L = false;
  }


  // BANG B
  if (bools.rightSwitch && !bools.oldRightSwitch) {
    bools.BANG_R = true;
    bools.oldRightSwitch = true;
  } else if (!bools.rightSwitch && bools.oldRightSwitch) {
    bools.oldRightSwitch = false;
    bools.BONG_R = true;
  } else {
    bools.BANG_R = false;
    bools.BONG_R = false;
  }
}

void modeHandle() {

  if (bools.leftSwitch & bools.rightSwitch) {
    if (!bools.doubleButt) {                                              //make sure we havent already run this once this time
      bools.doubleButt = true;                                            //flag that we have run the doublebutt code for this time
      mode++;
      if (mode > numberOfModes) {
        mode = 1;
      }
      if (!bools.preserveMelody) {
        refreshRandom();                //refresh the melody if bools.preserveMelody isn't flagged
      } else {
        Decay = random(5, 10);
      }
      xMode = 0;
      bools.play = false;
      bools.bend = false;
      t = 0;
      bools.firstRun = true;
      bools.myFirstSongMode = false;
      bools.writeNote = false;
      bools.eraseNote = false;
      bools.disablePortB = false;
      bools.beatWrite = false;
      bools.beatErase = false;
      distAmount = 0;
     // oct = 0;

    }

    PORTB = (PORTB & ~mask) | ((t * (t >> x) >> (t >> 4)) & mask);
    t++;

    playNoteNow(random(0, 2000), 0, 1);



  } else {
    bools.doubleButt = false;
  }
}


