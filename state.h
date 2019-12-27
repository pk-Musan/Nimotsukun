#ifndef _STATE_H_
#define _STATE_H_

#include "array2D.h"

class State {
    private:
        enum Object {
            OBJ_SPACE,
            OBJ_WALL,
            OBJ_BLOCK,
            OBJ_MAN,
            OBJ_UNKNOWN
        };
        int mWidth;
        int mHeight;
        Array2D< Object > mObjects;
        Array2D< bool > mGoalFlags;

    private:
        void setSize( const char *stageData, int size );

    public:
        State( const char* stageData, int size );
        void update( char input );
        void draw() const;
        bool hasCleared() const;
};

#endif