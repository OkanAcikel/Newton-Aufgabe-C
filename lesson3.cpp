// A2_3.cpp
#include <iostream>
#include "Problem.h"
#include "DiffStrategy.h"
#include "LinearSolver.h"
#include "Newton.h"

int main() {
    using ProblemA = ProblemOriginal;
    using Vec      = ProblemA::VectorType;

    // Globale Solver-Parameter laut Aufgabenstellung
    const double tol        = 1e-10;
    const int    n_iter_max = 1000;
    const double h          = 1e-5;

    // a) Test des Verfahrens fuer Originalsystem mit Startwert (-1000, 6)^T
    {
        ProblemA      problem;
        DiffStrategy<ProblemA> diff;
        LinearSolver  linsolver;

        Newton<ProblemA, DiffStrategy<ProblemA>, LinearSolver>
            newton(problem, tol, n_iter_max, h);

        Vec x_start = { -1000.0, 6.0 };
        Vec x_sol;

        std::cout << "===== Aufgabe 3a: Originalsystem, Residuum als Abbruch =====\n";
        newton.solve(x_start, x_sol, /*use_correction_norm=*/false);
        std::cout << "Loesung (ungefaehr): x = (" << x_sol[0]
                  << ", " << x_sol[1] << ")\n\n";
    }

    // b) Skalierte Funktion f1_tilde = 1e6 * f1
    {
        ProblemScaled problem;
        DiffStrategy<ProblemScaled> diff;
        LinearSolver  linsolver;

        Newton<ProblemScaled, DiffStrategy<ProblemScaled>, LinearSolver>
            newton(problem, tol, n_iter_max, h);

        Vec x_start = { -1000.0, 6.0 };
        Vec x_sol;

        std::cout << "===== Aufgabe 3b: Skalierte Gleichung f1_tilde =====\n";
        newton.solve(x_start, x_sol, /*use_correction_norm=*/false);
        std::cout << "Loesung (ungefaehr): x = (" << x_sol[0]
                  << ", " << x_sol[1] << ")\n\n";

        // Im Report: Vergleiche hier die Anzahl Iterationen und die
        // Entwicklung der Residuen mit Fall a) und kommentiere
        // den Einfluss der Skalierung auf das numerische Verhalten.
    }

    // c) Abbruch ueber L2-Norm der Newton-Korrektur Delta x^k
    {
        ProblemA      problem;
        DiffStrategy<ProblemA> diff;
        LinearSolver  linsolver;

        Newton<ProblemA, DiffStrategy<ProblemA>, LinearSolver>
            newton(problem, tol, n_iter_max, h);

        Vec x_start = { -1000.0, 6.0 };
        Vec x_sol;

        std::cout << "===== Aufgabe 3c: Abbruch ueber ||Delta x||_2 =====\n";
        newton.solve(x_start, x_sol, /*use_correction_norm=*/true);
        std::cout << "Loesung (ungefaehr): x = (" << x_sol[0]
                  << ", " << x_sol[1] << ")\n\n";

        // Im Report: Vergleiche die Anzahl Iterationen und die
        // Newton-Korrekturen mit dem Residuenkriterium aus a).
    }

    // d) Zweite Loesung mit anderem Startwert suchen
    {
        ProblemA      problem;
        DiffStrategy<ProblemA> diff;
        LinearSolver  linsolver;

        Newton<ProblemA, DiffStrategy<ProblemA>, LinearSolver>
            newton(problem, tol, n_iter_max, h);

        Vec x_start = { 0.0, 0.0 };   // Beispiel-Startwert; weitere ausprobieren
        Vec x_sol;

        std::cout << "===== Aufgabe 3d: Zweite Loesung mit anderem Startwert =====\n";
        newton.solve(x_start, x_sol, /*use_correction_norm=*/false);
        std::cout << "Loesung (ungefaehr): x = (" << x_sol[0]
                  << ", " << x_sol[1] << ")\n\n";

        // Im Report: Dokumentiere, welche Startwerte zu welcher
        // Loesung gefuehrt haben, und diskutiere das Thema
        // Konvergenzregionen und Abhaengigkeit vom Startwert.
    }

    return 0;
}
