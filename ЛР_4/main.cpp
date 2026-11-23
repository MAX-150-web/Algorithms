#include <iostream>
#include <windows.h>
using namespace std;

template<class T>
class SinglyLinkedList {
    struct Node {
        T value;
        Node* next;
        Node(T v) : value(v), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;
public:
    ~SinglyLinkedList() { clear(); }
    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    void push_front(T value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
        if (!tail) tail = node;
        count++;
    }
    void push_back(T value) {
        Node* node = new Node(value);
        if (tail) tail->next = node;
        else head = node;
        tail = node;
        count++;
    }
    bool pop_front() {
        if (!head) return false;
        Node* node = head;
        head = head->next;
        delete node;
        if (!head) tail = nullptr;
        count--;
        return true;
    }
    bool pop_back() {
        if (!head) return false;
        if (head == tail) return pop_front();
        Node* node = head;
        while (node->next != tail) node = node->next;
        delete tail;
        tail = node;
        tail->next = nullptr;
        count--;
        return true;
    }
    bool find(T value) const {
        for (Node* node = head; node; node = node->next)
            if (node->value == value) return true;
        return false;
    }
    bool remove(T value) {
        if (!head) return false;
        if (head->value == value) return pop_front();
        Node* node = head;
        while (node->next && node->next->value != value) node = node->next;
        if (!node->next) return false;
        Node* old = node->next;
        node->next = old->next;
        if (old == tail) tail = node;
        delete old;
        count--;
        return true;
    }
    void clear() { while (head) pop_front(); }
    int size() const { return count; }
    bool empty() const { return count == 0; }
    void print() const {
        for (Node* node = head; node; node = node->next) cout << node->value << ' ';
        cout << '\n';
    }
};

template<class T>
class DoublyLinkedList {
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(T v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

    void erase(Node* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;
        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;
        delete node;
        count--;
    }
public:
    class reverse_iterator {
        Node* node;
    public:
        reverse_iterator(Node* p) : node(p) {}
        T& operator*() const { return node->value; }
        reverse_iterator& operator++() { node = node->prev; return *this; }
        bool operator!=(const reverse_iterator& other) const { return node != other.node; }
    };
    DoublyLinkedList() = default;
    ~DoublyLinkedList() { clear(); }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void push_front(T value) {
        Node* node = new Node(value);
        node->next = head;
        if (head) head->prev = node;
        else tail = node;
        head = node;
        count++;
    }
    void push_back(T value) {
        Node* node = new Node(value);
        node->prev = tail;
        if (tail) tail->next = node;
        else head = node;
        tail = node;
        count++;
    }
    bool pop_front() {
        if (!head) return false;
        erase(head);
        return true;
    }
    bool pop_back() {
        if (!tail) return false;
        erase(tail);
        return true;
    }
    bool find(T value) const {
        for (Node* node = head; node; node = node->next)
            if (node->value == value) return true;
        return false;
    }
    bool remove(T value) {
        for (Node* node = head; node; node = node->next)
            if (node->value == value) { erase(node); return true; }
        return false;
    }
    void removeEverySecond() {
        Node* node = head;
        while (node && node->next) {
            Node* next = node->next->next;
            erase(node->next);
            node = next;
        }
    }
    void clear() { while (head) pop_front(); }
    int size() const { return count; }
    bool empty() const { return count == 0; }
    void print() const {
        for (Node* node = head; node; node = node->next) cout << node->value << ' ';
        cout << '\n';
    }
    reverse_iterator rbegin() { return reverse_iterator(tail); }
    reverse_iterator rend() { return reverse_iterator(nullptr); }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SinglyLinkedList<int> one;
    cout << "Односвязный список пуст: " << (one.empty() ? "да" : "нет") << '\n';
    one.push_front(2);
    one.push_front(1);
    one.push_back(3);
    one.push_back(4);
    cout << "Односвязный список: "; one.print();
    cout << "Поиск 3: " << (one.find(3) ? "да" : "нет") << '\n';
    one.remove(3);
    one.pop_front();
    one.pop_back();
    cout << "После удаления 3, первого и последнего: "; one.print();
    one.clear();
    cout << "Размер после очистки: " << one.size() << '\n';
    cout << "Удаление из пустого списка: " << (one.pop_back() ? "да" : "нет") << "\n\n";

    DoublyLinkedList<int> two;
    two.push_front(2);
    two.push_front(1);
    two.push_back(3);
    two.push_back(4);
    two.push_back(5);
    cout << "Двусвязный список: "; two.print();
    cout << "В обратном порядке: ";
    for (auto it = two.rbegin(); it != two.rend(); ++it) cout << *it << ' ';
    cout << "\nПоиск 4: " << (two.find(4) ? "да" : "нет") << '\n';
    two.removeEverySecond();
    cout << "После удаления каждого второго: "; two.print();
    two.remove(3);
    two.pop_front();
    two.pop_back();
    cout << "Размер после удаления остальных: " << two.size() << '\n';
    cout << "Двусвязный список пуст: " << (two.empty() ? "да" : "нет") << '\n';
    cout << "Удаление из пустого списка: " << (two.pop_front() ? "да" : "нет") << '\n';
}
