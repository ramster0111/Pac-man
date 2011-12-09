#ifndef SEARCH_H
#define SEARCH_H
#include<iostream>
#include "stlastar.h"
class MapSearchNode
{
public:
      
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;	
    static int z;
	MapSearchNode() {
                    
                    MakeMap(); 
                                                       
                    x = y = 0;
    }
	MapSearchNode( unsigned int px, unsigned int py) {
                   MakeMap();
                   x=px;
                   y=py;
                  
    }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );
    int GetMap( int x, int y );
	void PrintNodeInfo(); 
    void MakeMap();
    int RetX();
    int RetY();

};
#endif

