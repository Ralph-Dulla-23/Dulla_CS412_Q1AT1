#include <iostream>
#include <omp.h>
using namespace std;




int main()
{
    omp_set_num_threads(4);
   
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        for (int i = 0; i < 10; ++i)
        {
            #pragma omp critical
            {
                cout << "Thread " << thread_id + 1 << " # " << i + 1 << endl;
            }
        }
       
    }
    return 0;
}
/*  t1 : i++
    t2: i--
    t3: i**
    t4: --i
    t5: ++i
    t6: t1 + t2 + t3 + t4 + t5 + t6
    the threads will cycle for 10 loops    */
