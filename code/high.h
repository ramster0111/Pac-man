#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <fstream>
#include <string>
#include <list>

class Highscore
{
public:
    Highscore() {score = 0;}
    virtual ~Highscore() {}

    int score;
    std::string name;

    static std::string sFileName;

    static void createHighScores();
    static void read(std::list<Highscore> & list);
    static void write(std::list<Highscore> & vec);
    void input();
    bool operator < (const Highscore & rhs) const
    { return score < rhs.score; }
    
    void handleHighscore(const Highscore & h);
};


#endif // HIGHSCORE_H
