#ifndef _ARRAY2D_H_
#define _ARRAY2D_H_

template< typename T >
class Array2D {
    private:
        T *mArray;
        int mSizeY;
        int mSizeX;

    public:
        Array2D() : mArray( 0 ) {}
        ~Array2D() {
            delete[] mArray;
            mArray = 0;
        }
        void setSize( int sizeY, int sizeX ) {
            mSizeY = sizeY;
            mSizeX = sizeX;
            mArray = new T[ sizeY * sizeX ];
        }
        T& operator() (int indexY, int indexX ) {
            return mArray[ indexY * mSizeX + indexX ];
        }
        const T& operator() ( int indexY, int indexX ) const {
            return mArray[ indexY * mSizeX + indexX ];
        }
};

#endif