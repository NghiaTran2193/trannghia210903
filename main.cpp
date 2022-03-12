#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
struct process
{
  int proId;
  int arrTime;
  int burTime;

};
typedef struct process Process;
struct danhsach
{
    vector< Process> ds_a;
};
typedef struct danhsach DanhSach;
void Doc_ (ifstream &filein,Process &pr)
{


           filein >> pr.proId;
           filein >> pr.arrTime;
           filein >> pr.burTime;

}
void Doc_File(ifstream &filein,vector< Process> & ds_a)
{
    while(filein.eof() == false)
    {
        int n;
        filein >> n;
        for (int i=1;i<=n;i++)
        {
            Process pr;
            Doc_(filein, pr);
           ds_a.push_back(pr);
        }
    }
}
void test(Process pr)
{
    cout<< "\nProcess ID: "<< pr.proId;
    cout<< "\tArrival Time: "<< pr.arrTime;
    cout<< "\tBurst Time: "<< pr.burTime;
}
void xuat(vector< Process> ds_a)
{
    int i;

    for( i = 0;i < ds_a.size();i++)
    {
     test(ds_a[i]);
    }
}
int mat[10][6];

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrangeArrival(int num, int mat[][6])
{
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 5; k++) {
                    swap(mat[j][k], mat[j + 1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < num; i++) {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < num; j++) {
            if (temp >= mat[j][1] && low >= mat[j][2]) {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++) {
            swap(mat[val][k], mat[i][k]);
        }
    }
}

int main()
{
    Process pr;

   ifstream filein;
   filein.open("input.txt", ios_base::in);
   vector< Process> ds_a;
   DanhSach ds;
   Doc_File(filein, ds_a);
   xuat(ds_a);

     int num, temp;
     int arr[3]{pr.proId,pr.arrTime,pr.burTime};

  // for(int i = 0;i < ds_a.size();i++)
   //{
       // num++;

  // }


    for (int i = 0; i <4; i++) {



     mat[0][0]=ds_a.at(0).proId;
 mat[1][0]=ds_a.at(1).proId;
  mat[2][0]=ds_a.at(2).proId;
   mat[3][0]=ds_a.at(3).proId;
   mat[0][1]=ds_a.at(0).arrTime;
     mat[1][1]=ds_a.at(1).arrTime;
      mat[2][1]=ds_a.at(2).arrTime;
       mat[3][1]=ds_a.at(3).arrTime;
    mat[0][2]=ds_a.at(0).burTime;
      mat[1][2]=ds_a.at(1).burTime;
        mat[2][2]=ds_a.at(2).burTime;
          mat[3][2]=ds_a.at(3).burTime;

    }


    cout << "\nBefore Arrange...\n";
    cout << "Process ID\tArrival Time\tBurst Time\n";
    for (int i = 0; i < num; i++) {
        cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
             << mat[i][2] << "\n";
    }

    arrangeArrival(num, mat);
    completionTime(num, mat);
    cout << "Final Result...\n";
    cout << "Process ID\tArrival Time\tBurst Time\tWaiting "
            "Time\tTurnaround Time\n";
    for (int i = 0; i < num; i++) {
        cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
             << mat[i][2] << "\t\t" << mat[i][4] << "\t\t"
             << mat[i][5] << "\n";

    }

}
