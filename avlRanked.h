
#ifndef WET2_AVLRanked_H
#define WET2_AVLRanked_H


#include <iostream>


class AVLRankedNode {
private:
    // Struct of each vertex in the AVL tree
    int score;
    AVLRankedNode *left;
    AVLRankedNode *right;
    AVLRankedNode *parent;
    int factor, height, rank, scoreSum;

    //Methods for the object node
public:
    //Default constructor with no inputs
    AVLRankedNode()
            : score(0), left(NULL), right(NULL), parent(NULL), factor(0),
              height(0), rank(0), scoreSum(0) {}

    AVLRankedNode(int score_, AVLRankedNode *parent)
            : score(score_), left(NULL), right(NULL), parent(parent), factor(0),
              height(0), rank(1), scoreSum(score_) {}

    //Constructor with data and key inputs
    AVLRankedNode(int score_) : score(score_), left(NULL), right(NULL), parent(NULL),
                          rank(1), scoreSum(score_) {}

    //Destructor because must
    ~AVLRankedNode() {
        this->left = NULL;
        this->right = NULL;
    }

    int &getFactor() {
        return this->factor;
    }

    int &getHeight() {
        return this->height;
    }

    int getRank() {
        return this->rank;
    }

    void setRank(int r) {
        this->rank = r;
    }

    int getScoreSum() {
        return this->scoreSum;
    }

    void setScoreSum(int ScoreSum) {
        this->scoreSum = ScoreSum;
    }

    //Method that return the node key
    int getScore() {
        return this->score;
    }


    void setFactor(int factor) {
        this->factor = factor;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setScore(int score_) {
        this->score = score_;
    }

    //Method that return the left son of node
    AVLRankedNode *getLeft() {
        //if (!this->left) return NULL;
        return this->left;
    }

    //Method that return the right son of node
    AVLRankedNode *getRight() {
        //if (!this->right) return NULL;
        return this->right;
    }

    //Method that return the parent of node
    AVLRankedNode *getParent() {
        //if (!this->parent) return NULL;
        return this->parent;
    }

    //Method that set the left son
    void setLeftSon(AVLRankedNode *left) {
        this->left = left;
    }

    //Method that set the right son
    void setRightSon(AVLRankedNode *right) {
        this->right = right;
    }

    //Method that set the parent
    void setParent(AVLRankedNode *parent) {
        this->parent = parent;
    }

};


class AVLRankedTree {
private:
    int size;

    friend class AVLRankedNode;

    AVLRankedNode *root;

    void deleteSubTree(AVLRankedNode *node);

public:
    //Constructor
    AVLRankedTree() : size(0), root(NULL) {};

    ~AVLRankedTree() {
        if (this->root) {
            deleteSubTree(root);
        }
    }

    //Get the root of tree
    AVLRankedNode *getRoot() {
        return this->root;
    };

    //Get the balance factor of vertex
    int balanceFactor(AVLRankedNode *root) const;

    //Get The Height of sub-tree
    int getHeight(AVLRankedNode *node) const;

    //Insert new node to the tree with data and key given
    void insert(int score);


    //Print inorder
    void printInOrder(AVLRankedNode *root) const;

    //Print inorder
    void printInOrder() const;

    int getSize() const {
        return this->size;
    }

    void swap_node(AVLRankedNode *a, AVLRankedNode *b) {
        int score = a->getScore();
        a->setScore(b->getScore());
        b->setScore(score);
    }

    void update(AVLRankedNode *node);

    void updateroot();

    void roll_LR(AVLRankedNode *node1);

    void roll_RR(AVLRankedNode *node);

    void roll_LL(AVLRankedNode *node1);

    void roll_RL(AVLRankedNode *node1);

    void roll(AVLRankedNode *node);

    int getScore(int k);

