#include<bits/stdc++.h>
using namespace std;
class DataType{
public:
    //赋初值构造
    DataType(char _value):  val_char(_value),_type("char"){}
    DataType(int _value):   val_int(_value),_type("int"){}
    DataType(float _value): val_float(_value),_type("float"){}
    //复制构造
    DataType(DataType &tmp){
        _type=tmp._type;
        if(_type=="char")       val_char=tmp.val_char;
        else if(_type=="int")   val_int=tmp.val_int;
        else if(_type=="float") val_float=tmp.val_float;
        else                    val_char=val_int=val_float=0;
    }
    //默认构造
    DataType(){_type="none";val_char=val_int=val_float=0;}

    //编辑对象
    void Set_Value(char _value)  {_type="char";val_char=_value;}
    void Set_Value(int _value)   {_type="int";val_int=_value;}
    void Set_Value(float _value) {_type="float";val_float=_value;}

    //获取对象信息
    inline string Get_Type(){return _type;}
    char Get_char();
    int Get_int();
    float Get_float();

    //无需判断类型，直接输出对象的值
    void Print();

private:
    string _type;
    char val_char;
    int val_int;
    float val_float;
};

char DataType::Get_char(){
    if(_type=="char") return val_char;
    throw runtime_error("Type_Error!");
}
int DataType::Get_int(){
    if(_type=="int") return val_int;
    throw runtime_error("Type_Error!");
}
float DataType::Get_float(){
    if(_type=="float") return val_float;
    throw runtime_error("Type_Error!");
}


void DataType::Print(){
    if(_type=="char")       cout << val_char;
    else if(_type=="int")   cout << val_int;
    else if(_type=="float") cout << val_float;
    else                    cout << "none";
}

int main(){
    DataType x1('A');
    cout << "Type1:" << x1.Get_Type() << "   " << "Value1:" << x1.Get_char() << endl;
    DataType x2(18);
    cout << "Type2:" << x2.Get_Type() << "   " << "Value2:" << x2.Get_int() << endl;
    DataType x3((float)3.14);
    cout << "Type3:" << x3.Get_Type() << "   " << "Value3:" << x3.Get_float() << endl;
    x3.Set_Value('C');
    cout << "Type3_1:" << x3.Get_Type() << "   " << "Value3_1:"; x3.Print();cout << endl;
    DataType x4(x3);
    cout << "Type4:" << x4.Get_Type() << "   " << "Value4:"; x4.Print();cout << endl;
    DataType x5;
    cout << "Type5:" << x5.Get_Type() << "   " << "Value5:"; x5.Print();cout << endl;
}