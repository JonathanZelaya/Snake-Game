#include "game.h"
#include "pen.h"


using namespace std;
// 33 is olive
// 37 is grey
// 44 is black
// 0 is white
// 41 is red

//get_key will return the key user typed
char Game::get_key() {
    int n;
    char buf[3];
    n = read(0,buf,sizeof(buf));
    if(3 == n && buf[0] == 27 && buf[1] == 91){
        return buf[2];
    }
    else if(1 == n){
        return buf[0];
    }
    return 0;
}


//need to implement end funtion()
int Game::end()                  //exit game function
{
    pen.draw_box(9,34,4,14,44,0,'X');
    pen.goto_xy(11,37);
    pen.putstr(31,1,"GAME OVER");
    
    pen.goto_xy(22,20);
    pen.putstr(31,1,"Score: " + to_string(score));
    
    system("stty echo icanon");     //restart cache
    pen.goto_xy(100,0);
    pen.show_cur();
    
	//TODO
	//need to make cursor goto the bottom
	//need to show cursor
	
    exit(0);                        //exit
}

//TODO need to implement this function which will take a infinite loop to
//set direction of snake head

int Game::getKey(){
    
    int quit = 0;
    int flag = 1;
    
    while(!quit){
        char key;
        key = get_key();                   // Call given function
        
        switch(key){
            case UP:
                snake.head.direction = UP;
                break;
            case DOWN:
                snake.head.direction = DOWN;
                break;
            case LEFT:
                snake.head.direction = LEFT;
                break;
            case RIGHT:
                snake.head.direction = RIGHT;
                break;
            default:
                break;
        }
    }
    return 0;
}


//function use to draw a box
void Game::drawBox()                     //draw the outer range
{
    pen.clr_scrn();
    if(score < 100){
    pen.draw_box(1,20,ROW,COL,44,34,'#');
    }else{
    pen.draw_box(1,20,ROW,COL,0,41,'x');
    }
}

void Game::drawSnake(void)                   // draw snake
{
    int i;
    pen.draw_rect(snake.head.pos.x,snake.head.pos.y + 20,1,1,43,43,'O');
    for(i = 0; i <=snake.body.count()-1;i++){
        /////////////////////////////////
        pen.draw_rect(snake.body.body_[i].x,snake.body.body_[i].y + 20,1,1,43,43,' ');
    }
}

void Game::snakeMove(void){
    
    int i;
    // If head reaches edge
    if(snake.head.pos.x <= 1 || snake.head.pos.x >= ROW + 1 || snake.head.pos.y <= 0 || snake.head.pos.y >= COL){
        end();
    }
    
    // If head crashes into body
    for(i = 0; i < snake.body.count(); i++){
        if(snake.head.pos.x == snake.body.body_[i].x && snake.head.pos.y == snake.body.body_[i].y){
            end();
        }
    }
    
    // if head reaches the food
    if(snake.head.pos.x == food.pos.x && snake.head.pos.y == food.pos.y){
        food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);
        snake.body.add(0,0);
        score = score + 10;
    }
    
    snake.body.move(snake.head.pos.x,snake.head.pos.y);
    
    switch(snake.head.direction){
        case UP:
            if(fkey != 'd'){
                snake.head.pos.x -= 1;
                fkey = 'u';
            }else{
                snake.head.pos.x += 1;
            }
            break;
                
        case DOWN:
            if(fkey != 'u'){
                snake.head.pos.x += 1;
                fkey = 'd';
            }else{
                snake.head.pos.x -= 1;
            }
            break;
            
        case LEFT:
            if(fkey != 'r'){
                snake.head.pos.y -= 1;
                fkey = 'l';
            }else{
                snake.head.pos.y += 1;
            }
            break;
            
        case RIGHT:
            if(fkey != 'l'){
                snake.head.pos.y += 1;
                fkey = 'r';
            }else{
                snake.head.pos.y -=1;
            }
            
        default:
            break;
                
    }
    
	//TODO
	//need to check if the head space is valid 
	//if it is valid check if the space has food
	//if it has food-->update food && update body
	//make movement
	//update head position
	//use fkey(fault key) to check the wrong direction
}

void Game::start(){
    int quit = 0;
    score = 0;
    while(!quit){
        system("stty -echo -icanon");   //cancel cache；
        pen.hide_cur();
        pen.clr_scrn();                     
        drawBox();                     
 
        pen.goto_xy(5,29);
        pen.putstr(31,1,"Welcome to the Snack Game!");
        
        pen.goto_xy(8,26);
        pen.putstr(31,1,"MOVE WITH THE ARROW KEYS! EAT");
        pen.goto_xy(9,26);
        pen.putstr(31,1,"  THE FOOD TO MAKE THE SNAKE");
        pen.goto_xy(10,26);
        pen.putstr(31,1," GROW! DO NOT EAT YOURSELF OR");
        pen.goto_xy(11,26);
        pen.putstr(31,1," CRASH INTO WALLS! GOOD LUCK!");
        
        pen.goto_xy(15,32);
        pen.putstr(31,1,"Press UP to start!");
		
        fflush(stdout); //flush the buffer
        int back = 0;
        while(!back){
            char key = '0';
            int i;
            key = get_key();            //get key
            switch(key){
                case 65:        // start game,??? is the key you use to start game
					gameStart();
					std::thread f1([&](){
						handler();
					});
					std::thread f2([&](){
						getKey();
					});
					f1.join();
					f2.join(); 
 
                    back = 1;           // note for end
                    break;
            }   
 
        }
    }
    end();                     // end of game
}


//handler is use to draw food and update snake position
void Game::handler(){

    while(true){
        drawBox();
        pen.draw_rect(food.pos.x,food.pos.y + 20, 1,1,46,36,'#');
        snakeMove();
        drawSnake();
        
        if(score >= 0 && score < 50){speed = 100000;}
        else if(score >= 50 && score < 150){speed = 75000;}
        else if(score >= 150 && score < 200){speed = 50000;}
        else{speed = 30000;}
        
        pen.goto_xy(22,20);
        pen.putstr(31,1,"Score: " + to_string(score));
        fflush(stdout);
        usleep(speed);
       
    }
	//TODO
	//use a infinite loop
	//draw the game box
	//draw the food
	//move the snake
	//flush the cache
	//use usleep(speed) to control speed
}

void Game::gameStart(){
    snake.head.pos.x = 10;                          //init the head position
    snake.head.pos.y = 21;
	snake.body.add(10,19);                          //init the body position
	snake.body.add(10,18); 
	snake.body.add(10,17);
    snake.body.add(10,16);
    snake.body.add(10,15);
    
    fkey = 'r';                                     //direction
    snake.head.direction = RIGHT;                   //head direction
    speed =  50;
    food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);
}


