#include <bits/stdc++.h>


using namespace std;

int dims[9] = {100, 500, 1000, 2000, 10000, 15000, 30000, 50000, 100000};

/*!
@brief Структура для работы с данным о квартирах
\param houseNum номер дома
\param flatNum номер квартиры
\param roomCount количество комнат
\param flatSquare площадь квартиры
\param ownerName имя владельца
\param countResidents количество жителей
*/
struct flatsData{
    int houseNum;
    int flatNum;
    int roomCount;
    int flatSquare;
    string ownerName;
    int countResidents;
    

    flatsData(int houseNum, int flatNum, int roomCount, int flatSquare, string ownerName, int countResidents){
        this->houseNum = houseNum;
        this->flatNum = flatNum;
        this->roomCount = roomCount;
        this->flatSquare = flatSquare;
        this->ownerName = ownerName;
        this->countResidents = countResidents;
    }

    /*!
    @brief Оператор проверки на равенство двух квартир
    \param a данные о первой квартире
    \param b данные о второй квартире
    \return Совпадают ли данные о квартирах
    */
    friend bool operator == (const flatsData & a, const flatsData & b){
        return a.flatSquare == b.flatSquare && a.houseNum == b.houseNum && a.flatNum == b.flatNum && a.ownerName == b.ownerName;
    }
    /*!
    @brief Оператор проверки меньше
    \param a данные о первой квартире
    \param b данные о второй квартире
    \return Меньше ли данные о первой квартире
    */
    friend bool operator < (const flatsData & a, const flatsData & b){
        return ((a.flatSquare > b.flatSquare) || (a.flatSquare == b.flatSquare && a.houseNum < b.houseNum) || (a.flatSquare == b.flatSquare && a.houseNum == b.houseNum && a.flatNum < b.flatNum) || (a.flatSquare == b.flatSquare && a.houseNum == b.houseNum && a.flatNum == b.flatNum && a.ownerName < b.ownerName));
    }

    /*!
    @brief Оператор проверки на меньше или равно
    \param a данные о первой квартире
    \param b данные о второй квартире
    \return Меньше или равны ли данные о первой 
    */
    friend bool operator <= (const flatsData & a, const flatsData & b){
        return a < b || a == b;
    }

    /*!
    @brief Оператор проверки на больше
    \param a данные о первой квартире
    \param b данные о второй квартире
    \return Больше ли данные о первой квартире
    */
    friend bool operator > (const flatsData & a, const flatsData & b){
        return !(a <= b);
    }

    /*!
    @brief Оператор проверки на больше или равно
    \param a данные о первой квартире
    \param b данные о второй квартире
    \return больше или равны ли данные о первой квартире
    */
    friend bool operator >= (const flatsData & a, const flatsData & b){
        return !(a < b);
    }

};

/*!
\brief Функция для генерации строки определенной длины
\param len Длина генерируемой строки
*/
string generateString(const int len){


    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string tmp = "";
    for (int i = 0; i < len; i++)
        tmp += alphabet[rand() % (sizeof(alphabet) - 1)];
    
    return tmp;

}


/*!
\brief Функция для генерации данных о пассажирах
\param dim Количество данных, которое надо сгенерировать
*/
void generateData(int dim){

    ofstream fout("data.txt");
    for (int i = 0; i < dim; i++){
        int nameLen = rand() % 50 + 20;
        string ownerName = generateString(nameLen);
        int houseNum = rand() % 200;
        int flatNum = rand() % 1000;
        int roomCount = rand() % 4 + 1;
        int flatSquare = rand() % 500; 
        int countResidents = rand() % 5;
        fout << houseNum << " " << flatNum << " " << roomCount << " " << flatSquare << " " << ownerName << " " << countResidents << "\n";
    }

    fout.close();
}

/*!
\brief Функция чтения данных из файла о квартираъ 
\param data Массив данных о квартирах 
*/
void readFromFile(vector<flatsData> & data){

    ifstream finp("data.txt");
    string tmp;
    data.clear();
    while(getline(finp, tmp)){
        stringstream ss(tmp);
        int houseNum, flatNum, roomCount, flatSquare, countResidents;
        string ownerName;
        ss >> houseNum >> flatNum >> roomCount >> flatSquare >> ownerName >> countResidents;
        flatsData tmpFlat(houseNum, flatNum, roomCount, flatSquare, ownerName, countResidents);
        data.push_back(tmpFlat);
    }
    finp.close();
}

/*!
\brief Функция сортировки пузырьком
\param vec Массив который надо отсортировать
*/
void bubbleSort(vector<flatsData> &vec){


   for (int i = 1; i < vec.size(); i++){
        for (int j = 0; j < vec.size()-i; j++){
            if (vec[j] > vec[j+1]) swap(vec[j], vec[j+1]);
        }
   }

}

/*!
\brief Функция сортировки вставками
\param vec Массив для соритвроки
*/
void insertSort(vector<flatsData> &vec){

    for (int i = 1; i < vec.size(); i++){
        int j = i - 1;
        flatsData key = vec[i];
        while (j >= 0 && vec[j] > key){
            vec[j+1] = vec[j];
            vec[j] = key;
            j--;
        }
        
    }
}

/*!
\brief Функция быстрой сортирвоки
\param vec Массив для сортировки
\param start Начало подпоследовательности для сортировки
\param end Конец подпоследовательности для сортировки
*/
 
void quickSort(vector<flatsData> &vec, int start, int end){
   if (start >= end)
        return;

    int left = start;
    int right = end;

    
    flatsData p(vec[(right+left)/ 2].houseNum, vec[(right+left)/ 2].flatNum, vec[(right+left)/ 2].roomCount, vec[(right+left)/ 2].flatSquare, vec[(right+left)/ 2].ownerName, vec[(right+left)/ 2].countResidents); 

    do{
        while (vec[left] < p) left++;
        while (vec[right] > p) right--;

        if (left <= right){
            swap(vec[left], vec[right]);
            
            left++;
            right--;
        }

    } while (left <= right);

    quickSort(vec, start, right);
    quickSort(vec, left, end);
}

void writeDataToConsole(const vector<flatsData> &a){
    for (int i = 0; i < a.size(); i++){
        cout << a[i].houseNum << " " << a[i].flatNum << " " << a[i].roomCount << " " << a[i].flatSquare << " " << a[i].ownerName << " " << a[i].countResidents << endl; 
    }
}


int main(){
    generateData(10);
    vector<flatsData> a;
    readFromFile(a);
    quickSort(a, 0, a.size()-1);
    writeDataToConsole(a);

    
    ofstream times("timestamps.txt");

    for (int i = 0; i < 9; i++){
        generateData(dims[i]);
        vector<flatsData> a;

        times << dims[i] << endl;
        chrono::steady_clock::time_point time_start; 
        chrono::steady_clock::time_point time_end;

        readFromFile(a);
        cout << a.size() << endl;
        time_start = chrono::steady_clock::now();
        bubbleSort(a);
        time_end = chrono::steady_clock::now();
        times <<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << endl; 

        readFromFile(a);
        cout << a.size() << endl;
        time_start = chrono::steady_clock::now();
        insertSort(a);
        time_end = chrono::steady_clock::now();
        times <<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << endl; 

        readFromFile(a);
        cout << a.size() << endl;
        time_start = chrono::steady_clock::now();
        quickSort(a, 0, a.size() - 1);
        time_end = chrono::steady_clock::now();
        times <<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count() << endl; 

    }
    times.close();
}
