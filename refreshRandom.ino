void refreshRandom() {
  a = random(1, 20);
  b = random(1, 20);
  c = random(5, 31);
  selector = random (1, 17);
  melodyOffset = random(0,12);
  melodyOffsetOffset = random(1,7);
  scalesOffset = random(0,3)*10;
  Decay = random(5,10);//   5 absolute min
  modulationinterval = 2^random(1,4);
  gener8Melody();
  gener8BDbeat();
  gener8SDbeat();
  gener8hats();
  generateOctaves();
}
