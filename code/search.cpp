#include "config.h"
#include "search.h"
#include <cmath>
int map[468];
int MapSearchNode::z=0;
void MapSearchNode::MakeMap(){
     if(z==0){                    
     FILE *f = fopen("data\\r.txt","r");
                char c;
     for(int i=0;i<468;i++){
       c = fgetc (f);
       if(c=='7')map[i]=1;
       else if(c=='9')map[i]=1;       
       else if(c=='0')map[i]=1;                           
       else if(c==32)map[i]=1;
       else if(c==56)map[i]=1;
       else if(c=='3')map[i]=1;
       else if(c=='4')map[i]=1;
       else if(c=='4')map[i]=1;
       else if(c=='6')map[i]=1;
       else map[i]=9;
   //    std::cout<<c<<" "<<map[i]<<" ";
     //  if(i%26==0)std::cout<<std::endl;
       //std::cout<<std::endl;
     }
     std::cout<<std::endl; 
     std::cout<<std::endl;
     for(int i=0;i<18;i++){
     for(int j=0;j<26;j++)
     std::cout<<map[i*26+j]<<" ";
     std::cout<<std::endl; 
     }
     std::cout<<std::endl;
     }
     z++;
     
}

int MapSearchNode::GetMap( int x, int y )
{

	if( x < 0 ||
	    x >= 26 ||
		 y < 0 ||
		 y >= 18
	  )
	{
		return 9;	 
	}

	return map[(y*26)+x];
}

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	cout << "Node position : (" << x << ", " << y << ")" << endl;
}
int MapSearchNode::RetX()
{
return x;
}
int MapSearchNode::RetY()
{
return y;
}
// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = fabs(float(((float)x - (float)nodeGoal.x)));
	float yd = fabs(float(((float)y - (float)nodeGoal.y)));

	return xd + yd;
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y-1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (GetMap( x, y+1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}
