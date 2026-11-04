#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <windows.h>
using namespace std;

template <class T>
class Vector {
    T* data = nullptr;
    size_t count = 0;
    size_t capacity = 0;

public:
    Vector() = default;

    Vector(size_t n, const T& value) {
        unique_ptr<T[]> temp(new T[n]);
        for (size_t i = 0; i < n; i++) temp[i] = value;
        data = temp.release();
        count = capacity = n;
    }

    ~Vector() { delete[] data; }

    Vector(const Vector& other) {
        unique_ptr<T[]> temp(new T[other.capacity]);
        for (size_t i = 0; i < other.count; i++) temp[i] = other.data[i];
        data = temp.release();
        count = other.count;
        capacity = other.capacity;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(data, temp.data);
            swap(count, temp.count);
            swap(capacity, temp.capacity);
        }
        return *this;
    }

    Vector(Vector&& other) noexcept {
        data = other.data;
        count = other.count;
        capacity = other.capacity;
        other.data = nullptr;
        other.count = other.capacity = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            count = other.count;
            capacity = other.capacity;
            other.data = nullptr;
            other.count = other.capacity = 0;
        }
        return *this;
    }

    void reserve(size_t n) {
        if (n <= capacity) return;
        unique_ptr<T[]> temp(new T[n]);
        for (size_t i = 0; i < count; i++) temp[i] = data[i];
        delete[] data;
        data = temp.release();
        capacity = n;
    }

    void push_back(const T& value) {
        T copy = value;
        if (count == capacity) reserve(capacity == 0 ? 1 : capacity * 2);
        data[count] = copy;
        count++;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    T& operator[](size_t index) {
        if (index >= count) throw out_of_range("Неверный индекс");
        return data[index];
    }

    T* begin() { return data; }
    T* end() { return data ? data + count : nullptr; }
    const T* begin() const { return data; }
    const T* end() const { return data ? data + count : nullptr; }

    void unique() {
        for (size_t i = 0; i < count; i++) {
            size_t j = i + 1;
            while (j < count) {
                if (data[i] == data[j]) {
                    for (size_t k = j; k + 1 < count; k++) data[k] = data[k + 1];
                    count--;
                } else {
                    j++;
                }
            }
        }
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Vector<int> numbers;
    cout << "Массив пуст: " << (numbers.empty() ? "да" : "нет") << '\n';
    numbers.reserve(2);
    for (int x : {4, 2, 4, 3, 2, 1}) numbers.push_back(x);
    cout << "Исходный массив: ";
    for (int x : numbers) cout << x << ' ';
    numbers.unique();
    cout << "\nПосле удаления повторений: ";
    for (int x : numbers) cout << x << ' ';
    cout << "\nРазмер: " << numbers.size() << '\n';

    Vector<int> copy(numbers);
    Vector<int> assigned;
    assigned = copy;
    Vector<int> moved(move(copy));
    Vector<int> movedAgain;
    movedAgain = move(assigned);
    moved[0] = 9;
    cout << "Изменённая копия: " << moved[0] << '\n';
    cout << "Оригинал не изменился: " << numbers[0] << '\n';
    cout << "После перемещения исходные копии пусты: "
         << (copy.empty() && assigned.empty() ? "да" : "нет") << '\n';
    Vector<int> filled(2, 7);
    cout << "Массив с заданным значением: ";
    for (int x : filled) cout << x << ' ';
    try { numbers[4]; }
    catch (const out_of_range&) { cout << "\nНеверный индекс обнаружен\n"; }
}
