void pinRead() {
	//GET x
	
	x = (analogRead(LDR) * -1) + 1024; //invert the range (because it is pullup)
	x = x - 400;
	xManip(xMode);   // manipulate x value : 1=insanepitchrange 2=megapitchrange 0 = donothing
	if (bools.bend) {
		bender = x;
	}
	else {
		bender = 0;
	}



	byte pinState = PINB;
	bools.leftSwitch = !bitRead(pinState, 0); // "Obey"
	bools.rightSwitch = !bitRead(pinState, 3); // "Purify + eyeWhite

	//SYNC RECEIVE
	if (bools.receiveSync) {
		bools.inSignal = (digitalRead(syncPin));

		if (bools.inSignal && !bools.oldInSignal) { //if the sync pin is HIGH and it was flagged as LOW
			bools.oldInSignal = true;                 //flag that we have detected the signal going high so now we need to wait for it to go low
			syncPeriod = periodTimer >> 1;            //set the syncPeriod to be half og how far we have counted with the periodTimer             I THINK PERIODTIMER NEEDS TO BE VOLATILE!!!!!
			periodTimer = 0;                          //now reset the periodTimer
			notePlayer();                           //play A Note
		}
		else if (bools.oldInSignal && periodTimer > syncPeriod) { //if either the inSignal isn't high, or if we have allready done whats necessary to do when it went high, check if periodTimer has exeeded what we counted foir last time and make sure we didnt allready do that
			bools.oldInSignal = false;                //flag that we have detected the state where the offbeat note should be triggered by writing oldInSignal to false

		}
	}
}

void BANGdetectors() {

	// BANG A
	if (bools.leftSwitch && !bools.oldLeftSwitch) {
		bools.BANG_L = true;
		bools.oldLeftSwitch = true;
	}
	else if (!bools.leftSwitch && bools.oldLeftSwitch) {
		bools.oldLeftSwitch = false;
		bools.BONG_L = true;
	}
	else {
		bools.BANG_L = false;
		bools.BONG_L = false;
	}


	// BANG B
	if (bools.rightSwitch && !bools.oldRightSwitch) {
		bools.BANG_R = true;
		bools.oldRightSwitch = true;
	}
	else if (!bools.rightSwitch && bools.oldRightSwitch) {
		bools.oldRightSwitch = false;
		bools.BONG_R = true;
	}
	else {
		bools.BANG_R = false;
		bools.BONG_R = false;
	}
}

void modeHandle() {

	if (bools.leftSwitch & bools.rightSwitch) {
		if (!bools.doubleButt) {                                              //make sure we havent already run this once this time
			dingDong();
			bools.disablePortB = false;
			bools.play = false;
			bools.doubleButt = true;                                            //flag that we have run the doublebutt code for this time
			bools.limbo = true;
		}
	}

	if (bools.doubleButt && !(bools.leftSwitch || bools.rightSwitch)) {        //if they where both pressed in and now they have both been released!
		bools.doubleButt = false;
		bools.limbo = false;
		if (!bools.tonesMode) {
			if (mode == 1) {
				mode = 3;
			}
			else {
				mode = 0;
			}
		}
		mode++;
		portBselector = (portBselector + 1) % 4;
		mode = mode % numberOfModes;
		if (!bools.preserveMelody) {
			refreshRandom();                //refresh the melody if bools.preserveMelody isn't flagged
		}
		else {
//			Decay = random(5, 10);
		}
		xMode = 0;   
		bools.play = false;
		bools.bend = false;
		t = 0;
		bools.firstRun = true;
		bools.myFirstSongMode = false;
		bools.writeNote = false;
		bools.eraseNote = false;
		bools.disablePortB = false;
		bools.beatWrite = false;
		bools.beatErase = false;
		distAmount = 0;
		// oct = 0;

	}

	//PORTB = (PORTB & ~mask) | ((t * (t >> x) >> (t >> 4)) & mask);
	//t++;

	//   playNoteNow(random(0, 2000), 0, 1);



}




