//Поворот квадратного изображения NxN пикселей (4 байта на пиксель)
//На 90 градусов против часовой стрелке
//Для простоты вместо настоящего изображения используется массив 32-разрядных целых чисел

#include <iostream>
#define coord(j,i, N) ((i)+(j)*(N))

void print_matrix(int *m, int N)
{
    for(int i = 0; i< N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cout<<m[j+i*N];
        }
        std::cout<<'\n';
    }
}

bool compare_matrix(int *m, int *n, int N)
{
    for(int i = 0; i< N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(m[coord(i,j,N)]!=n[coord(i,j,N)])
                return false;
        }
    }
    return true;
}

void rotate_inplace(int* image, int N)
{
    int temp = 0;
    int n = N-1;
    for(int j = 0; j < N/2; j++)
    {
        for(int i = j; i < N-1-j; i++)
        {
            temp = image[coord(j,i,N)];
            image[coord(j,i,N)] = image[coord(i,n,N)];
            image[coord(i,n,N)] = image[coord(n,n-i+j,N)];
            image[coord(n,n-i+j,N)] = image[coord(n-i+j,j,N)];
            image[coord(n-i+j,j,N)] = temp;
        }
        n--;
    }
}

void rotate(int* image, int N, int*res)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            res[coord(i,j,N)] = image[coord(j,N-i-1,N)];
        }
    }
}

int main(int argc, char *argv[])
{
    const int N = 2;
    int image[N*N], res[N*N];
    for(int i = 0;i<N;i++)
    {
        for(int j = 0; j < N; j++)
            image[j+i*N] = j+i*N;
    }
    //Поворот в другом блоке памяти
    rotate(image,N,res);
    //Поворот на месте
    rotate_inplace(image,N);
    //Проверка
    std::cout<<compare_matrix(image,res,N);
}