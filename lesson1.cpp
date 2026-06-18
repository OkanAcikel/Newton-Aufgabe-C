#include <iostream>
#include <cmath>
#include <iomanip>

/*
 * Aufgabe 1:
 * Newton-Verfahren zur Bestimmung einer Nullstelle von
 *     f(x) = x^2 - 2x - 3
 * mit Startwert x(0) = -2.
 *
 * Gefordert sind die ersten drei Iterationsschritte von Hand.
 * Dieses Programm spiegelt die theoretischen Rechenschritte
 * 1:1 wider und dokumentiert sie.
 */

// Zielfunktion f(x) = x^2 - 2x - 3
double f(double x) {
    return x * x - 2.0 * x - 3.0;
}

// Ableitung f'(x) = 2x - 2
double df(double x) {
    return 2.0 * x - 2.0;
}

int main() {
    // Startwert laut Aufgabenstellung
    double x = -2.0;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Newton-Verfahren fuer f(x) = x^2 - 2x - 3\n";
    std::cout << "Startwert x(0) = " << x << "\n\n";

    // Drei Iterationsschritte: k = 0,1,2 -> wir berechnen x(1), x(2), x(3)
    for (int k = 0; k < 3; ++k) {
        // Funktionswert und Ableitung im aktuellen Punkt x(k)
        double fx  = f(x);
        double dfx = df(x);

        std::cout << "Iteration " << k << ":\n";
        std::cout << "  x(" << k << ")      = " << x   << "\n";
        std::cout << "  f(x(" << k << "))   = " << fx  << "\n";
        std::cout << "  f'(x(" << k << "))  = " << dfx << "\n";

        // Newton-Formel:
        //   x(k+1) = x(k) - f(x(k)) / f'(x(k))
        double x_next = x - fx / dfx;

        std::cout << "  x(" << k+1 << ")    = x(" << k << ") - f(x(" << k
                  << "))/f'(x(" << k << "))\n";
        std::cout << "              = " << x_next << "\n\n";

        // Vorbereitung des nächsten Schritts
        x = x_next;
    }

    return 0;
}
