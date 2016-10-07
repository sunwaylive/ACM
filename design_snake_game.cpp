/*
题目描述

实现一个贪吃蛇游戏，贪吃蛇一开始在［0，0］位置且长度为1。每当贪吃蛇吃到食物，长度和获得的分数都增加一。对于每次move输出move之后的分数。如果贪吃蛇走出边界或和自己的身体相撞则游戏结束，输出－1。下面地图中 S是Snake， F是food.
给出一个地图长为3，宽为2，food的位置是[1,2],[0,1]
一开始snake出现在[0,0]，food出现在[1,2]
以下用S表示snake，用F表示food
|S| | |
| | |F|

snake.move("R"); -> Returns 0
| |S| |
| | |F|

snake.move("D"); -> Returns 0
| | | |
| |S|F|

snake.move("R"); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )
| |F| |
| |S|S|

snake.move("U"); -> Returns 1
| |F|S|
| | |S|

snake.move("L"); -> Returns 2 (Snake eats the second food)
| |S|S|
| | |S|

snake.move("U"); -> Returns -1 (Game over because snake collides with)

算法分析

本题是个看似复杂的模拟题，需要我们实现两个函数：一是贪吃蛇游戏的构造函数，二是每一次的move并返回当前分数。
对于模拟题而言，一般有以下两个特点
算法简单，只需模拟给定的操作。比如本题中就是模拟贪吃蛇的移动，纪录移动后贪吃蛇的身体的位置。
代码量大（相对），细节较多。
以本题为例，讲讲模拟题的思路。
1. 读题，跟着样例梳理整个操作。本题中，我们首先按照输入的指定方向移动一下贪吃蛇（同时判断贪吃蛇有没有出界或者撞到自己），然后我们看看有没有吃到食物：对于吃到和不吃到两种情况调整贪吃蛇的长度。
2. 选取合适的数据结构保存数据。本题中我们需要保存贪吃蛇的身体位置，同时贪吃蛇的头和尾巴的位置都有可能发生变化，因此我们需要用一个两端都能操作的队列（Deque）来保存贪吃蛇。另外，为了O(1)判断贪吃蛇是否撞到自己，我们用一个HashSet纪录贪吃蛇的身体。
3. 细节与边界情况处理。本题中，有一种情况是贪吃蛇下一次move恰好移动到了尾巴位置，此时我们不应该认为贪吃蛇发生了相撞，因为头和尾巴是一起移动的（前提是它没吃到东西）。

最后我们来分析一下时空复杂度，Deque操作O(1)，判断游戏结束也是O(1)，总的move时间复杂度O(1)。空间复杂度，Deque大小为move的次数（用循环队列可以优化到width*height），HashSet最大为width*height。
*/

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct Position {
    int x, y;
    Position(int x_, int y_) : x(x_), y(y_) {}
};

class SnakeGame {
public:
    SnakeGame(int width, int height, vector<Position> food_list)
              : m_width(width), m_height(height), m_food_list(food_list),
                m_is_game_over(false), m_food_get(0) {
        m_snake.push_front(Position(0, 0));
        // snake first appears at (0, 0)
        m_snake_used_map.push_back(0);

        //if the food appears at start pos
        if (m_food_list[m_food_get].x == 0 && m_food_list[m_food_get].y == 0) {
            m_food_get++;
        }

        cout << m_food_list.size() <<endl;
    }

    int Move(char direction) {
        if (m_is_game_over) {
            return -1;
        }

        int inc_x = 0, inc_y = 0;
        switch (direction) {
            case 'U' : inc_x = -1; inc_y = 0; break;
            case 'D' : inc_x = 1;  inc_y = 0; break;
            case 'L' : inc_x = 0; inc_y = -1; break;
            case 'R' : inc_x = 0; inc_y = 1; break;
            default : break;
        }

        Position head = m_snake.front();
        Position next_pos(head.x + inc_x, head.y + inc_y);
        cout<< "pos: " << next_pos.x << " " << next_pos.y <<endl;
        if (next_pos.x >= 0 && next_pos.x < m_width && next_pos.y >= 0 && next_pos.y < m_height) {
            //check collision
            vector<int>::iterator iter = std::find(m_snake_used_map.begin(), m_snake_used_map.end(), next_pos.x * m_width + next_pos.y);
            if (iter != m_snake_used_map.end()) {
                m_is_game_over = true;
                cout << "collide" <<endl;
                return -1;
            }

            m_snake.push_front(next_pos);
            //check whether we have eat food
            //food appears one by one, you must eat the previous one, the next can appear
            if (next_pos.x == m_food_list[m_food_get].x && next_pos.y == m_food_list[m_food_get].y) {
                m_food_get++;
                m_snake_used_map.push_back(next_pos.x * m_width + next_pos.y);
            } else {
                m_snake_used_map.push_back(next_pos.x * m_width + next_pos.y);
                m_snake_used_map.erase(m_snake_used_map.begin());
                m_snake.pop_back();
            }

            return m_food_get;
        } else {
            m_is_game_over = true;
            return -1;
        }

        return -1;
    }

private:
    bool m_is_game_over;
    int m_width, m_height;
    int m_food_get;
    vector<int> m_snake_used_map;
    vector<Position> m_food_list;
    deque<Position> m_snake;
};

int main() {
    vector<Position> food_list;
    food_list.push_back(Position(1, 2));
    food_list.push_back(Position(0, 1));

    SnakeGame sg(2, 3, food_list);
    cout << sg.Move('R') << endl;
    cout << sg.Move('D') << endl;
    cout << sg.Move('R') << endl;
    cout << sg.Move('U') << endl;
    cout << sg.Move('L') << endl;
    cout << sg.Move('U') << endl;
    return 0;
}

