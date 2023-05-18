using namespace std;
struct puzzle {
    int **matrix;
    int length;
    int fval, hval, gval;
    puzzle *from = nullptr;

    puzzle(int side_length = 3) {
        matrix = new int*[side_length];
        for (int i = 0; i < side_length; i++)
            matrix[i] = new int[side_length];
        length = side_length;
        fval = hval = gval = 0;
    }

    void copy_matrix(int *m) {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < length; j++)
                matrix[i][j] = m[i * length + j];
    }

    void read_matrix() {
        for (int i = 0; i < length; i++) {
            printf("Enter the %dth row: ", i + 1);
            for (int j = 0; j < length; j++) 
                scanf("%d", &matrix[i][j]);
        }
    } 

    void cal_val(int heuristic = 2) { 
    // 0 for uniform cost search, 1 for misplaced tile heuristic, 2 for manhattan distance heuristic
        hval = 0;
        if (heuristic == 1) {
            for (int i = 0; i < length; i++)
                for (int j = 0; j < length; j++) { // compared to goal {{1,2,3.}{..}..}
                    if (i == length - 1 && j == length - 1) continue; // last is empty in goal
                    if (matrix[i][j] != i * length + j + 1) hval++;
                }
        }
        else if (heuristic == 2) {
            for (int i = 0; i < length; i++)
                for (int j = 0; j < length; j++) { // goal_x, goal_y: m[i][j] position in goal
                    if (matrix[i][j] == 0) continue;
                    int goal_x = (matrix[i][j] - 1) / length;
                    int goal_y = matrix[i][j] - goal_x * length - 1;
                    hval += abs(goal_x - i) + abs(goal_y - j);
                }
        }
        fval = hval + gval;
    }

    bool is_goal() {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < length; j++) {
                if (i == length - 1 && j == length - 1) continue;
                if (matrix[i][j] != i * length + j + 1) return false;
            }
        return true;
    }

    puzzle* swap_empty(int x, int y, int px, int py, int h) {
        puzzle* other = new puzzle(length);
        for (int i = 0; i < length; i++)
            for (int j = 0; j < length; j++)
                other->matrix[i][j] = matrix[i][j];
        swap(other->matrix[x][y], other->matrix[px][py]);
        other->gval = gval + 1;
        other->cal_val(h);
        return other;
    }

    void print() {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++)
                printf("%d ", matrix[i][j]);
            puts("");
        }
    }
};

class Less {
public:
    bool operator() (const puzzle* x, const puzzle* y) const {
        return x->fval > y->fval;
    }
};

class Mat_Less {
public:
    bool operator() (const puzzle* x, const puzzle* y) const {
        for (int i = 0; i < x->length; i++)
            for (int j = 0; j < x->length; j++)
                if (x->matrix[i][j] != y->matrix[i][j]) 
                    return x->matrix[i][j] < y->matrix[i][j];
        return false;
    }
};