    int getScore(AVLRankedNode *node, int k);
};

void AVLRankedTree::insert(int score) {
    if (!root) {
        root = new AVLRankedNode(score);
        size++;
        return;
    }

    bool fLeft = true;
    AVLRankedNode *current = root;
    AVLRankedNode *previous = current->getParent();
    while (current) {
        previous = current;
        fLeft = score < current->getScore();
        current = fLeft ? current->getLeft() : current->getRight();
    }
    AVLRankedNode *new_node = new AVLRankedNode(score, previous);
    if (fLeft) {
        previous->setLeftSon(new_node);
    } else {
        previous->setRightSon(new_node);
    }
    update(new_node);
    roll(new_node);
    updateroot();
    size++;
}


//Calculate the heigth fo given node
int AVLRankedTree::getHeight(AVLRankedNode *node) const {
    int height = 0;
    if (node) {
        int left = getHeight(node->getLeft());
        int right = getHeight(node->getRight());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}



//Recursive delete

void AVLRankedTree::deleteSubTree(AVLRankedNode *node) {
    if (node) {
        deleteSubTree(node->getLeft());
        deleteSubTree(node->getRight());
        delete node; // Post Order Deletion
    }
}


//Calculate the height of left sub tree minus height of right sub tree
int AVLRankedTree::balanceFactor(AVLRankedNode *root) const {
    int balance = 0;
    if (root) {
        balance = getHeight(root->getLeft()) - getHeight(root->getRight());
    }
    return balance;
}


void AVLRankedTree::printInOrder() const {
    return this->printInOrder(this->root);
}


void AVLRankedTree::printInOrder(AVLRankedNode *root) const {
    if (root) {
        printInOrder(root->getLeft());  // Left
        std::cout << root->getScore();// Parent
        std::cout << " ";
        printInOrder(root->getRight()); // Right
    }
}


void AVLRankedTree::update(AVLRankedNode *node) {
    while (node) {
        int left_h, right_h, left_r, right_r, left_sum, right_sum;
        if (node->getLeft()) {
            left_h = node->getLeft()->getHeight();
            left_r = node->getLeft()->getRank();
            left_sum = node->getLeft()->getScoreSum();
        } else {
            left_h = -1;
            left_r = 0;
            left_sum = 0;
        }
        if (node->getRight()) {
            right_h = node->getRight()->getHeight();
            right_r = node->getRight()->getRank();
            right_sum = node->getRight()->getScoreSum();
        } else {
            right_h = -1;
            right_r = 0;
            right_sum = 0;
        }
        node->setFactor(left_h - right_h);
        node->setHeight(std::max(left_h, right_h) + 1);
        node->setRank(1 + right_r + left_r);
        node->setScoreSum(node->getScore() + left_sum + right_sum);
        node = node->getParent();
    }
}

void AVLRankedTree::updateroot() {
    if (!this->root) return;
    while (this->root->getParent()) {
        this->root = this->root->getParent();
    }
}


//Roll left
void AVLRankedTree::roll_LL(AVLRankedNode *node1) {
    AVLRankedNode *node = node1->getLeft();
    if (!node) return;
    int height_node1_r = node1->getRight() ? getHeight(node1->getRight()) : -1;
    int height_node_r = node->getRight() ? getHeight(node->getRight()) : -1;
    int height_a_left = node->getLeft() ? getHeight(node->getLeft()) : -1;
    node->setParent(node1->getParent());
    if (node1->getParent() && node1 == node1->getParent()->getLeft())
        node1->getParent()->setLeftSon(node);
    else if (node1->getParent()) {
        node1->getParent()->setRightSon(node);
    }
    node1->setParent(node);
    node1->setLeftSon(node->getRight());
    if (node->getRight()) {
        node->getRight()->setParent(node1);
    }
    node->setRightSon(node1);
    node1->setHeight(std::max(height_node1_r, height_node_r) + 1);
    node1->setFactor(height_node_r - height_node1_r);

    int node1_left_r = 0, node1_right_r = 0, node1_left_sum = 0, node1_right_sum = 0;
    int node_left_r = 0, node_left_sum = 0;
    if (node1->getLeft()) {
        node1_left_r = node1->getLeft()->getRank();
        node1_left_sum = node1->getLeft()->getScoreSum();
    }
    if (node1->getRight()) {
        node1_right_r = node1->getRight()->getRank();
        node1_right_sum = node1->getRight()->getScoreSum();
    }
    if (node->getLeft()) {
        node_left_r = node->getLeft()->getRank();
        node_left_sum = node->getLeft()->getScoreSum();
    }
    node1->setRank(1 + node1_left_r + node1_right_r);
    node1->setScoreSum(node1->getScore() + node1_left_sum + node1_right_sum);
    node->setRank(1 + node_left_r + node1->getRank());
    node->setScoreSum(node->getScore() + node_left_sum + node1->getScoreSum());
    node->setHeight(std::max(node1->getHeight(), height_a_left) + 1);
    node->setFactor(height_a_left - node1->getHeight());
}

void AVLRankedTree::roll_RR(AVLRankedNode *node) {
    AVLRankedNode *node1 = node->getRight();
    if (!node1) {
        return;
    }
    int height_node_l = node->getLeft() ? node->getLeft()->getHeight()
                                        : -1;  //Height
    int height_node1_r = node1->getRight() ? node1->getRight()->getHeight()
                                           : -1;   ////Height
    int height_node1_l = node1->getLeft() ? node1->getLeft()->getHeight()
                                          : -1;   ////Height
    node1->setParent(node->getParent());
    if (node->getParent() && node == node->getParent()->getLeft())
        node->getParent()->setLeftSon(node1);
    else if (node->getParent()) {
        node->getParent()->setRightSon(node1);
    }
    node->setParent(node1);
    node->setRightSon(node1->getLeft());
    if (node1->getLeft()) {
        node1->getLeft()->setParent(node);
    }
    node1->setLeftSon(node);
    node->setHeight(std::max(height_node_l, height_node1_l) + 1);
    node->setFactor(height_node_l - height_node1_l);
    node1->setHeight(std::max(node->getHeight(), height_node1_r) + 1);
    node1->setFactor(node->getHeight() - height_node1_r);
    int node_left_r = 0, node_right_r = 0, node_left_sum = 0, node_right_sum = 0;
    int node1_right_r = 0, node1_right_sum = 0;
    if (node->getLeft()) {
        node_left_r = node->getLeft()->getRank();
        node_left_sum = node->getLeft()->getScoreSum();
    }
    if (node->getRight()) {
        node_right_r = node->getRight()->getRank();
        node_right_sum = node->getRight()->getScoreSum();
    }
    if (node1->getRight()) {
        node1_right_r = node1->getRight()->getRank();
        node1_right_sum = node1->getRight()->getScoreSum();
    }
    node->setRank(1 + node_left_r + node_right_r);
    node->setScoreSum(node->getScore() + node_left_sum + node_right_sum);
    node1->setRank(1 + node->getRank() + node1_right_r);
    node1->setScoreSum(
            node1->getScore() + node->getScoreSum() + node1_right_sum);
}


void AVLRankedTree::roll_LR(AVLRankedNode *node1) {
    AVLRankedNode *node = node1->getLeft();
    roll_RR(node);
    roll_LL(node1);
}

void AVLRankedTree::roll_RL(AVLRankedNode *node1) {
    AVLRankedNode *node = node1->getRight();
    roll_LL(node);
    roll_RR(node1);
}

//Decide how to roll
void AVLRankedTree::roll(AVLRankedNode *node) {
    AVLRankedNode *current = node;
    while (current) {
        int current_factor = current->getFactor();
        if (current_factor >= -1 && current_factor <= 1) {
            current = current->getParent();
            continue;
        }
        int left_factor = current->getLeft() ? current->getLeft()->getFactor()
                                             : -1;
        int right_factor = current->getRight()
                           ? current->getRight()->getFactor() : -1;
        if (current_factor == 2 && left_factor >= 0) {
            roll_LL(current);
        } else if (current_factor == 2 && left_factor == -1) {
            roll_LR(current);
        } else if (current_factor == -2 && right_factor <= 0) {
            roll_RR(current);
        } else if (current_factor == -2 && right_factor == 1) {
            roll_RL(current);
        }
        current = current->getParent();
    }
}

int AVLRankedTree::getScore(int k) {
    if (!this->root)
        return 0;
    return this->getScore(root, k);
}

int AVLRankedTree::getScore(AVLRankedNode *node, int k) {
    if (k <= 0 || !node)
        return 0;
    if (node->getRank() <= k) {
        return node->getScoreSum();
    } else if (node->getRight()) {
        if (node->getRight()->getRank() >= k) {
            return getScore(node->getRight(), k);
        } else {
            return node->getScore() + getScore(node->getRight(), k - 1) +
                   getScore(node->getLeft(),
                            k - node->getRight()->getRank() - 1);
        }
    } else {
        return node->getScore() + getScore(node->getLeft(), k-1);
    }
}


#endif //WET2_AVLRanked_H