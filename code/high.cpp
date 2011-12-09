#include "high.h"
#include <iostream>
#include <cassert>

std::string Highscore::sFileName = std::string("Data/highscores.txt");


void Highscore::input(){
score=25000;
name="RAMINDER";
}
void Highscore::read(std::list<Highscore> & list)
{
    std::ifstream file( sFileName.c_str() );

    if(file.is_open() == false)
        assert(!"HighScore File Could not be openened");

    for(int i=0;i<10;i++)
    {
        Highscore hs;
        std::getline(file, hs.name);
        file >> hs.score;
        list.push_back(hs);
        std::getline(file, hs.name); //Blank Line
    }
    file.close();
    //std::cout << "Highscore - read - done" << std::endl;
}

void Highscore::write(std::list<Highscore> & vec)
{
    std::ofstream file( sFileName.c_str());
    if(file.is_open() == false)
        assert(!"HighScore File Could not be openened");

    std::list<Highscore>::iterator it = vec.begin();
    for(int i=0;i<10 || it==vec.end();i++)
    {
        Highscore hs = *it;
        it++;
        file << hs.name << std::endl << hs.score << std::endl;
    }
    file.close();
}
void Highscore::handleHighscore(const Highscore & h)
{
    std::list<Highscore> list;
    Highscore::read(list);
    list.push_back(h);
    list.sort();
    list.reverse();


    Highscore::write(list);

}


