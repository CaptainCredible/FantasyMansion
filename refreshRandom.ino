void refreshRandom() {
	bools.allowTranspose = true;      //debug
	
	a = random(1, 20);
	b = random(1, 20);
	c = random(5, 31);

	portBlength = random(50, 500);
  
	root = random(0, 12);

	//baseTempo = 3;
  baseTempo = random(3,6);
  melodyOffset = random(0,12);       //what is this
  melodyOffsetOffset = random(1,7);	 //what is this
  scaleSelect = 2;
  scaleSelect = random(0, 3);
  modulationSteps = random(2, 6);
  modulationinterval = random(-7, 7)*bools.allowTranspose;
  bools.swing = random(0, 2);
  bools.Arp = random(2);
  bools.BASSOCT = random(2);

  //FUNCS
  generateDecayArray();
  gener8Melody();
 // melodyTEST();
  if (!bools.ownBeat) {
	  gener8BDbeat();
	  gener8SDbeat();
	  gener8hats();
  }
  generateOctaves();
  
  /*
  byte magic = random(0, 3);
  switch (magic) {
  case 0:
	  barLength = random(1, 5) * 8;
	  break;
  case 1:
	  barLength = random(4, 32);
	  break;
  default:
	  barLength = 32;

  }

  */
}