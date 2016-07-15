#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Split convention:
 * bool true  means 'x'
 *      false means 'y'
 */

class Node {
    int x_;
    int y_;

public:
    Node(int x, int y) : x_(x), y_(y) {}

    int x() const {
        return x_;
    }

    int y() const {
        return y_;
    }

    class compare {
        bool split_;
    public:
        compare(bool split) : split_(split) {}

        bool operator() (Node* node1, Node* node2) {
            if (split_) {
                return node1->x() < node2->x();
            } else {
                return node1->y() < node2->y();
            }
        }
    };
};

ostream &operator<<(ostream &out, const Node &node) {
    out << node.x() << " " << node.y() << endl;
    return out;
}

void kd_partition(vector<Node*> nodes, bool split = true) {
    if (nodes.size() == 1) {
        cout << *nodes.at(0);
    }
    if (nodes.size() <= 1) {
        return;
    }

    // Sort based on x/y split
    sort(nodes.begin(), nodes.end(), Node::compare(split));

    // Partition into two sub-arrays
    int median = nodes.size() / 2; // floored
    vector<Node*> partitionLeft, partitionRight;
    copy(nodes.begin(), nodes.begin() + median, back_inserter(partitionLeft));
    copy(nodes.begin() + median + 1, nodes.end(), back_inserter(partitionRight));

    // Pre-order traversal
    cout << *nodes.at(median);
    kd_partition(partitionLeft,  !split);
    kd_partition(partitionRight, !split);
}

int main() {
    int num, x, y;
    vector<Node*> nodes;

    // Read input
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> x >> y;
        nodes.push_back(new Node(x, y));
    }

    kd_partition(nodes);

    return 0;
}
