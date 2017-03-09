void musicbox() {
	if (bools.firstRun) {             //one time code

		xMode = 0;
		bools.disablePortB = false;
		bools.play = true;
		bools.firstRun = false;
		clearDrums();
		bools.ownBeat = false;
		bools.allowHHSeqMod = true;
		bools.allowSDSeqMod = true;
		bools.allowTranspose = true;
		bools.allowBDSeqMod = false;
		bools.allowNoteAddition = true;
		// bools.ownBeat = true;
		if (!bools.preserveMelody) {
			clearMelody();
			clearBassLine();
			generateChords();
			generateBassLine();
			gener8Melody();
			gener8BDbeat();
			//gener8SDbeat();
			gener8hatsStraight();
			bools.MELODY = true;
			bools.BASS = false;
		}

		//refreshRandom();
	}

	if (bools.leftSwitch) {    //if left button is in
		bools.bend = true;

//		Decay = 4;
		octOffset = (x >> 7);
		playPortBsamp(t, portBselector);
		t++;

	}
	else if (bools.rightSwitch) { //    If right button is in

		xMode = 0;
		octOffset = (x >> 7);
		distAmount = 1;


	}
	else {                    //if no buttons are in
		xMode = 0;
		bools.bend = false;
		//Decay = 10;
		distAmount = 0;

		if (bools.BONG_L) {            //if this is transition from On to Off
			octOffset = 2;
			if (!bools.ownBeat) {
				newDrums();
			}
			//      selector = random(1, 17);
			bools.disablePortB = !bools.disablePortB;
		}

		if (bools.BONG_R) {            //if this is transition from On to Off
			playMode++;
			if (playMode % 3 == 0) {
				bools.BASS = true;
				bools.MELODY = true;
				bools.bend = false;
			}
			else if (playMode % 3 == 1) {
				bools.MELODY = true;
				bools.BASS = false;
			}
			else {
				bools.MELODY = false;
				bools.BASS = true;
			}
		}


	}

}

void myFirstSong() {
	if (bools.firstRun) {
		if (!bools.preserveMelody) {
			clearMelody();
			clearBassLine();
		}
		xMode = 0;
		bools.disablePortB = false;
		bools.play = true;
		bools.ownBeat = false;
		bools.preserveMelody = true;
		bools.allowBDSeqMod = false;
		bools.allowHHSeqMod = false;
		bools.allowSDSeqMod = false;
		bools.myFirstSongMode = true;
		bools.allowTranspose = false;
		bools.bend = false;
		bools.allowHHSeqMod = true;
		bools.allowSDSeqMod = true;
		bools.allowBDSeqMod = true;
		bools.allowNoteAddition = true;
		bools.MELODY = true;
		bools.BASS = true;
		
		clearDrums();
		gener8BDbeat();
		bools.firstRun = false;
		for (int i = 0; i < 16; i++) {
	//		amps[i] = 4;

		}
	}


	bools.play = true;
	if (bools.leftSwitch) {
		
		bools.eraseNote = true;
	}
	else if (bools.rightSwitch) {
		xMode = 0;
		bools.writeNote = true;
	}
	else {
		bools.eraseNote = false;
		bools.writeNote = false;
	}



}

void myFirstBeat() {
	if (bools.firstRun) {
		bools.ownBeat = true;
		bools.preserveMelody = true; //this will actually preserve both
		bools.allowBDSeqMod = false;
		bools.allowHHSeqMod = false;
		bools.allowSDSeqMod = false;
		bools.ownBeat = true;
		bools.play = true;
		bools.disablePortB = false;
		bools.firstRun = false;
		BDseq = 0;
		SDseq = 0;
		HHseq = 0;
	}
	if (bools.rightSwitch) {
		bools.beatWrite = true;		
	}
	else if (bools.leftSwitch) {
		bools.beatErase = true;
	}
	else {
		bools.beatErase = false;
		bools.beatWrite = false;
	}
}



void trigOnChangeSolo() {

	if (bools.firstRun) {
		bools.portBMode = false;
		//bools.ownBeat = false;
		//bools.firstRun = false;
		xMode = 0;
	}
	bools.play = false;
	//digitalWrite(LED, LOW);
	xMode = 0;
	diff = oldX - x;
	if ((diff < -30) | (diff > 30)) {
		oldX = x;
		chordSolo(x);

	}
	if (bools.leftSwitch) {
		playPortBsamp(t, portBselector);
		//PORTB = (PORTB & ~mask) | (t % ((t >> x) & (t >> 5))) & mask ;
		t++;
	}
	if (bools.rightSwitch) {
		playPortBsamp(t, (portBselector+1)%5);
		//PORTB = (PORTB & ~mask) | (((t * (t >> 4 | t >> 9) | (t / 256 + x)&t >> 8)) ^ (t & t >> 8 | t >> 6)) & mask;
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
	//bools.play = false;
	//bools.portBMode = false;
	if (bools.BANG_R) {
		chordSolo(x);
	}
	if (bools.BANG_L) {
		chordSolo(x + 10);
	}
}



void buttonSolos() {
	bools.disablePortB = true; //only disaples drums
	bools.play = false;

	if (bools.rightSwitch) {
		xMode = 0;
		a = x / 10;

		playPortBsamp(t, portBselector);
		t++;
	}
	else if (bools.leftSwitch) {
		xMode = 1;
		bools.bend = true;
//		Decay = 7;
		// playNoteNow(x, octaveselect, 2);
	}
	else {
		refreshRandom();
		xMode = random(0, 2);
		octaveselect = random(0, 4);
	}
}


void portBplayer() {
	bools.disablePortB = true; //only disables drums
	if (bools.BANG_R) {
		pip++;
		pip = pip % 5;
	}
	else if (bools.leftSwitch) {
		refreshRandom();
		playNoteNow(x, 1, 4);
	}
	else {

		// bools.Blink=true;
		//refreshRandom();
		//xMode = 0;
		//octaveselect = random(0, 4);
		//t = 0;
		t = s >> pip;
	}
	//a = x / 10;
	bools.bend = true;
	playPortBsamp(t, portBselector); //using melody offset so i dont need to store an own portB

}




