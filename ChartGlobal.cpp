#include "ChartGlobal.h"

chartGlobal::chartGlobal() : title("Default title"), width(0){}

chartGlobal::chartGlobal(const chartGlobal & copy): istances(std::vector<chartItem*>(copy.tableHeight())), title(copy.title), width(copy.width), timeline(copy.timeline){
    for(u_int32 i = 0;i< tableHeight();i++)
    {istances[i] = new chartItem(*(copy.istances[i]));}
}
chartGlobal& chartGlobal::operator=(const chartGlobal &assign){
    if(this != &assign){
        while(!istances.empty())
        {delete *(istances.begin());
        istances.erase(istances.begin());}
        for(auto it = assign.istances.begin(); it != assign.istances.end();++it){
            chartItem aux = **it;
            istances.push_back(new chartItem(aux));
        }
        timeline = assign.timeline;
    }
    return *this;
}
chartGlobal::~chartGlobal(){
    for(auto it : istances)
        delete it;
}
///////////////////////////////////////////////////////////
std::string chartGlobal::getTitle() const{
    return title;
}

void chartGlobal::setTitle(std::string text){
    title = text;
}
///////////////////////////////////////////////////////////

void chartGlobal::addEntry(const std::string &text,u_int32 index){
    if(index >= tableHeight())
    istances.push_back(new chartItem(text,Data(width)));
    else
    istances.insert(istances.begin() + index,new chartItem(text,Data(width)));;
}

void chartGlobal::removeEntry(u_int32 count){
    if(tableHeight() - count + 1 > 0){
     for(; count > 0;count--){
    auto target = --(istances.end());
    chartItem * aux = *target;
    istances.pop_back();
    delete aux;
        }
    }
}

chartItem * chartGlobal::operator[](u_int32 k) const{
    if(k < tableHeight()){
    auto it = istances.begin() + k;
    return const_cast<chartItem *>(*it);
    }
    else throw std::string("Out of bounds!");
}

std::string chartGlobal::getLabel(u_int32 index) const{
    if(index > tableHeight()) throw std::string("Out of bounds!");
    else return istances[index]->getLabel();
}

void chartGlobal::setLabel(u_int32 index, std::string text){
    if(index < tableHeight()){
    auto it = istances.begin() + index;
    (*it)->setLabel(text);
    }
    else throw std::string("Out of bounds!");
}
///////////////////////////////////////////////////////////
void chartGlobal::addColumn(double k,u_int32 count){
    if(!istances.empty()){

        for(auto it : istances)
            it->Append(k,count);

        for(u_int32 j = count;j > 0;j--)
            timeline.push_back("Empty!");
        width += count;
      }
}

void chartGlobal::removeColumn(u_int32 count){
    if(!istances.empty() && tableWidth() - count >= 0){

            for(auto it : istances)
               it->Pop(count);

            for(u_int32 j = count;j > 0;j--)
                timeline.pop_back();

            width -= count;
           }
}
///////////////////////////////////////////////////////////

void chartGlobal::modIndex(u_int32 x, u_int32 y, double val){
    if(x < tableHeight())
        istances[x]->modIndex(y,val);
    else throw std::string("Out of bounds!");
}

double chartGlobal::atIndex(u_int32 x, u_int32 y) const{
    if(x < tableHeight() && y < tableWidth())
        return istances[x]->operator[](y);
    else throw std::string("Out of bounds!");
}

std::string chartGlobal::atTimelineIndex(u_int32 k) const{
    if( k < tableWidth())
        return timeline[k];
    else throw std::string("Out of bounds!");
}

void chartGlobal::modTimelineIndex(u_int32 k,const std::string & over){
    if( k < tableWidth())
        timeline[k] = over;
    else throw std::string("Out of bounds!");
}
u_int32 chartGlobal::tableHeight() const{
    return istances.size();
}

u_int32 chartGlobal::tableWidth() const{
    return width;
}




