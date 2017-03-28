void xManip(int select) {
	if (x < 0) {
		x = 0;                          //make 400 the floor
	}
	else if (x > 600) {
		x = 600;                        //make 600 the ceiling
	}


	switch (select) {
	case 0:
		//do nothing
		break;

	case 1: //insanepitchrange
		x = x << 2;
			//x = x * 5;
		//x = (15 ^ x) - 50000;
		break;

	case 2: //megapitchrange
		x = (x * 10) - 5000;
		//x = x - 5000;
		break;

	default:
		break;
	}
}