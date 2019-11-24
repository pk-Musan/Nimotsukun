#include <iostream>

const int gStageWidth = 8;
const int gStateHeight = 5;
const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

enum Object {
    OBJ_SPACE,
    OBJ_WALL,
    OBJ_GOAL,
    OBJ_BLOCK,
    OBJ_BLOCK_ON_GOAL,
    OBJ_MAN,
    OBJ_MAN_ON_GOAL,
    OBJ_UNKNOWN
};

void init(Object *stage, int width, int height, const char *stageData) {
    int x = 0, y = 0;
    const char *data = stageData;
    while ( *data != '\0' ) {
        Object t;

        switch (*data) {
            case '#': t = OBJ_WALL; break;
            case ' ': t = OBJ_SPACE; break;
            case 'o': t = OBJ_MAN; break;
            case 'O': t = OBJ_MAN_ON_GOAL; break;
            case '.': t = OBJ_GOAL; break;
            case 'p': t = OBJ_BLOCK; break;
            case 'P': t = OBJ_MAN_ON_GOAL; break;
            case '\n':
                x = 0;
                y++;
                t = OBJ_UNKNOWN;
                break;
            default: t = OBJ_UNKNOWN; break;
        }
        data++;

        if (t != OBJ_UNKNOWN) {
            stage[y*width + x] = t;
            x++;
        }
    }
}

void getInput() {

}

void update() {

}

void draw() {

}

int main() {
    Object *stage = new Object[ gStageWidth * gStateHeight ];
    init(stage, gStageWidth, gStateHeight, gStageData);
    /*
    for (int i = 0; i < gStageWidth*gStateHeight; i++) {
        std::cout << stage[i] << " ";
        if (i % 8 == 7) std::cout << std::endl;
    }
    */
    while (true) {
        getInput();

        update();

        draw();
    }

    return 0;
}