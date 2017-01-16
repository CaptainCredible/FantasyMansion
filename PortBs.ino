void playPortBsamp(int i) {

  //PORTB = (PORTB & ~mask) | (OutPut(i) & mask); //MASK THE PINS WE WANT TO WRITE TO
int OUT = OutPut(i);
PORTB = (PORTB & ~mask) | (OUT & mask);//mask);
// delay(1);
}


byte OutPut(long i) {
  switch (selector) {

    case 1:
      // Turings Tits Period = 16500
      return  i * (i >> a | i >> b);
      break;

    case 2:
      // Adas nightmare,
      return i * (i >> a | i >> b) & (c * 3) ;
      break;

    // case 3:
    // mandelbrots orgy, //seems a little crap, often silent
    //   return (i >> b + i << c);
    //   break;

    case 4:
      //long wank, Period = 16500
      return ((i * (i >> b | i >> 9) | (i / 256 + a)&i >> 8)) ^ (i & i >> c | i >> 6);
      break;

    case 5:
      // drunk drum machine,
      return (i * (b / 2) | i >> a) | (i * c & i >> 3);
      break;

    case 6:
      //Serpinskis Anus
      return (i & i >> a | i >> (b / 2));
      break;

    case 7:
      //descent into hell
      //a=5;
      //c=c/2;
      return i % ((i >> a) & (i >> c)) ;
      break;

    // case 8:
    //bad core
    //   return i * ( ((i >> 9) & 10) | ((i >> 11)&a) ^ ((i >> b) & 15 & (i >> c)) );
    //   break;

    case 9:
      //ROFL
      return i * ((i >> 3 | i >> b) & (a * 3)&i >> 9);
      break;

    case 10:
      //Schrodingers guilt,
      return i * ((i >> a | i >> b)&c & i >> 6);
      break;

    case 11:
      //it is dangerous to go alone,
      return i >> (i | b) >> c >> i;
      break;

    case 12:
      //Pewpewpewpewpewpewpewpewpew
      return i * (i >> a | i >> b) >> (i >> c);
      break;

    case 13:
      //C,O,U, simulation
      return ((i * 2) & (i >> (i >> a))) + ((i * 1) & (i >> c) & 31);
      break;

    case 14:
      //quack
      return ((i >> a | i % b) & (i >> c | i % 19));
      break;

    case 15:
      //???
      return i >> (i | b) >> c >> i;
      break;

    case 16:
      //skynetflix
      return i * (i >> a | i >> b) >> (i >> c);
      break;
    default:
      break;
  }
  return 0;


}
