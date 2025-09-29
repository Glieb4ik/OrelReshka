#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    string name;
    cout << "Введите имя: ";
    cin >> name;

    int money = 0;

    ifstream fin("cash.txt");
    if (fin.is_open()) {
        fin >> money;
        fin.close();
    }
    else {
        cout << "Не удалось открыть файл cash.txt.\n";
    }

    cout << "\nПривет, " << name << "! Баланс: " << money << "$\n";

    while (true) {

        cout << "\nМеню:\n1. Сделать ставку\n2. Выход\nВыбор: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            cout << "Выход из игры.\n";
            break;
        }

        else if (choice == 1) {

            int bet;
            cout << "Сколько ставим? ";
            cin >> bet;

            if (bet <= 0 || bet > money) {
                cout << "Тебе денюжек не хватает.\n";
                continue;
            }

            int side;
            cout << "Выберите сторону: 1 - Орел, 2 - Решка: ";
            cin >> side;

            if (side != 1 && side != 2) {
                cout << "Неверный выбор! Выберите 1 или 2\n";
                continue;
            }

            int flip = rand() % 2 + 1;

            if (flip == 1)
                cout << "Выпал: Орёл";
            else
                cout << "Выпала: Решка";

            if (flip == side) {

                cout << "\033[32m" << "\n\n##     ##   #####   ##     ##      ##      ##   ##   ###    ##" << endl;
                cout << " ##   ##   ##   ##  ##     ##      ##  ##  ##   ##   ####   ##" << endl;
                cout << "  ## ##    ##   ##  ##     ##      ##  ##  ##   ##   ## ##  ##" << endl;
                cout << "   ###     ##   ##  ##     ##      ##  ##  ##   ##   ##  ## ##" << endl;
                cout << "    #      ##   ##  ##     ##      ##  ##  ##   ##   ##    ###" << endl;
                cout << "    #       #####     #####         ##    ##    ##   ##     ##\n\n" << "\033[0m" << endl;

                cout << "Вы выиграли " << bet << "$\n";

                ofstream log("log.txt", ios::app);
                log << "\nПобеда! + " << bet << "$\n";
                log.close();

                money += bet;
            }

            else {
                cout << "\033[31m" << "\n\n##     ##   #####   ##     ##      ##        #####     #####     #####   ###### " << endl;
                cout << " ##   ##   ##   ##  ##     ##      ##       ##   ##   ##   ##   ##   ##  ##     " << endl;
                cout << "  ## ##    ##   ##  ##     ##      ##       ##   ##   ##   ##    ###     #####  " << endl;
                cout << "   ###     ##   ##  ##     ##      ##       ##   ##   ##   ##       ##   ##     " << endl;
                cout << "    #      ##   ##  ##     ##      ##       ##   ##   ##   ##   ##   ##  ##     " << endl;
                cout << "    #       #####     #####        #######   #####     #####     #####   ######\n\n" << "\033[0m" << endl;

                cout << "Вы проиграли " << bet << "$\n";

                ofstream log("log.txt", ios::app);
                log << "\nПроигрыш! - " << bet << "$\n";
                log.close();

                money -= bet;
            }

            cout << "Баланс: " << money << "$\n";

            ofstream fout("cash.txt");
            fout << money;
            fout.close();

            if (money <= 0) {
                cout << "Ты всё слил в казике! Пора на завод!\n";
                break;
            }
        }
        else {
            cout << "Неверный выбор!\n";
        }
    }
    return 0;
}