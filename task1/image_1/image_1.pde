PImage img;
 
void setup(){

    size(400, 400);
    
    //read image
    img = loadImage("photo.jpg");

    //set windowsize based on image size
    surface.setSize(img.width, img.height);
}

 
void draw() {
    image(img, 0, 0);  //display image
}
