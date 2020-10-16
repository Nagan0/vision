PImage img, img2;


void setup() {
  size(400, 400);

  img = loadImage("chinese_food.jpg");

  //create one more image
  img2 = createImage(img.width, img.height, RGB);

  surface.setSize(img.width*2, img.height);
}


void draw() {

  float r, g, b;

  color c;
  image(img, 0, 0);  //display original image

  for ( int y = 0; y < img.height; y++) {

    for ( int x = 0; x < img.width; x++) {

      //get rgb value
      r = red(img.get(x, y));
      g = green(img.get(x, y));
      b = blue(img.get(x, y));

      //exchange rgb data
      c = color(g, b, r);

      img2.set(x, y, c);
    }
  }

  image(img2, img.width, 0);  //display second image
}
