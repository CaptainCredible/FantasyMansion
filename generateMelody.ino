
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void melodyTEST() {
  for (int i = 0; i < barLength; i++) {        //step through steps
    //Chords[i] = 0;                      //erase steps
    if (true) {
      //writeANote(i,i%barLength );              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
      //writeANote(i,currentScale[(i*-1)+10] + 8);              //by ofsetting by eight we are making a buffer of eight on either side of the melody for transposition
    }
  }
}
*/


////////////////////////////////////////////////////////////////////////////////////
void clearMelody() {
  for (int i = 0; i < barLength; i++) {        //step through sequence "chords"
    Chords[i] = 0; //clear melody       //delete chord
  }
}



///////////////////////////////////////////////////////////////////////////////////////
void writeANote(byte STEP, byte note) {
	note = 32 - note; //(note * -1) + 32;          //invert note
  bitSet(Chords[STEP], note);        //write note starting with lowest note
}



///////////////////////////////////////////////////////////////////////////////////////
void gener8Melody() {
  byte timeInterval = random(0, 10);
  for (int i = 0; i < barLength; i = i + random(0, 6)) {   //step through steps randomly like a drunk sensei
    bitSet(Chords[i], 32-(currentScale[random(5) + (scaleSelect*5)] + root));
  }
}

///////////////////////////////////////////////////////////////////////////////////////
//ADD NOTE RANDOMLY
void addNote() {
  //bitSet(Chords[random(barLength - 1)], 32 - (currentScale[random(5) + (scaleSelect * 5)])-(12*random(2)));
  bitSet(Chords[random(barLength - 1)], 32 - (currentScale[random(5) + (scaleSelect * 5)] + root) - (12 * random(2)));
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







////////////////////////////////////////////////////////////////////////////////////// CHORDS
void generateChords() {
  //int root = 12;
  byte tripChords = random(0, 8);
  byte chordBeatOffset = random(0, 8);
  for (int i = 0; i < barLength; i++) { //step through chords
    //Chords[i] = 0;  //delete them preexisting contents
    if ((i + chordBeatOffset) % tripChords == 0) {                 //on step 3-7-11 and so on tripchords chordBeatOffset
      for (byte chordStep = 0; chordStep < 3; chordStep++) {
        bitSet(Chords[i+(chordStep*bools.Arp)], 32-(root + currentScale[(chordStep%5)+(scaleSelect*5)]));       
      }
    }
  }
}



void generateBassLine() {
	clearBassLine();
	byte period = random(1, 5);
  for (int i = 0; i < barLength; i = i + period) {
		byte bassStep = i / period;
		byte bassScaleSelect = (4 - (bassStep%period)) % 5;
		if (random(3) == 1) {    //one in three chance to select random bass note (within scale)
			bassScaleSelect = random(5);
		}
		
		byte bassval = currentScale[bassScaleSelect + (scaleSelect*5)] + root;

//bitSet(ChordsB[i], root + currentScale[(((i%period)*-2-(2*i)))+(scaleSelect*5)]);
		
		

		bitSet(ChordsB[i], (16-bassval)+4);//+4);
		
  }
}

void clearBassLine() {
  for (byte i = 0; i < barLength; i++) {
    ChordsB[i] = 0;
  }
}

void generateDecayArray() {
	byte type = random(0, 2)*2;    //return either 0 or 2 ot add to the decay
	
	
		for (int i = 0; i < 16; i++) {
			if ((i)% 4 == 0) {
				decayArray[i] = random(4, 8)-type;
			}
			else {
				decayArray[i] = random(6, 8)-type;
			}
	}
}