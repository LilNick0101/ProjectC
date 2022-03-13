#include "Data.h"

Data::Data(){}

Data::Data(u_int32 size): values(std::vector<double>(size,0)){}

Data::Data(double k,u_int32 size) :values(std::vector<double>(size,k)){}

bool Data::IsEmpty() const{
      return values.empty();
}

u_int32 Data::Size() const{
    return values.size();
}

double Data::Max() const{
    double max = *values.begin();
    for(auto it : values)
    {
        if(it > max)
            max = it;
    }
    return max;
}

double Data::Min() const{
    double min = *values.begin();
    for(auto it : values)
    {
        if(it < min)
            min = it;
    }
    return min;
}
void Data::Pop(u_int32 count){
    for(;count > 0;--count){
    if(!IsEmpty()){
    values.pop_back();
    }
    else break;
    }
}

void Data::Append(double k,u_int32 count){
    for(;count > 0;--count)
    values.push_back(k);
}

double & Data::operator[](u_int32 k) const{
    if(k < Size()){
    auto it = values.begin() + k;
    return const_cast<double &>(*it);
    }
    else throw std::string("Out of bounds!");
}

double Data::obtainTotal() const{
    double tot = 0;
    for(auto it : values)
    {
          tot += it;
    }
    return tot;
}

void Data::modIndex(u_int32 index, double value){
    if(index < Size()){
      values[index] = value;
    }
    else throw std::string("Out of bounds!");
}


chartItem::chartItem(){}

chartItem::chartItem(const std::string & name, const Data & a) : Data(a),label(name){}

void chartItem::setLabel(std::string text){label = text;}

std::string chartItem::getLabel() const{return label;}
