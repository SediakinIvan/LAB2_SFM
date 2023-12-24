#include <iostream>
#include <cmath>
#include <fstream>


#define PI           3.14159265358979323846 
//#de//fine mu           4902     // m*c**2

using namespace std;

double newton_method(double M, double e, double epsilon = 1e-6)
{
    double E = M; // Íà÷àëüíîå ïðèáëèæåíèå äëÿ E

    for (int i = 0; i < 40; i++)
    {
        double f = E - e * sin(E) - M; // Çíà÷åíèå ôóíêöèè
        double f_prime = 1 + e * cos(E); // Çíà÷åíèå ïðîèçâîäíîé ôóíêöèè

        E -= f / f_prime; // Âû÷èñëåíèå ñëåäóþùåãî ïðèáëèæåíèÿ äëÿ E

        if (abs(f) < epsilon) // Ïðîâåðêà óñëîâèÿ ñõîäèìîñòè
        {
            break;
        }
    }

    return abs(E);
}

int main() {
    // Ïàðàìåòðû îðáèòû 
    double r_a = 1017 + 1737;                   // êì ðàäèóñ àïîöåíòðà (h+r)
    double r_p = 350 + 1737;                    // êì ðàäèóñ ïåðèöåíòðà 
    double epsilon = 1e-6;

    double GM_m = 4902.80003; //â êì
    double a = (r_a + r_p) / 2;            // áîëüøàÿ ïîëóîñü
    double n = sqrt(GM_m / pow(a, 3));// ñðåäíÿÿ óãëîâàÿ ñêîðîñòü
    double T = 2 * PI / n;

    double e = ((r_a - r_p) / (2 * a));            // ýñöåíòðèñèòåò îðáèòû 0,48793

    // Ñîçäàíèå ôàéëà
    ofstream fout1;
    fout1.open("data_for_graphs.txt");

    // Ïðîâåðêà óñïåøíîãî îòêðûòèÿ ôàéëà
    if (!fout1) {
        cout << "Error opening file.";
        return 0;
    }

    fout1 << "t, c\t";
    fout1 << "M(t), ðàä\t";
    fout1 << "E(t), ðàä\t";
    fout1 << "Theta(t), ðàä\t" << endl;
    fout1 << "r(t), êì\t" << endl;
    fout1 << "V_r(t), ì/ñ\t" << endl;
    fout1 << "V_n(t), ì/ñ\t" << endl;
    fout1 << "V(t), ì/ñ\t" << endl;

    // Âû÷èñëåíèå è çàïèñü çíà÷åíèé àíîìàëèé â ôàéë
    for (int t = 0; t <= T; t++) {
        fout1 << t << "\t";

        double M = n * t; // Ñðåäíÿÿ àíîìàëèÿ
        double E = newton_method(M, e, epsilon); // Ýêñöåíòðè÷åñêàÿ àíîìàëèÿ

        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * (tan(E / 2))) * 2; // Èñòèííàÿ àíîìàëèÿ
        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        double p = a * (1 - e * e);                                       // ôîêàëüíîå ðàññòîÿíèå
        double r = (p / (1 + (e * cos(true_anomaly))));
        double V_n = (sqrt(GM_m / p)) * (1 + e * cos(true_anomaly));
        double V_r = (sqrt(GM_m / p)) * (e * sin(true_anomaly));
        double V = pow(((V_r * V_r) + (V_n * V_n)), 0.5);

        fout1 << M << "\t";
        fout1 << E << "\t";
        fout1 << true_anomaly << "\t";
        fout1 << r << "\t";
        fout1 << V_r << "\t";
        fout1 << V_n << "\t";
        fout1 << V << endl;
    }
    fout1.close();
    cout << "The data was successfully written to the 'data_for_graphs.txt' file.";

    return 0;
}