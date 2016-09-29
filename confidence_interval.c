#include <stdio.h>
#include <math.h>

#define NUM_DATA 50

double compute_avg(double* data, int num)
{
    double sum = 0.0;

    for(int i=0;i<num;++i)
        sum += data[i];

    return sum / num;
}

double compute_std(double avg,double* data)
{
    double sum = 0.0;

    for(int i=0;i<NUM_DATA;++i)
    {
        sum += pow(data[i]-avg,2);
    }

    return sqrt(sum / (double)(NUM_DATA - 1));
}

void compute_ci(double avg,double std,double* max,double* min)
{
    *max = avg + 2*std;
    *min = avg - 2*std;
}

int main()
{
    FILE* input = fopen("result_clock_gettime.csv","r");

    if(input != NULL)
    {
        double baseline[NUM_DATA],openmp2[NUM_DATA],openmp4[NUM_DATA],avx[NUM_DATA],avxun[NUM_DATA],openmp8[NUM_DATA],openmp16[NUM_DATA];
        
        double avg_base,avg_omp2,avg_omp4,avg_avx,avg_avxun,avg_omp8,avg_omp16;
        double std_base,std_omp2,std_omp4,std_avx,std_avxun,std_omp8,std_omp16;
        double max_base,max_omp2,max_omp4,max_avx,max_avxun,max_omp8,max_omp16;
        double min_base,min_omp2,min_omp4,min_avx,min_avxun,min_omp8,min_omp16;

        int num_base = NUM_DATA, num_omp2 = NUM_DATA, num_omp4 = NUM_DATA, num_avx = NUM_DATA, num_avxun = NUM_DATA, num_omp8 = NUM_DATA, num_omp16 = NUM_DATA;
        
        int tmp;

        for(int i=0;i<NUM_DATA;++i)
        {
            fscanf(input,"%d, %lf, %lf, %lf, %lf, %lf, %lf, %lf",&tmp,&baseline[i],&openmp2[i],&openmp4[i],&avx[i],&avxun[i],&openmp8[i],&openmp16[i]);
        }

//compute average of data
        avg_base = compute_avg(baseline,num_base);
        avg_omp2 = compute_avg(openmp2,num_omp2);
        avg_omp4 = compute_avg(openmp4,num_omp4);
        avg_avx = compute_avg(avx,num_avx);
        avg_avxun = compute_avg(avxun,num_avxun);
        avg_omp8 = compute_avg(openmp8,num_omp8);
        avg_omp16 = compute_avg(openmp16,num_omp16);

//compute standard deviation
        std_base = compute_std(avg_base,baseline);
        std_omp2 = compute_std(avg_omp2,openmp2);
        std_omp4 = compute_std(avg_omp4,openmp4);
        std_avx = compute_std(avg_avx,avx);
        std_avxun = compute_std(avg_avxun,avxun);
        std_omp8 = compute_std(avg_omp8,openmp8);
        std_omp16 = compute_std(avg_omp16,openmp16);
        
//compute upper-bound and lower-bound
        compute_ci(avg_base,std_base,&max_base,&min_base);
        compute_ci(avg_omp2,std_omp2,&max_omp2,&min_omp2);
        compute_ci(avg_omp4,std_omp4,&max_omp4,&min_omp4);
        compute_ci(avg_avx,std_avx,&max_avx,&min_avx);
        compute_ci(avg_avxun,std_avxun,&max_avxun,&min_avxun);
        compute_ci(avg_omp8,std_omp8,&max_omp8,&min_omp8);
        compute_ci(avg_omp16,std_omp16,&max_omp16,&min_omp16);
        
        for(int i=0;i<NUM_DATA;++i)
        {
            if(baseline[i] > max_base || baseline[i] < min_base)
            {
                baseline[i] = 0;
                num_base--;
            }
            else if(openmp2[i] > max_omp2 || openmp2[i] < min_omp2)
            {
                openmp2[i] = 0;
                num_omp2--;
            }
            else if(openmp4[i] > max_omp4 || openmp4[i] < min_omp4)
            {
                openmp4[i] = 0;
                num_omp4--;
            }
            else if(avx[i] > max_avx || avx[i] < min_avx)
            {
                avx[i] = 0;
                num_avx--;
            }
            else if(avxun[i] > max_avxun || avxun[i] < min_avxun)
            {
                avxun[i] = 0;
                num_avxun--;
            }
            else if(openmp8[i] > max_omp8 || openmp8[i] < min_omp8)
            {
                openmp8[i] = 0;
                num_omp8--;
            }
            else if(openmp16[i] > max_omp16 || openmp16[i] < min_omp16)
            {
                openmp16[i] = 0;
                num_omp16--;
            }
        }

        avg_base = compute_avg(baseline,num_base);
        avg_omp2 = compute_avg(openmp2,num_omp2);
        avg_omp4 = compute_avg(openmp4,num_omp4);
        avg_avx = compute_avg(avx,num_avx);
        avg_avxun = compute_avg(avxun,num_avxun);
        avg_omp8 = compute_avg(openmp8,num_omp8);
        avg_omp16 = compute_avg(openmp16,num_omp16);
            
        printf("%d, %f, %f, %f, %f, %f, %f, %f\n",tmp,avg_base,avg_omp2,avg_omp4,avg_avx,avg_avxun,avg_omp8,avg_omp16);
    }

    fclose(input);

    return 0;
}
