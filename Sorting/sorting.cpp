#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;



//1、插入排序
//1.1、直接插入排序
//空间效率：O(1)
//时间效率：O(n^2)
//稳定性：稳定
//适用性：顺序存储和链式存储的线性表
void Insertion_Sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {                       //依次将 arr[1] ~ arr[n - 1] 插入前面已排序序列
        if (arr[i] < arr[i - 1]) {                      //若 arr[i] 关键字小于其前驱，将 arr[i] 插入有序表
            int temp = arr[i];                          //保存 arr[i]，避免向后挪位时丢失
            int j;                                      //后面需要 j，所以先声明保存
            for (j = i - 1; j >= 0 && temp < arr[j]; j--) {     //从 arr[i] 前一个，从后往前寻找待插入的位置，最终 j 会停在 temp 的前驱位置
                arr[j + 1] = arr[j];                    //向后挪位
            }
            arr[j + 1] = temp;                          //复制到插入位置
        }
    }

    cout << "Insertion_Sort排序后:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << '\n';
}



//1.2、折半插入排序
//空间效率：O(1)
//时间效率：O(n^2)
//稳定性：稳定
//适用性：顺序存储的线性表
void Binary_Insertion_Sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {                       //依次将 arr[1] ~ arr[n - 1] 插入前面的已排序序列
        int temp = arr[i];                              //保存 arr[i]，避免向后挪位时丢失
        int low = 0;                                    //折半查找的起点
        int high = i - 1;                               //折半查找的终点
        while (low <= high) {                           //折半查找（默认递增有序）
            int mid = low + (high - low) / 2;           //取中间点 等价于 int mid = (low + high) / 2 这种写法的好处在于避免 low 和 high 过大 相加超出 int 的范围
            if (arr[mid] > temp) high = mid - 1;        //如果中间点的值 > temp 查找左半子表
            else low = mid + 1;                         //如果中间点的值 <= temp 查找右半子表
        }
        for (int j = i; j > low; j--) {                 //从 i 开始 后移
            arr[j] = arr[j - 1];
        }
        arr[low] = temp;                                //最终 low 的左边都是 <= temp 的值 即 low 指的是第一个 > temp 的位置 就是 temp 该插入的位置
    }

    cout << "Binary_Insertion_Sort排序后:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << '\n';
}



//1.3、希尔排序
//空间效率：O(1)
//时间效率：未知 当 n 在常见范围内时，时间复杂度约为O(n^1.3)；最坏情况下退化为O(n^2)
//稳定性：不稳定
//适用性：顺序存储的线性表
void Shell_Sort(int arr[], int n) {
    int dk, i, j;
    for (dk = n / 2; dk >= 1; dk /= 2) {                //增量变化（无统一规定）
        for (i = dk; i < n; i++) {                      //依次将 arr[dk] ~ arr[n - 1] 插入各自前面的已排序序列
            if (arr[i] < arr[i - dk]) {                 //需将 arr[i] 插入有序增量表
                int temp = arr[i];                      //保存 arr[i]，避免向后挪位时丢失
                for (j = i - dk; j >= 0 && temp < arr[j]; j -= dk) {
                    arr[j + dk] = arr[j];               //记录后移 查找插入的位置
                }
                arr[j + dk] = temp;                     //插入
            }
        }
    }

    cout << "Shell_Sort排序后:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << '\n';
}



//2、交换排序
//2.1、冒泡排序
//空间效率：O(1)
//时间效率：O(n^2)
//稳定性：稳定
//适用性：顺序存储和链式存储的线性表
void Bubble_Sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;                              //表示u本趟冒泡是否发生交换的标志
        for (int j = 0; j < n - i - 1; j++) {           //一趟冒泡过程
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true;
            }
        }
        if (flag == false) break;//return;              //本趟遍历后没有发生交换 说明表已经有序
    }

    cout << "Bubble_Sort排序后:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << '\n';
}



