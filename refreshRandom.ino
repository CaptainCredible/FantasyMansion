void refreshRandom() {
//	bools.allowTranspose = true;      //debug
	
	a = random(1, 20);
	b = random(1, 20);
	c = random(5, 31);
	mood = random(5);
	portBlength = random(50, 500);
	root = random(0, 12);

	//baseTempo = 3;
  baseTempo = random(3,5);
  melodyOffset = random(0,4);       //THIS IS ACTUALLY PORTB SELECTOR
 // melodyOffsetOffset = random(1,7);	 //what is this
  scaleSelect = 2;
  scaleSelect = random(0, 3);
  modulationSteps = random(0, 6);
  modulationinterval = random(-7, 7)*bools.allowTranspose;
  bools.swing = 0;// random(0, 2);
  //bools.Arp = random(2);
  bools.Arp = true;
  
  bools.BASSOCT = random(2);
  

  //FUNCS
  generateDecayArray();
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