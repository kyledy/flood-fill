/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  // complete your implementation below
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  // complete your implementation below

  HSLAPixel px;
  HSLAPixel *tempPix;
  int adjustedX = p.x % img_other.width();
  int adjustedY = p.y % img_other.height();



  if (p.x < img_other.width() && p.y < img_other.height()) {
    tempPix = img_other.getPixel(p.x, p.y);
    px = *tempPix; 
  } else {
    tempPix = img_other.getPixel(adjustedX, adjustedY);
    px = *tempPix;
  }
  
  return px;
}