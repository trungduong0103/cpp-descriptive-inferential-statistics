#include <iostream>
#include <string>
#include <iomanip>
//#include <random>
#include "../headers/helpers.h"
#include "../headers/file.h"
#include "../headers/descriptive_statistics.h"
#include "../headers/inferential_statistics.h"
#include "../headers/merge_sort.h"

void print_array(double array[], unsigned int array_size) {
    for (double *p = array; p < array + array_size; p++) {
        std::cout << *p << "\n";
    }
}

double sum_of_array_elements(const double array[], unsigned int array_size) {
    double sum = 0;
    for (const double *p = array; p < array + array_size; p++) {
        sum += *p;
    }

    return sum;
}

int main_driver_function(const char *FILE_PATH) {
    // open the file and extract x and y columns to arrays
    if (can_open_file(FILE_PATH)) {
        // calculate array size using csv rows count
        const unsigned int ARRAY_SIZE = calculate_array_size(FILE_PATH);
        double *x_column_array, *y_column_array;
        x_column_array = new (std::nothrow) double[ARRAY_SIZE];
        y_column_array = new (std::nothrow) double[ARRAY_SIZE];
        // if pointer returned by new is a nullptr, memory allocation failed, return 1
        if (x_column_array == nullptr || y_column_array == nullptr) {
            std::cerr << "Error! Memory could not be allocated." << std::endl;
            return 1;
        }
        // validate if data in csv file is in correct format and extract data
        if (validate_and_extract_data_from_column(FILE_PATH, x_column_array, y_column_array)) {
            std::cout.precision(16);
            // inferential statistics
            // b1 covariance
            double cov_x_y = calculate_sample_covariance(x_column_array, y_column_array, ARRAY_SIZE);

            // b2 Pearson correlation coefficient (bivariant correlation or just correlation coefficient)
            double r_x_y = calculate_correlation_coefficient(x_column_array, y_column_array, ARRAY_SIZE);

            // b3 linear regression
            double mean_x = calculate_mean(x_column_array, ARRAY_SIZE);
            double mean_y = calculate_mean(y_column_array, ARRAY_SIZE);

            // sort for descriptive statistics
            merge_sort(x_column_array, 0, ARRAY_SIZE - 1);
            merge_sort(y_column_array, 0, ARRAY_SIZE - 1);

            // descriptive statistics
            // b1 median
            double median_x = calculate_median(x_column_array, ARRAY_SIZE);
            double median_y = calculate_median(y_column_array, ARRAY_SIZE);

            // b2 modes
            std::string modes_x = calculate_modes(x_column_array, ARRAY_SIZE);
            std::string modes_y = calculate_modes(y_column_array, ARRAY_SIZE);

            // b3 variance and standard deviation
            double variance_x = calculate_variance(x_column_array, ARRAY_SIZE);
            double variance_y = calculate_variance(y_column_array, ARRAY_SIZE);
            double stdev_x = calculate_standard_deviation(variance_x);
            double stdev_y = calculate_standard_deviation(variance_y);

            // b4 mean absolute deviation
            double mad_x = calculate_mad(x_column_array, ARRAY_SIZE);
            double mad_y = calculate_mad(y_column_array, ARRAY_SIZE);

            // b5 first quartile
            double q1_x = calculate_first_quantile(x_column_array, ARRAY_SIZE);
            double q1_y = calculate_first_quantile(y_column_array, ARRAY_SIZE);

            // b6 skewness
            double skew_x = calculate_skewness(x_column_array, ARRAY_SIZE);
            double skew_y = calculate_skewness(y_column_array, ARRAY_SIZE);

            // b7 kurtosis
            double kurt_x = calculate_kurtosis(x_column_array, ARRAY_SIZE);
            double kurt_y = calculate_kurtosis(y_column_array, ARRAY_SIZE);

            // display results
            std::cout << "median_x=" << median_x << " - median_y=" << median_y << std::endl;
            std::cout << "mode_x={" << modes_x << "} - mode_y={" << modes_y << "}" << std::endl;
            std::cout << "var_x=" << variance_x << " - var_y=" << variance_y << std::endl;
            std::cout << "stdev_x=" << stdev_x << " - stdev_y=" << stdev_y << std::endl;
            std::cout << "mad_x=" << mad_x << " - mad_y=" << mad_y << std::endl;
            std::cout << "q1_x=" << q1_x << " - q1_y=" << q1_y << std::endl;
            std::cout << "skew_x=" << skew_x << " - skew_y=" << skew_y << std::endl;
            std::cout << "kurt_x=" << kurt_x << " - kurt_y=" << kurt_y << std::endl;
            std::cout << "cov(x_y)=" << cov_x_y << std::endl;
            std::cout << "r(x_y)=" << r_x_y << std::endl;
            display_linear_regression_formula(mean_x, mean_y, stdev_x, stdev_y, r_x_y);
            std::cout << "ASSIGNMENT 1 GROUP 11" << std::endl;
            std::cout << "s3698997, s3698997@rmit.edu.vn, Trung, Duong" << std::endl;
            std::cout << "s3748874, s3748874@rmit.edu.vn, Phat, Tran" << std::endl;
            std::cout << "s3698989, s3698989@rmit.edu.vn, Thuan, Trang" << std::endl;

            delete[] x_column_array;
            delete[] y_column_array;
            x_column_array = nullptr;
            y_column_array = nullptr;

            return 0;
        }
    }

    // return 1 if the file cannot be read or the validate/extract function cannot be completed
    // cerr is not required here because it's already handled in can_open_file()
    return 1;
}