#define numberOfModes 9

void modeSelect() {
	if (bools.limbo) {
		bools.disablePortB = true;
		bools.play = true;
		playPortBsamp(t, 1);
	}
	else {

		switch (mode) {

			//case 1:
				//musicbox();   //INIT STATE, WILL GENERATE ITS OWN BEAT AND MELODY WHEN IT CANT FIND A USER MADE CONTENT
				//break;

		case 2:
			bools.TMelOrFBass = true;
			//dingDong();
			myFirstSong();
			bools.BASS = true;
			break;

		case 3:
			bools.TMelOrFBass = false;
			myFirstSong();
			bools.BASS = true;

			break;

		case 4:
			myFirstBeat();
			//HHseq = 0B0001000100010001;
			
			break;

		case 6:
			//musicbox();
			buttonSolos();
//			trigOnPurifySolo();
			break;

		case 7:
			portBplayer();
			break;
		case 8:
			//trigOnChangeSolo();
			break;

		default:
			musicbox();   // will use myBeat and myMelody
			break;
		}
	}
}

//unused wont fit:
//buttonSolos()
//trig on change solo
