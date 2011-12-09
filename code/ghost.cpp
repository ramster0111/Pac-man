#include"ghost.h"
#include<iostream>
#include"search.h"
#include"config.h"
#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0
Ghost::Ghost(){           
}

Ghost::Ghost(int color){
  Color=color;
  if(color==1){//pink
                 SetX(330);
                 SetY(300);
  } 
  if(color==2){//red
                 SetX(360);
                 SetY(300);
  } 
  if(color==3){//orange
                 SetX(390);
                 SetY(300);
  } 
  if(color==4){//brown
                 SetX(300);
                 SetY(300);
  }
  pill=0;
  Dead=false; 
  Uint32 Timer=0;
}

void Ghost::Reset(){
  if(Color==1){//pink
                 SetX(330);
                 SetY(300);
  } 
  if(Color==2){//red
                 SetX(360);
                 SetY(300);
  } 
  if(Color==3){//orange
                 SetX(390);
                 SetY(300);
  } 
  if(Color==4){//brown
                 SetX(300);
                 SetY(300);   
  }
  
pill=0;
Dead=false;
}
int Ghost::RetColor(){
    if(pill==0&&!Dead)
    return Color;
    else if(pill==1&&!Dead)
    return -1 ;
    if(Dead)
    return 10;
}

int Ghost::Move(){
    //cout <<this->GetX()/30<<"  "<<targetNx+1<<"  "<<this->GetY()/30<<"  "<<targetNy<<endl;
    if(this->GetX()/30==targetNx && this->GetY()/30==targetNy+1 )
    return 1;
    if(this->GetX()/30==targetNx-1 && this->GetY()/30==targetNy )
    return 2;
    if(this->GetX()/30==targetNx && this->GetY()/30==targetNy-1 )
    return 3;
    if(this->GetX()/30==targetNx+1 && this->GetY()/30==targetNy )
    return 4;
  //  return 1;
}


void Ghost::PacPos(int x,int y){
    targetFx=x;
    targetFy=y; 
}
void Ghost::ActivatePill(){
    pill=1;
   
    
}
int Ghost::IsPillActive(){
    return pill;
}
void Ghost::DeActivatePill(){
    pill=0;
}
void Ghost::InitiateKill(){
    Dead=true;
}
int Ghost::SetTarget(){
    // std::cout<<"target set"<<std::endl;
     
     
AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{

		// Create a start state
		MapSearchNode nodeStart;

		nodeStart.x = m_X/30;
		nodeStart.y = m_Y/30; 

		// Define the goal state
		MapSearchNode nodeEnd;
		if(pill==0&&!Dead){
		  nodeEnd.x = targetFx;						
		  nodeEnd.y = targetFy; 
        }
        if(pill==1&&!Dead){
		  nodeEnd.x = targetFy;						
		  nodeEnd.y = targetFx; 
        } 
        if(Dead){
                 
          nodeEnd.x = 12;
         // targetFx=12;
         // targetFy=9;						
          nodeEnd.y = 10; 
        }
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
			//	((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();
				
			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
			//	p->PrintNodeInfo();
	#endif			
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
		//	cout << "Search found goal state\n";
                
				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif

			//	node->PrintNodeInfo();
				node = astarsearch.GetSolutionNext();
				if(!node){
                          
                    return 1;
                }
                if(node){
 
                  targetNx=node->RetX();
			      targetNy=node->RetY();                        
            //    node->PrintNodeInfo();
                   if(Dead)
                      if(targetNx==12&&targetNy==10)
			               Reset();

			               
                }
/*			    cout << "for reference \n";
			    for( ;; )
				{
					node = astarsearch.GetSolutionNext();
					if( !node )
					{
						break;
					}

					node->PrintNodeInfo();
				};
	*/		    
			// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();

	
		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			cout << "Search terminated. Did not find goal state\n";
		
		}

		// Display the number of loops the search went through
	//	cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}

return 0;

                   
}

