// https://pl.spoj.com/problems/JPESEL/
// Program sprawdzajacy poprawnosc peselu w C++ i Assembler
// 
// Dzialanie:
// 1. Mnozenie cyfr przez odpowiednie iloczyny
// 2. Sumowanie iloczynow
// 3. Sprawdzenie sumy
//    Ostatnia liczba sumy musi byc rowna zero.

#include <iostream>

using namespace std;

int main()
{
    cout << "Podaj pesel: ";
        
    // Get input
    unsigned char pesel_input[11];
    for (int i = 0; i < 11; i++) {
        cin >> pesel_input[i];
    }

    // Convert to short
    unsigned short pesel[11];
    for (int i = 0; i < 11; i++) {
        pesel[i] = pesel_input[i] - '0';
    }
        
    int sum = 0;
    sum += pesel[0];
    sum += pesel[1] * 3;
    sum += pesel[2] * 7;
    sum += pesel[3] * 9;
    sum += pesel[4];
    sum += pesel[5] * 3;
    sum += pesel[6] * 7;
    sum += pesel[7] * 9;
    sum += pesel[8];
    sum += pesel[9] * 3;
    sum += pesel[10];
        
    cout << "C++ suma peselu: " << sum << endl;

    if (sum < 0) {
        cout << "Niepoprawny pesel" << endl;
    }

    if (sum % 10 == 0) {
        cout << "C++ - Pesel poprawny" << endl;
    }
    else {
        cout << "C++ - Pesel niepoprawny" << endl;
    }

    unsigned short suma = 0;
    unsigned char wynik = 0;
    _asm {
        MOV Ax, 0
        MOV Bx, 0
        MOV Cx, 0

        MOV Ax, [pesel]
        MOV Cx, 1
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 2]
        MOV Cx, 3
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 4]
        MOV Cx, 7
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 6]
        MOV Cx, 9
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 8]
        MOV Cx, 1
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 10]
        MOV Cx, 3
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 12]
        MOV Cx, 7
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 14]
        MOV Cx, 9
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 16]
        MOV Cx, 1
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 18]
        MOV Cx, 3
        MUL Cx
        ADD Bx, Ax

        MOV Ax, [pesel + 20]
        MOV Cx, 1
        MUL Cx
        ADD Bx, Ax

        MOV suma, Bx

        AND Bx, 1
        CMP Bx, 0
        jz dobrypesel
        MOV wynik, 0
        JMP koniec

        dobrypesel:
        MOV wynik, 1

        koniec:
    }

    cout << "Assembler suma peselu: " << suma << endl;

    if (wynik) {
        cout << "Assembler - Pesel poprawny" << endl;
    }
    else {
        cout << "Assembler - Pesel niepoprawny" << endl;
    }

    return 0;
}