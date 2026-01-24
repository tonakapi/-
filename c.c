#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TASKS 20
#define DATA_FILE "tasks.dat"

struct task_data {
    char title[50];
    char date[11];
    int is_done;
};

struct task_data todo_list[MAX_TASKS];
int task_count = 0;
const char* TODAY_STR = "2026-01-24";

void save_tasks() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) return;
    for (int i = 0; i < task_count; i++) {
        fprintf(fp, "%d,%s,%s\n", todo_list[i].is_done, todo_list[i].date, todo_list[i].title);
    }
    fclose(fp);
}

void init_tasks() {
    strcpy(todo_list[0].title, "レポートの課題"); strcpy(todo_list[0].date, "2026-01-20"); todo_list[0].is_done = 0;
    strcpy(todo_list[1].title, "奨学金継続締め切り");   strcpy(todo_list[1].date, "2026-01-24"); todo_list[1].is_done = 0;
    strcpy(todo_list[2].title, "ホテル代を払う");     strcpy(todo_list[2].date, "2026-01-30"); todo_list[2].is_done = 0;
    strcpy(todo_list[3].title, "部活のミーティング");     strcpy(todo_list[3].date, "2026-02-15"); todo_list[3].is_done = 0;
    task_count = 4;
}

void load_tasks() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        init_tasks();
        return;
    }
    task_count = 0;
    // 修正ポイント：書式指定子を1行にまとめ、最後に \n を追加
    while (task_count < MAX_TASKS && 
           fscanf(fp, "%d,%10[^,],%49[^\n]\n", 
                  &todo_list[task_count].is_done, 
                  todo_list[task_count].date, 
                  todo_list[task_count].title) == 3) {
        task_count++;
    }
    fclose(fp);
}

time_t string_to_time(const char* date_str) {
    struct tm tm_date = {0};
    int y, m, d;
    sscanf(date_str, "%d-%d-%d", &y, &m, &d);
    tm_date.tm_year = y - 1900;
    tm_date.tm_mon = m - 1;
    tm_date.tm_mday = d;
    return mktime(&tm_date);
}

int main(int argc, char *argv[]) {
    load_tasks();

    if (argc < 2) {
        printf("--- Usage ---\n");
        printf("  list             : 全表示\n");
        printf("  add [名] [日]    : 追加\n");
        printf("  done [番号]      : 完了チェック\n");
        printf("  delete [番号]    : 削除\n");
        printf("  expired          : 期限切れのみ表示\n");
        printf("  near [day/week/month] : 指定期間内のタスク表示\n");
        return 1;
    }

    if (strcmp(argv[1], "list") == 0) {
        printf("ID  Stat  Deadline    Task\n");
        for (int i = 0; i < task_count; i++) {
            printf("%d:  [%s]  %s  %s\n", i, todo_list[i].is_done ? "x" : " ", todo_list[i].date, todo_list[i].title);
        }
    }
    else if (strcmp(argv[1], "add") == 0) {
        if (argc < 4) return 1;
        strncpy(todo_list[task_count].title, argv[2], 49);
        strncpy(todo_list[task_count].date, argv[3], 10);
        todo_list[task_count].is_done = 0;
        task_count++;
        printf("Added: %s\n", argv[2]);
    }
    else if (strcmp(argv[1], "done") == 0) {
        int idx = atoi(argv[2]);
        if (idx >= 0 && idx < task_count) {
            todo_list[idx].is_done = 1;
            printf("Marked %d as Done\n", idx);
        }
    }
    else if (strcmp(argv[1], "delete") == 0) {
        int idx = atoi(argv[2]);
        if (idx >= 0 && idx < task_count) {
            for (int i = idx; i < task_count - 1; i++) {
                todo_list[i] = todo_list[i+1];
            }
            task_count--;
            printf("Deleted task %d\n", idx);
        }
    }
    else if (strcmp(argv[1], "expired") == 0) {
        printf("--- Expired Tasks ---\n");
        for (int i = 0; i < task_count; i++) {
            if (strcmp(todo_list[i].date, TODAY_STR) < 0 && !todo_list[i].is_done) {
                printf("%d: %s %s\n", i, todo_list[i].date, todo_list[i].title);
            }
        }
    }
    else if (strcmp(argv[1], "near") == 0) {
        if (argc < 3) return 1;
        time_t now = string_to_time(TODAY_STR);
        double range = 0;
        if (strcmp(argv[2], "day") == 0) range = 86400;
        else if (strcmp(argv[2], "week") == 0) range = 86400 * 7;
        else if (strcmp(argv[2], "month") == 0) range = 86400 * 30;

        printf("--- Near Tasks (%s) ---\n", argv[2]);
        for (int i = 0; i < task_count; i++) {
            time_t t_time = string_to_time(todo_list[i].date);
            double diff = difftime(t_time, now);
            if (diff >= 0 && diff <= range) {
                printf("%d: %s %s\n", i, todo_list[i].date, todo_list[i].title);
            }
        }
    }

    save_tasks(); // 最後に保存
    return 0;
}