// Problem.h
#pragma once
#include <array>

/*
 * Problemklasse fuer das 2x2-System aus Aufgabe 3a/b:
 *
 *   f1(x0,x1) = x0^2 - 3 x1
 *   f2(x0,x1) = 2 x0^2 - 8 x1^3 + 4
 *
 * Als Vektor- und Matrix-Typ verwenden wir hier einfache std::array-Strukturen.
 */
struct ProblemOriginal {
    static const int dim = 2;

    using VectorType = std::array<double, dim>;
    using MatrixType = std::array<std::array<double, dim>, dim>;

    // Auswertung von F(x) an der Stelle x
    VectorType evaluate(const VectorType &x) const {
        VectorType Fx;
        const double x0 = x[0];
        const double x1 = x[1];

        Fx[0] = x0 * x0 - 3.0 * x1;                // f1
        Fx[1] = 2.0 * x0 * x0 - 8.0 * x1 * x1 * x1 + 4.0; // f2

        return Fx;
    }
};

/*
 * Skalierte Variante fuer Aufgabe 3b:
 *   f1_tilde = 1e6 * f1, f2 bleibt unveraendert.
 */
struct ProblemScaled {
    static const int dim = 2;

    using VectorType = std::array<double, dim>;
    using MatrixType = std::array<std::array<double, dim>, dim>;

    VectorType evaluate(const VectorType &x) const {
        VectorType Fx;
        const double x0 = x[0];
        const double x1 = x[1];

        const double f1 = x0 * x0 - 3.0 * x1;
        const double f2 = 2.0 * x0 * x0 - 8.0 * x1 * x1 * x1 + 4.0;

        Fx[0] = 1e6 * f1;   // Skalierung nur der ersten Gleichung
        Fx[1] = f2;

        return Fx;
    }
};