//2.2、快速排序
//空间效率：最好情况O(log2(n))、最坏情况O(n)、平均情况O(log2(n))
//时间效率：最好情况O(nlog2(n))、最坏情况O(n^2)、平均运行时间非常接近其最优情况，远优于最坏情况，因此快速排序时所有内部排序算法中平均性能最优的排序方法
//稳定性：不稳定
//适用性：顺序存储的线性表
int Partition(int arr[], int low, int high) {           //一趟划分
    int pivot = arr[low];                               //将当前表中第一个元素设为枢轴 对表进行划分
    while (low < high) {                                //只要 low < high 就执行循环 当 low == high 说明这就是枢轴元素的最终位置
        while (low < high && arr[high] >= pivot) high--;//从后往前找到第一个 < pivot 的元素
        arr[low] = arr[high];                           //将比枢轴小的元素移动到左端
        while (low < high && arr[low] <= pivot) low++;  //从前往后找到第一个 > pivot 的元素
        arr[high] = arr[low];                           //将比枢轴大的元素移动到右端
    }

    arr[low] = pivot;                                   //枢轴元素存放到最终位置
    return low;                                         //返回存放枢轴元素的最终位置
}

void Quick_Sort(int arr[], int low, int high, bool first = true) {
    if (low < high) {                                   //递归需要满足的条件 即当前子表至少包含 2 个元素，才需要继续划分
        //Partition() 就是划分操作 将 arr[low...high] 划分为满足上述条件的两个子表
        int pivotpos = Partition(arr, low, high);       //划分
        Quick_Sort(arr, low, pivotpos - 1 , false);             //对左子表继续划分
        Quick_Sort(arr, pivotpos + 1, high , false);            //对右子表继续划分
    }

    if (first) {
        cout << "Quick_Sort排序后:" << endl;
        for (int i = 0; i < 10; i++) cout << arr[i] << " ";
        cout << '\n';
    }
}



//3、选择排序
//3.1、简单选择排序
//空间效率：O(1)
//时间效率：O(n^2)
//稳定性：不稳定
//适用性：顺序存储和链式存储的线性表
void Selection_Sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {                   //共进行 n - 1 趟
        int min = i;                                    //初始化为 i 并用来记录最小元素的位置
        for (int j = i + 1; j < n; j++) {               //在 arr[i] - arr[n - 1] 中选择最小的元素
            if (arr[j] < arr[min]) min = j;             //如果 j 索引的值小与最小元素坐标的值 就更新最小元素坐标
        }
        if (min != i) {                                 //如果最小元素坐标不是初始值 交换
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }

    cout << "Selection_Sort排序后:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << '\n';
}



//3.2、堆排序
//空间效率：O(1)
//时间效率：最好、最坏、平均情况下均为O(nlog2(n))
//稳定性：不稳定
//适用性：顺序存储的线性表
void Heap_Adjust(int arr[], int k, int n) {             //对以 k 为根的子树进行调整
    int temp = arr[k];                                  //temp 暂存子树的根结点
    for (int i = 2 * k; i <= n; i *= 2) {               //找到根结点的左右孩子 沿关键字较大的子结点向下筛选
        if (i < n && arr[i] < arr[i + 1]) i++;          //取关键字较大的子结点的下标
        if (temp > arr[i]) break;
        else {
            arr[k] = arr[i];                            //将较大的结点上移
            k = i;                                      //修改 k 值 以便继续向下筛选
        }
    }
    arr[k] = temp;                                      //把原本根结点的值放到最终位置 k
}

void Build_Max_Heap(int arr[], int n) {
    for (int i = n / 2; i > 0; i--) {                   //从最后一个分支结点到根结点
        Heap_Adjust(arr, i, n);                         //反复调整子树
    }
}

