#ifndef cfastSQL_head
#define cfastSQL_head
#include<unordered_map>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <ios>
#include <iosfwd>
#include <fstream>
#include <sstream> 
#include <bits/stdc++.h>
using namespace std;

static string SpiltKey = "end_data_5454sda65s4d541sd14";
static string SpiltValue = "end_data_5454sda65s4d541sd14";
template<class Type>
class cfastNode{
    public:
        cfastNode *next;
        cfastNode *prev;
        Type data;

        cfastNode(Type data){
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }

        cfastNode(){
            this->next = nullptr;
            this->prev = nullptr;
        }

        cfastNode(cfastNode *next, cfastNode *prev, Type data){
            this->next = next;
            this->prev = prev;
            this->data = data;
        }

        cfastNode(cfastNode *prev, Type data){
            this->next = next;
            this->prev = prev;
        }

};

template<class Type>
class cfastTable{
private:
    cfastNode<Type> *start;
    cfastNode<Type> *last;
    int size;

public:
    cfastTable(){
        this->start = new cfastNode<Type>();
        this->last = new cfastNode<Type>();
        this->last->prev = this->start;
        this->start->next = this->last;
        this->size = 0;
    }

    int getSize(){
        return this->size;
    }

    void insert(int index, Type data){
        cfastNode<Type> *newNode = new cfastNode<Type>(data);
        cfastNode<Type> *temp = this->start->next;
        for(int i = 0; i < index; i++){
            temp = temp->next;
        }
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        this->size++;
    }

    void insertFront(Type data){
        cfastNode<Type> *newNode = new cfastNode<Type>(data);
        newNode->next = this->start->next;
        newNode->prev = this->start;
        this->start->next->prev = newNode;
        this->start->next = newNode;
        this->size++;
    }

    void insertLast(Type data){
        cfastNode<Type> *newNode = new cfastNode<Type>(data);
        newNode->next = this->last;
        newNode->prev = this->last->prev;
        this->last->prev->next = newNode;
        this->last->prev = newNode;
        this->size++;
    }
    
    Type getNodeValue(int index){
        cfastNode<Type> *temp = this->start->next;
        if(index - 1 < 0){
            return temp->data;                  //returns the first node
        }else if(index > size -1){
            return last->prev->data;            //returns the last node
        }
        for(int i = 0; i < index; i++){         //returns the node at the index
            temp = temp->next;
        }
        return temp->data;
    }
    
    void deleteNode(int index){
        cfastNode<Type> *temp;
        if(index - 1 < 0){
            temp = this->start->next;
            this->start->next = temp->next;
            temp->next->prev = this->start;
        }else if(index > size -1){
            temp = this->last->prev;
            this->last->prev = temp->prev;
            temp->prev->next = this->last;
        }else{
            temp = this->start->next;
            for(int i = 0; i < index; i++){
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
        this->size--;
    }

    std::string to_string(){
        string str = "";
        cfastNode<Type> *temp = this->start->next;
        while(temp != this->last){
            str += temp->data + " ";
            temp = temp->next;
        }
        return str;
    }
};


class cfastSQL
{       
    private:
        unordered_map<string,string> data_map;       //data hash_map 
        unordered_map<string,cfastTable<string>> table_map;  //table hash_map  
    
    public:
        cfastSQL(string file_name){
            ifstream dataInStream(file_name);
            string key,value;

            while(dataInStream >> key >> value){
                if(key.compare(SpiltKey) == 0){
                    break;
                }
                data_map[key] = value;
            }


            while(dataInStream >> key){
                if(key.compare(SpiltKey) == 0){
                    break;
                }
                while(dataInStream >> value){
                    if(value.compare(SpiltKey) == 0){
                        break;
                    }
                    table_map[key].insertLast(value);
                }
            }
        };

        cfastSQL(){};

        ~cfastSQL(){};

        void savecfastSQL(string file_name){
            ofstream dataOutStream(file_name);
            dataOutStream<<print_all_map_data()
                         <<SpiltKey<<" "<<SpiltValue<< endl;
            for(auto i:table_map){
                dataOutStream<<i.first<<" "<<i.second.to_string()
                             <<SpiltValue<<endl;
            }
            dataOutStream<<SpiltKey<<endl;
        };

        void set_map_data(string key ,string value){
            data_map[key]=value;
        }

        string get_map_data(string key){
            return data_map[key];
        }

        string print_all_map_data(){
            stringstream ss;
            for(auto i:data_map){
                ss<<i.first<<" "<<i.second<<endl;
            }
            return ss.str();
        }

        void delete_map_data(string key){
            data_map.erase(key);
        }

        void delete_all_map_data(){
            data_map.clear();
        }

        void insert_table_value_front(string key, string value){
            table_map[key].insertFront(value);
        }

        void insert_table_value_last(string key, string value){
            table_map[key].insertLast(value);
        }

        void insert_table_value_index(string key, int index, string value){
            table_map[key].insert(index,value);
        }

        string get_table_value(string key, int index){
            return table_map[key].getNodeValue(index);
        }

        string get_table_value_front(string key){
            return table_map[key].getNodeValue(0);
        }

        string get_table_value_last(string key){
            return table_map[key].getNodeValue(table_map[key].getSize()-1);
        }

        void delete_table_value_index(string key, int index){
            table_map[key].deleteNode(index);
        }

        string pop_table_front(string key){
            string value = table_map[key].getNodeValue(0);
            table_map[key].deleteNode(0);
            return value;
        }

        string pop_table_value_last(string key){
            string value = table_map[key].getNodeValue(table_map[key].getSize()-1);
            table_map[key].deleteNode(table_map[key].getSize()-1);
            return value;
        }

};



#endif /* cfastSQL_head */
