#include <iostream>
#include <cmath>
#include <iomanip>

/*
 * Aufgabe 2:
 * Numerische Umsetzung des 1D-Newtonverfahrens fuer
 *     f(x) = x^2 - 2x - 3
 * in C++.
 *
 * Anforderungen aus dem Aufgabenblatt:
 *  - Programmdatei: A2_2.cpp
 *  - Startwert x(0) wird vom Benutzer eingegeben
 *  - Newton-Iteration in einer while-Schleife
 *  - Abbruchkriterium: |f(x(k))| < tol mit tol = 1E-10
 *  - Ausgabe der Iterationswerte x(k) in Abhaengigkeit von k
 *    zur spaeteren grafischen Darstellung (Plot)
 *  - Ausgabe des Residuums res = |f(x(k))| je Schritt
 */

// Zielfunktion
double f(double x) {
    return x * x - 2.0 * x - 3.0;
}

// Ableitung
double df(double x) {
    return 2.0 * x - 2.0;
}

int main() {
    // Parameter fuer Newton-Verfahren
    const double tol     = 1e-10;  // Toleranz fuer das Residuum |f(x(k))|
    const int    maxIter = 100;    // Sicherheitslimit fuer Iterationsanzahl

    // Einlesen des Startwertes x(0) (z.B. -2 bzw. 42)
    double x;
    std::cout << "Startwert x0 = ";
    std::cin  >> x;

    // Ausgabeformat (viele Nachkommastellen zur Beurteilung der Konvergenz)
    std::cout << std::fixed << std::setprecision(15);

    // Tabellenkopf:
    // k      ... Iterationsindex
    // x_k    ... Naeherungswert der Nullstelle nach k Schritten
    // |f(x_k)|... Betrag des Residuums (Verletzung der Gleichung f(x)=0)
    std::cout << "# k\t x_k\t\t\t |f(x_k)|\n";

    int k = 0;
    while (k < maxIter) {
        double fx  = f(x);              // Funktionswert am aktuellen Punkt
        double res = std::fabs(fx);     // Residuum: Abstand von f(x) zu 0

        // Iterationsdaten ausgeben (geeignet fuer Export in Plot-Programm)
        std::cout << k << "\t" << x << "\t" << res << "\n";

        // Abbruch, falls das Residuum die geforderte Toleranz unterschreitet
        if (res < tol) {
            break;
        }

        double dfx = df(x);             // Ableitung am aktuellen Punkt

        // Schutz gegen Division durch 0 in der Newton-Formel
        if (dfx == 0.0) {
            std::cerr << "Ableitung ist 0 -> Newton-Schritt nicht definiert, Abbruch.\n";
            break;
        }

        // Newton-Schritt:
        // s        = f(x(k)) / f'(x(k))
        // x(k+1)   = x(k) - s
        double s = fx / dfx;
        x = x - s;

        ++k;                            // naechster Iterationsschritt
    }

    // Zusammenfassung nach Ende der Iteration
    std::cout << "\nApprox. Nullstelle: x* = " << x << "\n";
    std::cout << "Anzahl Iterationen: " << k << "\n";

    return 0;
}
