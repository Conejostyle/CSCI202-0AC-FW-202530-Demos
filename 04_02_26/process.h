#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <map>
#include <iostream>

enum statusType
{
    WAITING,
    READY,
    FINISHED
};

const std::map<std::string, statusType> strToStatus = {{"waiting", WAITING}, {"ready", READY}, {"finished", FINISHED}};
const std::map<statusType, std::string> statusToStr = {{WAITING, "Waiting"}, {READY, "Ready"}, {FINISHED, "Finished"}};

class process
{
public:
    process(std::string, int, int, int, statusType);
    process(const process &);
    void run();
    statusType getStatus();
    void changePriority(int);
    void changeStatus(statusType);
    const process &operator=(const process &);
    bool operator>(const process &) const;
    bool operator<(const process &) const;
    bool operator>=(const process &) const;
    bool operator<=(const process &) const;
    bool operator==(const process &) const;
    bool operator!=(const process &) const;
    friend std::ostream &operator<<(std::ostream &, const process &);

private:
    std::string name;
    int priority;
    int slicesNeeded;
    int IOSlice;
    int slicesUsed;
    statusType status;
};

#endif