void melodyTEST() {
  for (int i = 0; i < barLength; i++) {        //step through steps
  //Chords[i] = 0;                      //erase steps
    if(true){
    //writeANote(i,i%barLength );              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
    //writeANote(i,currentScale[(i*-1)+10] + 8);              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////

void clearMelody() {
  for (int i = 0; i < 16; i++) {        //step through sequence oc "chords"
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

  for (int i = 0; i < 16; i++) {        //step through steps
    Chords[i] = 0;                      //erase steps
    if (random(0, 3) < 2) { //gives it a 2 in three chance
      bitSet(Chords[i], currentScale[random(0, 11) + scalesOffset]);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////
//ADD NOTE RANDOMLY
void addNote() {
  bitSet(Chords[random(17)], currentScale[random(11) + scalesOffset]);
}

///////////////////////////////////////////////////////////////////////////////////////
//DELETE NOTE RANDOMLY
void deleteNote(byte steppo) {
  //bitClear(Chords[random(17)], random(32));
  for (int i = 0; i<32; i++){
if (bitRead(Chords[steppo],i)){
  bitClear(Chords[steppo],i);
  i = 99;
  break;
}
  }
}

///////////////////////////////////////////////////////////////////////////////////////
int generateOctaves() {
  for (int i = 0; i < 16; i++) {
    octArray[i] = random(0, 2);
  }
}


//////////////////////////////////////////////////////////////////////////////////////
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

void generateBassLine(){
  
}



