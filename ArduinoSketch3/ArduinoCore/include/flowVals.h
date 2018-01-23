float flows94[15][2];

void set2() {
  flows94[0][0] = -15.00;
  flows94[0][1] = 0.561;
  flows94[1][0] = -12.50;
  flows94[1][1] = 0.620;
  flows94[2][0] = -10.00;
  flows94[2][1] = 0.691;
  flows94[3][0] = -7.50;
  flows94[3][1] = 0.787;
  flows94[4][0] = -5.00;
  flows94[4][1] = 0.919;
  flows94[5][0] = -2.50;
  flows94[5][1] = 1.132;
  flows94[6][0] = -1.25;
  flows94[6][1] = 1.308;
  flows94[7][0] = 0.00;
  flows94[7][1] = 1.652;
  flows94[8][0] = 1.25;
  flows94[8][1] = 2.001;
  flows94[9][0] = 2.50;
  flows94[9][1] = 2.186;
  flows94[10][0] = 5.00;
  flows94[10][1] = 2.411;
  flows94[11][0] = 7.50;
  flows94[11][1] = 2.553;
  flows94[12][0] = 10.00;
  flows94[12][1] = 2.660;
  flows94[13][0] = 12.50;
  flows94[13][1] = 2.740;
  flows94[14][0] = 15.00;
  flows94[14][1] = 2.813;
}



float flows95[15][2];

void set() {
  flows95[0][0] = -15.00;
  flows95[0][1] = 0.471;
  flows95[1][0] = -12.50;
  flows95[1][1] = 0.538;
  flows95[2][0] = -10.00;
  flows95[2][1] = 0.621;
  flows95[3][0] = -7.50;
  flows95[3][1] = 0.735;
  flows95[4][0] = -5.00;
  flows95[4][1] = 0.891;
  flows95[5][0] = -2.50;
  flows95[5][1] = 1.142;
  flows95[6][0] = -1.25;
  flows95[6][1] = 1.351;
  flows95[7][0] = 0.00;
  flows95[7][1] = 1.751;
  flows95[8][0] = 1.25;
  flows95[8][1] = 2.143;
  flows95[9][0] = 2.50;
  flows95[9][1] = 2.356;
  flows95[10][0] = 5.00;
  flows95[10][1] = 2.615;
  flows95[11][0] = 7.50;
  flows95[11][1] = 2.785;
  flows95[12][0] = 10.00;
  flows95[12][1] = 2.911;
  flows95[13][0] = 12.50;
  flows95[13][1] = 3.008;
  flows95[14][0] = 15.00;
  flows95[14][1] = 3.096;
  set2();
}




float interpolate(float values[15][2], float val) {
  float lastVal; // S small
  float currentVal; // S big
  float lastKey; // F small
  float currentKey; // F big
  if (val >= 3.096) {
//    Serial.println("-------------\ninterpolation error: value to large");
//    Serial.println(val);
    
    return values[14][1];
  }

  for (int i = 0; i <= 14; i++) {
    currentVal = values[i][1];
    currentKey = values[i][0];
    if (!(val >= currentVal))
      break;
    lastVal = currentVal;
    lastKey = currentKey;
  }
  float out = (((val - lastVal) / (currentVal - lastVal)) * (currentKey - lastKey)) + lastKey;


  /*Serial.println("interpolated value -> ");
    Serial.print(out);
    Serial.println();
    Serial.println(val);
  */
  return out;

}

