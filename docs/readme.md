# cfastSQL
## Introduce
```
    This is a fast and convenient NoSQL for cpp (c11 or higher),which just need include this head file instead of connect to the sql.It support hash_map and table dataFromat.And it also supports persistence.
    Now,it can only use string as the data.
```
## How to use
```cpp
#include<bits/stdc++.h>
#include"cfastsql.h"            //include this
using namespace std;

int main(){
    cfastSQL sql("./test.txt");  //create a cfastSQL object with the file name
    
    //hash_map set
    sql.set_map_data("test1","test1");
    sql.set_map_data("test2","test2");
    sql.set_map_data("test3","test3");
    sql.set_map_data("test4","test4");

    //table insert
    sql.insert_table_value_front("test5","test5");
    sql.insert_table_value_last("test5","test6");

    //delete example
    sql.delete_map_data("test4");
    cout<<sql.pop_table_value_last("test5");
    
    //get example
    cout<<sql.get_map_data("test2")<<endl;
    cout<<sql.get_table_value_last("test2")<<endl;
    
    // the data save as a file
    sql.savecfastSQL("test.txt");
system("pause");
return 0;
}
```

