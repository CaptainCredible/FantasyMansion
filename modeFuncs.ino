void musicbox() {
  //bitSet(BOOLS_A, 1);   //rewrite for smalle code
  if (firstRun) {             //one time code
    play = true;
    firstRun = false;
  }
  if (leftSwitch) {    //if left button is in
    //gener8SDbeat();
    Decay = 4;

    playPortBsamp(t);
    t++;

  } else if (rightSwitch) { //    If right button is in
    // bend = true;
    xMode = 0;
    octOffset = (x >> 7);
    distAmount = 1;


  } else {                    //if no buttons are in
    xMode = 0;
    bend = false;
    Decay = 7;
    distAmount = 0;

    if (BONG_L) {            //if this is transition from On to Off
      octOffset = 2;
      if (!ownBeat) {
        newDrums();
      }
      selector = random(1, 17);
      disablePortB = !disablePortB;
    }

    if (BONG_R) {            //if this is transition from On to Off
      playMode++;
      if (playMode % 3 == 0) {
        BASS = true;
        MELODY = true;
      } else if (playMode % 3 == 1) {
        MELODY = true;
        BASS = false;
      }else{
        MELODY = false;
        BASS = true;
      }
    }


  }
}


void trigOnChangeSolo() {
  if (firstRun) {
    ownBeat = false;
    firstRun = false;
  }
  Blink = false;
  play = false;
  //digitalWrite(LED, LOW);
  xMode = 0;
  diff = oldX - x;
  if ((diff < -30 ) | (diff > 30)) {
    oldX = x;
    chordSolo(x);

  }
  if (leftSwitch) {
    PORTB = (PORTB & B11111101) | t % ((t >> x) & (t >> 5)) ;
    t++;
  }
  if (rightSwitch) {
    PORTB = (PORTB & B11111101) | ((t * (t >> 4 | t >> 9) | (t / 256 + x)&t >> 8)) ^ (t & t >> 8 | t >> 6);
    t++;
    if (BANG_R) {
      octaveselect++;
      if (octaveselect > 4) {
        octaveselect = 0;
        //oldRightSwitch = true;
      }
    }
  }
  //oldRightSwitch = false;
}




void trigOnPurifySolo() {
  Blink = false;
  play = false;
  if (BANG_R) {
    chordSolo(x);
  }
  if (BANG_L) {
    chordSolo(x + 10);
  }
}


void buttonSolos() {
  play = false;
  Blink = false;
  if (rightSwitch) {
    xMode = 0;
    a = x / 10;

    playPortBsamp(t);
    t++;
  } else if (leftSwitch) {
    xMode = 1;
    bend = true;
    Decay = 7;
    playNoteNow(x, octaveselect, 2);
  } else {
    refreshRandom();
    xMode = random(0, 2);
    octaveselect = random(0, 4);
  }
}


void portBplayer() {
  if (rightSwitch) {
    Blink = false;
    a = x / 10;
    bend = true;


    playPortBsamp(t);
    t++;
  } else if (leftSwitch) {
    refreshRandom();
  } else {
    // Blink=true;
    //refreshRandom();
    xMode = 0;
    octaveselect = random(0, 4);
    t = 0;
  }
}


void myFirstSong() {
  if (firstRun) {
    preserveMelody = true;
    clearMelody();
    myFirstSongMode = true;
    firstRun = false;
  }

  play = true;
  if (rightSwitch) {
    xMode = 0;
    writeNote = true;
  } else if (leftSwitch) {
    eraseNote = true;
  } else {
    writeNote = false;
    eraseNote = false;
    //noteWritten = false;
  }



}



void myFirstBeat() {
  if (firstRun) {
    ownBeat = true;
    preserveMelody = true; //this will actually preserve both
    //gener8BDbeat();
    myFirstBeatMode = true;
    play = true;
    disablePortB = false;
    firstRun = false;
    BDseq = 0;
    SDseq = 0;
    HHseq = 0;
  }
  if (rightSwitch) {
    beatWrite = true;
  } else if (leftSwitch) {
    beatErase = true;
  } else {
    beatErase = false;
    beatWrite = false;
  }
}


void chordtest() {
  if (firstRun) {
    clearDrums();
    ownBeat = false;
    // clearMelody();
    play = true;
    gener8BDbeat();
    gener8SDbeat();
    gener8hats();

    //generateChords();
    // melodyTEST();
    BDseq = 0b1000100010001000;
    //SDseq = 0b0000100000001111;
    firstRun = false;
  }

}