void Heap_Sort(int arr[], int n) {
    Build_Max_Heap(arr, n);                             //初始建堆
    cout << "Heap_Sort排序后：" << endl;
    for (int i = n; i > 1; i--) {                       //执行 n - 1 趟
        cout << arr[1] << " ";                          //输出堆顶元素
        int temp = arr[1];                              //将堆顶元素与堆底元素交换
        arr[1] = arr[i];
        arr[i] = temp;

        Heap_Adjust(arr, 1, i - 1);                     //把剩余 i - 1 个元素重新整理为堆
    }
    cout << arr[1] << endl;
}



//4、归并排序
//空间效率：O(n)
//时间效率：O(nlog2(n))
//稳定性：稳定
//适用性：顺序存储和链式存储的线性表
int* B = (int*)malloc(10 * sizeof(int));                //辅助数组 B
//int* B = new int[10];
void Merge(int arr[], int low, int mid, int high) {     //表 arr 的两段 arr[low...mid] arr[mid + 1...high] 各自有序 将它们合并成一个有序表
    int i, j, k;
    for (i = low; i <= high; i++) {                     //将 arr 中所有元素复制到 B 中
        B[i] = arr[i];
    }
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++) {
        if (B[i] <= B[j]) arr[k] = B[i++];              //比较 B 的两个段中的元素
        else arr[k] = B[j++];                           //将较小值复制到 arr 中
    }
    while (i <= mid) arr[k++] = B[i++];                 //若第一个表未检测完 复制
    while (j <= high) arr[k++] = B[j++];                //若第二个表未检测完 复制
}

void Merge_Sort(int arr[], int low, int high , bool first = true) {
    if (low < high) {
        int mid = (low + high) / 2;                     //从中间划分两个子序列
        Merge_Sort(arr, low, mid, false);               //对左侧子序列进行递归
        Merge_Sort(arr, mid + 1, high, false);          //对右侧子序列进行递归
        Merge(arr, low, mid, high);
    }
    if (first) {
        cout << "Merge_Sort排序后:" << endl;
        for (int i = 0; i < 10; i++) cout << arr[i] << " ";
        cout << '\n';
    }
}



//5、基数排序
//空间效率：O(r)
//时间效率：O(d(n + r))
//稳定性：稳定
//适用性：顺序存储和链式存储的线性表 链式结构尤其适合
void Radix_Sort();



//6、计数排序
//空间效率：O(n + k) 计数排序是一种以空间换时间的算法
//时间效率：O(n + k)
//稳定性：稳定
//适用性：顺序存储的线性表
void Count_Sort(int arr[], int B[], int n, int k) {
    int C[1000];
    for (int i = 0; i < k; i++) {                       //初始化计数数组
        C[i] = 0;
    }
    for (int i = 0; i < n; i++) {                       //遍历输入数组 统计每个元素出现的次数
        C[arr[i]]++;                                    //C[arr[i]] 保存的是等于 arr[i] 的元素个数
    }
    for (int i = 1; i < k; i++) {                       //C[x] 保存的是小于或等于 x 的元素总数
        C[i] += C[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {                  //从后往前遍历输入数组
        B[C[arr[i]] - 1] = arr[i];                      //将元素 arr[i] 放置到输出数组 B[] 的正确位置
        C[arr[i]]--;                                    //更新计数数组 确保相同元素的相对顺序
    }
    cout << "Count_Sort排序后:" << endl;
    for (int i = 0; i < 10; i++) cout << B[i] << " ";
    cout << '\n';
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand((unsigned)time(NULL));

    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }

    cout << "排序前:" << endl;
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << '\n';

    //Insertion_Sort(arr, 10);
    //Binary_Insertion_Sort(arr, 10);
    //Shell_Sort(arr, 10);
    //Bubble_Sort(arr, 10);
    //Quick_Sort(arr, 0, 9);
    //Selection_Sort(arr, 10);

    int brr[11] = { -1 , 10 , 2 , 63 , 4 , 5 , 60 , 7 , 88 , 19 , 10 };
    Heap_Sort(brr, 10);

    //Merge_Sort(arr, 0, 9);

    int ans[10];
    Count_Sort(arr, ans, 10, 100);

    system("pause");

    return 0;
}