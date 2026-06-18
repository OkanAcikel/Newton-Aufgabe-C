// Newton.h
#pragma once

#include <cmath>
#include <iostream>

/*
 * Generische Newton-Klasse fuer nichtlineare Gleichungssysteme F(x) = 0.
 *
 * Template-Parameter:
 *  - Problem: kapselt F(x) und liefert Dimension n und Auswertung F(x)
 *  - DiffStrategy: Strategie zur Berechnung/Approximation der Jacobi-Matrix DF(x)
 *  - LinearSolver: Loeser fuer das lineare Gleichungssystem DF(x^k) * s = F(x^k)
 */
template <typename Problem,
          typename DiffStrategy,
          typename LinearSolver>
class Newton {
public:
    using Vector = typename Problem::VectorType;
    using Matrix = typename Problem::MatrixType;

    /*
     * Konstruktor:
     * Setzt Standardwerte fuer Toleranz, maximale Iterationszahl und
     * Schrittweite zur Jacobi-Approximation.
     */
    Newton(const Problem &problem,
           double tol        = 1e-10,
           int    n_iter_max = 1000,
           double h          = 1e-5)
        : problem_(problem),
          tol_(tol),
          n_iter_max_(n_iter_max),
          h_(h) {}

    /*
     * configure:
     * Erlaubt es, nach der Instanziierung die Einstellungen des Solvers
     * (Toleranz, maximale Iterationszahl, Schrittweite) anzupassen.
     * Dies erfuellt die Forderung der Aufgabenstellung, den Solver
     * flexibel konfigurierbar zu halten.
     */
    void configure(double tol, int n_iter_max, double h) {
        tol_        = tol;
        n_iter_max_ = n_iter_max;
        h_          = h;
    }

    /*
     * solve:
     * Fuehrt das Newton-Verfahren aus.
     *
     * Eingabe:
     *  - x_start: Startvektor x(0)
     * Ausgabe:
     *  - x: approximierte Loesung nach Erreichen des Abbruchkriteriums
     *
     * Variante a/b:
     *  - Abbruch ueber L2-Norm des Residuums ||F(x^k)||_2 < tol
     * Variante c:
     *  - optional zusaetzlicher Abbruch ueber L2-Norm der Korrektur ||s^k||_2
     */
    void solve(const Vector &x_start, Vector &x,
               bool use_correction_norm = false) {
        x = x_start;

        for (int k = 0; k < n_iter_max_; ++k) {
            // 1) Residuum F(x^k) berechnen
            Vector Fx = problem_.evaluate(x);

            // 2) L2-Norm des Residuums als Mass fuer die Gleichungsverletzung
            double res_norm = norm2(Fx);

            // Protokollzeile (optional: in Datei umleiten fuer Plot)
            std::cout << "k = " << k
                      << ", ||F(x)||_2 = " << res_norm << std::endl;

            // Abbruchkriterium ueber Residuum (Aufgabe 3a/b)
            if (res_norm < tol_) {
                break;
            }

            // 3) Jacobi-Matrix DF(x^k) approximieren
            Matrix J = diff_strategy_.jacobian(problem_, x, h_);

            // 4) Newton-Richtung s^k aus linearem Gleichungssystem bestimmen:
            //      DF(x^k) * s^k = F(x^k)
            Vector s = linear_solver_.solve(J, Fx);

            // 5) Korrektur anwenden: x^{k+1} = x^k - s^k
            x = x - s;

            // Optionale zweite Abbruchbedingung fuer Aufgabe 3c:
            // L2-Norm der Newton-Korrektur ||s^k||_2 < tol
            if (use_correction_norm) {
                double dx_norm = norm2(s);
                std::cout << "   ||Delta x||_2 = " << dx_norm << std::endl;
                if (dx_norm < tol_) {
                    break;
                }
            }
        }
    }

private:
    // Hilfsfunktion: euklidische Norm eines Vektors
    double norm2(const Vector &v) const {
        double sum = 0.0;
        for (int i = 0; i < v.size(); ++i) {
            sum += v[i] * v[i];
        }
        return std::sqrt(sum);
    }

    Problem       problem_;        // beschreibt F(x)
    DiffStrategy  diff_strategy_;  // Strategie fuer DF(x)
    LinearSolver  linear_solver_;  // Loeser fuer das lineare Gleichungssystem

    double tol_;                    // Toleranz fuer Abbruch
    int    n_iter_max_;             // maximale Anzahl Iterationen
    double h_;                      // Schrittweite fuer numerische Ableitungen
};
