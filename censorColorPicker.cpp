/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;
  
  // initializing the blocky img
  blockyimg = blockify(img);  
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{  
  HSLAPixel px;
  
  // determines if is in active region or not
  if (PointDistance(p, center) <= radius) {
    px = *blockyimg.getPixel(p.x, p.y);
  } else {
    px =  *img.getPixel(p.x, p.y); 
  }
  return px;
}

PNG CensorColorPicker::blockify(PNG& img) {
  PNG imgtoAdjust = PNG(img);


  for (unsigned int x = 0; x < imgtoAdjust.width(); x += blockwidth) {
    for (unsigned int y = 0; y < imgtoAdjust.height(); y += blockwidth) {
      HSLAPixel px = getColorFromBlock(x, y);

      for (unsigned int i = x; i < imgtoAdjust.width(); i++) {
        for (unsigned int j = y; j < imgtoAdjust.height(); j++) {
          HSLAPixel *pixel = imgtoAdjust.getPixel(i, j);
          *pixel = px;
        }
      }
      
    }
  }

  return imgtoAdjust;
}

HSLAPixel CensorColorPicker::getColorFromBlock(int x, int y) {
  double sumHue = 0.0;
  double sumSat = 0.0;
  double sumLum = 0.0;
  double sumAlp = 0.0;
  
  for (unsigned int i = x; i < x + blockwidth; i++) {
    for (unsigned int j = y; j < y + blockwidth; j++) {
      HSLAPixel *px = img.getPixel(i, j);
      sumHue += px->h;
      sumSat += px->s;
      sumLum += px->l;
      sumAlp += px->a;
    }
  }

  double areaofBlock = (double) blockwidth * (double) blockwidth;

  double avgHue = (double) sumHue / (double) areaofBlock;
  double avgSat = (double) sumSat / (double) areaofBlock;
  double avgLum = (double) sumLum / (double) areaofBlock;
  double avgAlp = (double) sumAlp / (double) areaofBlock;

  HSLAPixel toReturn;
  toReturn.h = avgHue;
  toReturn.s = avgSat;
  toReturn.l = avgLum;
  toReturn.a = avgAlp;
  return toReturn;
  // skjdnvdsnvdjsvns
}




