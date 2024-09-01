#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TASKS 10
#define MAX_WORDS 100

typedef struct task {
	int id;
	char *task_name;
	int is_completed;
} Tasks[MAX_TASKS];

Tasks tasks;
int op = 1;
int iterator = 1;

void print_menu()
{
	printf("ITERATOR VALUE: %d\n", iterator);
    printf("+-----+--------------------------------------------------+---------------+\n");
    printf("| Id  |                     Task                         |   Completed   |\n");
    printf("+-----+--------------------------------------------------+---------------+\n");

	for (int i = 0; i < MAX_TASKS; ++i)
	{
		if (tasks[i].task_name != NULL) {
			printf("|  %d  |  %-*s  |      %s      |\n", tasks[i].id, 46, tasks[i].task_name, tasks[i].is_completed ? "Yes" : "No ");
			printf("+-----+--------------------------------------------------+---------------+\n");
		}
	}

	printf("(A) Add task, (D) Delete task, (X) Mark as completed, (Q) Quit\n");
}

int first_empty_value()
{
	for (int i = 0; i < MAX_TASKS; ++i)
	{
		if (tasks[i].task_name == NULL)
			return i;
	}

	return -1;
}

void input_task()
{
	char *task_name = tasks[first_empty_value()].task_name = malloc(sizeof(char) * MAX_WORDS);
	int i = first_empty_value();

	printf("Task name: ");
	fgets(task_name, MAX_WORDS, stdin);
	task_name[strlen(task_name)-1] = '\0';

	tasks[i-1].is_completed = 0;
	tasks[i-1].id = iterator;

	iterator++;
}

void delete_task(int i)
{
	iterator--;
	tasks[i].id--;

	for (int j = i; j < iterator; ++j)
	{
		tasks[j-1] = tasks[j];
		tasks[j].id = -1;
		tasks[j].task_name = NULL;
		tasks[j].is_completed = -1;

		tasks[i].id--;
	}

}

void mark_as_completed(int i)
{
	tasks[i-1].is_completed = 1;
}

void free_all()
{
	for (int i = 0; i < MAX_TASKS; ++i)
		free(tasks[i].task_name);
}

void clear_term()
{
	system("clear");
}

int get_id_task()
{
	int i = 0;

	printf("id task :: ");
	scanf("%d", &i);
	getchar();

	return i;
}

void request_option()
{
	int option;

	printf(":: ");
	option = getchar();
	getchar();

	switch (option)
	{
		case 'a':
		case 'A':
			input_task();
			break;
		case 'd':
		case 'D':
			delete_task(get_id_task());
			break;
		case 'x':
		case 'X':
			mark_as_completed(get_id_task());
			break;
		case 'q':
		case 'Q':
			op = 0;
			break;
		default:
			printf("Option doesn't exist.\n");
			system("sleep .4");
	}
}

int main()
{
	clear_term();
	print_menu();
	request_option();

	while (op)
	{
		clear_term();
		print_menu();
		request_option();
	}

	free_all();

	return 0;
}
