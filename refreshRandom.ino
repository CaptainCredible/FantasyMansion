void refreshRandom() {
  a = random(1, 20);
  b = random(1, 20);
  c = random(5, 31);
  portBlength = random(50, 500);
  root = random(0, 12);
baseTempo = random(3,6);
  //WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt
//  selector = random (1, 17);
  melodyOffset = random(0,12);
  melodyOffsetOffset = random(1,7);
  scalesOffset = random(0,3)*10;
  //Decay = 1; is defined by decayarray
  generateDecayArray();
  modulationinterval = random(-7, 7)*bools.allowTranspose;
  gener8Melody();
  melodyTEST();
  if (!bools.ownBeat) {
	  gener8BDbeat();
	  gener8SDbeat();
	  gener8hats();
  }
  generateOctaves();
  modulationSteps = random(2, 6);
  scaleSelect = random(0, 3);
  bools.swing = random(0,2);
  
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