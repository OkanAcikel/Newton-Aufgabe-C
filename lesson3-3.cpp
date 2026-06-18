// DiffStrategy.h
#pragma once
#include <array>

/*
 * Differenzierungsstrategie: vorwaertsgerichtete finite Differenzen
 * zur Approximation der Jacobi-Matrix DF(x).
 */
template <typename Problem>
struct DiffStrategy {
    using Vector = typename Problem::VectorType;
    using Matrix = typename Problem::MatrixType;

    Matrix jacobian(const Problem &problem, const Vector &x, double h) const {
        Matrix J{};
        Vector Fx = problem.evaluate(x);

        // fuer jede Komponente x_j eine gestorte Version x + h e_j betrachten
        for (int j = 0; j < Problem::dim; ++j) {
            Vector x_plus = x;
            x_plus[j] += h;

            Vector Fx_plus = problem.evaluate(x_plus);

            // Spalte j der Jacobi-Matrix: (F(x+h e_j) - F(x)) / h
            for (int i = 0; i < Problem::dim; ++i) {
                J[i][j] = (Fx_plus[i] - Fx[i]) / h;
            }
        }
        return J;
    }
};
// LinearSolver.h
#pragma once
#include <array>
#include <stdexcept>

/*
 * Einfacher Gauss-Eliminationssolver fuer kleine 2x2-Systeme.
 * Loest A * s = b.
 */
struct LinearSolver {
    template <typename Matrix, typename Vector>
    Vector solve(Matrix A, Vector b) const {
        const int n = b.size();

        // Gauss-Elimination mit partieller Pivotisierung (hier: klein und explizit)
        for (int k = 0; k < n; ++k) {
            // Pivotpruefung
            if (std::fabs(A[k][k]) < 1e-14) {
                throw std::runtime_error("Pivot zu klein in LinearSolver");
            }
            // Normierung der Pivot-Zeile
            double pivot = A[k][k];
            for (int j = k; j < n; ++j) {
                A[k][j] /= pivot;
            }
            b[k] /= pivot;

            // Elimination in den darunterliegenden Zeilen
            for (int i = k + 1; i < n; ++i) {
                double factor = A[i][k];
                for (int j = k; j < n; ++j) {
                    A[i][j] -= factor * A[k][j];
                }
                b[i] -= factor * b[k];
            }
        }

        // Rueckwaertssubstitution
        Vector x{};
        for (int i = n - 1; i >= 0; --i) {
            x[i] = b[i];
            for (int j = i + 1; j < n; ++j) {
                x[i] -= A[i][j] * x[j];
            }
        }

        return x;
    }
};
