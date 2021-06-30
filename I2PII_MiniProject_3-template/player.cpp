#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "src/LOG.h"
#define MAXIMUM 0x7fffffff
#define MINIMUM -0x7fffffff
static const int SIZE = 8;
std::ifstream fin;
std::ofstream fout;

int board_importants[8][8] = {
    {3000, -300, 500, 100, 100, 500, -300, 3000},
    {-300, -500, 0, 0, 0, 0, -500, -300},
    {500, 0, 50, 50, 50, 50, 0, 500},
    {100, 0, 50, 100, 100, 50, 0, 100},
    {100, 0, 50, 100, 100, 50, 0, 100},
    {500, 0, 50, 50, 50, 50, 0, 500},
    {-300, -500, 0, 0, 0, 0, -500, -300},
    {3000, -300, 500, 100, 100, 500, -300, 3000},
};

struct Point {
    int x, y;
    Point() : Point(0, 0) {}
    Point(float x, float y) : x(x), y(y) {}
    bool operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Point &rhs) const { return !operator==(rhs); }
    Point operator+(const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};

int MAXDEPTH = 7;
int cur_player;
std::vector<Point> fin_next_valid_spots;
class OthelloBoard {
   public:
    friend std::ostream &operator<<(std::ostream &, const OthelloBoard &);
    OthelloBoard &operator=(const OthelloBoard &rhs) {
        board = rhs.board;
        disc_count = rhs.disc_count;
        return *this;
    }
    const std::array<Point, 8> directions{
        {Point(-1, -1), Point(-1, 0), Point(-1, 1), Point(0, -1),
         /*{0, 0}, */ Point(0, 1), Point(1, -1), Point(1, 0), Point(1, 1)}};
    enum SPOT_STATE { EMPTY = 0,
                      BLACK = 1,
                      WHITE = 2 };

    std::array<std::array<int, SIZE>, SIZE> board;
    std::vector<Point> next_valid_spots;
    std::array<int, 3> disc_count;

    int getHeuristicValue(int player) {
        int h = 0;
        h += disc_count[player] - disc_count[get_next_player(player)];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == player) {
                    h += board_importants[i][j];
                } else if (board[i][j] == get_next_player(player)) {
                    h -= board_importants[i][j];
                }
            }
        }
        return h;
    }

   private:
    int get_next_player(int player) const { return 3 - player; }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const { return board[p.x][p.y]; }
    void set_disc(Point p, int disc) {
        board[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const {
        if (!is_spot_on_board(p)) return false;
        if (get_disc(p) != disc) return false;
        return true;
    }
    bool is_spot_valid(Point center, int player) const {
        if (get_disc(center) != EMPTY) return false;
        for (Point dir : directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(player))) continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, player)) return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center, int player) {
        for (Point dir : directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(player))) continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, player)) {
                    for (Point s : discs) {
                        set_disc(s, player);
                    }
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }

   public:
    OthelloBoard() {
        disc_count = {0, 0, 0};
    }
    OthelloBoard(const OthelloBoard &copied) {
        OthelloBoard();
        operator=(copied);
    }
    std::vector<Point> get_valid_spots(int player) const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (board[i][j] != EMPTY) continue;
                if (is_spot_valid(p, player)) {
                    // LOG() << "NO\n";
                    valid_spots.push_back(p);
                }
            }
        }
        // LOG() << "sp\n";
        // if(valid_spots.empty()) LOG() << "Empty\n";
        return valid_spots;
    }
    void put_disc(Point p, int player) {
        set_disc(p, player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p, player);
    }
    bool is_board_terminate() {
        if (this->disc_count[0] == 0) return true;
        std::vector<Point> me = get_valid_spots(cur_player);
        std::vector<Point> op = get_valid_spots(get_next_player(cur_player));
        if (me.size() != 0) return false;
        if (op.size() != 0) return false;
        return true;
    }
    void init() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++) {
                if(board[i][j] == 0) disc_count[EMPTY]++;
                else if(board[i][j] == 1) disc_count[BLACK]++;
                else if(board[i][j] == 2) disc_count[WHITE]++;
            }
        next_valid_spots = fin_next_valid_spots;
    }
};

std::ostream &operator<<(std::ostream &os, const OthelloBoard &rhs) {
    os << "+---------------+\n";
    for (int i = 0; i < SIZE; i++) {
        os << "|";
        for (int j = 0; j < SIZE; j++) {
            switch (rhs.board[i][j]) {
                case 1:
                    os << "O";
                    break;
                case 2:
                    os << "X";
                    break;
                default:
                    os << " ";
                    break;
            }
            if (j != SIZE - 1) os << " ";
        }
        os << "|\n";
    }
    os << "+---------------+\n";
    return os;
}
OthelloBoard cur_board;

void read_board() {
    fin >> cur_player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> cur_board.board[i][j];
        }
    }
}

void read_valid_spots() {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        fin_next_valid_spots.push_back(Point(x, y));
    }
}

void write_valid_spot(Point p) {
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
}

int alphabeta(OthelloBoard state, int depth, int a, int b, bool maximizingPlayer) {
    // if terminate win or lose
    if (state.is_board_terminate() || depth == 0)
        return state.getHeuristicValue(cur_player);
    OthelloBoard next_state;
    if (maximizingPlayer) {
        int val = MINIMUM;
        // if(next_state.next_valid_spots.empty()) LOG() << "empty\n";
        state.next_valid_spots = state.get_valid_spots(cur_player);
        for (auto it : state.next_valid_spots) {
            next_state = state;
            next_state.put_disc(it, cur_player);
            int next_val = alphabeta(next_state, depth - 1, a, b, false);
            if (next_val > val) {
                val = next_val;
                if (depth == MAXDEPTH) {
                    write_valid_spot(it);
                    LOG() << "Val of " << it.x << " " << it.y << " is " << val << "\n"
                          << next_state;
                }
            }
            a = std::max(a, val);
            if (a >= b) break;
        }
        return val;
    } else {
        int val = MAXIMUM;
        state.next_valid_spots = state.get_valid_spots(3 - cur_player);
        for (auto it : state.next_valid_spots) {
            next_state = state;
            next_state.put_disc(it, 3 - cur_player);
            int next_val = alphabeta(next_state, depth - 1, a, b, true);
            val = std::min(val, next_val);
            b = std::min(b, val);
            if (b <= a) break;
        }
        return val;
    }
}

int main(int, char **argv) {
    fin.open(argv[1]);
    fout.open(argv[2]);
    read_board();
    read_valid_spots();
    write_valid_spot(fin_next_valid_spots[0]);
    cur_board.init();

    LOG::initialize();
    LOG() << "=====================\nCurrent Board:\n"
          << cur_board
          << "\nblack: " << cur_board.disc_count[1] << "\nwhite: " << cur_board.disc_count[2] << "\n";
    for (auto it = fin_next_valid_spots.begin(); it != fin_next_valid_spots.end(); it++) {
        auto nxtit = it;
        LOG() << "(" << (*it).x << ", " << (*it).y << ")" << (++nxtit != fin_next_valid_spots.end() ? ", " : "\n");
    }
    alphabeta(cur_board, MAXDEPTH, MINIMUM, MAXIMUM, true);
    LOG() << "End\n=====================\n";

    fin.close();
    fout.close();
    LOG::terminate();
    return 0;
}
