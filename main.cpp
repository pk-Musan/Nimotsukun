#include <iostream>
#include <fstream>

int gStageWidth = 0;
int gStateHeight = 0;
std::string gStageData;
const std::string gStageDataPath = "stageData.txt";

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

void readFileImage(const std::string dataPath) {
    std::ifstream inputFile(dataPath, std::ifstream::binary);

    std::string str;
    getline(inputFile, str);
    if ( !str.empty() ) gStageWidth = str.length();

    inputFile.seekg(0, std::ifstream::beg);
    while (getline(inputFile, str)) {
        gStageData += str;
        gStateHeight++;
    }
}

void init(Object *state, const std::string stageData) {
    int i = 0;
    while (stageData[i] != '\0') {
        Object t;

        switch (stageData[i]) {
            case '#': t = OBJ_WALL; break;
            case ' ': t = OBJ_SPACE; break;
            case 'o': t = OBJ_BLOCK; break;
            case 'O': t = OBJ_BLOCK_ON_GOAL; break;
            case '.': t = OBJ_GOAL; break;
            case 'p': t = OBJ_MAN; break;
            case 'P': t = OBJ_MAN_ON_GOAL; break;
            default: t = OBJ_UNKNOWN; break;
        }

        if (t != OBJ_UNKNOWN) {
            state[i] = t;
        }
        i++;
    }
}

char getInput() {
    std::cout
        << "a: left, d: right, w: up, s: down."
        << std::endl
        << "press your command: ";
    std::string input;
    getline(std::cin, input);

    if (input.length() != 1) return '\0';
    else return *input.c_str();
}

void update(Object *state, char input, int width, int height) {
    int dx = 0;
    int dy = 0;
    int x, y;

    switch (input) {
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        default: break;
    }

    for (int i = 0; i < width*height; i++) {
        if (state[i] == OBJ_MAN || state[i] == OBJ_MAN_ON_GOAL) {
            x = i % width;
            y = i / width;
            break;
        }
    }

    int tx = x + dx;
    int ty = y + dy;

    if (tx <= 0 || ty <= 0 || tx >= width || ty >= height) return;

    int p = y*width + x;    // stateにおける現在地
    int tp = ty*width + tx; // stateにおける移動後の位置

    // 移動先が空白か目的地の時
    // 移動先がブロックの場合は動けない
    if (state[tp] == OBJ_SPACE || state[tp] == OBJ_GOAL) {
        state[tp] = (state[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
        state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
    } else if (state[tp] == OBJ_BLOCK || state[tp] == OBJ_BLOCK_ON_GOAL) {
        int tx_b = tx + dx;
        int ty_b = ty + dy;

        if (tx_b <= 0 || ty_b <= 0 || tx_b >= width || ty_b >= height) return;
        int tp_b = ty_b*width + tx_b;

        if (state[tp_b] == OBJ_SPACE || state[tp_b] == OBJ_GOAL) {
            state[tp_b] = (state[tp_b] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
            state[tp] = (state[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
            state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
        }
    }
}

bool checkClear(Object *state, int width, int height) {
    for (int i = 0; i < width*height; i++) {
        if (state[i] == OBJ_BLOCK) return false;
    }

    return true;
}

void draw(Object *state, int width, int height) {
    const char font[] = {' ', '#', '.', 'o', 'O', 'p', 'P'};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Object o = state[y*width + x];
            std::cout << font[o];
        }
        std::cout << std::endl;
    }
}

int main() {
    readFileImage(gStageDataPath);
    
    Object *state = new Object[ gStageWidth * gStateHeight ];
    init(state, gStageData);
    draw(state, gStageWidth, gStateHeight);

    while (true) {
        if (checkClear(state, gStageWidth, gStateHeight)) break;
        
        char input = getInput();

        update(state, input, gStageWidth, gStateHeight);

        draw(state, gStageWidth, gStateHeight);
    }

    delete[] state;
    
    return 0;
}