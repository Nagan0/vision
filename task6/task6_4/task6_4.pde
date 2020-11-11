int mouseLeft = 0;

int mouseRight = 0;

int x, y, ox, oy;

int count = 0;

int[][] point = new int[100][2];

int[] state = new int[100];



float[][] pData = new float[100][10];

int ndata = 0;

int data_number = 0;



void setup(){

     size(600, 300);

     background(0);

     

     stroke(100);

     

     line(0, 100, 300,100);

     line(0, 200, 300, 200);

     line(100, 0, 100, 300);

     line(200, 0, 200, 300);

     line(300, 0, 300, 300);

     

     noStroke();

}



void mm(){



     float[] val = new float[9];

     float[] aff = new float[9];

     color c;



     fill(0);

     rect(300,0,300,300);

     fill(255);


     for (int i = 0; i < 9; i++) {

       val[i] = 0;

          for (int j = 0; j < 100 ; j++) {

            for (int k = 0; k < 100 ; k++) {

              c = get(i%3*100+j, i/3*100+k);

              if (red(c) > 150 && green(c)>150 && blue(c)>150) {

                val[i]++;

              }   

            }

          }

          val[i] /= 100;

          pData[ndata][i] = val[i];

     }

     

     pData[ndata][9] = data_number;

   

     

     for (int i = 0; i < 9; i++){

         text(i+": "+val[i], 320, 32+i*32);

     }



}



void draw(){

     

      textSize(16);

      text(data_number, 20, 50);



     if (mouseLeft == 1) {

          stroke(255);

          strokeWeight(5);

          line(ox, oy, x, y);

          noStroke();

          ox = x; oy = y;

          int tx, ty;

          tx = x-point[count][0];

          ty = y-point[count][1];

     }

}



void mousePressed()

{

     if (mouseButton == LEFT) {

          mouseLeft = 1;

          ox = x = mouseX;

          oy = y = mouseY;

          point[0][0] = x;

          point[0][1] = y;

     }



     if (mouseButton == RIGHT) {

          mouseRight = 1;

          background(0);

          stroke(100);

     strokeWeight(1);

     line(0, 100, 300,100);

     line(0, 200, 300, 200);

     line(100, 0, 100, 300);

     line(200, 0, 200, 300);

     line(300, 0, 300, 300);

          count = 0;



 ndata++;

     }

}



void mouseDragged()

{

     if (mouseButton == LEFT) {

          mouseLeft = 1;

          x = mouseX;

          y = mouseY;

     }

}



void mouseReleased()

{

     if (mouseLeft == 1) {

          fill(0);

          ellipse(50, 25, 50, 50);

          fill(255);

          textSize(40);

          mm();

          textSize(12);

           text(ndata, 40, 50);

     }

     mouseLeft = 0;

     mouseRight = 0;

}



void keyPressed() {    //キーボード処理



  if (key == '0') data_number = 0;

  if (key == '1') data_number = 1;

  if (key == '2') data_number = 2;

  if (key == '3') data_number = 3;

  if (key == '4') data_number = 4;

  if (key == '5') data_number = 5;

  if (key == '6') data_number = 6;

  if (key == '7') data_number = 7;

  if (key == '8') data_number = 8; 

  if (key == '9') data_number = 9;

  fill(0);

  rect(5,25, 30, 30); 

  fill(255);



  if(key == 'q'){

    PrintWriter outfile;   

    outfile = createWriter("data.txt"); 

     for (int j = 0; j < 9; j++) {

      outfile.print("data" + j +"\t");

      }

     

      outfile.print("class" +"\t");

      outfile.println();

    for (int i = 0; i < ndata; i++) {

      for (int j = 0; j < 9; j++) {

      outfile.print(pData[i][j]+"\t");

      }

      outfile.print("["+pData[i][9]+"]"+"\t");

      outfile.println();

    }



    outfile.flush(); //残りを出力する

    outfile.close(); // ファイルを閉じる

    exit(); // 終了

  }

}
