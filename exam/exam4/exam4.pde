int mouseLeft = 0;
int mouseRight = 0;
int x, y, ox, oy;
int count = 0;
int[][] point = new int[100][2];
int[] state = new int[100];

float[][][] p = new float[10][4][4];

void setp()
{
for (int i = 0; i < 10; i++) {
for (int j = 0; j < 4; j++) {
for (int k = 0; k < 4; k++ ){
p[i][j][k] = 0.25;
}
}
}


//transition probability for 1
p[1][2][0] = 0.1;
p[1][2][1] = 0.1;
p[1][2][2] = 0.7;
p[1][2][3] = 0.1;

//transition probability for 3
p[3][0][0] = 0.6;
p[3][0][1] = 0.1;
p[3][0][2] = 0.2;
p[3][0][3] = 0.1;

p[3][1][0] = 0.2;
p[3][1][1] = 0.5;
p[3][1][2] = 0.1;
p[3][1][3] = 0.2;

p[3][2][0] = 0.1;
p[3][2][1] = 0.2;
p[3][2][2] = 0.6;
p[3][2][3] = 0.1;

p[3][3][0] = 0.2;
p[3][3][1] = 0.1;
p[3][3][2] = 0.1;
p[3][3][3] = 0.6;

//transition probability for 8
p[8][0][0] = 0.6;
p[8][0][1] = 0.1;
p[8][0][2] = 0.2;
p[8][0][3] = 0.1;

p[8][1][0] = 0.1;
p[8][1][1] = 0.5;
p[8][1][2] = 0.2;
p[8][1][3] = 0.2;

p[8][2][0] = 0.2;
p[8][2][1] = 0.2;
p[8][2][2] = 0.5;
p[8][2][3] = 0.1;

p[8][3][0] = 0.1;
p[8][3][1] = 0.1;
p[8][3][2] = 0.1;
p[8][3][3] = 0.7;

//transition probability for C
p[7][0][0] = 0.7;
p[7][0][1] = 0.1;
p[7][0][2] = 0.1;
p[7][0][3] = 0.1;

p[7][1][0] = 0.1;
p[7][1][1] = 0.6;
p[7][1][2] = 0.2;
p[7][1][3] = 0.1;

p[7][2][0] = 0.2;
p[7][2][1] = 0.1;
p[7][2][2] = 0.6;
p[7][2][3] = 0.1;

p[7][3][0] = 0.1;
p[7][3][1] = 0.1;
p[7][3][2] = 0.1;
p[7][3][3] = 0.1;

//transition probability for V
p[9][0][0] = 0.1;
p[9][0][1] = 0.1;
p[9][0][2] = 0.1;
p[9][0][3] = 0.7;

p[9][1][0] = 0.1;
p[9][1][1] = 0.1;
p[9][1][2] = 0.1;
p[9][1][3] = 0.1;

p[9][2][0] = 0.2;
p[9][2][1] = 0.1;
p[9][2][2] = 0.6;
p[9][2][3] = 0.1;

p[9][3][0] = 0.2;
p[9][3][1] = 0.1;
p[9][3][2] = 0.1;
p[9][3][3] = 0.6;
}

void setup(){
size(400, 400);
background(0);
noStroke();

setp();
}

int mm(){

float[] val = new float[10];

for (int i = 0; i < 10; i++) {
val[i] = 1;
for (int j = 1; j < count ; j++) {
val[i] *= p[i][state[j-1]][state[j]];
}
}

int max = 0;
for (int i = 1; i < 10; i++){
if (val[max] < val[i]){
max = i;
}
}

return max;
}

void draw(){

if (mouseLeft == 1) {
stroke(255);
strokeWeight(5);
line(ox, oy, x, y);
noStroke();
ox = x; oy = y;
int tx, ty;
tx = x-point[count][0];
ty = y-point[count][1];

if (abs(tx) > 20 || abs(ty) > 20 ) {
fill(255, 0, 0);
ellipse(x, y, 10, 10);

point[count+1][0] = x;
point[count+1][1] = y;
fill(255);
if (abs(tx) > 20) {
if (tx > 0) state[count] = 0;
else state[count] = 1;
} else if (abs(ty) > 20) {
if (ty > 0) state[count] = 2;
else state[count] = 3;
}
text(state[count], (count)%20*18+20, int((count)/20)*20+360);
count++;
}

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
count = 0;
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
ellipse(30, 25, 50, 50);
fill(255);
textSize(40);
int result = mm();
if (result == 7) {
text("C", 20, 50);
} else if (result == 9){
text("V", 20, 50);
} else {
text(result, 20, 50);
}
textSize(12);
}
mouseLeft = 0;
mouseRight = 0;

}
