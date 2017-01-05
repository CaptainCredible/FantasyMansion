void clearMelody() {
  for (int i = 0; i < 16; i++) {
    Chords[i] = 0; //clear melody
  }
}


////////////////////////////////////////////////////////////////////////////////////
void gener8Melody() {
  ///////////////////////////////////////////////////////////////////////7
  int arpstep = 0;
  for (int i = 0; i < 16; i++) {        //step through steps
    //unsigned long chord = Chords[i];
    //for (int s = 0; s<10; s++){         //step through notes in step
    Chords[i] = 0;
    arpstep++;
    if (arpstep >= arpLength) {
      arpstep = 0;
    }
    if (random(0, 3) < 2) { //gives it a 2 in three chance
      bitSet(Chords[i], currentScale[random(0, 11) + scalesOffset]);
    }
  }
}

void addNote() {
  bitSet(Chords[random(0, 17)], currentScale[random(0, 11) + scalesOffset]);
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
        bitSet(Chords[i], root + chordIntevals[chordStep + (chordIntervalSelector*3)]);
      }

    }

  }
}

