#include <bits/stdc++.h>
#include <chrono>

using namespace std;

#define N 3

struct Node {
    Node *parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

int showPuzzle(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

Node *newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node *parent) {
    Node *node = new Node;
    node->parent = parent;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            node->mat[i][j] = mat[i][j];
        }
    }

    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

int CostCalculation(int mat[N][N], int final[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] != final[i][j]) {
                count++;
            }
    return count;
}

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};
int checkLimit(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void DisplayPuzzle(Node *root) {
    if (root == NULL)
        return;
    DisplayPuzzle(root->parent);
    showPuzzle(root->mat);
    printf("\n");
}

struct comp {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

void solve(int initial[N][N], int x, int y, int final[N][N]) {
    priority_queue<Node *, vector<Node *>, comp> pq;

    unordered_set<string> visited; // Keep track of visited states

    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = CostCalculation(initial, final);
    pq.push(root);

    while (!pq.empty()) {
        Node *min = pq.top();
        pq.pop();

        if (min->cost == 0) {
            DisplayPuzzle(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (checkLimit(min->x + row[i], min->y + col[i])) {
                Node *child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                child->cost = CostCalculation(child->mat, final);
                pq.push(child);
            }
        }
    }
}

int main() {

    int initial[N][N] =
            {
                    {1, 2, 3},
                    {0, 6, 5},
                    {7, 8, 4}
            };

    int final[N][N] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8}
    };
    
    int x = 1, y = 0;

    solve(initial, x, y, final);

    return 0;
}
