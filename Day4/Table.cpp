#include "Table.h"

vector<int> Table::loadDrowenNumbers(fstream &file) {
    vector<int> drowenNumbers;
    int element;
    //char trash;
    while (file >> element) {
        drowenNumbers.push_back(element);
        if (file.get() == '\n')
            break;
    }
    return drowenNumbers;
}

Table::table Table::loadTable(fstream& file) {
    int element;
    table t;
    for (int i = 0; i != 5; i++) {
        vector<int> temp;
        for (int i = 0; i != 5; i++) {
            file >> element;
            temp.push_back(element);
        }
        t.push_back(temp);
    }
    return t;
}

void Table::markDrowenNumber(table& t, const int& number) {
    for (auto outIter = t.begin(); outIter != t.cend(); ++outIter) {
        for (auto inIter = outIter->begin(); inIter != outIter->cend(); inIter++) {
            if (*inIter == number) {
                if (*inIter == 0)
                    (*inIter) = 100;
                else
                    (*inIter) *= -1;
                return;
            }
        }
    }
}

int Table::checkBingo(const table& t, int last) {
    int score;
    if ((score = checkLines(t, last)) != 0) {
        return score;
    }
    if ((score = checkColumns(t, last)) != 0) {
        return score;
    }
    else return 0;
}

int Table::returnBingo(const table& t, int last) {
    int sum = 0;
    for (auto outIter = t.cbegin(); outIter != t.cend(); ++outIter) {
        for (auto inIter = outIter->cbegin(); inIter != outIter->cend(); inIter++) {
            if (*inIter > 0 && *inIter != 100) {
                sum += (*inIter);
            }
        }
    }
    return sum;// *last;
}


int Table::checkLines(const table& t, int last) {
    int bingo = 0;
    for (auto outIter = t.cbegin(); outIter != t.cend(); ++outIter) {
        for (auto inIter = outIter->cbegin(); inIter != outIter->cend(); inIter++) {
            if (*inIter < 0) {
                bingo += -1 * (*inIter);
            }
            else if (*inIter == 100);
            else {
                bingo = 0;
                break;
            }
        }
        if (bingo != 0) {
            return returnBingo(t, last);
        }
    }
    return 0;
}

int Table::checkColumns(const table& t, int last) {
    int bingo = 0;
    for (int i = 0; i != 5; i++) {
        for (int j = 0; j != 5; j++) {
            if (t[j][i] < 0) {
                bingo += -t[j][i];
            }
            else if (t[j][i] == 100);
            else {
                bingo = 0;
                break;
            }
        }
        if (bingo != 0)
            return returnBingo(t, last);
    }
    return 0;
}
