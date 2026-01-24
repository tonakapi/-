#include <stdio.h>
#include <math.h>
double matrix[3][30];

double average(double mtr[3][30], int i) {
    double sum = 0;
    for (int j = 0; j < 30; j++) {
        sum += mtr[i][j];
    }
    return sum / 30;
}
double standard_deviation(double mtr[3][30], int i, double avg) {
    double sum = 0;
    for (int j = 0; j < 30; j++) {
        sum += (mtr[i][j] - avg) * (mtr[i][j] - avg);
    }
    return sqrt(sum / 30);
}

int main() {
    FILE *in;
    in = fopen("exam.dat", "r");
    if (in == NULL) {
        printf("Error opening file");
        return 1;
    }
    
    for (int j = 0; j < 30; j++) {
      
        if (fscanf(in, "%lf,%lf,%lf", &matrix[0][j], &matrix[1][j], &matrix[2][j]) != 3) {
            printf("Error reading data at line %d\n", j + 1);
            fclose(in);
            return 1;
        }
    }
fclose(in);
char *subject_names[] = {"", "English", "Mathematics"};

    for (int i = 1; i < 3; i++) {
        double avg = average(matrix, i);
        double stddev = standard_deviation(matrix, i, avg);
    
        printf("%-11s: Average = %6.2f, Standard Deviation = %6.2f\n", subject_names[i], avg, stddev);
    }
    return 0;
}