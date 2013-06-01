#ifdef USE_PRODUCTION

#ifndef LABOUR_H
#define LABOUR_H


class Human;

class Labour
{
public:
    Labour(Human& human);

    bool Ok();
    double Productivity();

private:
    Human& m_human;
};

#endif // LABOUR_H

#endif//    USE_PRODUCTION
