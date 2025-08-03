#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    omp_set_num_threads(6);

    int results[6][10] = {0}; // Store results for each thread and iteration

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        for (int i = 0; i < 10; ++i)
        {
            int result = 0;
            switch (thread_id) {
                case 0:
                    result = i + 1; // i++
                    break;
                case 1:
                    result = i - 1; // i--
                    break;
                case 2:
                    result = i * i; // i*i
                    break;
                case 3:
                    result = i - 1; // --i
                    break;
                case 4:
                    result = i + 1; // ++i
                    break;
                case 5:
                    // Will be set after barrier
                    break;
            }
            results[thread_id][i] = result;

            // Synchronize all threads before thread 5 sums
            #pragma omp barrier

            if (thread_id == 5) {
                int sum = 0;
                for (int t = 0; t < 5; ++t) {
                    sum += results[t][i];
                }
                results[thread_id][i] = sum;
                result = sum;
            }

            #pragma omp critical
            cout << "Thread " << thread_id << " iteration " << i << " result: " << results[thread_id][i] << endl;
        }
    }
    return 0;
}