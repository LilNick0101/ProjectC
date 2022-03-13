#ifndef DATA_H
#define DATA_H
#include<vector>
#include<string>

typedef unsigned int u_int32;
class Data
{
private:
    std::vector<double> values;
public:

    Data();

    Data(u_int32 size);

    Data(double k,u_int32 size);

    bool IsEmpty() const;

    u_int32 Size() const;

    double Max() const;

    double Min() const;

    double obtainTotal() const;

    void Append(double k,u_int32 count = 1);

    void Pop(u_int32 count = 1);

     double & operator[](u_int32 k) const;

     void modIndex(u_int32 index,double value);
};

class chartItem : public Data{
private:
    std::string label;
public:
    chartItem();

    chartItem(const std::string & name,const Data & a);

    void setLabel(std::string text);

    std::string getLabel() const;
};

#endif // DATA_H
