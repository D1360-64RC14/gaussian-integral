#include <iostream>
#include <cmath>
#include <limits>

// This code calculates the integral of a Gaussian function breaking it in
// various pieces, then adding the area of all pieces together to obtain the
// total area.

const double a_height = 10; // Height
const double b_center = 0;  // Center position
const double c_spread = 2;  // Width (standard derivation)

// The total samples that the function will be divided to calculate the area.
// Bigger values result in better precisions, but long iterations.
const uint32_t sample_count = 100000;

/**
 * Create a Gaussian Function and returns the data above the specified x.
 * https://en.wikipedia.org/wiki/Gaussian_function
 *
 * @param x X of the graph
 * @param a Height
 * @param b Center position
 * @param c Width (standard derivation)
 * @return Value at X
 */
inline double gauss_f(
        const double x,
        const double a,
        const double b,
        const double c
    ) {
    return a * exp(- (pow(x - b, 2) / (2 * c * c)));
}

int main() {
    /*                              |
     *                           :::|:::
     *                         ::   |   ::
     *                       ::     |     ::
     *                     ::       |       ::
     *                    :         |         :
     *                  ::          |          ::
     *                ::            |            ::
     *              ::              |              ::
     *           :::                |                :::
     *  ____:::::___________________|___________________:::::_____
     *    -25  -20  -15  -10  -5    0    5    10   15   20   25
     *      ^------------- function_total_size -------------^
     *      ^----- spread_size -----^
     *      ^- fn_start
     */
    double spread_size = exp(c_spread);
    double fn_start  = b_center - spread_size;

    double function_total_size = spread_size * 2;
    double sample_size = function_total_size / sample_count;

    // Accumulator
    double area = 0;

    for (uint32_t position = 0; position < sample_count; position++) {
        double point = gauss_f(
            fn_start + sample_size * position,
            a_height,
            b_center,
            c_spread
        );

        // The code sum the area of sample_count's squares with height gaussian x (point)
        // and width sample_size.
        area += point * sample_size;
    }

    std::cout.precision(std::numeric_limits<double>::max_digits10);

    std::cout << "The total area of the gaussian function it's about " << area;
    std::cout << " units²" << std::endl;

    return 0;
}
