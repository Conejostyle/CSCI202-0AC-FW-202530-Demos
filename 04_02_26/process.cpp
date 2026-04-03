#include "process.h"

process::process(std::string name, int priority, int slicesNeeded, int IOSlice, statusType status)
{
    this->name = name;
    if (priority <= 0)
    {
        this->priority = 1;
    }
    else
        this->priority = priority;
    if (slicesNeeded <= 0)
        this->slicesNeeded = 5;
    else
        this->slicesNeeded = slicesNeeded;
    this->IOSlice = IOSlice;
    this->status = status;
    this->slicesUsed = 0;
}
process::process(const process &o)
{
    this->name = o.name;
    this->priority = o.priority;
    this->status = o.status;
    this->IOSlice = o.IOSlice;
    this->slicesNeeded = o.slicesNeeded;
    this->slicesUsed = o.slicesUsed;
}
const process &process::operator=(const process &p)
{
    this->name = p.name;
    this->priority = p.priority;
    this->status = p.status;
    this->IOSlice = p.IOSlice;
    this->slicesNeeded = p.slicesNeeded;
    this->slicesUsed = p.slicesUsed;
    return *(this);
}
void process::run()
{
    this->slicesUsed++;
    if (slicesNeeded == slicesUsed)
        changeStatus(FINISHED);
    else if (slicesUsed == IOSlice)
        changeStatus(WAITING);
}
statusType process::getStatus()
{
    return status;
}
void process::changePriority(int priority)
{
    this->priority = priority;
}
void process::changeStatus(statusType status)
{
    this->status = status;
}
bool process::operator>(const process &o) const
{
    return this->priority > o.priority;
}
bool process::operator<(const process &o) const
{
    return this->priority < o.priority;
}
bool process::operator>=(const process &o) const
{
    return this->priority >= o.priority;
}
bool process::operator<=(const process &o) const
{
    return this->priority <= o.priority;
}
bool process::operator==(const process &o) const
{
    return this->priority == o.priority;
}
bool process::operator!=(const process &o) const
{
    return this->priority != o.priority;
}
std::ostream &operator<<(std::ostream &o, const process &p)
{
    o << "Process Name: " << p.name << std::endl;
    o << "Status: " << statusToStr.at(p.status) << std::endl;
    o << "Priority: " << p.priority << std::endl;
    o << "Time slices left to finish: " << p.slicesNeeded - p.slicesUsed;
    return o;
}
