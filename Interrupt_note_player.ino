

// Watchdog interrupt plays notes

ISR(WDT_vect) {  //interupt triggered by watchdog INTERUPT SHOULD BE DISABLED IF WE ARE IN SLAVE MODE!
	if (!bools.receiveSync) {
		notePlayer(); //note player also plats beats
	}
}

void notePlayer() {
	if (bools.sendSync) {
		bools.syncTick = true;
		//digitalWrite(syncPin, HIGH);
	}

	if (bools.play) {                                                      //if we "flag play"
		playNextNote();                                                      //play the next stored note
		t = 1;
		s = 4;
	}

}

void playNextNote() {

	////////////////////////WRITING NOTES AND DRUMS///////////////////////////////
	if (bools.writeNote) {
		int EXX = 600 - x;                    //EXX is remapped x
		//int EXX = x;
		//EXX = EXX >> 3;
		
		/*
		if (EXX < 0) {
			EXX = 0;
			
		}
		else if (EXX > 31) {
			EXX = 31;
		}
		*/

		int EXXOCT = EXX / 5;

		//int pop = selex;
		if (bools.TMelOrFBass) {
			bitSet(Chords[(selex) % barLength], (Scale[(EXX%5)+scaleSelect]+(12*EXXOCT))%32);  //the note will be played immediately afterwards
		}
		else {
			bitSet(ChordsB[(selex) % barLength], EXX%16);  //the note will be played immediately afterwards
		}
		bools.writeNote = false;
	}
	if (bools.eraseNote) {
		if (bools.TMelOrFBass) {
			Chords[selex] = 0;
		}
		else {
			ChordsB[selex] = 0;
			bools.eraseNote = false;
		}
	}

	if (bools.beatWrite) {
		byte beatSeqSelexLookahead = (beatSeqSelex - 1) % 16; //make a lookahead number

		if (x < 300) {                                         //BD because it is pullup this is actually darkness
			bitSet(BDseq, beatSeqSelexLookahead);                //set next step to BD
		}
		else if (x < 400) { //SD
			bitSet(HHseq, beatSeqSelexLookahead);                //set next step to HH
		}
		else {
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
	if (bools.swing) {
		bools.slowMo = !((selex+1) % 2);
	}
	Tempo = baseTempo + bools.slowMo;                                    //used for swing
	WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt
	sei();                                                          // Allow interrupts
	WDTCR |= 1 << WDIE;                                             //no idea what this is, is this the


	///////CHORDSPLAY///////
	if ((bools.MELODY || bools.BASS) && syncPin != 4) { //   if melodies are allowed

		for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 32bit number

			if (bools.MELODY) {
				if (bitRead(Chords[(selex)], Note)) {
					int freqSelector = 32 - (Note - ((modulationinterval * (barTicker % modulationSteps))*bools.allowTranspose));
					if (freqSelector > 32)
					{
						freqSelector = freqSelector - 12;
					}
					else if (freqSelector < 0) {
						freqSelector = freqSelector + 12;
					}
					int oct = 1 << bitRead(octArray, selex % 16);
					Freq[Chan] = (pgm_read_word_near(Scale + (freqSelector) % 32)) >> (oct);//Scale[freqSelector] >> oct;          //look up the notes frequency and shift the octave as per the array
					//Decay = decayArray[selex % 16];
					//Amp[Chan] = (amps[selex % 16]);                       // change to 2 for epic dist
					Amp[Chan] = (1 << (Decay + 5 + bitRead(dists, selex)));
					//Amp[Chan] = (4 + (bitRead(dists, selex%16))) << (amps[selex%16] + 5);                       // change to 2 for epic dist
					Chan = (Chan + 1) % (Channels);
				}
			}
			//////BASSPLAY//////
			if (bools.BASS) {
				if (bitRead(ChordsB[(selex)], Note)) {

					int bassFreqSelector = 32 - (Note - ((modulationinterval * (barTicker % modulationSteps))*bools.allowTranspose));    // offset by 6 or 18
					if (bassFreqSelector < 0) {
						bassFreqSelector += 12;
					}
					Freq[Chan] = (pgm_read_word_near(Scale + (bassFreqSelector - 3) % 32)) >> (3 + bools.BASSOCT);                //look up the notes frequency and shift the octave as per the array
					//Amp[Chan] = 2 - (bitRead(dists, selex)) << (amps[selex ] + 5);                     // change to 2 for epic dist
					//Amp[Chan] = (4 + (bitRead(dists, selex % 16))) << (amps[selex % 16] + 5);                       // change to 2 for epic dist
					//Amp[Chan] = (1 << amps[selex % 16]);                       // change to 2 for epic dist
					Amp[Chan] = (1 << (Decay + 6));
					Chan = (Chan + 1) % (Channels);
				}
			}

		}
	}

	/* ////////BASSPLAY////////
	 if (bools.BASS && syncPin != 4) {
	   for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 16bit number
		 if (bitRead(ChordsB[(selex) % barLength], Note)) {
		   int freqSelector = (((Note * -1) + 32) - (modulationinterval * (barTicker % modulationSteps)))-2;    // offset by 6 or 18
		   Freq[Chan] = pgm_read_word_near(Scale + (freqSelector-11)) >> (3+bools.BASSOCT);                //look up the notes frequency and shift the octave as per the array
		   Amp[Chan] = 1 + (bitRead(dists, selex)) << (amps[selex % 16] + 6);                     // change to 2 for epic dist
		   Chan = (Chan + 1) % (Channels - 1);
		 }
	   }
	 }
	 */

	 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	selex++;                                                     // add one to the selector for chords (step ahead in the index)
	if (selex > barLength - 1) {                                 //if we reached the end
		barTicker++;                                                  //add one to the bar counter
		if (barTicker > 1) {
			if (bools.allowSDSeqMod) {
				gener8SDbeat();
			}
			if (bools.allowHHSeqMod) {
			//	gener8hats();
			}
		}
		if ((barTicker % 2 == 0) && (random(2) == 1)) {                 //on even ticks there is a 50% chance of adding a note
			addNote();
		}
		t = 0;
		selex = 0;                                                    //reset the selector
	}

	if (barTicker > 3) {                                            //every 4 bars
		barTicker = 0;                                                //reset bar counter
		if (!bools.myFirstSongMode && bools.allowNoteAddition) {                 //if we are allowed to
			addNote();                                                    //add a "random" note
			deleteNote(random(barLength));                                                 //remove a random note (or not if there is no note on the step we chose
		}
		partTicker++;                                                 //increment the part ticker
		//bools.BASS = true;//( !bools.BASS;										//toggle BAss on and off



		if (bools.allowBDSeqMod) {
			gener8BDbeat();
		}
	}
	if (partTicker > 2) {
		partTicker = 0;
		songTicker++;
		if (songTicker > 4 && !(bools.myFirstSongMode || bools.ownBeat)) {
			refreshRandom();															//this remakes beats regardless of ownBeat further down so put the if bools ownbeat code in refreshrandom instead
			songTicker = 0;
		}
	}
	t = 0;                                                         //set portBt back to 0 so portBs are audible

}

