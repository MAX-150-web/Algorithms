#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <windows.h>
using namespace std;

template<class Tin, class Tout>
class Mapper {
    vector<pair<Tin, Tout>> mappings;
public:
    Mapper() = default;
    void addMapping(const Tin& input, const Tout& output) {
        mappings.push_back({input, output});
    }
    Tout apply(const Tin& input) const {
        for (const auto& mapping : mappings)
            if (mapping.first == input) return mapping.second;
        throw out_of_range("Нет соответствия");
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Mapper<int, string> colors;
    colors.addMapping(1, "красный");
    colors.addMapping(2, "зелёный");
    cout << "Цвет для 1: " << colors.apply(1) << '\n';
    cout << "Цвет для 2: " << colors.apply(2) << '\n';
    try { colors.apply(3); }
    catch (const out_of_range&) { cout << "Для 3 соответствие не найдено\n"; }

    Mapper<string, int> marks;
    marks.addMapping("отлично", 5);
    marks.addMapping("хорошо", 4);
    cout << "Оценка отлично: " << marks.apply("отлично") << '\n';
    cout << "Оценка хорошо: " << marks.apply("хорошо") << '\n';
}
