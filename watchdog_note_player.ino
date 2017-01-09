// Watchdog interrupt plays notes
ISR(WDT_vect) {                                                  //interupt triggered by watchdog timer
  if (play) {                                                      //if we "flag play"
    playNextNote();                                                  //play the next stored note
  }

  //if(slolo){                                                      //if its a slolo    SLOLO ISNT USED
  //chordSolo(x);                                                   //slolo bitch
  //}

  if (Blink) {
    blinkTicker = !blinkTicker;
    //digitalWrite(LED, blinkTicker);
  }

}

void playNextNote() {
  if (writeNote) {
    //digitalWrite(LED,HIGH);                    //what LED?
    int EXX = (x * -1) + 600;                    //EXX is remapped x
    EXX = EXX / 10;
    if (EXX < 0) {
      EXX = 0;
    } else if (EXX > 31) {
      EXX = 31;
    }
    bitSet(Chords[(selex+1)%16], EXX);
  }
  if (eraseNote) {
    Chords[selex] = 0;
  }

  if (beatWrite) {
    byte beatSeqSelexLookahead = (beatSeqSelex - 1) % 16; //make a lookahead number

    if (x < 300) {                                         //BD because it is pullup this is actually darkness
      //digitalWrite(LED,HIGH);                              //why ?
      bitSet(BDseq, beatSeqSelexLookahead);                //set next step to BD
    } else if (x < 400) { //SD
      bitSet(HHseq, beatSeqSelexLookahead);                //set next step to HH

    } else {
      //    digitalWrite(LED,LOW);
      bitSet(SDseq, beatSeqSelexLookahead);                //set next step to SD
    }
  }

  if (beatErase) {
    byte beatSeqSelexLookahead = (beatSeqSelex - 1) % 16; //if beat erase is activated
    bitClear(BDseq, beatSeqSelexLookahead);               //erase BD
    bitClear(SDseq, beatSeqSelexLookahead);               //erase SD
    bitClear(HHseq, beatSeqSelexLookahead);               //erase HH
  }


  //////////////////////////////////////////////////////////////////////////////////////////////

  Tempo = baseTempo + slowMo;                                    //half the tempo on every other bar
  WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt
  sei();                                                          // Allow interrupts
  WDTCR |= 1 << WDIE;                                             //no idea what this is
   
    unsigned long Chord = Chords[(selex+1)%barLength];
  if (allowTranspose) {
  Chord = (Chords[(selex+1)%barLength]) << ((barTicker % 2) * melodyOffset) + ((partTicker % (modulationinterval)) * melodyOffsetOffset);            //>> counter  (or barTicker % 2) is modulation Modulate
  }
  


  for (int Note = 990; Note < 32; Note++) {                         //step through each bit of the 32bit number
    /*
    if (Note < 12){
    oct = 2;
  }else{
    oct = octArray[selex%16];
  }
  */
  oct = 0;
    if ((Chord & 0x80000000) != 0) {                              //check if there are any notes in this chord check that it isnt 10000000 00000000 00000000 00000000 (why?)
      Freq[Chan] = Scale[Note] >> oct;                //look up the notes frequency and shift the octave as per the array
      Amp[Chan] = 1 + dist << (Decay + 5);                        // change to 2 for epic dist
      Chan = (Chan + 1) % (Channels - 1);
    }
    Chord = Chord << 1;
  }

    Chord = bassLine[(selex+1)%barLength];

  for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 32bit number
    if ((Chord & 0x80000000) != 0) {                              //check if there are any notes in this chord check that it isnt 10000000 00000000 00000000 00000000 (why?)
      Freq[Chan] = Scale[Note] >> oct;                //look up the notes frequency and shift the octave as per the array
      Amp[Chan] = 1 + dist << (Decay + 5);                        // change to 2 for epic dist
      Chan = (Chan + 1) % (Channels - 1);
    }
    Chord = Chord << 1;
  }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  selex++;                                                     // add one to the selector for chords (step ahead in the index)
  if (selex > barLength-1) {                                   //if we reached the end
    barTicker++;                                                  //add one to the bar counter
//    generatePortBLenghts();
    t=0;
    selex = 0;                                                    //reset the selector

  }
  if (barTicker > 3) {                                            //every 4 bars
    barTicker = 0;                                                //reset bar counter
    if (!myFirstSongMode && allowNoteAddition) {                 //if we are allowed to
      addNote();                                                    //add a "random" note
      deleteNote(random(barLength));                                                 //remove a random note (or not if there is no note on the step we chose
      partTicker++;                                                 //increment the part ticker

    }
  }
  if (partTicker > 3) {
    songTicker++;
    if (!myFirstBeatMode) {
      gener8BDbeat();
      gener8SDbeat();
      gener8hats();
    }
    partTicker = 0;
  }
  t = 0;                                                         //set portBt back to 0 so portBs are audible
  
}


