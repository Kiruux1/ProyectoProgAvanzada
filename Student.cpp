#include "Student.h"


std::ostream& operator<<(std::ostream& os, const Student& s) {
    os.write(reinterpret_cast<const char*>(&s.serialNo), sizeof(s.serialNo));
    os.write(reinterpret_cast<const char*>(&s.greScore), sizeof(s.greScore));
    os.write(reinterpret_cast<const char*>(&s.toeflScore), sizeof(s.toeflScore));
    os.write(reinterpret_cast<const char*>(&s.universityRating), sizeof(s.universityRating));
    os.write(reinterpret_cast<const char*>(&s.sop), sizeof(s.sop));
    os.write(reinterpret_cast<const char*>(&s.lor), sizeof(s.lor));
    os.write(reinterpret_cast<const char*>(&s.cgpa), sizeof(s.cgpa));
    os.write(reinterpret_cast<const char*>(&s.research), sizeof(s.research));
    os.write(reinterpret_cast<const char*>(&s.chanceOfAdmit), sizeof(s.chanceOfAdmit));
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    is.read(reinterpret_cast<char*>(&s.serialNo), sizeof(s.serialNo));
    is.read(reinterpret_cast<char*>(&s.greScore), sizeof(s.greScore));
    is.read(reinterpret_cast<char*>(&s.toeflScore), sizeof(s.toeflScore));
    is.read(reinterpret_cast<char*>(&s.universityRating), sizeof(s.universityRating));
    is.read(reinterpret_cast<char*>(&s.sop), sizeof(s.sop));
    is.read(reinterpret_cast<char*>(&s.lor), sizeof(s.lor));
    is.read(reinterpret_cast<char*>(&s.cgpa), sizeof(s.cgpa));
    is.read(reinterpret_cast<char*>(&s.research), sizeof(s.research));
    is.read(reinterpret_cast<char*>(&s.chanceOfAdmit), sizeof(s.chanceOfAdmit));
    return is;
}