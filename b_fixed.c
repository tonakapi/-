#include <stdio.h>
#include <string.h> // strcmpを使用するために追加
#include <math.h>

// 1人分の学生データを格納する構造体
struct student_data {
    char family[20];
    char name[20];
    int kokugo_score;
    int suugaku_score;
    int eigo_score;
    int syakai_score;
    int rika_score;
};

int main(int argc, char *argv[]) {
    FILE *in;
    in = fopen("score.dat", "r");
    if (in == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // 20人分の学生データを格納する構造体の配列を宣言
    struct student_data students[20];

    for (int i = 0; i < 20; i++) {
        // 構造体の配列に直接データを読み込む
        if (fscanf(in, " %19s %19s %d %d %d %d %d",
                   students[i].family, students[i].name,
                   &students[i].kokugo_score, &students[i].suugaku_score,
                   &students[i].eigo_score, &students[i].syakai_score,
                   &students[i].rika_score) != 7) {
            printf("Error reading data at line %d\n", i + 1);
            fclose(in);
            return 1;
        }
    }

    // 引数が足りない場合のチェック
    if (argc < 3) {
        printf("入力例: %s [average|top|bottom] [kokugo|suugaku|eigo|syakai|rika|all]\n", argv[0]);
        return 1;
    }

    // strcmpで文字列を比較
    if (strcmp(argv[1], "average") == 0) {
        if (strcmp(argv[2], "kokugo") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].kokugo_score;
            }
            double avg = sum / 20;
            printf("国語の平均点: %.2f点\n", avg);
        } else if (strcmp(argv[2], "suugaku") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].suugaku_score;
            }
            double avg = sum / 20;
            printf("数学の平均点: %.2f点\n", avg);
        } else if (strcmp(argv[2], "eigo") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].eigo_score;
            }
            double avg = sum / 20;
            printf("英語の平均点: %.2f点\n", avg);
        } else if (strcmp(argv[2], "syakai") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].syakai_score;
            }
            double avg = sum / 20;
            printf("社会の平均点: %.2f点\n", avg);
        } else if (strcmp(argv[2], "rika") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].rika_score;
            }
            double avg = sum / 20;
            printf("理科の平均点: %.2f点\n", avg);
        } else if (strcmp(argv[2], "all") == 0) {
            double sum = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].kokugo_score;
                sum += students[i].suugaku_score;
                sum += students[i].eigo_score;
                sum += students[i].syakai_score;
                sum += students[i].rika_score;
            }
            double avg = sum / (20 * 5); // 5教科なので*5
            printf("全教科の平均点: %.2f点\n", avg);
        }
    } else if (strcmp(argv[1], "top") == 0) {
        if (strcmp(argv[2], "kokugo") == 0) {
            int top_score = 0;
            for (int i = 0; i < 20; i++) {
                if (students[i].kokugo_score > top_score) {
                    top_score = students[i].kokugo_score;
                }
            }
            printf("国語の最高点: %d点\n", top_score);
        } else if (strcmp(argv[2], "suugaku") == 0) {
            int top_score = 0;
            for (int i = 0; i < 20; i++) {
                if (students[i].suugaku_score > top_score) {
                    top_score = students[i].suugaku_score;
                }
            }
            printf("数学の最高点: %d点\n", top_score);
        } else if (strcmp(argv[2], "eigo") == 0) {
            int top_score = 0;
            for (int i = 0; i < 20; i++) {
                if (students[i].eigo_score > top_score) {
                    top_score = students[i].eigo_score;
                }
            }
            printf("英語の最高点: %d点\n", top_score);
        } else if (strcmp(argv[2], "syakai") == 0) {
            int top_score = 0;
            for (int i = 0; i < 20; i++) {
                if (students[i].syakai_score > top_score) {
                    top_score = students[i].syakai_score;
                }
            }
            printf("社会の最高点: %d点\n", top_score);
        } else if (strcmp(argv[2], "rika") == 0) {
            int top_score = 0;
            for (int i = 0; i < 20; i++) {
                if (students[i].rika_score > top_score) {
                    top_score = students[i].rika_score;
                }
            }
            printf("理科の最高点: %d点\n", top_score);
        }
    } else if (strcmp(argv[1], "bottom") == 0) {
        if (strcmp(argv[2], "kokugo") == 0) {
            int bottom_score = 100;
            for (int i = 0; i < 20; i++) {
                if (students[i].kokugo_score < bottom_score) {
                    bottom_score = students[i].kokugo_score;
                }
            }
            printf("国語の最低点: %d点\n", bottom_score);
        } else if (strcmp(argv[2], "suugaku") == 0) {
            int bottom_score = 100;
            for (int i = 0; i < 20; i++) {
                if (students[i].suugaku_score < bottom_score) {
                    bottom_score = students[i].suugaku_score;
                }
            }
            printf("数学の最低点: %d点\n", bottom_score);
        } else if (strcmp(argv[2], "eigo") == 0) {
            int bottom_score = 100;
            for (int i = 0; i < 20; i++) {
                if (students[i].eigo_score < bottom_score) {
                    bottom_score = students[i].eigo_score;
                }
            }
            printf("英語の最低点: %d点\n", bottom_score);
        } else if (strcmp(argv[2], "syakai") == 0) {
            int bottom_score = 100;
            for (int i = 0; i < 20; i++) {
                if (students[i].syakai_score < bottom_score) {
                    bottom_score = students[i].syakai_score;
                }
            }
            printf("社会の最低点: %d点\n", bottom_score);
        } else if (strcmp(argv[2], "rika") == 0) {
            int bottom_score = 100;
            for (int i = 0; i < 20; i++) {
                if (students[i].rika_score < bottom_score) {
                    bottom_score = students[i].rika_score;
                }
            }
            printf("理科の最低点: %d点\n", bottom_score);
        }
    }
    else if (strcmp(argv[1], "standard_deviation") == 0) {
        if (strcmp(argv[2], "kokugo") == 0) {
            double sum = 0;
            double sum_sq = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].kokugo_score;
                sum_sq += students[i].kokugo_score * students[i].kokugo_score;
            }
            double avg = sum / 20;
            double variance = (sum_sq / 20) - (avg * avg);
            double stddev = sqrt(variance);
            printf("国語の標準偏差: %.2f点\n", stddev);
        }
        else if (strcmp(argv[2], "suugaku") == 0) {
            double sum = 0;
            double sum_sq = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].suugaku_score;
                sum_sq += students[i].suugaku_score * students[i].suugaku_score;
            }
            double avg = sum / 20;
            double variance = (sum_sq / 20) - (avg * avg);
            double stddev = sqrt(variance);
            printf("数学の標準偏差: %.2f点\n", stddev);
        }
        else if (strcmp(argv[2], "eigo") == 0) {
            double sum = 0;
            double sum_sq = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].eigo_score;
                sum_sq += students[i].eigo_score * students[i].eigo_score;
            }
            double avg = sum / 20;
            double variance = (sum_sq / 20) - (avg * avg);
            double stddev = sqrt(variance);
            printf("英語の標準偏差: %.2f点\n", stddev);
        }
        else if (strcmp(argv[2], "syakai") == 0) {
            double sum = 0;
            double sum_sq = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].syakai_score;
                sum_sq += students[i].syakai_score * students[i].syakai_score;
            }
            double avg = sum / 20;
            double variance = (sum_sq / 20) - (avg * avg);
            double stddev = sqrt(variance);
            printf("社会の標準偏差: %.2f点\n", stddev); 
        }
        else if (strcmp(argv[2], "rika") == 0) {
            double sum = 0;
            double sum_sq = 0;
            for (int i = 0; i < 20; i++) {
                sum += students[i].rika_score;
                sum_sq += students[i].rika_score * students[i].rika_score;
            }
            double avg = sum / 20;
            double variance = (sum_sq / 20) - (avg * avg);
            double stddev = sqrt(variance);
            printf("理科の標準偏差: %.2f点\n", stddev);
        }

    
        
        
    }

    fclose(in);
    return 0;
}
