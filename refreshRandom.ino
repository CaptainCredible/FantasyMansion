void refreshRandom() {
  a = random(1, 20);
  b = random(1, 20);
  c = random(5, 31);
  portBlength = random(50, 500);
  root = random(0, 12);
  //Tempo = 6;
  //WDTCR = 1 << WDIE | Tempo << WDP0; // 4 Hz interrupt
//  selector = random (1, 17);
  melodyOffset = random(0,12);
  melodyOffsetOffset = random(1,7);
  scalesOffset = random(0,3)*10;
  Decay = 1;// random(8, 2);//   5 absolute min   //MAKE A DECAYARRAY!!!!
  generateDecayArray();
  //modulationinterval = 2^random(1,6);
  modulationinterval = random(-7, 7);
  gener8Melody();
  melodyTEST();
  gener8BDbeat();
  gener8SDbeat();
  gener8hats();
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