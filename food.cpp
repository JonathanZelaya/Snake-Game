#include "food.h"

//need to update the random food position
//need to be implemented
void Food::update(std::vector<Position> &body,int hx,int hy){
    int i;
    int flag = 0;
    while(true){
        // Generate x and y position
        pos.x = (rand() % (ROW - 2))+2;
        pos.y = (rand() % (COL - 2))+2;
        
        // check if food is inside the snake body
        if(pos.x != hx && pos.y != hy){
            for(i = 0; i < body.size(); i++){
                if(pos.x != body[i].x && pos.y != body[i].y){
                    flag = 1;
                }
            }
        }
 
        if(flag){break;}
        //continue;
    }
}

