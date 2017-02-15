
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void melodyTEST() {
  for (int i = 0; i < barLength; i++) {        //step through steps
    //Chords[i] = 0;                      //erase steps
    if (true) {
      //writeANote(i,i%barLength );              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
      //writeANote(i,currentScale[(i*-1)+10] + 8);              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
    }
  }
}



////////////////////////////////////////////////////////////////////////////////////
void clearMelody() {
  for (int i = 0; i < barLength; i++) {        //step through sequence oc "chords"
    Chords[i] = 0; //clear melody       //delete chord
  }
}



///////////////////////////////////////////////////////////////////////////////////////
void writeANote(byte STEP, byte note) {
  note = (note * -1) + 32;          //invert note
  bitSet(Chords[STEP], note);        //write note starting with lowest note
}



///////////////////////////////////////////////////////////////////////////////////////
void gener8Melody() {
  byte timeInterval = random(0, 10);
  for (int i = 0; i < barLength; i = i + random(0, 6)) {   //step through steps randomly like a drunk sensei
    bitSet(Chords[i], currentScale[random(0, 11) + scalesOffset] + root);
  }
}

///////////////////////////////////////////////////////////////////////////////////////
//ADD NOTE RANDOMLY
void addNote() {
  bitSet(Chords[random(barLength - 1)], currentScale[random(11) + scalesOffset]);
}

///////////////////////////////////////////////////////////////////////////////////////
//DELETE NOTE RANDOMLY
void deleteNote(byte steppo) {
  //bitClear(Chords[random(17)], random(32));
  for (int i = 0; i < 32; i++) {
    if (bitRead(Chords[steppo], i)) {
      bitClear(Chords[steppo], i);
      i = 99;
      break;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////// Throws a bunch of random octaves into the mix
void generateOctaves() {
  for (int i = 0; i < random(16); i++) {
    //    octArray[i] = random(0, 2);
    bitSet(octArray, random(16));
  }
}







//////////////////////////////////////////////////////////////////////////////////////
void generateChords() {
  //int root = 12;
  byte tripChords = 3; random(0, 8);
  byte chordBeatOffset = 4; random(0, 8);
  for (int i = 0; i < barLength; i++) { //step through chords
    Chords[i] = 0;  //delete them preexisting contents
    if ((i + chordBeatOffset) % tripChords == 0) {                 //on step 3-7-11 and so on tripchords chordBeatOffset
      //bitSet(Chords[i], 5);
      for (byte chordStep = 0; chordStep < 3; chordStep++) {
        bitSet(Chords[i], (root + currentScale[(chordStep%5)+(scaleSelect*5)]));       
      }
    }
  }
}



void generateBassLine() {
  byte period = random(2, 9);
  for (int i = 0; i < barLength; i = i + period) {
//    bitSet(ChordsB[i], 4);
bitSet(ChordsB[i], root + currentScale[((i%2)*-2)+(scaleSelect*5)]);
  }
}

void clearBassLine() {
  for (byte i = 0; i < barLength; i++) {
    ChordsB[i] = 0;
  }
}

