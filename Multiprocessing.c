// Taleen Bayatneh 1211305 section:2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#define MAX_LINE_LENGTH 100
#define MAX_RECORDS 1000
typedef struct
{
    float height;
    float weight;
} Person;

Person people[MAX_RECORDS];
int num_people = 0;
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
float child(double child_lines,int numofchild)
{
    float child_total =0;
    int x = child_lines*(numofchild-1) ;

    for(int i=x+1; i<=child_lines+x; i++)
    {
        if (i>=num_people)
        break;
        child_total += (BMI_naive_appraoch(people[i].height,  people[i].weight));

    }
    return child_total;
}

int main()
{
    struct  timespec begin;
    timespec_get(&begin,TIME_UTC);
    int num_of_child = 5;
    float avg=0;
    float total=0;
    read_data();
    double child_lines =0.0;
    child_lines= num_people/num_of_child;
    ceil(child_lines);

    int fd[num_of_child][2];

    for (int x =0; x<num_of_child; x++)
    {
        if (pipe(fd[x]) == -1)
        {
            printf("error with opening the pipe \n");
            return 1;
        }

    }

// Loop to create child processes
    for (int y = 1; y <= num_of_child; y++)
    {
        int pid = fork();
        if (pid == -1)
        {
            printf("Fork failed\n");
        }
        else if (pid == 0) // Child process
        {

            total += child(child_lines, y);
            write(fd[y-1][1], &total, sizeof(float));
            close(fd[y-1][1]);
            exit(0);
        }
        else // Parent process
        {
            close(fd[y-1][1]);
            read(fd[y-1][0], &total, sizeof(float));
            close(fd[y-1][0]);
        }
    }

   /*while(wait(NULL)!=-1||errno!= ECHILD)
    {
        printf("\n waited for a child to finish");

    }*/

    int j =0;
    avg = total / (500);
    if( j==0)
    {
        printf("avg bmi = %.2f\n",avg);
        j=1;
    }
 struct  timespec end;
    timespec_get(&end,TIME_UTC);

     double time_spent=(end.tv_sec - begin.tv_sec)+(end.tv_nsec - begin.tv_nsec)/1000000000.0;
     printf("it took time= %lf\n",time_spent);




    return 0;
}
