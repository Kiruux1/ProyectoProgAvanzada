#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <fstream> 

struct Student {
    int serialNo;
    int greScore;
    int toeflScore;
    int universityRating;
    float sop;
    float lor;
    float cgpa;
    int research;
    float chanceOfAdmit;


    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

std::ostream& operator<<(std::ostream& os, const Student& s);

std::istream& operator>>(std::istream& is, Student& s);

#endif 