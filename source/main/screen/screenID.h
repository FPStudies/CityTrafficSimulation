#ifndef SCREEN_ID_H
#define SCREEN_ID_H

class ScreenID{
    static int ID;

    ScreenID();

public:
    
    ~ScreenID();
    ScreenID(const ScreenID& s);

    bool create();
    ScreenID newID();

    friend bool operator==(const ScreenID& s1, const ScreenID& s2);
    friend bool operator!=(const ScreenID& s1, const ScreenID& s2);
    friend bool operator<(const ScreenID& s1, const ScreenID& s2);
    int operator* ();
};

#endif