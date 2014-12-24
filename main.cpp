#include<allegro.h>
#include<string>
#include<time.h>

#include"block.h"
  
//Creates the blocks on screen
Block MyBlocks[14][9];

//Images
BITMAP* buffer;
BITMAP* background;
BITMAP* cursor;
BITMAP* bimages[11];
BITMAP* foreground;
BITMAP* menu;
BITMAP* splash;
BITMAP* title;

//Sounds
SAMPLE* explode;
SAMPLE* timer;

//Fonts
FONT *f1, *f2, *f3, *f4, *f5; 

//Variables
int done;
int mines; 
int flags;
int elaspedTime;
int gameScreen;

bool mousedown;
bool firstPress;
bool sound;
bool closeGame;

//Timers
clock_t startTime;
clock_t currentTime;

//FPS System
volatile int ticks = 0;
int updates_per_second = 100;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

void ticker(){
    ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
    game_time++;
}
END_OF_FUNCTION(ticker)

//Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest; 
  int range = (highest - lowest) + 1;    
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber; 
}

//Fade in
void highcolor_fade_in(BITMAP* bmp_orig, int speed){
  BITMAP* bmp_buff;
     
  if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
    int a;
    if (speed<=0)speed=16;
      
    for(a=0;a<256;a+=speed){
      clear(bmp_buff);
      set_trans_blender(0,0,0,a);
      draw_trans_sprite(bmp_buff,bmp_orig,0,0);
      vsync();
      blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    destroy_bitmap(bmp_buff);
  }
  blit(bmp_orig,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

//Fade out
void highcolor_fade_out(int speed){
  BITMAP* bmp_orig, *bmp_buff;
     
  if((bmp_orig=create_bitmap(SCREEN_W,SCREEN_H))){
    if((bmp_buff=create_bitmap(SCREEN_W,SCREEN_H))){
      int a;
      blit(screen,bmp_orig,0,0,0,0,SCREEN_W,SCREEN_H);
      if (speed<=0)speed=16;
      
      for(a=255-speed;a>0;a-=speed){
         clear(bmp_buff);
         set_trans_blender(0,0,0,a);
         draw_trans_sprite(bmp_buff,bmp_orig,0,0);
         vsync();
         blit(bmp_buff,screen,0,0,0,0,SCREEN_W,SCREEN_H);
      }
    destroy_bitmap(bmp_buff);
    }
    destroy_bitmap(bmp_orig);
  }
  rectfill(screen,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
}

//Sets up game
void setup(bool first){
  //Sets Variables
  mines = 0;
  flags = 0;
  
  mousedown = false;
  firstPress = false;
  sound = true;
  
  //Resets Timers
  startTime = clock();
  currentTime = clock();
  
  //Resets blocks for new game
  for(int i=0; i<14; i++){
    for(int t=0; t<9; t++){
      MyBlocks[i][t].SetType(0);
    }
  }
  
  //Sets Block Mines
  for(int i=0; i<14; i++){
    for(int t=0; t<9; t++){
      if(random(0, 7) == 0){
        MyBlocks[i][t].SetType(9);
        mines++;
      }
    }
  }
  
  //Sets block number based on surrounding mines
  for(int i=0; i<14; i++){
    for(int t=0; t<9; t++){
      if(MyBlocks[i][t].GetType()!=9){                       
        int type=0;
        
        if(i<13){               
          if(MyBlocks[i+1][t].GetType()==9){type++;}
        }
        if(i<13 && t>0){     
          if(MyBlocks[i+1][t-1].GetType()==9){type++;}
        }
        if(i<13 && t<8){      
          if(MyBlocks[i+1][t+1].GetType()==9){type++;}
        }
        if(t<8){
          if(MyBlocks[i][t+1].GetType()==9){type++;}
        }
        if(i>0){
          if(MyBlocks[i-1][t].GetType()==9){type++;}
        }
        if(i>0 && t>0){ 
          if(MyBlocks[i-1][t-1].GetType()==9){type++;}
        }
        if(i>0 && t<8){     
          if(MyBlocks[i-1][t+1].GetType()==9){type++;}
        }
        if(t>0){     
          if(MyBlocks[i][t-1].GetType()==9){type++;}
        }
        MyBlocks[i][t].SetType(type);
      } 
    }   
  } 
  
  //Sets Info
  for(int i=0; i<14; i++){
    for(int t=0; t<9; t++){
      MyBlocks[i][t].SetImages("images/blocks/none.bmp","images/blocks/none.bmp");
      MyBlocks[i][t].SetFlaged(false); 
      MyBlocks[i][t].SetSelected(false); 
    }
  }
  
  //Sets positions
  for(int i=0; i<14; i++){
    for(int t=0; t<9; t++){
      MyBlocks[i][t].SetX(i*40+40);
      MyBlocks[i][t].SetY(t*40+40);
    }
  }
  
  if(first){
    //Creates a random number generator (based on time)
    srand (time(NULL));
    
    //Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
    
    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
    
    //Set variables
    gameScreen = 0;
    
    //Sets Cursors
    cursor = load_bitmap( "images/cursor.bmp", NULL);
    
    //Creates a buffer
    buffer = create_bitmap( 640, 480);
    
    //Sets Starting Images
    title = load_bitmap( "images/title.bmp", NULL);
    splash = load_bitmap( "images/splash.bmp", NULL);
    
    //Sets background
    background = load_bitmap( "images/background.bmp", NULL);
    
    //Sets Foreground
    foreground = load_bitmap( "images/foreground.bmp", NULL);
    
    //Sets Sounds
    explode = load_sample( "sounds/explode.wav" );
    timer = load_sample( "sounds/timer.wav" );
    
    //Sets menu
    menu = load_bitmap( "images/menu.bmp", NULL);
    
    //Sets Font
    f1 = load_font("data/arial_rounded_mt_bold.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    
    // Merge fonts 
    font = merge_fonts(f4, f5 = merge_fonts(f2, f3));
    
    // Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);
  }
}   

//Updates screen, does mouse routines and checks for falling
void game(){
  
  //A.D.S. Games Splash         
  if(gameScreen == 0){
    highcolor_fade_in(splash,8);
    rest(2000);
    highcolor_fade_out(8);
    gameScreen = 1;
  }
  
  //Minesweeper Splash
  else if(gameScreen == 1){
    highcolor_fade_in(title,8);
    readkey();
    highcolor_fade_out(8);
    gameScreen = 4;
    highcolor_fade_in(background,8);
    setup(false);
  }
  
  //Menu
  else if(gameScreen == 2){
    gameScreen = 3;
  }
  
  //Difficulty Select
  else if(gameScreen == 3){
    gameScreen = 4;
  }
  
  //Game
  else if(gameScreen == 4){   
    //Update Clock
    currentTime = clock();
    
    //Plays stressing timer sound
    if((int(currentTime-startTime)/CLOCKS_PER_SEC)>elaspedTime && sound==true){
      play_sample(timer,255,122,500,0);
    }
    
    //Updates Elasped Time
    elaspedTime = int(currentTime-startTime)/CLOCKS_PER_SEC;
    
    //Checks for win
    if(mines-flags==0){
      int blocks = 0;
      bool blanks = false;
      for(int i=0; i<14; i++){
        for(int t=0; t<9; t++){
          if(MyBlocks[i][t].GetFlaged()==true && MyBlocks[i][t].GetType()==9){
            blocks++;
          }
          if(MyBlocks[i][t].GetSelected() == false && MyBlocks[i][t].GetFlaged() == false && MyBlocks[i][t].GetType() != 9){
            blanks = true;
          }
          if(blocks==mines && !blanks){
            //Reveal Map
            for(int i=0; i<14; i++){
              for(int t=0; t<9; t++){
                MyBlocks[i][t].Change();
              }
            }
            gameScreen = 5;
          }     
        }
      }
    }           
    
    
    //Checks if mouse is in collision with object
    if(mouse_b){
      for(int i=0; i<14; i++){
        for(int t=0; t<9; t++){
          if((MyBlocks[i][t].GetX()/40)*40==(mouse_x/40)*40 && (MyBlocks[i][t].GetY()/40)*40==(mouse_y/40)*40){
            if(mouse_b&1 && mousedown==false && MyBlocks[i][t].GetFlaged()==false){
              MyBlocks[i][t].Change();
              MyBlocks[i][t].SetSelected(true);
              if(MyBlocks[i][t].GetType()==9){
                play_sample(explode,255,122,random(500, 1500),0);
                //Reveal Map
                for(int i=0; i<14; i++){
                  for(int t=0; t<9; t++){
                    MyBlocks[i][t].Change();
                  }
                }
                gameScreen = 6;
              }
              mousedown=true;
            }
            if(mouse_b&2 && mousedown==false){
              if(MyBlocks[i][t].GetSelected()==false){             
                if(MyBlocks[i][t].GetFlaged()==false){
                  MyBlocks[i][t].SetFlaged(true);
                  flags++;
                }
                else{
                  MyBlocks[i][t].SetFlaged(false);
                  flags--;
                }
              }
              mousedown=true;
            }
          }                            
        }            
      }
    }
    
    //Checks near blocks and removes wrapping
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        
        if(MyBlocks[i][t].GetSelected()==true && MyBlocks[i][t].GetType()==0){
          MyBlocks[i][t].SetType(10);
          MyBlocks[i][t].Change();  
          if(i<13){               
            MyBlocks[i+1][t].Change();
            MyBlocks[i+1][t].SetSelected(true);
          }
          if(i<13 && t>0){     
            MyBlocks[i+1][t-1].Change();
            MyBlocks[i+1][t-1].SetSelected(true);
          }
          if(i<13 && t<8){      
            MyBlocks[i+1][t+1].Change();
            MyBlocks[i+1][t+1].SetSelected(true);
          }
          if(t<8){
            MyBlocks[i][t+1].Change();
            MyBlocks[i][t+1].SetSelected(true);
          }
          if(i>0){
            MyBlocks[i-1][t].Change();
            MyBlocks[i-1][t].SetSelected(true);
          }
          if(i>0 && t>0){ 
            MyBlocks[i-1][t-1].Change();
            MyBlocks[i-1][t-1].SetSelected(true);
          }
          if(i>0 && t<8){     
            MyBlocks[i-1][t+1].Change();
            MyBlocks[i-1][t+1].SetSelected(true);
          }
          if(t>0){     
            MyBlocks[i][t-1].Change();
            MyBlocks[i][t-1].SetSelected(true);
          }
        }
      }        
    }
    
    //Resets Mousdown
    if(!mouse_b && !key[KEY_SPACE]){
      mousedown=false; 
    }
    
    //Counter for FPS
    frames_done++;
  }
  
  //Win
  else if(gameScreen == 5){
    int newgame = 0;
    
    //Press buttons
    if(mouse_b&1){
      if(mouse_x<260&&mouse_x>170&&mouse_y<290&&mouse_y>260){
        setup(false);
        gameScreen = 4;
        highcolor_fade_out(8);
      }
      else if(mouse_x<470&&mouse_x>380&&mouse_y<290&&mouse_y>260){
        closeGame = true;
      }
    }
  }
  
  //Lose
  else if(gameScreen == 6){
    int newgame = 0;
    
    //Press buttons
    if(mouse_b&1){
      if(mouse_x<260&&mouse_x>170&&mouse_y<290&&mouse_y>260){
        setup(false);
        gameScreen = 4;
        highcolor_fade_out(8);
      }
      else if(mouse_x<470&&mouse_x>380&&mouse_y<290&&mouse_y>260){
        closeGame = true;
      }
    }
  }
  
  //End game
  if(key[KEY_ESC]){
    closeGame = true;
  }
}

void draw(){
  //A.D.S. Games Splash         
  if(gameScreen == 0){ }
  
  //Minesweeper Splash
  else if(gameScreen == 1){ }
  
  //Menu
  else if(gameScreen == 2){ }
  
  //Difficulty Select
  else if(gameScreen == 3){ }
  
  //Game
  else if(gameScreen == 4){
    //Draws background         
    draw_sprite( buffer, background, 0, 0);
    
    //Draw blocks
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        MyBlocks[i][t].draw(buffer);
      }
    }
    
    //Draws foreground         
    draw_sprite( buffer, foreground, 0, 0);
    
    //Draws text
    textprintf_right_ex(buffer,font,620,0, makecol(255,255,255),-1,"Mines Left: %i" ,mines-flags);
    textprintf_ex(buffer,font,20,0, makecol(255,255,255),-1,"Time: %i" ,elaspedTime);
    
    
    //Draws Mouse
    draw_sprite( buffer, cursor, mouse_x-10, mouse_y-10);
  }
  
  //Win
  else if(gameScreen == 5){
    draw_sprite( buffer, background, 0, 0);
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        MyBlocks[i][t].draw(buffer);
      }
    }
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        if(MyBlocks[i][t].GetSelected()==true){
          MyBlocks[i][t].draw(buffer);
        }
      }   
    }
    
    draw_sprite(buffer, menu, 150, 150);   
    draw_sprite(buffer, foreground, 0, 0);
    
    textprintf_centre_ex(buffer,font,320,155, makecol(0,0,0),-1,"You Win!");
    textprintf_centre_ex(buffer,font,320,185, makecol(0,0,0),-1,"Time: %i Seconds",elaspedTime);
    
    draw_sprite( buffer, cursor, mouse_x, mouse_y);
  }
  
  //Lose
  else if(gameScreen == 6){
    draw_sprite( buffer, background, 0, 0);
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        MyBlocks[i][t].draw(buffer);
      }
    }
    for(int i=0; i<14; i++){
      for(int t=0; t<9; t++){
        if(MyBlocks[i][t].GetSelected()==true){
          MyBlocks[i][t].draw(buffer);
        }
      }   
    }
    
    draw_sprite(buffer, menu, 150, 150);   
    draw_sprite(buffer, foreground, 0, 0);

    textprintf_centre_ex(buffer,font,320,155, makecol(0,0,0),-1,"You Lose!");
    textprintf_centre_ex(buffer,font,320,185, makecol(0,0,0),-1,"Mines Left: %i",mines-flags);
    
    draw_sprite( buffer, cursor, mouse_x, mouse_y);
  }
    
  //Draws buffer         
  draw_sprite( screen, buffer, 0, 0);
}

//main function of program    
int main(){
  
  //Initializing  
  allegro_init();
  install_keyboard();
  install_mouse();
  install_timer();
  set_color_depth(32);
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  set_window_title("Minesweeper");
  
  //Setup game
  setup(true);
  
  //Handles exit
  while(!closeGame){
    //Runs FPS system
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;
      //Update always
      game();
      ticks--;
      if(old_ticks <= ticks){  
        break; 
      }
    }
    if(game_time - old_time >= 10){
      fps = frames_done;
      frames_done = 0;
      old_time = game_time;
    }
    //Update every set amount of frames
    draw();
  }      
  
  //Clears Memory
  delete [] buffer, background, cursor, bimages, foreground, title, explode, menu, font;
  
  allegro_exit();
  
  return 0;
}
END_OF_MAIN();
