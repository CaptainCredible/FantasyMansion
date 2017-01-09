void clearMelody() {
  for (int i = 0; i < 16; i++) {        //step through sequence oc "chords"
    Chords[i] = 0; //clear melody       //delete chord
  }
}


void writeANote(byte STEP, byte note){
  note = (note*-1)+32;              //invert note
  bitSet(Chords[STEP],note);         //write note starting with lowest note
}

void melodyTEST() {
  for (int i = 0; i < 16; i++) {        //step through steps
    Chords[i] = 0;                      //erase steps
    //bitSet(Chords[i], i);               //set chord to be same as step
    writeANote(i,i+8);                 //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
  }

  }

  ////////////////////////////////////////////////////////////////////////////////////
  void gener8Melody() {
    ///////////////////////////////////////////////////////////////////////7
    int arpstep = 0;
    for (int i = 0; i < 16; i++) {        //step through steps
      Chords[i] = 0;                      //erase steps
      arpstep++;
      if (arpstep >= arpLength) {
        arpstep = 0;
      }
      if (random(0, 3) < 2) { //gives it a 2 in three chance
        bitSet(Chords[i], currentScale[random(0, 11) + scalesOffset]);
      }
    }
  }

  //ADD NOTE RANDOMLY
  void addNote() {
    bitSet(Chords[random(17)], currentScale[random(11) + scalesOffset]);
  }
  //DELETE NOTE RANDOMLY
  void deleteNote() {
    bitClear(Chords[random(17)], random(32));
  }


  /*
    void gener8MelodyArp() {                                                      // THIS FUNCTION IS NOT USED!!!!

    int arpstep = 0;
    for (int i = 0; i < 16; i++) {        //step through steps
      //unsigned long chord = Chords[i];
      //for (int s = 0; s<10; s++){         //step through notes in step
      Chords[i] = 0;
      arpstep++;
      if (arpstep >= arpLength) {
        arpstep = 0;
      }
      bitSet(Chords[i], currentScale[arpstep]); //+scalesOffset]);                                        //arpeggio
      if (arpstep % bassTempo == 0) {
        bitSet(Chords[i], currentScale[scaleSelect]);
      }
    }
  */

  int generateOctaves() {
    for (int i = 0; i < 16; i++) {
      octArray[i] = 0;//random(0, 2);
    }
  }


  /////////////////////////////////////////////////////////////////////////
  void generateChords() {
    int root = 12;
    for (int i = 0; i < 16; i++) { //step through chords
      Chords[i] = 0;
      if ((i + 2) % 4 == 0) {                 //on step 3-7-11 and so on
        for (byte chordStep = 0; chordStep < 3; chordStep++) {
          bitSet(Chords[i], root + chordIntevals[chordStep + (chordIntervalSelector * 3)]);
        }

      }

    }
  }

