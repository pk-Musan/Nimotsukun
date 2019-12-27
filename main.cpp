#include <iostream>
#include <fstream>
#include "state.h"

void readFile( char **buffer, int *size, const char *filename);

int main( int argc, char **argv ) {
    const char *filename = "stageData.txt";
    if ( argc >= 2 ){
		filename = argv[ 1 ];
	}
    char *stageData;
    int fileSize;

    readFile( &stageData, &fileSize, filename );
    if ( !stageData ) {
        std::cout << "ステージデータが読み込めません．" << std::endl;
        return 1;
    }

    State *state = new State( stageData, fileSize );

    while ( true ) {
        state -> draw();

        if ( state->hasCleared() ) {
            break;
        }

        std::cout << "w: up, a: left, s: down, d: right." << std::endl;
        std::cout << "command: ";
        char input;
        std::cin >> input;

        state->update( input );
    }

    std::cout << "Congratulation!" << std::endl;

    delete[] stageData;
    stageData = 0;
    delete state;
    state = 0;

    return 0;
}

void readFile( char **buffer, int *size, const char *filename ) {
    std::ifstream in( filename );
    if ( !in ) {
        *buffer = 0;
        *size = 0;
    } else {
        // ストリームの読み込み位置を第二引数から第一引数分移動した位置に変更
        in.seekg( 0, std::ifstream::end );
        // ストリームの読み込み位置がデータの末尾に来ているのでtellg()を使うことでデータのサイズがわかる
        *size = static_cast< int >( in.tellg() );
        // std::cout << *size << std::endl; 
        in.seekg( 0, std::ifstream::beg );
        *buffer = new char[ *size ];
        in.read( *buffer, *size );
    }
}