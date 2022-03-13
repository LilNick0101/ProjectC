#ifndef CHARTGLOBAL_H
#define CHARTGLOBAL_H
#include"Data.h"

class chartGlobal
{
private:

    std::vector<chartItem*> istances;
    std::string title;
    u_int32 width;
    std::vector<std::string> timeline;
public:

    chartGlobal();

    chartGlobal(const chartGlobal & copy);

    chartGlobal& operator=(const chartGlobal& assign);

    ~chartGlobal();

    std::string getTitle() const;

    void setTitle(std::string title);

    std::string getLabel(u_int32 index) const;

    void setLabel(u_int32 index, std::string text);

    void addEntry(const std::string & text,u_int32 index = -1);

    void modIndex(u_int32,u_int32,double);

    double atIndex(u_int32,u_int32) const;

    std::string atTimelineIndex(u_int32) const;

    void modTimelineIndex(u_int32,const std::string &);

    void removeEntry(u_int32 count = 1);

    void addColumn(double k = 0,u_int32 count = 1);

    void removeColumn(u_int32 count = 1);

    chartItem* operator[](u_int32 k) const;

    u_int32 tableHeight() const;

    u_int32 tableWidth() const;
};
#endif // CHARTGLOBAL_H
