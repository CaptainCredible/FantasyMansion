
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
//ADD NOTE RANDOMLY
void addNote() {
	//bitSet(Chords[random(barLength - 1)], 32 - (currentScale[random(5) + (scaleSelect * 5)])-(12*random(2)));
	//bitSet(Chords[random(barLength - 1)], 31 - (currentScale[random(5) + (scaleSelect * 5)] + root) - (12 * random(2)));
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
	byte tripChords = random(0, 8);
	tripChords = 3;
	byte chordBeatOffset = random(0, 8);
	for (int i = 0; i < barLength; i++) { //step through chords
		if ((i + chordBeatOffset) % tripChords == 0) {                 //on step 3-7-11 and so on tripchords chordBeatOffset
			for (byte chordStep = 0; chordStep < 3; chordStep++) {
				bitSet(Chords[i + (chordStep*bools.Arp)], 31 - (root + currentScale[(chordStep % 5) + (scaleSelect * 5)]));
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void gener8Melody() {
	//byte timeInterval = 1;// random(0, 10);
	for (int i = 0; i < initBarLength; i = i + random(1, 6)) {   //step through steps randomly like a drunk sensei
																 // bitSet(Chords[i], 16);
		bitSet(Chords[i], 31 - ((currentScale[random(5) + (scaleSelect * 5)] + root)));
		//bitSet(Chords[i], 12);
	}
}

void generateBassLine() {
	clearBassLine();
	//byte period = random(1, 5);
	byte period = 1;
	for (int i = 0; i < barLength; i = i + period) {
		byte bassStep = i / period;
		//byte bassScaleSelect = (bassStep%period) % 5;
		byte bassScaleSelect = ((bassStep % (2 * period)) * 2) % 5;
		//if (random(3) == 1) {    //one in three chance to select random bass note (within scale)
			//bassScaleSelect = random(5);
		//}
		//byte bassval = currentScale[1 + (scaleSelect * 5)] + root + 3;
		byte bassval = currentScale[bassScaleSelect + (scaleSelect * 5)] + root;

		//bitSet(ChordsB[i], root + currentScale[(((i%period)*-2-(2*i)))+(scaleSelect*5)]);



		bitSet(ChordsB[i], (16 - bassval));//+4);

	}
}

void clearBassLine() {
	for (byte i = 0; i < barLength; i++) {
		ChordsB[i] = 0;
	}
}



void generateDecayArray() {
	byte type = random(0, 2) * 2;    //return either 0 or 2 ot add to the decay	
	byte trip = random(3, 5);
	for (byte i = 0; i < 16; i++) {
		//decays[i] = 6;

		if ((i) % trip == 0) {
			decays[i] = random(6, 10) - type;
			//decays[i] = 8;
		}
		else {
			decays[i] = random(4, 6) - type;
		}
		

	}
}