//taleen bayatneh 1211305 sec:2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define MAX_LINE_LENGTH 100
#define MAX_RECORDS 1000
typedef struct
{
    float height;
    float weight;
} Person;

Person people[MAX_RECORDS];
int num_people = 0;
float thread_lines = 0;
float final_total =0.0;
int th =0;
int numOfThds =5;

pthread_mutex_t lock;

void read_data()
{

    char *gender;
    char *Height_str;
    char *Weight_str;

    FILE *file = fopen("/home/taleen-bayatneh/Desktop/taleen-/bmi.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file");
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        gender = strtok(line, ",");
        Height_str = strtok(NULL, ",");
        Weight_str = strtok(NULL, ",");


        people[num_people].height = atof(Height_str);
        people[num_people].weight = atof(Weight_str);

        num_people++;
    }

    fclose(file);
}
float BMI_naive_appraoch(float Height, float Weight)
{
    float BMI;
    float hight_m= Height / 100.0;

    BMI = Weight / (hight_m * hight_m);

    return BMI;
}

void* threadFunction (void* thread_number)
{

    int num= *(int*)thread_number;
    int x = thread_lines*(num) ;
    float sub_total=0;
    pthread_mutex_lock(&lock);

    for(int i=x+1; i<=thread_lines+x ; i++)
    {
        if (i>=num_people)
            break;

        //printf("Height:%.2f \t Weight:%.2f \n", people[i].height, people[i].weight);

        sub_total += (BMI_naive_appraoch(people[i].height, people[i].weight));


    }
    th ++;
    //printf("sub_total= %.2f ,T=%d\n", sub_total,num);
    final_total+=sub_total;
    pthread_mutex_unlock(&lock);

    free(thread_number);
    if (th==numOfThds)
        printf("bmi avg = %.2lf\n", final_total/ (num_people-1));


}
int main()
{
 struct  timespec begin;
    timespec_get(&begin,TIME_UTC);


    read_data();


    pthread_t threads [numOfThds];
    thread_lines= num_people/numOfThds;
    float final_total=0;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init has failed\n");
        return 1;
    }


    for (int  t=0; t < numOfThds; t++)
    {
        int* thNUM = malloc(sizeof(int));
        *thNUM = t;
        pthread_create(&threads[t],NULL,&threadFunction,(void *)thNUM);

    }

    for (int a=0; a < numOfThds; a++)
    {
        pthread_join(threads[a],NULL);
    }


    pthread_mutex_destroy(&lock);

 struct  timespec end;
     timespec_get(&end,TIME_UTC);

     double time_spent=(end.tv_sec - begin.tv_sec)+(end.tv_nsec - begin.tv_nsec)/1000000000.0;
     printf("it took time= %lf\n",time_spent);

     return 0;
}
