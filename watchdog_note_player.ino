//pin 1 is portB and pin 4 is tones

// Watchdog interrupt plays notes
ISR(WDT_vect) {  //interupt triggered by watchdog timer
  
  digitalWrite(bootMode,(selex+1)%2);
  if (bools.play) {                                                      //if we "flag play"
    playNextNote();                                                  //play the next stored note
    t = 0;
    s = 0;
  }

  //if(bools.slolo){                                                      //if its a slolo    SLOLO ISNT USED
  //chordSolo(x);                                                   //slolo bitch
  //}

  if (bools.Blink) {
    bools.blinkTicker = !bools.blinkTicker;
    //digitalWrite(LED, bools.blinkTicker);
  }

}

void playNextNote() {
  if (bools.writeNote) {
    //digitalWrite(LED,HIGH);                    //what LED?
    int EXX = (x * -1) + 600;                    //EXX is remapped x
    EXX = EXX / 10;
    if (EXX < 0) {
      EXX = 0;
    } else if (EXX > 31) {
      EXX = 31;
    }
    bitSet(Chords[(selex + 1) % 16], EXX);
  }
  if (bools.eraseNote) {
    Chords[selex] = 0;
  }

  if (bools.beatWrite) {
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

  if (bools.beatErase) {
    byte beatSeqSelexLookahead = (beatSeqSelex - 1) % 16; //if beat erase is activated
    bitClear(BDseq, beatSeqSelexLookahead);               //erase BD
    bitClear(SDseq, beatSeqSelexLookahead);               //erase SD
    bitClear(HHseq, beatSeqSelexLookahead);               //erase HH
  }


  //////////////////////////////////////////////////////////////////////////////////////////////

  Tempo = baseTempo + bools.slowMo;                                    //half the tempo on every other bar
  WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt
  sei();                                                          // Allow interrupts
  WDTCR |= 1 << WDIE;                                             //no idea what this is


  ///////CHORDSPLAY///////
  if (bools.MELODY && bootMode != 2) {
    for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 32bit number
      oct = 0;
      if (bitRead(Chords[(selex) % barLength], Note)) {
        int freqSelector = ((Note * -1) + 31); - modulationinterval * (barTicker % 2);
        Freq[Chan] = pgm_read_word_near(Scale + freqSelector) >> oct ;//Scale[freqSelector] >> oct;          //look up the notes frequency and shift the octave as per the array
        Amp[Chan] = 1 + (bitRead(dists, selex)) << (Decay + 5);                       // change to 2 for epic dist
        Chan = (Chan + 1) % (Channels - 1);
      }
    }
  }

  ////////BASSPLAY////////
  if (bools.BASS && bootMode != 2) {
    for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 16bit number
      if (bitRead(ChordsB[(selex) % barLength], Note)) {
        int freqSelector = ((Note * -1) + 15); - modulationinterval * (barTicker % 2);
        Freq[Chan] = pgm_read_word_near(Scale + freqSelector) >> 2;                //look up the notes frequency and shift the octave as per the array
        Amp[Chan] = 3 + (bitRead(dists, selex)) << (decays[selex % 16] + 6);                     // change to 2 for epic dist
        Chan = (Chan + 1) % (Channels - 1);
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  selex++;                                                     // add one to the selector for chords (step ahead in the index)
  if (selex > barLength - 1) {                                 //if we reached the end
    barTicker++;                                                  //add one to the bar counter
    if (barTicker >> 1) {
      gener8SDbeat();
      gener8hats();
    }
    //    generatePortBLenghts();
    t = 0;
    selex = 0;                                                    //reset the selector

  }
  if (barTicker > 3) {                                            //every 4 bars
    barTicker = 0;                                                //reset bar counter
    if (!bools.myFirstSongMode && bools.allowNoteAddition) {                 //if we are allowed to
      addNote();                                                    //add a "random" note
      deleteNote(random(barLength));                                                 //remove a random note (or not if there is no note on the step we chose
      partTicker++;                                                 //increment the part ticker

    }
  }
  if (partTicker > 3) {
    songTicker++;
    if (!bools.myFirstBeatMode) {
      gener8BDbeat();
      gener8SDbeat();
      gener8hats();
    }
    partTicker = 0;
  }
  t = 0;                                                         //set portBt back to 0 so portBs are audible

}
/*
void handleSyncOut() {
  if (bootMode == 1) {
    //delay(100000000);
    if ((selex-1) % 4 == 0) {
      if (t < portBlength && bools.portBticker) {
        PORTB = (PORTB & B11111101) | B00000010;
        t++;
      } else {
        PORTB = (PORTB & B11111101) | B00000000;
      }
    }
  }
}
*/

