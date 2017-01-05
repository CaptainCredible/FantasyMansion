void xManip(int select) {

  switch (select) {
    case 0:
      //do nothing
      break;

    case 1: //insanepitchrange
      x = x * 5;
      x = 10 ^ x;
      break;

    case 2: //megapitchrange
      x = x * 10;
      x = x - 5000;
      break;

      default:
      //nothing
      break;

  }
}

