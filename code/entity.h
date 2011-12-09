#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:

	Entity(){
    }
	int GetX(){
         return m_X;
    }
	int GetY(){
         return m_Y;
    }

	void SetX(int x) {
          m_X = x;
    }
	void SetY(int y) {
          m_Y = y;
    }
	
protected:

	// Screen location 
	int m_X;
	int m_Y;



};
#endif
