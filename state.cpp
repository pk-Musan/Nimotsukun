#include "state.h"
#include <iostream>
#include <algorithm>

State::State(const char* stageData, int size) {
    // stageDataからmHeight, mWidthが決まる
    setSize( stageData, size );

    // ステージ上のオブジェクトとゴールフラグの領域確保
    mObjects.setSize( mHeight, mWidth );
    mGoalFlags.setSize( mHeight, mWidth );

    // ステージ上のオブジェクトとゴールフラグを初期化
    for ( int y = 0; y < mHeight; y++ ) {
        for ( int x = 0; x < mWidth; x++ ) {
            mObjects( y, x ) = OBJ_WALL;
            mGoalFlags( y, x ) = false;
        }
    }

    int y = 0;
    int x = 0;
    for ( int i = 0; i < size; i++ ) {
        Object t;
        bool goalFlag = false;

        // stageDataから一マスごとの状態をt, goalFlagに格納
        switch ( stageData[i] ) {
            case '#': t = OBJ_WALL; break;
            case ' ': t = OBJ_SPACE; break;
            case 'o': t = OBJ_BLOCK; break;
            case 'O': t = OBJ_BLOCK; goalFlag = true; break;
            case '.': t = OBJ_SPACE; goalFlag = true; break;
            case 'p': t = OBJ_MAN; break;
            case 'P': t = OBJ_MAN; goalFlag = true; break;
            case '\n': x = 0; y++; t = OBJ_UNKNOWN; break;

            default: t = OBJ_UNKNOWN; break;
        }

        // t, goalFlagからステージ上のオブジェクトとゴールフラグの情報を上書き
        if ( t != OBJ_UNKNOWN ) {
            mObjects( y, x ) = t;
            mGoalFlags( y, x ) = goalFlag;
            x++;
        }
    }
}

void State::update( char input ) {
    int dy = 0;
    int dx = 0;

    // inputから進む方向を確定
    switch ( input ) {
        case 'w': dy = -1; break;
        case 'a': dx = 1; break;
        case 's': dy = 1; break;
        case 'd': dx = -1; break;
    }

    // プレイヤーの現在地を特定
    int y, x;
    bool found_man = false;
    for ( y = 0; y < mHeight; y++ ) {
        for ( x = 0; x < mWidth; x++ ) {
            if ( mObjects( y, x ) == OBJ_MAN ) {
                found_man = true;
                break;
            }
        }
        // 見つかっていれば抜ける
        if ( found_man ) break;
    }

    // 移動先の座標を確定
    int ty = y + dy;
    int tx = x + dx;

    // 移動先がステージの領域外でないかチェック
    if ( ty < 0 || ty >= mHeight || tx < 0 || tx >= mWidth ) {
        return;
    }

    // 移動先が空白またはゴールの場合，プレイヤーを移動
    if ( mObjects( ty, tx ) == OBJ_SPACE ) {
        mObjects( ty, tx ) = OBJ_MAN;
        mObjects( y, x ) = OBJ_SPACE;
    // 移動先がブロックの場合，さらに次のマスが空白またはゴールであれば移動
    } else if ( mObjects( ty, tx ) == OBJ_BLOCK ) {
        // ブロックのさらに次のマス
        int ty2 = ty + dy;
        int tx2 = tx + dx;

        // ブロックの次のマスがステージの領域内かチェック
        if ( ty2 < 0 || ty2 >= mHeight || tx2 < 0 || tx2 >= mWidth ) {
            return;
        }

        // ブロックの次のマスが空白またはゴールなので移動
        if ( mObjects( ty2, tx2 ) == OBJ_SPACE ) {
            mObjects( ty2, tx2 ) = OBJ_BLOCK;
            mObjects( ty, tx ) = OBJ_MAN;
            mObjects( y, x ) = OBJ_SPACE;
        }
    }
}

void State::draw() const {
    for ( int y = 0; y < mHeight; y++ ) {
        for ( int x = 0; x < mWidth; x++ ) {
            Object t = mObjects( y, x );
            bool goalFlag = mGoalFlags( y, x );
            if ( goalFlag ) {
                switch ( t ) {
                    case OBJ_SPACE: std::cout << '.'; break;
                    case OBJ_WALL: std::cout << '#'; break;
                    case OBJ_BLOCK: std::cout << 'O'; break;
                    case OBJ_MAN: std::cout << 'P'; break;
                }
            } else {
                switch ( t ) {
                    case OBJ_SPACE: std::cout << " "; break;
                    case OBJ_WALL: std::cout << '#'; break;
                    case OBJ_BLOCK: std::cout << 'o'; break;
                    case OBJ_MAN: std::cout << 'p'; break;
                }
            }
        }
        std::cout << std::endl;
    }
}

bool State::hasCleared() const {
    for ( int y = 0; y < mHeight; y++ ) {
        for ( int x = 0; x < mWidth; x++ ) {
            if ( mObjects( y,x ) == OBJ_BLOCK && mGoalFlags( y, x ) == false ) {
                return false;
            }
        }
    }
    return true;
}

void State::setSize( const char* stageData, int size ) {
    mWidth = mHeight = 0;

    int y = 0;
    int x = 0;

    for ( int i = 0; i < size; i++ ) {
        switch ( stageData[i] ) {
            case '#': case ' ': case 'o': case 'O':
            case '.': case 'p': case 'P':
                x++;
                break;
            
            case '\n':
                y++;
                mWidth = std::max(x, mWidth);
                mHeight = std::max(y, mHeight);
                x = 0;
                break;
        }
    }
}