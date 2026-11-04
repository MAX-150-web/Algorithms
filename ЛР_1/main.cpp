#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

class Soldier {
    string rank, name;
    int experience;
    static int count;
public:
    Soldier(string r, string n, int e) : rank(r), name(n), experience(e) { count++; }
    ~Soldier() { count--; }
    Soldier(const Soldier&) = delete;
    Soldier& operator=(const Soldier&) = delete;
    void show() const { cout << rank << " " << name << ", опыт: " << experience << " лет\n"; }
    static int getCount() { return count; }
};
int Soldier::count = 0;

class Squad {
    vector<Soldier*> soldiers;
public:
    void add(Soldier& soldier) { soldiers.push_back(&soldier); }
    void show() const { for (auto soldier : soldiers) soldier->show(); }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Soldier first("Сержант", "Иван", 5);
    Soldier second("Рядовой", "Алексей", 2);
    cout << "Количество солдат: " << Soldier::getCount() << '\n';
    {
        Squad squad;
        squad.add(first);
        squad.add(second);
        cout << "Состав отряда:\n";
        squad.show();
    }
    cout << "Отряд расформирован. Солдаты остались:\n";
    first.show();
    second.show();
    cout << "Количество солдат: " << Soldier::getCount() << '\n';
}
