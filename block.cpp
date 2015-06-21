#include "block.h"

using namespace std;

// Create
Block::Block(){

}

// Destroy!
Block::~Block(){
  delete [] images[0][0], images[0][1];
}

// Load 2 images ( animation)
void Block::SetImages( string image1, string image2){
  images[0][0]= load_bitmap(image1.c_str(), NULL);
  images[0][1]= load_bitmap(image2.c_str(), NULL);
  flag = load_bitmap("images/blocks/flag.png" , NULL);
  flaged = false;
  animated = true;
}

// Load 1 image
void Block::SetImages( string image1){
  images[0][0]= load_bitmap(image1.c_str(), NULL);
  flag = load_bitmap("images/blocks/flag.png" , NULL);
  flaged = false;
  animated = false;
}

int Block::GetType(){
  return type;
}

// X/Y
int Block::GetX(){
  return x;
}

int Block::GetY(){
  return y;
}

// Width/height
int Block::GetHeight(){
  return height;
}

int Block::GetWidth(){
  return width;
}

bool Block::GetSelected(){
  return selected;
}

bool Block::GetFlaged(){
  return flaged;
}

// Get that image
BITMAP* Block::GetImage(){
  return images[0][0];
}

// Set the type
void Block::SetType(int newType){
  type = newType;
}

// Set whether already selected
void Block::SetSelected(bool newSelected){
  selected = newSelected;
}

// Set whether flagged or not
void Block::SetFlaged(bool newFlag){
  flaged = newFlag;
}

// SetX
void Block::SetX( int newValue){
  x = newValue;
}

// Set Y
void Block::SetY( int newValue){
  y = newValue;
}

// Setter for width
void Block::SetWidth(int newValue){
  width = newValue;
}

void Block::SetHeight(int newValue){
  height = newValue;
}

// Draw
void Block::draw(BITMAP* tempBitmap, float stretchWidth, float stretchHeight){
  if( !animated||frame==0||frame==1||frame==2||frame==3||frame==4||frame==5||frame==6||frame==7){
    frame += 1;
    DrawNewSprite( tempBitmap, images[0][0], stretchWidth, stretchHeight);
  }
  else if( frame==8||frame==9||frame==10||frame==11||frame==12||frame==13||frame==14||frame==15){
    frame+=1;
    DrawNewSprite( tempBitmap, images[0][1], stretchWidth, stretchHeight);
    if(frame==16){
      frame=0;
    }
  }
}


// Load new image
void Block::Change(){
  SetImages( string( "images/blocks/" + convertIntToString(type) + ".png"));
}

// Draw
void Block::DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw, float stretchWidth, float stretchHeight){
  if( GetFlaged()!=false){
    stretch_sprite( tempBitmap, spriteToDraw, x, y, stretchWidth, stretchHeight);
    stretch_sprite( tempBitmap, flag, x, y, stretchWidth, stretchHeight);
  }
  else if( GetFlaged()==false){
    stretch_sprite( tempBitmap, spriteToDraw, x, y, stretchWidth, stretchHeight);
  }
}
