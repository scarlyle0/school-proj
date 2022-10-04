#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aerbmvnsh"

double diff(double first, double second);

// getopt code based on assignment PDF
int main(int argc, char **argv) {
    int opt = 0;
    bool all = false;
    bool taylor_e = false;
    bool euler = false;
    bool bbp = false;
    bool madhava = false;
    bool viete = false;
    bool newton = false;
    bool statistics = false;
    bool help = false;

    double math_pi = M_PI;
    // Parse command line and set bools to true if in command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': all = true; break;
        case 'e': taylor_e = true; break;
        case 'r': euler = true; break;
        case 'b': bbp = true; break;
        case 'm': madhava = true; break;
        case 'v': viete = true; break;
        case 'n': newton = true; break;
        case 's': statistics = true; break;
        case 'h': help = true; break;
        }
    }

    // Set all bools to true is -a in command line
    if (all && !help) {
        taylor_e = true;
        euler = true;
        madhava = true;
        bbp = true;
        viete = true;
        newton = true;
    }

    // Print e difference and statistics if needed
    if (taylor_e && !help) {
        double math_e = M_E;
        double my_e = e();
        double e_diff = diff(my_e, math_e);
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", my_e, math_e, e_diff);
        if (statistics) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    // Print euler difference and statistics if needed
    if (euler && !help) {
        double my_rpi = pi_euler();
        double r_diff = diff(my_rpi, math_pi);
        printf(
            "pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_rpi, math_pi, r_diff);
        if (statistics) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    // Print bbp difference and statistics if needed
    if (bbp && !help) {
        double my_bpi = pi_bbp();
        double b_diff = diff(my_bpi, math_pi);
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_bpi, math_pi, b_diff);
        if (statistics) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    // Print madhava difference and statistics if needed
    if (madhava && !help) {
        double my_mpi = pi_madhava();
        double m_diff = diff(my_mpi, math_pi);
        printf(
            "pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_mpi, math_pi, m_diff);
        if (statistics) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    // Print viete difference and statistics if needed
    if (viete && !help) {
        double my_vpi = pi_viete();
        double v_diff = diff(my_vpi, math_pi);
        printf(
            "pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", my_vpi, math_pi, v_diff);
        if (statistics) {
            printf("pi_viete() factors = %d\n", pi_viete_factors());
        }
    }

    // Print newton difference from 0-10 and statistics if needed
    if (newton && !help) {
        double tester = 0;
        double sqrt_ans = 0;
        double newton_ans = 0;
        double n_diff = 0;
        while (tester < 10) {
            sqrt_ans = sqrt(tester);
            newton_ans = sqrt_newton(tester);
            n_diff = diff(newton_ans, sqrt_ans);
            printf("sqrt_newton(%.6lf) = %16.15lf, sqrt(%.6lf) = %16.15lf, diff = %16.15lf\n",
                tester, newton_ans, tester, sqrt_ans, n_diff);
            if (statistics) {
                printf("sqrt_newton iterations = %d\n", sqrt_newton_iters());
            }

            tester += 0.1;
        }
    }

    // Prints help text
    if (help) {
        printf("SYNOPSIS\n   A test harness for the small numerical library.\n\n");
        printf("USAGE\n   ./mathlib-test [-aebmrvnsh]\n\n");
        printf("OPTIONS\n  -a   Runs all tests.\n  -e   Runs e test.\n  -b   Runs BBP pi test.\n  "
               "-m   Runs Madhava pi test.\n  -r   Runs Euler pi test.\n  -v   Runs Viete pi "
               "test.\n  -n   Runs Newton square root tests.\n  -s   Print verbose statistics.\n  "
               "-h   Display program synopsis and usage.\n");
    }
    return 0;
}

// diff finds the difference bewteen two numbers
// Returns the difference between the two numbers
// Accepts first number and second number as doubles
double diff(double first, double second) {
    double diff = 0;
    if (first > second) {
        diff = first - second;
    } else {
        diff = second - first;
    }
    return diff;
}
