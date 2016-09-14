#include "body.h"

void Body::move(int x1,int y1){
	//TODO
	//You need to iterate through the body and 
	//shift the previous body position to itself 
	//in order to make movement
    
    for(int i = count() - 1; i > 0; i--){
        body_[i].x = body_[i-1].x;
        body_[i].y = body_[i-1].y;
    }
    
    // set front as the new positions
    body_[0].x = x1;
    body_[0].y = y1;
}