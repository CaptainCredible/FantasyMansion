void modeSelect() {
	switch (mode) {

	//case 1:
		//musicbox();   //INIT STATE, WILL GENERATE ITS OWN BEAT AND MELODY WHEN IT CANT FIND A USER MADE CONTENT
		//break;

	case 2:
		myFirstSong();
		break;

	case 3:
		myFirstBeat();
		break;

	//case 4:
	//	musicbox();   // will use myBeat and myMelody
	//	break;


	case 5:
		trigOnPurifySolo();
		break;

	case 6: 
		portBplayer();
		break;

	default:
		musicbox();   // will use myBeat and myMelody
		break;
	}
}

//unused wont fit:
//buttonSolos()
//trig on change solo
