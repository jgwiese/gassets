#ifndef MATERIAl_H
#define MATERIAl_H

#include <string>


class t_material {
public:
    t_material(std::string name);
    ~t_material();
    std::string get_name();

private:
    std::string name;
};

#endif // MATERIAl_H

