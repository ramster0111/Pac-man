//check moveFLAG
    if(moveFLAG==1){            
        if(bvar.myposition[2]==bvar.target[0] || bvar.myposition[1]==bvar.target[1])
        {
            //turn the bot
            //to check whether to move down
            if(bvar.target[1]==bvar.myposition[1]+1){
                    changePhase(3);
            }
            
            //to check whether to move up
            if(bvar.target[1]==bvar.myposition[1]-1){
                    changePhase(1);
            }
    
            //to check whether to move left
            if(bvar.target[0]==bvar.myposition[2]-1){
                    changePhase(4);
            }
    
            //to check whether to move right
            if(bvar.target[0]==bvar.myposition[2]+1){
                    changePhase(2);
            }
        }    
        move();    
