#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>

using namespace std;

template <class T>
struct Min {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template <class T>
struct Max {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

template <class T>
class Node {
public:
    T val;
    Node* left;
    Node* right;
    Node* parent;

    Node(T value) : val(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <class T, class U>
class CHeap {
public:
    U comp;
    Node<T>* root;

    CHeap() : root(nullptr) {}

    Node<T>* findpush(Node<T>* root) {
        if (!root) return nullptr;
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();
            if (!current->left || !current->right) {
                return current;
            }
            q.push(current->left);
            if (current->right) {
                q.push(current->right);
            }
        }
        return nullptr;
    }

    void Check(Node<T>*& a, Node<T>*& b) {
        if (!comp(a->val, b->val)) {
            T tmp = a->val;
            a->val = b->val;
            b->val = tmp;
        }
    }

    void push(T v) {
        Node<T>* newNode = new Node<T>(v);
        if (!root) {
            root = newNode;
            return;
        }
        Node<T>* parent = findpush(root);
        if (!parent->left) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        newNode->parent = parent;
        Node<T>* p = newNode;
        while (p != root) {
            Check(p->parent, p);
            p = p->parent;
        }
    }

    Node<T>* findLastNode(Node<T>* root) {
        if (!root) return nullptr;

        queue<Node<T>*> q;
        q.push(root);
        Node<T>* lastNode = nullptr;

        while (!q.empty()) {
            lastNode = q.front();
            q.pop();

            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }
        return lastNode;
    }

    void pop() {
        if (!root) return;

        Node<T>* lastNode = findLastNode(root);

        if (lastNode == root) {
            delete root;
            root = nullptr;
            return;
        }

        root->val = lastNode->val;

        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        }
        else {
            lastNode->parent->right = nullptr;
        }
        delete lastNode;

        Node<T>* current = root;

        while (current) {
            Node<T>* nextNode = nullptr;

            if (current->left && current->right) {
                nextNode = comp(current->left->val, current->right->val) ? current->left : current->right;
            }
            else if (current->left) {
                nextNode = current->left;
            }
            else if (current->right) {
                nextNode = current->right;
            }

            if (nextNode && !comp(current->val, nextNode->val)) {
                Check(current, nextNode);
                current = nextNode;
            }
            else {
                break;
            }
        }
    }

    T Top() {
        if (!root) {
            cout << "No hay raiz" << endl;
        }
        return root->val;
    }
};

template <class T>
void drawTree(sf::RenderWindow& window, Node<T>* node, float x, float y, float xOffset, float level, const sf::Font& font) {
    if (!node) return;

    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(x, y);

    window.draw(circle);

    sf::Text text(std::to_string(node->val), font, 20);
    text.setPosition(x + 8, y + 5);
    window.draw(text);

    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - xOffset + 20, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - xOffset, y + 80, xOffset / 2, level + 1, font);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + xOffset + 20, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + xOffset, y + 80, xOffset / 2, level + 1, font);
    }
}

int main() {
    CHeap<int, Max<int>> tree;

    sf::Font font;
    if (!font.loadFromFile("C:/Users/Usuario/Downloads/Arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(1280, 720), "CHeap");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    int value;
                    std::cout << "Enter value to push: ";
                    std::cin >> value;
                    tree.push(value);
                }
                if (event.key.code == sf::Keyboard::R) {
                    cout << "Deleting root " << tree.Top() << endl;
                    tree.pop();
                }
            }
        }

        window.clear(sf::Color::White);

        if (tree.root) {
            drawTree(window, tree.root, 640, 50, 300, 1, font);
        }

        window.display();
    }
    return 0;
}
