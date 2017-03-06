void refreshRandom() {
	Decay = 6;
	//	bools.allowTranspose = true;      //debug

	a = random(1, 20);
	b = random(1, 20);
	c = random(5, 31);
	mood = random(5);
	portBlength = random(50, 500);
	root = random(0, 12);

	baseTempo = 3;
	//baseTempo = random(3,5);
	portBselector = random(0, 4);       //THIS IS ACTUALLY PORTB SELECTOR
	scaleSelect = 2;
	scaleSelect = random(0, 3);
	modulationSteps = random(0, 6);
	modulationinterval = random(-7, 7)*bools.allowTranspose;
	bools.swing = random(0, 2);
	bools.Arp = !(random(3));   //1 in 3 chance

	bools.BASSOCT = random(2);


	//FUNCS
	//generateDecayArray();
	gener8Melody();
	generateBassLine();
	// melodyTEST();
	if (!bools.ownBeat) {
		gener8BDbeat();
		gener8SDbeat();
		gener8hats();
	}


	//generateOctaves();

	/*
	byte magic = random(0, 3);
	switch (magic) {
	case 0:
		barLength =initBarLength >> random(4);
		break;
	case 1:
		barLength = random(4, initBarLength+1);
		break;
	default:
		barLength = initBarLength;

	}

	*/
}