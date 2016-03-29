#ifndef COMPARATOR_H_INCLUDED
#define COMPARATOR_H_INCLUDED

class IntegerComparator
{
public:
    static int compare(int first, int second);
    static bool equals (int first, int second);
private:
    IntegerComparator();
};

int IntegerComparator::compare(int first, int second)
{
    if (first < second)
        return -1;
    if (first > second)
        return 1;
    else
        return 0;
}

bool IntegerComparator::equals(int first, int second)
{
    if (first == second)
        return true;
    return false;
}
#endif // COMPARATOR_H_INCLUDED
