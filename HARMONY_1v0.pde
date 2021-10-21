import org.openkinect.processing.*; //<>//
import processing.serial.*;

Kinect2 kinect2;
Serial myPort;  // Create object from Serial class
int totalB = 0, count = 0;

void setup() {
  size(512, 424, P3D);
  kinect2 = new Kinect2(this);
  kinect2.initDepth();
  kinect2.initDevice();
  
  String portName = "COM5";
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0);

  PImage img = kinect2.getDepthImage();
  image(img, 0, 0);

  int skip = 20;
  for (int x = 0; x < img.width; x+=skip) {
    for (int y = 0; y < img.height; y+=skip) {
      int index = x + y * img.width;
      float b = brightness(img.pixels[index]);
      totalB = totalB + (int)b;
      //println(b);

      //float z = map(b, 0, 255, 250, -250);
      fill(b);
      //pushMatrix();
      //translate(x, y, z);
      rect(x, y, skip, skip);
      //popMatrix();
    }
  }
      //println("-" + totalB);

  if(totalB > 1000) {
    count++;
    if(count > 500){
    println(totalB);
    count = 0;
    } 
  } else {count = 0;}
  myPort.write(totalB);


  totalB = 0;

}
