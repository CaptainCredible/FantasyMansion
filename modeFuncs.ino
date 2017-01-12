void musicbox() {
  //bitSet(BOOLS_A, 1);   //rewrite for smalle code
  if (bools.firstRun) {             //one time code
    bools.play = true;
    bools.firstRun = false;
  }
  if (bools.leftSwitch) {    //if left button is in
    //gener8SDbeat();
    Decay = 4;
    
    playPortBsamp(t);
    t++;

  } else if (bools.rightSwitch) { //    If right button is in
    // bend = true;
    xMode = 0;
    octOffset = (x >> 7);
    distAmount = 1;


  } else {                    //if no buttons are in
    xMode = 0;
    bools.bend = false;
    Decay = 7;
    distAmount = 0;

    if (bools.BONG_L) {            //if this is transition from On to Off
      octOffset = 2;
      if (!bools.ownBeat) {
        newDrums();
      }
      selector = random(1, 17);
      bools.disablePortB = !bools.disablePortB;
    }

    if (bools.BONG_R) {            //if this is transition from On to Off
      playMode++;
      if (playMode % 3 == 0) {
        bools.BASS = true;
        bools.MELODY = true;
      } else if (playMode % 3 == 1) {
        bools.MELODY = true;
        bools.BASS = false;
      }else{
        bools.MELODY = false;
        bools.BASS = true;
      }
    }


  }
}


void trigOnChangeSolo() {
  if (bools.firstRun) {
    bools.ownBeat = false;
    bools.firstRun = false;
  }
  bools.Blink = false;
  bools.play = false;
  //digitalWrite(LED, LOW);
  xMode = 0;
  diff = oldX - x;
  if ((diff < -30 ) | (diff > 30)) {
    oldX = x;
    chordSolo(x);

  }
  if (bools.leftSwitch) {
    PORTB = (PORTB & B11111101) | t % ((t >> x) & (t >> 5)) ;
    t++;
  }
  if (bools.rightSwitch) {
    PORTB = (PORTB & B11111101) | ((t * (t >> 4 | t >> 9) | (t / 256 + x)&t >> 8)) ^ (t & t >> 8 | t >> 6);
    t++;
    if (bools.BANG_R) {
      octaveselect++;
      if (octaveselect > 4) {
        octaveselect = 0;
        //bools.oldRightSwitch = true;
      }
    }
  }
  //bools.oldRightSwitch = false;
}




void trigOnPurifySolo() {
  bools.Blink = false;
  bools.play = false;
  if (bools.BANG_R) {
    chordSolo(x);
  }
  if (bools.BANG_L) {
    chordSolo(x + 10);
  }
}


void buttonSolos() {
  bools.play = false;
  bools.Blink = false;
  if (bools.rightSwitch) {
    xMode = 0;
    a = x / 10;

    playPortBsamp(t);
    t++;
  } else if (bools.leftSwitch) {
    xMode = 1;
    bools.bend = true;
    Decay = 7;
    playNoteNow(x, octaveselect, 2);
  } else {
    refreshRandom();
    xMode = random(0, 2);
    octaveselect = random(0, 4);
  }
}


void portBplayer() {
  if (bools.rightSwitch) {
    bools.Blink = false;
    a = x / 10;
    bools.bend = true;


    playPortBsamp(t);
    t++;
  } else if (bools.leftSwitch) {
    refreshRandom();
  } else {
    // bools.Blink=true;
    //refreshRandom();
    xMode = 0;
    octaveselect = random(0, 4);
    t = 0;
  }
}


void myFirstSong() {
  if (bools.firstRun) {
    bools.preserveMelody = true;
    clearMelody();
    bools.myFirstSongMode = true;
    bools.firstRun = false;
  }

  bools.play = true;
  if (bools.rightSwitch) {
    xMode = 0;
    bools.writeNote = true;
  } else if (bools.leftSwitch) {
    bools.eraseNote = true;
  } else {
    bools.writeNote = false;
    bools.eraseNote = false;
    //bools.noteWritten = false;
  }



}



void myFirstBeat() {
  if (bools.firstRun) {
    bools.ownBeat = true;
    bools.preserveMelody = true; //this will actually preserve both
    //gener8BDbeat();
    bools.myFirstBeatMode = true;
    bools.play = true;
    bools.disablePortB = false;
    bools.firstRun = false;
    BDseq = 0;
    SDseq = 0;
    HHseq = 0;
  }
  if (bools.rightSwitch) {
    bools.beatWrite = true;
  } else if (bools.leftSwitch) {
    bools.beatErase = true;
  } else {
    bools.beatErase = false;
    bools.beatWrite = false;
  }
}


void chordtest() {
  if (bools.firstRun) {
    clearDrums();
    bools.ownBeat = true;
    bools.allowBDSeqMod = false;
    bools.allowHHSeqMod = false;
    bools.allowSDSeqMod = false;
    // bools.myFirstBeatMode = true;
    // clearMelody();
    bools.play = true;
   // gener8BDbeat();
   // gener8SDbeat();
   // gener8hats();

    //generateChords();
    // melodyTEST();
    BDseq = 0b1000100010001000;
    SDseq = 0b0001001000000011;
    HHseq = 0b0000000000100000;
    bools.firstRun = false;
  }

}

