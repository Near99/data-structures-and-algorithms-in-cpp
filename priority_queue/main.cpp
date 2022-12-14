#include "assert.h"
#include "pq.h"

using namespace pq;

int main() {
    const int Q_CAP = 10;
    PriorityQueue q(Q_CAP);
    assert(q.size() == 0 && q.capacity() == Q_CAP);
    assert(q.empty() == true && q.full() == false);
    int intput_arr[] = {66, 3, 899, 24, 123, 758, 97, 77, 222, 1};
    for (int i = 0; i < 10; i++) {
        q.insert(intput_arr[i]);
    }
    assert(q.empty() == false && q.full() == true);
    q.heapSort(intput_arr, Q_CAP);
    for (int i = 0; i < 10; i++) {
        std::cout << intput_arr[i] << std::endl;
    }

    return 0;
}
