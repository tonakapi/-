#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[]){
    FILE *in;
    in = fopen("exam.dat", "r");
    if (in == NULL) {
        printf("Error opening file");
        return 1;
    }
    struct student_data{
        char family[20];
        char name[20];
        int kokugo_score[20];
        int suugaku_score[20];
        int eigo_score[20];
        int syakai_score[20];
        int rika_score[20];
    };
    struct student_data student;
  for(int i=0; i<20; i++){
    if (fscanf(in, "%19[^,],%19[^,],%d,%d,%d,%d,%d", &student.family[i], &student.name[i], &student.kokugo_score[i], &student.suugaku_score[i], &student.eigo_score[i], &student.syakai_score[i], &student.rika_score[i]) != 7) {
        printf("Error reading data at line %d\n", i + 1);
        fclose(in);
        return 1;
  }  
    }
    if (argv[1] == NULL) {
        printf("No argument provided\n");
        return 1;
    }
    if (argv[1] == average){
        if(argv[2] == kokugo){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.kokugo_score[i];
            }
            double avg = sum / 20;
            printf("国語の平均点: %.2f\n", avg, "点");
        }
        else if(argv[2] == suugaku){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.suugaku_score[i];
            }
            double avg = sum / 20;
            printf("数学の平均点: %.2f\n", avg, "点");
        }
        else if(argv[2] == eigo){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.eigo_score[i];
            }
            double avg = sum / 20;
            printf("英語の平均点: %.2f\n", avg, "点");
        }
        else if(argv[2] == syakai){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.syakai_score[i];
            }
            double avg = sum / 20;
            printf("社会の平均点: %.2f\n", avg, "点");
        }
        else if(argv[2] == rika){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.rika_score[i];
            }
            double avg = sum / 20;
            printf("理科の平均点: %.2f\n", avg, "点");
        }
        else if(argv[2] == all){
            double sum = 0;
            for(int i=0; i<20; i++){
                sum += student.kokugo_score[i];
                sum += student.suugaku_score[i];
                sum += student.eigo_score[i];
                sum += student.syakai_score[i];
                sum += student.rika_score[i];
            }
            double avg = sum / 100;
            printf("全教科の平均点: %.2f\n", avg, "点");
        }
    }
    if(argv[1] == top){
        if(argv[2] == kokugo){
            int top_score = 0;
            for(int i=0; i<20; i++){
                if(student.kokugo_score[i] > top_score){
                    top_score = student.kokugo_score[i];
                }
            }
            printf("国語の最高点: %d\n", top_score, "点");
        }
        else if(argv[2] == suugaku){
            int top_score = 0;
            for(int i=0; i<20; i++){
                if(student.suugaku_score[i] > top_score){
                    top_score = student.suugaku_score[i];
                }
            }
            printf("数学の最高点: %d\n", top_score, "点");
        }
        else if(argv[2] == eigo){
            int top_score = 0;
            for(int i=0; i<20; i++){
                if(student.eigo_score[i] > top_score){
                    top_score = student.eigo_score[i];
                }
            }
            printf("英語の最高点: %d\n", top_score, "点");
        }
        else if(argv[2] == syakai){
            int top_score = 0;
            for(int i=0; i<20; i++){
                if(student.syakai_score[i] > top_score){
                    top_score = student.syakai_score[i];
                }
            }
            printf("社会の最高点: %d\n", top_score, "点");
        }
        else if(argv[2] == rika){
            int top_score = 0;
            for(int i=0; i<20; i++){
                if(student.rika_score[i] > top_score){
                    top_score = student.rika_score[i];
                }
            }
            printf("理科の最高点: %d\n", top_score, "点");
        }
    }
    if(argv[1] == bottom){
        if(argv[2] == kokugo){
            int bottom_score = 100;
            for(int i=0; i<20; i++){
                if(student.kokugo_score[i] < bottom_score){
                    bottom_score = student.kokugo_score[i];
                }
            }
            printf("国語の最低点: %d\n", bottom_score, "点");
        }
        else if(argv[2] == suugaku){
            int bottom_score = 100;
            for(int i=0; i<20; i++){
                if(student.suugaku_score[i] < bottom_score){
                    bottom_score = student.suugaku_score[i];
                }
            }
            printf("数学の最低点: %d\n", bottom_score, "点");
        }
        else if(argv[2] == eigo){
            int bottom_score = 100;
            for(int i=0; i<20; i++){
                if(student.eigo_score[i] < bottom_score){
                    bottom_score = student.eigo_score[i];
                }
            }
            printf("英語の最低点: %d\n", bottom_score, "点");
        }
        else if(argv[2] == syakai){
            int bottom_score = 100;
            for(int i=0; i<20; i++){
                if(student.syakai_score[i] < bottom_score){
                    bottom_score = student.syakai_score[i];
                }
            }
            printf("社会の最低点: %d\n", bottom_score, "点");
        }
        else if(argv[2] == rika){
            int bottom_score = 100;
            for(int i=0; i<20; i++){
                if(student.rika_score[i] < bottom_score){
                    bottom_score = student.rika_score[i];
                }
            }
            printf("理科の最低点: %d\n", bottom_score, "点");
        }
    }
    fclose(in);
    return 0;
}
