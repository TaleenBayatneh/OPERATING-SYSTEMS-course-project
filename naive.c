//taleen bayatneh 1211305 sec: 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LINE_LENGTH 1000

float BMI_naive_appraoch(float Height, float Weight)
{
    float BMI;
    float hight_m= Height / 100.0;

    BMI = Weight / (hight_m * hight_m);

    return BMI;
}

int main()
{
struct  timespec begin;
    timespec_get(&begin,TIME_UTC);

    char *gender;
    char *Height_str;
    char *Weight_str;

    float Height;
    float Weight;
    float BMI;


    FILE *bmiFile;
    bmiFile= fopen("/home/taleen-bayatneh/Desktop/taleen-/bmi.csv","r");

    if (bmiFile == NULL) {
        printf("The file is not opened. The program will "
               "now exit.\n");
        exit(0);
        }
    else {
        printf("The file is opened Successfully. \n \n");
    }


    char line[MAX_LINE_LENGTH];

    float BMI_total=0;
    int counter=0;
    float BMI_avg;


    while (fgets(line, sizeof(line), bmiFile) != NULL) {



        gender = strtok(line, ",");
        Height_str = strtok(NULL, ",");
        Weight_str = strtok(NULL, ",");

        Height = atof(Height_str);
        Weight = atof(Weight_str);

        // Calculate BMI
        if (Height != 0 && Weight != 0){
         BMI= BMI_naive_appraoch(Height, Weight);
        BMI_total+= BMI;
        counter++;
        }


    }



    BMI_avg= BMI_total / counter;

    printf("BMI average= %.2lf\n", BMI_avg);
      fclose(bmiFile);

    struct  timespec end;
     timespec_get(&end,TIME_UTC);

     double time_spent=(end.tv_sec - begin.tv_sec)+(end.tv_nsec - begin.tv_nsec)/1000000000.0;
     printf("it took time= %lf\n",time_spent);


    return 0;
}

